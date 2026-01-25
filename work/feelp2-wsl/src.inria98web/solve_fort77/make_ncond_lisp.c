/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_ncond_lisp.c
 *      Date:   1994/02/03
 *   
 *   Purpose:   ノイマン境界条件に関するLISPプログラムを生成する
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "solve_fort77_funcs.h"


void make_ncond_lisp(fp,solve_ptr,solve_element_ptr,n_ptr,solve_no,ncond_no)
     FILE         *fp;
     Solve        *solve_ptr;
     SolveElement *solve_element_ptr;
     NeumannData  *n_ptr;
     int           solve_no,ncond_no;
{
    int i,j,k;
    int kptr;
    int unknown_vars;

    int freedom;
    int fem_vars;
    int scalar_vars;
    int bd_terms;

    char **name_ptr,*name;
    char *element_name;

    int        equations;                 /* 連立している方程式の数 */
    Equation **eq_ptrptr,*eq_ptr;

    EdgeBasis *test_eb_ptr[MAX_EQUATIONS]; /* Edge上の試験関数のBasis */
    EdgeBasis *unknown_eb_ptr[MAX_EQUATIONS];
    EdgeBasis *fem_eb_ptr[MAX_VARIABLES];
    EdgeBasis *shape_eb_ptr;
    EdgeBasis *eb_ptr;

    Expression **bd_expr_ptrptr;
    Expression  *bd_expr_ptr;

    /* SolveElement内のEquation情報引き出し */

    equations    = solve_element_ptr -> equations;
    eq_ptrptr    = solve_element_ptr -> eq_data;

    unknown_vars = n_ptr -> unknown_vars;
    fem_vars     = n_ptr -> fem_vars;
    scalar_vars  = n_ptr -> scalar_vars;

    /* ノイマン境界条件は単一のガウス積分法のみ */
    

    /* 
     * 試験関数のelementに対する構造体 EdgeBasis作成
     */

    freedom = 0;
    for(i=0;i<equations;i++) {
	eq_ptr = *(eq_ptrptr + i);
	test_eb_ptr[i] = make_edge_basis(eq_ptr->test_function);
	freedom = freedom + test_eb_ptr[i]->basis;
    }
    
    /*
     * 未知fem変数のelementに対するEdgeBasis構造体作成
     */
    for(i=0;i<solve_element_ptr -> unknowns;i++) {
	element_name = get_elem_name_by_ND(*(solve_element_ptr
					     ->unknown_name + i),
					   solve_element_ptr->domain_name);
	unknown_eb_ptr[i] = make_edge_basis( element_name );
    }

    /*
     *   NeumannData構造体に反映させる
     */
    n_ptr->unknown_basis = (EdgeBasis **)FEEL_GetMemory(sizeof(EdgeBasis *) *
							solve_element_ptr->
							unknowns);
    for(i=0;i<solve_element_ptr -> unknowns;i++) {
	*(n_ptr->unknown_basis + i) = unknown_eb_ptr[i];
    }


    /*
     * 既知fem変数のelementに対するEdgeBasis構造体作成
     */
    for(i=0;i<fem_vars;i++) {
	element_name = get_elem_name_by_ND(*(n_ptr -> fem_var_name + i),
					   solve_element_ptr->domain_name);
	fem_eb_ptr[i] = make_edge_basis( element_name );
    }
    /*
     *   NeumannData構造体に反映させる
     */
    n_ptr->fem_known_basis = (EdgeBasis **)FEEL_GetMemory(sizeof(EdgeBasis *) *
							  fem_vars);
    for(i=0;i<fem_vars;i++) {
	*(n_ptr->fem_known_basis + i) = fem_eb_ptr[i];
    }


    /*
     * 形状変換関数のelementに対するEdgeBasis構造体作成
     */
    shape_eb_ptr = make_edge_basis( solve_element_ptr -> shape_func );
    n_ptr->shape_basis = shape_eb_ptr;

    /*========================*/
    /* [LISP-SEND] 試験関数   */
    /*========================*/
    LISP_SEND(fp,"(setq *test-funcs* '(");
    for(i=0;i<equations;i++) {
	if(i !=0 ) LISP_SEND(fp,"                     ");
	LISP_SEND(fp,"(");
	for(j=0;j<test_eb_ptr[i]->basis;j++) {
	    LISP_SEND_sd(fp," %s_%d",test_eb_ptr[i]->element_name,
			 *(test_eb_ptr[i]->basis_no+j)+1);
	}
	LISP_SEND(fp,")");
	if(i!= equations -1) LISP_SEND(fp,"\n");
    }
    LISP_SEND(fp,") )\n");

    /*========================*/
    /* [LISP-SEND] 係数リスト */
    /*========================*/
    make_coff_vect(fp, freedom);
			 
    /*=============================================*/
    /* [LISP-SEND] 展開関数リスト *eval-vars*作成  */
    /*             まず未知変数から(SolveElement順)*/
    /*=============================================*/
    if(unknown_vars > 0) {
	kptr = 0;
	for(i=0;i<solve_element_ptr->unknowns;i++) {
	    LISP_SEND_s(fp,"(setq %s '(+ ",*(solve_element_ptr->unknown_name+i));
	    eb_ptr = unknown_eb_ptr[i];
	    for(j=0;j<eb_ptr->basis;j++) {
		kptr++;
		LISP_SEND_sdsd(fp," (* %s%d %s_%d)","M",kptr,
			       eb_ptr->element_name,
			      *(eb_ptr-> basis_no + j) + 1);
	    }
	    LISP_SEND(fp,"))\n");
	}
    }

    /*=============================================*/
    /* [LISP-SEND] 展開関数リスト *eval-vars*作成  */
    /*             既知FEM変数(NeumannData登録順)  */
    /*=============================================*/
    for(i=0;i<fem_vars;i++) {
	LISP_SEND_s(fp,"(setq %s '(+ ",*(n_ptr ->fem_var_name + i));
	eb_ptr = fem_eb_ptr[i];
	for(j=0;j<eb_ptr->basis;j++) {
	    LISP_SEND_sdsd(fp," (* %s_%d %s_%d)",
			   *(n_ptr->fem_var_name + i),
			   j+1,
			   eb_ptr->element_name,
			   *(eb_ptr-> basis_no + j) + 1);
	}
	LISP_SEND(fp,"))\n");
    }

    /*=================================*/
    /* [LISP-SEND] *eval-vars*の設定   */
    /*=================================*/
    if(unknown_vars + fem_vars == 0) {
	LISP_SEND(fp,"(setq *eval-vars* nil)\n");
    }
    else {
	LISP_SEND(fp,"(setq *eval-vars* '(");
	for(i=0;i<unknown_vars;i++) { /*さっきはsolve_element_ptrを使ったが */
	    LISP_SEND_s(fp," %s",*(n_ptr -> unknown_name + i));
	}

	for(i=0;i<fem_vars;i++) {
	    LISP_SEND_s(fp," %s",*(n_ptr -> fem_var_name + i));
	}
	LISP_SEND(fp,"))\n");
    }

    /*=================================*/
    /* [LISP-SEND] *fem-funcs*の設定   */
    /*=================================*/
    LISP_SEND(fp,"(setq *fem-funcs*\n");
    LISP_SEND(fp," '(");
    for(i=0;i<equations;i++) {
	if(i != 0) LISP_SEND(fp,"   ");

	for(j=0;j<test_eb_ptr[i]->basis;j++) {
	    LISP_SEND_sd(fp,"%s_%d ",test_eb_ptr[i]->element_name,
			 *(test_eb_ptr[i]->basis_no+j)+1);
	}
	LISP_SEND(fp,"\n");
    }
    if(unknown_vars > 0) {
	for(i=0;i<solve_element_ptr->unknowns;i++) {
	    LISP_SEND(fp,"   ");
	    eb_ptr = unknown_eb_ptr[i];
	    for(j=0;j<eb_ptr->basis;j++) {
		LISP_SEND_sd(fp,"%s_%d ",eb_ptr->element_name,
			       *(eb_ptr-> basis_no + j) + 1);
	    }
	    LISP_SEND(fp,"\n");
	}
    }
    for(i=0;i<fem_vars;i++) {
	LISP_SEND(fp,"   ");
	eb_ptr = fem_eb_ptr[i];
	for(j=0;j<eb_ptr->basis;j++) {
	    LISP_SEND_sd(fp,"%s_%d ",eb_ptr->element_name,
			   *(eb_ptr-> basis_no + j) + 1);
	}
	LISP_SEND(fp,"\n");
    }

    for(i=0;i<shape_eb_ptr -> basis;i++) {
	LISP_SEND_sd(fp," %s_%d",shape_eb_ptr->element_name,
		     *(shape_eb_ptr->basis_no+i)+1);
    }

    LISP_SEND(fp,") )\n");
    
    /*========================================*/
    /* [LISP-SEND] 各*fem-funcs*へのbound実行 */
    /*========================================*/
    /* まずは試験関数 */
    for(i=0;i<equations;i++) {
	for(j=0;j<test_eb_ptr[i]->basis;j++) {
	    make_fem_funcs_co_bound(fp , test_eb_ptr[i]->element_name,
				    *(test_eb_ptr[i]->basis_no+j));
	}
    }
    /* 未知FEM変数 */
    if(unknown_vars > 0) {
	for(i=0;i<solve_element_ptr->unknowns;i++) {
	    eb_ptr = unknown_eb_ptr[i];
	    for(j=0;j<eb_ptr->basis;j++) {
		make_fem_funcs_co_bound(fp,eb_ptr->element_name,
					*(eb_ptr-> basis_no + j) );
	    }
	}
    }
    /* 既知FEM変数 */
    for(i=0;i<fem_vars;i++) {
	eb_ptr = fem_eb_ptr[i];
	for(j=0;j<eb_ptr->basis;j++) {
	    make_fem_funcs_co_bound(fp,eb_ptr->element_name,
				    *(eb_ptr-> basis_no + j) );
	}
    }    

    /*=================================================*/
    /* [LISP-SEND] 形状関数リスト *shape-funcs* の設定 */
    /*=================================================*/
    LISP_SEND(fp,"(setq *shape-funcs* '(");
    for(j=0;j<shape_eb_ptr->basis;j++) {
	LISP_SEND_sd(fp," %s_%d",shape_eb_ptr->element_name,
		     *(shape_eb_ptr->basis_no+j)+1);
    }
    LISP_SEND(fp,") )\n");

    /*===============================*/
    /* [LISP-SEND] 形状関数へのbound */
    /*===============================*/
    for(j=0;j<shape_eb_ptr->basis;j++) {
	make_fem_funcs_co_bound(fp,shape_eb_ptr->element_name,
				*(shape_eb_ptr-> basis_no + j) );
    }

    /*===============================*/
    /* [LISP-SEND] *solve-no*の設定  */
    /*===============================*/
    LISP_SEND_d(fp,"(setq *solve-no* %d)\n",solve_no);
    

    /*===============================*/
    /* [LISP-SEND] *elem-no*の設定   */
    /* ncond番号の１００倍           */
    /*===============================*/
    LISP_SEND_d(fp,"(setq *elem-no* %d)\n",100*ncond_no);

    /*=================================*/
    /* [LISP-SEND] *integral-no*の設定 */
    /*            1に固定              */
    /*=================================*/
    LISP_SEND(fp,"(setq *integral-no* 1)\n");

    /*=================================*/
    /* [LISP-SEND] *quad-method*の設定 */
    /*=================================*/
    LISP_SEND(fp,"(setq *quad-method* 'boundary)\n");

    /*=================================*/
    /* [LISP-SEND] *fem-weak-eq*の設定 */
    /*=================================*/
    eq_ptrptr    = solve_element_ptr -> eq_data;
    LISP_SEND(fp,"(setq *fem-weak-eq* '(");
    for(i=0;i<equations;i++) {
	if(i!=0) LISP_SEND(fp,"                      ");
	
	/* 連立の各方程式について一つのリストに書く */
	eq_ptr   = *(eq_ptrptr + i);
	bd_terms = eq_ptr ->boundary_terms;
	bd_expr_ptrptr = eq_ptr -> bd_term;

	switch(bd_terms) {
	  case 0:                    /* 境界項が無い */
	    LISP_SEND(fp," 0 ");
	    break;
	
	  case 1:
	    bd_expr_ptr = *(bd_expr_ptrptr);
	    LISP_SEND_s(fp," %s ",bd_expr_ptr->expr);
	    break;
	    
	  default:
	    LISP_SEND(fp,"(+ ");
	    for(j=0;j<bd_terms;j++) {
		bd_expr_ptr = *(bd_expr_ptrptr + j);
		LISP_SEND_s(fp," %s ",bd_expr_ptr->expr);
	    }
	    LISP_SEND(fp," )");
	    break;
	}
    }
    LISP_SEND(fp,") )\n");        /* '( と (setq の終わり */

    /*=================================*/
    /* [LISP-SEND] 境界仮変数の変換    */
    /* replace-string関数の設定        */
    /*=================================*/
    name_ptr    = n_ptr->left_var;
    bd_expr_ptrptr = n_ptr->expr_right;
    for(i=0;i<n_ptr->args;i++) {
	bd_expr_ptr = *(bd_expr_ptrptr + i);
	LISP_SEND(fp,"(setq *fem-weak-eq*\n");
	LISP_SEND_s(fp," (replace-string *fem-weak-eq* '%s\n",*(name_ptr+i));
	LISP_SEND_s(fp,"                               '%s\n",bd_expr_ptr->expr);
	LISP_SEND(fp," ))\n");
    }

    /*=================================*/
    /* [LISP-SEND] *quad-vars*の設定   */
    /* 解析的積分法は現在行わない仕様  */
    /*=================================*/
    LISP_SEND(fp,"(setq *quad-vars* nil)\n");

    /*=================================*/
    /* [LISP-SEND] *eval-smbl*の設定   */
    /* 解析的積分法は現在行わない仕様  */
    /*=================================*/
    LISP_SEND(fp,"(setq *eval-smbl* nil)\n");

    /*=================================*/
    /* [LISP-SEND] *dimension*の設定   */
    /*=================================*/
    LISP_SEND(fp,"(setq *dimension* 1)\n");

    /*=================================*/
    /* [LISP-SEND] 実行文の設定        */
    /*=================================*/
    LISP_SEND(fp,"(make-linear-weak)\n");    
    LISP_SEND(fp,"(make-num-integral)\n");    
    LISP_SEND(fp,"(make-num-int-matrix-dat)\n");    


    return; 
}
