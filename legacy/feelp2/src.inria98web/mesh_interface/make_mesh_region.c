/*
 * FEEL system Prototype Version 2
 * 
 * File     make_mesh_region.c
 * Made     1992/08/31
 * Modified 
 * Version  0.0
 *
 * Purpose: Make mesh regionwise.
 *
 */

#include "mesh_interface.h"
#include "../mesh_comp/mesh_comp.h"

make_mesh_region()
/*## Read region pointer and call mesh generate program by
  ## the method specified in region->type.

  %% called from mesh_generate_main.c
*/
{
    int i;

    int regions;

    Region *region_ptr;

    regions = how_many_regions();
    
    for(i=0;i<regions;i++) {

	region_ptr = get_nth_region_ptr(i);
	
	if(streq(region_ptr->method,MESH_METHOD_RECT)) {
	    do_region_mesh_rect(region_ptr);
	}
	else {
	    NotImplement("do_region_mesh_free.");

	 /*    do_region_mesh_free(region_ptr); */
	}

    }

    return;
}







