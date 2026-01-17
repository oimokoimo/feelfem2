/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File: showmesh.c
 *      Date: 1993/06/03
 *   
 *   Purpose: showmesh文の指定／非指定のフラグ
 *            
 */

#include "../feel_def/feel_def.h"

static int showmesh_flag = NO;

void showmesh_st()
{
    showmesh_flag = YES;
    return;
}

int is_showmesh()
{
    return(showmesh_flag);      /* YES -> Xウインドウにて表示する */
}     

