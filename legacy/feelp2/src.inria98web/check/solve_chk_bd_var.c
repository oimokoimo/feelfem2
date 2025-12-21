/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_bd_var.c
 *      Date:   1993/07/14
 *   
 *  Modified:   1999/04/04   newton_times
 *    
 *   Purpose:   各solve文について、全ての既知、未知変数のリストを作成する。
 *
 *              SolveElement内の領域積分項、境界積分項
 *              境界条件式内のリスト
 *              
 *              ここでは、特に境界項を新たに付け加えると同時に、境界項に
 *              現れる変数が宣言されているかどうかの確認も行う。
 *              また、ディリクレ条件のIDENTIFIERが未知変数かどうかも調べる
 *
 *              ノイマン条件仮変数に関する処理付加(94/01/24)
 *              
 *              ノイマン条件のみに現れるfem既知変数登録(94/08/01)
 *                SolveElementの既知変数項として付加する
 *                    やめやめ ｰ>solve_chk_only_neumann.c でやることにした
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"

solve_chk_bd_var()
{
    int i,j,j2,j3,k;
    int neumann_args;    /* ノイマン条件の仮変数の数 */
    int solves;
    int bdcs;    /* boundary conditions の略 */
    int equations;
    int bd_terms;
    int identifiers;

    int fem_knowns,ewise_knowns,scalar_knowns;
    char **fem_known_name,**ewise_known_name,**scalar_known_name;

    int vars;

    int err_flag;

    int solve_elements;

    Solve *solve_ptr;
    SolveElement *solve_element_ptr;

    DirichletData *dirichlet_ptr;
    NeumannData   *neumann_ptr;

    Expression *eq_ptr;
    Expression *expr_ptr;

    char **identifier;

    char *domain_name;
    char *cp,*name;

    int    nbc_args;          /* 境界積分項内の仮変数 */
    char **nbc_arg_name;
    char *nbc_var_name;

    /*================================*/
    /*すべてのsolve文について走査する */
    /*  solve文毎に、
     *    領域積分項、境界積分項	
     *    境界条件設定式にあらわれる既知変数群を登録する
     *
     *    ノイマン条件仮変数に関しては注意が必要(登録しない)
     *    
     *
     *
     */
    solves = how_many_solves();

    for(i=0;i<solves;i++ ) {
	solve_ptr = get_nth_solve_ptr(i);
	
	uniq_list_init();  /* 各solve文毎に設定 */

	/* 非線形方程式で、初期値設定している場合の処理 */
	for(j=0;j<solve_ptr->initial_settings;j++) {
	    eq_ptr = *(solve_ptr->initial_expr + j);
	    identifier = eq_ptr->identifier;
	    for(k=0;k<eq_ptr->identifiers;k++) {
		put_uniq_name(*(identifier + k) );
	    }
	}
	/* 非線形方程式で、緩和係数指定している場合の処理 */
	eq_ptr = solve_ptr->newton_factor;
	if(eq_ptr != NULL) {
	    identifier = eq_ptr->identifier;
	    for(k=0;k<eq_ptr->identifiers;k++) {
		put_uniq_name(*(identifier + k) );
	    }
	}

	eq_ptr = solve_ptr->newton_times;
	if(eq_ptr != NULL) {
	    identifier = eq_ptr->identifier;
	    for(k=0;k<eq_ptr->identifiers;k++) {
		put_uniq_name(*(identifier + k) );
	    }
	}

	/* 先ずは未知変数unknown_varから */
	vars = solve_ptr -> unknowns;
	identifier = solve_ptr->unknown_name;

	for(j = 0; j< vars;j++) {
	    put_uniq_name( *(identifier+j) );
	}

	
	/* 次に境界項の検査 その１ 境界条件内の諸変数について */

	/*====================*/
	/* ディリクレ境界条件 */
	/*====================*/
	bdcs = solve_ptr ->  d_conditions;

	for(j=0;j<bdcs;j++) {
	    dirichlet_ptr = *(solve_ptr->d_dat + j);

	    /* 一つの境界条件式中には一つのdomainに関する記述しかできない
	     * ようにする (複数domain時要拡張:dbg:)
	     */
	    
	    /*====================================================*/
	    /* ディリクレ条件に指定されている変数のエラーチェック */
	    /*====================================================*/
	    err_flag = YES;
	    for(k=0;k<solve_ptr->unknowns;k++) {
		cp = *(solve_ptr->unknown_name + k);
		if(streq(cp,dirichlet_ptr->var)) {
		    err_flag = NO;
		    break;
		}
	    }

	    if(err_flag == YES) {
		if(english_mesg) {
		    SystemError_yy_s("%s is not unknown fem variable.",
				     dirichlet_ptr->var,
				     dirichlet_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("ディリクレ条件に指定されている変数 %s は未知変数では有りません。\n",dirichlet_ptr->var,dirichlet_ptr->yylineno);
		}
	    }


	    expr_ptr = dirichlet_ptr -> expr;
	    identifiers = expr_ptr->identifiers;
	    identifier  = expr_ptr->identifier;

	    for(k=0;k<identifiers;k++) {

		if(get_var_kind(*(identifier+k)) == NO) {
		    SystemError_yy_s("%s is not defined.(in boundary condition specification)",*(identifier+k),dirichlet_ptr->yylineno);
		}
		else {
		    put_uniq_name( *(identifier+k) );
		}
	    }
	}

	/*------------------------------------------------------*/
	/* ノイマン境界条件                                     */
	/* ノイマン条件の左辺は仮変数、ここでは右辺について登録 */
	/*------------------------------------------------------*/
	bdcs = solve_ptr ->  n_conditions;

	for(j=0;j<bdcs;j++) {
	    neumann_ptr = *(solve_ptr->n_dat + j);  /* ノイマン条件 */

	    neumann_args = neumann_ptr -> args;

	    /*==========================*/
	    /* ノイマン条件仮変数の検査 */
	    /*==========================*/
	    /* 複数domain時要拡張 */
	    /* 境界名からdomain名を得る */
	    /* 一つの境界条件式中には一つのdomainに関する記述しかできない
	     * ようにする (複数domain時要拡張:dbg:)
	     *
	     * 本当は check_only_domain_boundary(boundary,boundaries);
	     * dbg: dbg:
	     */
	    
	    domain_name = "シリマヘンガナ";
	    /* 本当は domain_name = get_domain_name_by_boundary(); */

	    solve_element_ptr = *(solve_ptr -> solve_elem_dat + 0);
	    /* 本当は get_solve_element_ptr_by_solve_domain_name() */

	    nbc_args     = solve_element_ptr -> nbc_args;
	    nbc_arg_name = solve_element_ptr->nbc_arg_name;

	    /* その１ nbc:文での仮変数が境界積分項にあるかどうかの検査 */
	    for(j2 = 0;j2 < neumann_args;j2++) {
		nbc_var_name = *(neumann_ptr -> left_var + j2);
		err_flag = YES;

		for(j3 = 0; j3 < nbc_args;j3++) {
		    if(streq(*(nbc_arg_name+j3) , nbc_var_name)) {
			err_flag = NO;
			break;
		    }
		}
		if(err_flag == YES) { /* 定義されど、境界積分項に対応無し */
		    if(english_mesg) {
			SystemError_yy_s("Boundary value symbol %s doesn't exist in boundary integral term.",nbc_var_name,neumann_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("ノイマン境界仮変数 %sは境界積分項に存在しない",nbc_var_name,neumann_ptr->yylineno);
		    }
		}
	    }
	    
	    /* その２ 境界積分項に出現すれど定義されないもの */
	    for(j2 = 0; j2 < nbc_args;j2++) {
		err_flag = YES;
		nbc_var_name = *(nbc_arg_name + j2);   /* 境界積分項内の変数 */

		
		for(j3 = 0; j3 < neumann_args;j3++) {


		    if(streq(*(neumann_ptr->left_var + j3) , nbc_var_name)) {
			err_flag = NO;
			break;
		    }
		}
		if(err_flag == YES) { /* 境界積分項に出現すれど未定義 */
		    if(english_mesg) {
			SystemError_yy_s("There is no formula for boundary term symbol %s in Neumman condition.",nbc_var_name,neumann_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("ノイマン条件設定において境界積分項変数%sに対する値が未設定",nbc_var_name,neumann_ptr -> yylineno);
		    }
		}
	    }

	    /* 境界積分仮変数の多重定義検査 */
	    for(j2 = 0;j2 < neumann_args; j2++) {
		nbc_var_name = *(neumann_ptr->left_var + j2);
		for(j3 = j2+1; j3 < neumann_args;j3++) {
		    if(streq(nbc_var_name,*(neumann_ptr->left_var + j3))) {
			if(english_mesg) {
			    SystemError_yy_s("Boundary integral term symbol %s is multiply defined.",nbc_var_name,neumann_ptr->yylineno);
			}
			else {
			    SystemError_yy_s("ノイマン境界仮変数 %s は多重定義されている",nbc_var_name,neumann_ptr->yylineno);
			}
		    }
		}
	    }

	    /*==========================*/
	    /* 境界条件式で指定する     */
	    /*==========================*/
	    for(j2=0;j2 < neumann_args; j2++) {

		expr_ptr = *(neumann_ptr -> expr_right + j2);
		identifiers = expr_ptr->identifiers;
		identifier  = expr_ptr->identifier;

		for(k=0;k<identifiers;k++) {

		    if(get_var_kind(*(identifier+k)) == NO) {

			/*==============================================*/
			/* 仮変数はノイマン条件右辺に出現してはいけない */
			/*==============================================*/
			if(english_mesg) {
			    SystemError_yy_s("variable %s is not defined.",
					     *(identifier+k),
					     neumann_ptr->yylineno);
			}
			else {
			    SystemError_yy_s("境界条件で使用されている変数%sは宣言されていない",*(identifier+k),neumann_ptr->yylineno);
			}
		    }
		    else {
			put_uniq_name( *(identifier+k) );
		    }
		}
	    }

	}

	
	/* 各SolveElement内の登録 */
	solve_elements = solve_ptr->solve_elements;

	for(j=0;j<solve_elements;j++) {
	    solve_element_ptr = *(solve_ptr -> solve_elem_dat + j);
	    
	    /* 領域項fem既知変数 */
	    vars = solve_element_ptr->fem_knowns;
	    identifier = solve_element_ptr -> fem_known_name;
	    for(k=0;k<vars;k++) {
		put_uniq_name( *(identifier+k) );
	    }

	    /* 領域項ewise既知変数 */
	    vars = solve_element_ptr->ewise_knowns;
	    identifier = solve_element_ptr -> ewise_known_name;
	    for(k=0;k<vars;k++) {
		put_uniq_name( *(identifier+k) );
	    }

	    /* 領域項scalar既知変数 */
	    vars = solve_element_ptr->scalar_knowns;
	    identifier = solve_element_ptr -> scalar_known_name;
	    for(k=0;k<vars;k++) {
		put_uniq_name( *(identifier+k) );
	    }

	    /*---------------------------------------------*/

	    /* 境界項fem既知変数 */
	    vars = solve_element_ptr->bd_fem_knowns;
	    identifier = solve_element_ptr -> bd_fem_known_name;
	    for(k=0;k<vars;k++) {
		put_uniq_name( *(identifier+k) );
	    }

	    /* 境界項ewise既知変数 */
	    vars = solve_element_ptr->bd_ewise_knowns;
	    identifier = solve_element_ptr -> bd_ewise_known_name;
	    for(k=0;k<vars;k++) {
		put_uniq_name( *(identifier+k) );
	    }

	    /* 境界項scalar既知変数 */
	    vars = solve_element_ptr-> bd_scalar_knowns;
	    identifier = solve_element_ptr -> bd_scalar_known_name;
	    for(k=0;k<vars;k++) {
		put_uniq_name( *(identifier+k) );
	    }
	}



	/*======================*/
	/* Solve構造体への      */
	/* 既知変数の検査と登録 */
	/*======================*/

	fem_knowns = 0;
	ewise_knowns = 0;
	scalar_knowns = 0;

	identifiers = how_many_uniq_items();

	for(k=0;k<identifiers;k++) {
		
	    name = get_nth_uniq_item(k);

	    if(is_member(name,solve_ptr->unknown_name,
			 solve_ptr->unknowns)) continue;
		
	    switch(get_var_kind(name)) {
	      case FEM:
		fem_knowns++;
		break;

	      case EWISE:
		ewise_knowns++;
		break;
		    
	      case DOUBLE:
	      case INT:
	      case CONST:
		scalar_knowns++;
		break;

	      case SYSTEM_VAR: /* 空間変数x,y,z */
		break;

	      case TEST_VAR:   /* 試験関数シンボル $ */
		break;

	      case NO:
		/* solve_chk_varでエラーメッセージを出力しているので
		   ここでは出力しない */
		break;

	      default:
		SystemAbort("おーまいがぁ(既知変数登録ルーチン)\n");
	    }
	}

	/* 記録用メモリ割り当て */

	if(fem_knowns) {
	    fem_known_name = (char **)FEEL_GetMemory(fem_knowns *
						     sizeof(char *));
	}
	else {
	    fem_known_name = NULL;
	}

	if(ewise_knowns) {
	    ewise_known_name = (char **)FEEL_GetMemory(ewise_knowns *
						       sizeof(char *));
	}
	else {
	    ewise_known_name = NULL;
	}

	if(scalar_knowns) {
	    scalar_known_name = (char **)FEEL_GetMemory(scalar_knowns *
							sizeof(char *));
	}
	else {
	    scalar_known_name = NULL;
	}

	
	fem_knowns = 0;         /* これらをポインタに流用 */
	ewise_knowns = 0;       /* 次のforループ終了時には*/
	scalar_knowns = 0;      /* もとに戻る             */

	for(k=0;k<identifiers;k++) {
	    
	    name = get_nth_uniq_item(k);
	    
	    if(is_member(name,solve_ptr->unknown_name,
			 solve_ptr->unknowns)) continue;
	    
	    switch(get_var_kind(name)) {
	      case FEM:
		*(fem_known_name+fem_knowns) = name;
		fem_knowns++;
		break;
		
	      case EWISE:
		*(ewise_known_name+ewise_knowns) = name;
		ewise_knowns++;
		break;
		
	      case DOUBLE:
	      case INT:
	      case CONST:
		*(scalar_known_name+scalar_knowns) = name;
		scalar_knowns++;
		break;
		
	      case SYSTEM_VAR: /* 空間変数x,y,z */
		break;
		
	      case TEST_VAR:   /* 試験関数シンボル $ */
		break;
		
	      case NO:
		/* ここではエラーメッセージは出さない */
		break;
		
	      default:
		SystemAbort("おーまいがぁ(既知変数登録ルーチンarienai)\n");
	    }
	}
	
	solve_ptr -> fem_knowns = fem_knowns;
	solve_ptr -> fem_known_name  = fem_known_name;
	
	solve_ptr -> ewise_knowns = ewise_knowns;
	solve_ptr -> ewise_known_name  = ewise_known_name;
	
	solve_ptr -> scalar_knowns = scalar_knowns;
	solve_ptr -> scalar_known_name  = scalar_known_name;
	
    }
    return;
    
}
