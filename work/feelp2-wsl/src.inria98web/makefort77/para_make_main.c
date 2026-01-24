/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   para_make_main.c
 *      Date:   1995/09/13
 *   
 *   Purpose:   make main routine for parallel version(並列処理版)
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "main.h"


#include <stdio.h>
#include "MainProgram.h"
#include "../system/system.h"
#include "../feel_def/feel_def.h"

#include "../parallel/parallel.h"


para_make_main()
{
    
    FILE *fp;
    int i,data_files;

    /* make system subroutines */
    make_filset();
    make_datinp();

    fp = OpenFileToWrite(FEEL_MAIN);

    StoreMakefile(FEEL_MAIN,USER_LIBRARY);

    main_declare(fp);      /* メインプログラムの宣言部分                 */
    main_prepare(fp);      /* ファイル設定、データ読み込み、feel()の設定 */
    main_const_let(fp);    /* 定数変数の代入文 */
/*  main_meshdat(fp);  */  /* meshの点の名称←→節点番号等の対応テーブル */
    main_variable(fp);     /* fem変数、ewise変数等の設定                 */


    /*  (p-feel)  プロセッサ台数の入力 */
    F77("*\n");
    F77("* Number of processors\n");
    F77("*\n");
    PUT(fp,"      npe = %d\n",parallel_npe);



    /* 各solveブロックの情報配列へのインデックスを得る(p-feel)*/
    F77("*\n");
    F77("* allocate solve information data area\n");
    F77("*\n");
    for(i=0;i<how_many_solves();i++) {
	PUT(fp,"      call f_alloc(npp_base%d,'Base address for solve%d',npe*2,0,0)\n",i+1,i+1);
    }


    /* 並列版  ＭＰＩ宣言 (p-feel)*/
    F77("*------------------------------------------------\n");
    F77("*  Initialize MPI function\n");
    F77("*\n");

    F77("      call mpi_set_nr(npe,ierr)\n");
    F77("      if(ierr.ne.0) stop 'mpi_set_nr failed'\n");
    F77("      call mpi_init(ierr)\n");
    F77("      if(ierr.ne.0) stop 'mpi_init failed'\n");
    F77("      call mpi_top_communicator(mpi_comm_world,ierr)\n");
    F77("      if(ierr.ne.0) stop 'mpi_top_communicator failed'\n");

    F77("      call mpi_comm_size(mpi_comm_world,p_size,ierr)\n");
    F77("      if(ierr.ne.0) stop 'mpi_comm_size failed.'\n");
    F77("      call mpi_comm_rank(mpi_comm_world,p_rank,ierr)\n");
    F77("      if(ierr.ne.0) stop 'mpi_comm_rank failed.'\n");
    F77("*------------------------------------------------\n");


    /* 並列版  データ作成プログラム(p-feel) */
    F77("*------------------------------------------------\n");
    F77("* Make parallel data\n");
    F77("*------------------------------------------------\n");
    F77("      if(p_rank.eq.0) then\n");
    for(i=0;i<how_many_solves();i++) {
	
	
	/**/
	F77("*------------------------------------------------\n");
	PUT(fp,"* solve No.%d\n",i+1);
	F77(   "*------------\n");
	F77("*\n");
	
	PUT(fp,"      call ");
	PUT(fp,BLOCK_DATA_NAME,i+1);
	PUT(fp,"(feel(npp_base%d),feel)\n",i+1);
	F77("*------------------------------------------------\n");
    }
    F77("      endif\n");
    F77("*------------------------------------------------\n");

    /* ここからparallel block data 読み込みプログラム作成ルーチンを呼び出す */
    para_block_data();     /* parallel/ 内の関数 */

    main_scheme(fp);       /* スキームブロックのドライブルーチン         */

    comment1(fp);

    close_let_fp();           /* 単一let文の場合       */
    close_file_fort77(fp);    /* close data ファイル   */

    if(is_x11_flag()) {
	F77("      if(p_rank.eq.0) then\n");
	F77("*      write(io_stderr,*) 'Click the window to terminate'\n");
	F77("*      call vewt(0)\n");
	F77("       continue\n");
	F77("       endif\n");

	COM;
	comment1(fp);
    }

    /* 並列処理の終了処理(スクラッチファイル関係)*/
    if(parallel) {
	for(i=0;i<how_many_solves();i++) {
	    F77("*-----------\n");
	    PUT(fp,"%5d continue\n",9001+i);
	    F77("      if(p_rank.eq.0) then\n");
	    F77("        call p_close_file\n");
	    PUT(fp,"        NO = %d\n",i+1);
	    F77("        close(io_fem+NO-1)\n");
	    F77("      endif\n");
	}
    }
    F77("*-----------\n");

    /* 並列処理の終了処理(contour_file,showvec_file関数関係) */
    data_files = how_many_contour_files()+ how_many_showvec_files();
    if(data_files) {
	F77("* Close contour/showvec data files\n");
	F77("* -----\n");
	for(i=0;i<data_files;i++) {
	    PUT(fp,"      close(io_tmp+%d)\n",i+1);
	}
	F77("*-----------\n");
    }

    
    /* 並列処理の終了処理(MPI関数関係) */
    if(parallel) {
	F77(" 9999 continue\n");
	F77("*\n");
	F77("      call mpi_finalize(ierror)\n");
	F77("        if(ierror.ne.mpi_success) write(*,*) 'ERRNO=',ierrror\n");
	F77("        if(ierror.ne.mpi_success) stop 'MPI_FINALIZE error'\n");
    }
  
    /* 最終レポートルーチン */
    /* 並列版には無い */
    COM;

    fprintf(fp,"      end\n");
    CloseFile(fp);
    return;
}
