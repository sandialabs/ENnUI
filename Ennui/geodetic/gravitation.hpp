/**
 * @file gravitation.hpp
 * @brief Gravitational models
 */

#pragma once
#include "ennui_types.hpp"

namespace ennui {
namespace geodetic {

/**
 * @brief Gravitation vector from ECEF position
 *
 * @tparam GeodeMdl geodetic model
 * @param position position in ECEF reference frame
 * @return gravitation vector
 *
 * Second order gravitational model. See eq.(2.142) \cite
 * groves_principles_2013.
 */
template <class GeodeMdl>
Vector3 gravitation_ecef(ConstRefVector3 &position) {
  Vector3 gravitation;

  // pre-compute scalars
  const auto &r_z = position[2];
  const auto r2 = position.squaredNorm();

  if (r2 < 1e-10) {
    // Guard div-0. Don't travel through center of the earth.
    assert(false);
    gravitation = Vector3{0., 0., 0.};
    return gravitation;
  }

  const auto inv_r2 = 1 / r2;
  const auto tmp1 = 5.0 * r_z * r_z * inv_r2;
  const auto tmp2 = 1.5 * GeodeMdl::EARTH_DYNAMICAL_J2 *
                    GeodeMdl::EARTH_SEMIMAJOR_AXIS *
                    GeodeMdl::EARTH_SEMIMAJOR_AXIS * inv_r2;
  const auto tmp3 =
      (-inv_r2) / position.norm() * GeodeMdl::EARTH_GRAVITATIONAL_FIELD;

  Vector3 working = {1. - tmp1, 1. - tmp1, 3. - tmp1};
  // Element-wise multiplication of 'vectors' requires conversion to 'arrays'
  working.array() = working.array() * position.array();

  gravitation.noalias() = ((tmp2 * working) + position) * tmp3;

  return gravitation;
}
}  // namespace geodetic
}  // namespace ennui
