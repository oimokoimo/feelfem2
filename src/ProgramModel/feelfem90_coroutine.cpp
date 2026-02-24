/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90_coroutine.cpp
 *  Date     : 2000/12/08
 *  Modified : 2001/01/31  LINKLEVEL_EDEV added
 *             2002/02/28  ADD ewise UNKNOWN CAPACITY
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
 */

#include <cassert>

#include "PM_feelfem90.hpp"
#include "feelfuncs.hpp"            // for int getSpaceDimension();


// 1. Control routine

void PM_feelfem90::GenerateCoSolveRoutines(Solve *solvePtr)
{
  GenerateCoSolveIpdinfoRoutine(solvePtr);
  GenerateCoSolveEdevRoutine(solvePtr);

  return;
}


// 2. I/O related functions

void PM_feelfem90::pushIpdinfoRoutineName(int solveNo, int solveElementNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"ipdinfo%d_%d",solveNo,solveElementNo);
  pushSource(buf);

  return;
}

void PM_feelfem90::pushEdevRoutineName(int solveNo, int solveElementNo)
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



// 6. Generator subroutine IpdinfoRoutine
//    Generator subroutine EdevRoutine

void PM_feelfem90::GenerateCoSolveIpdinfoRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  const char *hereSourceName;

  int solveNo;
  int solveElementNo = 1;   // P2 FIXED to 1

  solveNo = solvePtr->GetSolveNo();

  sprintf(hereRoutineName,"ipdinfo%d_%d",solvePtr->GetSolveNo(),solveElementNo);  
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_EDEV);     // IPDINFO has the same level

  pushSource("module mod_");
  pushIpdinfoRoutineName( solveNo, solveElementNo);
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushIpdinfoRoutineName( solveNo, solveElementNo);
  pushSource("(npmax,ielem,nelem,np");


  list <Variable *>vPLst = sePtr->GetUnknownVariablePtrLst();
  listIterator<Variable *>itrFEMv(vPLst);
  for(itrFEMv.init(); !itrFEMv; ++itrFEMv) {
    pushSource(",");
    pushSource("ipd_");
    pushSource(itrFEMv()->GetName());
  }
  pushSource(")");

  flushSource();
  
  SourceStarters();
  writeSource("use numeric");
  fortImplicit();
  com();

  // integer,intent(in)              :: npmax");
  pushInteger4In();   flushSource("npmax");

  // integer,dimension(:,:)          :: ielem");
  pushInteger4Ptr2(); flushSource("ielem");

  // integer,intent(in)              :: nelem,np");
  pushInteger4In();   flushSource("nelem,np");
  com();

  list <Variable *>varPtrLst = sePtr->GetUnknownVariablePtrLst();

  // integer*4 ipd_*
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr;++itr) {

    // ONLY FEM variables
    if(itr()->GetType() != VAR_FEM &&
       itr()->GetType() != VAR_VFEM    ) continue;

    pushInteger4Ptr1();
    pushSource("ipd_");
    pushSource( itr()->GetName());
    flushSource();
  }

  com();

  writeSource("! auto variables");
  
  pushInteger4sc(); 
  flushSource("i,j");
  
  pushInteger4sc();
  flushSource("nd");

  // ienp_** and iedp_**   itr is defined for variable declaration
  for(itr.init(); !itr;++itr) {

    // ONLY FEM variables
    if(itr()->GetType() != VAR_FEM &&
       itr()->GetType() != VAR_VFEM    ) continue;


    pushSource("integer,dimension(");
    pushSourceInt(itr()->GetFreedom());
    pushSource(")                   ");

    if(itr()->GetFreedom() < 10) pushSource(" ");

    pushSource(":: ienp_");
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
    

    // ONLY FEM variables
    if(itr()->GetType() != VAR_FEM &&
       itr()->GetType() != VAR_VFEM    ) continue;

    pushSource("data ienp_");
    pushSource(itr()->GetName());
    pushSource("/ ");
    for(int k=0;k<itr()->GetFreedom();k++) {
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

  // -1 initialize for ipd_XXX
  writeSource("do i=1,npmax");
  com();
  for(itr.init(); !itr;++itr) {

    // ONLY FEM variables
    if(itr()->GetType() != VAR_FEM &&
       itr()->GetType() != VAR_VFEM    ) continue;

    pushSource("  ipd_");
    pushSource(itr()->GetName());
    pushSource("(i) =  -1   ! -1 means no freedom here");
    flushSource();
  }
  com();
  writeSource("end do");

  com();



  writeSource("do i=1,nelem");

  int ivars;
  ivars = 0;
  
  for(itr.init(); !itr;++itr) {

    // ONLY FEM variables
    if(itr()->GetType() != VAR_FEM &&
       itr()->GetType() != VAR_VFEM    ) continue;

    com();
    pushSource(" do j=1,");
    pushSourceInt( itr()->GetFreedom());
    flushSource();
    
    pushSource("  nd = ielem(ienp_");
    pushSource(itr()->GetName());
    pushSource("(j),i)");
    flushSource();


    pushSource("  ");

    switch( itr()->GetType()) {
    case VAR_FEM:
      pushSource("ipd_");
      pushSource(itr()->GetName());
      pushSource("(nd)");
      break;

    default:
      assert(1==0);

    }
    pushSource("= iedp_");
    pushSource(itr()->GetName());
    pushSource("(j)");
    flushSource();
    
    writeSource(" end do");

    ivars++;
  }
  com();

  writeSource("end do");
  com();

  
  pushSource("end subroutine ");
  pushIpdinfoRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  flushSource();
  
  pushSource("end module mod_");
  pushIpdinfoRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  flushSource();
  
  
  CloseSource();
  return;

}


void PM_feelfem90::GenerateCoSolveEdevRoutine(Solve *solvePtr)
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

  // real(kind=REAL8),dimension(:)   :: resvec
  pushReal8Ptr1();    flushSource("resvec");

  // integer,dimension(:)            :: ipd");
  pushInteger4Ptr1(); flushSource("ipd");

  // integer,dimension(:,:)          :: ielem");
  pushInteger4Ptr2(); flushSource("ielem");

  // integer,intent(in)              :: nelem,np");
  pushInteger4In();   flushSource("nelem,np");
  com();

  list <Variable *>varPtrLst = sePtr->GetUnknownVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  com();

  writeSource("! auto variables");
  
  pushInteger4sc(); 
  flushSource("i,j");
  
  pushInteger4sc();
  flushSource("nd");

  // ienp_** and iedp_**
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    pushSource("integer,dimension(");
    pushSourceInt(itr()->GetFreedom());
    pushSource(")                   ");

    if(itr()->GetFreedom() < 10) pushSource(" ");

    pushSource(":: ienp_");
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
    for(int k=0;k<itr()->GetFreedom();k++) {
      if(k != 0) { pushSource(","); }
      pushSourceInt(sePtr->GetIthIENP(ienp_ptr));
      ienp_ptr++;
    }
    pushSource("/");
    flushSource();

    pushSource("data iedp_");
    pushSource(itr()->GetName());
    pushSource("/ ");
    for(int k=0;k<itr()->GetFreedom();k++) {
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

    switch( itr()->GetType()) {
    case VAR_FEM:
      pushFEMVariableInCalled(itr());
      pushSource("(nd)");
      break;

    case VAR_EWISE_A:
      pushSource("ew_");
      pushSource(itr()->GetName());
      pushSource("(j,i)");
      break;

    default:
      assert(1==0);

    }
    pushSource("= resvec(ipd(nd) + iedp_");
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
