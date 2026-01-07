/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementType
 *  Date     : 2002/11/02
 *  Modified : 
 *  
 *  Purpose  : element type class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_ELEMENTTYPE
#define FEM_SYNTAX_ELEMENTTYPE

#include "SNunit.hpp"
#include "SNname.hpp"
#include "SNidentifierlist.hpp"

class SNelementType : public SNunit {
public:
  SNelementType( SNidentifierlist *lstPtr);
  ~SNelementType() { // do nothing 
    ;}
  // print
  void print(ostream & ost) 
  { ost << "etype list  (UC for print)" 
	<< endl; 
  return;}

  // check functions
  int  IsValidElementTypeName(void);  // in SNelementType_CHECK.cpp
                                      // add feelfemgeomobj

  // store into geometry object
  int InfoGenerate(void);

  // Code generate functions  (ProgramModel has no instance.)
  void CodeGenerate(void);
  void CodeGenerateMain(void *p,Main *m);

  // for SystemError functions
  void errWrtName(ostream &ost ) {
    etypeIdentifierLst->print(ost);
    return;
  }
 
private:

  SNidentifierlist *etypeIdentifierLst;  // valid only for GiD

};


#endif
