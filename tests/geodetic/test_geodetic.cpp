#include "frame_transform.hpp"
#include "gravitation.hpp"
#include "landmarks.hpp"
#include "test_utils.hpp"
#include "wgs84.hpp"

using ennui::Vector3;
using ennui::geodetic::gravitation_ecef;
using ennui::geodetic::position_geodetic_to_ecef;
using ennui::geodetic::Wgs84;

//! Validate WGS84 omega vector
TEST_CASE("WGS84 omega", "[geodetic]") {
  auto tolerance = 1e-14;

  Vector3 actual, expected = {0, 0, 7.2921151467e-5};
  // ennui::omega_vec(actual);
  actual = Vector3{0, 0, Wgs84::EARTH_ROTATION_RATE};

  REQUIRE_REL(actual, expected, tolerance);
  std::cout << "WGS84 Omega" << std::endl;
  print_errors(actual, expected);
}

//! Validate frame conversion: LLA to ECEF
TEST_CASE("lla landmarks", "[geodetic]") {
  auto tolerance = 1e-14;

  // White House
  Vector3 actual = position_geodetic_to_ecef<Wgs84>(WhiteHouse_LLH);
  Vector3 expected = WhiteHouse_ECEF;
  REQUIRE_REL(actual, expected, tolerance);
  PRINT_ERRORS(actual, expected, "LLA to ECEF, White House");

  // Sydney Opera House
  actual = position_geodetic_to_ecef<Wgs84>(SydneyOpera_LLH);
  expected = SydneyOpera_ECEF;
  REQUIRE_REL(actual, expected, tolerance);
  PRINT_ERRORS(actual, expected, "LLA to ECEF, Sydney Opera House");

  // Aconcagua mountain peak in Argentina
  actual = position_geodetic_to_ecef<Wgs84>(AconcaguaPeak_LLH);
  expected = AconcaguaPeak_ECEF;
  REQUIRE_REL(actual, expected, tolerance);
  PRINT_ERRORS(actual, expected, "LLA to ECEF, Aconcagua Peak");
}

//! Validate gravitation model
TEST_CASE("J2 model check", "[geodetic]") {
  auto tolerance = 1e-14;

  // White House
  Vector3 actual = gravitation_ecef<Wgs84>(WhiteHouse_ECEF);
  Vector3 expected = WhiteHouse_gamma;
  REQUIRE_REL(actual, expected, tolerance);
  PRINT_ERRORS(actual, expected, "J2 gravitation, White House");

  // Sydney Opera House
  actual = gravitation_ecef<Wgs84>(SydneyOpera_ECEF);
  expected = SydneyOpera_gamma;
  REQUIRE_REL(actual, expected, tolerance);
  PRINT_ERRORS(actual, expected, "J2 gravitation, Sydney Opera");

  // Aconcagua mountain peak in Argentina
  actual = gravitation_ecef<Wgs84>(AconcaguaPeak_ECEF);
  expected = AconcaguaPeak_gamma;
  REQUIRE_REL(actual, expected, tolerance);
  PRINT_ERRORS(actual, expected, "J2 gravitation, Aconcagua Peak");
}
