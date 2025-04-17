#include "rotation.hpp"
#include "test_utils.hpp"

//! Quantify whether 3x3 matrix is orthonormal
double score_SO3(ennui::Matrix3x3 m) {
  m = (m * (m.transpose()) - ennui::Matrix3x3::Identity());
  return m.lpNorm<Eigen::Infinity>();
}

//! Ensure SO3 is orthonormal
TEST_CASE("SO3", "[rotation]") 
{
  using ennui::Vector3;
  using ennui::math::normalize_SO3;
  using ennui::math::normalize_SO3_Groves;
  using ennui::math::R3_to_SO3;
  auto tolerance = 1e-14;

  ennui::Matrix3x3 m;

  // Euler’s finite rotation formula should result in orthonormal matrix
  // directly
  m = R3_to_SO3(Vector3{1., 1., 1.});
  auto rslt = score_SO3(m);
  REQUIRE(rslt < tolerance);

  // Perturb to obtain non-orthonormal matrix
  m(1, 2) += 1e-3;
  rslt = score_SO3(m);
  std::cout << "Before normalization error: " << rslt << std::endl;

  // Ortho-normalize using SVD
  rslt = score_SO3(normalize_SO3(m));
  std::cout << "After normalization error: " << rslt << std::endl;
  REQUIRE(rslt < tolerance);

  // Ortho-normalize using Groves, which works well for small perturbations
  rslt = score_SO3(normalize_SO3_Groves(m));
  std::cout << "Groves normalization error: " << rslt << std::endl;
  REQUIRE(rslt < 1e-6);
}
