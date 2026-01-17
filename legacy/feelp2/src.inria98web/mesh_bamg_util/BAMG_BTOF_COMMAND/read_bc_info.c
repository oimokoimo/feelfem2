/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   read_bc_info.c
 *      Date:   1995/09/1
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../../feel_def/feel_def.h"
#include "edat.h"


#define MAX_BCOND_STACK   500


/* for neumann condition */
typedef struct {   /* edat line */
  int   line_sets;
  char *from,*to;
  int   total_edge_points;
  int   use_points;
  int  *use_flag;
} EdatLine;

typedef struct {  /* boundary edat */
  int edatno;
  int np;
  int edatlines;
  EdatLine **edatline_ptrptr;
} BEdat;


/* for dirichlet condition */
typedef struct {  /* nset point */
  char *var_name;
  char *point_name;  /* point name for dirichlet condition */
  int   iedp;
} NsetPoint;

typedef struct {  /* nset line */
  char *var_name;
  char *from;
  char *to;
  int   unit_points;
  int  *eq_plus;      /* array for iedp */
  int  *use_flag;     /* use or not     */
} NsetLine;

typedef struct {   /* boundary nset */
  int nsetno;
  int nsetpoints;
  int nsetlines;
  NsetPoint **nsetpoint_ptrptr;
  NsetLine  **nsetline_ptrptr;
} BNset;

/* PLOT DATA */
typedef struct {
  int    segments;
  int    plotlineno;
  char **from_ptrptr;
  char **to_ptrptr;
} PlotLine;


#define NEUMANN   1
#define DIRICHLET 2

#define ON        1
#define OFF       0

static int   points;   /* point sentence */
static char *point_name[MAX_POINTS];

static int   bc_nsets;
static int   bc_edats;
static int   bc_plots;

static BNset    *bnset_buf[MAX_BCOND_STACK];
static BEdat    *bedat_buf[MAX_BCOND_STACK];
static PlotLine *plot_buf[MAX_BCOND_STACK];

static int edatline_count;
static int nsetline_count;
static int nsetpoint_count;
static EdatLine  *edatline_buf [MAX_POINTS];
static NsetLine  *nsetline_buf [MAX_POINTS];
static NsetPoint *nsetpoint_buf[MAX_POINTS];


int how_many_ip_points()
{
  return(points);
}

char *get_bamg_point_name_by_no( n )
     int n;
{

  if(points < n || n < 1) {
    fprintf(stderr,"Illegal point number in get_bamg_point_name_by_no.\n");
    exit(1);
  }
			
  return(point_name[n-1]);
}

int get_node_no_by_name_bamg( name )
     char *name;
{
  int i;

  for(i=0;i<points;i++) {
    if(streq(point_name[i],name)) {
      return( i+1 );  /* CAUTION: Dependency on BAMG version */
    }
  }
  fprintf(stderr,"cannot find point namd %s\n",name);
  exit(1);
}

char *make_string_copy(s)
     char *s;
{
  int len;
  char *ptr_buf,*ptr,*malloc();
  
  len = strlen(s);
  ptr_buf = malloc(len+1);
  ptr     = ptr_buf;
  
  
  while(*s) {
    *ptr = *s;
    ptr++;  s++;
  }
  *ptr = '\0';
  return(ptr_buf);
}


