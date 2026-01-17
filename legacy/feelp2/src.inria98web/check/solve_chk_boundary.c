/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_boundary.c
 *      Date:   1993/12/03
 *   
 *   Purpose:   境界条件に関する検査
 *   Functions: 
 *              
 *               1 指定した境界名称が定義されているか、矛盾が無いか？
 *              
 *            注意
 *                 Dirichlet条件の詳細検査はsolve_chk_DirichletData()で実行
 *              
 *                 境界節点集合(DCOND)、境界要素番号(NCOND)の付加は、
 *                 set_boundary_no.cで実行
 *                   なぜなら…  この段階で要素番号が確定していない…
 *                                make_edatの後でないと…
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"

void solve_chk_boundary() 
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

	/* 境界条件で指定された項が、境界の名称かの検査 */
	/* まずは、ノイマンデータから */
	for(j=0;j<n_data;j++) {
	    neumann_ptr = *(neumann_ptrptr + j);
	    
	    bd_names = neumann_ptr -> boundaries;
	    bd_name  = neumann_ptr -> b_name;

	    for(k=0;k<bd_names;k++) {
		type = get_mesh_name_type_by_name( *(bd_name + k));

		if(type == 0) {
		    SystemError_s("Boundary name %s is not defined.",
				  *(bd_name+k));
		    continue;
		}

		if(dimension == 1) {
		    if(type != MESH_POINT) {
			SystemError_s("Boundary name %s is not point.",
				    *(bd_name+k));
		    }
		}
		
		if(dimension == 2) {
		    if(type != MESH_LINE && type != MESH_ARC) {
			if(english_mesg) {
			    SystemError_s("Place %s for Neumann boundary is not edge.",*(bd_name+k));
			}
			else {
			    SystemError_s("Neumann条件境界名%sは二次元図形の境界でない",
				      *(bd_name+k));
			}
		    }
		}
		
		if(dimension == 3) {
		    SystemWarning("三次元問題の境界条件検査は行っていない");
		}
	    }
	}


	/* 境界条件で指定された項が、境界の名称かの検査 */
	/* 次にdirichlet条件 */
	for(j=0;j<d_data;j++) {
	    dirichlet_ptr = *(dirichlet_ptrptr + j);
	    
	    bd_names = dirichlet_ptr -> boundaries;
	    bd_name  = dirichlet_ptr -> b_name;

	    for(k=0;k<bd_names;k++) {
		type = get_mesh_name_type_by_name( *(bd_name + k));

		if(type == 0) {
		    SystemError_s("Boundary name  %s is not defined.",
				  *(bd_name+k));
		    continue;
		}

		if(dimension == 1) {
		    if(type != MESH_POINT) {
			SystemError_s("境界名%sが点でない(一次元問題)",
				    *(bd_name+k));
		    }
		}
		
		if(dimension == 2) {
		    if(type != MESH_LINE && type != MESH_ARC && type != MESH_POINT) {
			SystemError_s("Dirichlet condition place %s is not boundary name.",
				      *(bd_name+k));
		    }
		}
		
		if(dimension == 3) {
		    SystemWarning("三次元問題の境界条件検査は行っていない");
		}
	    }
	}
    }

    return;
}

		    
		    
		
		
	
    
