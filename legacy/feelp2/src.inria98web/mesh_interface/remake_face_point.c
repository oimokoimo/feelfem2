/*
 * FEEL system Prototype Version 2
 * 
 * File     remake_face_point.c
 * Made     1992/09/03
 * Modified 
 * Version  0.0
 *
 * Purpose: remake points in face line with specified points
 *
 */

#include "mesh_interface.h"

remake_face_point( face_ptr , points )
     FaceLine *face_ptr;
     int       points;
{
    int i;

    if(points < 2 ) {
	SystemAbort("Remake Face Point routine error.(<2)");
    }

    if(face_ptr->remake_flag == YES) {
	SystemAbort("Attempt to remake face line again.");
    }

    face_ptr->remake_flag = YES;
    face_ptr->points      = points;

    FEEL_FreeMemory(face_ptr->x);
    FEEL_FreeMemory(face_ptr->y);

    face_ptr->x = (double *)FEEL_GetMemory( sizeof(double) * points);
    face_ptr->y = (double *)FEEL_GetMemory( sizeof(double) * points);

    /* make nodes from 'from' to 'to' */
    for(i=0;i<points;i++) {
	*(face_ptr->x+i) = (face_ptr->x2-face_ptr->x1) / ((double)(points-1))
	                   * (double)i + face_ptr->x1;
	*(face_ptr->y+i) = (face_ptr->y2-face_ptr->y1) / ((double)(points-1))
	                   * (double)i + face_ptr->y1;
    }

    return;
    
}
    
