/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_boundary_edat_bamg.c
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

static int  line_sets;
static int *line_buf[MAX_LINES];
static int  elems_buf[MAX_LINES];
static int  reverse_buf[MAX_LINES];

void boundary_edat_reset_bamg() {
    line_sets = 0;
    return;
}

void push_boundary_edat_line_bamg(from, to, use_flag, 
				  use_points,total_edge_points)
     char *from;       
     char *to  ;       
     int   use_flag[]; 

     int   use_points;          
     int   total_edge_points;   
{
    int i,j;
    int reverse_flag;
    int belems;

    Boundary2Dbamg *b2d_ptr,*get_b2d_ptr_by_both_ends_bamg();
    int *store_ptr;
    int *from_ptr;

    char *malloc();

   /* 
    fprintf(stderr,"edat check\n");
    fprintf(stderr,"from=%s\n",from);
    fprintf(stderr,"to  =%s\n",to);
    fprintf(stderr,"use_p=%d\n",use_points);
    fprintf(stderr,"tot_p=%d\n",total_edge_points);
*/


    b2d_ptr = get_b2d_ptr_by_both_ends_bamg( from , to );
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
    store_ptr = (int *)malloc(sizeof(int) * belems *
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
	store_ptr++;              

    }


    line_sets++;
    return;
}

void make_boundary_edat_bamg(fp,edatno,np,edat_ptr)
     FILE *fp;
     int   edatno;
     int   np;
     FEM_edat *edat_ptr;
{
    int i,j,k;
    int elems;
    int nodes;
    int *ptr;
    int reverse_flag;

    int *corresp;  /* BAMG ONLY */

    corresp = edat_ptr->corresp;

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
		fprintf(fp,"%8d",*(corresp+*ptr-1));
		
		if(reverse_flag) {
		    ptr--;
		}
		else {
		    ptr++;
		}
	    }
	    fprintf(fp,"%8d\n",99999);  
	}
    }
    return;
}




