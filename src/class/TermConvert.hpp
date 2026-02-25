/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert.hpp
 *  Date     : 2001/06/20
 *  Modified : 2002/04/01   Simple reverse added 
 *             2002/09/01   Material variable
 *             2002/09/16   user function symbol
 *             2002/09/18   user function symbol list
 *  
 *  Purpose  : Term conversion 
 *  
 *             u -> m1*_n1(x,y),,, etc.
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
 */

#ifndef FEM_CLASS_TERMCONVERT
#define FEM_CLASS_TERMCONVERT

#define TERMCONVERT_EXPRESSION_BUFLEN  4096

//#include <stdio.h>    // for BUFSIZ
#include <iostream> // for print
#include <cassert>

#include "feeldef.hpp"
#include "ptrList.hpp"
#include "pairClass.hpp"

class Element;
class Variable;

class TermConvert {

public:
  TermConvert();
  ~TermConvert();

  void storeConvertPair(const char *, const char *);
  void replaceConvertPair(const char *,const char *);  // if exists replace,
                                                       // if not exists create

  // AddVariable function for 
  void AddVariable(Variable * );         // return value is starting..
  void StoreVariableList( Variable *);   // for making reverse  with uniq check

  void AddVariableBoundary(Variable * ); // for boundary part

  // these functions are called from AddVariable
  virtual void AddVariableFEM(Variable *);
  void  AddVariableEWISEquad(Variable *);
  void  AddVariableEWISEmaterial(Variable *);
  void  AddVariableMaterial(Variable *);
  void  AddVariableScalar(Variable *);

  void  AddVariableFEM_boundary(Variable *);
  void  AddVariableEWISEquad_boundary(Variable *);
  void  AddVariableEWISEmaterial_boundary(Variable *);
  void  AddVariableScalar_boundary(Variable *);  


  // Reverse converter
  void MakeReverseTC(void);    // this is for weak integrand (with Variable)
  void MakeReverseTC_boundary(void); // for boundary integrand

  virtual void ReverseAddVariableFEM(Variable *);
  void ReverseAddVariableEWISEquad(Variable *);
  void ReverseAddVariableEWISEmaterial(Variable *);
  void ReverseAddVariableMaterial(Variable *);
  void ReverseAddVariableScalar(Variable *);

  void ReverseAddNormalComponent_boundary(void);    // for normal components
  void ReverseAddVariableFEM_boundary(Variable *);
  void ReverseAddVariableEWISEquad_boundary(Variable *);
  void ReverseAddVariableEWISEmaterial_boundary(Variable *);
  void ReverseAddVariableScalar_boundary(Variable *);

  // called from GalerkinMethod::GalerkinTestFunction
  void SetTestFunctionSymbol( string &, int );
  void SetTestFunctionSymbol_boundary( string &, int );

  // Do convert function
  char *convertExpressionString( const char *);
  char *convertExpressionStringDBL( const char *);   // 1 -> 1.0 etc
  char *SimpleReverseConvertExpressionString( const char *);  // 2002-04-01
  char *ReverseConvertExpressionString( const char *);        // by Variable

  void GetConvertedElementPtrList( list<Element *> &);
  void GetConvertedIdentifierList( list<string> &);
  void GetConvertedIdentifierInReverseList( list<string> &);

  void GetConvertedUserFuncStrList(list <string> &);
  void GetConvertedUserFuncStrInReverseList( list <string> &);
  void StoreIgnoreSymbolLstForConvertedStrLst(const char *nm);

  // for boundary normal component
  // TermConvert_SpecialStore_Boundary.cpp
  void SetNormalComponent_boundary();
  void UseNX(void);
  void UseNY(void);
  void UseNZ(void);

  //  used for eset routine
  void StoreMetaPair(const char *from, const char *to);
  //                 from --> _m1,_m2,_m3, ..   -> to  (in reverse)


  //  Expression *convertExpression(const Expression &);

  // private judge functionn
  int is_identifier_char( char );
  int is_identifier_start_char( char );
  int is_number_exp_char( char );
  int is_delimiter(char );
  int is_number(char );

  void putChar(char);  // write outputBuf
  void putIdentifier(void);
  void putIdentifierReverse(void);   // simple reverse (2002/04/01)
  void putStr(const char *);
  //  void putStr(string &);

  void print(std::ostream &);
  void rev_print(std::ostream &);

protected:
  TermConvert *reverseTC;    // accessed also from derived EwiseQuadTC 020729

private:

  // private functions
  void makeNthSymbol(char *,int , int );  // makeLinearCombi has also make smbl

  // makeLinearCombi has also make smbl
  void makeNthSymbol_boundary(char *,int , int );  

  void makeLinearCombi(char *buf, int bufferSize,
		       int stno,    // starting symbol no.
		       int estno,   // starting function no
		       int freedom );// number of freedom

  void makeLinearCombi_boundary(char *buf, int bufferSize,
		       int stno,    // starting symbol no.
		       int estno,   // starting function no
		       int freedom);// number of freedom

  int  numberOfItems;
  ptrList <StrStrPair *> ssPairPtrLst;

  // permanent buffer
  char outputBuf[TERMCONVERT_EXPRESSION_BUFLEN];
  int  outputBufptr;

  // writing buffer
  char ibuf[BUFSIZ];  // identifier buffer
  char nbuf[BUFSIZ];  // number buffer for convertExpressionStringDBL()
  int  ibufptr;
  int  nbufptr;
 
  int  buflen;

  // control for 
  int  startingSblNo;    // initial value is 1

  int  elementTypes;
  list <Element *> elementPtrLst;   // comparison is class allocated address
  list <int>       elementStnoLst;

  // Reverse TermConvert
  list <Variable *>varPtrLst;       // for making reverseTC;
  
  list <string>convertedStrLst;     // converted string(actual terms list)
  list <string>usedUserFuncSymbolStrLst;

  list <string>ignoreConvertedStrLst;  // cancel converted string
                                       // This is for user function

  int smblNo;      // used for MetaPair group
  list <string>metaPairSblStrLst;

  int nxFlag ,nyFlag ,nzFlag ;            // for boundary
  int sblNoNX,sblNoNY,sblNoNZ;

};

#endif
