/**
 * @file ennui_types.hpp
 * @brief Common types within ennui
 */

#pragma once

#include <Eigen/Core>

// #define ENNUI_MATRIX_ROW_MAJOR

#ifdef ENNUI_MATRIX_ROW_MAJOR
#define EIGEN_STORAGE Eigen::RowMajor
#else
#define EIGEN_STORAGE Eigen::ColMajor
#endif

/**
 * @namespace ennui
 * @brief primary namespace for ennui
 */
namespace ennui {
/**
 * @namespace ennui::math
 * @brief namespace for general mathematical operations
 */
namespace math {}
/**
 * @namespace ennui::mechanization
 * @brief namespace for mechanization (inertial state propagation)
 */
namespace mechanization {
/**
 * @namespace ennui::mechanization::ecef
 * @brief namespace for ecef mechanization
 */
namespace ecef {}
}  // namespace mechanization
/**
 * @namespace ennui::geodetic
 * @brief namespace for geodetic models
 */
namespace geodetic {}

// Commonly used fixed size vectors
typedef Eigen::Matrix<double, 1, 1, EIGEN_STORAGE> Scalar;
typedef Eigen::Vector2d Vector2;
typedef Eigen::Vector3d Vector3;
typedef Eigen::Vector4d Vector4;
typedef Eigen::Matrix<double, 10, 1, EIGEN_STORAGE> Vector10;
typedef Eigen::Matrix<double, 16, 1, EIGEN_STORAGE> Vector16;
typedef Eigen::Matrix<double, 3, 3, EIGEN_STORAGE> Matrix3x3;

// Reference types for efficiency
typedef const Eigen::Ref<const Vector3> ConstRefVector3;
typedef Eigen::Ref<Vector3> RefVector3;

// Convenience variables mapping C++ types to Eigen efficiently
typedef const Eigen::Map<const ennui::Vector3> ConstMapVector3;
typedef const Eigen::Map<const ennui::Matrix3x3> ConstMapMatrix3x3;
typedef Eigen::Map<ennui::Vector3> MapVector3;
typedef Eigen::Map<ennui::Matrix3x3> MapMatrix3x3;

}  // namespace ennui
