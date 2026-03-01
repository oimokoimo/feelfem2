#pragma once

#include <ginac/ginac.h>
#include <stdexcept>

namespace feelfem_ginac_userfunc {

using namespace GiNaC;

// =============================================================
// 1 parameters: _fn11 .. _fn15
// =============================================================

DECLARE_FUNCTION_1P(_fn11)
inline symbol _fn11_dx("_fn11_dx"), _fn11_dy("_fn11_dy"), _fn11_dz("_fn11_dz");
static ex _fn11_eval(const ex& x) { return _fn11(x).hold(); }
static ex _fn11_evalf(const ex& x) { return _fn11(x); }
static ex _fn11_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn11_dx;
    case 1: return _fn11_dy;
    case 2: return _fn11_dz;
    default: throw std::runtime_error("_fn11: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn11,
    eval_func(_fn11_eval).evalf_func(_fn11_evalf).derivative_func(_fn11_deriv))

DECLARE_FUNCTION_1P(_fn12)
inline symbol _fn12_dx("_fn12_dx"), _fn12_dy("_fn12_dy"), _fn12_dz("_fn12_dz");
static ex _fn12_eval(const ex& x) { return _fn12(x).hold(); }
static ex _fn12_evalf(const ex& x) { return _fn12(x); }
static ex _fn12_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn12_dx;
    case 1: return _fn12_dy;
    case 2: return _fn12_dz;
    default: throw std::runtime_error("_fn12: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn12,
    eval_func(_fn12_eval).evalf_func(_fn12_evalf).derivative_func(_fn12_deriv))

DECLARE_FUNCTION_1P(_fn13)
inline symbol _fn13_dx("_fn13_dx"), _fn13_dy("_fn13_dy"), _fn13_dz("_fn13_dz");
static ex _fn13_eval(const ex& x) { return _fn13(x).hold(); }
static ex _fn13_evalf(const ex& x) { return _fn13(x); }
static ex _fn13_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn13_dx;
    case 1: return _fn13_dy;
    case 2: return _fn13_dz;
    default: throw std::runtime_error("_fn13: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn13,
    eval_func(_fn13_eval).evalf_func(_fn13_evalf).derivative_func(_fn13_deriv))

DECLARE_FUNCTION_1P(_fn14)
inline symbol _fn14_dx("_fn14_dx"), _fn14_dy("_fn14_dy"), _fn14_dz("_fn14_dz");
static ex _fn14_eval(const ex& x) { return _fn14(x).hold(); }
static ex _fn14_evalf(const ex& x) { return _fn14(x); }
static ex _fn14_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn14_dx;
    case 1: return _fn14_dy;
    case 2: return _fn14_dz;
    default: throw std::runtime_error("_fn14: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn14,
    eval_func(_fn14_eval).evalf_func(_fn14_evalf).derivative_func(_fn14_deriv))

DECLARE_FUNCTION_1P(_fn15)
inline symbol _fn15_dx("_fn15_dx"), _fn15_dy("_fn15_dy"), _fn15_dz("_fn15_dz");
static ex _fn15_eval(const ex& x) { return _fn15(x).hold(); }
static ex _fn15_evalf(const ex& x) { return _fn15(x); }
static ex _fn15_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn15_dx;
    case 1: return _fn15_dy;
    case 2: return _fn15_dz;
    default: throw std::runtime_error("_fn15: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn15,
    eval_func(_fn15_eval).evalf_func(_fn15_evalf).derivative_func(_fn15_deriv))

// =============================================================
// 2 parameters: _fn21 .. _fn25
// =============================================================

DECLARE_FUNCTION_2P(_fn21)
inline symbol _fn21_dx("_fn21_dx"), _fn21_dy("_fn21_dy"), _fn21_dz("_fn21_dz");
static ex _fn21_eval(const ex& x, const ex& y) { return _fn21(x,y).hold(); }
static ex _fn21_evalf(const ex& x, const ex& y) { return _fn21(x,y); }
static ex _fn21_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn21_dx;
    case 1: return _fn21_dy;
    case 2: return _fn21_dz;
    default: throw std::runtime_error("_fn21: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn21,
    eval_func(_fn21_eval).evalf_func(_fn21_evalf).derivative_func(_fn21_deriv))

DECLARE_FUNCTION_2P(_fn22)
inline symbol _fn22_dx("_fn22_dx"), _fn22_dy("_fn22_dy"), _fn22_dz("_fn22_dz");
static ex _fn22_eval(const ex& x, const ex& y) { return _fn22(x,y).hold(); }
static ex _fn22_evalf(const ex& x, const ex& y) { return _fn22(x,y); }
static ex _fn22_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn22_dx;
    case 1: return _fn22_dy;
    case 2: return _fn22_dz;
    default: throw std::runtime_error("_fn22: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn22,
    eval_func(_fn22_eval).evalf_func(_fn22_evalf).derivative_func(_fn22_deriv))

DECLARE_FUNCTION_2P(_fn23)
inline symbol _fn23_dx("_fn23_dx"), _fn23_dy("_fn23_dy"), _fn23_dz("_fn23_dz");
static ex _fn23_eval(const ex& x, const ex& y) { return _fn23(x,y).hold(); }
static ex _fn23_evalf(const ex& x, const ex& y) { return _fn23(x,y); }
static ex _fn23_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn23_dx;
    case 1: return _fn23_dy;
    case 2: return _fn23_dz;
    default: throw std::runtime_error("_fn23: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn23,
    eval_func(_fn23_eval).evalf_func(_fn23_evalf).derivative_func(_fn23_deriv))

DECLARE_FUNCTION_2P(_fn24)
inline symbol _fn24_dx("_fn24_dx"), _fn24_dy("_fn24_dy"), _fn24_dz("_fn24_dz");
static ex _fn24_eval(const ex& x, const ex& y) { return _fn24(x,y).hold(); }
static ex _fn24_evalf(const ex& x, const ex& y) { return _fn24(x,y); }
static ex _fn24_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn24_dx;
    case 1: return _fn24_dy;
    case 2: return _fn24_dz;
    default: throw std::runtime_error("_fn24: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn24,
    eval_func(_fn24_eval).evalf_func(_fn24_evalf).derivative_func(_fn24_deriv))

DECLARE_FUNCTION_2P(_fn25)
inline symbol _fn25_dx("_fn25_dx"), _fn25_dy("_fn25_dy"), _fn25_dz("_fn25_dz");
static ex _fn25_eval(const ex& x, const ex& y) { return _fn25(x,y).hold(); }
static ex _fn25_evalf(const ex& x, const ex& y) { return _fn25(x,y); }
static ex _fn25_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn25_dx;
    case 1: return _fn25_dy;
    case 2: return _fn25_dz;
    default: throw std::runtime_error("_fn25: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn25,
    eval_func(_fn25_eval).evalf_func(_fn25_evalf).derivative_func(_fn25_deriv))

// =============================================================
// 3 parameters: _fn31 .. _fn35
// =============================================================

DECLARE_FUNCTION_3P(_fn31)
inline symbol _fn31_dx("_fn31_dx"), _fn31_dy("_fn31_dy"), _fn31_dz("_fn31_dz");
static ex _fn31_eval(const ex& x, const ex& y, const ex& z) { return _fn31(x,y,z).hold(); }
static ex _fn31_evalf(const ex& x, const ex& y, const ex& z) { return _fn31(x,y,z); }
static ex _fn31_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn31_dx;
    case 1: return _fn31_dy;
    case 2: return _fn31_dz;
    default: throw std::runtime_error("_fn31: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn31,
    eval_func(_fn31_eval).evalf_func(_fn31_evalf).derivative_func(_fn31_deriv))

DECLARE_FUNCTION_3P(_fn32)
inline symbol _fn32_dx("_fn32_dx"), _fn32_dy("_fn32_dy"), _fn32_dz("_fn32_dz");
static ex _fn32_eval(const ex& x, const ex& y, const ex& z) { return _fn32(x,y,z).hold(); }
static ex _fn32_evalf(const ex& x, const ex& y, const ex& z) { return _fn32(x,y,z); }
static ex _fn32_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn32_dx;
    case 1: return _fn32_dy;
    case 2: return _fn32_dz;
    default: throw std::runtime_error("_fn32: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn32,
    eval_func(_fn32_eval).evalf_func(_fn32_evalf).derivative_func(_fn32_deriv))

DECLARE_FUNCTION_3P(_fn33)
inline symbol _fn33_dx("_fn33_dx"), _fn33_dy("_fn33_dy"), _fn33_dz("_fn33_dz");
static ex _fn33_eval(const ex& x, const ex& y, const ex& z) { return _fn33(x,y,z).hold(); }
static ex _fn33_evalf(const ex& x, const ex& y, const ex& z) { return _fn33(x,y,z); }
static ex _fn33_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn33_dx;
    case 1: return _fn33_dy;
    case 2: return _fn33_dz;
    default: throw std::runtime_error("_fn33: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn33,
    eval_func(_fn33_eval).evalf_func(_fn33_evalf).derivative_func(_fn33_deriv))

DECLARE_FUNCTION_3P(_fn34)
inline symbol _fn34_dx("_fn34_dx"), _fn34_dy("_fn34_dy"), _fn34_dz("_fn34_dz");
static ex _fn34_eval(const ex& x, const ex& y, const ex& z) { return _fn34(x,y,z).hold(); }
static ex _fn34_evalf(const ex& x, const ex& y, const ex& z) { return _fn34(x,y,z); }
static ex _fn34_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn34_dx;
    case 1: return _fn34_dy;
    case 2: return _fn34_dz;
    default: throw std::runtime_error("_fn34: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn34,
    eval_func(_fn34_eval).evalf_func(_fn34_evalf).derivative_func(_fn34_deriv))

DECLARE_FUNCTION_3P(_fn35)
inline symbol _fn35_dx("_fn35_dx"), _fn35_dy("_fn35_dy"), _fn35_dz("_fn35_dz");
static ex _fn35_eval(const ex& x, const ex& y, const ex& z) { return _fn35(x,y,z).hold(); }
static ex _fn35_evalf(const ex& x, const ex& y, const ex& z) { return _fn35(x,y,z); }
static ex _fn35_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return _fn35_dx;
    case 1: return _fn35_dy;
    case 2: return _fn35_dz;
    default: throw std::runtime_error("_fn35: illegal deriv_param");
    }
}
REGISTER_FUNCTION(_fn35,
    eval_func(_fn35_eval).evalf_func(_fn35_evalf).derivative_func(_fn35_deriv))

} // namespace feelfem_ginac_userfunc
