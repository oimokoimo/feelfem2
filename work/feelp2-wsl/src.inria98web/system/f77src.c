/*
 * FEEL system Prototype Version 2
 * 
 * File     f77src.c
 * Made     1992/09/24
 * Modified 
 * Version  0.0
 *
 * Purpose: print-out fortran source code.
 *
 */

#include <stdio.h>
#include <string.h>
#include "system.h"

static int f77src_nest_level = 0;

f77src(fp,buf)
     FILE *fp;
     char *buf;
{
    int i;
    int ret_flag;

    i        = 0;
    ret_flag = 1;

    if(f77src_nest_level == 0) {
	if(*buf != 'c') {
	    tolower_buf(buf);
	}
    }

    f77src_nest_level++;

    while(*buf) {
	if(i == 71) {
	    fprintf(fp,"\n     &");
	    f77src(fp,buf);
	    ret_flag = 0;
	    break;
	}
	fputc(*buf , fp);
	i++;
	buf++;
    }

    if(ret_flag) fputc('\n' , fp);

    f77src_nest_level--;
    return;
}
