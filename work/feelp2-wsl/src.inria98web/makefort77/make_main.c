/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 * 
 */

#include <stdio.h>
#include "MainProgram.h"
#include "../system/system.h"
#include "../feel_def/feel_def.h"

#include "main.h"

/* 並列版は、para_make_main.c にて作成する */
/* AVS version is prcessed in this routine */

make_main()
{
    
    FILE *fp,*OpenFileToWrite();

    /* make system subroutines */
    rep_proc("goto make_filset");
    make_filset();

    rep_proc("goto make_datinp");
    make_datinp();

    fp = OpenFileToWrite(FEEL_MAIN);

    StoreMakefile(FEEL_MAIN,USER_LIBRARY);

    rep_proc("goto main_declare");
    main_declare(fp);      /* メインプログラムの宣言部分                 */

    rep_proc("goto main_prepare");
    main_prepare(fp);      /* ファイル設定、データ読み込み、feel()の設定 */


    rep_proc("goto main_const_let");
    main_const_let(fp);    /* 定数変数の代入文 */
/*  main_meshdat(fp);  */  /* meshの点の名称←→節点番号等の対応テーブル */

    rep_proc("goto main_subdomain");
    main_subdomain(fp);    /* subdomain指定時の処理 */

    rep_proc("goto main_variable");
    main_variable(fp);     /* fem変数、ewise変数等の設定                 */

    if(avs_mode) {
      F77("      if(meshonly .EQ. 999) goto 9999\n");
    }

    rep_proc("goto main_scheme");
    main_scheme(fp);       /* スキームブロックのドライブルーチン         */

    comment1(fp);

    close_let_fp();           /* 単一let文の場合       */
    close_file_fort77(fp);    /* close data ファイル   */


    if(is_x11_flag() && web_mode != 1 && avs_mode != 1) {
	F77("      write(io_stderr,*) 'Click the window to terminate'\n");
	F77("      call vewt(0)\n");
	COM;
	comment1(fp);
    }

    /* 最終レポートルーチン */
    F77("      call rep_last\n");
    COM;

    if(avs_mode) {
      fprintf(fp,"8888  continue\n");
      fprintf(fp,"      if(imode .gt. 0) then\n");
      fprintf(fp,"        call avserrmsgalloc(UCD_id,IARGSIZ,imode)\n");
      fprintf(fp,"        call doclosefil(-1)\n");
      fprintf(fp,"        return\n");
      fprintf(fp,"      endif\n");
      fprintf(fp,"*\n");
      fprintf(fp,"9999  continue\n");
      fprintf(fp,"      call %s",AVS_OUTPUT_SUBFUNC);
      fprintf(fp,"(feel,UCD_id,event_mask,seq_num,IARGSIZ,imode,\n");
      fprintf(fp,"     $     feel(np_x),feel(np_y)");

      rep_proc("goto listup_avsoutput_in_main_fp");
      listup_avsoutput_in_main_fp(fp);
      fprintf(fp,")\n");
      fprintf(fp,"*\n");

      fprintf(fp,"      call doclosefil(-1)\n");
      fprintf(fp,"*\n");
      
      fprintf(fp,"      return\n");
      fprintf(fp,"*\n");
    }
    else {
      fprintf(fp," 8888 if(imode .gt. 0) then\n");
      fprintf(fp,"        write(io_stderr,*) 'Shortage of MAX_FEEL ',imode\n");
      fprintf(fp,"        call doclosefil(-1)\n");
      fprintf(fp,"        stop 'memory allocation error'\n");
      fprintf(fp,"      else\n");
      fprintf(fp,"        if(imode .eq. %d) then\n",ERROR_IMODE_NONLINEAR_DIVERGENT);
      fprintf(fp,"          call doclosefil(-1)\n");
      fprintf(fp,"          stop 'Divergent in Newton Method'\n");
      fprintf(fp,"        endif\n");
      fprintf(fp,"*\n");      
      fprintf(fp,"      endif\n");
      fprintf(fp,"*\n");


      fprintf(fp,"      call doclosefil(-1)\n");
      fprintf(fp,"*\n");
    }

    fprintf(fp,"      end\n");
    CloseFile(fp);
    return;
}
