/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1993/09/02
 *   
 *   Purpose:   solve_lisp_exec.c
 *   Functions: solve_lisp_exec()
 *              
 *              solve文に関連するLISPプログラムを実行する
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

void solve_lisp_exec()
{
    char com[BUFSIZ];

    sprintf(com,"lisp < %s >lisp_debug.l",LISP_EXEC_FILE);

    system(com);
    DBGWRT("\n.....done\n");

    return;
}
