/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   mesh_info_for_meshbook.c
 *      Date:   1993/09/10
 *   
 *   Purpose:   中間節点情報を抜き出す
 *              
 *              現在は、メッシュ生成の都合上、要素境界の節点配置は
 *              対称であることを要請する。ただしこのチェックは行わ
 *              ない。
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../element/element.h"
#include "mesh_exec.h"

void mesh_info_for_meshbook_TRI( ElemDat *edat_ptr , MidPoint2D *mesh_info_ptr );
void mesh_info_for_meshbook_RECT(ElemDat *edat_ptr , MidPoint2D *mesh_info_ptr );

/* Frac は 分母、分子の順番  注意！   */
Frac frac_p0 = { 1, 0};    /* 0       */  
Frac frac_m1 = { 1,-1};    /* minus 1 */
Frac frac_p1 = { 1, 1};    /* plus  1 */

void mid_info_for_meshbook( edat_ptr , mesh_info_ptr )
     ElemDat *edat_ptr;
     MidPoint2D *mesh_info_ptr;
{
    int etype;

    etype = edat_ptr -> etype;
    switch(etype) {
      case TRI:
	mesh_info_for_meshbook_TRI( edat_ptr , mesh_info_ptr );
	break;

      case RECT:
	mesh_info_for_meshbook_RECT( edat_ptr , mesh_info_ptr );
	break;

      default:
	SystemAbort("現在三角形、および四角形以外のメッシュは指定できない");
    }

    return;
}


/* 三角形 中間節点情報抜き出し関数 */
void mesh_info_for_meshbook_TRI( edat_ptr , mesh_info_ptr )
     ElemDat *edat_ptr;
     MidPoint2D *mesh_info_ptr;
{
    int i;
    int nodes;
    Node *node_ptr;
    Frac r,s;

    double node_val;

    int no_1,no_2,no_3,inner;   /* 各辺上の節点のカウンター */
    
    no_1 = no_2 = no_3 = inner =  0;  /* 初期化 */

    nodes = edat_ptr -> nodes;

    if(nodes < 3) {
	SystemAbort("Error mesh_info_for_meshbook_TRI(too few nodes)");
    }

    /* まず、最初の３点が頂点であることの確認 */

    /* 【第１の点】 */
    node_ptr = *(edat_ptr -> node_ptrptr);
    r = node_ptr -> r;
    s = node_ptr -> s;


    if(frac_neq(r , frac_p0) || frac_neq( s , frac_p0))  {
	SystemAbort("Error mesh_info_for_meshbook_TRI No.1");
    }

    /* 【第２の点】 */
    node_ptr = *(edat_ptr -> node_ptrptr + 1);
    r = node_ptr -> r;
    s = node_ptr -> s;
    if(frac_neq(r , frac_p1) || frac_neq( s , frac_p0))  {
	SystemAbort("Error mesh_info_for_meshbook_TRI No.2");
    }

    /* 【第３の点】 */
    node_ptr = *(edat_ptr -> node_ptrptr + 2);
    r = node_ptr -> r;
    s = node_ptr -> s;
    if(frac_neq(r , frac_p0) || frac_neq( s , frac_p1))  {
	SystemAbort("Error mesh_info_for_meshbook_TRI No.3");
    }

    /* 中間節点が指定されていない場合 */
    if(nodes == 3) {
	mesh_info_ptr -> edge_points = 0;
	mesh_info_ptr -> inner_points = 0;
	return;
    }

    /* 中間節点の走査 */
    /* 中間節点の順番は正規順に確定していること(内部節点評価の為) */
	
    /* 境界上点の評価 */
    for(i=3;i<nodes;i++) {
	node_ptr = *(edat_ptr -> node_ptrptr + i );
	r = node_ptr -> r;
	s = node_ptr -> s;
	
	node_val = tri_eval_frac(r,s);
	
	if(node_val > 3000.0) { /* 第１辺上 */
	    mesh_info_ptr->edge[no_1] =
	      (double)r.bunsi/(double)r.bunbo ;
	    mesh_info_ptr->edge_val[no_1] = node_val;
	    
	    if(no_1 > 0) {
		if(mesh_info_ptr->edge_val[no_1] > 
		   mesh_info_ptr->edge_val[no_1 - 1] ) {
		    SystemAbort("edge order ERR(mid_info_for_meshbook(TRI))");
		}
	    }
	    no_1++;
	}
	else if(node_val > 2000.0) { /* 第２辺 */
	    no_2++;
	}
	else if(node_val > 1000.0) { /* 第３辺 */
	    no_3++;
	}
	else {                       /* 【内部節点】*/
	    mesh_info_ptr->mid_x[inner] = (double)r.bunsi/(double)r.bunbo; 
	    mesh_info_ptr->mid_y[inner] = (double)s.bunsi/(double)s.bunbo; 
	    mesh_info_ptr->mid_val[inner] = node_val;

	    inner++;
	}
    }

    if(no_1 != no_2) {
	SystemWarning("第２辺の節点が第１辺と異なっています\n");
    }

    if(no_1 != no_3) {
	SystemWarning("第３辺の節点が第１辺と異なっています\n");
    }

    mesh_info_ptr->edge_points = no_1;
    mesh_info_ptr->inner_points = inner;

    return;
}


