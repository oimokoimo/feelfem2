/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   read_bamg_mesh.c
 *      Date:   1997/06/03
 *   
 *   Purpose:   read BAMG mesh data
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

#define  DBGMODE 1

void read_bamg_mesh()
{
  FILE *fp;
  char key[BUFSIZ];

  
  fp = fopen(BAMG_MESH_FILE,"r");
  if(fp == NULL) {
    fprintf(stderr,"Cannot open %s.\n",BAMG_MESH_FILE);
    exit(1);
  }

  
  while(fscanf(fp,"%s",key) != EOF) {

    if(1 == strindex(key,"MeshVersionFormatted")) {
      bamg_MeshVersionFormatted(fp);
      continue;

    }
    if(1 == strindex(key,"Dimension")) {
      bamg_Dimension(fp);
      continue;
    }

    if(1 == strindex(key,"Identifier")) {
      bamg_Identifier(fp);
      continue;
    }

    if(1 == strindex(key,"Geometry")) {
      bamg_Geometry(fp);
      continue;
    }

    if(1 == strindex(key,"Vertices")) {
      bamg_Vertices(fp);
      continue;
    }

    if(1 == strindex(key,"Edges")) {
      bamg_Edges(fp);
      continue;
    }

    if(1 == strindex(key,"End")){
      fclose(fp);
      return;
    }

    if(1 == strindex(key,"Triangles")) {
      bamg_Triangles(fp);
      continue;
    }

    if(1 == strindex(key,"SubDomainFromMesh")) {
      bamg_SubDomainFromMesh(fp);
      continue;
    }

    if(1 == strindex(key,"SubDomainFromGeom")) {
      bamg_SubDomainFromGeom(fp);
      continue;
    }

    if(1 == strindex(key,"VertexOnGeometricVertex")) {
      bamg_VertexOnGeometricVertex(fp);
      continue;
    }

    if(1 == strindex(key,"VertexOnGeometricEdge")) {
      bamg_VertexOnGeometricEdge(fp);
      continue;
    }
    
    if(1 == strindex(key,"EdgeOnGeometricEdge")) {
      bamg_EdgeOnGeometricEdge(fp);
      continue;
    }


    /* END OF BAMG mesh data */ 
    if(1 == strindex(key,"End")){
      fclose(fp);
      return;
    }

    /* UNKNOWN keyword */
    fprintf(stderr,"Not supported BAMG keyword [%s]\n",key);
  }


  fprintf(stderr,"Unexpected end of file for BAMG mesh\n");
  fclose(fp);
  exit(1);


}

void bamg_MeshVersionFormatted(fp)
     FILE *fp;
{
  int version;

  fscanf(fp,"%d",&version);
  if(DBGMODE) fprintf(stderr,"Version = %d\n",version);

  return;
}

void bamg_Dimension(fp)
     FILE *fp;
{
  int dimension;
  
  fscanf(fp,"%d",&dimension);
  if(DBGMODE) fprintf(stderr,"Dimension = %d\n",dimension);

  return;
}

void bamg_Geometry(fp)
     FILE *fp;
{
  char buf[BUFSIZ];
  fgets(buf,sizeof(buf),fp);
  fgets(buf,sizeof(buf),fp);
  if(DBGMODE) fprintf(stderr,"Geometry = %s\n",buf);
  return;
}

void bamg_Identifier(fp)
     FILE *fp;
{
  char buf[BUFSIZ];
  fgets(buf,sizeof(buf),fp);
  fgets(buf,sizeof(buf),fp);
  if(DBGMODE) fprintf(stderr,"Identifier = %s\n",buf);
  return;
}


void bamg_Vertices(fp)
     FILE *fp;
{
  int i;
  int vertices;
  double *x,*y;
  int *type;


  fscanf(fp,"%d",&vertices);
  if(DBGMODE) fprintf(stderr,"Vertices = %d\n",vertices);

  x    = (double *)malloc(sizeof(double) * vertices);  
  y    = (double *)malloc(sizeof(double) * vertices);
  type = (int    *)malloc(sizeof(int   ) * vertices);

  if(x == NULL || y == NULL || type == NULL) {
    if(DBGMODE) fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<vertices;i++) {
    fscanf(fp,"%lf %lf %d",x+i,y+i,type+i);

    if(DBGMODE) fprintf(stderr,"No.%3d (%lf,%lf) [%2d]\n",i+1,*(x+i),*(y+i),*(type+i));
  }

  return;
}

void bamg_Edges(fp)
     FILE *fp;
{
  int i;
  int edges;
  int *from,*to,*type;

  fscanf(fp,"%d",&edges);
  if(DBGMODE) fprintf(stderr,"Edges = %d\n",edges);

  from = (int *)malloc(sizeof(int) * edges);  
  to   = (int *)malloc(sizeof(int) * edges);
  type = (int *)malloc(sizeof(int) * edges);

  if(from == NULL || to == NULL || type == NULL) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }  

  for(i=0;i<edges;i++) {
    fscanf(fp,"%d %d %d",from+i,to+i,type+i);

    if(DBGMODE) fprintf(stderr,"No.%3d   (%3d,%3d)  [%2d]\n",i+1,*(from+i),*(to+i),*(type+i));
  }

  return;
}  

