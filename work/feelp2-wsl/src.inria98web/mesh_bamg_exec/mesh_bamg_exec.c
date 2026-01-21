/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   mesh_bdamg_exec.c
 *      Date:   1997/05/27
 *   
 *  Modified:   1999/04/12 Addition of rect functionality   
 *              1999/11/29 change avs_ref_etype to etype in 
 *              set_bamg_info_etype
 *              There must be confusion in etype usage
 *              etype TRI=2,RECT=3, but avs_ref_etype, tri=3,rect=4
 *   
 *   Purpose:   interface program to BDAMG/INRIA mesh generator
 *              
 *              
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"

#include "../mesh_exec/mesh_exec.h"    /* Caution */

#define DBG 0

static MidPoint2D total;

extern int recursive_mesh_div;

void mesh_bamg_exec( mesh_edat_ptr )
     ElemDat *mesh_edat_ptr;
{
    int i,j,k;

    FILE *fp;

    int solve_elements;
    ElemDat *edat_ptr;

    int domains;             /* now this is not used????? */
    char *domain_name;       
    Domain *domain_ptr;

    int regions,inner_regions;
    Region *region_ptr;

    int total_points;
    int edge_points,isolate_points;
    Point *point_ptr;
    int *mesh_no_order_ptr;

    int app_edges;          /* approximate number of edges */

    int etype;
    int matno;
    int nodes;
    int bamgnodes;          /* add 2000/03/09 */
    double nodes_for_rect; 

    double total_area;
    double h_initiale;

    char bamg_command[BUFSIZ];



    /* Set BAMG GEOMETRY DATA in make_bamg_info.c */
    domain_name = mesh_edat_ptr -> domain_name;
    domain_ptr = get_domain_ptr_by_name( domain_name );

    etype = domain_ptr -> etype;
    nodes = get_region_nodes( domain_ptr -> name );

    
    if(nodes == 0) {
	SystemWarning_s("Number of nodes of domain %s is not defined.",
			domain_ptr-> name);
	nodes = DEFAULT_NODES;   /* Now 200 is used */
    }
    
    regions = domain_ptr->regions;
    if(regions == 0) {
	SystemAbort("There is no region(regions=0)\n");
    }


    /* Calculate the are of region */
    total_area = 0.0;
    for(i=0;i<regions;i++) {


      region_ptr = get_region_ptr_by_name(*(domain_ptr->region_name+i));

      region_ptr -> area = get_region_area( region_ptr );



      total_area = total_area + region_ptr->area;
    }


    /*-----------------------------------------------------------------*/
    /*  MAKE BAMG-GEOM DATA                                            */
    /*-----------------------------------------------------------------*/
    rep_proc("bamg_info_init");
    bamg_info_init();                        /* Iitialize bamg struct  */


    rep_proc("bamg_info_etype");
    set_bamg_info_etype( etype );            /* Triangle or Rectangle  */
    rep_proc("bamg_info_nodes");

    /* bamg mode for rect */
    if(avs_mesh_ref == 4) {
      nodes_for_rect = nodes;
      nodes_for_rect = nodes_for_rect /4.0;
      nodes = nodes_for_rect;
/*      fprintf(stderr,"nodes new = %d\n",nodes); */
    }


    set_bamg_info_nodes( total_area, nodes); /* Initial Mesh partition */
    
    /* Set Vertices in Geometry */


    edge_points = how_many_outer_edge_points() +
                  how_many_inner_edge_points();
    isolate_points = how_many_isolate_points();
    total_points = edge_points + isolate_points;


    set_bamg_info_vertices_init(total_points,edge_points);

    mesh_no_order_ptr = get_mesh_point_no_order_ptr();

    for(i=0;i<total_points;i++) {
      point_ptr = get_nth_point_ptr(*(mesh_no_order_ptr+i));
      set_bamg_info_vertices(i+1,point_ptr->x,point_ptr->y,i+1);
    }


    /* Make edge informations */


    app_edges = 0;
    for(i=0;i<regions;i++) {
      matno = i + 1;
      region_ptr = get_region_ptr_by_domain_matno(domain_ptr->name,
						  matno            );
      for(j=0;j<region_ptr->edges;j++) {
	app_edges = app_edges + region_ptr->points[j]+1;
      }
    }

    bamg_make_edge_info_init(app_edges);

    for(i=0;i<regions;i++) {

      matno = i + 1;
      region_ptr = get_region_ptr_by_domain_matno(domain_ptr->name,
						  matno            );
      
      for(j=0;j<region_ptr->edges;j++) {
	for(k=0;k<region_ptr->points[j];k++) {
	  int from,to;

	  point_ptr = 
	    get_point_ptr_by_name(region_ptr->compos[j][k]);
	  
	  from = point_ptr->mesh_no;

	  if(k == (region_ptr->points[j]-1)) {
	    point_ptr = get_point_ptr_by_name(region_ptr->compos[j][0]);
	  }
	  else {
	    point_ptr = get_point_ptr_by_name(region_ptr->compos[j][k+1]);
	  }

	  to   = point_ptr->mesh_no;

	  bamg_make_edge_info_store(from,to);
	}
      }
    }

    make_bamg_geom_edges();
    
    /* Set Subdomains in Geometry (Subdomain is defined by matno)*/

    make_bamg_subdomain_info_init(regions);

    for(i=0;i<regions;i++) {
      int from,to;
      matno = i + 1;
      region_ptr = get_region_ptr_by_domain_matno(domain_ptr->name,matno);

      /* Using first edge in region definition */
      point_ptr = get_point_ptr_by_name(region_ptr->compos[0][0]);
      from      = point_ptr->mesh_no;

      point_ptr = get_point_ptr_by_name(region_ptr->compos[0][1]);
      to        = point_ptr->mesh_no;

      set_bamg_info_subdomains(i+1,matno,from,to);
    }


    /* WRITE OUT GEOMETRY FILE */
    if(DBG) fprintf(stderr,"File output...\n");


    fp = fopen(BAMG_GEOM_FILE,"w");
    if(fp == NULL) {
      fprintf(stderr,"Cannot open %s to write.\n",BAMG_GEOM_FILE);
      exit(1);
    }
    wrt_bamg_geom(fp);
    fclose(fp);


    /*=====================================*/
    /* Execute BAMG                        */
    /*=====================================*/
    
    if(etype == TRI) {
      if(nodes <= 50000 ) {
      sprintf(bamg_command,"%s %s  -g %s -o %s",
	      BAMG_COMMAND_NAME,
	      BAMG_DEFAULT_OPTION,
	      BAMG_GEOM_FILE,
	      BAMG_MESH_FILE );
      } else
      {
      bamgnodes = nodes*1.2;
      sprintf(bamg_command,"%s %s -nbv %d -g %s -o %s",
	      BAMG_COMMAND_NAME,
	      BAMG_DEFAULT_OPTION,
	      bamgnodes,
	      BAMG_GEOM_FILE,
	      BAMG_MESH_FILE );
      }	        
    }
    else {
      if(nodes <= 50000 ) {
      sprintf(bamg_command,"%s %s %s -g %s -o %s",
	      BAMG_COMMAND_NAME,
	      BAMG_DEFAULT_OPTION,
	      BAMG_RECT_OPTION,
	      BAMG_GEOM_FILE,
	      BAMG_MESH_FILE );
      } else
      {
      bamgnodes = nodes*1.2;
      sprintf(bamg_command,"%s %s -nbv %d %s -g %s -o %s",
	      BAMG_COMMAND_NAME,
	      BAMG_DEFAULT_OPTION,
	      bamgnodes,
	      BAMG_RECT_OPTION,
	      BAMG_GEOM_FILE,
	      BAMG_MESH_FILE );
      }
    }

    fprintf(stderr,"Mesh Generation by BAMG..");  /* dbg: */

    system(bamg_command);

    fprintf(stderr,"done\n");


    /*---------------------*/
    /* MID NODE            */
    /*---------------------*/
    mid_info_for_meshbook( mesh_edat_ptr, &total);
    save_midpoint2d_total(&total);  /* This is in make_feel_data_file_bamg.c */
    save_meshedatptr(mesh_edat_ptr);/* This is in make_feel_data_file_bamg.c */

    /*    get_mesh_data();  */

    return;
}
