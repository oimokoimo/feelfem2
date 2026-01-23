/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   contour_fort77.c
 *      Date:   1993/12/15
 *   
 *   Purpose:   ２次元変位図
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

static int displacements = 0;

void displacement_fort77( fp  , d_ptr )
     FILE *fp;
     Displacement *d_ptr;
{
    FILE *wfp;
    FEM_var  *fem_var_ptr;
    FEM_type *fem_type_ptr;
    Subdomain *subdomain_ptr;
    char fname[80];

    /* feel_main.f中のcall文作成 */
    displacements++;
    F77("      call ");
    PUT(fp,DISPLACEMENT_NAME,displacements);
    PUT(fp,"(feel,feel(np_x),feel(np_y),feel(npf_%s),feel(npf_%s)"
	,d_ptr->u_var,d_ptr->v_var);
    if(d_ptr -> p_var != NULL) {
	PUT(fp,",feel(npf_%s)",d_ptr->p_var);
    }
    PUT(fp,")\n");



    /* contr*.fの作成 */
    sprintf(fname,DISPLACEMENT_FNAME,displacements);

    StoreMakefile( fname ,USER_LIBRARY);
    wfp = OpenFileToWrite( fname );

    /* subroutine文 */
    PUT(wfp,"      subroutine ");
    PUT(wfp,DISPLACEMENT_NAME,displacements);
    PUT(wfp,"( feel, x, y,");
    PUT(wfp,FEM_VAR_NAME77,d_ptr->u_var); PUT(wfp,",");
    PUT(wfp,FEM_VAR_NAME77,d_ptr->v_var);
    if(d_ptr->p_var != NULL) {
	PUT(wfp,","); 
	PUT(wfp,FEM_VAR_NAME77,d_ptr->p_var);
    }
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
    PUT(wfp,"      dimension ic(2)\n");

    PUT(wfp,"      dimension ");
    PUT(wfp,FEM_VAR_NAME77,d_ptr->u_var);    PUT(wfp,"(*),");
    PUT(wfp,FEM_VAR_NAME77,d_ptr->v_var);    PUT(wfp,"(*)");
    if(d_ptr->p_var != NULL) {
	PUT(wfp,","); PUT(wfp,FEM_VAR_NAME77,d_ptr->p_var);    PUT(wfp,"(*)");
    }
    PUT(wfp,"\n");

    CommonBlock(wfp);
    comment1(wfp);

    /* edatデータの読み込み */
    
    /* PUT(wfp,"      np_push = np_work\n"); OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_push\n");

    if(d_ptr -> subdomain == NULL) {
	PUT(wfp,"* Whole domain EDAT data no is 1\n");
	PUT(wfp,"      iedat_no =1\n");
    }
    else {
	subdomain_ptr = get_subdomain_ptr_by_name(d_ptr->subdomain);
	PUT(wfp,"* subdomain [%s]\n",d_ptr->subdomain);
	PUT(wfp,"      iedat_no = %d\n",subdomain_ptr->edatno);
    }

    PUT(wfp,"      neelem = n_edat(iedat_no,1)\n");
    PUT(wfp,"      nenode = n_edat(iedat_no,2)\n");

    /* 領域割り付け */
    PUT(wfp,"      call f_alloc(np_ielem,'displacement_%d(ielem)',neelem * nenode,0,0)\n",displacements);
    PUT(wfp,"      call f_alloc(np_matno,'displacement_%d(matno)',neelem ,0,0)\n",displacements);

    /* ワーク領域の割り付け */
    PUT(wfp,"      call f_alloc(np_wx,'displacement%d(wx)',npmax,1,0)\n",
	displacements);
    PUT(wfp,"      call f_alloc(np_wy,'displacement%d(wx)',npmax,1,0)\n",
	displacements);

    /* p_var がNULLの時は、変位のノルムを表示する */
    if(d_ptr->p_var == NULL) {
	PUT(wfp,"      call f_alloc(np_dsp,'displacement%d(dsp)',npmax,1,0)\n",
	    displacements);
	PUT(wfp,"      call feel_vlen(npmax,");
	PUT(wfp,FEM_VAR_NAME77,d_ptr->u_var);    PUT(wfp,",");
	PUT(wfp,FEM_VAR_NAME77,d_ptr->v_var);    PUT(wfp,",");
	PUT(wfp,"feel(np_dsp))\n");
	comment1(wfp);
    }

    /* ielemの取得 */
    PUT(wfp,"      iunit = iedat_no + io_edat - 1\n");
    PUT(wfp,"      call get_ielem(iunit,feel(np_ielem),feel(np_matno),neelem,nenode)\n");

    PUT(wfp,"*\n");

    PUT(wfp,"* Window ID\n");
    PUT(wfp,"      IWD = %d\n",d_ptr-> window_id);
    PUT(wfp,"*\n");

    PUT(wfp,"* Window Position\n");
    PUT(wfp,"      IWX = 0\n");
    PUT(wfp,"      IWY = 0\n");
    PUT(wfp,"*\n");


    WriteWinsiz(wfp,d_ptr->winsiz);
/*
    PUT(wfp,"* Window Size\n");
    PUT(wfp,"      IWW = %d\n",d_ptr->winsiz);
    PUT(wfp,"      IWH = %d\n",d_ptr->winsiz);
    PUT(wfp,"*\n");
    */

    PUT(wfp,"* Para FLAG 0:automatic 1:disp. range 2:value range 3:manual\n");
    PUT(wfp,"      IFLG = %d\n",d_ptr->IFLG);
    PUT(wfp,"*\n");

    if(d_ptr -> IFLG == 3) {   /* 全てマニュアル時には、UMAX,UMINを設定 */
	PUT(wfp,"      ICS  = 1\n");
	PUT(wfp,"      SMIN = %lf\n",d_ptr -> umin);
	PUT(wfp,"      SMAX = %lf\n",d_ptr -> umax);
    }
    else {
	PUT(wfp,"      ICS   = 2\n");  /* しきい値flag  0:auto 1:manu 2:fullauto*/
	PUT(wfp,"      SMIN  = 0.0\n"); /* しきい値の最小値 */
	PUT(wfp,"      SMAX  = 1.0\n"); /* しきい値の最大値 */
    }

    PUT(wfp,"* Displacement TYPE   0:normal  1:ln\n");
    PUT(wfp,"      ITYP = %d\n",d_ptr->LOG_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* displacement lines\n");
    PUT(wfp,"      IDIV = %d\n",d_ptr->divide);
    PUT(wfp,"*\n");


    PUT(wfp,"* graph type     0:paint   1:line only\n");
    PUT(wfp,"      IOUT = %d\n",d_ptr->paint_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* show scale     0:not show  1:show\n");
    PUT(wfp,"      ISCL = %d\n",d_ptr->scale_flag);

    /* 変位後のメッシュを書く 1: かかない 0: */
    PUT(wfp,"* Mesh draw flag 0:no mesh line  1:draw mesh line\n");
    PUT(wfp,"      ICM = %d\n",d_ptr->mesh_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* Gray scale 0=color 1=gray\n");
    PUT(wfp,"      IGRY = %d\n",d_ptr->gray_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* Facotr\n");
    PUT(wfp,"      fact = %lf\n",d_ptr->fact);
    PUT(wfp,"*\n");

    PUT(wfp,"      ic(1) = 1\n");
    PUT(wfp,"      ic(2) =10\n");
    PUT(wfp,"      ISL   = 1\n");  /* 変位後の図の背景を塗りつぶす 1/0 */
    PUT(wfp,"      ICT   = 1\n");  /* 変位後のコンターを書く1/0        */
    PUT(wfp,"      IDV   =20\n");  /* 今他のしきい値 */
    PUT(wfp,"      ITP   = 1\n");  /* コンタ表示タイプ  0:line  1:paint */
    PUT(wfp,"      ICB   = 0\n");   /* カラーバーの有無 0:なし  1:あり */
    PUT(wfp,"      NCBX  = 10\n");  /* カラーバーの位置 x */
    PUT(wfp,"      NCBY  = 10\n");  /* カラーバーの位置 y */

    /* 表示範囲指定フラグが立っていなければ自動指定 */
    if( d_ptr -> set_flag % 10 == 0) {
	PUT(wfp,"      call EDATRANGE(x,y,feel(np_ielem),neelem,nenode,XMIN,XMAX,YMIN,YMAX)\n");
    }
    else {
	PUT(wfp,"      XMIN = %lf\n",d_ptr -> xmin);
	PUT(wfp,"      XMAX = %lf\n",d_ptr -> xmax);
	PUT(wfp,"      YMIN = %lf\n",d_ptr -> ymin);
	PUT(wfp,"      YMAX = %lf\n",d_ptr -> ymax);
    }

    PUT(wfp,"      call FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX,IGRY)\n");
    PUT(wfp,"*\n");      
    PUT(wfp,"      call FEEL_DSPLC(npmax,neelem,nenode,feel(np_ielem),x,y,");
    PUT(wfp,"feel(np_wx),feel(np_wy),");
    PUT(wfp,FEM_VAR_NAME77,d_ptr->u_var);  PUT(wfp,",");
    PUT(wfp,FEM_VAR_NAME77,d_ptr->v_var);  PUT(wfp,",");
    PUT(wfp,"fact,");
    if(d_ptr->p_var != NULL) {
	PUT(wfp,FEM_VAR_NAME77,d_ptr->p_var);
    }
    else {
	PUT(wfp,"feel(np_dsp)");
    }
    PUT(wfp,",IC,ISL,ICT,IDV,ICS,ITP,ICM,SMIN,SMAX,ICB,NCBX,NCBY,");
    if(d_ptr->etype == TRI) {
	PUT(wfp,"%d",3);
    }
    else {
	PUT(wfp,"%d",4);
	if(d_ptr->etype != RECT) SystemAbort("Oh my god, in displacement_fort77");
    }
    PUT(wfp,",IWD)\n");
    PUT(wfp,"*\n");

    /* タイトルを書く */
    PUT(wfp,"      call FEEL_TITLE('%d feel displacement[%d]',IWD)\n",
	d_ptr->window_id+1,displacements);

    /* メッセージが指定されていれば書く */
    if(d_ptr -> mesg != NULL ) {
	PUT(wfp,"      call FEEL_MESSAGE(%s,IWD)\n",d_ptr->mesg);
    }

    
    PUT(wfp,"      call report('displacement[%s,%s] @feel:%d')\n",
	d_ptr->u_var,d_ptr->v_var,d_ptr->yylineno);
    PUT(wfp,"*\n");

    /* PUT(wfp,"      np_work=np_push\n");   OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_pop\n");

    PUT(wfp,"*\n");
    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");

    CloseFile(wfp);

    return;
}
