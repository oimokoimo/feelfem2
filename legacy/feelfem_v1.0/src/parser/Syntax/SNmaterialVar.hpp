/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmaterialVar.hpp
 *  Date     : 2002/08/29   (copy from SNewiseVar.hpp)
 *  Modified : 
 *  
 *  Purpose  : materialVar class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_MATERIALVAR
#define FEM_SYNTAX_MATERIALVAR

#include "stack.hpp"
#include "string.hpp"

#include "SNunit.hpp"


class SNoption;
class Variable;
class SNunit;

class SNmaterialVar : public SNunit {
public:
  SNmaterialVar( char *   ,stack <SNunit *> &) ;

  void print(ostream & ost);
  
  void errWrtName(ostream &ost ) {
    ost << name;
    return;
  }

  void errWrtData(ostream &ost ) {
    return;
  }

  // check routines
  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  int IsValidAttribute(void);
  int CheckPairs(void);
  int CheckRegions(void);

  Variable *CreateVariablePtr(void);

private:
  string  name;
  int               options;
  list <SNoption *> optionLst;

  int               pairs;
  double           *values;   // allocate and set at SNmaterialVar_CHECK.cpp

};


#endif
