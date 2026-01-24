/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   contour_fort77.c
 *      Date:   1994/01/14
 *   
 *   Purpose:   PLOT図作成用
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../var_comp/var_comp.h"

void plot_file_fort77( fp  , p_ptr )
     FILE *fp;
     Plot *p_ptr;
{
    int i;

    FILE *wfp;
    FEM_var  *fem_var_ptr;
    FEM_type *fem_type_ptr;
    char fname[80];

    /* feel_main.f中のcall文作成 */
    F77("      call ");
    PUT(fp,PLOT_NAME,p_ptr -> plot_no);
    F77("(feel");
    
    for(i=0;i<p_ptr -> items;i++) {
	F77(",");
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case FEM:
	    F77("feel(");
	    PUT(fp,NP_FEM_VAR,*(p_ptr->var_name+i));
	    F77(")");
	    break;

	  case SYSTEM_VAR:
	    if(**(p_ptr->var_name + i) == 'x') {
		F77("feel(np_x)");
		break;
	    }
	    if(**(p_ptr->var_name + i) == 'y') {
		F77("feel(np_y)");
		break;
	    }
	    if(**(p_ptr->var_name + i) == 'z') {
		F77("feel(np_z)");
		break;
	    }

	    SystemAbort("Illegal code @ plot_fort77(switch )");
	    break;

	  default:
	    SystemAbort("Illegal var_kind_type()");
	    break;
	}
    }
    F77(")\n");

    /*===============*/
    /* plot*.fの作成 */
    /*===============*/
    sprintf(fname,PLOT_FNAME,p_ptr->plot_no);

    wfp = OpenFileToWrite( fname );
    StoreMakefile( fname ,USER_LIBRARY);


    /* subroutine文 */
    PUT(wfp,"      subroutine ");
    PUT(wfp,PLOT_NAME,p_ptr->plot_no);
    PUT(wfp,"(feel");

    for(i=0;i<p_ptr -> items;i++) {
	PUT(wfp,",");
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case FEM:
	    PUT(wfp,FEM_VAR_NAME77,*(p_ptr->var_name+i));
	    break;

	  case SYSTEM_VAR:

	    PUT(wfp,"%s",*(p_ptr->var_name + i));
	    break;

	  default:
	    SystemAbort("Illegal var_kind_type():po2");
	    break;
	}
    }
    PUT(wfp,")\n");

    /*----------*/
    /* 定形処理 */
    /*----------*/
    CopyRight(wfp);
    TimeStamp(wfp);
    real8(wfp);
    common_parameters(wfp);
    PUT(wfp,"*\n");

    PUT(wfp,"       parameter (NSETNO = %d)\n",p_ptr->numdat_no);
    PUT(wfp,"*\n");
    
    /*---------------*/
    /* dimension宣言 */
    /*---------------*/
    PUT(wfp,"      real*4 feel(*)\n");

    for(i=0;i<p_ptr -> items;i++) {
	PUT(wfp,"      dimension ");
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case FEM:
	    PUT(wfp,FEM_VAR_NAME77,*(p_ptr->var_name+i));
	    break;

	  case SYSTEM_VAR:

	    PUT(wfp,"%s",*(p_ptr->var_name + i));
	    break;

	  default:
	    SystemAbort("Illegal var_kind_type():po2");
	    break;
	}
	PUT(wfp,"(*)\n");
    }

    CommonBlock(wfp);
    comment1(wfp);

    /* 節点集合データの取得 */
    /*    PUT(wfp,"      np_push = np_work\n"); OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_push\n");
    PUT(wfp,"*\n");

    PUT(wfp,"      nodes = n_nset(NSETNO,1)\n");
    PUT(wfp,"      np    = n_nset(NSETNO,2)\n");
    PUT(wfp,"*\n");

    PUT(wfp,"      call f_alloc(np_inset,'");
    PUT(wfp,PLOT_NAME,p_ptr->plot_no);
    PUT(wfp,"(INSET)',nodes*np,0,0)\n");
    PUT(wfp,"*\n");

    PUT(wfp,"      iunit = NSETNO + io_node -1\n");
    PUT(wfp,"      call get_inset(iunit,feel(np_inset),nodes,np)\n");
    PUT(wfp,"*\n");

    /* こルーチンの呼び出し */
    PUT(wfp,"      call ");
    PUT(wfp,CO_PLOT_NAME,p_ptr->plot_no);
    PUT(wfp,"(io_tmp,feel(np_inset),nodes,np");
    for(i=0;i<p_ptr -> items;i++) {
	PUT(wfp,",");
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case FEM:
	    PUT(wfp,FEM_VAR_NAME77,*(p_ptr->var_name+i));
	    break;

	  case SYSTEM_VAR:

	    PUT(wfp,"%s",*(p_ptr->var_name + i));
	    break;

	  default:
	    SystemAbort("Illegal var_kind_type():po3");
	    break;
	}
    }
    PUT(wfp,")\n");
    PUT(wfp,"*\n");

    /*    PUT(wfp,"      np_work = np_push\n"); OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_pop\n");
    PUT(wfp,"*\n");

    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");

    /*-----------------*/
    /* plot coルーチン */
    /*-----------------*/
    PUT(wfp,"      subroutine ");
    PUT(wfp,CO_PLOT_NAME,p_ptr->plot_no);
    PUT(wfp,"(io_tmp,inset,nodes,np");

    for(i=0;i<p_ptr -> items;i++) {
	PUT(wfp,",");
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case FEM:
	    PUT(wfp,FEM_VAR_NAME77,*(p_ptr->var_name+i));
	    break;

	  case SYSTEM_VAR:

	    PUT(wfp,"%s",*(p_ptr->var_name + i));
	    break;

	  default:
	    break;
	}
    }
    PUT(wfp,")\n");

    /*----------*/
    /* 定形処理 */
    /*----------*/
    CopyRight(wfp);
    TimeStamp(wfp);
    real8(wfp);

    /*-------------*/
    /* dimension文 */
    /*-------------*/
    PUT(wfp,"      dimension inset(np,nodes)\n");
    PUT(wfp,"*\n");

    for(i=0;i<p_ptr -> items;i++) {
	PUT(wfp,"      dimension ");
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case FEM:
	    PUT(wfp,FEM_VAR_NAME77,*(p_ptr->var_name+i));
	    break;

	  case SYSTEM_VAR:

	    PUT(wfp,"%s",*(p_ptr->var_name + i));
	    break;

	  default:
	    break;
	}
	PUT(wfp,"(*)\n");
    }

    comment1(wfp);
    PUT(wfp,"      io_no = io_tmp + %d\n",p_ptr->file_io_no);
    PUT(wfp,"      open(unit=io_no,file=%s)\n",p_ptr->filename);
    PUT(wfp,"*\n");

    PUT(wfp,"      do 100 i=1,nodes\n");
    PUT(wfp,"       ip = inset(1,i)\n");
    PUT(wfp,"*\n");

    PUT(wfp,"       write(io_no,110) ");

    for(i=0;i<p_ptr -> items;i++) {
	if(i != 0) { 
	    PUT(wfp,",");
	}
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case FEM:
	    PUT(wfp,FEM_VAR_NAME77,*(p_ptr->var_name+i));
	    PUT(wfp,"(ip)");
	    break;

	  case SYSTEM_VAR:

	    PUT(wfp,"%s(ip)",*(p_ptr->var_name + i));
	    break;

	  default:
	    break;
	}
    }
    PUT(wfp,"\n");

    PUT(wfp,"*\n");

    PUT(wfp,"100   continue\n");

    /* format文 */

    PUT(wfp," 110  format(%d(F12.5,1X))\n",p_ptr->items);
    PUT(wfp,"*\n");

    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");
    
    CloseFile(wfp);

    return;  
}


