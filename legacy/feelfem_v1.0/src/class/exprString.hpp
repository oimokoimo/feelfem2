/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : exprString.hpp
 *  Date     : 2001/08/16
 *  Modified : 
 *  
 *  Purpose  : mathematical expression stored as a string
 *             
 *             with term convert functionalities
 *             
 */

#ifndef FEM_CLASS_EXPRSTRING
#define FEM_CLASS_EXPRSTRING

#include "string.hpp"

class exprString : public string {

public:
  exprString();
  ~exprString();


private:
  string expr;

};


#endif
