/*
 * FEEL system Prototype Version 2
 * 
 * File     make_points_in_face.c
 * Made     1992/08/24
 * Modified 
 * Version  0.0
 *
 * Purpose: make points in face line
 *
 */

#include "mesh_interface.h"
#include "../mesh_comp/mesh_comp.h"


make_points_in_face( )
/*## Read all face_line pointer and make initial nodes on each face line.
  $$ Notice:  This version divides the line in equal interval.

  %% called from mesh_generate_main.c
*/
{
    int i,j;
    
    int face_lines;
    FaceLine *face_line_ptr;

    double h_size_first,h_size_second,h_size;
    double r,x,y,xx,yy;
    int points;

    face_lines = how_many_face_lines();


    for(i=0;i<face_lines;i++) {
	face_line_ptr = get_nth_face_line_ptr(i);
	
	if(face_line_ptr->regions == 1 ) {
	    h_size = get_region_mesh_size_by_name( face_line_ptr->first);
	}
	else {
	    h_size_first =get_region_mesh_size_by_name( face_line_ptr->first);
	    h_size_second=get_region_mesh_size_by_name( face_line_ptr->second);

	    if(h_size_first < h_size_second) h_size = h_size_first;
	    else                             h_size = h_size_second;
	}
	
	x = face_line_ptr->x2 - face_line_ptr->x1;
	y = face_line_ptr->y2 - face_line_ptr->y1;

	r = sqrt( x * x + y * y );


/*	printf("x=%f  y=%f  r=%f  h_size=%f\n",x,y,r,h_size); */

	points = r / h_size;

	points ++;

/*	printf("FaceLine From %s To %s   points=%d\n",face_line_ptr->from,face_line_ptr->to,points); */


	face_line_ptr -> points = points;
	
	face_line_ptr->x = (double *)FEEL_GetMemory(sizeof(double)*points);
	face_line_ptr->y = (double *)FEEL_GetMemory(sizeof(double)*points);

	for(j=0;j<points;j++) {
	    xx = face_line_ptr->x1 + (x / (double)(points-1)) * j;
	    yy = face_line_ptr->y1 + (y / (double)(points-1)) * j;

	    *(face_line_ptr->x + j) = xx;
	    *(face_line_ptr->y + j) = yy;
	}
    }

    return;

}
    
