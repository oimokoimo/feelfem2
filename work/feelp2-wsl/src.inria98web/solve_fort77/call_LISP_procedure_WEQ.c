/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   call_LISP_procedure_WEQ.c
 *      Date:   1993/11/16
 *   
 *   Purpose:   積分法別にLISPプログラムを呼び出す
 *   Functions: 
 *              非線形版未対応(93/11/16)
 *              
 *              *smbl-eval*  の設定
 *              *quad-vars* (数値積分内挿法付き変数指定)
 *
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../quadrature/quadrature.h"

void call_LISP_procedure_WEQ(solve_no, elem_no, no , quad_method,
			solve_element_ptr , fp)
     int solve_no;
     int elem_no;
     int no;
     char *quad_method;
     SolveElement *solve_element_ptr;
     FILE *fp;
{
    
    Quadrature *quad_ptr;

    if(streq(quad_method,ANALYTIC_QUAD)) {
	LISP_SEND(fp,"(setq *quad-vars* nil)\n");

	SystemAbort("解析的積分対応は未決(call_LISP_procedure_WEQ)");
	/* call_LISP_proc_WEQ_analytic(); */
    }

    /* 数値積分法に対する生成 */
    quad_ptr = get_quadrature_ptr_by_name(quad_method);
    
    if(quad_ptr->rvars == 0 ) {
	LISP_SEND(fp,"(setq *quad-vars* nil)\n");
    }
    else {
	SystemAbort("QuadInterpolateに関する設定はほとんどやっとらんわ。\n");
    }

    LISP_SEND(fp,"(setq *eval-smbl* nil)\n");   
    LISP_SEND_d(fp,"(setq *dimension* %d)\n",quad_ptr->dimension);

    /* LISP処理の記述 */
    LISP_SEND(fp,"(make-linear-weak)\n");         /* *fem-integrand* 等作成 */


    if(solve_element_ptr->nonlinear_flag == NO) {
	/* 線形問題 */
	LISP_SEND(fp,"(make-num-integral)\n");        /* est****.dat作成 */
	LISP_SEND(fp,"(make-num-int-matrix-dat)\n");  /* ecal***.dat作成 */
    }
    else {
	/* 非線形問題 */
	LISP_SEND(fp,"(make-num-integral-nonlinear)\n");
	LISP_SEND(fp,"(make-num-int-matrix-dat-nonlinear)\n");
    }	
    return;
}
