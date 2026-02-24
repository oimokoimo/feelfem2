/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90DRAMA_elem.cpp
 *  Date     : 2000/10/19
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : elem related routine generator for feelfem90DRAMA model
 *  
 *  1. I/O related. (get/push routine name)
 *  
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
#include "feelfuncs.hpp"

#include "Quadrature.hpp"
#include "PM_feelfem90DRAMA.hpp"
#include "ElemGeneratorTemplate.hpp"


// 0. Special rinji routines

string PM_feelfem90DRAMA::SuperRinjiEcalP2DRAMA(const  char *s)
{
  char  femname[100];
  char  number [100];
  char  val    [BUFSIZ];
  int   ptr;
  ptr = 4;
  while(*(s+ptr) != '(') {
    femname[ptr-4] = *(s+ptr);
    ptr++;
  }
  femname[ptr-4] = '\0';
  
  ptr += 7;
  int base = ptr;
  while(*(s+ptr) != ',') {
    number[ptr-base] = *(s+ptr);
    ptr++;
  }
  number[ptr-base]='\0';

  sprintf(val,"efem_%s(%s)",femname,number);

  string ret = val;
  return(ret);
}


// 1. I/O related.

const char *PM_feelfem90DRAMA::GetElemRoutineName( int solveNo )
{
  int length = stringLength("elem?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
	    std::cerr <<"solve number too large(GetElemRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"elem%d",solveNo);

  return(ptr);
}

void PM_feelfem90DRAMA::pushElemRoutineName(int solveNo)
{
  const char *ptr;
  ptr = GetElemRoutineName(solveNo);
  pushSource(ptr);
  delete ptr;

  return;
}

void PM_feelfem90DRAMA::F90useElemPM(SolveElement *sePtr)
{
  // use sentence for ecal routine
  pushSource("use mod_");
  pushEcalRoutineName( sePtr );
  flushSource();
  com();

  // use sentence for eset routines
  for(int i=0;i<sePtr->GetQuadratures();i++) {
    pushSource("use mod_");
    pushEsetRoutineName( sePtr->GetSolveNo(),
			 sePtr->GetElemNo(),
			 i + 1);
    flushSource();
  }
  com();

  return;
}

// ###  Variable definitons
void PM_feelfem90DRAMA::doElemDeclareArgumentVariablesPM(SolveElement *sePtr)
{
  writeInteger4In("mypeid,nprocs");
  writeInteger4sc("isumup(nprocs)");
  writeInteger4Ptr2("enptr,con");
  writeInteger4In("nelem");
  CoordinateVariableDeclaration();
  com();

  writeInteger4Ptr1("ipf,ipd");
  writeInteger4In("npmax");
  writeInteger4In("neq");
  com();

  writeInteger4Ptr2("enptr_ex,con_ex");
  writeInteger4In("nelem_ex");
  writeInteger4In("nouter");
  writeInteger4sc("ndno(nouter),peno(nouter)");
  writeInteger4sc("ipf_ex(nouter),ipd_ex(nouter)");
  CoordinateExternalVariableDeclaration();
  com();

  // fem,ewise,scalar variables
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);

  // fem external variables
  FEMExternalVariableDeclarationLst(varPtrLst);
  com();

  return;
}


void PM_feelfem90DRAMA::DoElemVariableDefinitionsPM(SolveElement *sePtr)
{
  int strindex(const char *, const char *);
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *> itr(varPtrLst);

  COMMENTlong("Auto variables");
  writeInteger4sc("i,j,k,l");
  writeInteger4sc("ip,jp");
  writeInteger4sc("ind,ipe");
  writeInteger4sc("nd");  
  writeInteger4sc("iptf,iptt");
  writeInteger4sc("ipos_from,ipos_to");
  writeInteger4sc("ietype");
  writeInteger4sc("nodes");

  switch(getSpaceDimension()){
  case 1:
    writeReal8sc("ex(NDP)");
    break;

  case 2:
    writeReal8sc("ex(NDP),ey(NDP)");
    break;

  case 3:
    writeReal8sc("ex(NDP),ey(NDP),ez(NDP)");
    break;
    
  default:
    assert(1==0);
  }

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushReal8sc();
      pushSource("efem_");
      pushSource(itr()->GetName());
      pushSource("(NDP)");
      flushSource();
    }
  }  
  com();

  writeInteger4sc("ienp(NDF),iedp(NDF)");
  writeInteger4sc("ikp(NDF),jkp(NDF)");
  com();

  writeReal8sc("ea,eb");

  comment();

  pushSource("common /em");
  pushSourceInt(sePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(sePtr->GetElemNo());
  pushSource("/ ea(NDF,NDF),eb(NDF)");
  flushSource();
  comment();

  return;
}

// ###

void PM_feelfem90DRAMA::doElemStarters()
{
  SourceStarters();
  return;
}

// ###

