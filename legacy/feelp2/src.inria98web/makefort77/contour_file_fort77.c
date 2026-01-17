/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   contour_file_fort77.c
 *      Date:   1994/01/17
 *   
 *   Purpose:   ２次元コンター図用ファイル作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../var_comp/var_comp.h"
#include "../mesh_comp/mesh_comp.h"

#include "../parallel/parallel.h"

static int contour_files = 0;

void contour_file_fort77( fp  , c_ptr )
     FILE *fp;
     Contour *c_ptr;
{
    FILE *wfp;
    FEM_var  *fem_var_ptr;
    FEM_type *fem_type_ptr;
    Subdomain *subdomain_ptr;
    char fname[80];

    /* feel_main.f中のcall文作成 */
    contour_files++;

    /* 並列処理 */
    if(parallel) {
	F77("      if(p_rank .EQ. 0) then\n");
    }

    F77("      call ");
    PUT(fp,CONTOUR_FILE_NAME,contour_files);
    PUT(fp,"(feel,feel(np_x),feel(np_y),feel(npf_%s))\n",c_ptr->var);

    
    /* 並列処理 */
    if(parallel) {
	F77("      endif\n");
    }


    /* contrf*.fの作成 */
    sprintf(fname,CONTOUR_FILE_FNAME,contour_files);

    StoreMakefile( fname ,USER_LIBRARY);
    wfp = OpenFileToWrite( fname );

    /* subroutine文 */
    PUT(wfp,"      subroutine ");
    PUT(wfp,CONTOUR_FILE_NAME,contour_files);
    PUT(wfp,"( feel, x, y,");
    PUT(wfp,FEM_VAR_NAME77,c_ptr->var);
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
    PUT(wfp,FEM_VAR_NAME77,c_ptr->var);
    PUT(wfp,"(*)\n");

    CommonBlock(wfp);
    comment1(wfp);

    /* edatデータの読み込み */
    /*    PUT(wfp,"      np_push = np_work\n");  OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_push\n");
    PUT(wfp,"*\n");

    if(c_ptr -> subdomain == NULL) {
	PUT(wfp,"* Whole domain EDAT data no is 1\n");
	PUT(wfp,"      iedat_no =1\n");
    }
    else {
	subdomain_ptr = get_subdomain_ptr_by_name(c_ptr->subdomain);
	PUT(wfp,"* subdomain [%s]\n",c_ptr->subdomain);
	PUT(wfp,"      iedat_no = %d\n",subdomain_ptr->edatno);
    }

    PUT(wfp,"      iedat_no =1\n");
    PUT(wfp,"      neelem = n_edat(iedat_no,1)\n");
    PUT(wfp,"      nenode = n_edat(iedat_no,2)\n");

    /* 領域割り付け */
    PUT(wfp,"      call f_alloc(np_ielem,'contour_file_%d(ielem)',neelem * nenode,0,0)\n",contour_files);
    PUT(wfp,"      call f_alloc(np_matno,'contour_file_%d(matno)',neelem ,0,0)\n",contour_files);
    /* ielemの取得 */
    PUT(wfp,"      iunit = iedat_no + io_edat - 1\n");
    PUT(wfp,"      call get_ielem(iunit,feel(np_ielem),feel(np_matno),neelem,nenode)\n");

    PUT(wfp,"*\n");

    if(c_ptr->etype == TRI) {
	PUT(wfp,"      IETYPE = %d\n",3);
    }
    else {
	PUT(wfp,"      IETYPE = %d\n",4);
	if(c_ptr->etype != RECT) SystemAbort("Oh my god, in contour_fort77");
    }

    

    PUT(wfp,"*\n");

    PUT(wfp,"* Window ID\n");
    PUT(wfp,"      IWD = %d\n",c_ptr-> window_id);
    PUT(wfp,"*\n");

    PUT(wfp,"* Window Size\n");
    PUT(wfp,"      IWW = %d\n",c_ptr->winsiz);
    PUT(wfp,"      IWH = %d\n",c_ptr->winsiz);
    PUT(wfp,"*\n");

    PUT(wfp,"* Para FLAG 0:automatic 1:disp. range 2:value range 3:manual\n");
    PUT(wfp,"      IFLG = %d\n",c_ptr->IFLG);
    PUT(wfp,"*\n");

    if(c_ptr -> IFLG == 3) {   /* 全てマニュアル時には、UMAX,UMINを設定 */
	PUT(wfp,"      UMIN = %lf\n",c_ptr -> umin);
	PUT(wfp,"      UMAX = %lf\n",c_ptr -> umax);
    }

    PUT(wfp,"* Contour TYPE   0:normal  1:ln\n");
    PUT(wfp,"      ITYP = %d\n",c_ptr->LOG_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* contour lines\n");
    PUT(wfp,"      IDIV = %d\n",c_ptr->divide);
    PUT(wfp,"*\n");

    PUT(wfp,"* graph type     0:paint   1:line only  2: monochro\n");
    PUT(wfp,"      IOUT = %d\n",c_ptr->paint_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* show scale     0:not show  1:show\n");
    PUT(wfp,"      ISCL = %d\n",c_ptr->scale_flag);

    PUT(wfp,"* Mesh draw flag 0:no mesh line  1:draw mesh line\n");
    PUT(wfp,"      IMSH = %d\n",c_ptr->mesh_flag);
    PUT(wfp,"*\n");

    PUT(wfp,"* Gray scale 0=color 1=gray\n");
    PUT(wfp,"      IGRY = %d\n",c_ptr->gray_flag);
    PUT(wfp,"*\n");

    /* 表示範囲指定フラグが立っていなければ自動指定 */
    if( c_ptr -> set_flag % 10 == 0) {
	PUT(wfp,"      call EDATRANGE(x,y,feel(np_ielem),neelem,nenode,XMIN,XMAX,YMIN,YMAX)\n");
    }
    else {
	PUT(wfp,"      XMIN = %lf\n",c_ptr -> xmin);
	PUT(wfp,"      XMAX = %lf\n",c_ptr -> xmax);
	PUT(wfp,"      YMIN = %lf\n",c_ptr -> ymin);
	PUT(wfp,"      YMAX = %lf\n",c_ptr -> ymax);
    }


    /* ファイル番号を得る */
    PUT(wfp,"      io_no = io_tmp + %d\n",c_ptr-> file_io_no);

    PUT(wfp,"      open(unit=io_no,file=%s,form='unformatted',status='UNKNOWN')\n",c_ptr->filename);
    PUT(wfp,"      write(io_no) npmax,neelem,nenode,IETYPE\n");
    PUT(wfp,"      write(io_no) XMIN,XMAX,YMIN,YMAX\n");
    PUT(wfp,"      write(io_no) IWD,IWW,IWH,IFLG,ITYP,IDIV,ISCL,IOUT,IMSH,UMAX,UMIN\n");


    PUT(wfp,"      call diskwrti(io_no,neelem*nenode,feel(np_ielem))\n");
    PUT(wfp,"      call diskwrtd(io_no,npmax,x)\n");
    PUT(wfp,"      call diskwrtd(io_no,npmax,y)\n");

    PUT(wfp,"      call diskwrtd(io_no,npmax,");
    PUT(wfp,FEM_VAR_NAME77,c_ptr->var);
    PUT(wfp,")\n");
    
    PUT(wfp,"*\n");

    if(!parallel) {
	PUT(wfp,"      call report('contour_file[%s] @feel:%d')\n",
	    c_ptr->var,c_ptr->yylineno);
	PUT(wfp,"*\n");
    }


    /*    PUT(wfp,"      np_work=np_push\n");    OLD F_ALLOC */
    PUT(wfp,"      call f_alloc_pop\n");
    PUT(wfp,"*\n");
    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");

    CloseFile(wfp);

    return;
}


int how_many_contour_files()
{
    return(contour_files);
}
