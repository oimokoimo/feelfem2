/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelement.hpp
 *  Date     : 2001/03/05
 *  Modified : 
 *  
 *  Purpose  : SNelement class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_ELEMENT
#define FEM_SYNTAX_ELEMENT

#include "stack.hpp"         // use stack (list)
#include "string.hpp"
#include "orderedPtrList.hpp"

#include "SNunit.hpp"

class Element;
class Node;

class SNelementIntp;

class SNelement : public SNunit {

public:

  // constructor  (initialize all value..)
  SNelement( char *nm, char *elem, stack <SNunit *> &) ;

  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  // following functions are used in element_check.cpp
  int setEtype(void);          // set etype, if error, return non zero.
  int CheckNodeDimension();    // check node dimension consistency
  int CheckSystemVariables();  // check usage of x1,x2,..., nx,ny,nz,...



  // element information generator
  int EvalExpressions(void);      // evaluate double, assignment with defaults
                                  // (for checking)

  int ParseInterpolates(void);    // make node list, etc.
                                  // (in SNelement_CHECK.cpp)

  int CheckInterpType(void);      // check nodal, dx,dy,dz, dn etc.

  // Information functions  (used check routine, etc.)
  int GetNumberOfInterpolates(void);
  int GetNumberOfNodes(void);        


  // Generate Element class
  int InfoGenerate(void);


  // for error message
  void errWrtName(ostream &ost ) {
    ost << name;
    return;
  }


  // for debug
  void print(ostream & ) ;


private:

  string name;
  string elementShape;
  int    etype;               // assigned in SetEtype called from check routine
  int    dimension;           // assigned in SetEtype called from check routine

  int    doubles;
  int    assignments;

  int    interpolates;      // (interpolates > nodes) always,,,
  int    nodes;

  list <SNunit *>dblAndAssignPtrLst;
  list <SNelementIntp *>intpPtrLst;   // 

  orderedPtrList <Node *>nodeOrderedPtrLst;
  
  Element *elemPtr;    // generated InfoGenerate function

  void setIntpEtype(void);   // inner function, called SNelement::setEtype()

};
#endif
