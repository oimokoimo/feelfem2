/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   XYZ_dimension.c
 *      Date:   1993/10/14
 *   
 *   Purpose:   XYZ_dimension     空間変数に対するdimension宣言を行う
 *              XYZ_in_call       空間変数のCALL文内引き数生成
 *              XYZ_in_subroutine 空間変数のSUBROUTINE文内等の仮引き数生成
 *   Functions: what_dimension() を呼び出す
 *              
 *              この次元は、システム次元(複数の次元が混在する問題はやめ)
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

void XYZ_dimension(fp)
     FILE *fp;
{
    switch(what_dimension()) {
      case 1:
	fprintf(fp,"      dimension x(*)\n");
	break;

      case 2:
	fprintf(fp,"      dimension x(*)\n");
	fprintf(fp,"      dimension y(*)\n");
	break;	

      case 3:
	fprintf(fp,"      dimension x(*)\n");
	fprintf(fp,"      dimension y(*)\n");
	fprintf(fp,"      dimension z(*)\n");
	break;	
    
      default:
	SystemAbort("what_dimension() ERROR (XYZ_dimension)");
    }

    return;
}

void XYZ_in_call(fp)
     FILE *fp;
{

    switch(what_dimension()) {
      case 1:
	F77("feel(np_x)");
	break;

      case 2:
	F77("feel(np_x),feel(np_y)");
	break;

      case 3:
	F77("feel(np_x),feel(np_y),feel(np_z)");
	break;

      default:
	SystemAbort("illegal what dimension() in let_call_xyz");
    }

    return;
}



void XYZ_in_subroutine(fp)
     FILE *fp;
{

    switch(what_dimension()) {
      case 1:
	F77("x");
	break;

      case 2:
	F77("x,y");
	break;

      case 3:
	F77("x,y,z");
	break;

      default:
	SystemAbort("illegal what dimension() in let_call_xyz");
    }

    return;
}
