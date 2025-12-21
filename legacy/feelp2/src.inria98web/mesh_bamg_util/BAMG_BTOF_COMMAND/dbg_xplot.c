#include <stdio.h>
#include "edat.h"

extern int debug_mode;

dbg_xplot_init(edat_ptr)
     FEM_edat *edat_ptr;
{
  int i,j,k;
  int npmax;

  double *x,*y;
  double xmax,xmin,ymax,ymin,r;

  if(!debug_mode) return;

  npmax = edat_ptr->npmax;
  x     = edat_ptr->x;
  y     = edat_ptr->y;

  xmax = *x;
  xmin = *x;
  ymax = *y;
  ymin = *y;

  for(i=0;i<npmax;i++) {
    if(xmax < *(x+i)) xmax = *(x+i);
    if(xmin > *(x+i)) xmin = *(x+i);
    if(ymax < *(y+i)) ymax = *(y+i);
    if(ymin > *(y+i)) ymin = *(y+i);
  }

  r = (xmax-xmin)/20.0;

  openpl();
  fspace(xmin-r,ymin-r,xmax+r,ymax+r);

  return;
}


dbg_xplot_draw_elem_no(edat_ptr,eno,nosym)
     FEM_edat *edat_ptr;
     int eno;
     int nosym;
{
  int k;
  int shape;
  double *x,*y;
  int    *ielem,np,nx,ne;

  int     nno;
  double  xx,yy;


  if(!debug_mode) return;

  x     = edat_ptr->x;
  y     = edat_ptr->y;
  ielem = edat_ptr->ielem;
  np    = edat_ptr->np;
  ne    = edat_ptr->ne;
  nx    = edat_ptr->nx;



  xx = 0.0;
  yy = 0.0;


  shape = edat_ptr->shape;
  
  nno = *(ielem+(eno-1)*nx+shape-1);
  fmove(*(x+nno-1),*(y+nno-1));
  for(k=0;k<shape;k++) {
      nno = *(ielem+(eno-1)*nx+k);
      fcont(*(x+nno-1),*(y+nno-1));


      xx = xx + *(x+nno-1);
      yy = yy + *(y+nno-1);
  }
  xx = xx / 3.0;
  yy = yy / 3.0;
  /* fnumber(xx,yy,nosym); */

  /* Draw node */
  for(k=0;k<np;k++) {
      nno = *(ielem+(eno-1)*nx+k);
      fpeke(*(x+nno-1),*(y+nno-1));

  }


  plot_flush(0);


  for(k=0;k<100000;k++) {
    xx = xx + 1.0;
  }

  return;
}



dbg_xplot_draw_nodes(edat_ptr)
     FEM_edat *edat_ptr;
{
  int k;
  int shape;
  double *x,*y;
  int    *ielem,npmax,np,nx,ne;
  int    *rcorresp;

  int     nno;

  double  xx;

  if(!debug_mode) return;

  npmax    = edat_ptr->npmax;
  x        = edat_ptr->x;
  y        = edat_ptr->y;
  ielem    = edat_ptr->ielem;
  np       = edat_ptr->np;
  ne       = edat_ptr->ne;
  nx       = edat_ptr->nx;
  rcorresp = edat_ptr->rcorresp;

  for(k=0;k<npmax;k++) {

    if(*(rcorresp+k) == 0) {
      fpeke(*(x+k),*(y+k));
    }
    else {
      fhako(*(x+k),*(y+k));
    }

    fnumber(*(x+k),*(y+k),k+1);

  }

  plot_flush(0);


  for(k=0;k<100000;k++) {
    xx = xx + 1.0;
  }

  return;
}

dbg_xplot_draw_allmesh(edat_ptr)
     FEM_edat *edat_ptr;

{
  int i,k;
  int shape;
  double *x,*y;
  int    *ielem,np,nx,ne;
  int eno;
  int     nno;
  double  xx,yy;

  if(!debug_mode) return;

  x     = edat_ptr->x;
  y     = edat_ptr->y;
  ielem = edat_ptr->ielem;
  np    = edat_ptr->np;
  ne    = edat_ptr->ne;
  nx    = edat_ptr->nx;



  xx = 0.0;
  yy = 0.0;


  shape = edat_ptr->shape;
  
  for(i=0;i<ne;i++) {
  eno=i+1;
  nno = *(ielem+(eno-1)*nx+shape-1);
  fmove(*(x+nno-1),*(y+nno-1));
  for(k=0;k<shape;k++) {
      nno = *(ielem+(eno-1)*nx+k);
      fcont(*(x+nno-1),*(y+nno-1));


      xx = xx + *(x+nno-1);
      yy = yy + *(y+nno-1);
  }
  xx = xx / 3.0;
  yy = yy / 3.0;
  /* fnumber(xx,yy,nosym); */

  }


  plot_flush(0);


  for(k=0;k<100000;k++) {
    xx = xx + 1.0;
  }

  return;
}
