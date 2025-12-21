/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_boundary_nset_bamg.c
 *      Date:   1997/07/24
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../../feel_def/feel_def.h"
#include "edat.h"

static int  point_sets;
static int *point_buf[MAX_LINES];
static int *iedp_buf[MAX_LINES];
static int  points_buf[MAX_LINES];
static int  corner_points;
static char *corner_name[MAX_LINES][2];

push_boundary_nset_reset_bamg()
{
    point_sets    = 0;
    corner_points = 0;
    return;
}

push_boundary_nset_point_bamg(var_name,name,iedp)
     char *var_name;
     char *name;
     int   iedp;
{
    int  i;
    int *iptr;
    char *malloc();

    for(i=0;i<corner_points;i++) {
      if(streq(var_name,corner_name[i][0]) && streq(name,corner_name[i][1])) {
	fprintf(stderr,"Ignore the dirichlet point(Duplicate)\n");
	return;
      }
    }

    if(point_sets == MAX_LINES) {
	fprintf(stderr,"Too many dirichlet conditions(Some points ignored)\n");
	return;
    }

    iptr = (int *)malloc( sizeof(int) ) ;
    *iptr = get_node_no_by_name_bamg( name );

    point_buf[point_sets] = iptr;
    points_buf[point_sets] = 1;

    iptr = (int *)malloc( sizeof(int) ) ;
    *iptr = iedp;
    iedp_buf[point_sets] = iptr;
    
    point_sets++;

    return;
}


void push_boundary_nset_line_bamg(var_name,from,to,use_flag,eq_plus,
			     unit_points)
     char *var_name;        
     char *from;            
     char *to;              
     int   use_flag[];      
     int   eq_plus[];       
     int   unit_points;     
{
    int i,j;
    int flag;
    int reverse_flag;                   
    int from_skip_flag,to_skip_flag;    

    int tmp;

    int dpoints;                        
    int dpoints_per_unit;               
    int all_points;                     
    int units;
    
    char *swap_cha;
    int   swap_int;

    int *iptr_point;
    int *iptr_iedp ;
    int *iptr_node;

    char *malloc();

    Boundary2Dbamg *b2d_ptr,*get_b2d_ptr_by_both_ends_bamg();

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
    
    /* BAMG: store corner points here. */
    corner_name[corner_points][0] = var_name;
    corner_name[corner_points][1] = from;
    corner_points++;
    corner_name[corner_points][0] = var_name;
    corner_name[corner_points][1] = to;
    corner_points++;


    b2d_ptr = get_b2d_ptr_by_both_ends_bamg( from ,to );


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
      fprintf(stderr,"Boundary2dとunit_pointsのデータ整合性がとれていない");
      exit(1);
    }

    dpoints = (all_points - 1 )/unit_points * dpoints_per_unit;

    if(to_skip_flag == NO) {
	dpoints++;
    }
    if(from_skip_flag == YES) {
	dpoints--;
    }

    iptr_point = (int *)malloc(sizeof(int) * dpoints);
    iptr_iedp  = (int *)malloc(sizeof(int) * dpoints);
    iptr_node  = b2d_ptr -> node_no;
    tmp        = 0;

    units = (all_points - 1) /unit_points;

    point_buf[point_sets] = iptr_point;
    iedp_buf[point_sets]  = iptr_iedp;

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
	fprintf(stderr,"書き出した点数に矛盾有(make_boundary_nset_bamg)");
	exit(1);
    }
    points_buf[point_sets] = dpoints;

    point_sets++;
    return;
}


void make_boundary_nset_bamg(fp,node_set_no,edat_ptr)
     FILE *fp;
     int node_set_no;
     FEM_edat *edat_ptr;
{
    int i,j;

    int total_dpoints;
    int points;
    int *iptr_node;
    int *iptr_plus;

    int *corresp;   /* BAMG only */

    char *cp,*make_string_copy();

    corresp = edat_ptr->corresp;

    cp = make_string_copy(KEY_NSET);

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
	    fprintf(fp,"%8d%8d\n",*(corresp+*iptr_node-1),*iptr_plus);
	    iptr_node++;
	    iptr_plus++;
	}
    }

    /* ここでfreeをするが… */

    return;
}

