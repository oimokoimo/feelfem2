/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_f_alloc.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_f_alloc = 0;


void SL_feelP2::SL_f_alloc(int makeFlag)
{
  char *sourceName;

  if(come_yet_f_alloc == 1)  return;
  else                  come_yet_f_alloc = 1;

  sourceName = GetSourceName("f_alloc");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine f_alloc_init(max_feel)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  feelfem P2 Program model System Subroutine f_alloc_init");
  com();
  writeSource("*  2000/05/30 (feelfem_stokes version)");
  com();
  writeSource("*-------------------------------------------------------------------");
  writeSource("      parameter (MAX_PUSH=32)");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      common /feel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      if(max_feel .LT. 1 ) call abortexit(0,'ERR f_alloc_init')");
  writeSource("      np_work  = 1");
  writeSource("      max_heap = 1");
  writeSource("      np_heap  = max_feel");
  com();
  writeSource("      return");
  com();
  writeSource("      end");
  writeSource("      integer*4 function np_work_get_falloc()");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  feelfem P2 Program model System function np_work_get_falloc");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      parameter (MAX_PUSH=32)");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      common /feel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap");
  writeSource("c --------------------------------------------------------------------");
  com();
  writeSource("      np_work_get_falloc = np_work");
  com();
  writeSource("      return");
  com();
  writeSource("      end");
  writeSource("      subroutine f_alloc_get_info(np_work_ret,max_heap_ret)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  feelfem P2 Program model System function np_work_set_falloc");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      parameter (MAX_PUSH=32)");
  writeSource("      integer*4 np_work_ret,max_heap_ret");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      common /feel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      np_work_ret  = np_work");
  writeSource("      max_heap_ret = max_heap");
  com();
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine np_work_set_falloc(np)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  feelfem P2 Program model System function np_work_set_falloc");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      parameter (MAX_PUSH=32)");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      common /feel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      if(np .GT. np_heap .OR. np .LT. 1) then");
  writeSource("         call abortexit(-1,'np_work_set_err')");
  writeSource("      endif");
  com();
  writeSource("      np_work = np");
  writeSource("      if(max_heap .LT. np_work) max_heap = np_work");
  com();
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine f_alloc(nptr , cha, n , itype, imode)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  feelfem P2 Program model System Subroutine f_alloc");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose:  Allocate memory");
  com();
  writeSource("*   nptr  :out   : allocated address in real*4 feel(*)");
  writeSource("*   cha   :in    : comment for allocation");
  writeSource("*   n     :in    : size (as Fortran array, not word)");
  writeSource("*   itype :in    : 0 4-byte(integer)  1 8-byte(double precision)");
  writeSource("*   imode :in/out: [in] = 0 when error ABORT");
  writeSource("*                       =-1 when error return anyway");
  writeSource("*                  [out]=0 no error");
  writeSource("*                       >0 size of shortage in words");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      parameter (MAX_PUSH=32)");
  writeSource("      character cha*(*)");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      common /feel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap");
  writeSource("c --------------------------------------------------------------------");
  com();
  writeSource("      nn = 0");
  writeSource("      if(itype .eq. 1) then");
  writeSource("        if((np_work / 2) * 2 .eq. np_work) np_work = np_work+1");
  writeSource("	nn = n * 2");
  writeSource("      endif");
  writeSource("      if(itype .eq. 0) then");
  writeSource("	nn = n");
  writeSource("      endif");
  com();
  writeSource("      if(nn .eq. 0) then");
  writeSource("	write(*,*) 'in allocate ',cha");
  writeSource("	write(*,*) 'n = ',n,' itype = ',itype");
  writeSource("        call abortexit(-1,'f_alloc itype error')");
  writeSource("      endif");
  com();
  writeSource("      np = np_work + nn");
  writeSource("      if(np . gt . np_heap) then");
  writeSource("        if(imode .eq. 0) then");
  writeSource("          write(*,*) 'Cannot allocate array for ',cha");
  writeSource("          write(*,*) 'No space for ',np-np_heap ,' word'");
  writeSource("          call abortexit(-1,'feel: memory allocation')");
  writeSource("        else");
  writeSource("          write(*,*) 'Cannot allocate array for ',cha");
  writeSource("          if(imode .ne. -1) then");
  writeSource("             call abortexit(-1,'and imode error in f_alloc')");
  writeSource("          endif");
  writeSource("          imode = np-np_heap");
  writeSource("        endif");
  writeSource("      endif");
  com();
  writeSource("      nptr    = np_work");
  writeSource("      np_work = np");
  com();
  writeSource("      if(np_work.gt.max_heap) max_heap = np_work");
  writeSource("      if(imode.eq. -1) imode   = 0");
  com();
  writeSource("      return");
  com();
  writeSource("      end");
  writeSource("      subroutine f_alloc_push");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  feelfem P2 Program model System Subroutine f_alloc_push");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      parameter (MAX_PUSH=32)");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      common /feel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      data    iptr/0/");
  writeSource("      iptr = iptr + 1");
  writeSource("      if(iptr.GT.MAX_PUSH) then");
  writeSource("         call abortexit(-1,'TOO MANY F_ALLOC PUSH called')");
  writeSource("      endif");
  writeSource("      np_push(iptr) = np_work");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine f_alloc_pop");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  feelfem P2 Program model System Subroutine f_alloc_pop");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      parameter (MAX_PUSH=32)");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      common /feel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      if(iptr .eq. 0) then");
  writeSource("         call abortexit(-1,'TOO MANY F_ALLOC_POP called')");
  writeSource("      endif");
  writeSource("      np_work = np_push(iptr)");
  writeSource("      iptr = iptr - 1");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine f_move(ide,ia, num)");
  writeSource("*-----------------------------------");
  writeSource("* Move array block de ide(*) a ia(*).");
  writeSource("*-----------------------------------");
  writeSource("      integer*4 ide(*),ia(*)");
  writeSource("      do 100 i=1,num");
  writeSource("         ia(i)=ide(i)");
  writeSource(" 100  continue");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine abortexit(myrank,cha)");
  writeSource("*----------------------------------------");
  writeSource("* 2001/01/27");
  writeSource("*----------------------------------------");
  writeSource("      integer myrank");
  writeSource("      character cha*(*)");
  com();
  writeSource("      write(*,*) 'Error ',cha");
  writeSource("      call doclosefil(-1)");
  com();
  writeSource("      stop 'abort exit'");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
