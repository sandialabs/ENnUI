#include <nanobind/eigen/dense.h>

#include "ecef.hpp"
#include "gravitation.hpp"
#include "rotation.hpp"
#include "wgs84.hpp"

void normalize_SO3_return_arg(const Eigen::Ref<const ennui::Matrix3x3> &m,
                              Eigen::Ref<ennui::Matrix3x3> rslt) {
  rslt = ennui::math::normalize_SO3(m);
}

namespace nb = nanobind;
using ennui::geodetic::Wgs84;

NB_MODULE(pyennui, m) {
  auto m_math = m.def_submodule("math");
  m_math.def("normalize_SO3", &ennui::math::normalize_SO3);
  m_math.def("normalize_SO3_Groves", &ennui::math::normalize_SO3_Groves);
  m_math.def("R3_to_so3", &ennui::math::R3_to_so3);
  m_math.def("R3_to_SO3", &ennui::math::R3_to_SO3);

  auto m_geodetic = m.def_submodule("geodetic");
  m_geodetic.def("gravitation_ecef", &ennui::geodetic::gravitation_ecef<Wgs84>);

  auto m_mechanization = m.def_submodule("mechanization");
  auto m_ecef = m_mechanization.def_submodule("ecef");
  m_ecef.def("fwd_pva_S03", &ennui::mechanization::ecef::fwd_pva_S03<Wgs84>);

  m.def("normalize_SO3_return_arg", &normalize_SO3_return_arg);
};
