/*
 * Read element data for full mesh 
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

int strindex(const char *,const char *);

int *ReadEdatVertices( int &etype ,int &nelem)
{
  FILE *fp;
  char  buf[BUFSIZ];
  
  fp = fopen("bamg.mesh","r");
  if(fp == NULL ) {
    fprintf(stderr,"Cannot open bamg.mesh to read.\n");
    exit(1);
  }


  etype = 0;
  while(fgets(buf,sizeof(buf),fp)) {

    // Triangles?
    if(strindex(buf,"Triangles")) {
      fgets(buf,sizeof(buf),fp);
      sscanf(buf,"%d",&nelem);
      if(nelem < 1) {
	fprintf(stderr,"nelem is not positive number (=%d)\n",nelem);
	exit(1);
      }
      etype = 3;

      break;
    }
    
    // Quadrilaterals?
    if(strindex(buf,"Quadrilaterals")) {
      fgets(buf,sizeof(buf),fp);
      sscanf(buf,"%d",&nelem);
      if(nelem < 1) {
	fprintf(stderr,"nelem is not positive number (=%d)\n",nelem);
	exit(1);
      }
      etype = 4;

      break;
    }
  }

  if(etype != 3 && etype != 4) {
    fprintf(stderr,"Cannot find Triangles nor Quadriraterals in bamg.mesh.\n");
    exit(1);
  }

  int *ptr = new int[etype*nelem];

  if(etype == 3) {
    for(int i=0;i<nelem;i++) {
      fgets(buf,sizeof(buf),fp);
      sscanf(buf,"%d %d %d",ptr+i*etype+0,ptr+i*etype+1,ptr+i*etype+2);
    }
  }
  else {  // nur 4
    if(etype != 4) {fprintf(stderr,"etype not equal 4\n"); exit(1); }
    for(int i=0;i<nelem;i++) {
      fgets(buf,sizeof(buf),fp);
      sscanf(buf,"%d %d %d %d",ptr+i*etype+0,ptr+i*etype+1,
	                       ptr+i*etype+2,ptr+i*etype+3);
    }
  }
  return(ptr);
}

void WriteMetisMeshFile(int etype,int nelem, int *ptr)
{
  FILE *fp;

  fp = fopen("bamg.metis","w");
  if(fp == NULL) {
    fprintf(stderr,"Cannot create feel.metis to write.\n");
    exit(1);
  }

  int  metisEtype;
  switch(etype) {
  case 3:
    metisEtype = 1;
    break;
  case 4:
    metisEtype = 4;
    break;
  default:
    fprintf(stderr,"In metisEtype defining, etype is not 3 nor 4.\n");
    exit(1);
  }

  fprintf(fp,"%d %d\n",nelem,metisEtype);
  
  
  switch(etype) {
  case 3:
    for(int i=0;i<nelem;i++) {
      fprintf(fp,"%d %d %d\n",*(ptr+i*3+2),*(ptr+i*3+1),*(ptr+i*3+0));
    }
    break;

  case 4:
    for(int i=0;i<nelem;i++) {
      fprintf(fp,"%d %d %d %d\n",
	      *(ptr+i*4+3),*(ptr+i*4+2),*(ptr+i*4+1),*(ptr+i*4+0));
    }
    break;
  default:
    fprintf(stderr,"In metisEtype defining, etype is not 3 nor 4.\n");
    exit(1);
  }
  fclose(fp);

  return;
}

void main(void)
{
  int etype,nelem;
  int *ptr;

  
  ptr = ReadEdatVertices( etype , nelem);
  
  WriteMetisMeshFile(etype,nelem,ptr);

  exit(0);
}


  



