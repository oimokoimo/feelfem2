/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_test_funcs_vect.c
 *      Date:   1993/10/27
 *   
 *   Purpose:   試験関数リスト *test_funcs* を作成する
 *              
 *   Functions: 将来の拡張予定 ユーザ指定などがしたいですな。
 *              
 *              ( ( 第一の式に対する試験関数リスト)
 *                ( 第二の式に対する試験関数リスト)
 *                       ................
 *                ( 第ｎの式に対する試験関数リスト))
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

make_test_funcs_vect( fp , funcs , freedom ,equations)
     FILE *fp;
     char *funcs[];
     int   freedom[];
     int   equations;
{
    /* make_list_st を使わないばーじょん */

    int i,j;

    LISP_SEND(fp,"(setq *test-funcs* '(");
    for(i=0;i<equations;i++) {
	if(i != 0) LISP_SEND(fp,"                   ");

	LISP_SEND(fp,"(");                  /* 試験関数は各式毎にリスト */
	for(j=0;j<freedom[i];j++) {
	    LISP_SEND_sd(fp," %s_%d", funcs[i],j+1);
	}
	LISP_SEND(fp,")\n");
    }
    LISP_SEND(fp,") )\n");

    return;
}

	
