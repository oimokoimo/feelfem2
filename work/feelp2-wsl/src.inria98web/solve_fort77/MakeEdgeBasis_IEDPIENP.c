/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   MakeEdgeBasis_IEDPIENP.c
 *      Date:   1994/02/07
 *   
 *   Purpose:   EdgeBasis構造体の *iedp,*ienpの設定を行う
 *   Functions: 対応する FEMvarinfo構造体の*iedp,*ienpから引く
 *              未知変数以外にはienpは設定されていないが、機械的に代入
 *              (999が代入されていたりする)
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../mesh_exec/mesh_exec.h"

#include "../mesh_exec/mesh_exec_funcs.h"

void MakeEdgeBasis_IEDPIENP( name , eb_ptr , solve_element_ptr )
     char         *name;
     EdgeBasis    *eb_ptr;
     SolveElement *solve_element_ptr;
{
    int i;
    int etype;
    FEMvarinfo *fem_varinfo_ptr;
    MidPoint2D  elem_midpoint;
    ElementFORT77 *elem77_ptr;
    ElemDat       *edat_ptr;

    int mid_points,inner_points;

    int boundary_nodeno[128];   /* 要素IEDP -> 境界IEDP対応配列 */

    int  basis;
    int *basis_no;
    int *iedp,*ienp;
    
    elem77_ptr      = solve_element_ptr -> elem77_dat;
    edat_ptr        = elem77_ptr        -> elem_dat;
    fem_varinfo_ptr = get_femvarinfo_ptr_by_name( name , solve_element_ptr );
    etype           = solve_element_ptr -> etype;
    
    /* 領域要素節点番号→境界要素節点番号を求める */
    mid_info_for_meshbook( edat_ptr  , &elem_midpoint );

    mid_points   = elem_midpoint.edge_points;
    inner_points = elem_midpoint.inner_points;

    for(i=0;i<128;i++) {
	boundary_nodeno[i] = 999;   /* イニシャライズ */
    }

    boundary_nodeno[0] = 1;   /* 端点 */

    switch( etype ) {
      case TRI:
	boundary_nodeno[1] = 1 + mid_points + 1;
	for(i=0;i<mid_points;i++) {
	    boundary_nodeno[i+3] = i + 2;
	}
	break;

      case RECT:
	boundary_nodeno[1] = 1 + mid_points + 1;
	for(i=0;i<mid_points;i++) {
	    boundary_nodeno[i+4] = i + 2;
	}
	break;

      default:
	SystemAbort("illegal etype @MakeEdgeBasis_IEDPIENP");
    }

    basis    = eb_ptr ->basis;
    basis_no = eb_ptr ->basis_no;
    ienp     = (int *)FEEL_GetMemory(sizeof(int)*basis);
    iedp     = (int *)FEEL_GetMemory(sizeof(int)*basis);    
    
    for(i=0;i<basis;i++) {
	*(ienp + i) = boundary_nodeno[*(fem_varinfo_ptr->ienp +
					*(basis_no + i)) - 1];
	*(iedp + i) = *(fem_varinfo_ptr->iedp + *(basis_no + i));
    }

    eb_ptr -> ienp = ienp;
    eb_ptr -> iedp = iedp;

    return;
}
