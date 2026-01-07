/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNdomain.hpp
 *  Date     : 2001/02/27
 *  Modified : 
 *  
 *  Purpose  : domain class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_DOMAIN
#define FEM_SYNTAX_DOMAIN

#include "SNunit.hpp"
#include "../../class/string.hpp"

class SNdomain : public SNunit {
public:
  SNdomain( char *nm, SNunit *rptr) 
    : name(nm),regionLst(rptr),SNunit("domain",SN_DOMAIN) {
    return;
  }

  void print(ostream & ost) {
    ost << "domain ";
    ost <<  name;
    regionLst->print(ost);
    return;
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
  SNunit *regionLst;

};


#endif
