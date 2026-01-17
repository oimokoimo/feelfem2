/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   let_fem_fem.c
 *      Date:   1994/01/28
 *
 *   Purpose:   fem変数 ＝ fem変数の処理(微分処理なし)
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../mesh_comp/mesh_comp.h"
#include "../var_comp/var_comp.h"

extern FILE     *get_let_fp();    /* 単一let文のファイルポインタを返す  */


void let_fem_fem( fp_main , let_no , let_ptr ,from,to, max_buf )
     FILE *fp_main;
     int   let_no;
     Let  *let_ptr;
     char *from[];       /* term_convert用のバッファ */
     char *to[];
     int   max_buf;
{
    int i;
    Expression *expr_ptr;
    int term_converts;

    int AT_flag;

    FILE *fp;
    Point *point_ptr;

    char *name;


    char name_buf[80];
    char name_buf2[80];

    
    term_converts = 0;
    expr_ptr = let_ptr -> expr;


    /* let文対応FORTRANファイルのオープン */
    fp = get_let_fp();
    
    /*    sprintf(name_buf,LET_FNAME,let_no);
     *    StoreMakefile(name_buf,USER_LIBRARY);
     *
     *    fp = OpenFileToWrite(name_buf);
     */


    /* main ルーチンでの代入 */
    make_main_let_call(fp_main,let_no,let_ptr);

    /* subroutine文の作成 */
    make_let_called(fp,let_no,let_ptr);
    
    /* 定形処理 */
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);

    /* 将来はNSETデータにしたいだす */
    if(let_ptr->let_place == LET_AT) {
	AT_flag = YES;
    }
    else {
	AT_flag = NO;
    }
    if(AT_flag) {
	PUT(fp,"      parameter (NPTS = %d)\n",let_ptr->regions);
    }
	

    common_parameters(fp);
    COM;

    /* 変数宣言               */
    /* dimension 及び integer */
    make_let_called_dimension(fp,let_no,let_ptr);


    if(AT_flag) {
	PUT(fp,"      dimension npt(NPTS)\n");
    }

    CommonBlock(fp);

    if(AT_flag) {
	F77("      data npt/ ");
	for(i=0;i<let_ptr->regions;i++) {
	    if(i!= 0) F77(",");
	    point_ptr = get_point_ptr_by_name(*(let_ptr->region_name + i));
	    PUT(fp,"%d",point_ptr->node_no);
	}
	F77("/\n");
    }


    /*=======================*/
    /* fem_fem の NORMAL LET */
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

	    /* 節点位置での代入指定 */
	    if(AT_flag) {
		sprintf(name_buf,"%s(npt(i))",name,name);
	    }
	    else {
		sprintf(name_buf,"%s(i)",name,name);
	    }

	    to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;

	    break;

	  case FEM:
	    from[term_converts] = name;
	    sprintf(name_buf2,FEM_VAR_NAME77,name);

	    if(AT_flag) {
		sprintf(name_buf,"%s(npt(i))",name_buf2);
	    }
	    else {
		sprintf(name_buf,"%s(i)",name_buf2);
	    }
	    
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

    if(AT_flag) {
	F77("      do 100 i=1,NPTS\n");
    }
    else {
	F77("      do 100 i=1,npmax\n");
    }

    COM;
    
    F77("        ");
    PUT(fp,FEM_VAR_NAME77,let_ptr->var_name);

    if(AT_flag) {
	F77("(npt(i)) = ");
    }
    else {
	F77("(i) = ");
    }

    PUT(fp,"%s\n",term_convert(expr_ptr->expr_inf,from,to,term_converts));

    COM;
    
    F77("  100 continue\n");
    COM;

/*    PUT(fp,"      call report('let[%d] (FEM = FEM) END [line %d]')\n",
	let_no,let_ptr->yylineno);
*/

    F77("      return\n");
    F77("      end\n");

    /* fclose(fp); */

    return;

}
