/*
   FEEL p2  MAKE FORTRAN LIBRARY   mk_subdomain_nset
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "mk_subdomain_nset.f"
void lib_mk_subdomain_nset()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine mk_subdomain_nset(feel,ieg,neg,mats,matnos)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: show input data\n");
   F77("*  \n");
   F77("*  Caution:\n");
   F77("*\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      real*4    feel(*)\n");
   F77("      dimension matnos(*)\n");
   F77("*--------------------------------------------------------------------\n");
   common_parameters(fp);
   COM;
   CommonBlock(fp);
   comment1(fp);
   F77("*--------------------------------------------------------------------\n");
   F77("*      np_push = np_work\n");
   F77("      call f_alloc_push\n");
   F77("*--------------------------------------------------------\n");
   F77("      if(neg .gt. MAX_NODESET) then\n");
   F77("        stop 'Error: Required edat no is too big in mk_subdom_edat'\n");
   F77("      endif\n");
   F77("*--------------------------------------------------------\n");
   F77("      neelem = n_edat(ieg,1)\n");
   F77("      nenode = n_edat(ieg,2)\n");
   F77("      call f_alloc(np_ielem,'subdomain_nset',neelem*nenode,0)\n");
   F77("      call f_alloc(np_matno,'subdomain_nset',neelem       ,0)\n");
   F77("      iunit = ieg + io_edat -1\n");
   F77("      call get_ielem(iunit,feel(np_ielem),feel(np_matno),\n");
   F77("     $               neelem,nenode                       )\n");
   F77("*--------------------------------------------------------\n");
   F77("      call f_alloc(np_nset ,'subdomain_nset',neelem,0)\n");
   F77("*--------------------------------------------------------\n");
   F77("      iunit = io_node + neg -1\n");
   F77("      call sd_wrt_nset(iunit,mats,matnos,\n");
   F77("     $     feel(np_ielem),feel(np_matno),neelem,nenode,\n");
   F77("     $     feel(np_nset),nodes)\n");
   F77("*--------------------------------------------------------\n");
   F77("      n_nset(neg,1) = nodes\n");
   F77("      n_nset(neg,2) = 1\n");
   F77("*\n");
   F77("*      np_work=np_push\n");
   F77("      call f_alloc_pop\n");
   F77("*\n");
   F77("      return\n");
   F77("*--------------------------------------------------------\n");
   F77("      end\n");
   F77("      subroutine sd_wrt_nset(iunit,mats,matnos,\n");
   F77("     $                             ielem,matno,neelem,nenode,\n");
   F77("     $                             newise,nodes)\n");
   F77("*-----------------------------------------------------------\n");
   F77("*     SUB-SUBROUTINE [sd_wrt_nset] make sub region NSET data\n");
   F77("*     ****************************\n");
   F77("*-----------------------------------------------------------\n");
   F77("      dimension matnos(neelem)\n");
   F77("      dimension ielem(nenode,neelem),    matno  (neelem)\n");
   F77("      dimension newise(neelem)\n");
   F77("*-----------------------------------------------------------\n");
   F77("      inos = 0\n");
   F77("*\n");
   F77("      do 100 i=1,mats\n");
   F77("*\n");
   F77("         mno = matnos(i)\n");
   F77("*\n");
   F77("         do 200 j=1,neelem\n");
   F77("*\n");
   F77("            if( matno(j) .eq. mno) then\n");
   F77("               inos = inos + 1\n");
   F77("               newise(inos) = j\n");
   F77("            endif\n");
   F77(" 200     continue\n");
   F77("*\n");
   F77(" 100  continue\n");
   F77("*-----------------------------------------------------------\n");
   F77("      open(unit = iunit, status='scratch',form='unformatted')\n");
   F77("*\n");
   F77("      write(iunit) inos,1\n");
   F77("      write(iunit) (newise(i),i=1,inos)\n");
   F77("*\n");
   F77("      nodes = inos\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
