/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_FileManage.c
 *      Date:   1998/11/02
 *   
 *   Purpose:   File Open/Write/Close Manager for Modulef routines
 *   
 *   
 *             FILE *mfFileWriteOpen( name , code) 
 *             void  mfFileClose(fp)
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../modulef_def/modulef_def.h"

static FILE *fp_current = NULL;



static int   mf_files = 0;
static char *mf_file_name[MF_MAX_FILES];
static int   mf_file_code[MF_MAX_FILES];

void mfPushFilename_et_code( name , code)
     char *name;
{
  char *MakeStringCopy();

  if(mf_files == MF_MAX_FILES) {
    SystemAbort("Inner error, try to make too many files(mfPushFilename)");
  }

  mf_file_name[ mf_files ] = MakeStringCopy( name );
  mf_file_code[ mf_files ] = code;

  mf_files++;

  return;
}
  


FILE *mfFileWriteOpen( name , code) 
     char *name;
     int   code;
     
{
  FILE *fp;

  fp = fopen(name,"w");
  if(fp == NULL) {
    SystemAbort("Cannot create file.(mfFileWriteOpen)");
  }

  mfPushFilename_et_code( name , code );

  fp_current = fp;  

  return(fp);
}


void mfFileClose(fp)
     FILE *fp;
{
  fclose(fp);   /* now do nothing, just close the file
		   every source code are separate file */

  return;
}


void mf_wrt_objname(fp, name)
     FILE *fp;
     char *name;
{
  int  len;
  char buf[BUFSIZ];

  len = strlen(name);
  
  if(*(name + len-1) != 'f' || *(name + len-2) != '.')  {
    SystemAbort("Not Fortran file in mf_wrt_objname");
  }
  
  sprintf(buf,"%s",name);
  buf[len-1] = 'o';

  fprintf(fp,"%s",buf);

  return;
}

void mfMakeMakefile()
{
  int    i,j;
  FILE *fp;
  
  fp = fopen("Makefile","w");
  if(fp == NULL) {
    fprintf(stderr,"Cannot create Makefile\n");
    return;
  }


  /* PROG = */
  fprintf(fp,"PROG   = feelgo\n");
  
  
  /* OBJS = */
  j = 0;
  fprintf(fp,"OBJS   = ");

  for(i=0;i<mf_files;i++) {

    mf_wrt_objname(fp,mf_file_name[i]);
    fprintf(fp," ");

    j++;
    if(j == 5) {
      j = 0;
      if(i != mf_files-1) fprintf(fp," \\\n         ");
    }
  }
  fprintf(fp,"\n");

  fprintf(fp,"F77    = f77\n");
  fprintf(fp,"CC     = cc\n");
  fprintf(fp,"LINK   = f77\n");
  fprintf(fp,"FFLAGS = \n");
  fprintf(fp,"CFLAGS = \n");

  fprintf(fp,"\n");

  fprintf(fp,"MDLIB  = -L%s\n",MF_LIBRALY_DIRECTORY);

  fprintf(fp,".SUFFIXES: .o .f .c\n");
  fprintf(fp,"\n");

  fprintf(fp,"$(PROG) : $(OBJS)\n");

  fprintf(fp,"\t$(LINK) -o $(PROG) ($OBJS) $(OBJS) $(MDLIB) -lconw -lconv -lcosd -lelas -lelcp -lpiez -lther -lela2 -lela3 -lpoba -lutsd -lzzzz_mod -lblas_mod -lutii -lu_linux $(BLAS2)  $(STDLIB) \n");
  
  fprintf(fp,"\n");

  fprintf(fp,".f.o:\n");
  fprintf(fp,"\t$(F77) $(FFLAGS) -c $<\n");
  fprintf(fp,".c.o:\n");
  fprintf(fp,"\t$(CC)  $(CFLAGS) -c $<\n");
  fprintf(fp,"\n");

  fprintf(fp,"clean:\n");
  fprintf(fp,"\trm $(PROG) *.o\n");

  fclose(fp);

  return;
}


 
    






