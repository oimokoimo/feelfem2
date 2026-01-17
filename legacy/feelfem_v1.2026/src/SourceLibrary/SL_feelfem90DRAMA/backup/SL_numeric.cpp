/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SL_numeric.cpp
 *  Date     : 2000/11/21
 *  Modified : 2000/11/21
 *  
 *  Purpose  : numeric.f90 routine
 *  
 */
#include "SL_feelfem90DRAMA.hpp"

void SL_feelfem90DRAMA::SL_numeric(int makeFlag)
{
  char *sourceName;
  
  sourceName = GetSourceName("numeric");
  OpenSource(sourceName);
  StoreSource(sourceName,makeFlag);

  writeSource("module numeric");
  com();
  writeSource("integer, parameter :: INT4          = selected_int_kind(9)  ! INTEGER*4");
  writeSource("integer, parameter :: REAL8         = kind(1.0d0)           ! REAL   *8");
  writeSource("integer, parameter :: Oui           = 1");
  writeSource("integer, parameter :: Non           = 0");
  writeSource("integer, parameter :: NodeError     = -1");
  writeSource("integer, parameter :: already       = 1");
  writeSource("integer, parameter :: notYet        = 0");
  writeSource("integer, parameter :: Nur_One_Etype = -999            ! for enptr(2,*)");
  writeSource("integer, parameter :: EndOfEnptr    = -9999           ! for enptr(2,nelem+1)");
  com();
  writeSource("end module numeric");

  CloseSource();

  return;
}
