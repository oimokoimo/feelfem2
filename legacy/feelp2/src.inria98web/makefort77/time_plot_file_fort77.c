/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   time_plot_file_fort77.c
 *      Date:   1994/02/15
 *   
 *   Purpose:   時系列のplot用のデータファイルを作成する。
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"

void time_plot_file_fort77( fp , p_ptr )
     FILE *fp;
     Plot *p_ptr;
{
    int i,j;

    FILE *wfp;

    char fname[80];
    char tmp_buf[BUFSIZ];
    char buf[BUFSIZ];
    char *fmt;

    
    /* メインルーチン上 */
    PUT(fp,"      call ");
    PUT(fp,PLOT_NAME,p_ptr->plot_no);
    PUT(fp,"(");

    for(i=0;i<p_ptr -> items;i++) {
	if(i != 0) F77(",");
	PUT(fp,SCALAR_VAR_NAME77,*(p_ptr->var_name + i));
    }
    PUT(fp,")\n");

    /*===============*/
    /* plot*.fの作成 */
    /*===============*/
    sprintf(fname,PLOT_FNAME,p_ptr->plot_no);
    
    wfp = OpenFileToWrite( fname );
    StoreMakefile( fname , USER_LIBRARY );
    
    /* subroutine 文 */
    PUT(wfp,"      subroutine ");
    PUT(wfp,PLOT_NAME,p_ptr->plot_no);
    PUT(wfp,"(");

    for(i=0;i<p_ptr -> items;i++) {
	if(i != 0) PUT(wfp,",");
	PUT(wfp,SCALAR_VAR_NAME77,*(p_ptr->var_name + i));
    }
    PUT(wfp,")\n");    

    /* 定形処理 */
    CopyRight(wfp);
    TimeStamp(wfp);
    real8(wfp);
    common_parameters(wfp);
    PUT(wfp,"*\n");
    
    /*===================*/    
    /* real,integer 宣言 */
    /* ついでに、        */
    /* FORMAT文の作成    */
    /*===================*/    
    fmt = buf;
    for(i=0;i<p_ptr -> items;i++) {
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case DOUBLE:
	  case CONST:
	    PUT(wfp,"      real*8 ");
	    PUT(wfp,SCALAR_VAR_NAME77,*(p_ptr->var_name +i));
	    PUT(wfp,"\n");
	    if(i != 0) {
		sprintf(fmt,",F12.5");
		fmt += 6;
	    }
	    else {
		sprintf(fmt,"F12.5");
		fmt += 5;
	    }

	    break;

	  case INT:
	    PUT(wfp,"      integer ");
	    PUT(wfp,SCALAR_VAR_NAME77,*(p_ptr->var_name +i));
	    PUT(wfp,"\n");
	    if(i != 0) {
		sprintf(fmt,",I8");
		fmt += 3;
	    }
	    else {
		sprintf(fmt,"I8");
		fmt += 2;
	    }


	    break;

	  default:
	    SystemAbort("Illegal var kind @ time_plot_file_fort77");
	}
    }
    PUT(wfp,"*\n");

    CommonBlock(wfp);
    comment1(wfp);


    PUT(wfp,"      data is_come/ 1 /\n");
    comment1(wfp);


    PUT(wfp,"      io_no = io_tmp + %d\n",p_ptr->file_io_no);
    PUT(wfp,"*\n");


    PUT(wfp,"      if(is_come.eq.1) then\n");
    PUT(wfp,"        is_come = 0\n");
    PUT(wfp,"        open(unit=io_no,file=%s,status='UNKNOWN')\n",p_ptr->filename);
    PUT(wfp,"      endif\n");
    PUT(wfp,"*\n");

    PUT(wfp,"      write(io_no,100) ");
    for(i=0;i<p_ptr -> items;i++) {
	if(i != 0) PUT(wfp,",");
	PUT(wfp,SCALAR_VAR_NAME77,*(p_ptr->var_name + i));
    }
    PUT(wfp,"\n");


    PUT(wfp," 100  format(%s)\n",buf);
    PUT(wfp,"*\n");
    
    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");

    CloseFile(wfp);


    /* GNUPLOT用のコマンドファイル作成 */
    sprintf(tmp_buf,"%s",(p_ptr->filename + 1));      /* 最初の ' を無視 */
    tmp_buf[strlen(tmp_buf)-1] = '\0';               /* 最後の ' を無視 */
    sprintf(fname,"%s.gnu",tmp_buf);


    wfp = OpenFileToWrite(fname);
    fprintf(wfp,"plot ");

    for(j=0;j<p_ptr->items-1;j++) {
	if(j != 0) {
	    fprintf(wfp,",");
	}
	fprintf(wfp,"\"%s\" using 1:%d title \"%s\" with linespoints",tmp_buf,j+2,*(p_ptr->var_name+j+1));
    }
    fprintf(wfp,"\n");
    CloseFile(wfp);


    return;
}




