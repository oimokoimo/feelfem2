/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   LISP_SEND.c
 *      Date:   1993/12/2 
 *   
 *   Purpose:   LISPプログラムに
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"


void LISP_SEND(fp,s)
     FILE *fp;
     char *s;
{
    if(status_lisp_debug) {
	fprintf(lisp_debug_fp,s);
    }
    fprintf(fp,s);
    return;
}

void LISP_SEND_d(fp,s,d)
     FILE *fp;
     char *s;
     int   d;
{
    if(status_lisp_debug) {
	fprintf(lisp_debug_fp,s,d);
    }
    fprintf(fp,s,d);
    return;
}


void LISP_SEND_dd(fp,s,d1,d2)
     FILE *fp;
     char *s;
     int   d1,d2;
{
    if(status_lisp_debug) {
	fprintf(lisp_debug_fp,s,d1,d2);
    }
    fprintf(fp,s,d1,d2);
    return;
}

void LISP_SEND_ddd(fp,s,d1,d2,d3)
     FILE *fp;
     char *s;
     int   d1,d2,d3;
{
    if(status_lisp_debug) {
	fprintf(lisp_debug_fp,s,d1,d2,d3);
    }
    fprintf(fp,s,d1,d2,d3);
    return;
}

void LISP_SEND_s(fp,s,s1)
     FILE *fp;
     char *s;
     char *s1;
{
    if(status_lisp_debug) {
	fprintf(lisp_debug_fp,s,s1);
    }
    fprintf(fp,s,s1);
    return;
}


void LISP_SEND_sd(fp,s,s1,d1)
     FILE *fp;
     char *s;
     char *s1;
     int   d1;
{
    if(status_lisp_debug) {
	fprintf(lisp_debug_fp,s,s1,d1);
    }
    fprintf(fp,s,s1,d1);
    return;
}


void LISP_SEND_sds(fp,s,s1,d1,s2)
     FILE *fp;
     char *s;
     char *s1,*s2;
     int   d1;
{
    if(status_lisp_debug) {
	fprintf(lisp_debug_fp,s,s1,d1,s2);
    }
    fprintf(fp,s,s1,d1,s2);
    return;
}


void LISP_SEND_sdsd(fp,s,s1,d1,s2,d2)
     FILE *fp;
     char *s;
     char *s1,*s2;
     int   d1, d2;
{
    if(status_lisp_debug) {
	fprintf(lisp_debug_fp,s,s1,d1,s2,d2);
    }
    fprintf(fp,s,s1,d1,s2,d2);
    return;
}
