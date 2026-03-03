#ifndef FEELFEM2_GINAC_FUNCDEF_HPP
#define FEELFEM2_GINAC_FUNCDEF_HPP

#include <ginac/ginac.h>
#include <iostream>
#include <stdexcept>

namespace feelfem2::ginacfunc {

using GiNaC::ex;
using GiNaC::symbol;

// どこかで定義済みの x,y,z を使う（あなたのプロジェクトの実体に合わせる）
extern symbol x;
extern symbol y;
extern symbol z;

// =======================
// dx, dy, dz （1引数）
//  - “微分演算子”として eval だけ定義
//  - derivative_func は付けない（GiNaC が勝手に dz(...) を微分しようとしても落とさない）
// =======================

DECLARE_FUNCTION_1P(dx)
static inline ex dx_eval(const ex& t) { return t.diff(x); }
static inline ex dx_evalf(const ex& t) { return dx_eval(t); }
REGISTER_FUNCTION(dx, eval_func(dx_eval).evalf_func(dx_evalf))

DECLARE_FUNCTION_1P(dy)
static inline ex dy_eval(const ex& t) { return t.diff(y); }
static inline ex dy_evalf(const ex& t) { return dy_eval(t); }
REGISTER_FUNCTION(dy, eval_func(dy_eval).evalf_func(dy_evalf))

DECLARE_FUNCTION_1P(dz)
static inline ex dz_eval(const ex& t) { return t.diff(z); }
static inline ex dz_evalf(const ex& t) { return dz_eval(t); }
REGISTER_FUNCTION(dz, eval_func(dz_eval).evalf_func(dz_evalf))

// =======================
// _n* 系（3引数）
// =======================

[[noreturn]] inline ex illegal_deriv_param(const char* fname, unsigned p) {
  std::cerr << fname << ": Illegal deriv_param=" << p << "\n";
  throw std::runtime_error(std::string(fname) + ": Illegal deriv_param");
}

#define FEELFEM2_DEFINE_3P_HOLD_FUNC(NAME)                                     \
  DECLARE_FUNCTION_3P(NAME)                                                    \
  static symbol NAME##_dx(#NAME "_dx");                                         \
  static symbol NAME##_dy(#NAME "_dy");                                         \
  static symbol NAME##_dz(#NAME "_dz");                                         \
  static inline ex NAME##_eval(const ex& a, const ex& b, const ex& c) {         \
    return NAME(a, b, c).hold();                                                \
  }                                                                             \
  static inline ex NAME##_evalf(const ex& a, const ex& b, const ex& c) {        \
    return NAME(a, b, c);                                                       \
  }                                                                             \
  static inline ex NAME##_deriv(const ex&, const ex&, const ex&, unsigned p) { \
    if (p == 0) return NAME##_dx;                                               \
    if (p == 1) return NAME##_dy;                                               \
    if (p == 2) return NAME##_dz;                                               \
    return illegal_deriv_param(#NAME, p);                                       \
  }                                                                             \
  REGISTER_FUNCTION(NAME,                                                      \
    eval_func(NAME##_eval).evalf_func(NAME##_evalf).derivative_func(NAME##_deriv))

FEELFEM2_DEFINE_3P_HOLD_FUNC(ff_n1);
FEELFEM2_DEFINE_3P_HOLD_FUNC(ff_n2);
FEELFEM2_DEFINE_3P_HOLD_FUNC(ff_n3);
FEELFEM2_DEFINE_3P_HOLD_FUNC(ff_n4);
// 必要分だけ追加

#undef FEELFEM2_DEFINE_3P_HOLD_FUNC

} // namespace feelfem2::ginacfunc

#endif
