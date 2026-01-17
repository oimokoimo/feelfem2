/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 * 
 *  Modified :2001/01/27   to new version of f_alloc
 * 
 *  main_prepare  ファイル設定、データ読み込みのコール文を生成する
 */
#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../system/system.h"

#include "../parallel/parallel.h"

main_prepare( fp )
     FILE *fp;
{
    
    /*--------------------------*/
    /* call file open routine   */
    /*--------------------------*/
    comment2(fp);
    

    PUT(fp,"      call f_alloc_init(MAX_FEEL)\n");
    COM;

    PUT(fp,"      imode      = 0\n");
    PUT(fp,"      call closefil(0)\n");

    if(parallel) {
	PUT(fp,"      npe = %d\n",parallel_npe);
    }

    COM;

    /* 時間初期化プログラム */
    if(parallel) {
	;
    }
    else {
	PUT(fp,"      call timeinit\n");
	COM;
    }

    PUT(fp,"      call %s\n",PROG_FILSET);    /* ファイル設定プログラム */

    /* 並列版用時間処理初期化ルーチン */
    if(parallel) {
	F77("      call time_rep(0,'before datinp',io_out,isum)\n");
	COM;
    }


    file_write_open_fort77(fp);               /* fwrite文用OPEN文       */

    
    /*--------------------------*/
    /* call data read routine   */
    /*--------------------------*/
    PUT(fp,"      call %s(feel)\n",PROG_DATINP_MAIN);  
    COM;

    if(parallel) {
	F77("      call time_rep(1,'after datinp',io_out,isum)\n");
    }
    else {
	PUT(fp,"      call report('DATA INPUT')\n");
    }


    return;
}

