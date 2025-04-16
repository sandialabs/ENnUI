/**
 * @file frame_transform.hpp
 * @brief Frame transformations
 */

#pragma once
#include <math.h>

#include "ennui_types.hpp"
#include "units.hpp"

namespace ennui {
namespace geodetic {

/**
 * @brief Convert position from geodetic lat, long, height coordinates to
 * Cartesian ECEF
 *
 * @tparam GeodeMdl geodetic model
 * @param[in]  position_llh position in geodetic lat, long, height coordinates
 * @return pos_ecef position in Cartesian ECEF coordinates
 *
 * See Equation (4.A.2) in \cite misra_global_2001
 */
template <class GeodeMdl>
Vector3 position_geodetic_to_ecef(ConstRefVector3 &position_llh) {
  using ennui::math::Units;

  // Lat, Lon, Alt in [rad, rad, m]
  const auto phi = position_llh[0] * Units::DEGREES;
  const auto lambda = position_llh[1] * Units::DEGREES;
  const auto h = position_llh[2];

  // Earth constants
  static constexpr auto f = 1.0 / GeodeMdl::EARTH_INVERSE_FLATTENING;
  static constexpr auto e2 = 2.0 * f - f * f;

  const auto sin_phi = sin(phi);
  const auto cos_phi = cos(phi);
  const auto sin_lambda = sin(lambda);
  const auto cos_lambda = cos(lambda);

  // Note, e<<1 such that result is >0. No div-0 concern.
  const auto den2 = 1 - e2 * sin_phi * sin_phi;

  // (4.A.1) \cite misra_global_2001
  auto N = GeodeMdl::EARTH_SEMIMAJOR_AXIS / sqrt(den2);

  // (4.A.2) \cite misra_global_2001
  return Vector3{(N + h) * cos_phi * cos_lambda, (N + h) * cos_phi * sin_lambda,
                 (N * (1 - e2) + h) * sin_phi};
}
}  // namespace geodetic
}  // namespace ennui
