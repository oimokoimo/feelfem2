/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   read_LISP_procedure.c
 *      Date:   1993/11/16
 *   
 *   Purpose:   LISPプログラムを読み込む
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

static char *lisp_lib_file[] = {

    "fs.l",         /* 数式微分ファイル */
    NULL
  };

read_LISP_procedure( fp )
     FILE *fp;
{

    LISP_SEND(fp,";-------------------------------------\n");
    LISP_SEND(fp,"; LISPプログラムの読み込み            \n");
    LISP_SEND(fp,";-------------------------------------\n");
    LISP_SEND(fp,"(load \"/usr/feel/feel_p2/src/lisp_exec/feel-package.l\")\n");
    LISP_SEND(fp,";-------------------------------------\n");
    return;
}


