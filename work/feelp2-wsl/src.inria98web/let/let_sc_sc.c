/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   let_sc_sc.c
 *      Date:   1994/01/13
 *
 *   Purpose:   scalar変数 ＝ scalar変数の処理
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"

#include "../var_comp/var_comp.h"
#include "../mesh_comp/mesh_comp.h"

extern FILE     *get_let_fp();    /* 単一let文のファイルポインタを返す  */

void let_sc_sc( fp_main , let_no , let_ptr ,from,to, max_buf )
     FILE *fp_main;
     int   let_no;
     Let  *let_ptr;
     char *from[];       /* term_convert用のバッファ */
     char *to[];
     int   max_buf;
{
    int i;
    Expression *expr_ptr;
    Point      *point_ptr;
    int term_converts;

    FILE *fp;

    char *name;


    char name_buf[80];
    char name_buf2[80];

    
    term_converts = 0;
    expr_ptr = let_ptr -> expr;


    /* let文対応FORTRANファイルのオープン */
    fp = get_let_fp();
    /*
     * sprintf(name_buf,LET_FNAME,let_no);
     * StoreMakefile(name_buf,USER_LIBRARY);
     * fp = OpenFileToWrite(name_buf);
     *
     */

    /* main ルーチンでの代入 */
    make_main_let_call(fp_main,let_no,let_ptr);

    /* subroutine文の作成 */
    make_let_called(fp,let_no,let_ptr);
    
    /* 定形処理 */
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);

    /* 節点指定代入文の場合、NPTにmesh節点番号を代入する 
       実節点番号はcommonブロック中のn_nodeno dataにより、得る */
    
    if(let_ptr->let_place == LET_AT) {
	point_ptr = get_point_ptr_by_name( *(let_ptr->region_name + 0));

	PUT(fp,"      parameter (NPT = %d)\n",point_ptr->mesh_no);
    }


    common_parameters(fp);
    COM;

    /* 変数宣言               */
    /* dimension 及び integer */
    make_let_called_dimension(fp,let_no,let_ptr);

    /* COMMONブロック宣言 */
    CommonBlock(fp);

    comment1(fp);

    /*=======================*/
    /* sc_sc の NORMAL LET */
    /*                       */
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
		SystemAbort("term_buffer 不足(@let_fem_fem)");
	    }

	    sprintf(name_buf,SCALAR_VAR_NAME77,name);
	    to[term_converts] = MakeStringCopy(name_buf);
	    from[term_converts] = name;
	    term_converts++;
	    
	    break;

	  case SYSTEM_VAR:   /* 小文字x,y,z */
	    from[term_converts] = name;
	    sprintf(name_buf,"%s(n_nodeno(NPT))",name,name);
	    to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;

	    break;

	  case FEM:
	    from[term_converts] = name;
	    sprintf(name_buf2,FEM_VAR_NAME77,name);
	    sprintf(name_buf,"%s(n_nodeno(NPT))",name_buf2);
	    to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;

	    break;

	  case EWISE:
	  case MATERIAL:
	    SystemAbort("Illegal code@let_fem_fem");
	    break;

	  default:
	    SystemAbort("Unknown code@let_fem_fem");
	    break;
	}
    }

    comment1(fp);

    COM;

    F77("        ");
    PUT(fp,SCALAR_VAR_NAME77,let_ptr->var_name);
    F77(" = ");

    PUT(fp,"%s\n",term_convert(expr_ptr->expr_inf,from,to,term_converts));

    COM;

/*    PUT(fp,"      call report('let[%d] (SC = SC) END [line %d]')\n",
	let_no,let_ptr->yylineno);
*/
    COM;
    
    F77("      return\n");
    F77("      end\n");

    /* fclose(fp); */

    return;

}



