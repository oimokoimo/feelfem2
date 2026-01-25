/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_edge_basis.c
 *      Date:   1994/02/04
 *   
 *   Purpose:   試験関数名から境界が非零のものを抽出
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../element/element.h"
#include "../solve_comp/solve_comp.h"

EdgeBasis *make_edge_basis( basis_name )

     char      *basis_name;  /* 試験関数名 */
{
    int i,j;
    int ptr;
    int etype;

    EdgeBasis *eb_ptr;
    Element   *element_ptr;
    int basis,edge_basis;
    int end_edge_flag;
    int end_edge_no;

    Frac    *s_fr_ptr,fr;
    Frac    *r_fr_ptr;

    double   s;   /* y座標(s座標、η座標) */
    double   r;

    eb_ptr = (EdgeBasis *)FEEL_GetMemory(sizeof(EdgeBasis));
    
    eb_ptr -> element_name = basis_name; /* 代入してあげる */

    element_ptr = get_element_ptr_by_name( basis_name );
    basis      = element_ptr -> basis;
    etype      = element_ptr -> etype;
    s_fr_ptr   = element_ptr ->s_frac;
    r_fr_ptr   = element_ptr ->r_frac;

    if(etype != TRI && etype != RECT) {
	SystemAbort("三角形、四辺形以外はまだ作っていない@make_edge_basis");
    }

    /* 境界上に関するbaseの個数を計算する */
    edge_basis = 0;

    for(i=0;i<basis;i++) {
	fr = *(s_fr_ptr + i);
	s  = (double)(fr.bunsi)/(double)(fr.bunbo);

	if(etype ==  TRI && s ==  0.0) edge_basis++;
	if(etype == RECT && s == -1.0) edge_basis++;
    }

    eb_ptr -> basis = edge_basis;
    /* 領域割り当て */
    eb_ptr -> basis_no = (int *)FEEL_GetMemory(sizeof(int)*edge_basis);
    
    ptr = 0;
    end_edge_flag = NO;   /* 端点に規定があるかどうか(順番が異なる為) */
    for(i=0;i<basis;i++) {
	fr = *(s_fr_ptr + i);
	s  = (double)(fr.bunsi)/(double)(fr.bunbo);

	fr = *(r_fr_ptr + i);
	r  = (double)(fr.bunsi)/(double)(fr.bunbo);

	if(etype ==  TRI && s ==  0.0) {
	    if(r ==  1.0) {
		end_edge_flag = YES;  /* (0,1)に基底あり */
		end_edge_no   = i;
		continue;
	    }
	    *(eb_ptr->basis_no + ptr) = i;  /* 0から始まる */
	    ptr++;
	}
	    
	if(etype == RECT && s == -1.0) {
	    if(r ==  1.0) {
		end_edge_flag = YES;  /* (0,1)に基底あり */
		end_edge_no   = i;
		continue;
	    }
	    *(eb_ptr->basis_no + ptr) = i;  /* 0から始まる */
	    ptr++;
	}
    }
    if(end_edge_flag == YES) {
	*(eb_ptr->basis_no + ptr) = end_edge_no;
	ptr++;
    }

    if(ptr != edge_basis) {
	SystemAbort("アルゴリズム上不整合自体発生@make_edge_basis");
    }

    return(eb_ptr);
}
