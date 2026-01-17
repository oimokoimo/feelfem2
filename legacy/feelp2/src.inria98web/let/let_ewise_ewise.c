/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   let_ewise_ewise.c
 *      Date:   1993/12/28
 *  Modified:   2001/01/27
 *   
 *   Purpose:   ewise変数 ＝ ewise変数の処理
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"

#include "../var_comp/var_comp.h"
#include "../parallel/parallel.h"

extern FILE     *get_let_fp();    /* 単一let文のファイルポインタを返す  */

let_ewise_ewise( fp_main , let_no , let_ptr ,from,to, max_buf )
     FILE *fp_main;
     int   let_no;
     Let  *let_ptr;
     char *from[];       /* term_convert用のバッファ */
     char *to[];
     int   max_buf;
{
    int i;
    int term_converts;
    FILE *fp;
    char *name;
    Expression *expr_ptr;
    EWISE_type *ewise_type_ptr;
    EWISE_var  *ewise_var_ptr;
    int         ewise_no;
    char name_buf[80];
    char name_buf2[80];

    term_converts = 0;
    expr_ptr = let_ptr -> expr;

    ewise_var_ptr = get_ewise_ptr_by_name( let_ptr -> var_name );
    ewise_no= get_ewise_var_no_byname( let_ptr -> var_name);

    if(ewise_var_ptr -> ewise_types != 1) {
	SystemAbort("複数domainにまたがるewise変数は現在サポートしていない(let_ewise_sc)");
    }
    ewise_type_ptr = ewise_var_ptr->ewise_type_ptr[0];

    fp = get_let_fp();
    
    /*
     *    sprintf(name_buf,LET_FNAME,let_no);
     *    StoreMakefile(name_buf,USER_LIBRARY);
     *  fp = OpenFileToWrite(name_buf);
     */
    
    /* feel_mainでのサブルーチンコール */

    if(parallel) {
	PUT(fp_main,"      if(p_rank .eq. 0 ) then\n");
    }

    PUT(fp_main,"      call ");
    PUT(fp_main,LET_NAME,let_no);
    PUT(fp_main,"(feel,");
    XYZ_in_call(fp_main);
    
    PUT(fp_main,",feel(");
    PUT(fp_main,NP_EWISE_VAR,let_ptr -> var_name );
    PUT(fp_main,")");


    /* メインルーチンでの呼び出し関数の作成
       ついでに、term_convert用テーブルを作成 */

    for(i=0;i<expr_ptr -> identifiers;i++) {
	name = *(expr_ptr->identifier + i);
	
	switch(get_var_kind( name ) ) {
	  case INT:
	  case DOUBLE:
	  case CONST:
	    PUT(fp_main,",");
	    PUT(fp_main,SCALAR_VAR_NAME77,name);

	    /* term_convert用バッファ作成 */
	    if(term_converts == max_buf) {
		SystemAbort("term_buffer 不足(@let_ewise_sc)");
	    }
	    sprintf(name_buf,SCALAR_VAR_NAME77,name);
	    to[term_converts] = MakeStringCopy(name_buf);
	    from[term_converts] = name;
	    term_converts++;
	    
	    break;

	  case EWISE:
	    /* term_convert用バッファ作成 */
	    if(term_converts == max_buf) {
		SystemAbort("term_buffer 不足(@let_ewise_ewise)");
	    }
	    sprintf(name_buf2,EWISE_VAR_NAME77,name);
	    sprintf(name_buf,"%s(i)",name_buf2);
	    to[term_converts] = MakeStringCopy(name_buf);
	    from[term_converts] = name;
	    term_converts++;

	    if(streq(name,let_ptr->var_name)) break;
	    PUT(fp_main,",feel(");
	    PUT(fp_main,NP_EWISE_VAR,name );
	    PUT(fp_main,")");

	    break;

	  case SYSTEM_VAR:   /* 小文字x,y,z */
	    SystemAbort("Illegal system var@let_ewise_ewise");
	    from[term_converts] = name;
	    sprintf(name_buf,"%s%s",name,name);
	    to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;

	    break;


	  case FEM:
	  case MATERIAL:
	    SystemAbort("Illegal code@let_ewise_sc");
	    break;

	  default:
	    SystemAbort("Unknown code@let_ewise_sc");
	    break;
	}
    }
    PUT(fp_main,")\n");

    if(parallel) {
	PUT(fp_main,"      endif\n");
	PUT(fp_main,"      new_size=n_edat(n_ewise(%d,1),1)*n_ewise(%d,2)\n",
	    ewise_no+1,ewise_no+1);
	PUT(fp_main,"      call mpi_bcast(feel(");
	PUT(fp_main,NP_EWISE_VAR,let_ptr -> var_name );
	PUT(fp_main,"),new_size*2,mpi_real,0,\n");
	PUT(fp_main,"     $ mpi_comm_world,ierror)\n");
    }

    /*==========================*/
    /* letXXX.fプログラムの作成 */
    /*==========================*/
    F77("      subroutine ");
    PUT(fp,LET_NAME,let_no);
    F77("(feel,");

    XYZ_in_subroutine(fp);
    F77(",");
    
    /* ewise変数の仮引き数 */
    PUT(fp,EWISE_VAR_NAME77,let_ptr -> var_name );


    for(i=0;i<expr_ptr -> identifiers;i++) {
	name = *(expr_ptr->identifier + i);

	switch(get_var_kind( name ) ) {
	  case INT:
	  case DOUBLE:
	  case CONST:
	    F77(",");
	    PUT(fp,SCALAR_VAR_NAME77,name);
	    break;

	  case SYSTEM_VAR:   /* 小文字x,y,z */
	    break;

	  case EWISE:
	    if(streq(name,let_ptr->var_name)) break;
	    F77(",");	    
	    PUT(fp,EWISE_VAR_NAME77,name );
	    break;

	  case FEM:
	  case MATERIAL:
	    SystemAbort("Illegal code@let_ewise_sc2");
	    break;

	  default:
	    SystemAbort("Unknown code@let_ewise_sc2");
	    break;
	}
    }
    F77(")\n");

    /*==============*/
    /*   定形宣言    */
    /*==============*/
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);
    common_parameters(fp);

    /* 要素番号パラメータ文 */
    COM;
    PUT(fp,"      parameter (NENO = %d)\n",
	get_domain_edatno_by_name(ewise_type_ptr -> domain_name) );
    COM;

    F77("      real*4 feel(*)\n");

    XYZ_dimension(fp);

    F77("      dimension ");
    PUT(fp,EWISE_VAR_NAME77,let_ptr->var_name);

    if(ewise_type_ptr -> points == 1) {
	F77("(*)");
    }
    else {
	PUT(fp,"(%d,*)",ewise_type_ptr -> points);
    }
    F77("\n");

    /* ewise変数の宣言 */
    for(i=0;i<let_ptr->ew_vars;i++) {
	if(streq(*(let_ptr->ew_var_name+i),let_ptr->var_name)) continue;
	F77("      dimension ");
	PUT(fp,EWISE_VAR_NAME77,*(let_ptr->ew_var_name+i));	
	PUT(fp,"(*)\n");   /* 一自由度のみ */
    }

    /* 整数変数の宣言 */
    for(i=0;i<let_ptr->int_vars;i++) {
	F77("      integer ");
	PUT(fp,SCALAR_VAR_NAME77,*(let_ptr->int_var_name + i));
	F77("\n");
    }

    CommonBlock(fp);
    comment2(fp);
    
    /*    F77("      np_push = np_work\n"); OLD F_ALLOC */
    F77("      call f_alloc_push\n");
    COM;
    
    F77("      neelem = n_edat(NENO,1)\n");
    F77("      nenode = n_edat(NENO,2)\n");
    PUT(fp,"      call f_alloc(np_ielem,'let%d(ielem)',neelem*nenode,0,0)\n",let_no);
    PUT(fp,"      call f_alloc(np_matno,'let%d(matno)',neelem,       0,0)\n",let_no);
    F77("      iunit = NENO + io_edat - 1\n");
    F77("*\n");
    F77("      call get_ielem(iunit,feel(np_ielem),feel(np_matno),neelem,nenode)\n");
    COM;

    /* let coルーチン  */
    F77("      call ");
    PUT(fp,CO_LET_NAME,let_no);
    F77("(");
    XYZ_in_subroutine(fp);
    F77(",feel(np_ielem),feel(np_matno),neelem,nenode,");
    
    PUT(fp,EWISE_VAR_NAME77,let_ptr -> var_name );
    
    for(i=0;i<expr_ptr -> identifiers;i++) {
	name = *(expr_ptr->identifier + i);

	switch(get_var_kind( name ) ) {
	  case INT:
	  case DOUBLE:
	  case CONST:
	    F77(",");
	    PUT(fp,SCALAR_VAR_NAME77,name);
	    break;
	    
	  case SYSTEM_VAR:   /* 小文字x,y,z */
	    break;
	  case EWISE:
	    if(streq(name,let_ptr->var_name)) break;
	    PUT(fp,",");
	    PUT(fp,EWISE_VAR_NAME77,name );
	    break;

	  case FEM:
	  case MATERIAL:
            SystemAbort("Illegal code@let_ewise_sc2");
	    break;

	  default:
            SystemAbort("Unknown code@let_ewise_sc2");
	    break;
	}
    }
    F77(")\n");
    
    COM;

