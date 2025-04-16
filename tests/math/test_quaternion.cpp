#include <Eigen/Geometry>

#include "test_utils.hpp"

//! Ensure quaternion is stored as scalar-first: [w,x,y,z]
TEST_CASE("order", "[quaternion]") {
  Eigen::Quaterniond q = {1.0, 0.0, 0.0, 0.0};
  Eigen::Quaterniond rslt = q * q;

  Eigen::Vector3d expected = {0., 0., 0.};
  Eigen::Vector3d actual = rslt.vec();
  REQUIRE(actual == expected);

  // Square of scalar component is +1
  REQUIRE(rslt.w() == 1.0);

  // --------------------------------------

  q = {0.0, 1.0, 0.0, 0.0};
  rslt = q * q;
  actual = rslt.vec();
  REQUIRE(actual == expected);

  // Square of a vector  component is -1
  REQUIRE(rslt.w() == -1.0);

  q = {0.0, 0.0, 1.0, 0.0};
  rslt = q * q;
  actual = rslt.vec();
  REQUIRE(actual == expected);

  // Square of a vector  component is -1
  REQUIRE(rslt.w() == -1.0);

  q = {0.0, 0.0, 0.0, 1.0};
  rslt = q * q;
  actual = rslt.vec();
  REQUIRE(actual == expected);

  // Square of a vector  component is -1
  REQUIRE(rslt.w() == -1.0);
}

//! Ensure quaternion algebra ij=k
TEST_CASE("algebra", "[quaternion]") {
  Eigen::Quaterniond i = {0.0, 1.0, 0.0, 0.0};
  Eigen::Quaterniond j = {0.0, 0.0, 1.0, 0.0};
  Eigen::Quaterniond k = {0.0, 0.0, 0.0, 1.0};
  REQUIRE(i * j == k);
  REQUIRE(j * i == k.conjugate());
}
