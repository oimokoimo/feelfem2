/*
 * FEEL system Prototype Version 2
 * 
 * File     get_face_from_region.c
 * Made     1992/08/20
 * Modified 
 * Version  0.0
 *
 * Purpose: Make FACE data from region data.  Every region data must
 *          through this routine.
 */
#include "../mesh_comp/mesh_comp.h"
#include "mesh_interface.h"

static int face_lines = 0;
static FaceLine *face_line[MAX_FACELINES];

get_face_from_region( region )
     Region *region;
{
    int i,j,k;
    char *from,*to;

    double x1,y1,x2,y2;
    
    int EXIST_flag;

    
    for(i=0;i<region->edges;i++) {
	

	for(j=0;j<region->points[i];j++) {


	    EXIST_flag = NO;
	    from = region->compos[i][j];
	    if(j != region->points[i]-1) 
	      to = region->compos[i][j+1];
	    else
	      to = region->compos[i][0];
	    
	    for(k=0;k<face_lines;k++) {
		
		if(streq(from,face_line[k]->from) &&
		   streq(  to,face_line[k]->  to)) {
		    char buf[256];
		    sprintf(buf,"Region Face ERROR %s [%s-%s]"
			    ,region->name,from,to);
		    SystemError(buf);
		    EXIST_flag = YES;
		    break;
		}

		if(streq(from,face_line[k]->  to) &&
		   streq(  to,face_line[k]->from)) {

		       if(face_line[k]->regions != 1) {
			   char buf[256];
			   sprintf(buf,"Region Face ERROR %s [%s-%s]"
				   ,region->name,from,to);
			   SystemError(buf);
			   EXIST_flag = YES;
			   break;
		       }
		       
		       EXIST_flag = YES;
		       face_line[k]->regions += 1;
		       face_line[k]->second   = MakeStringCopy(region->name);
		       break;
		   }
	    }

	    if(EXIST_flag == NO) {

		if(face_lines+1 == MAX_FACELINES) {
		    SystemError("Too many faces");
		    continue;
		}

		face_line[face_lines] = (FaceLine *)FEEL_GetMemory(sizeof(FaceLine));
		
		face_line[face_lines]->regions = 1;
		face_line[face_lines]->remake_flag = NO;

		face_line[face_lines]->from    = MakeStringCopy(from);
		face_line[face_lines]->to      = MakeStringCopy(  to);
		face_line[face_lines]->first   = MakeStringCopy(region->name);

		get_point_xy_by_name( from ,&x1 ,&y1);
		face_line[face_lines]->x1 = x1;
		face_line[face_lines]->y1 = y1;

		get_point_xy_by_name( to   ,&x2 ,&y2);
		face_line[face_lines]->x2 = x2;
		face_line[face_lines]->y2 = y2;

		face_line[face_lines]->len = (double)sqrt((x1-x2)*(x1-x2) +
							  (y1-y2)*(y1-y2)   );

		
/*		printf("From  %s  To %s\n",face_line[face_lines]->from,face_line[face_lines]->to);*/

		face_lines++;
	    }
	}
    }

    return;
}
		
		       
int how_many_face_lines()
{
    return(face_lines);
}

FaceLine *get_nth_face_line_ptr( n )
     int n;
{
    return( face_line[n]);
}

FaceLine *get_face_line_ptr_by_2names( p1 , p2 )
     char *p1,*p2;
{
    int i;

    for(i=0;i<face_lines;i++) {

	if(streq(p1,face_line[i]->from) && 
	   streq(p2,face_line[i]->to)   ) {
	    return (face_line[i]);
	}

	if(streq(p2,face_line[i]->from) && 
	   streq(p1,face_line[i]->to)   ) {
	    return (face_line[i]);
	}
    }

    {
	char buf[256];

	sprintf(buf,"No line has %s and %s as its two ends.",p1,p2);
	SystemAbort(buf);
    }
 
}


