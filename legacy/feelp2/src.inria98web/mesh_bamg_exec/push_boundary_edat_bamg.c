/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   push_boundary_edat_bamg.c
 *      Date:   1997/07/14
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

static int  line_sets;
static int *line_buf[MAX_LINES];
static int  elems_buf[MAX_LINES];
static int  reverse_buf[MAX_LINES];

void boundary_edat_reset_bamg() {
    line_sets = 0;
    return;
}

void push_boundary_edat_line_bamg(fp,from, to, use_flag, use_points,total_edge_points)
     FILE *fp;
     char *from;       /* 境界の起点名称 */
     char *to  ;       /* 境界の終点名称 */
     int   use_flag[]; /* 使用フラグ配列 */

     int   use_points;          /* 使用する要素の中間節点＋端点    */
     int   total_edge_points;   /* 全メッシュ  の中間節点＋端点 */
{
    int i;
    line_sets++;


    fprintf(fp,"edatline %d %s %s\n",line_sets,from,to);
    fprintf(fp,"%d %d\n",total_edge_points,use_points);
    for(i=0;i<total_edge_points;i++) {
        fprintf(fp," %d",use_flag[i]);
    }
    fprintf(fp,"\n");
    return;
}


void store_boundary_edat_bamg(fp,edatno,np)
     FILE *fp;
     int   edatno;
     int   np;
{
    fprintf(fp,"end %d %d\n",edatno,np);
    return;
}
