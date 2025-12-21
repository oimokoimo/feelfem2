/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_dat_make.c
 *      Date:   1993/07/13
 *   
 *   Purpose:   solve構造体から、SolveElementを経て
 *              SolveFORT77,ElemFORT77構造体への変換
 *              solve番号付加
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "solve_comp.h"

solve_dat_make_main()
{
    int i,j,k;
    int solves,domains;
    int max_nodes;                         /* 各solve文内の最大要素内節点数 */
    Solve *solve_ptr;
    SolveElement *solve_element_ptr;
    SolveFORT77 *solve77_ptr;
    ElementFORT77 *elem77_ptr;
    ElementFORT77 **elem77_ptr_ptr;

    int fems,ewises,scalars;
    char **var_name;

    solves = how_many_solves();
    
    /*========================*/
    /*    SolveFORT77作成     */
    /*  要素データ集合の作成  */
    /*========================*/

    for(i=0;i<solves;i++) {

	solve_ptr = get_nth_solve_ptr(i);

	/* SolveFORT77用メモリ取得 */
	solve77_ptr = (SolveFORT77 *)FEEL_GetMemory(sizeof(SolveFORT77));
	solve_ptr -> solve77_ptr = solve77_ptr;

	solve77_ptr -> solve_no = solve_ptr->solve_no;   /* solve文番号定義 */
	solve77_ptr -> elemg    = solve_ptr->solve_elements;

	/*引き数の為のコール文等作成 */
	fems = solve_ptr->unknowns +
	       solve_ptr->fem_knowns;      /* ここをfem変数専門にする */


	var_name = (char **)FEEL_GetMemory(sizeof(char *) * fems);
	solve77_ptr -> fem_vars = fems;
	solve77_ptr -> fem_var_name = var_name;
	
	k = 0;
	for( j=0;j<solve_ptr->unknowns;j++) {
	    *(var_name+k) = *(solve_ptr->unknown_name + j);
	    k++;
	}
	for( j=0;j<solve_ptr->fem_knowns;j++) {
	    *(var_name+k) = *(solve_ptr->fem_known_name+j);
	    k++;
	}

	/* ewise,scalar 変数に関しては、元もとのsolve文での領域を使用 */
	solve77_ptr->ewise_vars = solve_ptr->ewise_knowns;
	solve77_ptr->ewise_var_name = solve_ptr->ewise_known_name;

	solve77_ptr->scalar_vars = solve_ptr->scalar_knowns;
	solve77_ptr->scalar_var_name = solve_ptr->scalar_known_name;

	elem77_ptr_ptr = (ElementFORT77 **)
	  FEEL_GetMemory( (solve_ptr->solve_elements) * 
			 sizeof(ElementFORT77 *));

	solve77_ptr->elem77_ptrptr = elem77_ptr_ptr;

	max_nodes = 0;

	/*==========================*/
	/* 各要素のデータ構造体作成 */
	/*==========================*/
	for(j=0;j<solve_ptr->solve_elements;j++) {
	    elem77_ptr =(ElementFORT77 *)FEEL_GetMemory(sizeof(ElementFORT77));

	    /* 【注意】!!! */
	    /* SolveFORT77内、SolveElement内のポインタと結合(ダブルで結合) */

	    /* SolveFORT77への書き込み */
	    *(elem77_ptr_ptr+j) = elem77_ptr;

	    /* SolveElementへの書き込み */
	    solve_element_ptr = *(solve_ptr->solve_elem_dat+j);
	    solve_element_ptr -> solve_no = solve_ptr -> solve_no;
	    solve_element_ptr -> element_no = j + 1;

	    solve_element_ptr -> elem77_dat = elem77_ptr;


	    elem_dat_make_main( solve_ptr,solve_element_ptr,elem77_ptr);

	    /* 各solve文内最大要素内節点数の計算 */
	    if(max_nodes < elem77_ptr->nodes) max_nodes = elem77_ptr -> nodes;

	}
	solve77_ptr -> max_nodes = max_nodes;  /* 各solve文最大要素内節点数 */

    }

    return;
}

