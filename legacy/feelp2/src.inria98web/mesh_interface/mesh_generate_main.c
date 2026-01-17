/*
 * FEEL system Prototype Version 2
 * 
 * File     mesh_generate_main.c
 * Made     1992/08/26
 * Modified 
 * Version  0.0
 *
 * Purpose: This function is the main function to generate 2d-mesh.
 *          This function is called directory from yacc program.
 */

#include "mesh_interface.h"
#include "../mesh_comp/mesh_comp.h"

mesh_generate_main()
{
    int i;

    int domains;
    int regions;
    int lines;
    int points;

    int face_lines;

    Domain *domain_ptr;
    Region *region_ptr;
    

    double    total_area,h;

    int    *making_mesh_order;


    domains = how_many_domains();
    regions = how_many_regions();
    lines   = how_many_lines();
    points  = how_many_points();

    

    if(domains == 0) {
	SystemAbort("There is no domain specified.");
    }
    if(points ==  0) {
	SystemAbort("There is no point specified.");
    }

    if(domains != 1) {
	SystemAbort("This FEEL Version is One domain version.");
	/* SINGLE DOMAIN */
    }


    /* Make complete region division */
    if(regions == 0 ) {
	/* IF NO REGION IS DECLARED, DOMAIN MUST BE SINGLE CONNECTED */
	domain_ptr = get_nth_domain_ptr(0); /* SINGLE DOMAIN */
	put_domain_data_to_region(domain_ptr);
	regions  = 1;
    }
    else {

	make_region_divide_complete();
	/* DIFFICULT ROUTINE */
    }


    for(i=0;i<regions;i++) {
	region_ptr = get_nth_region_ptr(i);
	get_face_from_region(region_ptr);
	put_region_point(region_ptr);       /* make point <-> region data */
    }

/*    {
       int i,j,points;
       Point *point_ptr;
       points = how_many_points();
       for(i=0;i<points;i++) {
	  point_ptr = get_nth_point_ptr(i);
	  printf("POINT %s   ",point_ptr->name);
	  for(j=0;j<point_ptr->concern_regions;j++) {
	      printf(" %s",point_ptr->region_name[j]);
          }
	  printf("\n");
       }
    }
*/


    face_lines = how_many_face_lines();


    /* Calculate Geometry Features of each region and store the data  */

    total_area = 0;
    for(i=0;i<regions;i++) {
        region_ptr = get_nth_region_ptr(i);
	region_ptr->area = get_region_area(region_ptr);
	total_area = total_area + region_ptr->area;
    }

    put_total_area(total_area);


    make_region_order();

    make_points_in_face();


    make_mesh_region();
/*
    make_mesh_data();

*/

/*     printf("total_area = %f\n",total_area); */
}

