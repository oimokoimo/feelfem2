/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   push_boundary_nset_bamg.c
 *      Date:   1997/07/14
 *   
 *   Purpose:   Make Dirichlet boundary data for bamg
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"

static int  point_sets;
static int *point_buf[MAX_LINES];
static int *iedp_buf[MAX_LINES];
static int  points_buf[MAX_LINES];

push_boundary_nset_reset_bamg()
{
    point_sets = 0;
    return;
}

push_boundary_nset_point_bamg( fp, var_name, name , iedp,corner_name , corner_points)
     FILE *fp;
     char *var_name;
     char *name;
     int   iedp;
     char *corner_name[][2];
     int   corner_points;
{
    int  i;
    Point *point_ptr;
    int *iptr;

    for(i=0;i<corner_points;i++) {
       if(streq(var_name,corner_name[i][0]) && streq(name,corner_name[i][1])) { 
        /* No warning */
          return;
	}
    }

    if(point_sets == MAX_LINES) {
	SystemWarning("dbc: 辺りのDirichlet節点形状が多すぎる為、一部作成しません");
	return;
    }

    fprintf(fp,"nsetpo %s %s %d\n",var_name,name,iedp);
    return;
}


void push_boundary_nset_line_bamg( fp,var_name, from, to,use_flag,eq_plus,unit_points,
			     corner_name , corner_points                 )
     FILE *fp;
     char *var_name;         /* 設定変数名 */
     char *from;             /* 開始点名称 */
     char *to;               /* 終了点名称 */
     int   use_flag[];       /* 使用するか否かのフラグ配列 */
     int   eq_plus[];        /* iedpの配列                 */
     int   unit_points;      /* one segmentの構成数        */
     char *corner_name[][2]; /* 境界点名称                 */
     int   corner_points;    /* 境界点名称の数             */
{
    int i,j;
    int flag;
    int reverse_flag;                   /* b2d_ptr内のデータの向き      */
    int from_skip_flag,to_skip_flag;    /* 境界点を含むかどうかのフラグ */

    int tmp;

    int dpoints;                        /* NSETとして書き出す点の数 */
    int dpoints_per_unit;               /* UNITあたり書き出す数     */
    int all_points;                     /* Boundary2d内の点の数総数 */
    int units;
    
    int *iptr_point;
    int *iptr_iedp ;
    int *iptr_node;


    fprintf(fp,"nsetline %s %s %s\n",var_name,from,to);
    fprintf(fp,"%d\n",unit_points);
    for(i=0;i<unit_points;i++) { 
      fprintf(fp," %d",eq_plus[i]);
    }
    fprintf(fp,"\n");
    for(i=0;i<unit_points;i++) {
      fprintf(fp," %d",use_flag[i]);
    }
    fprintf(fp,"\n");
   
    return;
}

void store_boundary_nset_bamg(fp,node_set_no)
     FILE *fp;
     int node_set_no;
{
    int i,j;

    fprintf(fp,"end %d\n",node_set_no);
    return;
}

