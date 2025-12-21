/*
 * FEEL system Prototype Version 2
 * 
 * File     make_region_order.c
 * Made     1992/08/27
 * Modified 
 * Version  0.0
 *
 * Purpose: This program makes the order of making mesh.
 *
 */
#include "mesh_interface.h"
#include "../mesh_comp/mesh_comp.h"


#include <stdio.h>

make_region_order()
{
    int i,j,ip,jp;
    
    int regions;
    int face_lines;
    
    int  *order_point;
    int  *dependency;

    Region   *region_ptr;
    Region   *region_ptr1,*region_ptr2;
    FaceLine *face_line_ptr;

    
    regions    = how_many_regions();
    face_lines = how_many_face_lines();

    order_point = (int  *)FEEL_GetMemory(sizeof(int)*regions);
    dependency  = (int  *)FEEL_GetMemory(sizeof(int)*regions*regions);

    for(i=0;i<regions;i++) {
	*(order_point+i) = 0;
	for(j=0;j<regions;j++) {
	    *(dependency + i * regions + j) = 0;
	}
    }

    
    for(i=0;i<face_lines;i++) {
	face_line_ptr = get_nth_face_line_ptr(i);

	if(face_line_ptr->regions == 1) continue;

	ip = get_region_no_by_name(face_line_ptr->first);
	jp = get_region_no_by_name(face_line_ptr->second);

	*(dependency + ip * regions + jp ) = 1;
	*(dependency + jp * regions + ip ) = 1;

    }


    for(i=0;i<regions;i++) {
	for(j=0;j<regions;j++) {
	    *(order_point+i) += *(dependency + i * regions + j);
	}
    }

    
    
    NotImplement("make_region_order(imcomplete)");


/*    for(i=0;i<regions;i++) {
	region_ptr = get_nth_region_ptr(i);
	printf("%s   %d\n",region_ptr->name,*(order_point+i));
    }
    */

}



	
	
	
