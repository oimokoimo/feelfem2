/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_avs_coroutine.c
 *      Date:   1998/09/03
 *   
 *   Purpose:   make service routine for AVSoutput
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

void make_avs_coroutine(fp)
     FILE *fp;
{
  F77("      subroutine feelavsoutnode(x,y,npmax,dat)\n");
  F77("      real*8 x(npmax),y(npmax)\n");
  F77("      real*4 z\n");
  F77("      real*4 dat(*)\n");
  F77("*\n");
  F77("      z = 0.0e0\n");
  F77("      do 100 i=1,npmax  \n");
  F77("        dat(3*(i-1)+1) = x(i)\n");
  F77("        dat(3*(i-1)+2) = y(i)\n");
  F77("        dat(3*(i-1)+3) = z\n");
  F77(" 100  continue\n");
  F77("*\n");
  F77("      return\n");
  F77("      end\n");
  F77("      subroutine feelavsoutielem(ielem,np,ne,iv,ndat)\n");
  F77("      dimension ielem(np,ne),ndat(*)\n");
  F77("*      \n");
  F77("      do 100 i=1,ne\n");
  F77("       do 200 j=1,iv\n");
  F77("        ndat((i-1)*iv+j) = ielem(j,i)-1\n");
  F77(" 200   continue\n");
  F77(" 100  continue\n");
  F77("*\n");
  F77("      return\n");
  F77("      end\n");
  F77("      subroutine feelavsoutdat1(n,dat1,dat)\n");
  F77("      real*8 dat1(*)\n");
  F77("      real*4 dat(*)\n");
  F77("      do 100 i=1,n\n");
  F77("       dat(i)=dat1(i)\n");
  F77(" 100  continue\n");
  F77("      return\n");
  F77("      end\n");
  F77("      subroutine feelavsoutdat2(n,dat1,dat2,dat)\n");
  F77("      real*8 dat1(*),dat2(*)\n");
  F77("      real*4 dat(*)\n");
  F77("      do 100 i=1,n\n");
  F77("       dat((i-1)*2+1)=dat1(i)\n");
  F77("       dat((i-1)*2+2)=dat2(i)\n");
  F77(" 100  continue\n");
  F77("      return\n");
  F77("      end\n");
  F77("      subroutine feelavsoutdat3(n,dat1,dat2,dat3,dat)\n");
  F77("      real*8 dat1(*),dat2(*),dat3(*)\n");
  F77("      real*4 dat(*)\n");
  F77("      do 100 i=1,n\n");
  F77("       dat((i-1)*3+1)=dat1(i)\n");
  F77("       dat((i-1)*3+2)=dat2(i)\n");
  F77("       dat((i-1)*3+3)=dat3(i)\n");
  F77(" 100  continue\n");
  F77("      return\n");
  F77("      end\n");


  return;
}


