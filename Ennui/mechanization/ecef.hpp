/**
 * @file ecef.hpp
 * @brief Earth centered earth fixed mechanization equations.
 */

#pragma once
#include <math.h>

#include "ennui_types.hpp"
#include "rotation.hpp"

namespace ennui {

namespace mechanization {
namespace ecef {

/**
 * @brief Forward propagation of mean state in ECEF reference frame
 *
 * @tparam GeodeMdl geodetic model
 * @param[in] position_minus prior position as 3-vector
 * @param[in] velocity_minus prior velocity as 3-vector
 * @param[in] attitude_minus prior attitude as 3x3 matrix
 * @param[in] gravitation gravitation as 3-vector
 * @param[in] specific_force specific force measurement ($Delta v$) as 3-vector
 * @param[in] angular_rate angular force measurement ($\Delta \theta$) as
 * 3-vector
 * @param[in] dt timestep scalar
 * @param[out] position_plus propagated position as 3-vector
 * @param[out] velocity_plus propagated velocity as 3-vector
 * @param[out] attitude_plus propagated attitude as 3x3 matrix
 *
 * See Section 5.5.1 in \cite groves_principles_2013.
 */
template <class GeodeMdl>
void fwd_pva_S03(ConstRefVector3 &position_minus,
                 ConstRefVector3 &velocity_minus,
                 const Eigen::Ref<const Matrix3x3> &attitude_minus,
                 ConstRefVector3 &gravitation, ConstRefVector3 &specific_force,
                 ConstRefVector3 &angular_rate, double dt,
                 RefVector3 position_plus, RefVector3 velocity_plus,
                 Eigen::Ref<Matrix3x3> attitude_plus) {
  const Matrix3x3 Omega =
      math::R3_to_so3({0, 0, GeodeMdl::EARTH_ROTATION_RATE});

  // Integrate, constant-rate assumption
  const Vector3 alpha = angular_rate * dt;
  // Eq. (5.69) \cite groves_principles_2013
  const Matrix3x3 Rb_prop = math::R3_to_SO3(alpha);

  // Propagate attitude
  //
  // Eq. (5.75) \cite groves_principles_2013
  attitude_plus = attitude_minus * Rb_prop - dt * Omega * attitude_minus;
  // TODO : Alternative derivation?!?
  // attitude_plus = math::R3_to_SO3({0, 0, -dt *
  // Wgs84::EARTH_ROTATION_RATE}) *
  //                attitude_minus * Rb_prop;
  attitude_plus = math::normalize_SO3_Groves(attitude_plus);

  // Specific force update
  //
  // Compute mean body rotation matrix from gyro measurements
  Matrix3x3 Rb_mean;
  const double alpha_norm = alpha.stableNorm();
  const Matrix3x3 alpha_cross = math::R3_to_so3(alpha);
  if (alpha_norm > 1e-10) {
    Rb_mean.noalias() = math::mean_attitude_update(alpha_cross, alpha_norm);
  } else {
    // Small angle approximation...
    Rb_mean.noalias() =
        math::mean_attitude_update_approx(alpha_cross, alpha_norm);
  }

  // Eq. (5.85) \cite groves_principles_2013
  Matrix3x3 Reb_mean =
      attitude_minus * Rb_mean - 0.5 * dt * Omega * attitude_minus;

  const Vector3 fe_ib = Reb_mean * specific_force;

  // Propagate (acceleration) velocity and position
  //
  // Eq. (5.36), using Eq. (2.132) \cite groves_principles_2013
  const Vector3 ae_eb = fe_ib + gravitation - Omega * Omega * position_minus -
                        2 * Omega * velocity_minus;
  velocity_plus = velocity_minus + ae_eb * dt;
  // Eq. (5.38) \cite groves_principles_2013
  position_plus = position_minus + 0.5 * dt * (2 * velocity_plus - ae_eb * dt);
}

}  // namespace ecef
}  // namespace mechanization
}  // namespace ennui
