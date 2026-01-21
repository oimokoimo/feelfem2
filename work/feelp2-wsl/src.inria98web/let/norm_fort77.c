/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   norm_fort77.c
 *      Date:   1994/12/20
 *
 *   Purpose:   double変数 ＝ norm[fem変数式の処理](微分処理なし)
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../mesh_comp/mesh_comp.h"
#include "../var_comp/var_comp.h"

extern FILE     *get_let_fp();    /* 単一let文のファイルポインタを返す  */
static int  norm_no = 0;

#define MAX_BUF  38

static char *from[MAX_BUF];
static char *to[MAX_BUF];

void norm_fort77( fp_main ,  norm_ptr )
     FILE *fp_main;
     Norm  *norm_ptr;
{
    int i;
    int   max_buf;
    Expression *expr_ptr;
    int term_converts;

    FILE *fp;
    Point *point_ptr;

    char *name;

    char name_buf[80];
    char name_buf2[80];

    max_buf = MAX_BUF;   /* let_fem_femを流用したからこうゆうことをしている */
    norm_no++;
    
    term_converts = 0;
    expr_ptr = norm_ptr -> expr;


    /* norm文対応FORTRANファイルのオープン */
    fp = get_let_fp();
    
    /*    sprintf(name_buf,LET_FNAME,let_no);
     *    StoreMakefile(name_buf,USER_LIBRARY);
     *
     *    fp = OpenFileToWrite(name_buf);
     */


    /* main ルーチンでの代入 */
    make_main_norm_call(fp_main,norm_no,norm_ptr);

    /* subroutine文の作成 */
    make_norm_called(fp,norm_no,norm_ptr);
    
    /* 定形処理 */
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);

    common_parameters(fp);
    COM;

    /* 変数宣言               */
    /* dimension 及び integer */
    make_norm_called_dimension(fp,norm_no,norm_ptr);


    CommonBlock(fp);

    /*=======================*/
    /* fem変数式 の          */
    /* term_convertの作成    */
    /*=======================*/
    for(i=0;i<expr_ptr -> identifiers;i++) {
	name = *(expr_ptr->identifier + i);

	switch(get_var_kind( name ) ) {
	  case INT:
	  case DOUBLE:
	  case CONST:
	    /* term_convert用バッファ作成 */
	    if(term_converts == max_buf) {
		SystemAbort("term_buffer 不足(@norm_fem_fem)");
	    }

	    sprintf(name_buf,SCALAR_VAR_NAME77,name);
	    to[term_converts] = MakeStringCopy(name_buf);
	    from[term_converts] = name;
	    term_converts++;
	    
	    break;

	  case SYSTEM_VAR:   /* 小文字x,y,z */
	    from[term_converts] = name;

	    /* 節点位置での代入指定 */
	    sprintf(name_buf,"%s(i)",name,name);
	    to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;

	    break;

	  case FEM:
	    from[term_converts] = name;
	    sprintf(name_buf2,FEM_VAR_NAME77,name);

	    sprintf(name_buf,"%s(i)",name_buf2);
	    to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;

	    break;

	  case EWISE:
	  case MATERIAL:
	    SystemAbort("Illegal code@norm_fem_fem");
	    break;

	  default:
	    SystemAbort("Unknown code@norm_fem_fem");
	    break;
	}
    }

    comment1(fp);

    /* norm計算の初期化 */
    F77("      dnorm = 0.0d0\n");
    COM;

    /* ノルム計算ループのはじまり */
    F77("      do 100 i=1,npmax\n");
    COM;

    /* FEM評価式の各点での評価 */
    F77("        dat = ");    
    PUT(fp,"%s\n",term_convert(expr_ptr->expr_inf,from,to,term_converts));
    COM;

    /* norm種別毎の対応 */
    switch(norm_ptr -> norm_type) {
      case L2NORM:
	F77("       dnorm = dnorm + dat * dat\n");
	break;
	
      case MAXNORM:
	F77("       if(dnorm .LT. abs(dat)) dnorm = abs(dat)\n");
	break;
    }
    
    F77("  100 continue\n");
    COM;
    
    /* L2_normの処理 */
    if(norm_ptr->norm_type == L2NORM) {
	F77("      dnorm = sqrt(dnorm / npmax)\n");
	COM;
    }

    /* double変数への代入 */
    F77("      ");
    PUT(fp,SCALAR_VAR_NAME77,norm_ptr->var_name);
    F77(" = dnorm\n");
    COM;

    F77("      return\n");
    F77("      end\n");

    /* fclose(fp); */

    return;

}
