/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   goto_fort77.c
 *      Date:   1993/07/06
 *   
 *   Purpose:   goto文のFORT77での実現
 *              
 */

#include <stdio.h>
#include "../scheme_comp/scheme_comp.h"

extern int web_exec;

goto_fort77(fp,goto_ptr)
     FILE  *fp;
     Goto *goto_ptr;
{
    comment_s(fp);
    fprintf(fp,"c goto [%s(%d)]\n",goto_ptr->label,goto_ptr->yylineno);
    if(web_exec) {
      fprintf(fp,"*      Disabled goto statement in web exec mode\n");
      fprintf(fp,"*      goto %d\n",goto_ptr->line_no);
    }
    else {
      fprintf(fp,"      goto %d\n",goto_ptr->line_no);
    }

    return;
}

