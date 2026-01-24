/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   showvec_fort77.c
 *      Date:   1994/02/09
 *   
 *   Purpose:   ２次元ベクトル図
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

static int showvecs = 0;


void showvec_fort77( fp  , s_ptr )
     FILE *fp;
     Showvec *s_ptr;
{
    FILE *wfp;
    FEM_var  *fem_var_ptr_x,*fem_var_ptr_y;
    FEM_type *fem_type_ptr;
    Subdomain *subdomain_ptr;
    char fname[80];

    /* feel_main.f中のcall文作成 */
    showvecs++;
    F77("      call ");
    PUT(fp,SHOWVEC_NAME,showvecs);
    PUT(fp,"(feel,feel(np_x),feel(np_y),feel(npf_%s),feel(npf_%s))\n",
	s_ptr->x,s_ptr->y);


    /* showvec*.f の作成 */
    sprintf(fname,SHOWVEC_FNAME,showvecs);

    StoreMakefile( fname ,USER_LIBRARY);
    wfp = OpenFileToWrite( fname );

    /* subroutine文 */
    PUT(wfp,"      subroutine ");
    PUT(wfp,SHOWVEC_NAME,showvecs);
    PUT(wfp,"( feel, x, y, vx, vy ) \n");   /* ルーチン内ではvx,vyで済ます */

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

    PUT(wfp,"      dimension vx(*),vy(*)\n");

    CommonBlock(wfp);
    comment1(wfp);

    /* edatデータの読み込み */
    /*    PUT(wfp,"      np_push = np_work\n"); OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_push\n");
    PUT(wfp,"*\n");

    if(s_ptr -> subdomain == NULL) {
	PUT(wfp,"* Whole domain EDAT data no is 1\n");
	PUT(wfp,"      iedat_no =1\n");
    }
    else {
	subdomain_ptr = get_subdomain_ptr_by_name(s_ptr->subdomain);
	PUT(wfp,"* subdomain [%s]\n",s_ptr->subdomain);
	PUT(wfp,"      iedat_no = %d\n",subdomain_ptr->edatno);
    }

    PUT(wfp,"      neelem = n_edat(iedat_no,1)\n");
    PUT(wfp,"      nenode = n_edat(iedat_no,2)\n");
    PUT(wfp,"      call f_alloc(np_ielem,'showvec_%d(ielem)',neelem * nenode,0,0)\n",showvecs);
    PUT(wfp,"      call f_alloc(np_matno,'showvec_%d(matno)',neelem ,0,0)\n",showvecs);
    /* ielemの取得 */
    PUT(wfp,"      iunit = iedat_no + io_edat - 1\n");
    PUT(wfp,"      call get_ielem(iunit,feel(np_ielem),feel(np_matno),neelem,nenode)\n");

    PUT(wfp,"*\n");

    /* ワーク領域確保 */

    PUT(wfp,"      call f_alloc(np_WK, 'showvec_%d(WK)',npmax*9 ,1,0)\n",showvecs);
    PUT(wfp,"      call f_alloc(np_IWK,'showvec_%d(IWK)',neelem ,1,0)\n",showvecs);

    PUT(wfp,"*\n");

    PUT(wfp,"* Window ID\n");
    PUT(wfp,"      IWD = %d\n",s_ptr-> window_id);
    PUT(wfp,"*\n");

    PUT(wfp,"* ID (triangle or rectangle)\n");
    if(s_ptr->etype == TRI) {
	PUT(wfp,"      ID = 3\n");
    }
    else {
	PUT(wfp,"      ID = 4\n");
	if(s_ptr->etype != RECT) SystemAbort("Oh my god, in showvec_fort77");
    }

    PUT(wfp,"* Window Position\n");
    PUT(wfp,"      IWX = 0\n");
    PUT(wfp,"      IWY = 0\n");
    PUT(wfp,"*\n");

    WriteWinsiz(wfp,s_ptr->winsiz);

/*    PUT(wfp,"* Window Size\n");
    PUT(wfp,"      IWW = %d\n",s_ptr->winsiz);
    PUT(wfp,"      IWH = %d\n",s_ptr->winsiz);
    PUT(wfp,"*\n"); */

    PUT(wfp,"* Para IFLG (0:full auto set 1:auto XRANGE 2:auto VMAX 3:MANUAL\n");
    PUT(wfp,"      IFLG = %d\n",s_ptr->IFLG);
    PUT(wfp,"*\n");

    PUT(wfp,"* ALLOW TYPE   0:paint 1:line only 2:MONOCHROME\n");
    if(s_ptr->mono_flag == YES) {
	PUT(wfp,"      IOUT = 2\n");
    }
    else {
	PUT(wfp,"      IOUT = 0\n");
    }

    PUT(wfp,"*\n");

    PUT(wfp,"* VM vector factor  \n");  
    PUT(wfp,"      VM = %lf\n",s_ptr->vm);

    PUT(wfp,"* Mesh draw flag 0:no mesh line  1:draw mesh line\n");
    PUT(wfp,"      IMSH = %d\n",s_ptr->mesh_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* Gray scale 0=color 1=gray\n");
    PUT(wfp,"      IGRY = %d\n",s_ptr->gray_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* ITYPE      1 = each node, 0 = each element\n");
    PUT(wfp,"      ITYPE = %d\n",s_ptr->ITYPE);
    PUT(wfp,"*\n");

    if(s_ptr->USE_EDATRANGE_flag == YES) {
	PUT(wfp,"      call EDATRANGE(x,y,feel(np_ielem),neelem,nenode,XMIN,XMAX,YMIN,YMAX)\n");
    }
    else {
	PUT(wfp,"      XMIN = %lf\n",s_ptr->xmin);
	PUT(wfp,"      XMAX = %lf\n",s_ptr->xmax);
	PUT(wfp,"      YMIN = %lf\n",s_ptr->ymin);
	PUT(wfp,"      YMAX = %lf\n",s_ptr->ymax);
    }
    PUT(wfp,"*\n");

    /* VMAXの設定 */
    if(s_ptr->IFLG == 3) {
	PUT(wfp,"      VMAX = %lf\n",s_ptr->vmax);
    }
    else {
	PUT(wfp,"*     VMAX will be set automatically\n");
    }
    PUT(wfp,"*\n");

    PUT(wfp,"*\n");

    PUT(wfp,"      call FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX,IGRY)\n");
    PUT(wfp,"*\n");      
    PUT(wfp,"      call FEEL_VECTOR(vx,vy,npmax,neelem,x,y,feel(np_ielem),");
    PUT(wfp,"nenode,ID,ITYPE,IWX,IWY,IWW,IWH,IWD,IFLG,XMIN,XMAX,YMIN,YMAX,");
    PUT(wfp,"VMAX,VM,IOUT,IMSH,feel(np_WK),feel(np_IWK))\n");

    PUT(wfp,"*\n");

    /* タイトルを書く */
    PUT(wfp,"      call FEEL_TITLE('%d feel showvec[%d]',IWD)\n",
	s_ptr->window_id+1,showvecs);

    /* メッセージが指定されていれば書く */
    if(s_ptr -> mesg != NULL ) {
	PUT(wfp,"      call FEEL_MESSAGE(%s,IWD)\n",s_ptr->mesg);
    }


    PUT(wfp,"      call report('showvec[%s,%s] @feel:%d')\n",
	s_ptr->x,s_ptr->y,s_ptr->yylineno);
    PUT(wfp,"*\n");
    /*    PUT(wfp,"      np_work=np_push\n");   OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_pop\n");
    PUT(wfp,"*\n");
    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");

    CloseFile(wfp);

    return;
}
