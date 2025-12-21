/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_etype_no.c
 *      Date:   1993/08/19
 *   
 *   Purpose:   要素形状を表す文字列から、要素形状番号に変換する
 *              このプログラムは、構文解析実行中に呼び出される様
 *              にすること。(yylineno を表示してエラー位置告知)
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

int get_etype_no( s )  /* 要素形状の文字列から要素タイプ番号に変換 */
     char *s;
{
    int yylineno;

    if(streq( LINE_STRING,s))  return(LINE);
    if(streq( TRI_STRING ,s))  return(TRI);
    if(streq( RECT_STRING,s))  return(RECT);
    if(streq( CUBE_STRING,s))  return(CUBE);
    if(streq( TETRA_STRING,s)) return(TETRA);

    yylineno = yylineno_info();

    SystemError_yy_s("%s is not element type.\n",s ,yylineno);

    return(ERR);
}

