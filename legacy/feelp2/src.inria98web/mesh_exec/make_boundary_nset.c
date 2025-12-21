/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_boundary_nset.c
 *      Date:   1993/12/10
 *   
 *   Purpose:   Dirichlet境界条件設定用のNSETプログラムを作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "boundary.h"

static int  point_sets;
static int *point_buf[MAX_LINES];
static int *iedp_buf[MAX_LINES];
static int  points_buf[MAX_LINES];

push_boundary_nset_reset()
{
    point_sets = 0;
    return;
}

push_boundary_nset_point( var_name, name , iedp,corner_name , corner_points)
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
	    SystemWarning("節点でのDirichlet条件は、他の境界との重なりの為無視しました");
	    return;
	}
    }

    if(point_sets == MAX_LINES) {
	SystemWarning("dbc: 辺りのDirichlet節点形状が多すぎる為、一部作成しません");
	return;
    }

    point_ptr = get_point_ptr_by_name( name );

    iptr = (int *)FEEL_GetMemory( sizeof(int) ) ;
    *iptr = point_ptr -> node_no;
    point_buf[point_sets] = iptr;
    points_buf[point_sets] = 1;

    iptr = (int *)FEEL_GetMemory( sizeof(int) ) ;
    *iptr = iedp;
    iedp_buf[point_sets] = iptr;

    
    point_sets++;

    return;
}


void push_boundary_nset_line( var_name, from, to,use_flag,eq_plus,unit_points,
			     corner_name , corner_points                 )
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
    
    char *swap_cha;
    int   swap_int;

    int *iptr_point;
    int *iptr_iedp ;
    int *iptr_node;


    Boundary2D *b2d_ptr;

    from_skip_flag = NO;

    for(i=0;i<corner_points;i++) {
	if(streq(var_name, corner_name[i][0]) && 
	   streq(from , corner_name[i][1]        )) {
	    from_skip_flag = YES;
	    break;
	}
    }

    to_skip_flag = NO;
    for(i=0;i<corner_points;i++) {
	if(streq(var_name, corner_name[i][0]) && 
	   streq(to , corner_name[i][1]          )) {
	    to_skip_flag = YES;
	    break;
	}
    }


/*    fprintf(stderr,"goto get_b2d_ptr ..."); */
    b2d_ptr = get_b2d_ptr_by_both_ends( from ,to );
/*    fprintf(stderr,"done\n"); */

    if(streq(b2d_ptr -> from_name, from)) {
	reverse_flag = NO;
    }
    else {
	reverse_flag = YES;
    }

    /* REVERSEしている時は、from,toをリバースさせる */
    if(reverse_flag == YES) {
	swap_cha = from;
	from     = to;
	to       = swap_cha;

	swap_int = from_skip_flag;
	from_skip_flag = to_skip_flag;
	to_skip_flag   = swap_int;

    }

    dpoints_per_unit = 0;
    for(i=0;i<unit_points;i++) {
	if(use_flag[i]== YES) dpoints_per_unit++;
    }

    all_points = b2d_ptr -> points;
    
    tmp = all_points -1 ;
    tmp = tmp / unit_points;
    tmp = tmp * unit_points + 1;
    if(tmp != all_points) {
	SystemAbort("Boundary2dとunit_pointsのデータ整合性がとれていない");
    }

    dpoints = (all_points - 1 )/unit_points * dpoints_per_unit;

    if(to_skip_flag == NO) {
	dpoints++;
    }
    if(from_skip_flag == YES) {
	dpoints--;
    }

    iptr_point = (int *)FEEL_GetMemory(sizeof(int) * dpoints);
    iptr_iedp  = (int *)FEEL_GetMemory(sizeof(int) * dpoints);
    iptr_node  = b2d_ptr -> node_no;
    tmp        = 0;

    units = (all_points - 1) /unit_points;

    point_buf[point_sets] = iptr_point;
    iedp_buf[point_sets]  = iptr_iedp;

    /* point_setsのインクリメントは、returnの直前で実行 */

    for(i=0;i<units;i++) {
	                  
	for(j=0;j<unit_points;j++) {
	    
	    if(from_skip_flag == YES && i == 0 && j == 0 ) {
		iptr_node++;
		continue;
	    }

	    if(use_flag[j] == YES) {
		*iptr_point = *iptr_node;
		*iptr_iedp  = eq_plus[j];
		iptr_point++;
		iptr_iedp++;
		tmp++;
	    }
	    iptr_node++;
	}
    }

    if(to_skip_flag != YES && use_flag[0] == YES) {
	*iptr_point = *iptr_node;
	*iptr_iedp  = eq_plus[0];       /* 端点はeq_plus[0]! */
	iptr_point++;
	iptr_iedp++;
	tmp++;
    }

    if(tmp != dpoints) {
	fprintf(stderr,"units = %d  dpoints = %d tmp =%d\n",units,dpoints,tmp);
	SystemAbort("書き出した点数に矛盾有(make_boundary_nset)");
    }
    points_buf[point_sets] = dpoints;

    point_sets++;
    return;
}


void make_boundary_nset(fp,node_set_no)
     FILE *fp;
     int node_set_no;
{
    int i,j;

    int total_dpoints;
    int points;
    int *iptr_node;
    int *iptr_plus;

    char *cp;

    cp = MakeStringCopy(KEY_NSET);
    *(cp + strlen(cp) - 1 ) = '\0';

    total_dpoints = 0;
    for(i=0;i<point_sets;i++) {
	total_dpoints = total_dpoints + points_buf[i];
    }

    fprintf(fp,"%s\n",(cp+1) );
    fprintf(fp,"%8d%8d%8d\n",node_set_no,total_dpoints,2);

    for(i=0;i<point_sets;i++) {
	iptr_node = point_buf[i];
	iptr_plus = iedp_buf[i];
	points    = points_buf[i];

	for(j=0;j<points;j++) {
	    fprintf(fp,"%8d%8d\n",*iptr_node,*iptr_plus);
	    iptr_node++;
	    iptr_plus++;
	}
    }

    /* ここでfreeをするが… */

    return;
}

