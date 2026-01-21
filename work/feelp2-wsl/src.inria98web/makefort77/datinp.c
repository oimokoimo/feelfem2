/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *  make data input routine
 */

#include <stdio.h>
#include "../system/system.h"
#include "Extern.h"
#include "../feel_def/feel_def.h"
#include "../parallel/parallel.h"



make_datinp()
{
    int i;
    FILE *fp;

    StoreMakefile( DATINP_MAIN , SYSTEM_LIBRARY);   /* Makefile への登録 */    
    StoreMakefile(INP_NODE     , SYSTEM_LIBRARY);
    StoreMakefile( INP_EDAT    , SYSTEM_LIBRARY);
    StoreMakefile( INP_NSET    , SYSTEM_LIBRARY);
    StoreMakefile( INP_NUM     , SYSTEM_LIBRARY);
    StoreMakefile( INP_IP      , SYSTEM_LIBRARY);


    if(LIMIT_FILE == 1) return;    /* LIMIT_FILE時にはファイル作成をしない */

    /* datinpプログラムの孫プログラムの作成 */

    make_inp_node();    /* 節点読み込みプログラム生成 */
    make_inp_edat();    /* 要素データ読み込みプログラム生成 */
    make_inp_nodeset();    /* 節点集合データ読み込みプログラム生成 */

    make_inp_num();     /* 数値データ読み込みプログラム生成 */
    make_inp_ip();      /* メッシュ生成時節点番号と実節点番号の対応データ */
/*    make_inp_comt();  */  /* コメントデータ読み込みプログラム生成   */
/*    make_inpdat_wrt();*/  /* 入力データチェックライトプログラム生成 */


    /* ファイルオープン */
    fp = OpenFileToWrite( DATINP_MAIN );


    /*====================*/
    /* subroutine文の作成 */
    /*====================*/

    PUT(fp,"      subroutine %s(feel)\n",PROG_DATINP_MAIN);

    /*----------*/
    /* 定形処理 */
    /*----------*/
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);
    common_parameters(fp);

    /*---------------*/
    /* dimension宣言 */
    /*---------------*/

    PUT(fp,"      real*4 feel(*)\n");
    PUT(fp,"      character*4 word\n");

    CommonBlock(fp);
    comment1(fp);
