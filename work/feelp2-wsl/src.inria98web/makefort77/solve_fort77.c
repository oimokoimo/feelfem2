/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_fort77.c
 *      Date:   1993/07/13
 *   
 *   Purpose:   メイン関数のsolve呼びだしプログラムを作成
 *              
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"
#include "../parallel/parallel.h"

solve_fort77( fp , solve_ptr )
     FILE *fp;
     Solve *solve_ptr;
{
    int i;
    SolveFORT77 *solve77_ptr;

    solve77_ptr = solve_ptr->solve77_ptr;


    /* subroutine文の作成 */
    F77("*---------------\n");
    F77("      call ");
    if(solve77_ptr->solve_no < 10 ) {
	PUT(fp,SOLVE_NAME77_A,solve77_ptr->solve_no);
    }
    else {
	PUT(fp,SOLVE_NAME77_B,solve77_ptr->solve_no);
    }
    F77("(");

    /*--------------*/
    /* 引き数の設定 */
    /*--------------*/
    
    /* 変数feelの受け渡し */
    /* ワーク領域は、インデックスが1から始まる用にメインから呼ぶ。
       call solve??(feel(np_work),てな具合) OLD F_ALLOC */

    F77("feel,imode");

    if(parallel) {
	PUT(fp,",feel(npp_base%d)",solve77_ptr->solve_no);
    }


    switch(what_dimension()) {
      case 1:
	F77(",feel(np_x)");
	break;
	
      case 2:
	F77(",feel(np_x),feel(np_y)");
	break;

      case 3:
	F77(",feel(np_x),feel(np_y),feel(np_z)");
	break;
    }


    /* fem 変数 */
    for(i=0;i<solve77_ptr->fem_vars;i++) {
	F77(",feel(");
	PUT(fp,NP_FEM_VAR,*(solve77_ptr->fem_var_name + i));
	F77(")");
    }

    /* ewise 変数 */
    for(i=0;i<solve77_ptr->ewise_vars;i++) {
	F77(",feel(");
	PUT(fp,NP_EWISE_VAR,*(solve77_ptr->ewise_var_name + i));
	F77(")");
    }

    /* scalar 変数 */
    for(i=0;i<solve77_ptr->scalar_vars;i++) {
	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,*(solve77_ptr->scalar_var_name + i));
    }

    if(parallel) F77(",noerr)\n");
    else         F77(")\n");

    /* 並列版処理 */
    if(parallel) {
	PUT(fp,"        if(noerr.EQ.1) goto %4d\n",9001);
	PUT(fp,"        if(imode.NE.0) then\n");
	F77(   "          write(io_stderr,*) 'Cannot allocate memory ',imode\n");
	F77(   "          stop 'memory allocation error'\n");
	F77(   "        endif\n");
    }
    else {
      F77("      if(imode .NE. 0) goto 8888\n");
    }

    F77("*---------------\n");



/*    if(parallel) {
	F77("      if(p_rank.eq.0) then\n");
	F77("        call p_close_file\n");
	PUT(fp,"        NO = %d\n",solve77_ptr->solve_no);
	F77("        close(io_fem+NO-1)\n");
	F77("      endif\n");
      }
*/

    return;
}

    




