/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   reverse_code_convert.c
 *      Date:   1993/09/03
 *   
 *   Purpose:   コード番号から逆に名称等を返す
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

static char *undefined_code = "未定義";

char *etype_no_to_name( no )
     int no;
{
    switch(no) {
      case LINE:
	return("線");
      case TRI:
	return("三角形");
      case RECT:
	return("四辺形");
      case CUBE:
	return("立方体");
      case TETRA:
	return("四面体");
      default:
	SystemError("内部エラー、予期しないetype番号が出現した");
	return( undefined_code );
    }
}


int etype_no_to_dimension( no )
     int no;
{
    switch(no) {
      case LINE:
	return(1);
      case TRI:
	return(2);
      case RECT:
	return(2);
      case CUBE:
	return(3);
      case TETRA:
	return(3);
      default:
	SystemError("内部エラー、予期しないetype番号が出現した");
	return(0 );
    }
}

