/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_elem_commons.c
 *      Date:   1993/11/09
 *   
 *   Purpose:   数値積分用のCOMMONブロック生成
 *   Functions: 
 *              ElementFORT77構造体のメンバ ↓ を設定
 *   int *quad_terms;                   COMMONブロックに宣言必要な配列変数の数
 *   char ***quad_term_var_aptr;        配列名への配列
 *   char ***quad_term_expr_aptr;       LISPが出力した定義式への配列
 *   int *quad_consts;                  COMMONブロックに宣言する定数変数の数
 *   char ***quad_const_var_aptr;       変数名への配列
 *
 *   quad_term_expr_aptr は11/15に追加した
 */
#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"

#include "../quadrature/quadrature.h"

make_elem_commons()
{
    int i,j,k,l;
    int terms,cterms;      /* quad_terms, quad_consts への代入本体 */
    char buf[BUFSIZ];
    char term[BUFSIZ];
    char term2[BUFSIZ];

    static FILE *fp_read_dbg;
    FILE *OpenFileToRead();
    char fname[FNAME_SIZE];

    int solves,solve_elements;
    int quad_methods;
    Solve         *solve_ptr;
    SolveElement  *solve_element_ptr;
    ElementFORT77 *elem77_ptr;

    Quadrature *quad_ptr;
    int       quad_nodes;

    
    int    *quad_terms;             /* ElementFORT77構造体内 */
    int    *quad_consts;            /* ElementFORT77構造体内 */

    char ***quad_term_var_aptr;     /* aptr は array ptr     */
    char **quad_term_var_ptr;       /* 配列変数名へのポインタ*/

    char ***quad_term_expr_aptr;    /* aptr は array ptr     */
    char **quad_term_expr_ptr;      /* 配列変数の計算式      */

    int  **quad_term_type_aptr;     /* 微分値のタイプ aptr   */
    int   *quad_term_type_ptr;      /* タイプへのポインタ    */

    char ***quad_const_var_aptr;    /* aptr は array ptr     */
    char **quad_const_var_ptr;      /* 定数変数名へのポインタ*/

    int dummy;
    
    /* 空間変数に関する処理 */
    int *x_flag,*y_flag,*z_flag;

    solves = how_many_solves();
    

    for(i=0;i<solves;i++) {


	solve_ptr = get_nth_solve_ptr(i);

	solve_elements = solve_ptr -> solve_elements;

	for(j=0;j<solve_elements;j++) {


	    
	    solve_element_ptr = *(solve_ptr -> solve_elem_dat + j);
	    
	    elem77_ptr = solve_element_ptr -> elem77_dat;

	    /* ElementFORT77構造体内の、
	       quad_terms,quad_term_var quad_consts,quad_const_var_aptr
	       の領域確保 */
	    quad_methods = elem77_ptr -> quad_methods;
	    quad_terms   = (int *)FEEL_GetMemory(sizeof(int) * 
							  quad_methods      );
	    quad_term_var_aptr = (char ***)FEEL_GetMemory(sizeof(char **) * 
							  quad_methods      );
	    quad_term_expr_aptr = (char ***)FEEL_GetMemory(sizeof(char **) * 
							  quad_methods      );
	    quad_term_type_aptr = (int **)FEEL_GetMemory(sizeof(int *) * 
				    	 		  quad_methods      );

	    quad_consts  = (int *)FEEL_GetMemory(sizeof(int) * 
							  quad_methods      );
	    quad_const_var_aptr = (char ***)FEEL_GetMemory(sizeof(char **) * 
							  quad_methods      );
	    /* 空間変数に関する処理 */
	    x_flag = (int *)FEEL_GetMemory(sizeof(int) * quad_methods);
	    y_flag = (int *)FEEL_GetMemory(sizeof(int) * quad_methods);
	    z_flag = (int *)FEEL_GetMemory(sizeof(int) * quad_methods);

	    /* 空間変数使用フラグ初期化 */
	    for(k=0;k<quad_methods;k++) {


		*(x_flag + k) = NO;
		*(y_flag + k) = NO;
		*(z_flag + k) = NO;
	    }

	    elem77_ptr -> quad_terms = quad_terms;
	    elem77_ptr -> quad_term_var_aptr = quad_term_var_aptr;
	    elem77_ptr -> quad_term_expr_aptr = quad_term_expr_aptr;
	    elem77_ptr -> quad_term_type_aptr = quad_term_type_aptr;

	    elem77_ptr -> quad_consts = quad_consts;
	    elem77_ptr -> quad_const_var_aptr = quad_const_var_aptr;

	    elem77_ptr -> x_flag = x_flag;
	    elem77_ptr -> y_flag = y_flag;
	    elem77_ptr -> z_flag = z_flag;

	    
	    for(k=0;k<quad_methods;k++) {



		if(*(elem77_ptr -> quad_type+k) == ANALYTICAL) {
		    *(quad_terms+k) = 0;    /* 解析的積分時にはCOMMON不要 */
		    *(quad_consts+k)= 0;
		    continue;
		}
		
		/* Quadrature構造体へのポインタ */
		quad_ptr = get_quadrature_ptr_by_name( *(elem77_ptr->
							 quad_name + k));

		sprintf(fname,EST_DAT_FILE,i+1,j+1,k+1);
		fp_read_dbg = fopen(fname,"r");
		if(fp_read_dbg == NULL) {
		  fprintf(stderr,"Cannot open %s to read\n",fname);
		  SystemAbort("Open file failed.");
		}


		StoreDeletefile( fname );

		
		/* このtermsには、空間変数も含んでいる     */

		terms = geti_file(fp_read_dbg); 

		cterms = quad_ptr -> consts;
		
		quad_term_var_ptr  = (char **)FEEL_GetMemory(sizeof(char *) *
							     terms );
		quad_term_expr_ptr = (char **)FEEL_GetMemory(sizeof(char *) *
							     terms );
		quad_term_type_ptr = (int   *)FEEL_GetMemory(sizeof(int   ) *
							     terms );

		quad_const_var_ptr = (char **)FEEL_GetMemory(sizeof(char *) *
							     cterms);

		/* 構造体への値の反映 */
		*(quad_terms+k)  =  terms;



		*(quad_consts+k) = cterms;



		
		*(quad_term_var_aptr + k) = quad_term_var_ptr;
		*(quad_term_expr_aptr + k) = quad_term_expr_ptr;


		*(quad_term_type_aptr + k) = quad_term_type_ptr;
		*(quad_const_var_aptr+ k) = quad_const_var_ptr;
		
		for(l=0;l<terms;l++) {



		    fgets_file(buf,sizeof(buf),fp_read_dbg,"make_elem_commons.1");
		    sscanf(buf,"%s %d %s",term,&dummy,term2);

		    /* 空間変数フラグをたてる */
		    if(streq(term,"qx")) *(x_flag + k) = YES;
		    if(streq(term,"qy")) *(y_flag + k) = YES;
		    if(streq(term,"qz")) *(z_flag + k) = YES;
		    
		    *(quad_term_var_ptr+l)  = MakeStringCopy(term);
		    *(quad_term_expr_ptr+l) = MakeStringCopy(term2);
		    *(quad_term_type_ptr+l) = dummy;
		}
		
		for(l=0;l<cterms;l++) {
		    /* 領域確保はしない */
		    *(quad_const_var_ptr+l) = *(quad_ptr -> const_var + l);
		}
		fclose(fp_read_dbg);   /* add 1998/09/17 win extention */
	    }
	}
    }
    return;
}

