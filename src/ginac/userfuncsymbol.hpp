#pragma once

#include <ginac/ginac.h>
#include <stdexcept>

namespace feelfem_ginac_userfunc {

using namespace GiNaC;

// =============================================================
// 1 parameters: ff_fn11 .. ff_fn15
// =============================================================

DECLARE_FUNCTION_1P(ff_fn11)
inline symbol ff_fn11_dx("ff_fn11_dx"), ff_fn11_dy("ff_fn11_dy"), ff_fn11_dz("ff_fn11_dz");
static ex ff_fn11_eval(const ex& x) { return ff_fn11(x).hold(); }
static ex ff_fn11_evalf(const ex& x) { return ff_fn11(x); }
static ex ff_fn11_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn11_dx;
    case 1: return ff_fn11_dy;
    case 2: return ff_fn11_dz;
    default: throw std::runtime_error("ff_fn11: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn11,
    eval_func(ff_fn11_eval).evalf_func(ff_fn11_evalf).derivative_func(ff_fn11_deriv))

DECLARE_FUNCTION_1P(ff_fn12)
inline symbol ff_fn12_dx("ff_fn12_dx"), ff_fn12_dy("ff_fn12_dy"), ff_fn12_dz("ff_fn12_dz");
static ex ff_fn12_eval(const ex& x) { return ff_fn12(x).hold(); }
static ex ff_fn12_evalf(const ex& x) { return ff_fn12(x); }
static ex ff_fn12_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn12_dx;
    case 1: return ff_fn12_dy;
    case 2: return ff_fn12_dz;
    default: throw std::runtime_error("ff_fn12: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn12,
    eval_func(ff_fn12_eval).evalf_func(ff_fn12_evalf).derivative_func(ff_fn12_deriv))

DECLARE_FUNCTION_1P(ff_fn13)
inline symbol ff_fn13_dx("ff_fn13_dx"), ff_fn13_dy("ff_fn13_dy"), ff_fn13_dz("ff_fn13_dz");
static ex ff_fn13_eval(const ex& x) { return ff_fn13(x).hold(); }
static ex ff_fn13_evalf(const ex& x) { return ff_fn13(x); }
static ex ff_fn13_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn13_dx;
    case 1: return ff_fn13_dy;
    case 2: return ff_fn13_dz;
    default: throw std::runtime_error("ff_fn13: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn13,
    eval_func(ff_fn13_eval).evalf_func(ff_fn13_evalf).derivative_func(ff_fn13_deriv))

DECLARE_FUNCTION_1P(ff_fn14)
inline symbol ff_fn14_dx("ff_fn14_dx"), ff_fn14_dy("ff_fn14_dy"), ff_fn14_dz("ff_fn14_dz");
static ex ff_fn14_eval(const ex& x) { return ff_fn14(x).hold(); }
static ex ff_fn14_evalf(const ex& x) { return ff_fn14(x); }
static ex ff_fn14_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn14_dx;
    case 1: return ff_fn14_dy;
    case 2: return ff_fn14_dz;
    default: throw std::runtime_error("ff_fn14: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn14,
    eval_func(ff_fn14_eval).evalf_func(ff_fn14_evalf).derivative_func(ff_fn14_deriv))

DECLARE_FUNCTION_1P(ff_fn15)
inline symbol ff_fn15_dx("ff_fn15_dx"), ff_fn15_dy("ff_fn15_dy"), ff_fn15_dz("ff_fn15_dz");
static ex ff_fn15_eval(const ex& x) { return ff_fn15(x).hold(); }
static ex ff_fn15_evalf(const ex& x) { return ff_fn15(x); }
static ex ff_fn15_deriv(const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn15_dx;
    case 1: return ff_fn15_dy;
    case 2: return ff_fn15_dz;
    default: throw std::runtime_error("ff_fn15: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn15,
    eval_func(ff_fn15_eval).evalf_func(ff_fn15_evalf).derivative_func(ff_fn15_deriv))

// =============================================================
// 2 parameters: ff_fn21 .. ff_fn25
// =============================================================

DECLARE_FUNCTION_2P(ff_fn21)
inline symbol ff_fn21_dx("ff_fn21_dx"), ff_fn21_dy("ff_fn21_dy"), ff_fn21_dz("ff_fn21_dz");
static ex ff_fn21_eval(const ex& x, const ex& y) { return ff_fn21(x,y).hold(); }
static ex ff_fn21_evalf(const ex& x, const ex& y) { return ff_fn21(x,y); }
static ex ff_fn21_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn21_dx;
    case 1: return ff_fn21_dy;
    case 2: return ff_fn21_dz;
    default: throw std::runtime_error("ff_fn21: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn21,
    eval_func(ff_fn21_eval).evalf_func(ff_fn21_evalf).derivative_func(ff_fn21_deriv))

DECLARE_FUNCTION_2P(ff_fn22)
inline symbol ff_fn22_dx("ff_fn22_dx"), ff_fn22_dy("ff_fn22_dy"), ff_fn22_dz("ff_fn22_dz");
static ex ff_fn22_eval(const ex& x, const ex& y) { return ff_fn22(x,y).hold(); }
static ex ff_fn22_evalf(const ex& x, const ex& y) { return ff_fn22(x,y); }
static ex ff_fn22_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn22_dx;
    case 1: return ff_fn22_dy;
    case 2: return ff_fn22_dz;
    default: throw std::runtime_error("ff_fn22: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn22,
    eval_func(ff_fn22_eval).evalf_func(ff_fn22_evalf).derivative_func(ff_fn22_deriv))

DECLARE_FUNCTION_2P(ff_fn23)
inline symbol ff_fn23_dx("ff_fn23_dx"), ff_fn23_dy("ff_fn23_dy"), ff_fn23_dz("ff_fn23_dz");
static ex ff_fn23_eval(const ex& x, const ex& y) { return ff_fn23(x,y).hold(); }
static ex ff_fn23_evalf(const ex& x, const ex& y) { return ff_fn23(x,y); }
static ex ff_fn23_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn23_dx;
    case 1: return ff_fn23_dy;
    case 2: return ff_fn23_dz;
    default: throw std::runtime_error("ff_fn23: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn23,
    eval_func(ff_fn23_eval).evalf_func(ff_fn23_evalf).derivative_func(ff_fn23_deriv))

DECLARE_FUNCTION_2P(ff_fn24)
inline symbol ff_fn24_dx("ff_fn24_dx"), ff_fn24_dy("ff_fn24_dy"), ff_fn24_dz("ff_fn24_dz");
static ex ff_fn24_eval(const ex& x, const ex& y) { return ff_fn24(x,y).hold(); }
static ex ff_fn24_evalf(const ex& x, const ex& y) { return ff_fn24(x,y); }
static ex ff_fn24_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn24_dx;
    case 1: return ff_fn24_dy;
    case 2: return ff_fn24_dz;
    default: throw std::runtime_error("ff_fn24: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn24,
    eval_func(ff_fn24_eval).evalf_func(ff_fn24_evalf).derivative_func(ff_fn24_deriv))

DECLARE_FUNCTION_2P(ff_fn25)
inline symbol ff_fn25_dx("ff_fn25_dx"), ff_fn25_dy("ff_fn25_dy"), ff_fn25_dz("ff_fn25_dz");
static ex ff_fn25_eval(const ex& x, const ex& y) { return ff_fn25(x,y).hold(); }
static ex ff_fn25_evalf(const ex& x, const ex& y) { return ff_fn25(x,y); }
static ex ff_fn25_deriv(const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn25_dx;
    case 1: return ff_fn25_dy;
    case 2: return ff_fn25_dz;
    default: throw std::runtime_error("ff_fn25: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn25,
    eval_func(ff_fn25_eval).evalf_func(ff_fn25_evalf).derivative_func(ff_fn25_deriv))

// =============================================================
// 3 parameters: ff_fn31 .. ff_fn35
// =============================================================

DECLARE_FUNCTION_3P(ff_fn31)
inline symbol ff_fn31_dx("ff_fn31_dx"), ff_fn31_dy("ff_fn31_dy"), ff_fn31_dz("ff_fn31_dz");
static ex ff_fn31_eval(const ex& x, const ex& y, const ex& z) { return ff_fn31(x,y,z).hold(); }
static ex ff_fn31_evalf(const ex& x, const ex& y, const ex& z) { return ff_fn31(x,y,z); }
static ex ff_fn31_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn31_dx;
    case 1: return ff_fn31_dy;
    case 2: return ff_fn31_dz;
    default: throw std::runtime_error("ff_fn31: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn31,
    eval_func(ff_fn31_eval).evalf_func(ff_fn31_evalf).derivative_func(ff_fn31_deriv))

DECLARE_FUNCTION_3P(ff_fn32)
inline symbol ff_fn32_dx("ff_fn32_dx"), ff_fn32_dy("ff_fn32_dy"), ff_fn32_dz("ff_fn32_dz");
static ex ff_fn32_eval(const ex& x, const ex& y, const ex& z) { return ff_fn32(x,y,z).hold(); }
static ex ff_fn32_evalf(const ex& x, const ex& y, const ex& z) { return ff_fn32(x,y,z); }
static ex ff_fn32_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn32_dx;
    case 1: return ff_fn32_dy;
    case 2: return ff_fn32_dz;
    default: throw std::runtime_error("ff_fn32: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn32,
    eval_func(ff_fn32_eval).evalf_func(ff_fn32_evalf).derivative_func(ff_fn32_deriv))

DECLARE_FUNCTION_3P(ff_fn33)
inline symbol ff_fn33_dx("ff_fn33_dx"), ff_fn33_dy("ff_fn33_dy"), ff_fn33_dz("ff_fn33_dz");
static ex ff_fn33_eval(const ex& x, const ex& y, const ex& z) { return ff_fn33(x,y,z).hold(); }
static ex ff_fn33_evalf(const ex& x, const ex& y, const ex& z) { return ff_fn33(x,y,z); }
static ex ff_fn33_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn33_dx;
    case 1: return ff_fn33_dy;
    case 2: return ff_fn33_dz;
    default: throw std::runtime_error("ff_fn33: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn33,
    eval_func(ff_fn33_eval).evalf_func(ff_fn33_evalf).derivative_func(ff_fn33_deriv))

DECLARE_FUNCTION_3P(ff_fn34)
inline symbol ff_fn34_dx("ff_fn34_dx"), ff_fn34_dy("ff_fn34_dy"), ff_fn34_dz("ff_fn34_dz");
static ex ff_fn34_eval(const ex& x, const ex& y, const ex& z) { return ff_fn34(x,y,z).hold(); }
static ex ff_fn34_evalf(const ex& x, const ex& y, const ex& z) { return ff_fn34(x,y,z); }
static ex ff_fn34_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn34_dx;
    case 1: return ff_fn34_dy;
    case 2: return ff_fn34_dz;
    default: throw std::runtime_error("ff_fn34: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn34,
    eval_func(ff_fn34_eval).evalf_func(ff_fn34_evalf).derivative_func(ff_fn34_deriv))

DECLARE_FUNCTION_3P(ff_fn35)
inline symbol ff_fn35_dx("ff_fn35_dx"), ff_fn35_dy("ff_fn35_dy"), ff_fn35_dz("ff_fn35_dz");
static ex ff_fn35_eval(const ex& x, const ex& y, const ex& z) { return ff_fn35(x,y,z).hold(); }
static ex ff_fn35_evalf(const ex& x, const ex& y, const ex& z) { return ff_fn35(x,y,z); }
static ex ff_fn35_deriv(const ex&, const ex&, const ex&, unsigned deriv_param) {
    switch (deriv_param) {
    case 0: return ff_fn35_dx;
    case 1: return ff_fn35_dy;
    case 2: return ff_fn35_dz;
    default: throw std::runtime_error("ff_fn35: illegal deriv_param");
    }
}
REGISTER_FUNCTION(ff_fn35,
    eval_func(ff_fn35_eval).evalf_func(ff_fn35_evalf).derivative_func(ff_fn35_deriv))

} // namespace feelfem_ginac_userfunc
