/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Element.hpp
 *  Date     : 1999/11/17
 *  Modified : 1999/11/17
 *  
 *  Purpose  : Element class definition
 *  
 *  
 *  
 *  In case for Boundary element,
 *  
 *     freedom     has 'boundary' freedom
 *  
 *     Node * list has 'boundary' node list
 *  
 *     Interpolation is a copy of Region interpolation copy, while
 *     expression may '0'.  Corresponding boundary Node is stored
 *     in Interpolation->boundaryNodePtr
 *  
 *  
 */

#ifndef FEM_CLASS_ELEMENT
#define FEM_CLASS_ELEMENT

#include <iostream.h>
#include "string.hpp"
#include "orderedPtrList.hpp"

#include "Node.hpp"
#include "Interpolation.hpp"

class SNelement;
class TermConvert;

class Element {
  
public:
  Element();  // Constructor
  ~Element(); // Destructor

  // Generation of class, called from SNelement_InfoGenerate.cpp
  void SetName( const char *nm);
  void SetEtype( int );
  void SetType( int );
  void SetNumberOfNodes( int );
  void SetNumberOfFreedom( int );

  void AddNodePtr( Node *);
  void AddInterpolationPtr(Interpolation *); // for eset

  int isNameIs(const char *nm) {
    return(name == nm);
  }

  int isNameIs(string &nm) {
    return(name == nm);
  }

  int IsDependentCoordinate();    // for eset routine

  int IsBoundaryElement(void) {
    return(boundaryElementFlag);   // return(YES) or return(NO)
  }

  int HasAlreadyDefinedNode( Node *);

  int GetEtype(void) {
    return(elementEtype);
  }

  int GetElementFreedom(void) {
    return(numberOfFreedom);
  }
  void print(ostream &ost) {
    ost << "Element.h::print " << name << endl;
  }

  // used in ElementNodePattern::MakePattern()
  void SetNodePtrInGivenList( orderedPtrList <Node *> &);
  
  // used in ElementNodePattern::MakeElementEquationNo();
  Node *GetIthInterpolationNodePtr(int);

  // used in BoundaryElementNodePattern::MakeElementEquationNo();
  Node *GetIthInterpolationBoundaryNodePtr(int);
  
  const char *GetName();     // class violation

  friend int operator == (const Element & , const Element &);


  // used in eset
  Interpolation *GetIthInterpolationPtr(int i);

  // TermConvert functions
  void SetEstNo(int no);
  int  GetEstNo(void);
  
  void initWorkTC(void);

  // boundary element
  Element *AcquireBoundaryElementPtr(void);
  Element *GetParentElementPtr(void);
  int GetIthOriginalIplus1( int );
  Node *GetIthBoundaryInterpolationNodePtr( int );  // GetIthOriginal+get bndP

private:
  void MakeBoundaryElement(void); // make Surface element nElementPtr
  void MakeBoundaryElement_tri(TermConvert &);
  void MakeBoundaryElement_rect(TermConvert &);
  void MakeBoundaryElement_tetra(TermConvert &);
  void MakeBoundaryElement_cube(TermConvert &);

  string name;
  int    elementEtype;    // ELEMENT_TYPE_POINT,ELEMENT_TYPE_LINE,...

  int    elementType;     // FEM_TYPE_NODAL,FEM_TYPE_HELMITE,...

  int    numberOfNodes;   // 
  int    numberOfFreedom; // numberOfFreedom > numberOfNodes

  int    numberOfRegionFreedom;  // number of original regional interpolations
                                 // in boundary element

  int    coordinateDependFlag;   // element is dependent on coordinate or not.

  int    boundaryElementFlag;

  orderedPtrList <Node *> nodePtrLst;   // be careful, these Node * are
                                        // allocated at SNelement_CHECK.cpp
                                        // 
                                        // for boundary element, it has
                                        // Boundary Node list

  orderedPtrList <Interpolation *>interpPtrLst;  // _InfoGenerate.cpp
                                        // In Boundary case, boundary node
                                        // is Interpolation->boundaryNodePtr
                                        // stored in MakeBoundaryElement_*.cpp
  // TermConvert work value
  int    estno_termConvert;   // element starting number of function symbol

  Element *bElementPtr;        // Neumann codition basis
  Element *rElementPtr;        // if boundary, region parent element pointer

  int     *bInterpolationFlag; // used for Element::GetIthOriginalIplus(int i)
                               // set in MakeBoundaryElement_***.cpp
                               // BOTH REGIONAL AND BOUNDAY HAS SAME INFO
                               // (INDEPENDENTLY ALLOCATED MEMORY)
};

#endif
