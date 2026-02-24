/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90vec_coroutine.cpp
 *  Date     : 2000/11/29 (copy from feelfem90_coroutine.cpp)
 *  Modified : 
 *  
 *  Purpose  : feelfem90 programming style implementation 
 *             scalar model (derived drama model)
 *
 *  1. Control routine (GenerateCoSolveRoutines)
 *  2. I/O related routines
 *  3. Make calling sequence ExtData routine in solve  [SubDoSolveMakeExtData()]
 * 
 *  5. Generator for the subrouitne mksolve#extdata.f90
 *  6. Generator subroutine EdevRoutine 
 * 
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 */

#include "PM_feelfem90vec.hpp"
#include "feelfuncs.hpp"            // for int getSpaceDimension();


// 1. Control routine

void PM_feelfem90vec::GenerateCoSolveRoutines(Solve *solvePtr)
{
  GenerateCoSolveEdevRoutine(solvePtr);

  return;
}


// 2. I/O related functions

void PM_feelfem90vec::pushEdevRoutineName(int solveNo, int solveElementNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"edev%d_%d",solveNo,solveElementNo);
  pushSource(buf);

  return;
}

// 3. Make calling sequence ExtData routine in solve

// *-- deleted --*


// 5. Generator for the subrouitne mksolve#extdata.f90
// *-- deleted --*



// 6. Generator subroutine EdevRoutine
void PM_feelfem90vec::GenerateCoSolveEdevRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  const char *hereSourceName;

  int solveNo;
  int solveElementNo = 1;   // P2 FIXED to 1

  solveNo = solvePtr->GetSolveNo();

  sprintf(hereRoutineName,"edev%d_%d",solvePtr->GetSolveNo(),solveElementNo);  
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_EDEV);

  pushSource("module mod_");
  pushEdevRoutineName( solveNo, solveElementNo);
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushEdevRoutineName( solveNo, solveElementNo);
  pushSource("(resvec,ipd,ielem,nelem,np");

  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");

  flushSource();
  
  SourceStarters();
  writeSource("use numeric");
  fortImplicit();
  com();

  writeSource("real(kind=REAL8),dimension(:)   :: resvec");
  writeSource("integer,dimension(:)            :: ipd");
  writeSource("integer,dimension(:,:)          :: ielem");
  writeSource("integer,intent(in)              :: nelem,np");
  com();

  list <Variable *>varPtrLst = sePtr->GetUnknownVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  com();

  writeSource("! auto variables");
  writeSource("integer                         :: i,j");
  writeSource("integer                         :: nd");

  // ienp_** and iedp_**
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    pushSource("integer,dimension(");
    pushSourceInt(itr()->testGetElementFreedom());
    pushSource(")            :: ienp_");
    pushSource(itr()->GetName());
    pushSource(",iedp_");
    pushSource(itr()->GetName());
    flushSource();
  }
  com();


  // data sentences

  writeSource("! data statements");

  int ienp_ptr,iedp_ptr;
  ienp_ptr = 0;
  iedp_ptr = 0;
  for(itr.init(); !itr;++itr) {
    
    pushSource("data ienp_");
    pushSource(itr()->GetName());
    pushSource("/ ");
    for(int k=0;k<itr()->testGetElementFreedom();k++) {
      if(k != 0) { pushSource(","); }
      pushSourceInt(sePtr->GetIthIENP(ienp_ptr));
      ienp_ptr++;
    }
    pushSource("/");
    flushSource();

    pushSource("data iedp_");
    pushSource(itr()->GetName());
    pushSource("/ ");
    for(int k=0;k<itr()->testGetElementFreedom();k++) {
      if(k != 0) { pushSource(","); }
      pushSourceInt(sePtr->GetIthIEDP(iedp_ptr));
      iedp_ptr++;
    }
    pushSource("/");
    flushSource();
  }
  comment();


  com();
  
  writeSource("do i=1,nelem");

  int ivars;
  ivars = 0;
  
  for(itr.init(); !itr;++itr) {
    com();
    pushSource(" do j=1,");
    pushSourceInt( itr()->testGetElementFreedom());
    flushSource();
    
    pushSource("  nd = ielem(ienp_");
    pushSource(itr()->GetName());
    pushSource("(j),i)");
    flushSource();


    pushSource("  ");
    pushFEMVariableInCalled(itr());
    pushSource("(nd) = resvec(ipd(nd) + iedp_");
    pushSource(itr()->GetName());
    pushSource("(j))");
    flushSource();
    
    writeSource(" end do");

    ivars++;
  }
  com();

  writeSource("end do");
  com();

  
  pushSource("end subroutine ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  flushSource();
  
  pushSource("end module mod_");
  pushEdevRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  flushSource();
  
  
  CloseSource();
  return;

}
