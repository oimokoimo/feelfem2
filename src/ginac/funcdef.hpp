#ifndef FEELFEM2_GINAC_FUNCDEF_HPP
#define FEELFEM2_GINAC_FUNCDEF_HPP
#include <ginac/ginac.h>
#include <iostream>
using namespace GiNaC;
using std::cerr;

extern symbol x, y, z;

//
// definition of dx
//
DECLARE_FUNCTION_1P(dx)

symbol dx_dx("dx_dx");

static ex dx_eval(const ex &t)
{
  return t.diff(x);
}

static ex dx_evalf(const ex &t)
{
  return dx(t).hold();
}

static ex dx_deriv(const ex &, unsigned deriv_param)
{
  if (deriv_param == 0) return dx_dx;
  throw std::runtime_error("Illegal deriv_param for dx");
}

REGISTER_FUNCTION(dx,
                  eval_func(dx_eval).
                  evalf_func(dx_evalf).
                  derivative_func(dx_deriv))

//
// definition of dy
//
DECLARE_FUNCTION_1P(dy)

symbol dy_dx("dy_dx");

static ex dy_eval(const ex &t)
{
  return t.diff(y);
}

static ex dy_evalf(const ex &t)
{
  return dy(t).hold();
}

static ex dy_deriv(const ex &, unsigned deriv_param)
{
  if (deriv_param == 0) return dy_dx;
  throw std::runtime_error("Illegal deriv_param for dy");
}

REGISTER_FUNCTION(dy,
                  eval_func(dy_eval).
                  evalf_func(dy_evalf).
                  derivative_func(dy_deriv))

//
// definition of dz
//
DECLARE_FUNCTION_1P(dz)

symbol dz_dx("dz_dx");

static ex dz_eval(const ex &t)
{
  return t.diff(z);
}

static ex dz_evalf(const ex &t)
{
  return dz(t).hold();
}

static ex dz_deriv(const ex &, unsigned deriv_param)
{
  if (deriv_param == 0) return dz_dx;
  throw std::runtime_error("Illegal deriv_param for dz");
}

REGISTER_FUNCTION(dz,
                  eval_func(dz_eval).
                  evalf_func(dz_evalf).
                  derivative_func(dz_deriv))

//
// shape functions
//
#define DEFINE_FF_SHAPE_FUNC3(NAME)                                      \
DECLARE_FUNCTION_3P(NAME)                                                \
                                                                          \
symbol NAME##_dx(#NAME "_dx");                                           \
symbol NAME##_dy(#NAME "_dy");                                           \
symbol NAME##_dz(#NAME "_dz");                                           \
                                                                          \
static ex NAME##_eval(const ex &x, const ex &y, const ex &z)             \
{                                                                        \
  return NAME(x,y,z).hold();                                             \
}                                                                        \
                                                                          \
static ex NAME##_evalf(const ex &x, const ex &y, const ex &z)            \
{                                                                        \
  return NAME(x,y,z).hold();                                             \
}                                                                        \
                                                                          \
static ex NAME##_deriv(const ex &, const ex &, const ex &,               \
                       unsigned deriv_param)                              \
{                                                                        \
  if (deriv_param == 0) return NAME##_dx;                                \
  if (deriv_param == 1) return NAME##_dy;                                \
  if (deriv_param == 2) return NAME##_dz;                                \
  throw std::runtime_error("Illegal deriv_param for " #NAME);            \
}                                                                        \
                                                                          \
REGISTER_FUNCTION(NAME,                                                   \
                  eval_func(NAME##_eval).                                 \
                  evalf_func(NAME##_evalf).                               \
                  derivative_func(NAME##_deriv))

DEFINE_FF_SHAPE_FUNC3(ff_n1);
DEFINE_FF_SHAPE_FUNC3(ff_n2);
DEFINE_FF_SHAPE_FUNC3(ff_n3);
DEFINE_FF_SHAPE_FUNC3(ff_n4);
DEFINE_FF_SHAPE_FUNC3(ff_n5);
DEFINE_FF_SHAPE_FUNC3(ff_n6);
DEFINE_FF_SHAPE_FUNC3(ff_n7);
DEFINE_FF_SHAPE_FUNC3(ff_n8);
DEFINE_FF_SHAPE_FUNC3(ff_n9);
DEFINE_FF_SHAPE_FUNC3(ff_n10);
DEFINE_FF_SHAPE_FUNC3(ff_n11);
DEFINE_FF_SHAPE_FUNC3(ff_n12);
DEFINE_FF_SHAPE_FUNC3(ff_n13);
DEFINE_FF_SHAPE_FUNC3(ff_n14);
DEFINE_FF_SHAPE_FUNC3(ff_n15);
DEFINE_FF_SHAPE_FUNC3(ff_n16);
DEFINE_FF_SHAPE_FUNC3(ff_n17);
DEFINE_FF_SHAPE_FUNC3(ff_n18);
DEFINE_FF_SHAPE_FUNC3(ff_n19);
DEFINE_FF_SHAPE_FUNC3(ff_n20);
DEFINE_FF_SHAPE_FUNC3(ff_n21);
DEFINE_FF_SHAPE_FUNC3(ff_n22);
DEFINE_FF_SHAPE_FUNC3(ff_n23);
DEFINE_FF_SHAPE_FUNC3(ff_n24);
DEFINE_FF_SHAPE_FUNC3(ff_n25);

/* 必要な数だけ続ける */

#undef DEFINE_FF_SHAPE_FUNC3

#endif
