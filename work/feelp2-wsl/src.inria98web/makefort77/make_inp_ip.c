/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   make_inp_node.c
 *      Date:   1993/06/10 (Modified)
 *   
 *   Purpose:   mesh節点番号 実節点番号対応データ入力プログラム生成ルーチン
 *   Functions: 節点情報入力プログラムの名称は INP_IP
 *              
 *              
 */

#include <stdio.h>
#include "../system/system.h"
#include "Extern.h"
#include "../feel_def/feel_def.h"

make_inp_ip()   /* 初期節点番号節点入力プログラムの作成 */
{
    FILE *fp;
    
    fp = OpenFileToWrite(INP_IP);
    
    PUT(fp,"      subroutine %s\n",PROG_INP_IP);

    /*==========*/
    /* 定形処理 */
    /*==========*/
    CopyRight(fp);
    real8(fp);
    common_parameters(fp);
    CommonBlock(fp);
    comment2(fp);
    
    PUT(fp," 8001 read(io_in,9001,end=8900) (n_nodeno(i),i=1,nip)\n");
    PUT(fp," 9001 format((8i8))\n");
    PUT(fp,"      return\n");
    comment1(fp);
    PUT(fp," 8900 write(io_stderr,*) 'IP DATA ERROR'\n");
    PUT(fp,"      stop 'inp_ip'\n");
    PUT(fp,"      end\n");
    
    CloseFile(fp);
    
    return;
}
