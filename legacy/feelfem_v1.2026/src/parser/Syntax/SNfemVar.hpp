/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfemVar.hpp
 *  Date     : 2001/03/07
 *  Modified : 
 *  
 *  Purpose  : femVar class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_FEMVAR
#define FEM_SYNTAX_FEMVAR

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"

class Variable;

class SNfemVar : public SNunit {
public:
  SNfemVar( char *nm,  char *bnm) 
    : SNunit("femVar",SN_FEMVAR) {

    name        = nm ;
    elementName = bnm;

  }

  void print(ostream & ost) {
    ost << "fem " << name << "[" << elementName << "]";
  }

  
  void errWrtName(ostream &ost ) {
    ost << name;
    return;
  }
  
  void errWrtData(ostream &ost ) {
    ost << elementName;
    return;
  }


  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  Variable *CreateVariablePtr(void);  

  int IsDefinedElement();

private:
  string  name;
  string  elementName;

};


#endif
