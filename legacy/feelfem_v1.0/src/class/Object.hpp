/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Object.hpp
 *  Date     : 1999/11/29
 *  Modified : 1999/11/29
 *  
 *  Purpose  : Registration class for all objects
 *  
 *             Object feelfemobj is assigned in Object/initObject.cpp
 *             extern feelfemobj is declared in feelfuncs.hpp
 */

#ifndef FEM_CLASS_OBJECT
#define FEM_CLASS_OBJECT

#include "feeldef.hpp"
#include "Variable.hpp"
#include "Element.hpp"
#include "Quadrature.hpp"
#include "list.hpp"
#include "Solve.hpp"
#include "Assign.hpp"
#include "Output.hpp"
#include "Label.hpp"

class Main;
class Bamg;
class Function;   // user function
class SNfunction;

class Object {
public:
  Object();
  ~Object();

  // Variable Objects
  void     StoreVariable(Variable );
  void     StoreVariable(Variable *);
  Variable *GetVariablePtrWithNameType(const char *, int);
  Variable *GetVariablePtrWithName(const char * );
  int       GetVariableTypeWithName(const char *);
  int       GetVariableTypeWithName(string & );

  // Ewise assignmen
  int      StoreParametricElementEw(const char *);      // with check
  Element *GetParametricElementPtrEwByEtype(int etype);
  

  void     StoreElement(Element *);
  Element  *GetElementPtrByName(const char *);

  void        StoreQuadrature(Quadrature *);
  Quadrature *GetQuadraturePtrByName(const char *);

  void     StoreInitialDouble(Variable *);  // with initialize from outer tool
  list <Variable *>&GetInitialDblVarList(void) {
    return initialDblVarPtrLst;
  }
  int      HowManyInitialDoubles(void) {return initialDoubles;}

  void     StoreInitialInteger(Variable *);  // with initialize from outer tool
  list <Variable *>&GetInitialIntVarList(void) {
    return initialIntVarPtrLst;
  }
  int      HowManyInitialIntegers(void) {return initialIntegers;}

  void     StoreMaterialVar(Variable *);
  list <Variable *>&GetMaterialVarList(void) {
    return materialVarPtrLst;
  }

  // 02/11/23 for write sentence
  list <Variable *>&GetVariablePtrList(void) {
    return(varPtrLst);
  }

  int      HowManyMaterialVars(void) { return numberOfMaterialVars; }

  int      IsUsedUserFunctionName(string &);
  int      HowManyUserFunctions(void) {return numberOfUserFunctions;}
  void     StoreUserFunction(Function *);
  list <Function *>&GetUserFunctionList(void) {
    return userFunctionPtrLst;
  }
  Function *GetFunctionPtrByName(string &);
  int      GetUserFunctionTCno(int arguments);   // int
  int      GUFTCN2(int,int);                     // coroutine

  // for check user function
  void     StoreSNfunctionPtr( SNfunction *);
  list <SNfunction *>&GetSNUserFunctionList(void) {
    return snUserFunctionPtrLst;
  }

  // Label
  void     StoreLabelPtr(Label *);
  Label   *GetLabelPtrByName(const char *);
    

  // set from mesh_check_dimension
  // set from 
  void     SetSpaceDimension(int n) { spaceDimension = n;     }

  int      GetSpaceDimension(void ) { return(spaceDimension); }

  // Solve objects
  void StoreSolve(Solve *);
  int HowManySolves(void);
  Solve *GetIthSolvePtr(int);   // i-th (starts 0)

  // Assign objects
  void StoreAssign(Assign *);
  int HowManyAssigns(void);

  // Output objects
  void StoreOutput(Output *);
  int HowManyOutputs(void);

  // Mesh objects ( for 2D problem, using bamg mesh generator)
  void     PutBamgPtr( Bamg * );

  // check function family
  int IsDefinedVariable(const char *);

  int IsDefinedElementName( const char *);
  int IsDefinedElementName( string & );
  int IsDefinedQuadratureName( const char *);

  int IsDefinedFEMVariable( const char *);      // not VFEM, now(02/01/21)
  int IsDefinedEWISEVariable( const char *);
  int IsDefinedScalarVariable( const char *);
  int IsDefinedMaterialVariable( const char *);

  int IsDefinedUnknownVariable( const char *);  // FEM and EWISE_A(element)

  // for Main class generation
  void MakeVarLstForMain( Main *);

  // for mesher code
  void SetMesherCode(int);
  int GetMesherCode();

  // File objects
  void StoreFileObject( const char *);
  int  GetFileObjects();
  list <string> &GetFileObjectStrList(void) {
    return( fileObjectStrLst );
  }

  void StoreTmpFileObject( const char *);
  int  GetTmpFileObjects();
  list <string> &GetTmpFileObjectStrList(void) {
    return( tmpFileObjectStrLst );
  }

private:
  // Basic information
  int spaceDimension;
  int used_mesher_code;

  // Variable Objects
  int variables;
  list <Variable *> varPtrLst;

  // Element Objects
  int elements;
  list <Element *> elementPtrLst;

  // Quadrature Objects
  int quadratures;
  list <Quadrature *> quadraturePtrLst;

  // Parametric Information
  Element *lineParametricElementPtr;
  Element *triParametricElementPtr;
  Element *rectParametricElementPtr;
  Element *tetraParametricElementPtr;
  Element *hexParametricElementPtr;

  // Solve Objects
  int solves;
  list <Solve *> solvePtrLst;

  int assigns;                  // used in making main routines
  list <Assign *>assignPtrLst;  // not used...

  int outputs;
  list <Output *>outputPtrLst;

  // Mesh Information
  Bamg *bamgPtr;

  int initialDoubles;
  list <Variable *>initialDblVarPtrLst;

  int initialIntegers;
  list <Variable *>initialIntVarPtrLst;

  int numberOfMaterialVars;                   // 2002/09/01(material var)
  list <Variable *>materialVarPtrLst;

  // label information
  list <Label *>labelPtrLst;

  // file objects
  int fileObjects;
  list <string>fileObjectStrLst;

  int tmpFileObjects;
  list <string>tmpFileObjectStrLst;

  int numberOfUserFunctions;
  list <Function *>userFunctionPtrLst;

  int arg1Functions;
  int arg2Functions;
  int arg3Functions;

  // for error check
  list <SNfunction *>snUserFunctionPtrLst;

};

#endif
