/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   make_inp_node.c
 *      Date:   1993/06/10 (Modified)
 *   
 *   Purpose:   節点情報入力プログラム生成ルーチン
 *   Functions: 節点情報入力プログラムの名称は INP_NODE
 *              
 *              
 */

#include <stdio.h>
#include "../system/system.h"
#include "Extern.h"
#include "../feel_def/feel_def.h"

make_inp_node()   /* 節点入力プログラムの作成 */
{
    FILE *fp;
    
    fp = OpenFileToWrite(INP_NODE);
    
    /* 一次元用プログラムの作成 */
    PUT(fp,"      subroutine %s1( x )\n",PROG_INP_NODE);
    CopyRight(fp);
    
    real8(fp);
    common_parameters(fp);
    
    PUT(fp,"      dimension x(*)\n");	
    CommonBlock(fp);
    comment2(fp);
    
    PUT(fp," 8001 read(io_in,9001,end=8900) inp,xx\n");
    PUT(fp," 9001 format(i8,f10.5)\n");
    PUT(fp,"      if(inp .eq. 0) return\n");
    PUT(fp,"      x(inp) = xx\n");
    PUT(fp,"      goto 8001\n");
    
    comment1(fp);
    PUT(fp," 8900 write(io_stderr,*) 'NODE DATA ERROR'\n");
    PUT(fp,"      stop 'inp_node'\n");
    PUT(fp,"      end\n");
    
    /* ２次元用プログラムの作成 */
    PUT(fp,"      subroutine %s2( x , y)\n",PROG_INP_NODE);
    CopyRight(fp);
    
    real8(fp);
    common_parameters(fp);
    
    PUT(fp,"      dimension x(*),y(*)\n");	
    CommonBlock(fp);
    comment2(fp);
    
    PUT(fp," 8001 read(io_in,9001,end=8900) inp,xx,yy\n");
    PUT(fp," 9001 format(i8,1PE12.5,1PE12.5)\n");
    PUT(fp,"      if(inp .eq. 0) return\n");
    PUT(fp,"      x(inp) = xx\n");
    PUT(fp,"      y(inp) = yy\n");
    PUT(fp,"      goto 8001\n");
    
    comment1(fp);
    PUT(fp," 8900 write(io_stderr,*) 'NODE DATA ERROR'\n");
    PUT(fp,"      stop 'inp_node'\n");
    PUT(fp,"      end\n");
    
    /* ３次元用プログラムの作成 */
    PUT(fp,"      subroutine %s3( x , y , z)\n",PROG_INP_NODE);
    CopyRight(fp);
    
    real8(fp);
    common_parameters(fp);
    
    PUT(fp,"      dimension x(*),y(*),z(*)\n");	
    CommonBlock(fp);
    comment2(fp);
    
    PUT(fp," 8001 read(io_in,9001,end=8900) inp,xx,yy,zz\n");
    PUT(fp," 9001 format(i8,3f10.5)\n");
    PUT(fp,"      if(inp .eq. 0) return\n");
    PUT(fp,"      x(inp) = xx\n");
    PUT(fp,"      y(inp) = yy\n");
    PUT(fp,"      z(inp) = zz\n");
    PUT(fp,"      goto 8001\n");
    
    comment1(fp);
    PUT(fp," 8900 write(io_stderr,*) 'NODE DATA ERROR'\n");
    PUT(fp,"      stop 'inp_node'\n");
    PUT(fp,"      end\n");
    
    
    
    CloseFile(fp);
    
    return;
}