void bamg_Triangles(fp)
     FILE *fp;
{
  int i;
  int triangles;
  int *vvvm;
  
  fscanf(fp,"%d",&triangles);
  if(DBGMODE) fprintf(stderr,"Triangles = %d\n",triangles);
  
  vvvm = (int *)malloc(sizeof(int) * 4 * triangles);
  if(vvvm == NULL) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<triangles;i++) {
    fscanf(fp,"%d %d %d %d",vvvm+(i*4),vvvm+(i*4)+1,vvvm+(i*4)+2,vvvm+(i*4)+3);
    if(DBGMODE) 
      fprintf(stderr,"%3d [%3d -%3d -%3d] [%2d]\n",i+1,
	      *(vvvm+(i*4)),*(vvvm+(i*4)+1),*(vvvm+(i*4)+2),*(vvvm+(i*4)+3));
  }

  return;
}



void bamg_SubDomainFromMesh(fp)
     FILE *fp;
{

  /* Be CAREFUL,  This is from GENERATED MESH  */

  int i;
  int subdomains;
  int *tndm;       /* type,number,direction,matno */

  
  fscanf(fp,"%d",&subdomains);
  if(DBGMODE) fprintf(stderr,"SubdomainsFromMesh = %d\n",subdomains);

  tndm = (int *)malloc(sizeof(int) * 4 * subdomains);
  if(tndm == NULL) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<subdomains;i++) {
    fscanf(fp,"%d %d %d %d",tndm+(i*4),tndm+(i*4)+1,tndm+(i*4)+2,tndm+(i*4)+3);
    if(DBGMODE) 
      fprintf(stderr,"%3d type [%d] No.%3d Direction %d  matno[%d]\n",i+1,
	      *(tndm+(i*4)),*(tndm+(i*4)+1),*(tndm+(i*4)+2),*(tndm+(i*4)+3));
  }
}

void bamg_SubDomainFromGeom(fp)
     FILE *fp;
{

  /* Be CAREFUL,  This is from GEOMETRY  */
  
  int i;
  int subdomains;
  int *tndm;       /* type,number,direction,matno */

  
  fscanf(fp,"%d",&subdomains);
  if(DBGMODE) fprintf(stderr,"SubdomainsFromGeom = %d\n",subdomains);

  tndm = (int *)malloc(sizeof(int) * 4 * subdomains);
  if(tndm == NULL) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<subdomains;i++) {
    fscanf(fp,"%d %d %d %d",tndm+(i*4),tndm+(i*4)+1,tndm+(i*4)+2,tndm+(i*4)+3);
    if(DBGMODE) 
      fprintf(stderr,"%3d type [%d] No.%3d Direction %d  matno[%d]\n",i+1,
	      *(tndm+(i*4)),*(tndm+(i*4)+1),*(tndm+(i*4)+2),*(tndm+(i*4)+3));
  }
}

void bamg_VertexOnGeometricVertex(fp)
     FILE *fp;
{
  int i;
  int vertices;
  int *mno_gno;     /* Number in mesh  to Number in Geometry */
  
  fscanf(fp,"%d",&vertices);
  if(DBGMODE) fprintf(stderr,"VertexOnGeometricVertex = %d\n",vertices);
  
  mno_gno = (int *)malloc(sizeof(int) * 2 * vertices);
  if(mno_gno == NULL) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<vertices;i++) {
    fscanf(fp,"%d %d",mno_gno+(i*2),mno_gno+(i*2+1));
    if(DBGMODE) fprintf(stderr," No in Mesh [%3d] -> No. in Geom [%3d]\n",
			*(mno_gno+(i*2)),*(mno_gno+(i*2+1)));
  }
  
  return;
}

void bamg_VertexOnGeometricEdge(fp)
     FILE *fp;
{
  int i;
  int vertices;
  int *no_geno;    /* Vertex Number vs Edge number in Geometry     */
  double *pos;     /* Position parameter  0.0 to 1.0 in the G-edge */

  fscanf(fp,"%d",&vertices);
  if(DBGMODE) fprintf(stderr,"VertexOnGeometricEdge = %d\n",vertices);

  no_geno = (int    *)malloc(sizeof(int)    * 2 * vertices);
  pos     = (double *)malloc(sizeof(double) *     vertices);

  if(no_geno == NULL || pos == NULL) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<vertices;i++) {
    fscanf(fp,"%d %d %lf",no_geno+(i*2),no_geno+(i*2+1),pos+i);
    if(DBGMODE) fprintf(stderr," No.[%3d] on G-Edge [%2d] in %lf\n",
			*(no_geno+(i*2)),*(no_geno+(i*2+1)),*(pos+i));
  }

  return;
}

void bamg_EdgeOnGeometricEdge(fp)
     FILE *fp;
{
  int i;
  int edges;
  int *meno_geno;  /* Mesh edge number vs Geom edge number */

  fscanf(fp,"%d",&edges);
  if(DBGMODE) fprintf(stderr,"EdgeOnGeometricEdge = %d\n",edges);

  meno_geno = (int *)malloc(sizeof(int)    * 2 * edges);

  if(meno_geno == NULL ) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<edges;i++) {
    fscanf(fp,"%d %d",meno_geno+(i*2),meno_geno+(i*2+1));
    if(DBGMODE) fprintf(stderr," Edge No.[%3d] on G-Edge [%2d]\n",
			*(meno_geno+(i*2)),*(meno_geno+(i*2+1)));
  }

  return;  
}

  

void main()
{
  read_bamg_mesh();
  fprintf(stderr,"TERMINATE NORMALLY\n");
}
