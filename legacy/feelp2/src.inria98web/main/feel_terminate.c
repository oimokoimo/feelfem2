/*
 * FEEL system Prototype Version 2
 * 
 * File     feel_terminate.c
 * Made     1992/09/04
 * Modified 
 * Version  0.0
 *
 * Purpose: FEEL TERMINATE program
 *
 */
#include <stdio.h>

#define STRESS  fprintf(stderr,"%c[5m",27)
#define NORMAL  fprintf(stderr,"%c[0m",27)

extern int not_implemented;

feel_terminate()
{

    /* DoDeletefile(); は、feel_exec_mainでやっている */
    /* DoDelefile();   dbg:  デバッグ中はこれを実行しない */
    /* EraseTemporaryFiles();  これは昔のばーじょん */

    /*                       これはやんぴ 
    DangerCodeReport();
    STRESS;
    fprintf(stderr,"NOT IMPLEMENTED MODULE = %d\n",not_implemented);
    NORMAL;
    */

    return;
}
