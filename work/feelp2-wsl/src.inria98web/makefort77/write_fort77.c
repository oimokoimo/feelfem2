/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   write_fort77.c
 *      Date:   1993/07/06
 *   
 *   Purpose:   write文の実現
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"

#include "../parallel/parallel.h"

write_fort77(fp,write_ptr,type)
     FILE *fp;
     Write *write_ptr;
     int type;
{
    int i,args;
    int strings,exprs;
    Expression *expr;
    
    comment_s(fp);

    if(parallel) {
	F77("      if(p_rank.eq.0) then \n");
    }
    
    if(type == WRITE) {
	PUT(fp,"      write(*,*) ");
    }
    else {
	PUT(fp,"      write(io_tmp+%d,*) ",write_ptr->file_io_no);
    }

    args = write_ptr->args;
    exprs = 0;
    strings = 0;

    for(i=0;i<args;i++) {
	switch(*(write_ptr->kind + i)) {
	  case EXPR:
	    expr = write_ptr->expr + exprs;
	    exprs++;
	    fprintf(fp,"%s",term_convert_scalar(expr->expr_inf));
	    break;

	  case STRING:
	    fprintf(fp,"%s",*(write_ptr->string + strings));
	    strings++;
	    break;

	  default:
	    SystemAbort("write文作成中に妙な*kindに出会いました。\n");
	}
	if(i != args-1) fprintf(fp,",");
    }

    fprintf(fp,"\n");


    if(parallel) {
	F77("      endif\n");
    }


    return;
}