void PM_feelfem90DRAMA::DoElemParameters(SolveElement *sePtr)
{

  COMMENTlong("Problem dependent parameters");
  pushInteger4pm();
  pushSource("NDF = ");
  pushSourceInt(sePtr->GetNdf());
  flushSource();

  pushInteger4pm();
  pushSource("NDP = ");
  pushSourceInt(sePtr->GetIelemNodes());
  flushSource();



  for(int i=0;i<sePtr->GetQuadratures();i++) {

    Quadrature *qPtr;
    qPtr = sePtr->GetIthQuadraturePtr(i);

    pushInteger4pm();
    pushSource("NPG");
    pushSourceInt(i+1);
    pushSource(" =  ");
    pushSourceInt(qPtr->GetQuadraturePoints());
    pushSource("  ! No.");
    pushSourceInt(i+1);
    pushSource(" [");
    pushSource(qPtr->GetName());
    pushSource("]");
    flushSource();

  }
  comment();
  return;

}




// ### Initializer 

void PM_feelfem90DRAMA::DoElemInitializer(SolveElement *sePtr)
{
  /* data statement for ienp */
  pushSource("data ienp/");
  for(int i=0;i<sePtr->GetNdf();i++) {
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetIthIENP(i));
  }
  pushSource("/");
  flushSource();

  /* data statement for iedp */
  pushSource("data iedp/");
  for(int i=0;i<sePtr->GetNdf();i++) {
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetIthIEDP(i));
  }
  pushSource("/");
  flushSource();

  comment();

  for(int i=0;i<sePtr->GetQuadratures();i++) {
    pushSource("call eset");
    pushSourceInt(sePtr->GetSolveNo());
    pushSource("_");
    pushSourceInt(sePtr->GetElemNo());
    pushSource("_");
    pushSourceInt(i+1);
    flushSource();
  }
  comment();

  return;
}

// ### loop start
  
void PM_feelfem90DRAMA::DoElemElementLoopStart(int flag)
{
  if(flag == MY_ELEMENT) {
    COMMENTlong("Own enptr loop");
    writeSource("do 100 i=1,nelem");         // just this!  ^^;
  }
  else {

    COMMENTlong("External enptr_ex loop");
    writeSource("      do 200 i=1,nelem_ex");         // just this!  ^^;
  }
  return; 
}


