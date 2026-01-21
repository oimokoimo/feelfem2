/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *  make filset.f routine
 *
 */
#include <stdio.h>
#include "../system/system.h"
#include "../feel_def/feel_def.h"
#include "../parallel/parallel.h"

static char *src1[] = {
    "      io_in     = 10",
    "      io_out    = 12",
    "      io_stderr =  7",
    "      open(unit=io_stderr,file='/dev/tty',status='UNKNOWN')",
    "      call closefil(io_stderr)",
    "c",
    NULL
  };

static char *src1_web[] = {
    "      io_in     = 10",
    "      io_out    = 12",
    "      io_stderr =  7",
    "      open(unit=io_stderr,file='/dev/null',status='UNKNOWN')",
    "      call closefil(io_stderr)",
    "c",
    NULL
  };

static char *src1_win[] = {
    "      io_in     = 10",
    "      io_out    = 12",
    "      io_stderr =  7",
    "      open(unit=io_stderr,file='ERROR.log',status='UNKNOWN')",
    "      call closefil(io_stderr)",
    "c",
    NULL
  };




static char *src2[] = {
    "c",
    "      io_edat = io_out  + 1",
    "      io_node = io_edat + MAX_EDATSET",
    "      io_num  = io_node + MAX_NODESET",
    "      io_fem  = io_num  + MAX_NUMSET*0 +1",
    "      io_tmp  = io_fem  + MAX_SOLVE *0 +1",       
    "*",
    "      call rep_head",
    "c---------------------------------------",
    "      return",
    "      end",
    NULL
  };



make_filset()
{
    FILE *fp;
    int i;

    StoreMakefile(FILSET,SYSTEM_LIBRARY);
    if(LIMIT_FILE == 1) return;

    fp = OpenFileToWrite(FILSET);


    fprintf(fp,"      subroutine %s\n",PROG_FILSET);

    CopyRight(fp);
    TimeStamp(fp);

    real8(fp);
    common_parameters(fp);

    CommonBlock(fp);
    comment1(fp);

    /*----------------------------------*/
    if(web_mode) {
	for(i=0;src1_web[i] != NULL;i++) {
	    fprintf(fp,"%s\n",src1_web[i]);
	}
    }
    else {
	if(MACHINE == Windows) {
	for(i=0;src1_win[i] != NULL;i++) {
	    fprintf(fp,"%s\n",src1_win[i]);
        }}
	else {
	for(i=0;src1[i] != NULL;i++) {
	    fprintf(fp,"%s\n",src1[i]);
	}}
    }
    
    /*----------------------------------*/
    fprintf(fp,"      open(unit=io_in,status='old',file='%s')\n",INPUT_FILE);
    fprintf(fp,"      call closefil(io_in)\n");
    fprintf(fp,"      open(unit=io_out,file='%s',status='UNKNOWN')\n",OUTPUT_FILE);
    fprintf(fp,"      call closefil(io_out)\n");

    /*----------------------------------*/

    for(i=0;src2[i] != NULL;i++) {
	fprintf(fp,"%s\n",src2[i]);
    }

    CloseFile(fp);
    return;
}
