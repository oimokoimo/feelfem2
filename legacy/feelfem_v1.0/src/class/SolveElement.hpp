/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveElement.hpp
 *  Date     : 1999/11/16
 *  Modified : 1999/11/16
 *             2002/03/27 BoundaryIntegrandSet
 *  
 *  Purpose  : SolveElement class definition
 *  
 */
#ifndef FEM_CLASS_SOLVELEMENT
#define FEM_CLASS_SOLVELEMENT

#include "Variable.hpp"
#include "string.hpp"
#include "orderedList.hpp"
#include "orderedPtrList.hpp"

class Quadrature;
class ElementNodePattern;
class DiscretizedComponent;
class IntegrandSet;
class BoundaryIntegrandSet;

class EcalInfo;
class EsetInfo;

class SolveElement {
public:
  SolveElement();
  ~SolveElement();

  friend int operator == (const SolveElement &, const SolveElement &);

  int GetSolveNo(void);
  int GetElemNo(void);
  int GetEdatno(void);
  int GetNenfre(int );
  int GetNode();
  int GetNdf();
  int GetIelemNodes() {return ielemNodes;}
  int GetIthIENP(int);
  int GetIthIEDP(int);
  int GetNumberOfUnknowns(void);

  int GetQuadratures(void);
  Quadrature *GetIthQuadraturePtr(int);
  
  const orderedPtrList <Variable *>GetVariablePtrLst(void) {
    return ( varPtrLst );
  }

  const list <Variable *>GetUnknownVariablePtrLst(void){
    return ( unknownVarPtrLst);
  }
  
  const list <string>GetEcalCallValueLst(void) {
    return (testEcalCallValueLst);
  }

  // Interface
  void SetSolveNo( int );
  void SetElemNo( int );
  void SetEtype ( int );
  void SetSpaceDim( int );

  void SetParametricElement (string & );
  Element *GetParametricElementPtr(void);

  // In SNsolve_InfoGenerate_SE.cpp (for ApplyGalerkin())
  void AddUnknownVariablePtr( Variable * );
  void AddTestfuncStr( string &);

  void AddVariablePtr_uniq_exceptUnknown(Variable *);  // not register
  void AddVariablePtr_nonlinearCase(Variable *);        // in nonlinear case,
                                                        // unknown also added

  void SetMainQuadratureName( string &);
  void AddQuadratureName( string  );

  void AddIntegrandSetPtr( IntegrandSet *);
  void SetBoundaryIntegrandSetPtr(BoundaryIntegrandSet *);


  // Infogenerate
  void MakeElementNodePattern(void);   // SolveElement_Infogenerate.cpp
  void SetIENPIEDP(void);              // SolveElement_Infogenerate.cpp
  void SetNENFRE(void);                // SolveElement_Infogenerate.cpp


  // for Ecal routines
  int *GetNodePatternForEcal(Variable *);  // must be free by used function
  int *GetNodePatternForEcal(Element  *);  // must be free by used function

  // Regional Discretization (called from discretizedSolve.cpp)
  void ApplyGalerkinMethod(void);   // SolveElement_discretize.cpp 
  void GenerateEcalInfo(void);      // SolveElement_discretize.cpp
  void GenerateEsetInfo(void);

  DiscretizedComponent *GetIthDiscretizedComponentPtr(int ith);
  EcalInfo             *GetIthEcalInfoPtr(int ith);
  EsetInfo             *GetIthEsetInfoPtr(int ith);

  orderedList<string> &GetEcalIntegrandTermLst() {
    return(ecalIntegrandTermLst);
  }


  // P2 inteface (from test directory)
  void testSetSolveNo(int);
  void testSetElemNo(int);
  void testSetNonlinerFlag(int);

  void testSetEdatno(int);
  void testSetNodeFreedom(int,int *);
  void testSetIelemNodes(int);

  void testSetUnknowns(int);

  void testAddVariablePtr(Variable *);
  void testAddUnknownVariablePtr(Variable *);
  void testAddQuadraturePtr(Quadrature *);
  void testAddEcalArgs( char *);
  void testSetNonlinearFlag( int );

  void testSetNDFIENPIEDP(int,int *,int *);



  // nenfre
  // 
  //



  // debug
  void print(ostream &ost);

private:
  int solveNo;
  int elemNo;
  int edatno;         // Element data set No.
  int sub_edatno;     //
  int sub_mats;       //
  int *sub_matnos;    //
  int etype;          // Element type (Triangle,Rectangle, etc.)

  int nodes;          // Nodes in one element  set in testNodeFreedom
  int ielemNodes;     // 2002/02/06 = nodes, set at setNENFRE
                      // SolveElement_InfoGenerate.cpp  SetNENFRE

  int spaceDim;       // space dimension

  int nonlinearFlag;  // nonlinear flag

  int *nodeFreedom;   // nenfre in P2

  int  unknowns;
  int  knownFemVars;
  int  knownEwiseVars;
  int  knownScalarVars;

  int  ndf;          // totalFreedom
  int  nedf;         // ewise freedom
  int *ienp,*iedp;   // iedp,ienp

  list <Variable   *> unknownVarPtrLst;
  list <Quadrature *> quadraturePtrLst;
  int   quadratures;     

  orderedPtrList <Variable *> varPtrLst;   // in nonlinear, unknowns should be
                                           // included

  list <string>           testEcalCallValueLst;  // temporary P2 interface

  // For future upgrade
  string domainName;


  // ielem 
  Element            *parametricElementPtr;   // coordinate transformation
  ElementNodePattern *seENPPtr;

  // For GalerkinMethod class
  list <string> testfuncSymbolLst;                  //SNs_I_SE.cpp
  list <IntegrandSet *> integrandSetLst;

  // ecal,eset related
  list <DiscretizedComponent *>discretizedCompPtrLst;
  orderedList <string>    ecalIntegrandTermLst;
  list <EcalInfo *>ecalInfoPtrLst;
  list <EsetInfo *>esetInfoPtrLst;

};

#endif
