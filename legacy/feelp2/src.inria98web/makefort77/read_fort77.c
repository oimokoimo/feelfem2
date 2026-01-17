/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   read_fort77.c
 *      Date:   1993/07/06
 *   
 *   Purpose:   read文の実現
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../scheme_comp/scheme_comp.h"
#include "../parallel/parallel.h"

void read_fort77(fp,read_ptr)
     FILE *fp;
     Read *read_ptr;
{
    int i,args;
    char **var_name;
    char *name;
    
    comment_s(fp);


    if(parallel) {
	F77("      if(p_rank.eq.0) then \n");
    }

    if(avs_mode) {
      fprintf(fp,"*     read(*,*) ");
    }
    else {
      fprintf(fp,"      read(*,*) ");
    }

    args     = read_ptr->args;
    var_name = read_ptr -> var_name;

    for(i=0;i<args;i++) {
	name = *(var_name + i);
	PUT(fp,SCALAR_VAR_NAME77,name);
	if(i != args-1) PUT(fp,",");
    }

    PUT(fp,"\n");

    if(parallel) {
	F77("      endif\n");
    }

    return;
}
