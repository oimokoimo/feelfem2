/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   read_bamg_mesh.c
 *      Date:   1997/06/03
 *   
 *  Modified:   1999/04/12  (quadrilaterals)
 *   
 *   Purpose:   read BAMG mesh data
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../system/system.h"

#include "edat.h"

#define  DBGMODE 0

int etype_WEBEXTENSION;


static int     rd_npmax; 
static int     shape;
static int     rd_np;
static int     rd_nx;
static int     rd_ne;
static int    *rd_ielem;      /* with matno */
static double *rd_x,*rd_y;
static int    *rd_type;

static int     Ngeometric_vertices;  /* Number of geometric vertices */
static int    *NAmeshV2geoV = NULL;  /* Correspondance array between
					Geometric data and mesh data */

static int       NVerticesOnGEdge;   /* Number of vertices on 
				      * geometrical edges     */
static VonGEdge *vongedge_ptr=NULL;  /* Structure pointer     */


static FEM_edat bamg_edat;

FEM_edat *get_rd_bamg_edat()
{
  bamg_edat.npmax = rd_npmax;
  bamg_edat.shape = shape;
  bamg_edat.ne    = rd_ne;
  bamg_edat.nx    = rd_nx;
  bamg_edat.np    = rd_np;
  bamg_edat.ielem = rd_ielem;
  bamg_edat.x     = rd_x;
  bamg_edat.y     = rd_y;
  bamg_edat.type  = rd_type;

  return(&bamg_edat);
}

/* VertexOnGemetricEdge */
int how_many_verticesOnGEdge()
{
  return(NVerticesOnGEdge);
}

VonGEdge *get_vongedge_ptr()
{
  if(vongedge_ptr == NULL) {
    fprintf(stderr,"Never read VertexOnGeometricEdge data\n");
    exit(1);
  }
  return(vongedge_ptr);
}


int get_rd_bamg_npmax()
{
  return(rd_npmax);
}

int get_rd_bamg_np()
{
  return(rd_np);
}
int get_rd_bamg_nx()
{
  return(rd_nx);
}
int get_rd_bamg_ne()
{
  return(rd_ne);
}
int *get_rd_bamg_ielem()
{
  return(rd_ielem);
}
double *get_rd_bamg_x()
{
  return(rd_x);
}
double *get_rd_bamg_y()
{
  return(rd_y);
}
int *get_rd_bamg_type()
{
  return(rd_type);
}



void rd_store_edat(ielem,ne,nx,np)
     int *ielem,ne,nx,np;
{
  rd_ielem =  ielem;
  rd_ne    =  ne;
  rd_nx    =  nx;
  rd_np    =  np;
  return;
}

void rd_store_node(x,y,type,npmax)
     double *x,*y;
     int    *type;
     int     npmax;
{
  rd_x    =  x;
  rd_y    =  y;
  rd_type =  type;
  rd_npmax=  npmax;
  return;
}





void read_bamg_mesh()
{
  FILE *fp;
  char key[BUFSIZ];

  void bamg_MeshVersionFormatted();
  void bamg_MeshVersionFormatted();
  void bamg_Dimension();
  void bamg_Dimension();
  void bamg_Geometry();
  void bamg_Geometry();
  void bamg_Identifier();
  void bamg_Identifier();
  void bamg_Vertices();
  void bamg_Vertices();
  void bamg_Edges();
  void bamg_Edges();
  void bamg_Triangles();
  void bamg_Triangles();
  void bamg_Quadrilaterals();
  void bamg_SubDomainFromMesh();
  void bamg_SubDomainFromMesh();
  void bamg_SubDomainFromGeom();
  void bamg_SubDomainFromGeom();
  void bamg_VertexOnGeometricVertex();
  void bamg_VertexOnGeometricEdge();
  void bamg_EdgeOnGeometricEdge();
  void bamg_EdgeOnGeometricEdge();

  void bamg_MeshSupportOfVertices();
  void bamg_IdentityOfMeshSupport();
  void bamg_VertexOnSupportEdge();
  void bamg_VertexOnSupportVertex();
  void bamg_VertexOnSupportTriangle();
  
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
  
    if(1 == strindex(key,"VertexOnSupportEdge")) {
      bamg_VertexOnSupportEdge(fp);
      continue;

    }

    if(1 == strindex(key,"VertexOnSupportVertex")) {
      bamg_VertexOnSupportVertex(fp);
      continue;

    }

    if(1 == strindex(key,"VertexOnSupportvertex")) {
      bamg_VertexOnSupportVertex(fp);
      continue;

    }


    if(1 == strindex(key,"VertexOnSupportTriangle")) {
      bamg_VertexOnSupportTriangle(fp);
      continue;

    }

    if(1 == strindex(key,"Dimension")) {
      bamg_Dimension(fp);
      continue;
    }

    if(1 == strindex(key,"MeshSupportOfVertices")) {
      bamg_MeshSupportOfVertices(fp);
      continue;
    }

    if(1 == strindex(key,"IdentityOfMeshSupport")) {
      bamg_IdentityOfMeshSupport(fp);
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
      etype_WEBEXTENSION = 3;                       /* this and below */
      continue;
    }
    
    if(1 == strindex(key,"Quadrilaterals")) {
      bamg_Quadrilaterals(fp);
      etype_WEBEXTENSION = 4;                  /* tri or rect is alternative */
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

  rd_store_node(x,y,type,vertices);

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

  shape = 3;
  
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

  rd_store_edat(vvvm,triangles,4,3);

  return;
}


void bamg_Quadrilaterals(fp)
     FILE *fp;
{
  int i;
  int quadrilaterals;
  int *vvvvm;

  shape = 4;
  
  fscanf(fp,"%d",&quadrilaterals);
  if(DBGMODE) fprintf(stderr,"Quadrilaterals = %d\n",quadrilaterals);
  
  vvvvm = (int *)malloc(sizeof(int) * 5 * quadrilaterals);
  if(vvvvm == NULL) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<quadrilaterals;i++) {
    fscanf(fp,"%d %d %d %d %d",vvvvm+(i*5),  vvvvm+(i*5)+1,vvvvm+(i*5)+2,
	                       vvvvm+(i*5)+3,vvvvm+(i*5)+4);
    if(DBGMODE) 
      fprintf(stderr,"%3d [%3d -%3d -%3d] [%2d]\n",i+1,
	      *(vvvvm+(i*5)),*(vvvvm+(i*5)+1),
	      *(vvvvm+(i*5)+2),*(vvvvm+(i*5)+3));
  }

  rd_store_edat(vvvvm,quadrilaterals,5,4);

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
  Ngeometric_vertices = vertices; 
  NAmeshV2geoV        = mno_gno;
			

  
  return;
}

