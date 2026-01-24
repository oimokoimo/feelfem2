/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_plot_check.c
 *      Date:   1994/01/12
 *   
 *   Purpose:   plot文をチェックし、plot境界節点データ番号を割り当てる
 *   Functions: 
 *              
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../scheme_comp/scheme_comp.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"

void scheme_plot_check()
{
    int i,j;
    int schemes;

    int var_type;

    Scheme *scheme_ptr;
    Plot   *plot_ptr,*plot_ptr2;
    int     plots;
    int     current_plot_no;
    Plot  **plot_ptrptr;   /* *plot_ptr を覚えておくため
			      →numdat_noを割り当てるため  */
    char  **var_name;

    schemes = how_many_schemes();
    plots   = how_many_plots();

    current_plot_no = 0;
    plot_ptrptr     = (Plot **)FEEL_GetMemory(sizeof(Plot *) * plots);

    
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);

	switch(scheme_ptr->type) {
	    
	  case PLOT_FILE:
	  case XPLOT:
	    plot_ptr                       = (Plot *)scheme_ptr->ptr;
	    *(plot_ptrptr+current_plot_no) = plot_ptr;  /* saveする */
	    
	    var_name = plot_ptr-> var_name;
	    
	    for(j=0;j<plot_ptr->items;j++) {
		var_type = get_var_kind(*(var_name +j));
		if( var_type != FEM && var_type != SYSTEM_VAR ) {
		    if(english_mesg) {
			SystemError_yy_s("%s is not fem variable(plot sentence)",*(var_name+j),plot_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("plot文で指定された変数 %s はfem変数型ではない",*(var_name+j),plot_ptr->yylineno);
		    }
		}
	    }
	    
	    if(get_mesh_name_type_by_name( plot_ptr->name ) != MESH_LINE) {
		if(english_mesg) {
		    SystemError_yy_s("Name %s is not edge name.(in plot)",
				     plot_ptr->name,plot_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("plot文で指定された名前 %s はedgeではない",
				 plot_ptr->name,plot_ptr -> yylineno);
		}
	    }
	    
	    /* numdat_no の割り当て */
	    for(j=0;j<current_plot_no;j++) {
		plot_ptr2 = *(plot_ptrptr + j);
		if(streq(plot_ptr->name,plot_ptr2->name)) {
		    plot_ptr -> numdat_no = plot_ptr2->numdat_no;
		    break;
		}
	    }
	    
	    if(plot_ptr -> numdat_no == NO) {
		/* 節点集合データ番号割り当て */
		plot_ptr -> numdat_no = get_new_nodesetno();  
	    }
	    current_plot_no ++;
	    break;

	    
	  case TIME_PLOT_FILE:

	    plot_ptr                       = (Plot *)scheme_ptr->ptr;
	    *(plot_ptrptr+current_plot_no) = plot_ptr;  /* saveする */
	    
	    var_name = plot_ptr-> var_name;
	    
	    for(j=0;j<plot_ptr->items;j++) {
		var_type = get_var_kind(*(var_name +j));
		if( var_type != DOUBLE && var_type != CONST && var_type != INT ) {
		    if(english_mesg) {
			SystemError_yy_s("%s is not scalar variable(time-fplot)",*(var_name+j),plot_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("time-fplot文で指定された変数 %s はスカラー変数ではない",*(var_name+j),plot_ptr->yylineno);
		    }
		}
	    }
	    break;

	  default:
	    break;
	}
    }
    return;
}

