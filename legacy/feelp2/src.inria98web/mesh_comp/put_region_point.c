 /*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File: put_ region_ point .c
 *      Date: 1993/06/03 (Modified)
 *   
 *   Purpose: pointデータ内にregionデータを代入する
 *            
 */

#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "mesh_comp.h"

put_region_point(region_ptr)
     Region *region_ptr;
{
    int i,j;

    for(i=0;i<region_ptr->edges;i++) {
	for(j=0;j<region_ptr->points[i];j++) {
	    store_region_name_in_point_st(region_ptr->compos[i][j],
					  region_ptr->name);
	}
    }

    return;
}


store_region_name_in_point_st(point_name,region_name)
     char *point_name;
     char *region_name;
{
    int i;
    
    Point *point_ptr;

    point_ptr = get_point_ptr_by_name( point_name );

    for(i=0;i<point_ptr->concern_regions;i++) {
	if(streq(point_ptr->region_name[i],region_name)) return;
    }

    
    if(point_ptr->concern_regions == MAX_CONC_REGIONS-1) {
	SystemAbort("Too many concerning regions in one point.");
    }

    /* CAUTION Not use heap memory */
    point_ptr->region_name[point_ptr->concern_regions] = region_name;
    

    point_ptr->concern_regions += 1;

    return;
}

