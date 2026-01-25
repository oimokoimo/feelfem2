/*
 *   Feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_solve77_data.c
 *      Date:   1993/11/09
 *   
 *   Purpose:   LISPプログラムの出力をプログラム生成の為に加工する
 *              
 *              数値積分用COMMONブロック作成の呼び出し
 *              
 *              
 *              
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"
#include "../quadrature/quadrature.h"


#include "solve_fort77_funcs.h"

void make_solve77_data()
{
    /* 数値積分用COMMONブロック作成の呼び出し */
    make_elem_commons();

    return;
}