int bamg_GetMeshVNfromGeoVN( geometric )
     int geometric;
{
  int i;

  if(NAmeshV2geoV == NULL) {
    fprintf(stderr,"There was no VertexOnGeometricVertex data\n");
    exit(1);
  }

  for(i=0;i<Ngeometric_vertices;i++) {
    if(*(NAmeshV2geoV+i*2+1) == geometric) {   /* CAUTION: +1 is uncertain */
      return(*(NAmeshV2geoV+i*2+0));
    }
  }
  fprintf(stderr,"No VertexOnGeometricVertex data for geometric vertex %d\n",
	  geometric);
  exit(1);
}




void bamg_VertexOnGeometricEdge(fp)
     FILE *fp;
{
  int i;
  int vertices;
  int node_no;     /* Vertex Number on Geometric Edge */
  int edge_no;     /* Geometric Edge number where this vertex is on */
  double pos;      /* Position parameter  0.0 to 1.0 in the G-edge */

  fscanf(fp,"%d",&vertices);
  if(DBGMODE) fprintf(stderr,"VertexOnGeometricEdge = %d\n",vertices);

  NVerticesOnGEdge = vertices;
  vongedge_ptr     = (VonGEdge *)malloc(sizeof(VonGEdge)*vertices);

  if(vongedge_ptr == NULL) {
    fprintf(stderr,"Cannot allocate memory in read BAMG MESH\n");
    exit(1);
  }

  for(i=0;i<vertices;i++) {
    fscanf(fp,"%d %d %lf",&node_no,&edge_no,&pos);

    if(DBGMODE) fprintf(stderr," No.[%3d] on G-Edge [%2d] in %lf\n",
			node_no,edge_no,pos);

    (vongedge_ptr+i)->node_no = node_no;
    (vongedge_ptr+i)->edge_no = edge_no;
    (vongedge_ptr+i)->pos     = pos;
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

void bamg_MeshSupportOfVertices(fp)
     FILE *fp;
{
  char buf[BUFSIZ];
  
  fscanf(fp,"%s",buf);
  if(DBGMODE) fprintf(stderr,"MeshSupportOfVertices=%s\n",buf);

  return;
}

void bamg_IdentityOfMeshSupport(fp)
     FILE *fp;
{
  char buf[BUFSIZ];
  
  fgets(buf,sizeof(buf),fp);
  fgets(buf,sizeof(buf),fp);
  if(DBGMODE) fprintf(stderr,"IdentityOfMeshSupport=%s\n",buf);

  return;
}

void bamg_VertexOnSupportEdge(fp)
     FILE *fp;
{
  int i;
  int n;
  int a,b;
  double x;

  fscanf(fp,"%d",&n);
  if(DBGMODE) fprintf(stderr,"VertexOnSupportEdge %d\n",n);
  
  for(i=0;i<n;i++) {
    fscanf(fp,"%d %d %lf",&a,&b,&x);
    if(DBGMODE) fprintf(stderr,"[%d] %d %d %lf\n",i+1,a,b,x);
  }

  return;
}

void bamg_VertexOnSupportVertex(fp)
     FILE *fp;
{
  int i;
  int n;
  int a,b;

  fscanf(fp,"%d",&n);
  if(DBGMODE) fprintf(stderr,"VertexOnSupportVertex %d\n",n);
  
  for(i=0;i<n;i++) {
    fscanf(fp,"%d %d",&a,&b);
    if(DBGMODE) fprintf(stderr,"[%d] %d %d \n",i+1,a,b);
  }

  return;
}

  

void bamg_VertexOnSupportTriangle(fp)
     FILE *fp;
{
  int i;
  int n;
  int a,b;
  double x,y;

  fscanf(fp,"%d",&n);
  if(DBGMODE) fprintf(stderr,"VertexOnSupportEdge %d\n",n);
  
  for(i=0;i<n;i++) {
    fscanf(fp,"%d %d %lf %lf",&a,&b,&x,&y);
    if(DBGMODE) fprintf(stderr,"[%d] %d %d %lf %lf\n",i+1,a,b,x,y);
  }

  return;
}

  
