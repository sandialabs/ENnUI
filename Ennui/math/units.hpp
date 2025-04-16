/**
 * @file units.hpp
 * @brief Unit conversions and mathematical constants
 */

#pragma once

namespace ennui {
namespace math {

//! Fixed mathematical constants and conversion factors.
class Units {
 public:
  //! Pi mathematical constant
  static constexpr auto PI = 3.14159265358979323846;

  //! Multiplicatively converts from degrees to radians
  static constexpr auto DEGREES = Units::PI / 180.0;
};
}  // namespace math
}  // namespace ennui