/* 四角形 中間節点情報抜き出し関数 */
void mesh_info_for_meshbook_RECT( edat_ptr , mesh_info_ptr )
     ElemDat *edat_ptr;
     MidPoint2D *mesh_info_ptr;
{
    int i;
    int nodes;
    Node *node_ptr;
    Frac r,s;
    double node_val;

    int no_1,no_2,no_3,no_4,inner; /* 各エッジのカウンタ */

    no_1 = no_2 = no_3 = no_4 = 0;
    inner = 0;

    nodes = edat_ptr -> nodes;
    if(nodes < 4) {              
	SystemAbort("Error mesh_info_for_meshbook_RECT(too few nodes)");
    }

    /* まず、最初の４点が頂点であることの確認 */

    /* 【第１の点】 */
    node_ptr = *(edat_ptr -> node_ptrptr);
    r = node_ptr -> r;
    s = node_ptr -> s;
    if(frac_neq(r , frac_m1) || frac_neq( s , frac_m1))  {
	SystemAbort("Error mesh_info_for_meshbook_RECT No.1");
    }

    /* 【第２の点】 */
    node_ptr = *(edat_ptr -> node_ptrptr + 1);
    r = node_ptr -> r;
    s = node_ptr -> s;
    if(frac_neq(r , frac_p1) || frac_neq( s , frac_m1))  {
	SystemAbort("Error mesh_info_for_meshbook_RECT No.2");
    }

    /* 【第３の点】 */
    node_ptr = *(edat_ptr -> node_ptrptr + 2);
    r = node_ptr -> r;
    s = node_ptr -> s;
    if(frac_neq(r , frac_p1) || frac_neq( s , frac_p1))  {
	SystemAbort("Error mesh_info_for_meshbook_RECT No.3");
    }

    /* 【第４の点】 */
    node_ptr = *(edat_ptr -> node_ptrptr + 3);
    r = node_ptr -> r;
    s = node_ptr -> s;
    if(frac_neq(r , frac_m1) || frac_neq( s , frac_p1))  {
	SystemAbort("Error mesh_info_for_meshbook_RECT No.4");
    }

    /* 中間節点が指定されていない場合 */
    if(nodes == 4) {                                 /* 節点が頂点のみ */
	mesh_info_ptr->edge_points = 0;
	mesh_info_ptr->inner_points = 0;
	return;
    }

    /* 中間節点を見つける */
    /* 中間節点の順番は正規順に確定していること(内部節点評価の為) */
    
    /* まず、境界辺上の中間節点を探す */
    for(i=4;i<nodes;i++) {
	
	node_ptr = *(edat_ptr -> node_ptrptr + i);
	r = node_ptr -> r ;
	s = node_ptr -> s ;

	node_val = rect_eval_frac(r,s);

/* dbg:	prt_frac_image_2d(r,s);              */
/* dbg:	DBGWRT("node_val = %lf\n",node_val); */
	
	if(node_val > 4000.0) {      /* 【第１辺】 */
	    mesh_info_ptr->edge[no_1] = 
	      ((double)r.bunsi/(double)r.bunbo + 1.0 ) / 2.0;
	    mesh_info_ptr->edge_val[no_1] = node_val;


	    if(no_1 > 0) {
		if(mesh_info_ptr->edge_val[no_1] > 
		   mesh_info_ptr->edge_val[no_1 - 1]) {
		    SystemAbort("edge order ERR(mid_info_for_meshbook(RECT))");
		}
	    }
	    no_1++;
	}
	else if(node_val > 3000.0) { /* 【第２辺】 */
	    no_2++;
	}
	else if(node_val > 2000.0) { /* 【第３辺】 */
	    no_3++;
	}
	else if(node_val > 1000.0) { /* 【第４辺】 */
	    no_4++;
	}
	else {                       /* 【内部節点】*/
	    mesh_info_ptr->mid_x[inner] = (double)r.bunsi/(double)r.bunbo; 
	    mesh_info_ptr->mid_y[inner] = (double)s.bunsi/(double)s.bunbo; 
	    mesh_info_ptr->mid_val[inner] = node_val;

	    inner++;
	}
    }

    if(no_1 != no_2) {
	SystemWarning("第２辺の節点が第１辺と異なっています\n");
    }

    if(no_1 != no_3) {
	SystemWarning("第３辺の節点が第１辺と異なっています\n");
    }

    if(no_1 != no_4) {
	SystemWarning("第４辺の節点が第１辺と異なっています\n");
    }

    mesh_info_ptr->edge_points = no_1;
    mesh_info_ptr->inner_points = inner;

    return;
}
