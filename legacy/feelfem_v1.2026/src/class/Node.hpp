/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Node.hpp       (instance is FiniteElement/Node.cpp)
 *  Date     : 2002/01/03
 *  Modified : 
 *  
 *  Purpose  : Node definition
 *  
 */

#ifndef FEM_CLASS_NODE
#define FEM_CLASS_NODE

#include "orderedPtrList.hpp"
class Element;
class ostream;

class Node {

public:
  Node(int);                        // 0-dimensional
  Node(int,double);                 // 1-dimensional
  Node(int,double,double);          // 2-dimensional
  Node(int,double,double,double);   // 3-dimensional
  ~Node();

  //  AddNodeLstWithElement(orderedPtrList<Node *> &, Element * );  // SolveElement

  double eval() const;

  double GetXi(void)   { return xi;   }
  double GetEta(void)  { return eta;  }
  double GetZeta(void) { return zeta; }

  friend int operator == (const Node &left, const Node &right);
  friend int operator  < (const Node &left, const Node &right);

  // debug
  void print(ostream &ost);
  
private:
  int dimension;
  //  int degreeOfFreedom;
  int etype;                 // element type (tri,rect,tetra,cube, etc.)
  //  int ntype;                 // node type    (nodal, etc.)
  //  int elementNodeNumber;

  double xi,eta,zeta;

};

#endif
