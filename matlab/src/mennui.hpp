#pragma once

// NOLINTNEXTLINE
#include "mennui_Export.h"

// As of 9/16/2024
// MATLAB does not understand std::arrays
// MATLAB does understand std::vectors, but requires users to hand-correct
// size in library definition file.

mennui_EXPORT namespace geodetic {
  mennui_EXPORT void gravitation_ecef(const double position[3],
                                      double gamma[3]);
}
mennui_EXPORT namespace math {}

mennui_EXPORT namespace mechanization {
  mennui_EXPORT namespace ecef {
    mennui_EXPORT void fwd_pva_S03(
        const double position_minus[3], const double velocity_minus[3],
        const double attitude_minus[9], const double gravitation[3],
        const double specific_force[3], const double angular_rate[3], double dt,
        double position_plus[3], double velocity_plus[3],
        double attitude_plus[9]);
  }
}