void read_bc_info(fpr)
     FILE *fpr;
{
  int i,ret;
  int reading_mode;
  int reading_type;
  
  char  buf[BUFSIZ],arg1[BUFSIZ],arg2[BUFSIZ],arg3[BUFSIZ];
  char *make_string_copy();
  
  int *iptr;
  
  int  dummy,total_edge_points,use_points;
  int  edatno,np;
  int  unit_points;
  int  iedp;
  int  nsetno;

  
  BNset     *bnset_ptr;
  BEdat     *bedat_ptr;
  EdatLine  *edatline_ptr;
  EdatLine **edatline_ptrptr;
  NsetLine  *nsetline_ptr;
  NsetLine **nsetline_ptrptr;
  NsetPoint *nsetpoint_ptr;
  NsetPoint **nsetpoint_ptrptr;

  char *malloc();
  
  
  /* Initialize */
  bc_nsets = 0;
  bc_edats = 0;
  bc_plots = 0;
  
  /* read for "points" */
  
  fscanf(fpr,"%s",buf);
  
  if(!strindex(buf,"points")) {
    fprintf(stderr,"Illegal bamg.feel file.(in reading points)\n");
    fprintf(stderr,"buf=%s\n",buf);
    exit(1);
  }
  
  fscanf(fpr,"%d",&points);
  
  for(i=0;i<points;i++) {
    fscanf(fpr,"%s",buf);
    point_name[i] = make_string_copy(buf);
  }
  
  reading_mode = OFF;
  
  while(EOF != (ret=fscanf(fpr,"%s",buf))) {
    if(strindex(buf,"edatline")) {
      if(reading_mode == OFF) {
	reading_mode = ON;
	reading_type = NEUMANN;
	edatline_count = 1;
      }
      else {
	edatline_count++;
	if(edatline_count >= MAX_POINTS) {
	  fprintf(stderr,"Too many EdatLines\n");
	  exit(1);
	}
      }
      edatline_ptr = (EdatLine *)malloc(sizeof(EdatLine));
      edatline_buf[edatline_count-1] = edatline_ptr;
      
      fscanf(fpr,"%d",&dummy);  
      if(dummy != edatline_count) fprintf(stderr,"JESUS");
      fscanf(fpr,"%s %s",arg1,arg2);
      edatline_ptr -> from = make_string_copy(arg1);
      edatline_ptr -> to   = make_string_copy(arg2);
      
      fscanf(fpr,"%d %d",&total_edge_points,&use_points);
      edatline_ptr -> total_edge_points = total_edge_points;
      edatline_ptr -> use_points        = use_points;
      
      iptr = (int *)malloc(sizeof(int)*total_edge_points);
      edatline_ptr -> use_flag = iptr;
      for(i=0;i<total_edge_points;i++) {
	fscanf(fpr,"%d",iptr+i);
      }
    }  /* end of EdatLine */
    
    else if( strindex(buf,"nsetline")) {  /* NsetLine */
      if(reading_mode == OFF) {
	reading_mode = ON;
	reading_type = DIRICHLET;
	nsetline_count  = 1;
	nsetpoint_count = 0;       /* caution */
      }
      else {
	nsetline_count++;
	if(nsetline_count >= MAX_POINTS) {
	  fprintf(stderr,"Too many NsetLine\n");
	  exit(1);
	}
      }
      nsetline_ptr = (NsetLine *)malloc(sizeof(NsetLine));
      nsetline_buf[nsetline_count-1] = nsetline_ptr;
      
      fscanf(fpr,"%s %s %s",arg1,arg2,arg3);
      nsetline_ptr->var_name = make_string_copy(arg1);
      nsetline_ptr->from     = make_string_copy(arg2);
      nsetline_ptr->to       = make_string_copy(arg3);
      
      fscanf(fpr,"%d",&unit_points);
      nsetline_ptr->unit_points = unit_points;
      
      iptr = (int *)malloc(sizeof(int)*unit_points);
      nsetline_ptr->eq_plus = iptr;
      for(i=0;i<unit_points;i++) {
	fscanf(fpr,"%d",iptr+i);
      }
      
      iptr = (int *)malloc(sizeof(int)*unit_points);
      nsetline_ptr->use_flag = iptr;
      for(i=0;i<unit_points;i++) {
	fscanf(fpr,"%d",iptr+i);
      }
      
    } /*  end of NsetLINE */
    else if(strindex(buf,"nsetpo")) {
      if(reading_mode == OFF) {
	reading_mode = ON;
	reading_type = DIRICHLET;
	nsetline_count  = 0;       /* caution */
	nsetpoint_count = 1;
      }
      else {
	nsetpoint_count++;
	if(nsetpoint_count >=MAX_POINTS) {
	  fprintf(stderr,"Too many NsetPoint\n");
	  exit(1);
	}
      }
      nsetpoint_ptr = (NsetPoint *)malloc(sizeof(NsetPoint));
      nsetpoint_buf[nsetpoint_count-1] = nsetpoint_ptr;
      
      fscanf(fpr,"%s %s %d",arg1,arg2,&iedp);
      nsetpoint_ptr->var_name   = make_string_copy(arg1);
      nsetpoint_ptr->point_name = make_string_copy(arg2);
      nsetpoint_ptr->iedp       = iedp;
      
    }  /* End of nsetpoint */	

    else if(strindex(buf,"plot")) {
      int    iplot;
      int    segments;
      int    plotlineno;
      char **plot_from,**plot_to;
      PlotLine *plot_ptr;

      fscanf(fpr,"%d %d",&plotlineno,&segments);
      
      plot_ptr  = (PlotLine *)malloc(sizeof(PlotLine));
      plot_from = (char    **)malloc(sizeof(char *)*segments);
      plot_to   = (char    **)malloc(sizeof(char *)*segments);

      if(plot_ptr == NULL || plot_from == NULL || plot_to == NULL) {
	fprintf(stderr,"Cannot allocate plot_ptr, etc. (read_bc_info.c)\n");
	exit(1);
      }
      plot_buf[bc_plots] = plot_ptr;
      plot_ptr->segments = segments;
      plot_ptr->plotlineno = plotlineno;
      plot_ptr->from_ptrptr = plot_from;
      plot_ptr->to_ptrptr   = plot_to;
      bc_plots++;

      for(iplot = 0;iplot < segments;iplot++) {
	fscanf(fpr,"%s %s",arg1,arg2);

	*(plot_from+iplot) = make_string_copy(arg1);
	*(plot_to  +iplot) = make_string_copy(arg2);
      }

      fscanf(fpr,"%s",buf);
      if(!strindex(buf,"end")) {
	fprintf(stderr,"Illegal plot line data reading...\n");
	exit(1);
      }

    }  /* end of plot loop */
    
    else if(strindex(buf,"end")) {
      
      if(reading_mode != ON) {
	fprintf(stderr,"Illegal end encountered.\n");
	exit(1);
      }
      reading_mode = OFF;
      
      if(reading_type == DIRICHLET) {
	
	bnset_ptr = (BNset *)malloc(sizeof(BNset));
	bnset_buf[bc_nsets] = bnset_ptr;
	bc_nsets++;
	if(bc_nsets >MAX_BCOND_STACK) {
	  fprintf(stderr,"Too many boundary line segments.\n");
	  exit(1);
	}
	
	fscanf(fpr,"%d",&nsetno);
	
	bnset_ptr -> nsetpoints = nsetpoint_count;
	bnset_ptr -> nsetlines  = nsetline_count;
	bnset_ptr -> nsetno     = nsetno;
	
	if(nsetline_count > 0) {
	  nsetline_ptrptr = (NsetLine **)malloc(sizeof (NsetLine *)*
						nsetline_count);
	  bnset_ptr->nsetline_ptrptr = nsetline_ptrptr;
	  for(i=0;i<nsetline_count;i++) {
	    *(nsetline_ptrptr+i) = nsetline_buf[i];
	  }
	}
	if(nsetpoint_count > 0) {
	  nsetpoint_ptrptr = (NsetPoint **)malloc(sizeof (NsetPoint *)*
						  nsetpoint_count);
	  bnset_ptr->nsetpoint_ptrptr = nsetpoint_ptrptr;
	  for(i=0;i<nsetpoint_count;i++) {
	    *(nsetpoint_ptrptr+i) = nsetpoint_buf[i];
	  }
	}
      } /* Dirichlet condition */
      
      
      
      else {  /* Neumann condition */
	
	if(reading_type != NEUMANN) {
	  fprintf(stderr,"Neumann/Dirichlet Mismatch\n");
	  exit(1);
	}
	
	bedat_ptr = (BEdat *)malloc(sizeof(BEdat));
	bedat_buf[bc_edats] = bedat_ptr;
	bc_edats++;
	if(bc_edats >MAX_BCOND_STACK) {
	  fprintf(stderr,"Too many boundary line segments.\n");
	  exit(1);
	}
	
	fscanf(fpr,"%d %d",&edatno,&np);
	
	bedat_ptr->edatno = edatno;
	bedat_ptr->np     = np;

	bedat_ptr->edatlines = edatline_count;
	
	if(edatline_count == 0) {
	  fprintf(stderr,"Inner error in edatline_count=0\n");
	  exit(1);
	}
	edatline_ptrptr = (EdatLine **)malloc(sizeof(EdatLine *)*
					      edatline_count     );
	bedat_ptr->edatline_ptrptr = edatline_ptrptr;
	for(i=0;i<edatline_count;i++) {
	  *(edatline_ptrptr+i)=edatline_buf[i];
	}
      }  /* end of 'end' keyword */
      
      
    }  /* if strindex */
    else {
      fprintf(stderr,"Internal err\n");
      exit(1);
    }


  }  /* while */
  return;
}

