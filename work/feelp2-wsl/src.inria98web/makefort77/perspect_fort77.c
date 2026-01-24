/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   perspect_fort77.c
 *      Date:   1993/12/15
 *   
 *   Purpose:   ２次元鳥瞰図
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
#include "../mesh_comp/mesh_comp.h"

static int perspects = 0;


void perspect_fort77( fp  , p_ptr )
     FILE *fp;
     Perspect *p_ptr;
{
    FILE *wfp;
    FEM_var  *fem_var_ptr;
    FEM_type *fem_type_ptr;
    Subdomain *subdomain_ptr;
    char fname[80];

    /* feel_main.f中のcall文作成 */
    perspects++;
    F77("      call ");
    PUT(fp,PERSPECT_NAME,perspects);
    PUT(fp,"(feel,feel(np_x),feel(np_y),feel(npf_%s))\n",p_ptr->var);


    /* perspect*.fの作成 */
    sprintf(fname,PERSPECT_FNAME,perspects);

    StoreMakefile( fname ,USER_LIBRARY);
    wfp = OpenFileToWrite( fname );

    /* subroutine文 */
    PUT(wfp,"      subroutine ");
    PUT(wfp,PERSPECT_NAME,perspects);
    PUT(wfp,"( feel, x, y,");
    PUT(wfp,FEM_VAR_NAME77,p_ptr->var);
    PUT(wfp,")\n");

    /*----------*/
    /* 定形処理 */
    /*----------*/
    CopyRight(wfp);
    TimeStamp(wfp);
    real8(wfp);
    common_parameters(wfp);

    /*---------------*/
    /* dimension宣言 */
    /*---------------*/

    PUT(wfp,"      real*4 feel(*)\n");
    PUT(wfp,"      dimension x(*),y(*)\n");

    PUT(wfp,"      dimension ");
    PUT(wfp,FEM_VAR_NAME77,p_ptr->var);
    PUT(wfp,"(*)\n");

    CommonBlock(wfp);
    comment1(wfp);

    /* edatデータの読み込み */
    /*    PUT(wfp,"      np_push = np_work\n"); OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_push\n");
    PUT(wfp,"*\n");


    if(p_ptr -> subdomain == NULL) {
	PUT(wfp,"* Whole domain EDAT data no is 1\n");
	PUT(wfp,"      iedat_no =1\n");
    }
    else {
	subdomain_ptr = get_subdomain_ptr_by_name(p_ptr->subdomain);
	PUT(wfp,"* subdomain [%s]\n",p_ptr->subdomain);
	PUT(wfp,"      iedat_no = %d\n",subdomain_ptr->edatno);
    }

    PUT(wfp,"      neelem = n_edat(iedat_no,1)\n");
    PUT(wfp,"      nenode = n_edat(iedat_no,2)\n");

    /* 領域割り付け */
    PUT(wfp,"      call f_alloc(np_ielem,'perspect_%d(ielem)',neelem * nenode,0,0)\n",perspects);
    PUT(wfp,"      call f_alloc(np_matno,'perspect_%d(matno)',neelem ,0,0)\n",perspects);
    /* ielemの取得 */
    PUT(wfp,"      iunit = iedat_no + io_edat - 1\n");
    PUT(wfp,"      call get_ielem(iunit,feel(np_ielem),feel(np_matno),neelem,nenode)\n");

    PUT(wfp,"*\n");

    /* ワーク変数の割り付け */
    PUT(wfp,"      call f_alloc(np_xa, 'perspect%d(xa)',npmax,0,0)\n",perspects);
    PUT(wfp,"      call f_alloc(np_ya, 'perspect%d(xa)',npmax,0,0)\n",perspects);
    PUT(wfp,"      call f_alloc(np_za, 'perspect%d(xa)',npmax,0,0)\n",perspects);
    PUT(wfp,"      call f_alloc(np_knc,'perspect%d(knc)',neelem",   perspects);
    if(p_ptr->etype == RECT) PUT(wfp,"*2");
    PUT(wfp,",0,0)\n");

    PUT(wfp,"* Window ID\n");
    PUT(wfp,"      IWD = %d\n",p_ptr-> window_id);
    PUT(wfp,"*\n");

    PUT(wfp,"* Window Position\n");
    PUT(wfp,"      IWX = 0\n");
    PUT(wfp,"      IWY = 0\n");
    PUT(wfp,"*\n");

    WriteWinsiz(wfp,p_ptr->winsiz);
/*
    PUT(wfp,"* Window Size\n");
    PUT(wfp,"      IWW = %d\n",p_ptr->winsiz);
    PUT(wfp,"      IWH = %d\n",p_ptr->winsiz);
    PUT(wfp,"*\n");
    */

    PUT(wfp,"* Para FLAG 0:automatic 1:disp. range 2:value range 3:manual\n");
    PUT(wfp,"      IFLG = %d\n",p_ptr->IFLG);
    PUT(wfp,"*\n");

    if(p_ptr -> IFLG == 3) {   /* 全てマニュアル時には、UMAX,UMINを設定 */
	PUT(wfp,"      UMIN = %lf\n",p_ptr -> umin);
	PUT(wfp,"      UMAX = %lf\n",p_ptr -> umax);
    }

    /* 表示範囲指定フラグが立っていなければ自動指定 */
    if( p_ptr -> USE_EDATRANGE_flag == YES) {
	PUT(wfp,"      call EDATRANGE(x,y,feel(np_ielem),neelem,nenode,XMIN,XMAX,YMIN,YMAX)\n");
    }
    else {
	PUT(wfp,"      XMIN = %lf\n",p_ptr -> xmin);
	PUT(wfp,"      XMAX = %lf\n",p_ptr -> xmax);
	PUT(wfp,"      YMIN = %lf\n",p_ptr -> ymin);
	PUT(wfp,"      YMAX = %lf\n",p_ptr -> ymax);
    }

    PUT(wfp,"      call FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,0.0D0,10.0D0,0.0D0,10.0D0,IGRY)\n");
    PUT(wfp,"*\n");      
    PUT(wfp,"      call FEEL_PERSPECT(npmax,neelem,x,y,");
    PUT(wfp,FEM_VAR_NAME77,p_ptr->var);
    PUT(wfp,",feel(np_ielem),nenode,IWD,IFLG,XMIN,XMAX,YMIN,");
    PUT(wfp,"YMAX,UMIN,UMAX,");
    if(p_ptr->etype == TRI) {
	PUT(wfp,"%d",3);
    }
    else {
	PUT(wfp,"%d",4);
	if(p_ptr->etype != RECT) SystemAbort("Oh my god, in perspect_fort77");
    }
    PUT(wfp,",feel(np_xa),feel(np_ya),feel(np_za),feel(np_knc))\n");
    PUT(wfp,"*\n");

    /* タイトルを書く */
    PUT(wfp,"      call FEEL_TITLE('%d feel perspect[%d]',IWD)\n",
	p_ptr->window_id+1,perspects);

    /* メッセージが指定されていれば書く */
    if(p_ptr -> mesg != NULL ) {
	PUT(wfp,"      call FEEL_MESSAGE(%s,IWD)\n",p_ptr->mesg);
    }



    PUT(wfp,"      call report('perspect[%s] @feel:%d')\n",
	p_ptr->var,p_ptr->yylineno);
    PUT(wfp,"*\n");
    /*    PUT(wfp,"      np_work=np_push\n"); OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_pop\n");
    PUT(wfp,"*\n");
    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");

    CloseFile(wfp);

    return;
}
