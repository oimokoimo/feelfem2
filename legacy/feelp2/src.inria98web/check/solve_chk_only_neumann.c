/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_only_neumann.c
 *      Date:   1994/08/01,02
 *   
 *   Purpose:   ノイマン条件設定式(nbc: の右辺)にのみ現れる既知fem変数の登録
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"

void solve_chk_only_neumann()
{
    int i,j,k,l,j2;
    int stores;

    int solves;
    int solve_elements;
    int nconds;
    int neumann_args;

    Solve *solve_ptr;
    SolveElement *solve_element_ptr;
    NeumannData *neumann_ptr;
    Expression *expr_ptr;
    int identifiers;
    char **identifier;

    char *var_name;
    int   only_names;
    int   find_flag;

    int knowns,unknowns;
    char **known_name_ptr;
    char **unknown_name_ptr;

    char *name_ptr_buf[MAX_FEM_TYPES];
    
    
    solves = how_many_solves();
    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr(i);
	nconds = solve_ptr -> n_conditions;
	
	/* まず、ノイマン条件式右辺に現れる既知fem変数の登録 */
	uniq_list_init();

	for(j=0;j<nconds;j++) {
	    neumann_ptr = *(solve_ptr->n_dat + j);
	    neumann_args = neumann_ptr ->args;

	    for(k=0;k<neumann_args;k++) {
		expr_ptr = *(neumann_ptr -> expr_right + k);
		identifiers = expr_ptr   -> identifiers;
		identifier  = expr_ptr   -> identifier;
		
		for(l=0;l<identifiers;l++) {

		    if(get_var_kind(*(identifier+l)) != FEM) {
			continue;
		    }
		    
		    put_uniq_name( *(identifier+l) );
		}
	    }
	}

	stores = how_many_uniq_items();

	/* 実際はSolveElementは一つだけだが、将来の拡張を考慮して
	 * SolveElement毎に代入措置をとる。これは、ノイマン条件を
	 * 課す境界条件上の節点も、対応するSolveElement節点として
	 * 生成する必要があるためである。  ちゃんちゃん。
	 * だから、指定のノイマン条件が課されている辺がどの
	 * SolveElementに含まれているかを判定する必要がある
	 * 今は、上に見るように、全部のNeumannDataを一色体にしている
	 * ので、実は、SolveElement毎にやるのは無意味なんだけど… ぶつぶつ
	 */
	solve_elements  = solve_ptr -> solve_elements;

	for(j2=0;j2<solve_elements;j2++) {
	    solve_element_ptr = *(solve_ptr -> solve_elem_dat + j2);
	    
	    only_names = 0;
	    
	    unknowns = solve_element_ptr -> unknowns;
	    knowns   = solve_element_ptr -> fem_knowns;
	    unknown_name_ptr = solve_element_ptr -> unknown_name;
	    known_name_ptr   = solve_element_ptr -> fem_known_name;
	    
	    for(j=0;j<stores;j++) {
		var_name  = get_nth_uniq_item(j);
		find_flag = NO;
		
		for(k=0;k<unknowns;k++) {
		    if(streq(var_name,*(unknown_name_ptr+k))) {
			find_flag = YES;
			break;
		    }
		}
		
		for(k=0;k<knowns;k++) {
		    if(streq(var_name,*(known_name_ptr+k))) {
			find_flag = YES;
			break;
		    }
		}
		if(find_flag == NO) {
		    name_ptr_buf[only_names] = MakeStringCopy(var_name);
		    only_names++;
		}
	    }
	    
	    /* SolveElement構造体内にノイマンデータのみの変数情報を登録 */
	    solve_element_ptr -> ndata_fem_knowns = only_names;
	    if(only_names) {
		solve_element_ptr -> ndata_fem_name = (char **)
		  FEEL_GetMemory(sizeof(char *) * only_names);
	    }
	    else {
		solve_element_ptr -> ndata_fem_name = NULL;
	    }
	    for(j=0;j<only_names;j++) {
		*(solve_element_ptr -> ndata_fem_name + j) = name_ptr_buf[j];

/*		fprintf(stderr,"%d  ndata_only name = %s\n",j,name_ptr_buf[j]); */
	    }

	} /* solve_elements のループ */

    }  /* solves のループ */

    return;
}	    

	    
