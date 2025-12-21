/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_set_MJ
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_set_MJ.f"
lib_p_set_MJ()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_set_MJ (MJ,isubelem,nelemsub,np,nenfre,\n");
   F77("     $     KK_MJ,npmaxsub,KK_MJR,KK_MJL)\n");
   F77("*\n");
   F77("*+++++++++++++++++++++++++++++++++++++++++++++\n");
   F77("*     Purpose : SET the bandwidth \"MJ\" for an\n");
   F77("c               Unsymmetric Sparse Matix\n");
   F77("*    \n");
   F77("*++++++++++++++++++++++++++++++++++++++++++++\n");
   F77("      include 'mpi.incl'\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      dimension isubelem(np,nelemsub)\n");
   F77("      dimension KK_MJR(npmaxsub),KK_MJL(npmaxsub)\n");
   F77("      dimension KK_MJ(npmaxsub)\n");
   F77("      dimension nenfre(*) \n");
   F77("*\n");
   F77("*++++++++++++++++++++++++++++++++++++++++++\n");
   F77("*   Initialization \"KK_MJL(*)\",\"KK_MJR(*)\"\n");
   F77("*+++++++++++++++++++++++++++++++++++++++++\n");
   F77("      do 1 i=1,npmaxsub\n");
   F77("         KK_MJL(i)=0\n");
   F77("         KK_MJR(i)=0\n");
   F77(" 1    continue\n");
   F77("*     \n");
   F77("      do 10 i=1,nelemsub\n");
   F77("         do 20 j=1,np\n");
   F77("            do 30 k=1,np\n");
   F77("               if (isubelem(k,i).gt.isubelem(j,i)) \n");
   F77("     $              then\n");
   F77("                  KK_MJR(isubelem(j,i))=\n");
   F77("     $                 KK_MJR(isubelem(j,i))+1\n");
   F77("               else if (isubelem(k,i).lt.isubelem(j,i)) \n");
   F77("     $                 then\n");
   F77("                  KK_MJL(isubelem(j,i))=\n");
   F77("     $                 KK_MJL(isubelem(j,i))+1\n");
   F77("               end if\n");
   F77("c\n");
   F77("c\n");
   F77("                  if ((isubelem(j,i).le.0).or.(\n");
   F77("     $                 isubelem(j,i).gt.npmaxsub)) then\n");
   F77("                     write (6,*) 'isubelem,j,i',isubelem(j,i),\n");
   F77("     $                    j,i\n");
   F77("                     stop 'isubelem error'\n");
   F77("                  end if\n");
   F77("c\n");
   F77("*                  \n");
   F77(" 30         continue\n");
   F77(" 20      continue\n");
   F77(" 10   continue\n");
   F77("*\n");
   F77("      do 15 i=1,npmaxsub\n");
   F77("         KK_MJ(i)=max0(KK_MJR(i),KK_MJL(i))\n");
   F77("         KK_MJ(i)=2*KK_MJ(i)+1\n");
   F77(" 15   continue\n");
   F77("*\n");
   F77("      \n");
   F77("      MJ=0\n");
   F77("      MJ=KK_MJ(1)\n");
   F77("      do 40 i=2,npmaxsub\n");
   F77("         MJ=max0(MJ,KK_MJ(i))\n");
   F77(" 40   continue\n");
   F77("*     \n");
   F77("      nfree=0\n");
   F77("      nfree=nenfre(1)\n");
   F77("      do 50 i=2,np\n");
   F77("         nfree=max0(nfree,nenfre(i))\n");
   F77(" 50   continue\n");
   F77("*\n");
   F77("      MJ=MJ*nfree\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
