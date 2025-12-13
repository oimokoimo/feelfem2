/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90DRAMA.cpp
 *  Date     : 2000/10/16
 *  Modified : 2000/
 *  Modified : 2001/02/02 orderedPtrList
 *  Modified : 2003/02/17
 *  
 *  Purpose  : feelfem90 programming style implementation 
 *             DRAMA double index parallel version
 *
 *
 *  1. constructor,destructor
 *  2. I/O related routines (Open/Close and routine name for solve#.f90)
 *  3. general pushSource routines (coordinates)
 *  4. comments,etc,
 *  5. General functional routine (memory allocation, memory 0 initialize)
 *  6. Calling sequence, variable name handling
 *
 */

#include "feelfem.hpp"
#include "PM_feelfem90DRAMA.hpp"
#include "feelfuncs.hpp"

//                >1234567890123456789012345678901234567890<
//                 integer                                 :: ");
#define  FEELFEM90_INDENT 40

// Constructor, Destructor

PM_feelfem90DRAMA::PM_feelfem90DRAMA()
{
  return;
}

PM_feelfem90DRAMA::~PM_feelfem90DRAMA()
{
  return;
}

// 2. I/O related

void PM_feelfem90DRAMA::OpenSource(char *filename)
{
  startSource( filename );
  Fortran90GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelfem90DRAMA::OpenSource(char *filename,int makeFlag)
{
  startSource( filename ,makeFlag);
  Fortran90GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelfem90DRAMA::CloseSource()
{
  endSource(  );
  Fortran90GeneratorSetFP( NULL );
  return;
}

//  Filename handling

void PM_feelfem90DRAMA::pushSolveRoutineName( int no )
{
  char *ptr;

  ptr = GetSolveRoutineName( no );
  pushSource(ptr);
  delete ptr;
}


char *PM_feelfem90DRAMA::GetSourceName( char *routineName)
{
  int   len = stringLength(routineName)+3+2;   // +2 = 90  (.f -> f90)
  char *ptr = new char[len];
  
  sprintf(ptr,"%s.f90",routineName);
  return(ptr);
}


// 3. General pushSource subroutine

void PM_feelfem90DRAMA::pushCoordinateSource(void)
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

void PM_feelfem90DRAMA::pushCoordinateExternalSource()
{
  switch(getSpaceDimension()){
  case 1:
    pushSource("x_ex");
    break;
  case 2:
    pushSource("x_ex,y_ex");
    break;
  case 3:
    pushSource("x_ex,y_ex,z_ex");
    break;
  }
  return;
}
  

// 4. Comments

void PM_feelfem90DRAMA::commentPM()
{
  writeSource("! feelfem90/DRAMA Program Model");
  return;
}



// 5. General functional routine (memory allocation, memory 0 initialize)

void PM_feelfem90DRAMA::MODULEzeroclearD(char *varname, char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"call zerod(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelfem90DRAMA::MODULEzeroclearI(char *varname, char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"call zeroi(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelfem90DRAMA::
MODULEmalloc(char *name,char *comment,char *size, char *type)
{
  MODULEmallocF90(name,size);
  return;
}

// error version
void PM_feelfem90DRAMA::
MODULEmallocERT(char *name,char *comment,char *size, char *type)
{
  MODULEmallocF90(name,size);
  return;
}

// F90 interface
void PM_feelfem90DRAMA::MODULEmallocF90(char *varName,char *varSize)
{
  pushSource("allocate(");
  pushSource(varName);
  pushSource("(");
  pushSource(varSize);
  pushSource("))");
  flushSource();
}


// 6. Calling sequence, variable name handling

void PM_feelfem90DRAMA::NameVariableInCalled( Variable *valPtr, string &name)
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

// variable memory allocation
void PM_feelfem90DRAMA::MainVariableAllocation( Variable *varPtr)
{
  switch(varPtr->GetType()) {
  case VAR_FEM:
    pushSource("allocate(");
    pushVariableNameInMain(varPtr);

    // npmax
    pushSource("(mynode))");     // mynode for DRAMA model
    flushSource();

    break;
    
  case VAR_EWISE:
    pushSource("allocate(");
    pushVariableNameInMain(varPtr);

    // npmax
    pushSource("(myelem))");     // myelem for DRAMA model
    flushSource();
    break;


  case VAR_EWISE_A:
    pushSource("allocate(");
    pushVariableNameInMain(varPtr);

    // npmax
    pushSource("(");
    pushSourceInt( varPtr->GetEWISEFreedom());
    pushSource(",myelem))");                      // myelem for DRAMA
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

// variable memory allocation
void PM_feelfem90DRAMA::doMainVariableInitialValue( Variable *varPtr)
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


void PM_feelfem90DRAMA::
pushVariableListInMain(orderedPtrList <Variable *>vPtrLst)
{
  pushVariableListInCalled(vPtrLst);
}

void PM_feelfem90DRAMA::pushVariableNameInMain( Variable *varPtr)
{
  pushVariableInCalled( varPtr );   // fortran90 (02/09/03)
  return;
}

void PM_feelfem90DRAMA::pushVariableInCalled( Variable *valPtr)
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

void PM_feelfem90DRAMA::pushVariableListInCalled( orderedPtrList <Variable *> varPtrLst)
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

void PM_feelfem90DRAMA::
pushVariableAndFEMExternalListInSolve( orderedPtrList <Variable *> varPtrLst)
{
  // this is same of in called with Fortran90
  pushVariableAndFEMExternalListInCalled(varPtrLst);
  return;
}
  

void PM_feelfem90DRAMA::
pushVariableAndFEMExternalListInCalled( orderedPtrList <Variable *> varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  // FEM,EWISE,SCALAR
  for(itr.init(); !itr;++itr) {
    pushSource(",");
    pushVariableInCalled(itr());
  }
  // FEM External
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType()==VAR_FEM) {
      pushSource(",");
      pushFEMVariableExternalInCalled(itr());
    }
  }
  return;

}

void PM_feelfem90DRAMA::
pushFEMExternalVariableListInCalled(orderedPtrList <Variable *>varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  int first = 0;
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType()==VAR_FEM) {
      if(first == 0) {
	first = 1;
      }
      else {
	pushSource(",");
      }
      pushFEMVariableExternalInCalled(itr());
    }
  }
  return;
}

void PM_feelfem90DRAMA::pushVariableListInCalled( list <Variable *> varPtrLst)
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

// add 2003/02/12
void PM_feelfem90DRAMA::pushVariableListInSolve(orderedPtrList<Variable*>varPtrLst)
{
  pushVariableListInCalled( varPtrLst );  // fortran90 (same of called)
  return;
}

/* Add 2000/05/09  (now only in feelfem90DRAMA) */
void PM_feelfem90DRAMA::pushFEMVariableInCalled( Variable *varPtr)
{
  pushSource("fem_");
  pushSource(varPtr->GetName());
  return;
}

void PM_feelfem90DRAMA::pushFEMVariableInSolve( Variable *varPtr)
{
  pushFEMVariableInCalled( varPtr );    // f90 same 
  return;
}

/* External FEM variable  2000/05/09 */
void PM_feelfem90DRAMA::pushFEMVariableExternalInCalled( Variable *varPtr)
{
  pushSource("fem_");
  pushSource(varPtr->GetName());
  pushSource("_ex");
  return;
}

void PM_feelfem90DRAMA::pushFEMVariableExternalInSolve( Variable *varPtr) 
{

  // in feelfem90, all variables have the same name
  pushFEMVariableExternalInCalled( varPtr );

  return;
}



///////////////////////////////////////////////////////////
void PM_feelfem90DRAMA::DefaultParameterBlock()
{
  //  comment();
  //  writeSource("! PM_feelfem90DRAMA::DefaultParameterBlock()");
  //  comment();

  doNothingNow("void PM_feelfem90DRAMA::DefaultParameterBlock()");
  return;

}


void PM_feelfem90DRAMA::PopReturn()                     // General in PM
{
  // ?????
  writeSource("      return");
  writeSource("      end");
  return;
}


/////////////////////////////////////////////////////////////////
// General components for generating subroutines
/////////////////////////////////////////////////////////////////
void PM_feelfem90DRAMA::pushTypeDefCC(char *s)
{
  int len = stringLength(s);
  pushSource(s);
  for(int i=0;i< FEELFEM90_INDENT - len; i++) {
    pushSource(" ");
  }
  pushSource(":: ");
  return;
}

void PM_feelfem90DRAMA::pushInteger4sc(void)
{
  pushSource(   "integer                                 :: ");
  return;
}

void PM_feelfem90DRAMA::pushInteger4pm(void)
{
  pushSource(   "integer,parameter                       :: ");
  return;
}

void PM_feelfem90DRAMA::pushInteger4In(void)
{
  pushSource(   "integer,intent(in)                      :: ");
  return;
}

void PM_feelfem90DRAMA::pushInteger4Ptr1(void)
{
  pushSource(   "integer,dimension(:)  ,pointer          :: ");
  return;
}

void PM_feelfem90DRAMA::pushInteger4Ptr2(void)
{
  pushSource(   "integer,dimension(:,:),pointer          :: ");
  return;
}

void PM_feelfem90DRAMA::pushLogical(void)
{
  pushSource(   "logical                                 :: ");
  return;
}


// write Integer
void PM_feelfem90DRAMA::writeInteger4sc(const char *str)
{
  pushInteger4sc();
  flushSource(str);
  return;
}

void PM_feelfem90DRAMA::writeInteger4pm(const char *str)
{
  pushInteger4pm();
  flushSource(str);
  return;
}

void PM_feelfem90DRAMA::writeInteger4In(const char *str)
{
  pushInteger4In();
  flushSource(str);
  return;
}

void PM_feelfem90DRAMA::writeInteger4Ptr1(const char *str)
{
  pushInteger4Ptr1();
  flushSource(str);
  return;
}

void PM_feelfem90DRAMA::writeInteger4Ptr2(const char *str)
{
  pushInteger4Ptr2();
  flushSource(str);
  return;
}

// real*8 
void PM_feelfem90DRAMA::pushReal8sc(void)
{
  pushSource(   "real(kind=REAL8)                        :: ");
  return;
}

void PM_feelfem90DRAMA::pushReal8pm(void)
{
  pushSource(   "real(kind=REAL8),parameter              :: ");
  return;
}

void PM_feelfem90DRAMA::pushReal8Ptr1(void)
{
  pushSource(   "real(kind=REAL8),dimension(:)  ,pointer :: ");
  return;
}

void PM_feelfem90DRAMA::pushReal8Ptr2(void)
{
  pushSource(   "real(kind=REAL8),dimension(:,:),pointer :: ");
  return;
}

void PM_feelfem90DRAMA::pushReal8Array1(void)
{
  pushSource(   "real(kind=REAL8),dimension(:)           :: ");
  return;
}

// write real*8
void PM_feelfem90DRAMA::writeReal8sc(const char *str)
{
  pushReal8sc();
  flushSource(str);
  return;
}

void PM_feelfem90DRAMA::writeReal8pm(const char *str)
{
  pushReal8pm();
  flushSource(str);
  return;
}

void PM_feelfem90DRAMA::writeReal8Ptr1(const char *str)
{
  pushReal8Ptr1();
  flushSource(str);
  return;
}

void PM_feelfem90DRAMA::writeReal8Ptr2(const char *str)
{
  pushReal8Ptr2();
  flushSource(str);
  return;
}

void PM_feelfem90DRAMA::writeLogical(const char *str)
{
  pushLogical();
  flushSource(str);
  return;
}

/////




void PM_feelfem90DRAMA::CoordinateVariableDeclaration(void)
{
  switch(getSpaceDimension()){
  case 1:
    writeReal8Ptr1("x");
    break;

  case 2:
    writeReal8Ptr1("x,y");
    break;

  case 3:
    writeReal8Ptr1("x,y,z");
    break;
  }

  return;
}

void PM_feelfem90DRAMA::CoordinateExternalVariableDeclaration(void)
{
  switch(getSpaceDimension()){
  case 1:
    writeReal8Ptr1("x_ex");
    break;
  case 2:
    writeReal8Ptr1("x_ex,y_ex");
    break;
  case 3:
    writeReal8Ptr1("x_ex,y_ex,z_ex");
    break;
  }
  return;
}

void PM_feelfem90DRAMA::FEMExternalVariableDeclaration(Variable *varPtr)
{
  pushReal8Ptr1();
  pushFEMVariableExternalInCalled( varPtr );
  flushSource();

  return;
}

void PM_feelfem90DRAMA::
FEMExternalVariableDeclarationLst( list <Variable *> &varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType()==VAR_FEM) {
      FEMExternalVariableDeclaration(itr());
    }
  }
  return;
}


// this is almost for solve routine
void PM_feelfem90DRAMA::DoArgumentSequenceFromMain
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
  pushSource("(myrank,nprocs,mypeid, &");
  flushSource();

  pushSource("   npmax,");
  pushCoordinateSource();
  pushSource(",                          &");
  flushSource();

  writeSource("   firstDramaEdatPtr,firstDramaNsetPtr,solveLst &");

  pushVariableListInCalled( varPtrLst);
  pushSource(")");
  flushSource();
  
  return;
}

