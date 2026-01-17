/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   main_variable.c
 *      Date:   1993/06/11
 * 
 *  Modified:   1999/03/25 initialize allocated area
 * 
 *   
 *   Purpose:   feel fort77のメインプログラム上にfem変数、ewise変数の
 *              為の初期化を行う
 *   Functions: 
 *              
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "../var_comp/var_comp.h"
#include "../parallel/parallel.h"

void main_variable(fp)    /* システムfem,システムewise変数共通常のfem,ewise
			変数の構造体として与えられる                   */
     FILE *fp;
{
    int i;
    int fem_vars;
    int ewise_vars;

    Var *var_ptr;

    fem_vars = how_many_fem_vars();
    
    comment1(fp);
    fprintf(fp,"      np_fem = np_work_get_falloc()\n");
    comment1(fp);

    for(i=0;i<fem_vars;i++) {
	var_ptr = get_nth_fem_ptr(i);

	/* 領域割り付け */
	F77("      call f_alloc(");
	PUT(fp,NP_FEM_VAR,var_ptr->name);
	PUT(fp,",'fem var(%s)',npmax,1,0)\n",
	    var_ptr->name);

	/* Initialize */
	PUT(fp,"      call zerod(feel(");
	PUT(fp,NP_FEM_VAR,var_ptr->name);
	PUT(fp,"),npmax)\n");

	if(i!=fem_vars-1) fprintf(fp,"c\n");
    }
    comment1(fp);

    ewise_vars = how_many_ewise_vars();

    fprintf(fp,"      np_ewise = np_work_get_falloc()\n");

    if(ewise_vars != 0 ) {
    comment1(fp);

    for(i=0;i<ewise_vars;i++) {  /* ewise変数の入力データ中の並びと
				  get_nth_ewise_ptrの並びは同じで
				  なければならない。              */
	var_ptr = get_nth_ewise_ptr(i);


	/* n_ewise(*,1) には関連するedat番号が入っている */
	/* n_ewise(*,2) には要素当りの節点数が入っている */
	PUT(fp,"      new_size = n_edat(n_ewise(%d,1),1)*n_ewise(%d,2)\n",
		i+1,i+1);

	F77("      call f_alloc(");
	PUT(fp,NP_EWISE_VAR,var_ptr->name);

	PUT(fp,",'alloc ewise %s',new_size,1,0)\n",
		var_ptr->name);

	/* Initialize */
	PUT(fp,"      call zerod(feel(");
	PUT(fp,NP_EWISE_VAR,var_ptr->name);
	PUT(fp,"),new_size)\n");

	if(i!=ewise_vars-1) fprintf(fp,"c\n");
    }

    }     /* if(ewise_vars != 0) に対応する */
    
    comment1(fp);

    /* 本質的変数に関するreport作成 */

    if(parallel) {
	F77("      call rep_var(npmax,io_out)\n");
    }
    else {
	F77("      call rep_var\n");
    }

    COM;

    return;
}
