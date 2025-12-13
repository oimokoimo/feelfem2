/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementNodePattern.hpp
 *  Date     : 2002/01/31
 *  Modified : 
 *  
 *  Purpose  : Element node pattern controling class
 *  
 */

#ifndef FEM_CLASS_ELEMENTNODEPATTERN
#define FEM_CLASS_ELEMENTNODEPATTERN

#include "Variable.hpp"
#include "Element.hpp"

#include "Node.hpp"

#include "string.hpp"
#include "orderedPtrList.hpp"

class ostream;

class ElementEquationNo {   //  iedp, ienp for each unknown variable
public:
  ElementEquationNo(const char *,int);       
  ~ElementEquationNo();

  void SetIthIenpIedp( int , int , int );
  
private:
  string varName;
  int    freedom;

  int   *ienp;        // local element node number
  int   *iedp;        // 
};


class ElementNodePattern {

public:
  
  ElementNodePattern();
  ~ElementNodePattern();

  void AddUnknownVariable(Variable *); // for unknown variable(make iedp,etc.)
  void AddNodeByVariable(Variable *);  // for known variable
  void AddNodeByElement(Element *);    // for parametric element

  void MakePattern();                  // with unknown control
                                       // ewise unknown add node

  void MakePatternEwiseQuad();         // with no unknowns
                                       // with no ewise node, making ienp,iedp

  void print(ostream &);

  int  GetNodes(void);
  int  GetTotalFreedom(void);
  int  GetEwiseFreedom(void);
  int *MakeIEDPcopy(void);
  int *MakeIENPcopy(void);
  int *MakeNENFREcopy(void);

  // used for ecal routines
  int *MakeNodeInfoForFEMvar( Element  *);
  int *MakeNodeInfoForFEMvar( Variable *);

private:
  void SetEtype(int);
  void MakeElementEquationNo(void); //FiniteElement/ElementNodePattern_Eqno.cpp

  string domain;    // domain name

  int etype;
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

  list <ElementEquationNo *>elemEqNoPtrLst;

};

#endif
