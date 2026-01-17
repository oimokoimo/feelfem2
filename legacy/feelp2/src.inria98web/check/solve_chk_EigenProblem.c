/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_EigenProblem.c
 *      Date:   1995/03/02
 *   
 *   Purpose:   固有値問題に対する検査
 *   Functions: 
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"

void solve_chk_EigenProblem() 
{
    int i,j,k;
    int solves;
    int n_data,d_data;
    int dimension;
    Solve *solve_ptr;
    SolveFORT77 *solve77_ptr;

    int    bd_names;
    char **bd_name;
    int    type;
    
    DirichletData **dirichlet_ptrptr;
    DirichletData  *dirichlet_ptr;
    NeumannData   **neumann_ptrptr;
    NeumannData    *neumann_ptr;

    solves = how_many_solves();

    for(i=0;i<solves;i++) {

	dimension = what_dimension();   /* ここが微妙なところ */
	
	solve_ptr = get_nth_solve_ptr( i );

	n_data = solve_ptr -> n_conditions;
	d_data = solve_ptr -> d_conditions;
	dirichlet_ptrptr = solve_ptr -> d_dat;
	neumann_ptrptr   = solve_ptr -> n_dat;


    }

    return;
}

		    
		    
		
		
	
    
