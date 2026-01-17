/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EwiseQuadTC.hpp
 *  Date     : 2002/07/23
 *  Modified : 
 *  
 *  Purpose  : TermConvert family for
 *             EwiseQuad point evaluation
 *  
 */

#ifndef FEM_CLASS_EWISEQUADTC
#define FEM_CLASS_EWISEQUADTC

#include "TermConvert.hpp"
#include "Variable.hpp"

class EwiseQuadTC :public TermConvert {
public:
  EwiseQuadTC();
  ~EwiseQuadTC();

  void AddVariable( Variable *);
  void AddVariableFEM(Variable *);        // this is special for EwiseQuad
  void ReverseAddVariableFEM(Variable *); // this is special for EwiseQuad

  void AddUserFunctionSymbol(void);       // this includes revere table also

private:

  int startingFuncNo;   // initial value is 1 

};

#endif
