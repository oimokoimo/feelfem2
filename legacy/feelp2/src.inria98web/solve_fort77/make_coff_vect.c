/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_coff_vect.c
 *      Date:   1993/10/26
 *   
 *   Purpose:   係数シンボル行列の作成
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

make_coff_vect( fp, n)
     FILE *fp;
     int    n;
{
    int i;
    char buf[LISP_BUFSIZ];
    char cof[11];
    char *cp;

    cp = buf;

    cp = make_list_st(cp , "(setq *coff-vect* '(");

    for(i=0;i<n;i++) {
	sprintf(cof,"M%d ",i+1);
	cp = make_list_st(cp , cof);
    }
    cp = make_list_st(cp , " ) )\n");
    
    end_list_st( cp );

    LISP_SEND(fp,buf);
    return;
}


   
