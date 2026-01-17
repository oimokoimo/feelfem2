/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNewiseVar.hpp
 *  Date     : 2001/03/07
 *  Modified : 
 *  
 *  Purpose  : ewiseVar class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_EWISEVAR
#define FEM_SYNTAX_EWISEVAR

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"

class Variable;

class SNewiseVar : public SNunit {
public:
  SNewiseVar( char *nm ) 
    : SNunit("ewiseVar",SN_EWISEVAR) {

    name        = nm ;
    isAttribute = NO ;

  }

  SNewiseVar( char *nm,  char *bnm) 
    : SNunit("ewiseVar",SN_EWISEVAR) {

    name          = nm ;
    isAttribute   = YES;
    attributeName = bnm;

  }


  void print(ostream & ost) {
    ost << "ewise " << name ;
    if(isAttribute == YES) {
      ost << "[" << attributeName << "]";
    }
  }
  
  void errWrtName(ostream &ost ) {
    ost << name;
    return;
  }

  void errWrtData(ostream &ost ) {
    ost << attributeName;
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

  Variable *CreateVariablePtr(void);

private:
  string  name;

  int     isAttribute;
  string  attributeName;

};


#endif
