/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   main_scheme.c
 *      Date:   1993/07/05
 *   
 *   Purpose:   schemeのメインプログラム上でのcall文の作成
 *              
 *   Functions: solveブロック以外では関数部分もこのプログラム中から
 *              作成プログラムを呼び出す。
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../scheme_comp/scheme_comp.h"
#include "../system/system.h"
#include "../parallel/parallel.h"


main_scheme(fp)
     FILE *fp;
{
    int i;
    int schemes;

    Scheme *scheme_ptr;


    schemes = how_many_schemes();

    comment1(fp);

    rep_proc("Welcome to main_scheme");
    

    for(i=0;i<schemes;i++) {
        
        rep_proc_no("Making scheme No.",i+1);

	scheme_ptr = get_nth_scheme_struct(i);

/*	fprintf(stderr,"scheme_ptr->type = %d(%d/%d)\n",scheme_ptr->type,
		i,schemes); */

	switch(scheme_ptr -> type) {
	    
	  case LABEL:
	    label_fort77(fp,scheme_ptr->ptr);
	    break;

	  case GOTO:
	    goto_fort77(fp,scheme_ptr->ptr);
	    break;

	  case READ:
	    read_fort77(fp,scheme_ptr->ptr);
	    break;

	  case WRITE:
	  case FILE_WRITE:
	    write_fort77(fp,scheme_ptr->ptr,scheme_ptr->type);
	    break;

	  case SOLVE:
	    solve_fort77(fp,scheme_ptr->ptr);
	    break;

	  case CONTOUR:
	    if(avs_mode) continue; /* Ignore if avs mode is specified */
	    
	    if(parallel) {
		select_PE0(fp);
	    }
	    contour_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case DISPLACEMENT:
	    if(avs_mode) continue; /* Ignore if avs mode is specified */

	    if(parallel) {
		select_PE0(fp);
	    }
	    displacement_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case PERSPECT:
	    if(avs_mode) continue; /* Ignore if avs mode is specified */

	    if(parallel) {
		select_PE0(fp);
	    }
	    perspect_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case SHOWVEC:
	    if(avs_mode) continue; /* Ignore if avs mode is specified */

	    if(parallel) {
		select_PE0(fp);
	    }
	    showvec_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case SHOWVEC_FILE:
	    if(parallel) {
		select_PE0(fp);
	    }
	    showvec_file_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case CONTOUR_FILE:
	    if(parallel) {
		select_PE0(fp);
	    }
	    contour_file_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case PLOT_FILE:
	    if(parallel) {
		select_PE0(fp);
	    }
	    plot_file_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case XPLOT:
	    if(avs_mode) continue; /* Ignore if avs mode is specified */

	    if(parallel) {
		select_PE0(fp);
	    }
	    xplot_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case TIME_PLOT_FILE:
	    if(parallel) {
		select_PE0(fp);
	    }
	    time_plot_file_fort77(fp,scheme_ptr->ptr);
	    if(parallel) {
		fprintf(fp,"      endif\n");
	    }
	    break;

	  case LET:
	    let_fort77(fp,scheme_ptr->ptr);
	    break;
	    
	  case NORM:
	    norm_fort77(fp,scheme_ptr->ptr);
	    break;

	  case IF_THEN:
	  case IF_GOTO:
	  case ELSE:
	  case ENDIF:
	    if_fort77(fp,scheme_ptr->ptr);
	    break;

	case ADAPTMESH:
	  adaptmesh_fort77(fp,scheme_ptr->ptr);
	  break;

	  default:
	    if(english_mesg) {
	      fprintf(stderr,"Component code=%d\n",scheme_ptr->type);
	      SystemAbort("Unknown scheme component");
	    }
	    else {
	      fprintf(stderr,"Component code=%d\n",scheme_ptr->type);
	      SystemAbort("不明のschemeブロックシンボルが出ました。(main_scheme)\n");
	    }
	}
    }

    rep_proc("end of making scheme instances");
    return;
}


select_PE0(fp)
     FILE *fp;
{
    fprintf(fp,"      if(p_rank .EQ. 0) then\n");
    return;
}

    
