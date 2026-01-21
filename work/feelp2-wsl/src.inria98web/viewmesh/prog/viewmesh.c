#include <stdio.h>

#include "../../feel_def/feel_def.h"
#include "../../mesh_comp/mesh_comp.h"

void viewmesh()
{
  int i;
  int points,edges,regions;
  double xmin,xmax,ymin,ymax;
  double dx,dy;
  Point *point_ptr;

  char buf[BUFSIZ];


  int no;

  points  = how_many_points();
  edges   = how_many_lines();
  regions = how_many_regions();

  point_ptr = get_nth_point_ptr(0);
  xmin = xmax = point_ptr->x;
  ymin = ymax = point_ptr->y;
  
  for(i=0;i<points;i++) {
    point_ptr = get_nth_point_ptr(i);
    if(xmin > point_ptr->x) xmin = point_ptr->x;
    if(ymin > point_ptr->y) ymin = point_ptr->y;
    if(xmax < point_ptr->x) xmax = point_ptr->x;
    if(ymax < point_ptr->y) ymax = point_ptr->y;
  }
  dx = xmax-xmin;
  dy = ymax-ymin;
  
  xmin = xmin - dx/20.0;
  ymin = ymin - dy/20.0;
  xmax = xmax + dx/20.0;
  ymax = ymax + dy/20.0;

  openpl();
  fspace(xmin,ymin,xmax,ymax);

  printf("------------------------------\n");
  printf("Points   %5d\n",points);
  printf("Edges    %5d\n",edges);
  printf("Regions  %5d\n",regions);


  drawpointall();
  for(i=0;i<regions;i++) {
    drawregions(i);
  }

  fprintf(stderr,"Hit window to continue\n");
  xwait();
  erase();

  for(i=0;i<regions;i++) {
    drawpointall();
    drawregions(i);
    fprintf(stderr,"REGION No. %d\n",i+1);
    fprintf(stderr,"Hit window to continue\n");
    xwait();
    erase();
  }

  drawpointall();
  for(i=0;i<regions;i++) {
    drawregions(i);
  }

  fprintf(stderr,"Hit window to continue\n");
  xwait();

}
    
   
drawpointall()
{
  int i;
  int points;
  Point *point_ptr;

  
  points = how_many_points();
  for(i=0;i<points;i++) {
    point_ptr = get_nth_point_ptr(i);

    fpeke(point_ptr->x,point_ptr->y);
    fsymbol(point_ptr->x,point_ptr->y,point_ptr->name);
  }

}

drawregions(no)
     int no;
{

  int i,j;
  int edges;
  int points;
  Point  *point_ptr;
  Region *region_ptr;
  double xmin,xmax,ymin,ymax;
  char buf[BUFSIZ];

  region_ptr = get_nth_region_ptr(no);

  edges = region_ptr->edges;
  
  for(i=0;i<edges;i++) {
    
    points = region_ptr->points[i];

    point_ptr = get_point_ptr_by_name(region_ptr->compos[i][points-1]);
    xmin = xmax = point_ptr->x;
    ymin = ymax = point_ptr->y;
    fmove(xmin,ymin);

    for(j=0;j<points;j++) {
      point_ptr = get_point_ptr_by_name(region_ptr->compos[i][j]);
      if(xmin > point_ptr->x) xmin = point_ptr->x;
      if(ymin > point_ptr->y) ymin = point_ptr->y;
      if(xmax < point_ptr->x) xmax = point_ptr->x;
      if(ymax < point_ptr->y) ymax = point_ptr->y;
      fcont(point_ptr->x,point_ptr->y);
      xwait();
    }

  }

  sprintf(buf,"Region %s",region_ptr->name);
  fsymbol((xmin+xmax)/2.0,(ymin+ymax)/2.0,buf);

  return;
}



