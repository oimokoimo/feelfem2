/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   fort77lib_make.c
 *      Date:   1993/06/17 (Modified)
 *   
 *   Purpose:   ライブラリとして使われるプログラムを生成する
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../parallel/parallel.h"

#include "fort77lib.h"

/* この関数はライブラリをソースファイルとして出力する時の為のもの */

void fort77lib_make()
{
    /* LIMIT_FILE の検査は各lib_XXXルーチンで行う。
       これは、StoreMakefileを実行する為である      */


    if(skyline_flag) {
      lib_cal_ht();    /* スカイラインの高さを求めるプログラム */
      lib_sol();       /* 連立一次方程式ルーチン */
      lib_scal();      /* subprogram for sol routine */
    }
    lib_get_ielem(); /* ielemデータ入力ルーチン */
    lib_ipd_make();  /* IPD(累積節点自由度配列)作成ルーチン */
    lib_make_KLD();  /* KLDを作るルーチン */
    lib_set();       /* 値を代入するルーチン */
    lib_zero();      /* ０を代入するルーチン */
    lib_f_alloc();   /* f_allocルーチン      */
    lib_f_free();    /* f_freeルーチン       */
    lib_inpdat_wrt(); /* INPUTデータチェックルーチン */
    lib_ipf_nfree();  /* 節点毎自由度を代入するルーチン */
    lib_ipd_nonode(); /* 節点無し自由度に関する処理 */
    lib_get_inset();  /* read inset data array from file */
    lib_edatrange();  /* コンター用にedatデータのxmin,xmax,ymin,ymaxを求める */
    lib_diskio();     /* disk io subroutines */
    lib_closefil();   /* close all files */

    /* 並列処理版 */
    if(parallel) {
	parallel_lib_make();    /*  ../parallel_libディレクトリ内の変数 */
	lib_parallel_report();  /* report program for parallel library  */
    }
    else {
        lib_report();     /* CPU時間計測および、REPORT作成 */
    }

    /* subdomain拡張 */
    if(subdomain_flag) {
	lib_mk_subdomain_edat();
	lib_mk_subdomain_nset();
    }

    /* 時間計測関数 */
    switch( MACHINE ) {
      case EWS4800:
      case EWS4800_R4000:
	lib_ews4800_erapse_time();
	break;

      case CONVEX:
	lib_convex_erapse_time();
	break;

      case IRIS:
/*	lib_ews4800_erapse_time();
	lib_iris_cptime();
*/   /* Use FreeBSD routine */
	break;

      case DEC_ALPHA:
	lib_alpha_erapse_time();
	break;

      case SPARC:
	lib_sparc_erapse_time();
	break;

      case FreeBSD:
      case Linux:
	/* FreeBSD and Linux's cptime routine is written in C library */
	break;

      case Windows:
	lib_MSFortran_erapse_time();

      default:
	break;
    }
    return;
}

