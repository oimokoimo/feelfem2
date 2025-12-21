/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 * 
 */

#include <stdio.h>
#include "../system/system.h"
#include "Extern.h"
#include "../feel_def/feel_def.h"

make_inp_edat()
{
    FILE *fp;

    int i;

    fp = OpenFileToWrite( INP_EDAT );

    fprintf(fp,"      subroutine %s(no,nelem,np,ielem,matno)\n",PROG_INP_EDAT);
    
    CopyRight(fp);
    real8(fp);
    common_parameters(fp);

    comment1(fp);
    F77("      dimension ielem(np,nelem),matno(nelem)\n");
    F77("      character*20 fmt\n");
    COM;
    CommonBlock(fp);
    comment1(fp);
    /*----------------------------------*/    
    COM;
    F77("      iunit = io_edat + no - 1"); CR;
    F77("      open(unit=iunit,status='scratch',form='unformatted')"); CR;
    F77("      call closefil(iunit)\n");
    COM;
    F77("      write(fmt,9003) np+1"); CR;
    F77(" 9003 format('(',I2,'I8)')"); CR;
    COM;
    F77("      do 100 i=1,nelem"); CR;
    F77("        read(io_in,fmt,end=8902) (ielem(j,i),j=1,np),matno(i)\n");
    F77("  100 continue"); CR;
    COM;
    F77("      write(iunit) nelem,np\n");
    F77("      write(iunit) ((ielem(i,j),i=1,np),j=1,nelem)\n");
    F77("      write(iunit) (matno(i),i=1,nelem)\n");
    COM; 
    F77("      return"); CR;
    COM3;
    F77(" 8902 write(io_stderr,*) 'edat data error'"); CR;
    F77("      stop 'inp_edat'"); CR;
    COM3;
    F77("      end"); CR;         
    /*----------------------------------*/    

    CloseFile(fp);
    return;
}

    

        
        
        
   
    