void PM_feelfem90DRAMA::DoElemCallEcalRoutine(SolveElement *sePtr,int flag)
{
  int strindex(const char *, const char *);
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *> itr(varPtrLst);

  if(flag == MY_ELEMENT) {

    // myelement loop
  
    writeSource("ipos_from = enptr(1,i  )");
    writeSource("ipos_to   = enptr(1,i+1)-1");
    writeSource("ietype    = enptr(2,i  )");
    writeSource("nodes     = ipos_to-ipos_from+1");
    com();
    writeSource("!**** if(ietype .EQ. 1) then");  // P2 limit
    writeSource("  do j=1,nodes");
    writeSource("   jp=j-1+ipos_from");
    writeSource("   if(con(2,jp) .eq. mypeid) then");
    writeSource("     ex(j)=x(con(1,jp))");
    writeSource("     ey(j)=y(con(1,jp))");

    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("     efem_");
	pushSource(itr()->GetName());
	pushSource("(j)=fem_");
	pushSource(itr()->GetName());
	pushSource("(con(1,jp))");
	flushSource();
      }
    }  

    writeSource("   else");
    writeSource("     nd = ndsearch_ex(con(1,jp),con(2,jp),ndno,peno,nouter)");
    writeSource("     ex(j) = x_ex(nd)");
    writeSource("     ey(j) = y_ex(nd)");

    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("     efem_");
	pushSource(itr()->GetName());
	pushSource("(j)=");
	pushFEMVariableExternalInCalled(itr());
	pushSource("(nd)");
	flushSource();
      }
    }  

    writeSource("   endif");
    writeSource("  end do");
    com();
    pushSource ("  call ecal");
    pushSourceInt(sePtr->GetSolveNo());
    pushSource("_");
    pushSourceInt(sePtr->GetElemNo());
    pushSource("(");

    int ielemNodes = sePtr->GetIelemNodes();
    for(int i=0;i<ielemNodes;i++) {
      if(i != 0) pushSource(",");
      pushSource("ex(");
      pushSourceInt(i+1);
      pushSource(")");

      if(getSpaceDimension() > 1){
	pushSource(",ey(");
	pushSourceInt(i+1);
	pushSource(")");
      }

      if(getSpaceDimension() > 2){
	pushSource(",ez(");
	pushSourceInt(i+1);
	pushSource(")");
      }
    }

    pushEcalArgumentLstInElem( sePtr, varPtrLst );   //feelfem90DRAMA_ecal.cpp

    pushSource(")");
    flushSource();
    com();

    writeSource(" do j=1,NDF");
    writeSource("  jp   = ienp(j)+ipos_from-1");
    writeSource("  ind  = con(1,jp)");
    writeSource("  ipe  = con(2,jp)");
    writeSource("  if(ipe == mypeid) then");
    writeSource("   ikp(j) = ipd(ind)+iedp(j)");
    writeSource("   jkp(j) = ikp(j)                                ! AMG/CRS");
    writeSource("  else");
    writeSource("   nd = ndsearch_ex(ind,ipe,ndno,peno,nouter)");
    writeSource("   ikp(j) = 0");
    writeSource("   jkp(j) = ipd_halo(nd)+iedp(j)+neq ! AMG/CRS");
    writeSource("  endif");
    writeSource(" end do");
    com();

  }  // end of MY_ELEMENT case
  else {

    // start of OTHER_ELEMENT case

    writeSource("ipos_from = enptr_ex(1,i  )");
    writeSource("ipos_to   = enptr_ex(1,i+1)-1");
    writeSource("ietype    = enptr_ex(2,i  )");
    writeSource("nodes     = ipos_to-ipos_from+1");
    com();
    writeSource("!**** if(ietype .EQ. 1) then");  // P2 limit
    writeSource("  do j=1,nodes");
    writeSource("   jp=j-1+ipos_from");
    writeSource("   if(con_ex(2,jp) .eq. mypeid) then");


    switch(getSpaceDimension()) {
    case 1:
      writeSource("     ex(j)=x(con_ex(1,jp))");
      break;

    case 2:
      writeSource("     ex(j)=x(con_ex(1,jp))");
      writeSource("     ey(j)=y(con_ex(1,jp))");
      break;

    case 3:
      writeSource("     ex(j)=x(con_ex(1,jp))");
      writeSource("     ey(j)=y(con_ex(1,jp))");
      writeSource("     ez(j)=z(con_ex(1,jp))");
      break;

    default:
      assert(1==0);
    }

    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("     efem_");
	pushSource(itr()->GetName());
	pushSource("(j)=");
	pushFEMVariableInCalled(itr());
	pushSource("(con_ex(1,jp))");
	flushSource();
      }
    }  

    writeSource("   else");
    writeSource("     nd = ndsearch_ex(con_ex(1,jp),con_ex(2,jp),ndno,peno,nouter)");


    switch(getSpaceDimension()){
    case 1:
      writeSource("     ex(j) = x_ex(nd)");
      break;

    case 2:
      writeSource("     ex(j) = x_ex(nd)");
      writeSource("     ey(j) = y_ex(nd)");
      break;

    case 3:
      writeSource("     ex(j) = x_ex(nd)");
      writeSource("     ey(j) = y_ex(nd)");
      writeSource("     ez(j) = z_ex(nd)");
      break;

    default:
      assert(1==0);
    }


    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("     efem_");
	pushSource(itr()->GetName());
	pushSource("(j)=");
	pushFEMVariableExternalInCalled(itr());
	pushSource("(nd)");
	flushSource();
      }
    }  

    writeSource("   endif");
    writeSource("  end do");
    com();
    pushSource ("  call ecal");
    pushSourceInt(sePtr->GetSolveNo());
    pushSource("_");
    pushSourceInt(sePtr->GetElemNo());
    pushSource("(");

    int ielemNodes = sePtr->GetIelemNodes();
    for(int i=0;i<ielemNodes;i++) {

      if(i != 0) pushSource(",");

      pushSource("ex(");
      pushSourceInt(i+1);
      pushSource(")");

      if(getSpaceDimension() > 1) {

	pushSource(",ey(");
	pushSourceInt(i+1);
	pushSource(")");
      }

      if(getSpaceDimension() > 2) {
	pushSource(",ez(");
	pushSourceInt(i+1);
	pushSource(")");
      }
    }

    pushEcalArgumentLstInElem(sePtr, varPtrLst );   //  feelfem90DRAMA_ecal.cpp

    pushSource(")");
    flushSource();
    com();

    writeSource(" do j=1,NDF");
    writeSource("  jp   = ienp(j)+ipos_from-1");
    writeSource("  ind  = con_ex(1,jp)");
    writeSource("  ipe  = con_ex(2,jp)");
    writeSource("  if(ipe == mypeid) then");
    writeSource("   ikp(j) = ipd(ind)+iedp(j)");
    writeSource("   jkp(j) = ikp(j)                                ! AMG/CRS");
    writeSource("  else");
    writeSource("   nd = ndsearch_ex(ind,ipe,ndno,peno,nouter)");
    writeSource("   ikp(j) = 0");
    writeSource("   jkp(j) = ipd_halo(nd)+iedp(j)+neq              ! AMG/CRS");
    writeSource("  endif");
    writeSource(" end do");
    com();

  }
  return;
}

void PM_feelfem90DRAMA::DoElemElementLoopEnd(int flag)
{
  if(flag == MY_ELEMENT) {
    writeSource(" 100  continue");
    writeSource("!---           end of my enptr loop");
    com();
  }
  else {
    writeSource(" 200  continue");
    writeSource("!---           end of external enptr loop");
    comment();
  }    
  return;
}

void PM_feelfem90DRAMA::DoElemReturnSequence(SolveElement *sePtr)
{
  pushSource("end subroutine ");
  pushElemRoutineName(sePtr->GetSolveNo());
  flushSource();

  pushSource("end module mod_");
  pushElemRoutineName(sePtr->GetSolveNo());
  flushSource();
  
  return;
}
  