/*    PUT(fp,"      call f_free('let%d(ielem)',neelem*nenode,0)\n",let_no);
 *    PUT(fp,"      call f_free('let%d(matno)',neelem       ,0)\n",let_no);
 *    COM;
 */

/*    PUT(fp,"      call report('let[%d] (EW = SC) END [line %d]')\n",
	let_no,let_ptr->yylineno);
*/

    COM;

    /*    F77("      np_work = np_push\n");   OLD F_ALLOC */
    F77("      call f_alloc_pop\n");
    COM;

    F77("      return\n");
    F77("      end\n");


    /*===========================================*/
    /* let_coルーチン                            */
    /*  coルーチンには、matno,ielemが渡っている  */
    /*===========================================*/
    F77("      subroutine ");
    PUT(fp,CO_LET_NAME,let_no);
    F77("(");
    XYZ_in_subroutine(fp);
    F77(",ielem,matno,neelem,nenode,");
    PUT(fp,EWISE_VAR_NAME77,let_ptr -> var_name );
    
    for(i=0;i<expr_ptr -> identifiers;i++) {
	name = *(expr_ptr->identifier + i);

	switch(get_var_kind( name ) ) {
	  case INT:
	  case DOUBLE:
	  case CONST:
	    F77(",");
	    PUT(fp,SCALAR_VAR_NAME77,name);
	    break;
	    
	  case SYSTEM_VAR:   /* 小文字x,y,z */
	    break;

	  case EWISE:
	    if(streq(name,let_ptr->var_name)) break;
	    F77(",");
	    PUT(fp,EWISE_VAR_NAME77,name );
	    break;

	  case FEM:
	  case MATERIAL:
            SystemAbort("Illegal code@let_ewise_sc2");
	    break;

	  default:
            SystemAbort("Unknown code@let_ewise_sc2");
	    break;
	}
    }
    F77(")\n");

    /*==============*/
    /*   定形宣言    */
    /*==============*/
    real8(fp);

    XYZ_dimension(fp);

    F77("      dimension ielem(nenode,neelem),matno(neelem)\n");

    F77("      dimension ");
    PUT(fp,EWISE_VAR_NAME77,let_ptr->var_name);

    if(ewise_type_ptr -> points == 1) {
	F77("(*)");
    }
    else {
	PUT(fp,"(%d,*)",ewise_type_ptr -> points);
    }
    F77("\n");


    /* ewise変数の宣言 */
    for(i=0;i<let_ptr->ew_vars;i++) {
	if(streq(*(let_ptr->ew_var_name+i),let_ptr->var_name)) continue;
	F77("      dimension ");
	PUT(fp,EWISE_VAR_NAME77,*(let_ptr->ew_var_name+i));	
	PUT(fp,"(*)\n");   /* 一自由度のみ */
    }

    /* 整数変数の宣言 */
    for(i=0;i<let_ptr->int_vars;i++) {
	F77("      integer ");
	PUT(fp,SCALAR_VAR_NAME77,*(let_ptr->int_var_name + i));
	F77("\n");
    }
    comment2(fp);

    F77("      do 100 i=1,neelem\n");
    COM;

    if(let_ptr->x_flag != NO) {
	F77("      xx = ");
	switch(ewise_type_ptr -> etype) {
	  case TRI:
	    F77("(x(ielem(1,i))+x(ielem(2,i))+x(ielem(3,i)))/3.0d0\n");
	    break;

	  case RECT:
	    F77("(x(ielem(1,i))+x(ielem(2,i))+x(ielem(3,i))+x(ielem(4,i)))/4.0d0\n");
	    break;

	  default:
	    SystemAbort("現在対応は三角形、四辺形のみ(let_ewise_sc)");
	}
	COM;
    }

    if(let_ptr->y_flag != NO) {
	F77("      yy = ");
	switch(ewise_type_ptr -> etype) {
	  case TRI:
	    F77("(y(ielem(1,i))+y(ielem(2,i))+y(ielem(3,i)))/3.0d0\n");
	    break;

	  case RECT:
	    F77("(y(ielem(1,i))+y(ielem(2,i))+y(ielem(3,i))+y(ielem(4,i)))/4.0d0\n");
	    break;

	  default:
	    SystemAbort("現在対応は三角形、四辺形のみ(let_ewise_sc)");
	}
	COM;
    }

    if(let_ptr->z_flag != NO) {
	SystemAbort("現在３次元には対応せず(let_ewise_sc)");
    }

    if(let_ptr -> let_place == LET_IN) {
	F77("      IF(");
	for(i=0;i<let_ptr->regions;i++) {
	    if(i != 0) {
		F77(" .OR. ");
	    }

	    PUT(fp,"matno(i).eq.%d",
		get_domain_region_no(ewise_type_ptr->domain_name,
				     *(let_ptr->region_name + i)));
	}
	F77(") THEN\n");
    }
	

    F77("        ");
    PUT(fp,EWISE_VAR_NAME77,let_ptr->var_name);
    F77("(i)=");

    PUT(fp,"%s\n",term_convert(expr_ptr->expr_inf,from,to,term_converts));
    
    COM;

    if(let_ptr -> let_place == LET_IN) {
	F77("      ENDIF\n");
	COM;
    }

    
    F77(" 100  continue\n");
    COM;
    F77("      return\n");
    F77("      end\n");

    /* fclose(fp); */

    return;

}
