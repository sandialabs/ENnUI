/**
 * @file test_utils.cpp
 * @brief Utilities for testing.
 */

#pragma once
#include <math.h>

#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>

#include "ennui_types.hpp"

//! Matrix comparison routines with tolerance (absolute and relative)
#define REQUIRE_ABS(arg, expected, tolerance)                        \
  INTERNAL_CHECK_THAT(                                               \
      "REQUIRE_THAT",                                                \
      Catch::Matchers::RangeEquals(                                  \
          expected, AbsoluteToleranceComparator<double>(tolerance)), \
      Catch::ResultDisposition::Normal, arg)
#define REQUIRE_REL(arg, expected, tolerance)                        \
  INTERNAL_CHECK_THAT(                                               \
      "REQUIRE_THAT",                                                \
      Catch::Matchers::RangeEquals(                                  \
          expected, RelativeToleranceComparator<double>(tolerance)), \
      Catch::ResultDisposition::Normal, arg)

// Equivalent to $|x - y| <= tol $
// Avoids subtraction, allowing INFINITY in comparison
inline bool within_tol(double x, double y, double tol) {
  return (x + tol >= y) && (y + tol >= x);
}

//! Absolute tolerance std::equal_to
template <typename T>
struct AbsoluteToleranceComparator {
  T tolerance;

  explicit AbsoluteToleranceComparator(T tolerance) : tolerance(tolerance) {}

  constexpr bool operator()(const T &lhs, const T &rhs) const {
    return within_tol(lhs, rhs, std::isinf(tolerance) ? 0 : tolerance);
  }
};

//! Relative tolerance std::equal_to
template <typename T>
struct RelativeToleranceComparator {
  T tolerance;

  explicit RelativeToleranceComparator(T tolerance) : tolerance(tolerance) {}

  constexpr bool operator()(const T &lhs, const T &rhs) const {
    const double rel_tol = tolerance * (std::max)(std::abs(lhs), std::abs(rhs));

    return within_tol(lhs, rhs, std::isinf(rel_tol) ? 0 : rel_tol);
  }
};

//! Print max abs and relative errors for matrix comparison
template <typename T>
void print_errors(T actual, T expected) {
  if (actual.rows() != expected.rows() || actual.cols() != expected.cols()) {
    std::cout << "Input arguments have different dimensions\n" << std::endl;
    return;
  }

  T err = actual - expected;
  err = err.cwiseAbs();
  T sf = actual.cwiseAbs().cwiseMax(expected.cwiseAbs());

  int i_max_abs = 0;
  int j_max_abs = 0;
  int i_max_rel = 0;
  int j_max_rel = 0;
  double rel_this, rel_max = 0.0;
  for (int i = 0; i < actual.rows(); ++i) {
    for (int j = 0; j < actual.cols(); ++j) {
      if (err(i, j) > err(i_max_abs, j_max_abs)) {
        i_max_abs = i;
        j_max_abs = j;
      }
      rel_this = err(i, j) * (std::isinf(sf(i, j)) ? 0 : 1. / sf(i, j));
      if (rel_this > rel_max) {
        rel_max = rel_this;
        i_max_rel = i;
        j_max_rel = j;
      }
    }
  }
  std::cout << "   Max abs error: " << err(i_max_abs, j_max_abs) << " at ( "
            << i_max_abs << ", " << j_max_abs << ")" << std::endl;
  std::cout << "   Max rel error: " << rel_max << " at ( " << i_max_rel << ", "
            << j_max_rel << ")" << std::endl;
}

#define PRINT_txt(txt) std::cout << txt << std::endl

#define PRINT_ERRORS(actual, expected, txt) \
  std::cout << txt << std::endl;            \
  print_errors(actual, expected)
