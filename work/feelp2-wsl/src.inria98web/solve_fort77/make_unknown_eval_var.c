/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_unknown_eval_var.c
 *      Date:   1993/10/27
 *   
 *   Purpose:   未知変数に対する展開式を作成する
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

make_unknown_eval_var(fp , name , start , element_name, freedom)
     FILE *fp;
     char *name;
     int   start;
     char *element_name;
     int freedom;
{
    int i;

    char buf[LISP_BUFSIZ];
    char buf2[38];
    char *cp;

    cp = buf;
    
    cp = make_list_st(cp,"(setq ");
    cp = make_list_st(cp,name);
    cp = make_list_st(cp," '(+ ");

    /* エルミート要素に対してもこの方法で行う */
    for(i=0;i<freedom;i++) {
	sprintf(buf2," (* M%d %s_%d)",i+start,element_name,i+1);
	cp = make_list_st(cp,buf2);
    }
    
    cp = make_list_st(cp," ) )\n");
    end_list_st(cp);

    LISP_SEND_s(fp,"%s",buf);

    return;
}


