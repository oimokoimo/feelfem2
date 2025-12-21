/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   label_fort77.c
 *      Date:   1993/07/06
 *   
 *   Purpose:   label文のFORT77での実現
 *              
 */

#include <stdio.h>
#include "../scheme_comp/scheme_comp.h"


label_fort77(fp,label_ptr)
     FILE  *fp;
     Label *label_ptr;
{
    comment_s(fp);
    fprintf(fp,"c label [%s(%d)]\n",label_ptr->label,label_ptr->yylineno);
    fprintf(fp,"%4d  continue\n",label_ptr->line_no);

    return;
}

