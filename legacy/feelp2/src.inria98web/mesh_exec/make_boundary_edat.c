/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_boundary_edat.c
 *      Date:   1994/01/28
 *   
 *   Purpose:   ノイマン境界要素節点集合を作る
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "boundary.h"

static int  line_sets;
static int *line_buf[MAX_LINES];
static int  elems_buf[MAX_LINES];
static int  reverse_buf[MAX_LINES];

void boundary_edat_reset() {
    line_sets = 0;
    return;
}

void push_boundary_edat_line(from, to, use_flag, use_points,total_edge_points)
     char *from;       /* 境界の起点名称 */
     char *to  ;       /* 境界の終点名称 */
     int   use_flag[]; /* 使用フラグ配列 */

     int   use_points;          /* 使用する要素の中間節点＋端点    */
     int   total_edge_points;   /* 全メッシュ  の中間節点＋端点 */
{
    int i,j;
    int reverse_flag;
    int belems;

    Boundary2D *b2d_ptr;
    int *store_ptr;
    int *from_ptr;


    b2d_ptr = get_b2d_ptr_by_both_ends( from , to );
    if(streq(b2d_ptr -> from_name, from)) {
	reverse_flag = NO;
    }
    else {
	reverse_flag = YES;
    }
    reverse_buf[line_sets] = reverse_flag;

    belems = (b2d_ptr->points - 1) / total_edge_points;
    
    elems_buf[line_sets] = belems;


    from_ptr  = b2d_ptr -> node_no;
    store_ptr = (int *)FEEL_GetMemory(sizeof(int) * belems *
				      (use_points+1));
    line_buf[line_sets] = store_ptr;

    for(i=0;i<belems;i++) {

	for(j=0;j<total_edge_points;j++) {
	    if(use_flag[j] == YES) {
		*store_ptr = *from_ptr;
		store_ptr++;
	    }
	    from_ptr++;
	}
	*store_ptr = *from_ptr;
	store_ptr++;               /* 端点の分 */

    }


    line_sets++;
    return;
}

void make_boundary_edat(fp,edatno,np)
     FILE *fp;
     int   edatno;
     int   np;
{
    int i,j,k;
    int elems;
    int nodes;
    int *ptr;
    int reverse_flag;

    nodes = np +1;
    elems = 0;
    for(i=0;i<line_sets;i++) {
	elems += elems_buf[i];
    }

    fprintf(fp,"%s\n",KEY_EDAT_REAL);
    fprintf(fp,"%8d%8d%8d\n",edatno,elems,nodes);

    for(i=0;i<line_sets;i++) {
	ptr = line_buf[i];

	reverse_flag = reverse_buf[i];
	if(reverse_flag) {
	    ptr = ptr + (nodes * elems_buf[i] - 1);
	}
	for(j=0;j<elems_buf[i];j++) {
	    for(k=0;k<nodes;k++) {
		fprintf(fp,"%8d",*ptr);
		
		/* 向きをユーザ指定と合わせる */
		if(reverse_flag) {
		    ptr--;
		}
		else {
		    ptr++;
		}
	    }
	    fprintf(fp,"%8d\n",99999);   /* 本当は要素番号を入れたい */
	}

    }

    return;
}

