/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Variable.hpp
 *  Date     : 1999/11/17
 *  Modified : 2001/03/08
 *  
 *  Purpose  : Variable class
 *             
 *             ref.  Solve/Variable.cpp
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

#ifndef FEM_VARIABLE_CLASS
#define FEM_VARIABLE_CLASS

#include "feeldef.hpp"
#include "list.hpp"
#include "string.hpp"

class Element;
class Quadrature;
class Variable;
class ostream;
class RegionObject;

// Variable related external function

class Variable {
public:
  Variable();
  Variable(char *,int);
  ~Variable();
  
  int isNameIs(const char *nm) {
    return(varName == nm);
  }
  const char *GetName();     // used in pushSource();.... uuum

  int   GetType();  // VAR_FEM,(VFEM,EWISE,EWISE_A,DOUBLE,INT,CONST)
  int   GetEwiseType();  // EWISE_TYPE_INTERPOLATION or _GAUSSPOINT
  int   GetEtype();      // Only for VAR_FEM,EWISE_A
  int   GetFEMVarType(); //

  int   IsConsistentEtypeWith( int refEtype);  // check consistency 

  int   GetFreedom(void);       // = GetEWISEFreedom() + GetFEMFreedom()
  int   GetEWISEFreedom(void);
  int   GetFEMFreedom(void);  
  int   GetMATERIALFreedom(void);
  
  int   IsElementPtrReady(void);

  void  SetInitialFlag(void)      { 
                                    initialFlag  = 1;    
                                    numerateInitialNo++;
                                    initialNo = numerateInitialNo;
                                    return; 
                                  }
  void  SetInitialValue(double d) { 
                                    initialValue = d;
				    numerateDblInitialNo++;
				    dblInitialNo = numerateDblInitialNo;
                                    return; 
                                  }

  void  SetIntInitialValue(int n) { 
                                    intInitialValue = n; 
				    numerateIntInitialNo++;
				    intInitialNo = numerateIntInitialNo;
                                    return; 
                                  }

  int    GetInitialFlag(void)     { return initialFlag;     }
  double GetInitialValue(void)    { return initialValue;    }
  int    GetIntInitialValue(void) { return intInitialValue; }

  int    GetInitialNo(void)       { return initialNo;    }
  int    GetDblInitialNo(void)    { return dblInitialNo; }
  int    GetIntInitialNo(void)    { return intInitialNo; }


  ///////////////////////
  void testPutElementFreedom(int n) { elementFreedom = n; return;}
  int  testGetElementFreedom(void ) { return(elementFreedom); }

  void operator = (const Variable &);

  void SetFunctionName(const char *);
  void SetParameters(void); // set information for VAR_EWISE_A and VAR_FEM


  // material variable
  void SetMaterialKinds(int);
  void SetMaterialValuePair( string &, double );
  double GetMaterialValueByName(const char *);         // this is by material name
  double GetMaterialValueByRegionName( string &);      // this is by region name
  int  HasDefinedForThisRegionPtr(RegionObject *); // var_material_region_check.cpp
  void GetMaterialNameByRegionName (string &,string &);


  // Comparison in orderedPtrList
  // int operator < (const Variable &, const Variable &);
  friend int operator <  (const Variable &, const Variable &);
  friend int operator == (const Variable &, const Variable &);

  Quadrature *GetQuadraturePtr(void);
  Element    *GetElementPtr   (void);



  // for term convert
  void SetSblNo(int no);
  int  GetSblNo(void);
  void SetElementTCNo( int no);
  int  GetElementTCNo(void);
  void SetElementStno( int no);
  int  GetElementStno(void);
  
  void SetFunctionTCNo( int no);   // for ewiseQuad
  int  GetFunctionTCNo( void  );
  
  void initWorkTC(void);

  // error check
  void print(ostream &);

private:
  int    varType;  // variable Type  VAR_FEM, VAR_EWISE, VAR_EWISE_A
                   //                VAR_DOUBLE,VAR_INT,VAR_CONST

  string varName;  // variable name

  int    initialFlag;      // used to avs-double, gid-double, etc.
  double initialValue;     // used to avs-double, gid-double, etc.
  int    intInitialValue;  // intger initial value field

  int    initialNo;        // initial no as  (double+integer)
  int    dblInitialNo;     // initial no for double
  int    intInitialNo;     // initial no for integer

  static int numerateInitialNo;
  static int numerateDblInitialNo;
  static int numerateIntInitialNo;


  string functionName;     // Interpolation name or quadrature method name
  int    elementFreedom;   // element freedom for VAR_FEM,VAR_EWISE_A

  int    ewiseType;        // specified by element or quadrature
                           // EWISE_TYPE_MATERIAL  or
                           // EWISE_TYPE_INTERPOLATION
                           // EWISE_TYPE_GAUSSPOINT
  Element    *ePtr;
  Quadrature *qPtr;

  // for termConvert temporary work information
  int sblNo_termConvert;
  int elementNo_termConvert;
  int elementStno_termConvert;
  int functionNo_termConvert;

  // for ecal position for fem vfem ewise-fem variables
  int  ielemNodes;
  int *iedp;

  // for material
  int           pairs;
  list <string> materialStrLst;
  double       *materialValues;                 // allocated SetMaterialKinds();

};

ostream & operator << ( ostream &,  Variable &);   // debug use

#endif
