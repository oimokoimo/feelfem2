/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_weak_eq_WEQ.c
 *      Date:   1993/10/26
 *   
 *   Purpose:   弱形式に関する方程式(数値積分毎)
 *              
 *   Functions: これがLISPプログラムのONEユニットとなる
 *              
 番号    *solve-no*       solve文番号
 *elem-no*        要素番号
 *integral-no*    積分法番号
 
 LISP式
 
 *fem-weak-eq*
 
 以下はSolveElementに共通の為、前routine make_elem_lispにて設定
 *test-funcs*
 *eval-vars*
 *eval-vars*の各シンボル(既知fem変数、未知変数)
 *fem-funcs*
 
 解析的積分法を採用する場合は、設定現在未対応
 *eval-smbl*
 
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void make_weak_eq_WEQ( solve_no , elem_no, no ,
		      quad_method, solve_element_ptr,fp)
     
     int solve_no,elem_no; 
     int           no;                       /* 数値積分法番号 */
     char         *quad_method;              /* 数値積分の名称 */
     SolveElement *solve_element_ptr;        /* solve_element_ptr */
     FILE         *fp;                        /* LISPプログラムへのポインタ */
{
    int i,j;
    
    int equations;
    int terms,match_terms;
    
    Equation *eq_ptr;
    Expression *expr_ptr;

    char  lisp_st[LISP_BUFSIZ];
    char *st_ptr;
    
    /*=====================*/
    /* 番号の作成          */
    /*=====================*/

    LISP_SEND_d(fp,"(setq *solve-no*    %d)\n",solve_no);
    LISP_SEND_d(fp,"(setq *elem-no*     %d)\n",elem_no);
    LISP_SEND_d(fp,"(setq *integral-no* %d)\n",no);
    
    equations = solve_element_ptr -> equations;
    
    LISP_SEND_s(fp,"(setq *quad-method* '%s)\n",quad_method);
    
    /*=====================*/
    /* *fem-weak-eq*を作成 */
    /*=====================*/
    st_ptr = lisp_st;
    st_ptr = make_list_st( st_ptr , "(setq *fem-weak-eq* '(");
    
    
    /* 式に対するループ(連立問題) */
    for(i=0;i<equations;i++) {
	if(i!= 0) {
	    st_ptr = make_list_st( st_ptr , "                      ");
	}
	
	eq_ptr      = *(solve_element_ptr -> eq_data + i);

	terms       =   eq_ptr -> equation_terms;

	
	/* 項に関するループ(複数の積分法が指定されている) */
	
	/* 各式に指定の積分法がいくつあるか計算 */
	match_terms =   0;
	for(j=0;j<terms;j++) {
	    if(streq(quad_method, *(eq_ptr->eq_method+j))) match_terms ++;
	}
	
	if( match_terms == 0 ) {
	    st_ptr = make_list_st( st_ptr , "( 0 ) ");
	}
	else {
	    /* 同じ積分法が指定されている場合はまとめる */
	    if(match_terms > 1) {
		st_ptr = make_list_st( st_ptr , "( +  ");
	    }
	    for(j=0;j<terms;j++) {
		if(streq(quad_method, *(eq_ptr->eq_method+j))) {
		    expr_ptr = *(eq_ptr->eq_term+j);
		    st_ptr = make_list_st( st_ptr , expr_ptr -> expr);
		}
	    }
	    if(match_terms > 1) {
		st_ptr = make_list_st( st_ptr , " )");
	    }

	}
	st_ptr = make_list_st( st_ptr , "\n");	
    }
    st_ptr = make_list_st( st_ptr , ")  )\n");
    end_list_st(st_ptr);

    LISP_SEND_s(fp,"%s",lisp_st);


    /*------------------------------------------*/
    /* 実際に積分法別にLISPプログラムを呼び出す */
    /*------------------------------------------*/
    call_LISP_procedure_WEQ(solve_no , elem_no, no ,
			    quad_method, solve_element_ptr,fp);

    
    return;
}
