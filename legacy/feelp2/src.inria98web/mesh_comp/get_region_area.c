/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File: get_region_area.c
 *      Date: 1993/06/03(Modified)
 *   
 *   Purpose: 指定されたdomain,regionの面積を計算する
 *   Functions: get_region_area( Domain *)         
 */

#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "mesh_comp.h"
#include "../geom2d/geom2d.h"


double get_region_area( region )
     Region *region;
{
    int i,j,tmp;
    double area,subarea;
    POLYGON_ST po;
    

    tmp = GetMaxInteger( region -> edges, region ->points );

    po.x = (double *)FEEL_GetMemory(sizeof(double) * tmp);
    po.y = (double *)FEEL_GetMemory(sizeof(double) * tmp);


    for(i=0;i<region->edges;i++) {

	for(j=0;j<region->points[i];j++) {
	  get_point_xy_by_name(region->compos[i][j],po.x+j,po.y+j);
	}
	po.n = region->points[i];

	if(i == 0) {
	    area = get_polygon_area( &po );   /* in geom2d directory */
            if(area <= 0) {
              SystemError_s("Region %s",region->name);
              SystemError("Region point specification may be clockwise \n             or not polygonal");
              SystemAbort("Region specification Error");
            }
           
	}
	else {
	    ReverseDoubleArray( po.n , po.x);   /* inner edge is clockwise */
	    ReverseDoubleArray( po.n , po.y);
            subarea = get_polygon_area(&po);

            if(subarea <= 0) {
              SystemError_sn("Region %s's %dth hole",region->name,
                              region->edges-i);
              SystemError("Inner hole point specification may be unti-clockwise \n             or not polygonal");
              SystemAbort("Hole specification Error");
            }

	    area = area - get_polygon_area( &po );
	}
    }

    FEEL_FreeMemory( po.x );
    FEEL_FreeMemory( po.y );

    return(area);
}
