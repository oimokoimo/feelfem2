/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90vec.cpp
 *  Date     : 2001/11/29 (copy from feelfem90.cpp)
 *  Modified : 
 *  
 *  Purpose  : feelfem90vec programming style implementation
 *   [copy]    scalar version (derived from DRAMA parallel version)
 *
 *  1. constructor,destructor
 *  2. I/O related routines (Open/Close and routine name for solve#.f90)
 *  3. general pushSource routines (coordinates)
 *  4. comments,etc,
 *  5. General functional routine (memory allocation, memory 0 initialize)
 *  6. Calling sequence, variable name handling
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

#include "feelfem.hpp"
#include "PM_feelfem90vec.hpp"
#include "feelfuncs.hpp"


// Constructor, Destructor

PM_feelfem90vec::PM_feelfem90vec()
{
  return;
}

PM_feelfem90vec::~PM_feelfem90vec() = default;

// 2. I/O related

void PM_feelfem90vec::OpenSource(const char *filename)
{
  startSource( filename );
  Fortran90GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelfem90vec::OpenSource(const char *filename,int makeFlag)
{
  startSource( filename, makeFlag );
  Fortran90GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelfem90vec::CloseSource()
{
  endSource(  );
  Fortran90GeneratorSetFP( NULL );
  return;
}

//  Filename handling

void PM_feelfem90vec::pushSolveRoutineName( int no )
{
  const char *ptr;

  ptr = GetSolveRoutineName( no );
  pushSource(ptr);
  delete ptr;
}


const char *PM_feelfem90vec::GetSourceName( const char *routineName)
{
  int   len = stringLength(routineName)+3+2;   // +2 = 90  (.f -> f90)
  char *ptr = new char[len];
  
  sprintf(ptr,"%s.f90",routineName);
  return(ptr);
}


// 3. General pushSource subroutine

void PM_feelfem90vec::pushCoordinateSource(void)
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

void PM_feelfem90vec::commentPM()
{
  writeSource("! feelfem90vec Program Model");
  return;
}



// 5. General functional routine (memory allocation, memory 0 initialize)

void PM_feelfem90vec::MODULEzeroclearD(const char *varname, const char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"call zerod(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelfem90vec::MODULEzeroclearI(const char *varname, const char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"call zeroi(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelfem90vec::
MODULEmalloc(const char *name,const char *comment,const char *size, const char *type)
{
  MODULEmallocF90(name,size);
  return;
}

// error version
void PM_feelfem90vec::
MODULEmallocERT(const char *name,const char *comment,const char *size, const char *type)
{
  MODULEmallocF90(name,size);
  return;
}

// F90 interface
void PM_feelfem90vec::MODULEmallocF90(const char *varName,const char *varSize)
{
  pushSource("allocate(");
  pushSource(varName);
  pushSource("(");
  pushSource(varSize);
  pushSource("))");
  flushSource();
}


// 6. Calling sequence, variable name handling

void PM_feelfem90vec::NameVariableInCalled( Variable *valPtr, string &name)
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
    
  default:
    assert(1==0);
  }
  
  name = buf;
  return;
}

void PM_feelfem90vec::pushVariableInCalled( Variable *valPtr)
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
    
  default:
    assert(1==0);
  }
  return;
}

void PM_feelfem90vec::pushVariableListInCalled( orderedPtrList <Variable *>varPtrLst)
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



void PM_feelfem90vec::pushVariableListInCalled( list <Variable *>varPtrLst)
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

void PM_feelfem90vec::pushVariableListInSolve( orderedPtrList <Variable *>varPtrLst)
{
  pushVariableListInCalled( varPtrLst );  // fortran90 (same of called)
  return;
}



/* Add 2000/05/09  (now only in feelfem90vec) */
void PM_feelfem90vec::pushFEMVariableInCalled( Variable *varPtr)
{
  pushSource("fem_");
  pushSource(varPtr->GetName());
  return;
}

void PM_feelfem90vec::pushFEMVariableInSolve( Variable *varPtr)
{
  pushFEMVariableInCalled( varPtr );    // f90 same 
  return;
}


///////////////////////////////////////////////////////////
void PM_feelfem90vec::DefaultParameterBlock()
{
  //  comment();
  //  writeSource("! PM_feelfem90vec::DefaultParameterBlock()");
  //  comment();

  doNothingNow("void PM_feelfem90vec::DefaultParameterBlock()");
  return;

}


void PM_feelfem90vec::PopReturn()                     // General in PM
{
  // ?????
  writeSource("      return");
  writeSource("      end");
  return;
}


/////////////////////////////////////////////////////////////////
// General components for generating subroutines
/////////////////////////////////////////////////////////////////
void PM_feelfem90vec::CoordinateVariableDeclaration(void)
{
  switch(getSpaceDimension()){
  case 1:
    writeSource("real(kind=REAL8),dimension(:),pointer :: x");
    break;

  case 2:
    writeSource("real(kind=REAL8),dimension(:),pointer :: x,y");
    break;

  case 3:
    writeSource("real(kind=REAL8),dimension(:),pointer :: x,y,z");
    break;
  }

  return;
}


void PM_feelfem90vec::DoArgumentSequenceFromMain
( const char                         *subroutineName,
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

  writeSource("   firstEdatPtr,firstNsetPtr &");

  pushVariableListInCalled( varPtrLst);
  pushSource(")");
  flushSource();
  
  return;
}

/////////////////////////////////////////////////////////////////////////////
void PM_feelfem90vec::ArgumentVariableDeclaration(Variable *varPtr)
{
  string a;
  NameVariableInCalled(varPtr,a);

  switch(varPtr->GetType()) {
  case VAR_FEM:
    pushSource("real(kind=REAL8),dimension(:),pointer :: ");
    pushSource(a);
    flushSource();
    break;
    
  case VAR_EWISE:
    pushSource("real(kind=REAL8),dimension(:),pointer :: ");
    pushSource(a);
    flushSource();
    break;

  case VAR_EWISE_A:
    pushSource("real(kind=REAL8),dimension(:,:),pointer:: ");
    pushSource(a);
    flushSource();
    break;
    
    
  case VAR_DOUBLE:
    pushSource("real(kind=REAL8)                      :: ");
    pushSource(a);
    flushSource();
    break;

  case VAR_INT:
    pushSource("integer                               :: ");
    pushSource(a);
    flushSource();
    break;
    
  case VAR_CONST:
    pushSource("real(kind=REAL8)                      :: ");
    pushSource(a);
    flushSource();
    break;
    
  default:
    assert(1==0);
  }
  
  return;
}


/////////////////////////////////////////////////////////////////////////////
void PM_feelfem90vec::ArgumentVariableDeclarationLst(list <Variable *>& varPtrLst)
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



void PM_feelfem90vec::MPIinclude(void)
{
  writeSource("include 'mpif.h'");
  return;
}

/////////////////////////////////////////////////////////////////
// solve related component generators
/////////////////////////////////////////////////////////////////
void PM_feelfem90vec::SourceStarters()
{
  copyright();
  commentPM();
  timestamp();
  
  return;
}


void PM_feelfem90vec::F90useAlways(void)
{
  writeSource("! general modules");
  writeSource("use report90");      
  writeSource("use numeric");
  writeSource("use abortmodule");

  return;
}

void PM_feelfem90vec::F90useFEMDataType(void)
{
  writeSource("! FEM DataType");
  writeSource("use femDataType");
  writeSource("use feelP2data");
  com();

  return;
}


void PM_feelfem90vec::
DoDeclareVariablesFromMainPM( orderedPtrList<Variable *>varPtrLst)
{
  // Variable definitions (Arguments in solve routine)

  writeSource("integer(kind=INT4 )                  :: npmax");

  switch(getSpaceDimension()) {
  case 1:
    writeSource("real   (kind=REAL8),dimension(:),pointer :: x");
    break;

  case 2:
    writeSource("real   (kind=REAL8),dimension(:),pointer :: x,y");
    break;

  case 3:
    writeSource("real   (kind=REAL8),dimension(:),pointer :: x,y,z");
    break;
  }
  writeSource("type (edatList),pointer         :: firstEdatPtr");
  writeSource("type (nsetList),pointer         :: firstNsetPtr");
  com();

  ArgumentVariableDeclarationLst( varPtrLst );
  com();
 
  return;
}
