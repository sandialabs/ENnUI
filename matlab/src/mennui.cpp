#include "mennui.hpp"

#include <Eigen/Core>
#include <Eigen/Dense>

#include "ecef.hpp"
#include "ennui_types.hpp"
#include "gravitation.hpp"
#include "wgs84.hpp"

typedef ennui::geodetic::Wgs84 GeodeMdl;

void geodetic::gravitation_ecef(const double position[3], double gamma[3]) {
  const ennui::ConstMapVector3 p(position);
  ennui::MapVector3 g(gamma);
  g = ennui::geodetic::gravitation_ecef<GeodeMdl>(p);
}

void mechanization::ecef::fwd_pva_S03(
    const double position_minus[3], const double velocity_minus[3],
    const double attitude_minus[9], const double gravitation[3],
    const double specific_force[3], const double angular_rate[3], double dt,
    double position_plus[3], double velocity_plus[3], double attitude_plus[9]) {
  const ennui::ConstMapVector3 pm(position_minus);
  const ennui::ConstMapVector3 vm(velocity_minus);
  const ennui::ConstMapMatrix3x3 am(attitude_minus);
  const ennui::ConstMapVector3 g(gravitation);
  const ennui::ConstMapVector3 f(specific_force);
  const ennui::ConstMapVector3 w(angular_rate);
  ennui::MapVector3 pp(position_plus);
  ennui::MapVector3 vp(velocity_plus);
  ennui::MapMatrix3x3 ap(attitude_plus);
  ennui::mechanization::ecef::fwd_pva_S03<GeodeMdl>(pm, vm, am, g, f, w, dt, pp,
                                                    vp, ap);
}
