/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   xplot_fort77.c
 *      Date:   1994/07/25
 *  Modified:   1994/11/11  (By XYGRAPH routine change)
 *   
 *   Purpose:   PLOT図作成用
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../var_comp/var_comp.h"


extern int web_exec;

void xplot_fort77( fp  , p_ptr )
     FILE *fp;
     Plot *p_ptr;
{
    int i;

    int mid_points;

    int NLINE;

    FILE *wfp;
    FEM_var  *fem_var_ptr;
    FEM_type *fem_type_ptr;
    char fname[80];
    char tmp_buf[80];


    mid_points = get_midpoints();


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

    /* SX,SY保存の為のデータファイル認識 */
    PUT(wfp,"      data icomeyet / 0 /\n");
    comment1(wfp);

    /* 節点集合データの取得 */
    /* PUT(wfp,"      np_push = np_work\n"); OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_push\n");
    
    
    PUT(wfp,"*\n");

    PUT(wfp,"      NODES = n_nset(NSETNO,1)\n");
    PUT(wfp,"      np    = n_nset(NSETNO,2)\n");
    PUT(wfp,"*\n");

    if(mid_points == 0) {
	PUT(wfp,"      NODER = NODES\n");
    }
    else {
	PUT(wfp,"      NODER = (NODES - 1) / (1 + %d) + 1\n",mid_points);
    }
	  

    PUT(wfp,"      NLINE = %d - 1\n", p_ptr->items);
    PUT(wfp,"*\n");

    /* 作業領域確保 */
    PUT(wfp,"      call f_alloc(np_px,'feelpt%d(PX)',NODER*NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_py,'feelpt%d(PY)',NODER*NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_sx,'feelpt%d(SX)',NODER*NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_sy,'feelpt%d(SY)',NODER*NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_ppx,'feelpt%d(PPX)',NODER,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_ppy,'feelpt%d(PPY)',NODER,1,0)\n",
	p_ptr->plot_no);

    /* 1994/11/11 追加分 */
    PUT(wfp,"      call f_alloc(np_pxmin,'feelpt%d(PXMIN)',NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_pxmax,'feelpt%d(PXMAX)',NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_pymin,'feelpt%d(PYMIN)',NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_pymax,'feelpt%d(PYMAX)',NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_nxdiv,'feelpt%d(NXDIV)',NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_nydiv,'feelpt%d(NYDIV)',NLINE,1,0)\n",
	p_ptr->plot_no);
    PUT(wfp,"      call f_alloc(np_naxis,'feelpt%d(NAXIS)',NLINE,1,0)\n",
	p_ptr->plot_no);
    

    comment1(wfp);

    /* SX,SY保存の作業ファイル設定 */
    PUT(wfp,"*\n* Set Scratch file for array SX,SY\n*\n");
    PUT(wfp,"      nasize = NODER * NLINE\n");
    PUT(wfp,"      io_no = io_tmp + %d\n",p_ptr->file_io_no);
    PUT(wfp,"*\n");
    PUT(wfp,"      if(icomeyet .EQ. 0) THEN\n");
    
    PUT(wfp,"        open(unit=io_no,status='scratch',form='unformatted')\n");

    PUT(wfp,"        icomeyet = 1\n");
    PUT(wfp,"      else\n");
    PUT(wfp,"        rewind(io_no)\n");
    PUT(wfp,"        call diskrdd(io_no,NLINE*NODER,feel(np_sx))\n");
    PUT(wfp,"        call diskrdd(io_no,NLINE*NODER,feel(np_sy))\n");
    PUT(wfp,"      endif\n");
    comment1(wfp);
    
    PUT(wfp,"      call f_alloc(np_inset,'");
    PUT(wfp,PLOT_NAME,p_ptr->plot_no);
    PUT(wfp,"(INSET)',nodes*np,0,0)\n");
    PUT(wfp,"*\n");

    PUT(wfp,"      iunit = NSETNO + io_node -1\n");
    PUT(wfp,"      call get_inset(iunit,feel(np_inset),nodes,np)\n");
    PUT(wfp,"*\n");


    /* 各種パラメータの設定 */
    PUT(wfp,"      IWX = 11\n");
    PUT(wfp,"      IWY = 11\n");

    if(web_exec) {
      PUT(wfp,"      IWW = %d\n",100);
      PUT(wfp,"      IWH = %d\n",100);
    }
    else {
      PUT(wfp,"      IWW = %d\n",p_ptr->IWW);
      PUT(wfp,"      IWH = %d\n",p_ptr->IWH);
    }


    PUT(wfp,"      IWD = %d\n",p_ptr->window_id);
    PUT(wfp,"      ISTEP = 1\n");

/*
    PUT(wfp,"      IRANGE = 0\n");
    PUT(wfp,"      NXAS   = 1\n");
    PUT(wfp,"      NYAS   = 1\n");
    PUT(wfp,"      PXMIN  = 0.0\n");
    PUT(wfp,"      PYMIN  = 0.0\n");
    PUT(wfp,"      PXMAX  = 1.0\n");
    PUT(wfp,"      PYMAX  = 1.0\n");
*/

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
    PUT(wfp,",feel(np_px),feel(np_py),feel(np_sx),feel(np_sy)");
    PUT(wfp,",feel(np_ppx),feel(np_ppy)");
    PUT(wfp,",IWX,IWY,IWW,IWH,IWD,NLINE,ISTEP");
    PUT(wfp,",feel(np_pxmin),feel(np_pxmax),feel(np_pymin)");
    PUT(wfp,",feel(np_pymax),feel(np_nxdiv),feel(np_nydiv)");
    PUT(wfp,",feel(np_naxis),NODER");
    PUT(wfp,")\n");


    /* SX,SY をファイルに書く */
    PUT(wfp,"      rewind(io_no)\n");
    PUT(wfp,"      call diskwrtd(io_no,NLINE*NODER,feel(np_sx))\n");
    PUT(wfp,"      call diskwrtd(io_no,NLINE*NODER,feel(np_sy))\n");
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
    PUT(wfp,",PX,PY,SX,SY,PPX,PPY,IWX,IWY,IWW,IWH,IWD");
    PUT(wfp,",NLINE,ISTEP,PXMIN,PXMAX,PYMIN,PYMAX");
    PUT(wfp,",NXDIV,NYDIV,NAXIS,NODER");
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
    PUT(wfp,"      dimension PX(NODER,NLINE),PY(NODER,NLINE)\n");
    PUT(wfp,"      dimension SX(NODER,NLINE),SY(NODER,NLINE)\n");
    PUT(wfp,"      dimension PPX(NODER),PPY(NODER)\n");
    PUT(wfp,"      dimension PXMIN(NLINE),PXMAX(NLINE)\n");
    PUT(wfp,"      dimension PYMIN(NLINE),PYMAX(NLINE)\n");
    PUT(wfp,"      dimension NXDIV(NLINE),NYDIV(NLINE)\n");
    PUT(wfp,"      dimension NAXIS(NLINE)\n");

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

    /*  詳細指定時の処理 */
    if(p_ptr -> IFLG == NO) {
	PUT(wfp,"      IRGF = 0\n");
    }
    else {
	PUT(wfp,"      IRGF = 1\n");
    }
    PUT(wfp,"*\n");

    PUT(wfp,"      it = 1\n");
    PUT(wfp,"*\n");


    PUT(wfp,"      do 100 i=1,nodes\n");
    PUT(wfp,"       ip = inset(1,i)\n");
    PUT(wfp,"*\n");

    /* ｘ軸用引数変数名をtmp_bufに記録 */
    switch(get_var_kind(*(p_ptr->var_name+0))) {
      case FEM:
	sprintf(tmp_buf,FEM_VAR_NAME77,*(p_ptr->var_name+0));
	break;

      case SYSTEM_VAR:
	sprintf(tmp_buf,"%s",*(p_ptr->var_name + 0));
	break;

      default:
	break;
    }

    /* 中間節点を除去 */
    if(mid_points != 0) {
	PUT(wfp,"*\n");
	PUT(wfp,"      if(mod(i-1,%d) .ne. 0) goto 100\n",mid_points + 1);
	PUT(wfp,"*\n");
    }

    /* 第一引数はｘ軸用の為、1から始める */
    for(i=1;i<p_ptr -> items;i++) {
	/* ｘ軸 */
	PUT(wfp,"      PX(it,%d) = %s(ip)\n",i,tmp_buf);

	if(p_ptr->IFLG == YES && i == 1) {
	    PUT(wfp,"      if(it .eq. 1) then\n");
	    PUT(wfp,"        XMIN = PX(it,1)\n");
	    PUT(wfp,"        XMAX = PX(it,1)\n");
	    PUT(wfp,"      else\n");
	    PUT(wfp,"        IF(XMIN .GT. PX(it,1)) XMIN = PX(it,1)\n");
	    PUT(wfp,"        IF(XMAX .LT. PX(it,1)) XMAX = PX(it,1)\n");
	    PUT(wfp,"      endif\n");
	}

	/* ｙ軸 */
	PUT(wfp,"      PY(it,%d) = ",i);
	switch(get_var_kind(*(p_ptr->var_name+i))) {
	  case FEM:
	    PUT(wfp,FEM_VAR_NAME77,*(p_ptr->var_name+i));
	    PUT(wfp,"(ip)\n");
	    break;

	  case SYSTEM_VAR:

	    PUT(wfp,"%s(ip)\n",*(p_ptr->var_name + i));
	    break;

	  default:
	    break;
	}
    }
    PUT(wfp,"      it = it + 1\n");

    PUT(wfp,"100   continue\n");
    
    comment1(wfp);
    
    /* 使用するY軸フラグの選択 */
    PUT(wfp,"* NAXIS  y-axis  1:use Y1  2:use Y2\n");
    for(i=1;i<p_ptr->items;i++) {
	PUT(wfp,"      NAXIS(%d) = 1\n",i);
    }
    /* Y軸レンジの統一フラグ */
    PUT(wfp,"* NYAS   Use one y-range\n");
    PUT(wfp,"      NYAS = 1\n");


    comment1(wfp);

    if(p_ptr -> IFLG == YES) {
	for(i=1;i<p_ptr->items;i++) {
	    PUT(wfp,"      PXMIN(%d) = XMIN\n",i);
	    PUT(wfp,"      PXMAX(%d) = XMAX\n",i);
	    PUT(wfp,"      PYMIN(%d) = %lf\n",i,p_ptr->umin);
	    PUT(wfp,"      PYMAX(%d) = %lf\n",i,p_ptr->umax);
	    PUT(wfp,"      NXDIV(%d) = 5\n",i);
	    PUT(wfp,"      NYDIV(%d) = 5\n",i);
	    PUT(wfp,"      NAXIS(%d) = 1\n",i);
	}
    }

    PUT(wfp,"      IGRY = 0\n");

    PUT(wfp,"      call FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX,IGRY)\n");
    comment1(wfp);
    PUT(wfp,"      call FEEL_XYGRAPH(NLINE,NODER,PX,PY,SX,SY,PPX,PPY,");
    PUT(wfp,"PXMIN,PXMAX,PYMIN,PYMAX,NXDIV,NYDIV,NAXIS,NYAS,ISTEP,IRGF,IWD)\n");
    comment1(wfp);

    /* タイトルを書く */
    PUT(wfp,"      call FEEL_TITLE('%d feel xplot[%d]',IWD)\n",
	p_ptr->window_id+1,p_ptr->plot_no);

    /* メッセージが指定されていれば書く */
    if(p_ptr -> mesg != NULL ) {
	PUT(wfp,"      call FEEL_MESSAGE(%s,IWD)\n",p_ptr->mesg);
    }


    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");
    
    CloseFile(wfp);

    return;  
}
