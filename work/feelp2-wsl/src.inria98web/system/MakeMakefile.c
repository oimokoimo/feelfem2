/*
 *   FEEL system  MakeMakefile.c
 *  
 *   Make Makefile 
 *
 *  Last Modified 1998/09/03  Justify avs interface routine
 *
 *
 */
#include <stdio.h>
#include <string.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../system/system.h"
#include "../var_comp/var_comp.h"
#include "../parallel/parallel.h"


static char *object_file_name[MAX_FILES];
static int   object_file_type[MAX_FILES];
static int   files = 0;
static FILE *Makefile_fp;
static char *exe_name = EXENAME;

static int   xlib_nsis_flag = YES;    /* 渡部氏作成のルーチン利用フラグ */
static int   x11_flag     = NO;      /* X11ライブラリ利用フラグ        */

static int   mpi_flag       = NO;    /* MPI ルーチン */
extern int   one_file;

void UseLibrary( item , lib_name)
     int item;
     char *lib_name;
{
    switch(item) {
	
      case MPP_SOLVER:
	mpi_flag = YES;
	xlib_nsis_flag = YES;    /* libpfeelG.a をリンクする */
	break;

      case ITERATIVE_SOLVER:
	xlib_nsis_flag = YES;
	break;

      case CONTOUR:
	xlib_nsis_flag = YES;
	x11_flag     = YES;
	break;

      case DISPLACEMENT:
	xlib_nsis_flag = YES;
	x11_flag     = YES;
	break;

      case SHOWVEC:
	xlib_nsis_flag = YES;
	x11_flag     = YES;
	break;

      case PERSPECT:
	xlib_nsis_flag = YES;
	x11_flag     = YES;
	break;

      case XPLOT:
	xlib_nsis_flag = YES;
	x11_flag     = YES;
	break;

      default:
	SystemWarning_s("IGNORE Library %s",lib_name);
	break;
    }

    return;
}

void InitMakeMakefile()
{
    files = 0;

    return;
}

void StoreMakefile( name , file_type )
     char *name;
     int   file_type;
{
    if(files == MAX_FILES) {
	StoreMakefileWarning("Too many files for Makefile\n");
	return;
    }

    if(one_file == YES) {
	files = 2;
	object_file_name[0] = "feel_main.f";
	object_file_name[1] = "feelgo.f";
	return;
    }

    object_file_name[files] = MakeStringCopy( name );
    object_file_type[files] = file_type;

    files ++;

    return;
}


void JustifyFORTfile()
{
    int i;
    for(i=0;i<files;i++) {
	if(LIMIT_FILE == 1 && object_file_type[i] == SYSTEM_LIBRARY) continue;
	MakeFORTsrc( object_file_name[i] );
    }

    if(avs_mode) {
      MakeFORTsrc( DEFAULT_AVS_MODULE_FILE );
    }

    return;
}