/////////////////////////////////////////////////////////////////////////////
void PM_feelfem90DRAMA::MainVariableDeclaration(Variable *varPtr)  // 030217
{
  ArgumentVariableDeclaration(varPtr); // in fortran90,  same as Arg...
  return;
}

void PM_feelfem90DRAMA::ArgumentVariableDeclaration(Variable *varPtr)
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
    
  default:
    assert(1==0);
  }
  
  return;
}


/////////////////////////////////////////////////////////////////////////////
void PM_feelfem90DRAMA::ArgumentVariableDeclarationLst(list <Variable *>& varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    ArgumentVariableDeclaration(itr());
  }  
  
  return;
}



/////////////////////////////////////////////////////////////////
// Routine name for feelP2 DRAMA program model
// Get  Routine name series  [Definition of routine names]
// push Routine name series  [Writing source file routine names]
/////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////



void PM_feelfem90DRAMA::MPIinclude(void)
{
  writeSource("include 'mpif.h'");
  return;
}

/////////////////////////////////////////////////////////////////
// solve related component generators
/////////////////////////////////////////////////////////////////
void PM_feelfem90DRAMA::SourceStarters()
{
  copyright();
  commentPM();
  timestamp();
  
  return;
}


void PM_feelfem90DRAMA::F90useAlways(void)
{
  writeSource("! general modules");
  writeSource("use preport90");
  writeSource("use numeric");
  writeSource("use abortmodule");

  return;
}

void PM_feelfem90DRAMA::F90useFEMDataType(void)
{
  writeSource("! FEM DataType");
  writeSource("use femDataType");
  writeSource("use dramaDataModel");
  com();

  return;
}


void PM_feelfem90DRAMA::
DoDeclareVariablesFromMainPM( orderedPtrList<Variable *>varPtrLst)
{
  // Variable definitions (Arguments in solve routine)

  writeInteger4sc("myrank,nprocs,mypeid");
  writeInteger4sc("npmax");

  switch(getSpaceDimension()) {
  case 1:
    writeReal8Ptr1("x");
    break;

  case 2:
    writeReal8Ptr1("x,y");
    break;

  case 3:
    writeReal8Ptr1("x,y,z");
    break;
  }
  writeSource("type (dramaEdatList),pointer         :: firstDramaEdatPtr");
  writeSource("type (dramaNsetList),pointer         :: firstDramaNsetPtr");
  writeSource("type (solveList)                     :: solveLst");
  com();

  ArgumentVariableDeclarationLst( varPtrLst );
  com();
 
  return;
}
