/*
 * FEEL system Prototype Version 2
 * 
 * File     mesh_size.c
 * Made     1992/08/26
 * Modified 
 * Version  0.0
 *
 * Purpose: Controle program for determing mesh sizes.
 *
 * LIMIT:   One domain only
 */

#include "mesh_interface.h"
#include "../mesh_comp/mesh_comp.h"


static double total_area;          
static int    total_freedom;
static double ideal_mesh_size;



put_total_area( area )
     double area;
{

    total_area    = area;
    total_freedom = get_freedom();

    ideal_mesh_size =(double)sqrt(total_area/(double)total_freedom*0.68*2.0);
    
    return;
}





double get_region_mesh_size_by_name( name )
     char *name;
{
    Region *region_ptr;

    region_ptr = get_region_ptr_by_name( name );


    /* LIMIT now do nothing */

    return(ideal_mesh_size);
}

