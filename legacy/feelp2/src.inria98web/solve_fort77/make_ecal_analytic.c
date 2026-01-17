/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_ecal_analytic.c
 *      Date:   1993/11/20
 *   
 *   Purpose:   ecalXXルーチンのうち、解析的積分法の部分を作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void make_ecal_analytic(fp,solve_no,elem_no,quad_no,solve_element_ptr)
     FILE *fp;
     int solve_no;
     int elem_no;
     int quad_no;
     SolveElement *solve_element_ptr;
{

    SystemAbort("解析的積分法に対応するecalルーチンはまだ作っていません");
}


