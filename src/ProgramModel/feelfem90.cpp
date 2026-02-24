/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90.cpp
 *  Date     : 2000/12/08
 *  Modified : 2000/
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : feelfem90 programming style implementation 
 *             scalar version (derived from DRAMA parallel version)
 *
 *  1. constructor,destructor
 *  2. I/O related routines (Open/Close and routine name for solve#.f90)
 *  3. general pushSource routines (coordinates)
 *  4. comments,etc,
 *  5. General functional routine (memory allocation, memory 0 initialize)
 *  6. Calling sequence, variable name handling
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

#include "feelfem.hpp"
#include "PM_feelfem90.hpp"
#include "feelfuncs.hpp"


//                >1234567890123456789012345678901234567890<
//                 integer                                 :: ");
#define  FEELFEM90_INDENT 40

// Constructor, Destructor

PM_feelfem90::PM_feelfem90()
{
  return;
}

PM_feelfem90::~PM_feelfem90() = default;


// 2. I/O related

void PM_feelfem90::OpenSource(const char *filename)
{
  startSource( filename );
  Fortran90GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelfem90::OpenSource(const char *filename,int makeFlag)
{
  startSource( filename, makeFlag );
  Fortran90GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelfem90::CloseSource()
{
  endSource(  );
  Fortran90GeneratorSetFP( NULL );
  return;
}

//  Filename handling

void PM_feelfem90::pushSolveRoutineName( int no )
{
  const char *ptr;

  ptr = GetSolveRoutineName( no );
  pushSource(ptr);
  delete ptr;
}


const char *PM_feelfem90::GetSourceName( const char *routineName)
{
  int   len = stringLength(routineName)+3+2;   // +2 = 90  (.f -> f90)
  char *ptr = new char[len];
  
  sprintf(ptr,"%s.f90",routineName);
  return(ptr);
}


// 3. General pushSource subroutine

void PM_feelfem90::pushCoordinateSource(void)
{

  switch(getSpaceDimension()){
  case 1:
    pushSource("x");
    break;
  case 2:
    pushSource("x,y");
    break;
  case 3:
    pushSource("x,y,z");
    break;
  }
  return;
}

// 4. Comments

void PM_feelfem90::commentPM()
{
  writeSource("! feelfem90 Program Model");
  return;
}



// 5. General functional routine (memory allocation, memory 0 initialize)

void PM_feelfem90::MODULEzeroclearD(const char *varname, const char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"call zerod(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelfem90::MODULEzeroclearI(const char *varname, const char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"call zeroi(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelfem90::
MODULEmalloc(const char *name,const char *comment,const char *size, const char *type)
{
  MODULEmallocF90(name,size);
  return;
}

void PM_feelfem90::MemAllocate(const char *arrayname,const char *index,
			       const char *sizeFormula,int   type )
{
  pushSource("allocate(");
  pushSource( arrayname );
  pushSource("(");
  pushSource(index);
  pushSource("))");
  flushSource();

  // if( memreport == ON) {  generate report routine }
  return;
}

void PM_feelfem90::MemDeallocate(const char *arrayname,const char *index,
				 const char *sizeFormula,int   type )
{
  pushSource("deallocate(");
  pushSource( arrayname );
  pushSource(")");
  flushSource();

  // if( memreport == ON) {  generate report routine }
  return;
}

// error version
void PM_feelfem90::
MODULEmallocERT(const char *name,const char *comment,const char *size, const char *type)
{
  MODULEmallocF90(name,size);
  return;
}

// F90 interface
void PM_feelfem90::MODULEmallocF90(const char *varName,const char *varSize)
{
  pushSource("allocate(");
  pushSource(varName);
  pushSource("(");
  pushSource(varSize);
  pushSource("))");
  flushSource();
}


// 6. Calling sequence, variable name handling

void PM_feelfem90::NameVariableInCalled( Variable *valPtr, string &name)
{
  char buf[BUFSIZ];
  switch(valPtr->GetType()) {
  case VAR_FEM:
    sprintf(buf,"fem_%s",valPtr->GetName());
    break;
    
  case VAR_EWISE:
  case VAR_EWISE_A:
    sprintf(buf,"ew_%s",valPtr->GetName());
    break;
    
  case VAR_DOUBLE:
  case VAR_INT:
    sprintf(buf,"sc_%s",valPtr->GetName());
    break;
    
  case VAR_CONST:
    sprintf(buf,"co_%s",valPtr->GetName());
    break;
    

  case VAR_MATERIAL:
    sprintf(buf,"m_%s",valPtr->GetName());
    break;

  default:
    assert(1==0);
  }
  
  name = buf;
  return;
}

void PM_feelfem90::pushVariableInCalled( Variable *valPtr)
{
  switch(valPtr->GetType()) {
  case VAR_FEM:
    pushSource("fem_");
    pushSource(valPtr->GetName());
    break;
    
  case VAR_EWISE:
  case VAR_EWISE_A:
    pushSource("ew_");
    pushSource(valPtr->GetName());
    break;
    
  case VAR_DOUBLE:
  case VAR_INT:
    pushSource("sc_");
    pushSource(valPtr->GetName());    
    break;
    
  case VAR_CONST:
    pushSource("co_");
    pushSource(valPtr->GetName());        
    break;

  case VAR_MATERIAL:
    pushSource("m_");
    pushSource(valPtr->GetName());        
    break;
    
  default:
    assert(1==0);
  }
  return;
}

void PM_feelfem90::pushVariableNameInMain( Variable *varPtr)
{
  pushVariableInCalled( varPtr );   // fortran90
  return;
}


// variable memory allocation
void PM_feelfem90::MainVariableAllocation( Variable *varPtr)
{
  switch(varPtr->GetType()) {
  case VAR_FEM:
    pushSource("allocate(");
    pushVariableNameInMain(varPtr);

    // npmax
    pushSource("(npmax))");
    flushSource();

    break;
    
  case VAR_EWISE:
    pushSource("allocate(");
    pushVariableNameInMain(varPtr);

    // npmax
    pushSource("(nelem_g))");
    flushSource();
    break;


  case VAR_EWISE_A:
    pushSource("allocate(");
    pushVariableNameInMain(varPtr);

    // npmax
    pushSource("(");
    pushSourceInt( varPtr->GetEWISEFreedom());
    pushSource(",nelem_g))");
    flushSource();
    break;
    
  case VAR_DOUBLE:
  case VAR_INT:
  case VAR_CONST:
    break;

  case VAR_MATERIAL:
    pushSource("allocate(");
    pushVariableNameInMain(varPtr);    
    pushSource("(");
    pushSourceInt( varPtr->GetMATERIALFreedom());
    pushSource("))");
    flushSource();
    break;
    
  default:
    assert(1==0);
  }
  return;
}

// initial value
void PM_feelfem90::doMainVariableInitialValue( Variable *varPtr)
{
  switch(varPtr->GetType()) {
  case VAR_FEM:
  case VAR_EWISE:
  case VAR_EWISE_A:
  case VAR_MATERIAL:        // initial for material is done in system sub
    break;

  case VAR_DOUBLE:
    if(varPtr->GetInitialFlag()) {
      pushVariableNameInMain(varPtr);
      pushSource(" = ");
      pushSourceDbl  (varPtr->GetInitialValue());
      flushSource();

      pushSource("if(nnum >= ");
      pushSourceInt(varPtr->GetDblInitialNo());
      pushSource(") then");
      flushSource();

      pushSource("  ");
      pushVariableNameInMain(varPtr);
      pushSource(" = numData%dat(");
      pushSourceInt(varPtr->GetDblInitialNo());
      pushSource(")");
      flushSource();
      
      writeSource("endif");
      com();
    }  
    break;

  case VAR_INT:
    if(varPtr->GetInitialFlag()) {
      pushVariableNameInMain(varPtr);
      pushSource(" = ");
      pushSourceInt(varPtr->GetIntInitialValue());
      flushSource();
      com();
    }
    break;

  case VAR_CONST:
    pushVariableNameInMain(varPtr);
    pushSource(" = ");
    pushSourceDbl(varPtr->GetInitialValue());
    flushSource();
    com();
    break;
    
  default:
    assert(1==0);
  }
  return;
}

void PM_feelfem90::pushVariableListInMain( orderedPtrList <Variable *>vPtrLst)
{
  pushVariableListInCalled(vPtrLst);
}

void PM_feelfem90::pushVariableListInCalled(orderedPtrList<Variable *>vPtrLst)
{
  listIterator <Variable *> itr(vPtrLst);
  for(itr.init(); !itr;++itr) {
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  return;
}


void PM_feelfem90::pushVariableListInCalled( list <Variable *> varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  return;

}

void PM_feelfem90::pushVariableListInCalledOnlyFEM(list <Variable *> varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {

    if(itr()->GetType() != VAR_FEM   &&
       itr()->GetType() != VAR_VFEM     ) continue;
    
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  return;
}

void PM_feelfem90::pushVariableListInSolve(orderedPtrList<Variable*>varPtrLst)
{
  pushVariableListInCalled( varPtrLst );  // fortran90 (same of called)
  return;
}


/* Add 2000/05/09  (now only in feelfem90) */
void PM_feelfem90::pushFEMVariableInCalled( Variable *varPtr)
{
  pushSource("fem_");
  pushSource(varPtr->GetName());
  return;
}

void PM_feelfem90::pushFEMVariableInSolve( Variable *varPtr)
{
  pushFEMVariableInCalled( varPtr );    // f90 same 
  return;
}



///////////////////////////////////////////////////////////
void PM_feelfem90::DefaultParameterBlock()
{
  //  comment();
  //  writeSource("! PM_feelfem90::DefaultParameterBlock()");
  //  comment();

  doNothingNow("void PM_feelfem90::DefaultParameterBlock()");
  return;

}


void PM_feelfem90::PopReturn()                     // General in PM
{
  // ?????
  writeSource("      return");
  writeSource("      end");
  return;
}


/////////////////////////////////////////////////////////////////
// General components for generating subroutines
/////////////////////////////////////////////////////////////////
void PM_feelfem90::pushTypeDefCC(char *s)
{
  int len = stringLength(s);
  pushSource(s);
  for(int i=0;i< FEELFEM90_INDENT - len; i++) {
    pushSource(" ");
  }
  pushSource(":: ");
  return;
}

void PM_feelfem90::pushInteger4sc(void)
{
  pushSource(   "integer                                 :: ");
  return;
}

void PM_feelfem90::pushInteger4pm(void)
{
  pushSource(   "integer,parameter                       :: ");
  return;
}

void PM_feelfem90::pushInteger4In(void)
{
  pushSource(   "integer,intent(in)                      :: ");
  return;
}

void PM_feelfem90::pushInteger4Ptr1(void)
{
  pushSource(   "integer,dimension(:)  ,pointer          :: ");
  return;
}

void PM_feelfem90::pushInteger4Ptr2(void)
{
  pushSource(   "integer,dimension(:,:),pointer          :: ");
  return;
}

void PM_feelfem90::pushLogical(void)
{
  pushSource(   "logical                                 :: ");
  return;
}


// write Integer
void PM_feelfem90::writeInteger4sc(const char *str)
{
  pushInteger4sc();
  flushSource(str);
  return;
}

void PM_feelfem90::writeInteger4pm(const char *str)
{
  pushInteger4pm();
  flushSource(str);
  return;
}

void PM_feelfem90::writeInteger4In(const char *str)
{
  pushInteger4In();
  flushSource(str);
  return;
}

void PM_feelfem90::writeInteger4Ptr1(const char *str)
{
  pushInteger4Ptr1();
  flushSource(str);
  return;
}

void PM_feelfem90::writeInteger4Ptr2(const char *str)
{
  pushInteger4Ptr2();
  flushSource(str);
  return;
}

// real*8 
void PM_feelfem90::pushReal8sc(void)
{
  pushSource(   "real(kind=REAL8)                        :: ");
  return;
}

void PM_feelfem90::pushReal8pm(void)
{
  pushSource(   "real(kind=REAL8),parameter              :: ");
  return;
}

void PM_feelfem90::pushReal8Ptr1(void)
{
  pushSource(   "real(kind=REAL8),dimension(:)  ,pointer :: ");
  return;
}

void PM_feelfem90::pushReal8Ptr2(void)
{
  pushSource(   "real(kind=REAL8),dimension(:,:),pointer :: ");
  return;
}

void PM_feelfem90::pushReal8Array1(void)
{
  pushSource(   "real(kind=REAL8),dimension(:)           :: ");
  return;
}

// write real*8
void PM_feelfem90::writeReal8sc(const char *str)
{
  pushReal8sc();
  flushSource(str);
  return;
}

void PM_feelfem90::writeReal8pm(const char *str)
{
  pushReal8pm();
  flushSource(str);
  return;
}

void PM_feelfem90::writeReal8Ptr1(const char *str)
{
  pushReal8Ptr1();
  flushSource(str);
  return;
}

void PM_feelfem90::writeReal8Ptr2(const char *str)
{
  pushReal8Ptr2();
  flushSource(str);
  return;
}

void PM_feelfem90::writeLogical(const char *str)
{
  pushLogical();
  flushSource(str);
  return;
}

/////



void PM_feelfem90::CoordinateVariableDeclaration(void)
{
  switch(getSpaceDimension()){
  case 1:
    pushReal8Ptr1();
    flushSource("x");
    break;

  case 2:
    pushReal8Ptr1();
    flushSource("x,y");
    break;

  case 3:
    pushReal8Ptr1();
    flushSource("x,y,z");
    break;
  }

  return;
}


void PM_feelfem90::DoArgumentSequenceFromMain
( char                         *subroutineName,
  orderedPtrList <Variable *>&varPtrLst       )
{
  //module declaration
  pushSource("module mod_");
  pushSource(subroutineName);
  flushSource();
  
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushSource(subroutineName);
  pushSource("(npmax,");
  pushCoordinateSource();
  pushSource(",");
  pushSource("                    &");
  flushSource();

  writeSource("   firstEdatPtr,firstNsetPtr, solveLst &");

  pushVariableListInCalled( varPtrLst);
  pushSource(")");
  flushSource();
  
  return;
}

/////////////////////////////////////////////////////////////////////////////
void PM_feelfem90::MainVariableDeclaration(Variable *varPtr)
{
  ArgumentVariableDeclaration(varPtr); // in fortran90,  same as Arg...
  return;
}

void PM_feelfem90::ArgumentVariableDeclaration(Variable *varPtr)
{
  string a;
  NameVariableInCalled(varPtr,a);

  switch(varPtr->GetType()) {

  case VAR_FEM:
    pushReal8Ptr1();
    pushSource(a);
    flushSource();
    break;
    
  case VAR_EWISE:
    pushReal8Ptr1();
    pushSource(a);
    flushSource();
    break;

  case VAR_EWISE_A:
    pushReal8Ptr2();
    pushSource(a);
    flushSource();
    break;
    
    
  case VAR_DOUBLE:
    pushReal8sc();
    pushSource(a);
    flushSource();
    break;

  case VAR_INT:
    pushInteger4sc();
    pushSource(a);
    flushSource();
    break;
    
  case VAR_CONST:
    pushReal8sc();
    pushSource(a);
    flushSource();
    break;

  case VAR_MATERIAL:
    pushReal8Ptr1();
    pushSource(a);
    flushSource();
    break;

  default:
    assert(1==0);
  }
  
  return;
}


/////////////////////////////////////////////////////////////////////////////
void PM_feelfem90::ArgumentVariableDeclarationLst(list <Variable *>& varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    ArgumentVariableDeclaration(itr());
  }  
  
  return;
}



/////////////////////////////////////////////////////////////////
// Get  Routine name series  [Definition of routine names]
// push Routine name series  [Writing source file routine names]
/////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////



void PM_feelfem90::MPIinclude(void)
{
  writeSource("include 'mpif.h'");
  return;
}

/////////////////////////////////////////////////////////////////
// solve related component generators
/////////////////////////////////////////////////////////////////
void PM_feelfem90::SourceStarters()
{
  copyright();
  commentPM();
  timestamp();
  
  return;
}


void PM_feelfem90::F90useAlways(void)
{
  writeSource("! general modules");
  writeSource("use report90");      
  writeSource("use numeric");
  writeSource("use abortmodule");
  com();

  return;
}

void PM_feelfem90::F90useFEMDataType(void)
{
  writeSource("! FEM DataType");
  writeSource("use femDataType");
  writeSource("use feelP2data");
  com();

  return;
}


void PM_feelfem90::
DoDeclareVariablesFromMainPM( orderedPtrList<Variable *>varPtrLst)
{
  // Variable definitions (Arguments in solve routine)

  writeSource("integer(kind=INT4 )                  :: npmax");

  switch(getSpaceDimension()) {
  case 1:
    pushReal8Ptr1();
    flushSource("x");
    break;

  case 2:
    pushReal8Ptr1();
    flushSource("x,y");
    break;

  case 3:
    pushReal8Ptr1();
    flushSource("x,y,z");
    break;
  }
  writeSource("type (edatList),pointer         :: firstEdatPtr");
  writeSource("type (nsetList),pointer         :: firstNsetPtr");
  writeSource("type (SolveList)                :: solveLst");
  com();

  ArgumentVariableDeclarationLst( varPtrLst );
  com();
 
  return;
}

