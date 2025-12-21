/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   let_fort77.c
 *      Date:   1993/12/27
 *   
 *   Purpose:   let文のfortranコード作成メインルーチン
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"

#define MAX_TERM_BUF  38

static int let_no = 0;

static int   term_converts;
static char *tc_from[MAX_TERM_BUF];
static char *tc_to[MAX_TERM_BUF];


void let_fort77( fp , let_ptr )
     FILE *fp;
     Let  *let_ptr;
{


    let_no++;

    switch(let_ptr -> let_type) {

      case LET_SC_FEMEWISE:


      case LET_FEM_FEMEWISE:
      case LET_FEM_OPERATOR:


      case LET_EWISE_FEM:
      case LET_EWISE_FEMEWISE:
      case LET_EWISE_OPERATOR:

	SystemWarning("現在let文のfort出力は一部を除き未対応");
	break;

      case LET_SC_SC:
	let_sc_sc(fp,let_no,let_ptr,tc_from,tc_to,MAX_TERM_BUF);
	break;

      case LET_FEM_FEM:
	let_fem_fem(fp,let_no,let_ptr,tc_from,tc_to,MAX_TERM_BUF);
	break;

      case LET_EWISE_SC:
	let_ewise_sc(fp,let_no,let_ptr,tc_from,tc_to,MAX_TERM_BUF);
	break;

      case LET_EWISE_EWISE:
	let_ewise_ewise(fp,let_no,let_ptr,tc_from,tc_to,MAX_TERM_BUF);
	break;

      default:
	SystemAbort("Illegal code in let_fort77");
	break;
    }

    return;
}
