/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Output.hpp
 *  Date     : 2002/04/23 (BCN)
 *  Modified : 
 *  
 *  Purpose  : Output class.  (general container)
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors 
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 *  
 */

#ifndef FEM_CLASS_OUTPUT
#define FEM_CLASS_OUTPUT

#include "orderedPtrList.hpp"
#include "Quadrature.hpp"
#include "Variable.hpp"

class Output {
public:
  Output();
  ~Output();

  int GetOutputNo(void);

  void AddIdentifier(string &);
  void AddVariablePtr(Variable *);

  void SetQuadraturePtr(Quadrature *);

  orderedPtrList <Variable *> &GetVarPtrList(void) {
    return varPtrLst;
  }  

  list <string> &GetOutputIdentifierList(void) {
    return identifierStrLst;
  }
  
  Quadrature *GetQuadraturePtr(void) {   // return NULL means fem variable out
    return(quadraturePtr);
  }

  int HowManyComponents(void) {
    return(components);
  }

  int HasOption(const char *);
  void GetOption(const char *key,string &);
  void AddOption(char *,char *);


private:
  static int outputs;
  int outputNo;

  int components;
  list <string>identifierStrLst;
  orderedPtrList <Variable *>varPtrLst;
  
  Quadrature *quadraturePtr;   // for ewise-quad


  int options;
  list <string>optionKeyStrLst;
  list <string>optionValStrLst;

};
  
#endif
