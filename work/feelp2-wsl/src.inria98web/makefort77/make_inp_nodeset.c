/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_inp_nodeset.c
 *      Date:   1993/12/06
 *   
 *   Purpose:   節点集合読み込みプログラムの作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include <stdio.h>
#include "../system/system.h"
#include "Extern.h"
#include "../feel_def/feel_def.h"


static char *src1[] = {
    NULL
  };

make_inp_nodeset()     /* 節点集合データ入力プログラム作成ルーチン */
{
    FILE *fp;
    
    int i;
    
    fp = OpenFileToWrite( INP_NSET );
    
    fprintf(fp,"      subroutine %s(no,nodes,np,inset)\n",PROG_INP_NSET);
    CopyRight(fp);
    common_parameters(fp);

    COM;
    F77("      dimension inset(np,nodes)\n");
    F77("      character fmt*10\n");
    comment1(fp);

    CommonBlock(fp);
    comment2(fp);

    COM;
    F77("c----------------------------\n");
    F77("c  no     nodeset number\n");
    F77("c  nodes  number of nodes\n");
    F77("c  np     data par each node\n");
    F77("c----------------------------\n");

    F77("      if(no .gt. MAX_NODESET .or. no .lt. 1) then\n");
    F77("        write(io_stderr,*) 'node set No. ERROR ',no\n");
    F77("        stop 'nodeset read routine'\n");
    F77("      endif\n");

    comment1(fp);
    F77("      write(fmt,90) np\n");
    F77("  90  format('(',I2,'I8)')\n");
    COM;
    
    F77("      do 100 i=1,nodes\n");
    F77("        read(io_in,fmt) (inset(j,i),j=1,np)\n");
    F77(" 100  continue\n");
    COM;

    F77("      iunit = io_node + no - 1\n");
    F77("      open(unit=iunit,status='scratch',form='unformatted')\n");
    F77("      call closefil(iunit)\n");
    COM;
    F77("      write(iunit) nodes,np\n");
    F77("      write(iunit) ((inset(j,i),j=1,np),i=1,nodes)\n");
    COM;

    F77("      return\n");
    comment1(fp);
    F77("      end\n"); 
    
    CloseFile(fp);
    return;
}



