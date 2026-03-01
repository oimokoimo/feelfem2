#ifndef FEELFEM2_GINAC_FUNCDEF_HPP
#define FEELFEM2_GINAC_FUNCDEF_HPP

#include <ginac/ginac.h>
#include <iostream>
#include <stdexcept>

namespace feelfem2::ginacfunc {

using GiNaC::ex;
using GiNaC::symbol;

// ここはあなたのプロジェクト側で x,y,z がどう定義されているかに合わせる。
// 既にどこかで global symbol x,y,z を持っているなら extern 宣言だけにするのが無難。
extern symbol x;
extern symbol y;
extern symbol z;

// ---- 共通: 不正 deriv_param を確実に return で終わらせる ----
[[noreturn]] inline ex illegal_deriv_param(const char* fname, unsigned p) {
  std::cerr << fname << ": Illegal deriv_param=" << p << "\n";
  throw std::runtime_error(std::string(fname) + ": Illegal deriv_param");
}

// =======================
// dx, dy, dz （1引数）
// =======================

DECLARE_FUNCTION_1P(dx)
static symbol dx_dx("dx_dx");

static inline ex dx_eval(const ex& t) { return t.diff(x); }
static inline ex dx_evalf(const ex& t) { return dx_eval(t); } // eval と同じでOK

static inline ex dx_deriv(const ex&, unsigned deriv_param) {
  if (deriv_param == 0) return dx_dx;
  return illegal_deriv_param("dx", deriv_param);
}

REGISTER_FUNCTION(dx,
  eval_func(dx_eval).evalf_func(dx_evalf).derivative_func(dx_deriv)
)

DECLARE_FUNCTION_1P(dy)
static symbol dy_dx("dy_dx");

static inline ex dy_eval(const ex& t) { return t.diff(y); }
static inline ex dy_evalf(const ex& t) { return dy_eval(t); }

static inline ex dy_deriv(const ex&, unsigned deriv_param) {
  if (deriv_param == 0) return dy_dx;
  return illegal_deriv_param("dy", deriv_param);
}

REGISTER_FUNCTION(dy,
  eval_func(dy_eval).evalf_func(dy_evalf).derivative_func(dy_deriv)
)

DECLARE_FUNCTION_1P(dz)
static symbol dz_dx("dz_dx");

static inline ex dz_eval(const ex& t) { return t.diff(z); }
static inline ex dz_evalf(const ex& t) { return dz_eval(t); }

static inline ex dz_deriv(const ex&, unsigned deriv_param) {
  if (deriv_param == 0) return dz_dx;
  return illegal_deriv_param("dz", deriv_param);
}

REGISTER_FUNCTION(dz,
  eval_func(dz_eval).evalf_func(dz_evalf).derivative_func(dz_deriv)
)

// =======================
// _n* 系（3引数）を量産するマクロ
// =======================

#define FEELFEM2_DEFINE_3P_HOLD_FUNC(NAME)                                   \
  DECLARE_FUNCTION_3P(NAME)                                                  \
  static symbol NAME##_dx(#NAME "_dx");                                       \
  static symbol NAME##_dy(#NAME "_dy");                                       \
  static symbol NAME##_dz(#NAME "_dz");                                       \
                                                                              \
  static inline ex NAME##_eval(const ex& a, const ex& b, const ex& c) {       \
    return NAME(a, b, c).hold();                                              \
  }                                                                           \
  static inline ex NAME##_evalf(const ex& a, const ex& b, const ex& c) {      \
    return NAME(a, b, c);                                                     \
  }                                                                           \
  static inline ex NAME##_deriv(const ex&, const ex&, const ex&, unsigned p) {\
    if (p == 0) return NAME##_dx;                                             \
    if (p == 1) return NAME##_dy;                                             \
    if (p == 2) return NAME##_dz;                                             \
    return illegal_deriv_param(#NAME, p);                                     \
  }                                                                           \
  REGISTER_FUNCTION(NAME,                                                    \
    eval_func(NAME##_eval).evalf_func(NAME##_evalf).derivative_func(NAME##_deriv)\
  )

// ---- ここから実体：列挙するだけ ----
// 100個も直書きしたくないので、次の「X-macro方式」を推奨（後述）
// とりあえず例：
FEELFEM2_DEFINE_3P_HOLD_FUNC(_n1);
FEELFEM2_DEFINE_3P_HOLD_FUNC(_n2);
FEELFEM2_DEFINE_3P_HOLD_FUNC(_n3);
// ...
// FEELFEM2_DEFINE_3P_HOLD_FUNC(_n100);

#undef FEELFEM2_DEFINE_3P_HOLD_FUNC

} // namespace feelfem2::ginacfunc

#endif // FEELFEM2_GINAC_FUNCDEF_HPP
