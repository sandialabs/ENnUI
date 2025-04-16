/**
 * @file wgs84.hpp
 * @brief Geodetic model based on the World Geodetic System 1984
 */

#pragma once

#include "ennui_types.hpp"

namespace ennui {
namespace geodetic {

/**
 * @brief World geodetic system 1984 constants
 *
 * Collection of constants generally considered WGS 84. Slight discrepancies
 * exists between authors (e.g. level of precision). We use NGA Standard 0036
 * \cite NGA-STND-0036.
 */
class Wgs84 {
 public:
  /**
   * @brief Semi-major axis $a$ in $m$
   *
   * WGS 84 defining parameter. See Section 3.4.1 \cite NGA-STND-0036.
   */
  static constexpr auto EARTH_SEMIMAJOR_AXIS = 6378137.0;

  /**
   * @brief Earth flattening factor $1/f$
   *
   * WGS 84 defining parameter. See Section 3.4.2 \cite NGA-STND-0036.
   */
  static constexpr auto EARTH_INVERSE_FLATTENING = 298.257223563;

  /**
   * @brief Earth gravitational field constant $GM$ in $m^3/sec^2$.
   *
   * WGS84 defining parameter. See Section 3.4.3 \cite NGA-STND-0036.
   */
  static constexpr auto EARTH_GRAVITATIONAL_FIELD = 3.986004418e14;

  /**
   * @brief Mean angular velocity of the Earth (omega) in rads/s
   *
   * WGS84 defining parameter (Section 3.4.4 \cite NGA-STND-0036), but with
   * increased precision. See Section 3.7.2 \cite NGA-STND-0036. Note,
   * additional precision attributed as the Inertnational Astronomical Union
   * (IAU) or GRS 67 version and not original to WGS84.
   */
  static constexpr auto EARTH_ROTATION_RATE = 7.2921151467e-5;

  /**
   * @brief Semi-mminor axis $b$ in $m$.
   *
   * Derived parameter $b = a(1-f)$. See Appendix B. Section 3.2 \cite
   * NGA-STND-0036
   */
  static constexpr auto EARTH_SEMIMINOR_AXIS =
      Wgs84::EARTH_SEMIMAJOR_AXIS *
      (1.0 - 1.0 / Wgs84::EARTH_INVERSE_FLATTENING);
  // static constexpr auto EARTH_SEMIMINOR_AXIS = 6.3567523142e6;

  /**
   * @brief Earth dynamical form factor f\$J_2f\$.
   *
   * Derived parameter. See Appendix B. Section 3.17 \cite NGA-STND-0036
   */
  static constexpr auto EARTH_DYNAMICAL_J2 = 1.082629821313e-3;

  /**
   * @brief Velocity of light $c$ in $m/s$
   *
   * Fundamental constant. See Section 3.6.1 \cite NGA-STND-0036
   */
  static constexpr auto SPEED_OF_LIGHT = 299792458.0;
};

}  // namespace geodetic
}  // namespace ennui
