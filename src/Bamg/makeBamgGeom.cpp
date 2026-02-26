/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : makeBamgGeom.cpp
 *  Date     : 2001/03/30
 *  Modified : 
 *  
 *  Purpose  : make a bamg geometry data file
 *  
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 */

#include <cstdio>
#include <math.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "Bamg.hpp"
#include "Point.hpp"

void Bamg::makeBamgGeom(const char *filename)
{
  
  FILE *fp;

  fp = fileOpenToWrite(filename);
  if(fp == NULL) {
    abortExit("Cannot create bamg geometry file.(file open to write failed.)");
  }

  fprintf(fp,"MeshVersionFormatted 0\n");

  /* Geometry file data */
  fprintf(fp,"# BAMG Geometry (for feelfem) created at %s\n",
	  getdate());
  
  /* Dimension */
  fprintf(fp,"Dimension\n");
  fprintf(fp,"%d\n\n",dimension);

  /* Corner definition  CAUTION: Now polygonal domain only */
  fprintf(fp,"MaximalAngleOfCorner\n");
  fprintf(fp,"%d\n\n",maximalAngleOfCorner);

  /* Vertices */
  fprintf(fp,"Vertices\n");
  fprintf(fp,"%d\n",bamgVertices);


  listIterator <BamgPoint *>itrP(bamgPointPtrLst);
  int counter;
  counter = 0;
  for(itrP.init(); !itrP ; ++itrP ) {
    counter++;
    assert(counter == itrP()->getBamgRefNo());
    
    fprintf(fp,"%lf %lf %d\n",itrP()->getX(),itrP()->getY(),
	    itrP()->getBamgRefNo());
  }
  fprintf(fp,"\n");

  /* Corner definition  CAUTION: Now polygonal domain only */
  fprintf(fp,"Corners\n%d\n",bamgVertices);
  for(int i=0;i<bamgVertices;i++) {
    fprintf(fp," %d",i+1);   /* Because isolated points follow last */
  }
  fprintf(fp,"\n");


  /* Edges */
  fprintf(fp,"Edges\n");
  fprintf(fp,"%d\n",bamgEdges);
  
  listIterator <BamgEdge *>itrE(bamgEdgePtrLst);
  for(itrE.init(); !itrE ; ++itrE) {
    BamgEdge *bePtr = itrE();
    fprintf(fp,"%d %d %d\n",  
	    bePtr->getFrom(),bePtr->getTo(),bePtr->getBamgRefNo());
  }

  /* hVertices */
  listIterator <BamgSubDomain *>itrSD(bamgSubDomainPtrLst);
  double areaOfDomain = 0.0;
  for(itrSD.init(); !itrSD; ++itrSD) {
    areaOfDomain += itrSD()->getArea();
  }

  //  cerr << "Total area = " << areaOfDomain << endl;  
  //  cerr << "specifiedVertices = " << specifiedVertices << endl;  

  double dnodes = (double)specifiedVertices;
  double dn     = sqrt(dnodes);
  double da     = areaOfDomain/(dn-1.0)/(dn-1.0)/2.0;
  double h      = sqrt(da * 4.0 / 1.7320508);


  fprintf(fp,"hVertices\n");
  for(int i=0;i<bamgVertices;i++) {
    fprintf(fp,"%lf ",h);
  }
  fprintf(fp,"\n");


  /* Bamg SubDomains */
  fprintf(fp,"SubDomain\n");
  fprintf(fp,"%d\n",bamgSubDomains);
  
  //  listIterator <BamgSubDomain *>itrSD(bamgSubDomainPtrLst);

  for(itrSD.init(); !itrSD; ++itrSD) {
    fprintf(fp,"%d %d %d %d\n",
	    itrSD()->getType(),
	    itrSD()->getEdgeRefNo(),
	    itrSD()->getDirection(),
	    itrSD()->getMatno());
  }


  // End of Bamg geometry file
  fprintf(fp,"End\n");      // end of BAMG.GEOM

  fclose(fp);
  return;
}

  //

  //    if(wrt_flag == 0) {
  //      fprintf(fp," %lf",bamg.initial_h);
  //    }
  //
  //  }
  //  fprintf(fp,"\n\n");
  //
  //
  //  /* SubDomain */
  //  fprintf(fp,"SubDomain\n");
  //  fprintf(fp,"%d\n",bamg.SubDomains);
  //  for(i=0;i<bamg.SubDomains;i++) {
  //    fprintf(fp,"%d %d %d %d\n",
  //	    *(bamg.Sub_type+i),*(bamg.Sub_ref+i),
  //	    *(bamg.Sub_dir+i), *(bamg.Sub_no+i));
  //  }
  //  fprintf(fp,"\n");
  //
  //	    
  //  fprintf(fp,"End\n");      // end of BAMG.GEOM
  //
  //  return;
  //
  //}
  //
  //
  //  
  //
  //void set_bamg_info_etype( etype )
  //     int etype;
  //{
  //  if(etype != TRI && etype != RECT) {
  //    SystemAbort("Now only triangle is allowd with -bamg option");
  //  }
  //
  //  bamg.element_type = etype +1 ;  /* CAUTION!!!!!!!!!!!!!!*/
  //
  //
  //  return;
  //}
  //
  //
  ///* Calculation of the initial mesh size */
  //void set_bamg_info_nodes( total_area, nodes )
  //     double total_area;
  //     int    nodes;
  //{
  //  double dnodes,n,elements;
  //  double da;
  //  double h;
  //  double sqrt();
  //
  //  dnodes = (double)nodes;
  //  n      = sqrt(dnodes);
  //
  //  da     = total_area/(n-1.0)/(n-1.0)/2.0;
  //
  //  h      = sqrt(da * 4.0 / 1.7320508);
  //
  //  bamg.initial_h            = h;
  //
  //  return;
  //}
  //
  //
  //void set_bamg_info_vertices_init( total_points , edge_points)
  //     int total_points;
  //     int edge_points;
  //{
  //  if(total_points <0 || total_points >9000000) {
  //    fprintf(stderr,"Illegal total_points %d\n",total_points);
  //    exit(1);
  //  }
  //
  //  bamg.Vertices = total_points;
  //  bamg.Corners  = edge_points;    /* THIS MEANS ONLY POLYGONAL DOMAIN ALLOWD */
  //  /* CAUTION: */
  //  bamg.Corners  = total_points;   /* For refine isolated points 97/12/12 */
  //  
  //  bamg.Vert_x = (double *)malloc(sizeof(double)*total_points);
  //  bamg.Vert_y = (double *)malloc(sizeof(double)*total_points);
  //  bamg.Vert_n = (int    *)malloc(sizeof(int   )*total_points);
  //
  //  if(bamg.Vert_x == NULL || bamg.Vert_y == NULL || bamg.Vert_n == NULL) {
  //    fprintf(stderr,"Cannot allocate memory in set_bamg_info_vertices_init\n");
  //    exit(1);
  //  }
  //  
  //  return;
  //}
  //
  //
  //
  //void set_bamg_info_vertices(no,x,y,type)
  //     int no;       /* number      */
  //     double x,y;   /* coordinates */
  //     int type;     /* point type  */
  //{
  //  if(no > bamg.Vertices || no <1) {
  //    SystemAbort("Illegal vertex number in set_bamg_info_vertices");
  //  }
  //  
  //  *(bamg.Vert_x + (no-1)) = x;
  //  *(bamg.Vert_y + (no-1)) = y;
  //  *(bamg.Vert_n + (no-1)) = type;
  //
  //  return;
  //}
  //
  //
  //void bamg_make_edge_info_init(app_edges)
  //     int app_edges;
  //{
  //  bamg_edge.app_edges = app_edges;
  //  bamg_edge.edges = 0;
  //
  //  bamg_edge.from  = (int *)malloc(sizeof(int)*app_edges);
  //  bamg_edge.to    = (int *)malloc(sizeof(int)*app_edges);
  //  bamg_edge.etype = (int *)malloc(sizeof(int)*app_edges);
  //
  //  if(bamg_edge.from  == NULL || bamg_edge.to == NULL ||
  //     bamg_edge.etype == NULL                            ) {
  //    SystemAbort("bamg_make_edge_info_init");
  //  }
  //  return;
  //}
  //
  //
  //void bamg_make_edge_info_store(from,to)
  //     int from,to;
  //{
  //  int i;
  //  int swap;
  //
  //  if(from > to ) {
  //    swap = from;
  //    from = to;
  //    to   = swap;
  //  }
  //
  //  for(i=0;i<bamg_edge.edges;i++) {
  //    if(*(bamg_edge.from + i) == from && *(bamg_edge.to + i) == to) return;
  //  }
  //  
  //  /* This means new edge detected */
  //
  //  if(bamg_edge.edges + 1 >= bamg_edge.app_edges) {
  //    SystemAbort("Illegal in void bamg_make_edge_info_store(from,to)");
  //  }
  //
  //  *(bamg_edge.from  + bamg_edge.edges) = from;
  //  *(bamg_edge.to    + bamg_edge.edges) = to  ;
  //  *(bamg_edge.etype + bamg_edge.edges) = bamg_edge.edges+1;  /* edge number */
  // 
  //  bamg_edge.edges = bamg_edge.edges + 1;
  //
  //  return;
  //}
  //
  //void make_bamg_geom_edges()
  //{
  //  int i;
  //
  //  bamg.Edges = bamg_edge.edges;
  //
  //  bamg.Edge_1 = (int *)malloc(sizeof(int)*bamg.Edges);
  //  bamg.Edge_2 = (int *)malloc(sizeof(int)*bamg.Edges);
  //  bamg.Edge_n = (int *)malloc(sizeof(int)*bamg.Edges);
  //
  //  if(bamg.Edge_1 == NULL || bamg.Edge_2 == NULL || bamg.Edge_n == NULL) {
  //    SystemAbort("Cannot allocate memory in make_bamg_geom_edges");
  //  }
  //
  //
  //  for(i=0;i<bamg_edge.edges;i++) {
  //    *(bamg.Edge_1+i) = *(bamg_edge.from  + i);
  //    *(bamg.Edge_2+i) = *(bamg_edge.to    + i);
  //    *(bamg.Edge_n+i) = *(bamg_edge.etype + i);
  //  }
  //
  //  return;
  //}
  //
  //void make_bamg_subdomain_info_init(subdomains)
  //     int subdomains;
  //{
  //  bamg.SubDomains = subdomains;
  //
  //  bamg.Sub_type   = (int *)malloc(sizeof(int)*subdomains);
  //  bamg.Sub_ref    = (int *)malloc(sizeof(int)*subdomains);
  //  bamg.Sub_dir    = (int *)malloc(sizeof(int)*subdomains);
  //  bamg.Sub_no     = (int *)malloc(sizeof(int)*subdomains);
  //
  //  if(bamg.Sub_type == NULL || bamg.Sub_ref == NULL ||
  //     bamg.Sub_dir  == NULL || bamg.Sub_no  == NULL    ) {
  //    SystemAbort("Cannot allocate memory in make_bamg_subdomain_info_init");
  //  }
  //
  //  return;
  //}
  //
  //
  //void set_bamg_info_subdomains(subno,matno,from,to)
  //     int subno,matno,from,to;   /* generally subno == matno */
  //{
  //  int i,type,ref,dir,no;
  //  int swap;
  //
  //  if(subno != matno) SystemAbort("Illegal subno/matno");
  //
  //  ref = -1;
  //  
  //  /* dir  */
  //  if(from > to) {
  //    dir  = -1;
  //    swap = from;
  //    from = to;
  //    to   = swap;
  //  }
  //  else {
  //    dir =   1;
  //  }
  //
  //  /* type */
  //  type = 2;   /* LINE only */
  //
  //  /* ref  */
  //  for(i=0;i<bamg_edge.edges;i++) {
  //    if(*(bamg_edge.from + i) == from && *(bamg_edge.to + i) == to) {
  //      ref = i+1;   /* This means edge number */
  //    }
  //  }
  //
  //  if(ref == -1) {
  //    SystemAbort("Illegal number in set_bamg_info_subdomains");
  //  }
  //
  //  /* no   */
  //  no = matno;
  //
  //
  //  *(bamg.Sub_type + (subno-1)) = type;
  //  *(bamg.Sub_ref  + (subno-1)) = ref;
  //  *(bamg.Sub_dir  + (subno-1)) = dir;
  //  *(bamg.Sub_no   + (subno-1)) = no;
  //
  //  return;
  //}
  //
  //void bamg_geometric_edge_wrt(fp)
  //  FILE *fp;
  //{
  //  int i;
  //  fprintf(fp,"%d\n",bamg.Edges);
  //  for(i=0;i<bamg.Edges;i++) {
  //    fprintf(fp,"%d %d\n",
  //      *(bamg.Edge_1+i), *(bamg.Edge_2+i));
  //  }
  //}
  //
                 
