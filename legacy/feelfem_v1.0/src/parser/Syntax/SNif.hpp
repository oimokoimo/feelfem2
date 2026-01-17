/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNif.hpp
 *  Date     : 2002/07/17
 *  Modified : 
 *  
 *  Purpose  : if class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_IF
#define FEM_SYNTAX_IF

#include "SNunit.hpp"

#include "list.hpp"
#include "string.hpp"

#include "Expression.hpp"
#include "IfBlock.hpp"

class Main;

class SNif : public SNunit {
public:
  SNif(Expression *ptr,char *nm) : SNunit("if",SN_IF) 
  { 
    exprPtr    = ptr;
    gotoLabel  = nm; 
    ifblockPtr = 0;
  }

  void print(ostream & ost) { 
    ost <<  "if (";
    exprPtr->print(ost);
    ost << ") goto " << gotoLabel; 
  }
  
  // check functions
  int labelDefined_check(list <string>&strLst);
  int checkValidExpr(void);

  // InfoGenerate
  int InfoGenerate(void);

  //  void CodeGenerate(void);
  void CodeGenerateMain(void *,Main *);      
  void CodeGenerate(void);                   // This is empty

private:
  Expression *exprPtr;
  string      gotoLabel;

  IfBlock *ifblockPtr;

};


#endif
