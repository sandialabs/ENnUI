/**
 * @file rotation.hpp
 * @brief Rotational mathematical operations
 */

#pragma once

#include <math.h>

#include <Eigen/Dense>

#include "ennui_types.hpp"

namespace ennui {
namespace math {

//! Vector to skew-symmetric matrix
inline Matrix3x3 R3_to_so3(const Vector3 &x) {
  Matrix3x3 R{                       //
              {0.00, -x[2], +x[1]},  //
              {+x[2], 0.00, -x[0]},  //
              {-x[1], +x[0], 0.00}};
  return R;
}

/**
 * @brief Euler's finite rotation, standard form
 *
 * @param  OmegaNormed skew-symmetric matrix of normalized 3-vector
 * @param  xnorm magnitude of the rotation vector
 * @return rotation matrix
 *
 * Supplying Omega normed and its magnitude as separate variables avoids
 * computing the sinc function (well-defined at 0 but problematic numerically).
 * See eq. (5.73) \cite groves_principles_2013
 */
inline Matrix3x3 euler_finite_rotation(
    const Eigen::Ref<const Matrix3x3> &OmegaNormed, double xnorm) {
  return Matrix3x3::Identity() + sin(xnorm) * OmegaNormed +
         (1 - cos(xnorm)) * (OmegaNormed * OmegaNormed);
}

/**
 * @brief Euler's finite rotation, small angle approximation
 *
 * @param  Omega skew-symmetric matrix (NOT normalized)
 * @param  xnorm magnitude of the rotation vector
 * @return rotation matrix
 *
 * Employing the small angle approximation avoids both evaluating trigonometric
 * functions and variable division. See eq. (5.72) \cite groves_principles_2013
 */
inline Matrix3x3 euler_finite_rotation_approx(
    const Eigen::Ref<const Matrix3x3> &Omega, double xnorm) {
  return Matrix3x3::Identity() + (1 - xnorm * xnorm / 6) * Omega +
         (0.5 - xnorm * xnorm / 24) * (Omega * Omega);
}

/**
 * @brief Euler's finite rotation, stable
 *
 * @param  x rotation vector
 * @return rotation matrix
 *
 * Stable version of the rotation expansion. Switches between small-angle
 * approximation and exact based on the vector magnitude to avoid numerical
 * instability.
 */
inline Matrix3x3 R3_to_SO3(ConstRefVector3 &x) {
  const double xnorm = sqrt(x.dot(x));
  Matrix3x3 Omega;
  Matrix3x3 rslt = Matrix3x3::Identity();
  if (xnorm > 1e-6) {
    // Standard form (Eq. 5.73)
    Omega.noalias() = R3_to_so3(x / xnorm);
    rslt.noalias() = euler_finite_rotation(Omega, xnorm);
  } else {
    // Small angle approximation (Eq. 5.72), without sinc
    Omega.noalias() = R3_to_so3(x);
    rslt.noalias() = euler_finite_rotation_approx(Omega, xnorm);
  }
  return rslt;
}

//! Quaternion to rotation matrix
inline Matrix3x3 R4_to_SO3(const Vector4 &q) {
  // Get indices for state components
  const auto vect_idx = Eigen::seqN(1, 3);

  const double qwt = 1.0 / sqrt(q.dot(q));
  const double qs = qwt * q[0];
  const Vector3 qv = qwt * q(vect_idx);

  // Eq. 117 [sola_quaternion_2017]
  return (qs * qs - qv.dot(qv)) * Matrix3x3::Identity() +
         2 * qv * qv.transpose() + 2 * qs * R3_to_so3(qv);
}

//! Matrix normalization by SVD
inline Matrix3x3 normalize_SO3(const Matrix3x3 R) {
  // Perform SVD
  Eigen::JacobiSVD<Matrix3x3> svd(R, Eigen::ComputeFullU | Eigen::ComputeFullV);

  // Reconstruct the normalized rotation matrix
  return svd.matrixU() * svd.matrixV().transpose();
}

//! Matrix normalization using Grove's approximation
inline Matrix3x3 normalize_SO3_Groves(const Matrix3x3 R) {
  const double d01 = R.row(0).dot(R.row(1));
  const double d02 = R.row(0).dot(R.row(2));
  const double d12 = R.row(1).dot(R.row(2));
  Matrix3x3 rslt;
  rslt.row(0) = R.row(0) - 0.5 * d01 * R.row(1) - 0.5 * d02 * R.row(2);
  rslt.row(1) = -0.5 * d01 * R.row(0) + R.row(1) - 0.5 * d12 * R.row(2);
  rslt.row(2) = -0.5 * d02 * R.row(0) - 0.5 * d12 * R.row(1) + R.row(2);
  for (int i = 0; i < 3; i++) {
    rslt.row(i) = rslt.row(i).stableNormalized();
  }
  return rslt;
}

/**
 * @brief Mean attitude update from delta-theta ("exact")
 *
 * @param  alpha_cross skew-symmetric matrix (NOT normalized)
 * @param  alpha_norm magnitude of the rotation vector
 * @return general matrix (3x3)
 *
 * See eq. (5.84) \cite groves_principles_2013
 */
inline Matrix3x3 mean_attitude_update(
    const Eigen::Ref<const Matrix3x3> &alpha_cross, double alpha_norm) {
  return Matrix3x3::Identity() +
         ((1 - cos(alpha_norm)) / (alpha_norm * alpha_norm)) * alpha_cross +
         (1 - sin(alpha_norm) / alpha_norm) / (alpha_norm * alpha_norm) *
             alpha_cross * alpha_cross;
}

/**
 * @brief Approximate mean attitude update from delta-theta
 *
 * @param  alpha_cross skew-symmetric matrix (NOT normalized)
 * @param  alpha_norm magnitude of the rotation vector
 * @return general matrix (3x3)
 *
 * See eq. (5.84) \cite groves_principles_2013
 */
inline Matrix3x3 mean_attitude_update_approx(
    const Eigen::Ref<const Matrix3x3> &alpha_cross, double alpha_norm) {
  return Matrix3x3::Identity() +
         (0.5 - alpha_norm * alpha_norm / 24.0) * alpha_cross +
         (1.0 / 6.0 - alpha_norm * alpha_norm / 120.0) * alpha_cross *
             alpha_cross;
}

}  // namespace math
}  // namespace ennui
