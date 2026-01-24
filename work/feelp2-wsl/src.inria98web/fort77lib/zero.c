/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   zero.c
 *      Date:   1993/07/12
 *   
 *   Purpose:   feel fort77ライブラリ zero シリーズを作成
 *              
 *              
 */

#include <stdio.h>
#include "../system/system.h"
#include "../feel_def/feel_def.h"

#define FILENAME "zero.f"

void lib_zero()
{
    FILE *fp;

    StoreMakefile(FILENAME , SYSTEM_LIBRARY);
    if(LIMIT_FILE == 1) return;

    fp = OpenFileToWrite(FILENAME);

    /* 整数変数初期化プログラム */
    F77("      subroutine zeroi(it,n)\n");
    F77("      dimension it(n)\n");
    F77("      do 100 i=1,n\n");
    F77(" 100  it(i) = 0\n");
    F77("      return\n");
    F77("      end\n");

    /* 倍精度実数変数初期化プログラム */
    F77("      subroutine zerod(dt,n)\n");
    F77("      real * 8   dt\n");
    F77("      dimension dt(n)\n");
    F77("      do 100 i=1,n\n");
    F77(" 100  dt(i) = 0.0d0\n");
    F77("      return\n");
    F77("      end\n");

    CloseFile(fp);
    return;
}
