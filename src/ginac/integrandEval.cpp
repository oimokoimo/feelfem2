/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : integrandEval.cpp
 *  Date     : 2002/02/18
 *  Modified : 2002/09/16    Add userfuncsymbol.hpp
 *
 *  Purpose  : treat element stiffness mathematical component
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 */

#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ginac/ginac.h>
using namespace GiNaC;

#include "feeldef.hpp"

// ------------------------------------------------------------
// Symbols
// ------------------------------------------------------------
symbol x("x"), y("y"), z("z");

// 253個を手で並べるのは保守不能なので、動的に作る。
// 既存コードは _m1.._m253 を直接参照していたが、今回からは配列 m[i] (1-origin) で参照する。
static const std::vector<symbol>& m_syms()
{
    static const std::vector<symbol> m = []() {
        std::vector<symbol> v;
        v.reserve(253);
        for (int i = 1; i <= 253; ++i) {
            v.emplace_back("_m" + std::to_string(i));
        }
        return v;
    }();
    return m;
}

// lst(x,y,z,_m1.._m253) 相当を一度だけ構築して使い回す
static const lst& all_syms_lst()
{
    static const lst syms = []() {
        lst l;
        l.append(x);
        l.append(y);
        l.append(z);
        for (const auto& s : m_syms()) {
            l.append(s);
        }
        return l;
    }();
    return syms;
}

// expr を Fortran向け文字列に落とす（旧 ostrstream 代替）
static void ex_to_cbuf(const ex& e, char* buf, int bufsiz)
{
    if (!buf || bufsiz <= 0) return;

    std::ostringstream oss;
    oss << e;
    const std::string s = oss.str();

    // NUL含めて収まること
    assert(static_cast<int>(s.size()) + 1 < bufsiz);

    std::memcpy(buf, s.c_str(), s.size() + 1); // NULまでコピー
}

#include "funcdef.hpp"
#include "userfuncsymbol.hpp"

// ------------------------------------------------------------
// Debug: parse and print
// ------------------------------------------------------------
void integrandEval(char *formula)
{
    ex e(formula, all_syms_lst());

    std::cerr << "Integrand eval = " << e << std::endl;

    // 旧コードは e.diff(_m1) だったが、今は m_syms()[0] が _m1
    std::cerr << "e.diff(_m1) = " << e.diff(m_syms().at(0)) << std::endl;
}

// ------------------------------------------------------------
// Derivative w.r.t. _mN (N=1..253)
// ------------------------------------------------------------
void integrandDerivative(char *formula, int n, char *buf, int bufsiz)
{
    ex e(formula, all_syms_lst());

    // n は 1..253 のはず
    assert(1 <= n && n <= 253);
    e = e.diff(m_syms().at(static_cast<size_t>(n - 1)));

    ex_to_cbuf(e, buf, bufsiz);

    // _n1(x,y,z) -> _n1 etc.
    void funcSymbolConvert_ginac(char *);
    funcSymbolConvert_ginac(buf);
}

// ------------------------------------------------------------
// RHS: substitute selected coefficient symbols to 0 then negate
// coeffSblNoVec[i] in 1..253
// ------------------------------------------------------------
void GetRightHandSide(char *formula, int totalDOF, int *coeffSblNoVec,
                      char *buf, int bufsiz)
{
    ex e(formula, all_syms_lst());

    for (int i = 0; i < totalDOF; i++) {
        const int k = coeffSblNoVec[i];
        if (k < 1 || k > 253) {
            std::cerr << "switch = " << k << std::endl;
            assert(false);
        }
        e = e.subs(m_syms().at(static_cast<size_t>(k - 1)) == 0);
    }

    e = -1.0 * e; // minus ! 020306

    ex_to_cbuf(e, buf, bufsiz);

    void funcSymbolConvert_ginac(char *);
    funcSymbolConvert_ginac(buf);
}

// ------------------------------------------------------------
// esetDerivative: TYPE_DIFF_X/Y/Z -> diff(_m1/_m2/_m3)
// ------------------------------------------------------------
void esetDerivative(const char *formula, int type, char *buf, int bufsiz)
{
    ex e(formula, all_syms_lst());

    switch (type) {
    case TYPE_DIFF_X:
        e = e.diff(m_syms().at(0)); // _m1
        break;
    case TYPE_DIFF_Y:
        e = e.diff(m_syms().at(1)); // _m2
        break;
    case TYPE_DIFF_Z:
        e = e.diff(m_syms().at(2)); // _m3
        break;
    default:
        assert(false);
    }

    ex_to_cbuf(e, buf, bufsiz);
}

// ------------------------------------------------------------
// ewiseQuadEval: just stringify and convert symbols
// ------------------------------------------------------------
void ewiseQuadEval(char *formula, char *buf, int bufsiz)
{
    ex e(formula, all_syms_lst());

    ex_to_cbuf(e, buf, bufsiz);

    void funcSymbolConvert_ginac(char *);
    funcSymbolConvert_ginac(buf);
}