void MakeMakefile()
{
    FILE *fp;
    char *cp;
    int i;
    int userfuncs;

    fp = OpenFileToWrite("Makefile");

/*    fprintf(fp,"all: %s\n",exe_name); */

    /*-----------------------------*/
    /* FORTRANコンパイルオプション */
    /*-----------------------------*/
    fprintf(fp,"FFLAGS = ");

    switch( MACHINE ) {
      case EWS4800_R4000:
	fprintf(fp," -Kmips2"); 
	break;

      case IRIS:
	fprintf(fp," -Nn32000");
        break;
   
      case Linux:
        fprintf(fp," -fallow-argument-mismatch");
        break;

      default:
	break;
    }
    fprintf(fp,"\n");

    /* Cenju-3 Option */
    if(parallel) {
	fprintf(fp,"FC = cjf77 -O -KOlimit=3000 -Kmips2\n");
    }
    
			 
    fprintf(fp,"%s: ",exe_name);
    for(i=0;i<files;i++) {
	cp = 	MakeStringCopy(object_file_name[i]);
	*(cp + strlen(cp) -1) = 'o';
	fprintf(fp,"%s ",cp);
    }

    /* ユーザ指定関数名 */
    userfuncs = how_many_userfuncs();
    for(i=0;i<userfuncs;i++) {
	fprintf(fp,"%s.o",get_nth_userfunc_name(i));
    }

    fprintf(fp,"\n");


    /* Makefile第２行 */
    if(parallel) {
	fprintf(fp,"%ccjf77 ",9);
    }
    else {
	fprintf(fp,"%cf77 ",9);
    }


    /* EWSの場合はDynamic LINKを指定する */
    switch( MACHINE ) {
      case EWS4800_R4000:
      case EWS4800:
	fprintf(fp," -dn "); 
	break;
	
      default:
	break;
    }

    fprintf(fp,"-o %s ",exe_name);
    for(i=0;i<files;i++) {
        cp =    MakeStringCopy(object_file_name[i]);
       *(cp + strlen(cp) -1) = 'o';
	fprintf(fp,"%s ",cp);
    }

    for(i=0;i<userfuncs;i++) {
	fprintf(fp,"%s.o",get_nth_userfunc_name(i));
    }
    /* ここにライブラリを書く */
    if(xlib_nsis_flag == YES) {
	switch( MACHINE ) {
	  case EWS4800:
	    fprintf(fp," %s",EWS4800_CONTOUR_LIB);
	    break;

	  case EWS4800_R4000:
	    fprintf(fp," %s",EWS4800_R4000_CONTOUR_LIB);
	    break;
	    
	  case CONVEX: 
	    fprintf(fp," %s",CONVEX_CONTOUR_LIB);
	    break;

	  case IRIS:
	    fprintf(fp," %s",IRIS_CONTOUR_LIB);
	    break;

          case DEC_ALPHA:
	    fprintf(fp," %s",DEC_ALPHA_CONTOUR_LIB);
	    break;
 
	  case SPARC:
	    fprintf(fp," %s",SPARC_CONTOUR_LIB);
	    break;
   
	  case FreeBSD:
	    fprintf(fp," %s",FreeBSD_CONTOUR_LIB);
	    break;

          case Linux:
	    fprintf(fp," %s",Linux_CONTOUR_LIB);
            break;


	  case CENJU3:
	    fprintf(fp," %s",Cenju3_CONTOUR_LIB);
	    break;

          case HP700:
            fprintf(fp," %s",HP700_CONTOUR_LIB);
            break; 

	  default:
	    SystemWarning("Ignore feelG library call.");
	}
    }


    /* MPI ライブラリのlink */
    if(mpi_flag == YES) {
	switch( MACHINE ) {
	  case CENJU3:
	    fprintf(fp," %s",Cenju3_MPI_LIB);
	    break;

	  default:
	    SystemWarning("MPI library is available for Cenju-3 only");
	    break;
	}
    }


    if(x11_flag == YES) {
	switch( MACHINE ) {
	  case EWS4800:
	  case EWS4800_R4000:
	    fprintf(fp," %s",EWS4800_X11_LIB);
	    break;

	  case CONVEX:
	    fprintf(fp," %s",CONVEX_X11_LIB);
	    break;

	  case IRIS:
	    fprintf(fp," %s",IRIS_X11_LIB);
	    break;

	  case SPARC:
	    fprintf(fp," %s",SPARC_X11_LIB);
	    break;

          case DEC_ALPHA:
	    fprintf(fp," %s",DEC_ALPHA_X11_LIB);
	    break;

          case FreeBSD:
	    fprintf(fp," %s",FreeBSD_X11_LIB);
	    break;

          case Linux:
	    fprintf(fp," %s",Linux_X11_LIB);
	    break;

	  case CENJU3:
	    SystemWarning("X is not available in Cenju-3");
	    break;

          case HP700:
            fprintf(fp," %s",HP700_X11_LIB);
            break;

	  default:
	    SystemWarning("Ignore X11 library call.");
	}
    }

    
    fprintf(fp,"\n");

    CloseFile(fp);
    return;
}

	
int is_x11_flag()
{
    return(x11_flag);
}
