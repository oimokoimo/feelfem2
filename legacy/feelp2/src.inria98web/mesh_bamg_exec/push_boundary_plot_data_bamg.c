/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   push_boundary_plot_data_bamg.c
 *      Date:   1997/07/14
 *   
 *   Purpose:   Make plot data for bamg mesh generator
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "../mesh_comp/mesh_comp.h"
#include "../scheme_comp/scheme_comp.h"



void make_boundary_plot_data_main_bamg(fp)
     FILE *fp;
{
    int i,j;
    int schemes;

    Scheme *scheme_ptr;
    Plot   *plot_ptr,*plot_ptr2;
    int     plots;
    Plot  **plot_ptrptr;   /* *plot_ptr を覚えておくため
			      →numdat_noをただ一つ作成する為  */
    int     made_flag;
    int     current_plot_no;

    FILE   *gnuplot_fp;
    char    fname[80];
    char    tmp_buf[80];

    schemes = how_many_schemes();
    plots   = how_many_plots();

    current_plot_no = 0;
    plot_ptrptr     = (Plot **)FEEL_GetMemory(sizeof(Plot *) * plots);


    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);
	if(scheme_ptr->type != PLOT_FILE && 
	   scheme_ptr->type != XPLOT        ) continue;
	
	plot_ptr                       = (Plot *)scheme_ptr->ptr;

	/* GNUPLOT用のコマンドファイル作成 */
	if(scheme_ptr->type != XPLOT) {  /* debug 94/10/18 */
	sprintf(tmp_buf,"%s",(plot_ptr->filename + 1));  /* 最初の ' を無視 */
	tmp_buf[strlen(tmp_buf)-1] = '\0';               /* 最後の ' を無視 */
	sprintf(fname,"%s.gnu",tmp_buf);
	gnuplot_fp = OpenFileToWrite(fname);
	fprintf(gnuplot_fp,"plot ");

	for(j=0;j<plot_ptr->items-1;j++) {
	    if(j != 0) {
		fprintf(gnuplot_fp,",");
	    }
	    fprintf(gnuplot_fp,"\"%s\" using 1:%d title \"%s\" with linespoints",tmp_buf,j+2,*(plot_ptr->var_name+j+1));
	}
	fprintf(gnuplot_fp,"\n");
	fclose(gnuplot_fp);
	}


	
	*(plot_ptrptr+current_plot_no) = plot_ptr;  /* saveする */

	made_flag = NO;

	/* 節点集合の作成 */
	for(j=0;j<current_plot_no;j++) {
	    plot_ptr2 = *(plot_ptrptr + j);
	    if(plot_ptr->numdat_no == plot_ptr2->numdat_no) {
		made_flag = YES;
		break;
	    }
	}
	current_plot_no ++;
	
	if(made_flag == YES)  continue;

	make_boundary_plot_data_bamg(fp,plot_ptr->name,plot_ptr->numdat_no);
	

    }
    
    return;
}


make_boundary_plot_data_bamg(fp,line_name,numdatno)
     FILE *fp;
     char *line_name;
     int   numdatno;
{
    int i,j;

    Line *line_ptr;

    int   segments;
    int   total_points,points;
    int  *node_ptr;

    char *from,*to;

    total_points = 0;
    line_ptr = get_line_ptr_by_name( line_name );
    

    segments = line_ptr -> points - 1;

    fprintf(fp,"plot  %d\n%d\n",numdatno,segments);    /*BAMG*/

    /* 総点数の計算 */
    for(i=0;i<segments;i++) {
	from = line_ptr -> compos[i];
	to   = line_ptr -> compos[i+1];

	fprintf(fp,"%s %s\n",from,to);
	
    }
    fprintf(fp,"end\n");

    return;
}
