
/**
 * @file landmark.hpp
 * @brief Common landmarks useful for testing.
 */

#pragma once
#include "ennui_types.hpp"
/* The following values have been contrasted against an independent reference
  codebase. Results are sensitive to selection of geodetic model parameters -
  even the retained precision.
*/
static const ennui::Vector3 WhiteHouse_LLH = {
    3.8897778000000002E+01, -7.7036389000000000E+01, 4.5719999999999999E+01};
static const ennui::Vector3 WhiteHouse_ECEF = {
    1.1150423452941689E+06, -4.8438122981491517E+06, 3.9835202164462707E+06};
static const ennui::Vector3 WhiteHouse_gamma = {
    -1.7170260919766687E+00, 7.4588665943134185E+00, -6.1541304311837033E+00};
static const ennui::Vector3 SydneyOpera_LLH = {
    -3.3856810000000003E+01, 1.5121513999999999E+02, 4.0000000000000000E+00};
static const ennui::Vector3 SydneyOpera_ECEF = {
    -4.6469638774879947E+06, 2.5530911988806850E+06, -3.5332702770814989E+06};
static const ennui::Vector3 SydneyOpera_gamma = {
    7.1547316446011369E+00, -3.9308853853322177E+00, 5.4577459118432454E+00};
static const ennui::Vector3 AconcaguaPeak_LLH = {
    -3.2653055999999999E+01, -7.0011667000000003E+01, 6.9608000000000002E+03};
static const ennui::Vector3 AconcaguaPeak_ECEF = {
    1.8394468460281149E+06, -5.0570424596377872E+06, -3.4253819319244744E+06};
static const ennui::Vector3 AconcaguaPeak_gamma = {
    -2.8227611074196277E+00, 7.7603888388830651E+00, 5.2735711300239210E+00};

typedef struct {
  ennui::Vector3 position;
  ennui::Vector3 velocity;
  ennui::Matrix3x3 attitude;
} state_pva_SO3;

typedef struct {
  state_pva_SO3 prior;
  ennui::Vector3 specific_force;
  ennui::Vector3 angular_rate;
  double dt;
  state_pva_SO3 posterior;
} prop_mean;

extern const prop_mean WhiteHouse_mean_prop;
extern const prop_mean SydneyOpera_mean_prop;
extern const prop_mean AconcaguaPeak_mean_prop;
