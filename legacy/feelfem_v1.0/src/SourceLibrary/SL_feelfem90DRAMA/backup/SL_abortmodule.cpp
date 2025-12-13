/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SL_preport90.cpp
 *  Date     : 2000/11/21
 *  Modified : 2000/11/21
 *  
 *  Purpose  : preport90.f90 routine
 *  
 */
#include "SL_feelfem90DRAMA.hpp"

void SL_feelfem90DRAMA::SL_abortmodule(int makeFlag)
{
  char *sourceName;
  
  sourceName = GetSourceName("abortmodule");
  OpenSource(sourceName);
  StoreSource(sourceName,makeFlag);

  writeSource("module abortmodule");
  com();
  writeSource("contains");
  com();
  writeSource("subroutine abortexit(mypeid)");
  writeSource("implicit none");
  writeSource("include 'mpif.h'");
  com();
  writeSource("integer, intent(in) :: mypeid");
  writeSource("integer             :: ierror");
  com();
  writeSource("write(*,*) 'Error occured in PE id.',mypeid");
  com();
  writeSource("call MPI_ABORT(MPI_COMM_WORLD,-1,ierror)");
  com();
  writeSource("end subroutine abortexit");
  com();
  writeSource("!--------------------");
  writeSource("end module abortmodule");

  CloseSource();
}
