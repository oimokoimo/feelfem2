/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_midpoints.c
 *      Date:   1994/07/29
 *   
 *   Purpose:   生成メッシュデータの中間節点数を返す
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "boundary.h"
#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"
#include "../element/element.h"
#include "../mesh_exec/mesh_exec.h"

int get_midpoints()
{
    ElemDat *mesh_edat_ptr;
    MidPoint2D  mesh_midpoint;
    int total_edge_points;


    mesh_edat_ptr  = get_nth_domain_elem_dat_ptr( 0 );
    /*====================*/
    /* domainの           */
    /* 中間節点情報を得る */
    /*====================*/
    mid_info_for_meshbook( mesh_edat_ptr , &mesh_midpoint);
/*    total_points      = mesh_edat_ptr -> nodes; */
    total_edge_points = mesh_midpoint.edge_points;
/*    total_inner_points= mesh_midpoint.inner_points; */


    return(total_edge_points);
}


