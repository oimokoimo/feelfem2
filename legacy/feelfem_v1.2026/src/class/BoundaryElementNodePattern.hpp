/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryElementNodePattern.hpp
 *  Date     : 2002/04/09
 *  Modified : 
 *  
 *  Purpose  : Element node pattern controling class
 *  
 */

#ifndef FEM_CLASS_BOUNDARYELEMENTNODEPATTERN
#define FEM_CLASS_BOUNDARYELEMENTNODEPATTERN

#include "Variable.hpp"
#include "Element.hpp"

#include "Node.hpp"

#include "string.hpp"
#include "orderedPtrList.hpp"

class ostream;

class BoundaryElementEquationNo {   //  iedp, ienp for each unknown variable
public:
  BoundaryElementEquationNo(const char *,int);       
  ~BoundaryElementEquationNo();

  void SetIthIenpIedp( int , int , int );
  
private:
  string varName;
  int    freedom;

  int   *ienp;        // local element node number
  int   *iedp;        // 
};


class BoundaryElementNodePattern {

public:
  
  BoundaryElementNodePattern();
  ~BoundaryElementNodePattern();

  void AddUnknownVariable(Variable *); // for unknown variable(make iedp,etc.)
  void AddNodeByVariable(Variable *);  // for known variable
  void AddNodeByElement(Element *);    // for parametric element
  void MakePattern();

  void print(ostream &);

  int  GetNodes(void);
  int  GetTotalFreedom(void);
  int  GetEwiseFreedom(void);

  int *MakeIEDPcopy(void);      // allocate memory, must be freed in calling
  int *MakeIENPcopy(void);      // allocate memory, must be freed in calling
  int *MakeNENFREcopy(void);    // allocate memory, must be freed in calling

  // used for ecal routines
  int *MakeNodeInfoForFEMvar( Element  *);
  int *MakeNodeInfoForFEMvar( Variable *);

private:
  void SetEtype(int);

  // src/FE/BoundaryElementNodePattern_Eqno.cpp
  void MakeElementEquationNo(void); 

  string domain;    // domain name  (still optional)

  int etype;        // etype for regional
  int betype;       // boundary etype
  int unknowns;

  int numberOfFEMVariables;
  int numberOfVFEMVariables;
  int numberOfEWISEVariables;

  list    <Variable *>unknownVarPtrLst;
  ptrList <Element *>elementPtrLst;

  orderedPtrList <Node *>nodeOrderedPtrLst;
  Node *ewiseNodePtr;                        // element wise node ptr

// pattern information
  int nodes;
  int totalFreedom;    // node freedom + ewise freedom
  int ewiseFreedom;    // ewise freedom

  int ewiseNodeNo;  // if there is an ewise variable, ewiseNodeNo has its 
                    // associated node.

  int *ienp;       // connection between local eq. No. to local node No.
  int *iedp;       // increment at each node for local equation
  int *nenfre;     // node freedom at each element node  

  list <BoundaryElementEquationNo *>elemEqNoPtrLst;

};

#endif