/*
 *
 *  Push boundary node data
 *
 */


#define MAX_TMP_POINTS 1000

static Boundary2Dbamg *bd2d[MAX_LINES];
static int             bd2ds = 0;

void store_boundary_data_bamg(from,to,points,region_no,iptr)
     int  from,to,points,region_no;
     int *iptr;
{

    int i;
    char *get_bamg_point_name_by_no();
    char *malloc();

    bd2d[bd2ds] = (Boundary2Dbamg *)malloc(sizeof(Boundary2Dbamg));
    
    bd2d[bd2ds]->points    = points;
    bd2d[bd2ds]->from      = from;
    bd2d[bd2ds]->from_name = get_bamg_point_name_by_no(from);
    bd2d[bd2ds]->to        = to;
    bd2d[bd2ds]->to_name   = get_bamg_point_name_by_no( to );
    bd2d[bd2ds]->node_no   = iptr;
    bd2d[bd2ds]->region_no = region_no;

    
    bd2ds++;
    return;
}

Boundary2Dbamg *get_b2d_ptr_by_both_ends_bamg( from ,to )
     char *from,*to;
{
    int i;

    for(i=0;i<bd2ds;i++) {
/*	fprintf(stderr,"bd2d[%d]->from_name = %s , ->to_name = %s\n",
		i,bd2d[i]->from_name , bd2d[i]->to_name);
*/
	if(streq(bd2d[i]->from_name, from) &&
	   streq(bd2d[i]->to_name  ,to   )) {
	    return(bd2d[i]);
	}

	if(streq(bd2d[i]->from_name, to ) &&
	   streq(bd2d[i]->to_name  ,from)) {
	    return(bd2d[i]);
	}
    }
    fprintf(stderr,"Boundary edge segment %s-%s is not exist.\n",from,to);
    fprintf(stderr,"No corresponding boundary.\n");
    exit(1);
}


