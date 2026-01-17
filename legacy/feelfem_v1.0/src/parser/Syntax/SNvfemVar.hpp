/*
 *  feelvfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNvfemVar.hpp
 *  Date     : 2001/03/07
 *  Modified : 
 *  
 *  Purpose  : vfemVar class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_VFEMVAR
#define FEM_SYNTAX_VFEMVAR

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"

class SNvfemVar : public SNunit {
public:
  SNvfemVar( char *nm,  char *bnm) 
    : SNunit("vfemVar",SN_VFEMVAR) {

    name        = nm ;
    elementName = bnm;

  }

  void print(ostream & ost) {
    ost << "vfem " << name << "[" << elementName << "]";
  }
  void errWrtName(ostream &ost ) {
    ost << name;
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
  

private:
  string  name;
  string  elementName;

};


#endif
