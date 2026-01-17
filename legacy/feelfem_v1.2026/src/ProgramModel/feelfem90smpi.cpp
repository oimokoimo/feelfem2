/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90smpi.cpp
 *  Date     : 2003/01/04 (copied from feelfem90)
 *  Modified : 
 *  
 *  Purpose  : feelfem90smpi programming style implementation 
 *             scalar version (derived from DRAMA parallel version)
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
#include "PM_feelfem90smpi.hpp"
#include "feelfuncs.hpp"


//                >1234567890123456789012345678901234567890<
//                 integer                                 :: ");
#define  FEELFEM90SMPI_INDENT 40

// Constructor, Destructor

PM_feelfem90smpi::PM_feelfem90smpi()
{
  return;
}

PM_feelfem90smpi::~PM_feelfem90smpi()
{
  return;
}

// 2. I/O related

void PM_feelfem90smpi::OpenSource(char *filename)
{
  startSource( filename );
  Fortran90GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelfem90smpi::OpenSource(char *filename,int makeFlag)
{
  startSource( filename, makeFlag );
  Fortran90GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelfem90smpi::CloseSource()
{
  endSource(  );
  Fortran90GeneratorSetFP( NULL );
  return;
}

//  Filename handling

void PM_feelfem90smpi::pushSolveRoutineName( int no )
{
  char *ptr;

  ptr = GetSolveRoutineName( no );
  pushSource(ptr);
  delete ptr;
}


char *PM_feelfem90smpi::GetSourceName( const char *routineName)
{
  int   len = stringLength(routineName)+3+2;   // +2 = 90  (.f -> f90)
  char *ptr = new char[len];
  
  sprintf(ptr,"%s.f90",routineName);
  return(ptr);
}


// 3. General pushSource subroutine

void PM_feelfem90smpi::pushCoordinateSource(void)
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

void PM_feelfem90smpi::commentPM()
{
  writeSource("! feelfem90smpi Program Model");
  return;
}



// 5. General functional routine (memory allocation, memory 0 initialize)

void PM_feelfem90smpi::MODULEzeroclearD(char *varname, char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"call zerod(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelfem90smpi::MODULEzeroclearI(char *varname, char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"call zeroi(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelfem90smpi::
MODULEmalloc(char *name,char *comment,char *size, char *type)
{
  MODULEmallocF90(name,size);
  return;
}

void PM_feelfem90smpi::MemAllocate(const char *arrayname,const char *index,
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

void PM_feelfem90smpi::MemDeallocate(const char *arrayname,const char *index,
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
void PM_feelfem90smpi::
MODULEmallocERT(char *name,char *comment,char *size, char *type)
{
  MODULEmallocF90(name,size);
  return;
}

// F90 interface
void PM_feelfem90smpi::MODULEmallocF90(char *varName,char *varSize)
{
  pushSource("allocate(");
  pushSource(varName);
  pushSource("(");
  pushSource(varSize);
  pushSource("))");
  flushSource();
}


// 6. Calling sequence, variable name handling

void PM_feelfem90smpi::NameVariableInCalled( Variable *valPtr, string &name)
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

void PM_feelfem90smpi::pushVariableInCalled( Variable *valPtr)
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

void PM_feelfem90smpi::pushVariableNameInMain( Variable *varPtr)
{
  pushVariableInCalled( varPtr );   // fortran90
  return;
}


// variable memory allocation
void PM_feelfem90smpi::MainVariableAllocation( Variable *varPtr)
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
void PM_feelfem90smpi::doMainVariableInitialValue( Variable *varPtr)
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

void PM_feelfem90smpi::pushVariableListInMain( orderedPtrList <Variable *>vPtrLst)
{
  pushVariableListInCalled(vPtrLst);
}

void PM_feelfem90smpi::pushVariableListInCalled(orderedPtrList<Variable *>vPtrLst)
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


void PM_feelfem90smpi::pushVariableListInCalled( list <Variable *> varPtrLst)
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

void PM_feelfem90smpi::pushVariableListInCalledOnlyFEM(list <Variable *> varPtrLst)
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

void PM_feelfem90smpi::pushVariableListInSolve(orderedPtrList<Variable*>varPtrLst)
{
  pushVariableListInCalled( varPtrLst );  // fortran90 (same of called)
  return;
}


/* Add 2000/05/09  (now only in feelfem90smpi) */
void PM_feelfem90smpi::pushFEMVariableInCalled( Variable *varPtr)
{
  pushSource("fem_");
  pushSource(varPtr->GetName());
  return;
}

void PM_feelfem90smpi::pushFEMVariableInSolve( Variable *varPtr)
{
  pushFEMVariableInCalled( varPtr );    // f90 same 
  return;
}



///////////////////////////////////////////////////////////
void PM_feelfem90smpi::DefaultParameterBlock()
{
  //  comment();
  //  writeSource("! PM_feelfem90smpi::DefaultParameterBlock()");
  //  comment();

  doNothingNow("void PM_feelfem90smpi::DefaultParameterBlock()");
  return;

}


void PM_feelfem90smpi::PopReturn()                     // General in PM
{
  // ?????
  writeSource("      return");
  writeSource("      end");
  return;
}


/////////////////////////////////////////////////////////////////
// General components for generating subroutines
/////////////////////////////////////////////////////////////////
void PM_feelfem90smpi::pushTypeDefCC(char *s)
{
  int len = stringLength(s);
  pushSource(s);
  for(int i=0;i< FEELFEM90SMPI_INDENT - len; i++) {
    pushSource(" ");
  }
  pushSource(":: ");
  return;
}

void PM_feelfem90smpi::pushInteger4sc(void)
{
  pushSource(   "integer                                 :: ");
  return;
}

void PM_feelfem90smpi::pushInteger4pm(void)
{
  pushSource(   "integer,parameter                       :: ");
  return;
}

void PM_feelfem90smpi::pushInteger4In(void)
{
  pushSource(   "integer,intent(in)                      :: ");
  return;
}

void PM_feelfem90smpi::pushInteger4Ptr1(void)
{
  pushSource(   "integer,dimension(:)  ,pointer          :: ");
  return;
}

void PM_feelfem90smpi::pushInteger4Ptr2(void)
{
  pushSource(   "integer,dimension(:,:),pointer          :: ");
  return;
}

void PM_feelfem90smpi::pushLogical(void)
{
  pushSource(   "logical                                 :: ");
  return;
}


// write Integer
void PM_feelfem90smpi::writeInteger4sc(const char *str)
{
  pushInteger4sc();
  flushSource(str);
  return;
}

void PM_feelfem90smpi::writeInteger4pm(const char *str)
{
  pushInteger4pm();
  flushSource(str);
  return;
}

void PM_feelfem90smpi::writeInteger4In(const char *str)
{
  pushInteger4In();
  flushSource(str);
  return;
}

void PM_feelfem90smpi::writeInteger4Ptr1(const char *str)
{
  pushInteger4Ptr1();
  flushSource(str);
  return;
}

void PM_feelfem90smpi::writeInteger4Ptr2(const char *str)
{
  pushInteger4Ptr2();
  flushSource(str);
  return;
}

// real*8 
void PM_feelfem90smpi::pushReal8sc(void)
{
  pushSource(   "real(kind=REAL8)                        :: ");
  return;
}

void PM_feelfem90smpi::pushReal8pm(void)
{
  pushSource(   "real(kind=REAL8),parameter              :: ");
  return;
}

void PM_feelfem90smpi::pushReal8Ptr1(void)
{
  pushSource(   "real(kind=REAL8),dimension(:)  ,pointer :: ");
  return;
}

void PM_feelfem90smpi::pushReal8Ptr2(void)
{
  pushSource(   "real(kind=REAL8),dimension(:,:),pointer :: ");
  return;
}

void PM_feelfem90smpi::pushReal8Array1(void)
{
  pushSource(   "real(kind=REAL8),dimension(:)           :: ");
  return;
}

// write real*8
void PM_feelfem90smpi::writeReal8sc(const char *str)
{
  pushReal8sc();
  flushSource(str);
  return;
}

void PM_feelfem90smpi::writeReal8pm(const char *str)
{
  pushReal8pm();
  flushSource(str);
  return;
}

void PM_feelfem90smpi::writeReal8Ptr1(const char *str)
{
  pushReal8Ptr1();
  flushSource(str);
  return;
}

void PM_feelfem90smpi::writeReal8Ptr2(const char *str)
{
  pushReal8Ptr2();
  flushSource(str);
  return;
}

void PM_feelfem90smpi::writeLogical(const char *str)
{
  pushLogical();
  flushSource(str);
  return;
}

/////



void PM_feelfem90smpi::CoordinateVariableDeclaration(void)
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


void PM_feelfem90smpi::DoArgumentSequenceFromMain
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
  pushSource("(myrank,npmax,");
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
void PM_feelfem90smpi::MainVariableDeclaration(Variable *varPtr)
{
  ArgumentVariableDeclaration(varPtr); // in fortran90,  same as Arg...
  return;
}

void PM_feelfem90smpi::ArgumentVariableDeclaration(Variable *varPtr)
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
void PM_feelfem90smpi::ArgumentVariableDeclarationLst(list <Variable *>& varPtrLst)
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



void PM_feelfem90smpi::MPIinclude(void)
{
  writeSource("include 'mpif.h'");
  return;
}

/////////////////////////////////////////////////////////////////
// solve related component generators
/////////////////////////////////////////////////////////////////
void PM_feelfem90smpi::SourceStarters()
{
  copyright();
  commentPM();
  timestamp();
  
  return;
}


void PM_feelfem90smpi::F90useAlways(void)
{
  writeSource("! general modules");
  writeSource("use report90");      
  writeSource("use numeric");
  writeSource("use abortmodule");
  com();

  return;
}

void PM_feelfem90smpi::F90useFEMDataType(void)
{
  writeSource("! FEM DataType");
  writeSource("use femDataType");
  writeSource("use feelP2data");
  com();

  return;
}


void PM_feelfem90smpi::
DoDeclareVariablesFromMainPM( orderedPtrList<Variable *>varPtrLst)
{
  // Variable definitions (Arguments in solve routine)

  writeInteger4sc("myrank");
  writeInteger4sc("npmax");
  

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