void bamg_feel_dat_bc(fp,edat_ptr)
     FILE     *fp;
     FEM_edat *edat_ptr;
{
  int i,j;

  /*==========*/
  /* For edat */
  /*==========*/
  int       edatlines;
  BEdat    *bedat_ptr;
  EdatLine *edat_line_ptr;

  /*==========*/
  /* For edat */
  /*==========*/
  int nsetpoints,nsetlines;
  BNset *bnset_ptr;
  NsetPoint *nsetpoint_ptr;
  NsetLine  *nsetline_ptr;


  /* make edat data */
  for(i=0;i<bc_edats;i++) {
    bedat_ptr = bedat_buf[i];

    edatlines = bedat_ptr->edatlines;

    boundary_edat_reset_bamg();   /* reset edat boundary data */

    for(j=0;j<edatlines;j++) {
      edat_line_ptr = *(bedat_ptr->edatline_ptrptr + j);

      push_boundary_edat_line_bamg(edat_line_ptr->from,
				   edat_line_ptr->to,
				   edat_line_ptr->use_flag,
				   edat_line_ptr->use_points,
				   edat_line_ptr->total_edge_points);
    }
    make_boundary_edat_bamg(fp,bedat_ptr->edatno,bedat_ptr->np,edat_ptr);
  }

  /*==========*/
  /* for nset */
  /*==========*/

  for(i=0;i<bc_nsets;i++) {
    bnset_ptr  = bnset_buf[i];
    nsetpoints = bnset_ptr->nsetpoints;
    nsetlines  = bnset_ptr->nsetlines;

    push_boundary_nset_reset_bamg();  /* reset nset boundary data */

    for(j=0;j<nsetlines;j++) {
      nsetline_ptr = *(bnset_ptr->nsetline_ptrptr+j);
      push_boundary_nset_line_bamg(nsetline_ptr->var_name,
				    nsetline_ptr->from,
				    nsetline_ptr->to,
				    nsetline_ptr->use_flag,
				    nsetline_ptr->eq_plus,
				    nsetline_ptr->unit_points);
    }

    for(j=0;j<nsetpoints;j++) {
      nsetpoint_ptr = *(bnset_ptr->nsetpoint_ptrptr+j);
      push_boundary_nset_point_bamg(nsetpoint_ptr->var_name,
				    nsetpoint_ptr->point_name,
				    nsetpoint_ptr->iedp);
    }

    make_boundary_nset_bamg(fp,bnset_ptr->nsetno,edat_ptr);
  }


  /******************/
  /* Plot line data */
  /******************/
  for(i=0;i<bc_plots;i++) {
    PlotLine *plot_line_ptr;
    plot_line_ptr = plot_buf[i];
    make_plot_nset_bamg(edat_ptr,fp,
			plot_line_ptr->plotlineno,
			plot_line_ptr->segments,
			plot_line_ptr->from_ptrptr,
			plot_line_ptr->to_ptrptr);
  }
			
    
  return;
}



