/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   set_boundary_no.c
 *      Date:   1993/12/08
 *   
 *   Purpose:   境界節点集合番号            for Dirichet境界条件
 *              境界要素節点集合番号の番号を付加する
 *              
 *              境界要素  要素節点集合番号  for Neumann境界条件
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "solve_comp_funcs.h"



void set_boundary_no()
{
    int i,j,k;
    int solves;
    int dconds,nconds;


    Solve *solve_ptr;
    DirichletData **d_ptrptr,*d_ptr;
    NeumannData   **n_ptrptr,*n_ptr;


    /* 先ずは、Dirichlet境界から */

    solves = how_many_solves();
    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr(i);
	
	dconds   = solve_ptr -> d_conditions;
	d_ptrptr = solve_ptr -> d_dat;

	for(j=0;j<dconds;j++) {
	    d_ptr      = *(d_ptrptr + j);

	    
	    /* 複数の境界が指定されている場合でもboundary_dataで
	       まとめる 

	       節点集合データ番号は ../main 内の関数で割り当て
	     */
	    d_ptr ->b_nodeset = get_new_nodesetno(); 
	}
    }

    /* ここから、ノイマン境界条件に対する境界要素節点番号付加 */
    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr(i);
	
	nconds   = solve_ptr-> n_conditions;
	n_ptrptr = solve_ptr-> n_dat;

	for(j=0;j<nconds;j++) {
	    n_ptr  = *(n_ptrptr + j);

	    /* 複数の境界が指定されている場合でもboundary_dataで
	       まとめる 

	       節点集合データ番号は ../main 内の関数で割り当て
	     */
	    n_ptr ->belem_no = get_new_edatno(); 

	}
    }
    return;
}



