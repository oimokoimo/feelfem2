/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1993/08/23
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "solve_comp.h"

dbg_show_elem_dat( elem_dat_ptr )
     ElemDat *elem_dat_ptr;
{
    int i,j;
    int nodes,type,etype;
    int dimension;

    Node *node_ptr;
    Frac r,s,t;
    
    printf("ElemDat構造体のデバッグルーチン\n");

    nodes = elem_dat_ptr -> nodes;
    etype = elem_dat_ptr -> etype;
    dimension = etype_no_to_dimension(etype);
    
    printf("要素形状  %s    節点数 %d\n",etype_no_to_name(etype),nodes);

    for(i=0;i<nodes;i++) {
	printf("[%d] ",i+1);

	node_ptr = *(elem_dat_ptr->node_ptrptr + i);

	printf("( %s",frac_image(node_ptr->r));

	if(dimension == 1) {
	    printf(" )\n");
	}
	else {
	    printf(" , %s",frac_image(node_ptr->s));

	    if(dimension == 2) {
		printf(" )\n");
	    }
	    else {
		printf(" , %s )\n",frac_image(node_ptr->t));
	    }
	}
    }

    return;
}
