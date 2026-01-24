/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_var.c
 *      Date:   1993/07/10
 *   
 *   Purpose:   solve文中に現れる変数に関するデータcheck
 *              (宣言されているかどうか)
 *              及び、既知変数リストの作成 と 未知変数部分をsolve_ptrの配列
 *              ~~~~~~~~~~~~~~~~~~~~~~~~~~    割り当て
 *
 *              非線形問題に於いて初期値を割り当てた場合の処理
 *
 * 多分これはうそ////////////  【注意！！！】ここでは領域積分項に対してのみ
 *                           /////////////// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *              また、この関数内で、要素番号を割り当てる
 *              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *              domain宣言のチェック、およびdomainが１個で、
 *              SolveElement内のdomainポインタがNULLならば
 *              その唯一のdomainを割り振る。
 *              
 *              
 *              境界積分項に含まれる仮変数と思われるリストを作成する
 *              これは、次のsolve_chk_bd_var()での検査等に用いる
 *              
 *              
 *              
 * Functions:   int how_many_elemeng_groups()
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"

/* modernize 2026/01/21 */
char *get_domain_name_by_no(int);  
char *get_domain_ptr_by_name(char *);

static element_groups;  /* 要素番号 */

solve_chk_var()
{
    int i,j,k,l,m;
    int solves;
    int solve_elements;
    int equations;
    int identifiers;

    int eq_terms;           
    int bd_terms;

    int unknowns;     

    int domains;

    Solve *solve_ptr;
    SolveElement *solve_element_ptr;
    Equation *equation_ptr;
    Expression *expr_ptr;
    char **identifier;

    /* Neumann条件仮変数記録用 */
    int   neumann_args;
    char *neumann_arg_name[MAX_NEUMANN_ARGS];

    /* 既知変数記録用 */
    int fem_knowns;
    int ewise_knowns;
    int scalar_knowns;

    char **fem_known_name;
    char **ewise_known_name;
    char **scalar_known_name;

    char **nbc_arg_name;

    char *name;

    domains = how_many_domains();   /* domain数の取得 */
    if(domains == 0 ) {
	if(english_mesg) {
	    SystemError("No domain definition.");
	}
	else {
	    SystemError("domain宣言がありません");
	}
    }

    solves = how_many_solves();
    element_groups = 0;

    for(i=0;i<solves;i++) {
	
	solve_ptr = get_nth_solve_ptr(i);

	/* solve文番号の付加 番号は1,2,3,...*/
	solve_ptr -> solve_no = i + 1;

	/* 未知変数が正しいfem変数であるかどうか調べる */
	/* ついでに、未知変数リストに重複定義が無いかもuniqを使って調べる */
	unknowns = solve_ptr->unknowns;
	identifier = solve_ptr->unknown_name;

	uniq_list_init();

	for(j=0;j<unknowns;j++) {

	    put_uniq_name(*(identifier+j));   /* uniqルーチンに登録 */

	    if(get_var_kind(*(identifier+j)) != FEM) {

		if(english_mesg) {
		    SystemError_yy_s("Specified unkown variable in solve block %s is not FEM variable.",*(identifier+j),solve_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("solve文で指定された未知変数%sはfem変数ではありません。\n",*(identifier+j),solve_ptr->yylineno);
		}

	    }
	}
	
	if(how_many_uniq_items() != unknowns) {

	    if(english_mesg) {
		SystemError_yy("There is a duplicated unknown term in solve block.",solve_ptr->yylineno);
	    }
	    else {
		SystemError_yy("solve文の未知変数定義に重複があります。\n",
			       solve_ptr->yylineno);
	    }
	}

	solve_elements = solve_ptr->solve_elements;

	/* 未知変数の検査は各SolveElement単位となる 
	   ここでは領域積分項のみを扱う！！！！      */

	for(j=0;j<solve_elements;j++) {

	    solve_element_ptr = *(solve_ptr->solve_elem_dat + j);

	    /*====================*/
	    /* domainに関する処理 */
	    /*====================*/

	    /* domainが唯一の場合 */
	    if(solve_element_ptr->domain_name == NULL &&
	       domains == 1                              ){
		solve_element_ptr->domain_name = 
		  (char *)get_domain_name_by_no( 0 );
	    }

	    if(solve_element_ptr->domain_name == NULL &&
	       domains > 1 ) {

		if(english_mesg) {
		    SystemError_yy("There is an element group with domain not defined.",solve_ptr->yylineno);
		}
		else {
		    SystemError_yy("計算領域が指定されていない要素グループがあります\n",solve_ptr->yylineno);
		}

	    }

	    else {
		if(get_domain_ptr_by_name( solve_element_ptr->domain_name)==NULL){
		    
		    if(english_mesg) {
			SystemError_yy_s("domain %s used in solve block is not defined.",solve_element_ptr->domain_name,solve_element_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("solve文で指定されているdomain %sは宣言されていません。\n",solve_element_ptr->domain_name,solve_element_ptr->yylineno);
		    }

		}
	    }
	
	    /* 領域積分項に対して */

	    uniq_list_init();  /* 変数名リスト作成の為の初期化(領域項) */
	    
	    equations = solve_element_ptr->equations;

	    
	    for(k=0;k<equations;k++) {
/*
		printf("equations =%d  (now = %d)\n",equations,k);
*/
		equation_ptr = *(solve_element_ptr->eq_data + k);

		eq_terms = equation_ptr->equation_terms;

		for(l=0;l<eq_terms;l++) {
		    expr_ptr = *(equation_ptr->eq_term + l);

/*		    printf("expr=%s\n",expr_ptr->expr); 
*/
		    identifiers = expr_ptr -> identifiers;
		    identifier  = expr_ptr -> identifier;

		    for(m=0;m<identifiers;m++) {
			put_uniq_name( *(identifier+m) );
		    }
		}
	    }


	    /* 既知変数の検査と登録 */
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
		    if(solve_element_ptr->type != WEAKEQ) {

			if(english_mesg) {
			    SystemError_yy("Test function is appeared in non weak-form equation.",solve_ptr->yylineno);
			}
			else {
			    SystemError_yy("弱形式以外の方程式記述に試験関数シンボル $ が使用されています。\n",solve_ptr->yylineno);
			}
		    }
		    break;

		  case NO:
		    if(english_mesg) {
			SystemError_yy_s("Variable %s is not defined.",name,
					 equation_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("変数%sは宣言されていません。",
					 name,equation_ptr->yylineno);
		    }
		    break;

		  default:
		    if(english_mesg) {
			SystemAbort("INNER ERROR, Oh, my God!!!(solve_chk_var)");
		    }
		    else {
			SystemAbort("おーまいがぁ(既知変数登録ルーチン)\n");
		    }
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

	    solve_element_ptr -> unknowns   = solve_ptr ->unknowns;
	    solve_element_ptr -> unknown_name = solve_ptr -> unknown_name;
	    
	    solve_element_ptr -> fem_knowns = fem_knowns;
	    solve_element_ptr -> fem_known_name  = fem_known_name;

	    solve_element_ptr -> ewise_knowns = ewise_knowns;
	    solve_element_ptr -> ewise_known_name  = ewise_known_name;

	    solve_element_ptr -> scalar_knowns = scalar_knowns;
	    solve_element_ptr -> scalar_known_name  = scalar_known_name;
	    
	    /*========================================*/
	    /* SolveElement内境界積分項に対しての処理 */
	    /*========================================*/

	    
	    neumann_args = 0;  /* 境界積分項に現れる仮変数の数         */
	    uniq_list_init();  /* 変数名リスト作成の為の初期化(境界項) */
	    
	    equations = solve_element_ptr->equations;

	    
	    for(k=0;k<equations;k++) {
/*
		printf("equations =%d  (now = %d)\n",equations,k);
*/
		equation_ptr = *(solve_element_ptr->eq_data + k);

		bd_terms = equation_ptr->boundary_terms;

		for(l=0;l<bd_terms;l++) {
		    expr_ptr = *(equation_ptr->bd_term + l);

/*		    printf("expr=%s\n",expr_ptr->expr); 
*/
		    identifiers = expr_ptr -> identifiers;
		    identifier  = expr_ptr -> identifier;

		    for(m=0;m<identifiers;m++) {
			put_uniq_name( *(identifier+m) );
		    }
		}
	    }


	    /* 既知変数の検査と登録 */
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

		    if(english_mesg) {
			SystemError_yy_s("There is EWISE variable '%s' in boundary integral term.",name,solve_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("境界積分項にewise変数%sが指定されている",
					 name,solve_ptr->yylineno);
		    }


		    break;
		    
		  case DOUBLE:
		  case INT:
		  case CONST:
		    scalar_knowns++;
		    break;

		  case SYSTEM_VAR: /* 空間変数x,y,z */
		    break;

		  case TEST_VAR:   /* 試験関数シンボル $ */
		    if(solve_element_ptr->type != WEAKEQ) {

			if(english_mesg) {
			    SystemError_yy("There is test function term in non weak-form equation.",solve_ptr->yylineno);
			}
			else {
			    SystemError_yy("弱形式以外の方程式記述に試験関数シンボル $ が使用されています。",solve_ptr->yylineno);
			}

		    }
		    break;

		  case NO:
		    /* ここでは、ノイマン仮変数と考える
		       ほんとうにundefinedの変数か否かは、次の
		       solve_chk_bd_varで検査する               */

		    if(neumann_args == MAX_NEUMANN_ARGS) {
			if(english_mesg) {
			    SystemError_yy("There are too many boundary temporary variables.",equation_ptr->yylineno);
			}
			else {
			    SystemError_yy("境界積分項での仮変数または未定義変数が多すぎる",equation_ptr->yylineno);
			}


			break;
		    }
		    neumann_arg_name[neumann_args] = MakeStringCopy(name);
		    neumann_args++;
		    break;

		  default:
		    SystemAbort("おーまいがぁ(既知変数登録ルーチン)\n");
		}
	    }

	    /*======================*/
	    /* 記録用メモリ割り当て */
	    /*                      */
	    /* neumann仮変数はあとで*/
	    /*======================*/
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
		    /* ノイマン条件境界に関する仮変数がここを通る */
		    break;

		  default:
		    SystemAbort("おーまいがぁ(既知変数登録ルーチンarienai)\n");
		}
	    }
	    
	    solve_element_ptr -> bd_fem_knowns = fem_knowns;
	    solve_element_ptr -> bd_fem_known_name  = fem_known_name;

	    solve_element_ptr -> bd_ewise_knowns = ewise_knowns;
	    solve_element_ptr -> bd_ewise_known_name  = ewise_known_name;

	    solve_element_ptr -> bd_scalar_knowns = scalar_knowns;
	    solve_element_ptr -> bd_scalar_known_name  = scalar_known_name;

	    /* 境界積分項にあらわれる仮変数と思われる変数(未定義変数) */
	    solve_element_ptr -> nbc_args = neumann_args;
	    nbc_arg_name = (char **)FEEL_GetMemory(sizeof(char *) *
						   neumann_args);
	    for(l=0;l<neumann_args;l++) {
		*(nbc_arg_name + l) = neumann_arg_name[l];

		/* fprintf(stderr,"ノイマン条件の仮変数と思われる変数名 %s\n",
			*(nbc_arg_name+l));
			
			*/
	    }
	    solve_element_ptr -> nbc_arg_name = nbc_arg_name;

	}
    }

    return;
}
