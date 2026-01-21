/*
 * FEEL system Prototype Version 2
 * 
 * File     region_data.c
 * Made     1992/09/28
 * Modified 
 * Version  0.0
 *
 * Purpose: store region data(node, element information)
 *
 */

#include "../main/feel.h"
#include "../mesh_comp/mesh_comp.h"    /* for MAX_REGIONS define */
#include "mesh_interface.h"


statinc int region_data_no = 0;
static RegionData *region_data[MAX_REGIONS];


void put_region_data( region_data_ptr )
     RegionData *region_data_ptr;
{
    if(region_data_no == MAX_REGIONS) {
	TooManyPutRegionDataError();
	return;
    }

    region_data[region_data_no] = region_data_ptr;

    region_data_no++;
    
    return;
}

int how_many_region_data()
{
    return(region_data_no);
}

RegionData *get_nth_region_data( n )
     int n;
{
    if(n < 0 || n >= region_data_no) {
	InternalError("get_nth_region_data");
    }

    return( region_data[n] );
}


