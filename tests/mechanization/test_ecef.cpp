#include "ecef.hpp"
#include "gravitation.hpp"
#include "landmarks.hpp"
#include "test_utils.hpp"
#include "wgs84.hpp"

using ennui::Matrix3x3;
using ennui::Vector3;
using ennui::geodetic::gravitation_ecef;
using ennui::geodetic::Wgs84;
using ennui::mechanization::ecef::fwd_pva_S03;

//! Measure error after single-step of state propagation
template <typename T>
void test_single_prop_mean(const prop_mean &pm, T tolerance) {
  Vector3 gamma;
  Vector3 position{0., 0., 0.};
  Vector3 velocity{0., 0., 0.};
  Matrix3x3 attitude{{0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.}};

  gamma = gravitation_ecef<Wgs84>(pm.prior.position);

  fwd_pva_S03<Wgs84>(pm.prior.position, pm.prior.velocity, pm.prior.attitude,
                     gamma, pm.specific_force, pm.angular_rate, pm.dt, position,
                     velocity, attitude);

  REQUIRE_REL(position, pm.posterior.position, tolerance);
  PRINT_ERRORS(position, pm.posterior.position, "position propagation");
  REQUIRE_REL(velocity, pm.posterior.velocity, tolerance);
  PRINT_ERRORS(velocity, pm.posterior.velocity, "velocity propagation");
  REQUIRE_REL(attitude.reshaped(), pm.posterior.attitude.reshaped(), tolerance);
  PRINT_ERRORS(attitude, pm.posterior.attitude, "attitude propagation");
}

TEST_CASE("Propagate", "[mechanization]") {
  auto tolerance = 1e-15;
  PRINT_txt("White House --------------------");
  test_single_prop_mean(WhiteHouse_mean_prop, tolerance);
  PRINT_txt("Sydney Opera House -------------");
  test_single_prop_mean(SydneyOpera_mean_prop, tolerance);
  PRINT_txt("Aconcagua Peak -----------------");
  test_single_prop_mean(AconcaguaPeak_mean_prop, tolerance);
}
