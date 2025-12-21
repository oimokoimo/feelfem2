/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   zero.c
 *      Date:   1993/07/13
 *   
 *   Purpose:   feel fort77ライブラリ makeipd の作成
 *              
 *              累積節点自由度配列を作成する
 *              また、方程式の数,neqを求める
 *              
 */

#include <stdio.h>
#include "../system/system.h"
#include "../feel_def/feel_def.h"

#define FILENAME "set.f"

lib_set()
{
    FILE *fp;

    StoreMakefile(FILENAME ,SYSTEM_LIBRARY);
    if(LIMIT_FILE == 1) return;
    
    fp = OpenFileToWrite(FILENAME);

    /* 値の初期化プログラム */
    F77("      subroutine seti(it,num,n)\n");
    F77("      dimension it(n)\n");
    COM;
    F77("      do 100 i=1,n\n");
    F77("        it(i) = num\n");
    F77(" 100  continue\n");
    F77("      return\n");
    F77("      end\n");

    F77("      subroutine setd(dt,dnum,n)\n");
    F77("      real*8 dt,dnum\n");
    F77("      dimension dt(n)\n");
    COM;
    F77("      do 100 i=1,n\n");
    F77("        dt(i) = dnum\n");
    F77(" 100  continue\n");
    F77("      return\n");
    F77("      end\n");

    CloseFile(fp);
    return;
}
