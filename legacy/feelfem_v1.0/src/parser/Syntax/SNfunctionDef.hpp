/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmaterialVar.hpp
 *  Date     : 2002/09/12
 *  Modified : 
 *  
 *  Purpose  : function definition
 *  
 */

#ifndef FEM_SYNTAX_FUNCTIONDEF
#define FEM_SYNTAX_FUNCTIONDEF

#include "stack.hpp"
#include "string.hpp"

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"


class SNfunctionDef : public SNunit {
public:
  SNfunctionDef( char *nm , SNidentifierlist *ptr) ;


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

  int GetNumberOfArgs();

  // check routines
  virtual int Check(void);

  // InfoGenerate
  virtual int InfoGenerate(void);

private:
  string                name;
  SNidentifierlist     *identifierLst;
  int                   arguments;
};


#endif