/*----------------------------------------------*/

    PUT(fp,"      read(io_in,9000) word\n");
    PUT(fp," 9000 format(a4)\n");
    PUT(fp,"      if(word .ne. %s) then\n",KEY_FEEL);
    PUT(fp,"        write(io_stderr,*) 'FEEL DATA ERROR'\n");
    PUT(fp,"        stop 'NOT FEEL DATA FILE'\n");
    PUT(fp,"      endif\n");
    comment1(fp);

    /*------------------------------------*/
    /*  問題記述の基本パラメータ読み込み  */
    /*------------------------------------*/
    F77("      read(io_in,9001) ndim,npmax,nedat,nodeset,numset,nip"); CR;
    F77(" 9001 format(6i8)"); CR;
    COM;

    /* 並列版拡張 */
    if(parallel) {
	F77("      nnodeset = nodeset\n");
	F77("      nnumdat  = numset\n");
    }
    

    F77("      read(io_in,9002) mode_ex,mode_output"); CR;
    F77(" 9002 format(2i8)"); CR;

    COM;
    F77("      read(io_in,9003) nvars_fem,nvars_ewise"); CR;
    F77(" 9003 format(2i8)"); CR;

    /*----------------------------*/
    /* 基本入力データのエラー検査 */
    /*----------------------------*/
    F77("      if(ndim .ne. 1 .and. ndim .ne. 2 .and. ndim .ne.3 ) then"); CR;
    F77("        stop 'ndim error'"); CR;
    F77("      endif"); CR;
    COM;
    F77("      if(nedat .gt. MAX_EDATSET) then"); CR;
    F77("       stop 'nedat error'"); CR;
    F77("      endif"); CR;
    COM;
    F77("      if(nodeset .gt. MAX_NODESET) then"); CR;
    F77("        stop 'nodeset error'"); CR;
    F77("      endif"); CR;
    COM;
    F77("      if(numset .gt. MAX_NUMSET) then"); CR;
    F77("        stop 'numset error'"); CR;
    F77("      endif"); CR;
    COM;
    F77("      do 100 i = 1,nedat"); CR;
    F77("        n_edat(i,1) = 0"); CR;
    F77(" 100  continue"); CR;
    COM;
    F77("      do 101 i = 1,nodeset"); CR;
    F77("        n_nset(i,1) = 0"); CR;
    F77("        n_nset(i,2) = 0"); CR;
    F77(" 101  continue"); CR;
    COM;
    F77("      do 102 i = 1,numset"); CR;
    F77("        n_num(i) = 0"); CR;
    F77(" 102  continue"); CR;
    COM;
    F77("      if(nvars_ewise.eq.0) goto 200"); CR;
    F77("      do 150 i=1,nvars_ewise"); CR;
    F77("        read(io_in,9005) n_ewise(i,1),n_ewise(i,2)"); CR;
    F77(" 9005   format(2i8)"); CR;
    F77("  150 continue"); CR;
    F77("  200 continue"); CR;
    
    comment1(fp);
    /*=========================================*/
    /*  読み込んだndimによって次元の判定を行う */
    /*  ndimは、基本節点座標の次元を定める     */
    /*=========================================*/
    /*    F77("      np_x = 1"); CR;
	  F77("      np_y = np_x + (npmax * 2)"); CR;
	  F77("      np_z = np_y + (npmax * 2)"); CR;
	  COM;                                          */
    /*  F77("      if(ndim .eq. 1) np_work = np_y"); CR; OLD F_ALLOC */
    /*  F77("      if(ndim .eq. 2) np_work = np_z"); CR;       OLD F_ALLOC */
    /*  F77("      if(ndim .eq. 3) np_work = np_z + (npmax*2)"); OLD F_ALLOC */

    F77("      call f_alloc(np_x,'x coordinate',npmax,1,0)\n");
    F77("      if(ndim .gt. 1) then\n");
    F77("        call f_alloc(np_y,'y coordinate',npmax,1,0)\n");
    F77("      endif\n");
    F77("      if(ndim .gt. 2) then\n");
    F77("        call f_alloc(np_z,'z coordinate',npmax,1,0)\n");
    F77("      endif\n");
		      
    comment1(fp);
    
    F77(" 8001 continue"); CR;
    COM;

    /*================================*/
    /* 入力データキーワードの読み込み */
    /*================================*/

    F77("      read(io_in,9010,end=8900) word"); CR;
    F77(" 9010 format(a4)"); CR;
    COM;
    
    /*--------------------*/
    /* データファイル終了 */
    /*--------------------*/
    
    PUT(fp,"      if(word .eq. %s) goto 8010\n",KEY_END);

    /*--------------------------*/
    /* 節点座標データの読み込み */
    /*--------------------------*/
    PUT(fp,"      if(word .eq. %s) then\n",KEY_NODE); CR;
    PUT(fp,"        if(ndim .eq. 1) call %s1(feel(np_x))\n",PROG_INP_NODE); CR;
    PUT(fp,"        if(ndim .eq. 2) call %s2(feel(np_x),feel(np_y))\n",PROG_INP_NODE); CR;
    PUT(fp,"        if(ndim .eq. 3) call %s3(feel(np_x),feel(np_y),\n     &                                 feel(np_z))\n",PROG_INP_NODE); CR;
    PUT(fp,"      endif\n");

    /*--------------------------*/
    /* 要素節点データの読み込み */
    /*--------------------------*/
    comment1(fp);
    PUT(fp,"      if(word .eq. %s) then\n",KEY_EDAT);
    PUT(fp,"        read(io_in,'(3i8)') no,nelem,np\n");
    COM;
    /*    F77(   "        np_push = np_work\n"); OLD F_ALLOC */
    F77(   "        call f_alloc_push\n");
    
    F77(   "        call f_alloc(np_ielem,'EDAT READ(ielem)',nelem*np,0,0)"); CR;
    F77(   "        call f_alloc(np_matno,'EDAT READ(matno)',nelem   ,0,0)"); CR;
    F77(   "        n_edat(no,1) = nelem"); CR;
    F77(   "        n_edat(no,2) = np"); CR;
    PUT(fp,"        call %s(no,nelem,np,feel(np_ielem),feel(np_matno))\n",PROG_INP_EDAT);
    /*    F77(   "        np_work = np_push\n");  OLD F_ALLOC */
    F77(   "        call f_alloc_pop\n");
    F77(   "      endif\n");
    comment1(fp);

    /*--------------------------*/
    /* 節点集合データの読み込み */
    /*--------------------------*/
    PUT(fp,"      if(word .eq. %s) then\n",KEY_NSET);
    PUT(fp,"        read(io_in,'(3i8)') no,nodes,np\n");
    COM;
    F77(   "        if(no .lt. 1 .or. no .gt.nodeset) then\n");
    F77(   "          write(*,*) 'nodeset no = ',no\n");
    F77(   "          stop 'nodeset error'\n");
    F77(   "        endif\n");
    COM;
    F77(   "        n_nset(no,1) = nodes\n");
    F77(   "        n_nset(no,2) = np\n");


    /*    F77(   "        np_push = np_work\n");  OLD F_ALLOC */
    F77(   "        call f_alloc_push\n");
 
    F77(   "        call f_alloc(np_inset,'NSET READ(inset)',nodes*np,0,0)"); CR;    
    PUT(fp,"        call %s(no,nodes,np,feel(np_inset))\n",PROG_INP_NSET);


    /* F77(   "        np_work = np_push\n"); OLD F_ALLOC */
    F77(   "        call f_alloc_pop\n");

    F77(   "      endif\n");
    comment1(fp);

    /*--------------------------*/
    /* 数値集合データの読み込み */
    /*--------------------------*/
    PUT(fp,"c      if(word .eq. %s) call %s\n",KEY_NUM,PROG_INP_NUM);
    PUT(fp,"      if(word .eq. %s) stop 'future function NUM'\n",KEY_NUM);
    comment1(fp);


    /*--------------------------------------------*/
    /* mesh節点番号と実節点番号の対応配列読み込み */
    /*--------------------------------------------*/
    PUT(fp,"      if(word .eq. %s) call %s\n",KEY_IP,PROG_INP_IP);
    comment1(fp);

    /*--------------------*/
    /* コメントの読み込み */
    /*- ------------------*/
/*
    PUT(fp,"      if(word .eq. %s) call %s\n",KEY_COMT,PROG_INP_COMT);
*/
    comment1(fp);


    F77("       goto 8001"); CR;
    comment1(fp);

    F77(" 8900 continue"); CR;
    F77("      write(io_stderr,9901)"); CR;
    F77(" 9901 format(' no end key word')"); CR;
    comment1(fp);


    F77(" 8010 continue"); CR;

      
    /*----------------------------------*/
    /* 節点情報データ読み込み部分       */
    /*----------------------------------*/


    fprintf(fp,"      if(mode_output .eq. %d) call inpdat_wrt\n",NORMAL_OUTPUT);
    fprintf(fp,"      if(mode_output .eq. %d) call inpdat_wrt\n",IGNORE_GRAPH);

    fprintf(fp,"c\n");
    fprintf(fp,"      return\n");
    fprintf(fp,"      end\n");

    CloseFile( fp );

    return;
}





