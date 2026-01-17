/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure.hpp 
 *  Date     : 2001/07/30
 *  Modified : 2001/10/26
 *  
 *  Purpose  : Store the correspondance information between 
 *             name and code number
 *
 *
 *             Important information on solvers are stored in this
 *             class.  (ex. symmetry solver or not etc.)
 *
 */

#ifndef FEM_CLASS_CONFIGURE
#define FEM_CLASS_CONFIGURE


#include <stdio.h>          // for WriteLIBSinMakefile (FILE *);

#include "pairClass.hpp"
#include "ptrList.hpp"

class Quadrature;

class Configure {
  
public:
  
  Configure();                     // Initialization  (Database)
                                   // src/Configure/*

  // Makefile initials
  int  HasMakefileAdditional(void) {return additionalEnvironmentFlag;}
  char *GetAdditionalMake() {return additional_environments; }
  char *GetF90()  { return f90_compiler;}
  char *GetF77()  { return f77_compiler;}
  char *GetCPP()  { return cpp_compiler;}
  char *GetCC()   { return c_compiler;  }
  
  void  SetF90(char *f90) { f90_compiler = f90; return; }

  // LIB section
  void UseSolverLibrary   ( int   );
  void StoreLIBSinMakefile( char *);
  void WriteLIBSinMakefile( FILE *);


  // Basic PDE file
  char *GetBasicPDE()   { return feelfem_basic_pde; }


  // Program Model and Solvers
  void StoreProgramModelNames(const char *,int);    // StrInt
  void StorePM_LIB(const char *,const char *, int); // StrStrInt
  void StoreDefaultPM_LIB(const char *,const char *); // StrStr

  // private function (called from StorePM_LIB)
  void StoreSolverNames      (char *);   // gmdamg, etc.

  // Quadratures
  Quadrature *GetDefaultQuadraturePtrByEtype(int );

  // for check routines
  int IsValidProgramModelName( string & );     // used in SNprogramModel

  int IsValidSolverName      ( string & );     // used in SNsolve
  int IsValidPM_LIB(string &,string &);// used in SNsolve

  int  GetProgramModelCodeFromName( string &);
  int  GetSolverLibraryCodeFromName( string &, string &);
  void SetProgramModelNameFromCode( int ,string &);      // danger???(01/11/26)
  void SetDefaultSolverName( string &,string &); // used in SNsolve::CheckInit();

  // Parametric Element
  void SetParametricElementName(int , string &);

  // for geom object
  void StoreMesherCode( char * , int );
  int IsValidMesherName( string &);
  int GetMesherCodeByName( string &);

  // correspondance between boundary etype and regional etype
  int GetBoundaryEtypeFromEtype( int );   // in Configure_Quadrature.cpp
  Quadrature *GetDefaultBoundaryQuadFromRegionEtype(int);

private:

  // initialize functions
  void init_StoreProgramModels();
  void init_StoreSolverLibraries();
  void init_DefaultSolveParameters();
  void init_MakefileParameters();
  void init_StoreGeomObj();

  void read_ResourceFile();


  ptrList <StrIntPair *>    programModelLst;   // PM-code pair
  ptrList <StrStrIntPair *> pglibPairLst;      // PM-LIB-code pair
  ptrList <StrStrPair *>    pglibDefaultPairLst; // default solver for each PM

  ptrList <string>          solverNameLst;     // no individual code

  ptrList <StrIntPair *>    mesherNameLst;

  // mesher


  //  list <string> solverNameLst;
  //  list <string> postProcessorNameLst;

  // Makefile data
  int    additionalEnvironmentFlag;
  string additional_environments;

  string f90_compiler;
  string f77_compiler;
  string cpp_compiler;
  string c_compiler;

  // where is the basic pde
  char *feelfem_basic_pde;

  // LIBS in Makefile
  list <int   >solverLibraryNumeroLst;
  list <string>LIBSinMakefileLst;

};

#endif
