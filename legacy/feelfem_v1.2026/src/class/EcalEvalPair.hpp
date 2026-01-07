/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EcalEvalPair.hpp
 *  Date     : 2002/09/10
 *  Modified : 
 *  
 *  Purpose  : Separate from EcalInfo.hpp on 2002/09/10
 *  
 */

#ifndef FEM_CLASS_ECALEVALPAIR
#define FEM_CLASS_ECALEVALPAIR

class Element;

class EcalEvalPair {
public:
  EcalEvalPair(Element *, int );
  ~EcalEvalPair();

  friend int operator == (const EcalEvalPair &, const EcalEvalPair &);
  int      GetType() { return diffType; }
  Element *GetElementPtr() { return elemPtr; }

private:
  int diffType;          // Differentiation type
                     // TYPE_DIFF_ZERO,TYPE_DIFF_X,Y,Z
  Element *elemPtr;
};


#endif
