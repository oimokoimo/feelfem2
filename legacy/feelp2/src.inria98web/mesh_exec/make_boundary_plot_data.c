/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_boundary_plot_data.c
 *      Date:   1994/01/14
 *   
 *   Purpose:   plot文用の境界節点集合データを作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "boundary.h"
#include "../mesh_comp/mesh_comp.h"
#include "../scheme_comp/scheme_comp.h"


void make_boundary_plot_data_main(fp)
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

	make_boundary_plot_data(fp,plot_ptr->name,plot_ptr->numdat_no);
	

    }
    
    return;
}


make_boundary_plot_data(fp,line_name,numdatno)
     FILE *fp;
     char *line_name;
     int   numdatno;
{
    int i,j;

    Line *line_ptr;
    Boundary2D *b2d_ptr;

    int   segments;
    int   total_points,points;
    int  *node_ptr;

    char *from,*to;

    total_points = 0;
    line_ptr = get_line_ptr_by_name( line_name );
    

    segments = line_ptr -> points - 1;

    /* 総点数の計算 */
    for(i=0;i<segments;i++) {
	from = line_ptr -> compos[i];
	to   = line_ptr -> compos[i+1];

	b2d_ptr = get_b2d_ptr_by_both_ends(from,to);
	
	total_points = total_points + b2d_ptr ->points;
    }
    total_points = total_points - (segments - 1);

    /* 実際に書く、ここでは向きはline通り */
    fprintf(fp,"%s\n",KEY_NSET_REAL);
    fprintf(fp,"%8d%8d%8d\n",numdatno,total_points,1);

    for(i=0;i<segments;i++) {
	from = line_ptr -> compos[i];
	to   = line_ptr -> compos[i+1];

	b2d_ptr = get_b2d_ptr_by_both_ends(from,to);
	
	if(streq(b2d_ptr->from_name,from)) {
	    /* 正の向き */
	    if(i == 0) {
		node_ptr = b2d_ptr -> node_no;
		points   = b2d_ptr -> points;
	    }
	    else {
		node_ptr = b2d_ptr -> node_no;
		node_ptr++;                     /* 最初はスキップ */
		points   = b2d_ptr -> points -1; /* 最初はスキップ */
	    }

	    /* 節点を書く */
	    for(j=0;j<points;j++) {
		fprintf(fp,"%8d\n",*node_ptr);
		node_ptr++;
	    }
	}
	else {
	    /* 逆向き   */

	    if(i == 0) {
		node_ptr = b2d_ptr -> node_no;
		points   = b2d_ptr -> points;

		node_ptr += points -1;
	    }
	    else {
		node_ptr = b2d_ptr -> node_no;
		points   = b2d_ptr -> points -1;  /* 最初はスキップ */

		node_ptr += points -1;
	    }
	    /* 節点を書く */
	    for(j=0;j<points;j++) {
		fprintf(fp,"%8d\n",*node_ptr);
		node_ptr--;
	    }		

	}

    }

    return;
}



