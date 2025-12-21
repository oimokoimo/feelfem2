/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   make_inp_num.c
 *      Date:   1993/06/11 (Modified)
 *   
 *   Purpose:   数値データの入力
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../system/system.h"
#include "Extern.h"
#include "../feel_def/feel_def.h"


static char *src1[] = {
    "      read(io_in,9001) no,nsetno",
    "c   ",
    "c  no     Nodeset number",
    "c  nsetno Number of nodes",
    "c",
    " 9001 format(2i8)",
    "c",
    "      if(no .gt. MAX_NODESET .or. no .le. 0) goto 8901",
    "      ns = n_nset(no,1)",
    "      if(ns .eq. 0) goto 8902",
    "c",
    "      if(ns*2 + np_work_get_falloc() .gt. np_heap) goto 8900", 
    "c",
    "      n_num(no) = nsetno",
    "c",
    "      iunit = io_num + no - 1",
    "      open(unit=iunit,status='scratch',form='unformatted')",
    "      call closefil(iunit)",
    "c",
    "      read(io_in,9010,end=8903) (dat(i),i=1,ns)",
    " 9010 format((5e14.5))",
    "c",
    "      write(iunit) ns,(dat(i),i=1,ns)",
    "c",
    "      return",
    "c---------------------------------------------------------",
    " 8900 write(io_stderr,*) 'no space left(inp_nset)'",
    "      write(io_stderr,*) ns*2+np_work_get_falloc()-np_heap",
    "      stop 'inp_nset'",
    "c----------------------",
    " 8901 write(io_stderr,*) 'node set no error(数値データ入力時)'",
    "      stop 'inp_nset'",
    "c----------------------",
    " 8902 write(io_stderr,*) '指定した節点集合データが定義されない'",
    "      stop 'inp_nset'",
    "c----------------------",
    " 8903 write(io_stderr,*) 'node set data error'",
    "      stop 'inp_nset'",
    "c---------------------------------------------------------",
    "      end",
    NULL
  };

make_inp_num()     /* 節点集合データ入力プログラム作成ルーチン */
{
    FILE *fp;
    
    int i;
    
    fp = OpenFileToWrite( INP_NUM );
    
    fprintf(fp,"      subroutine %s(dat)\n",PROG_INP_NUM);
    CopyRight(fp);

    real8(fp);
    common_parameters(fp);

    fprintf(fp,"      dimension dat(*)\n");
    CommonBlock(fp);
    comment2(fp);
    
    /*----------------------------------*/    
    for(i=0;src1[i]           != NULL;i++) {
	fprintf(fp,"%s\n",src1[i]);
    }
    /*----------------------------------*/    
    
    CloseFile(fp);
    return;
}

