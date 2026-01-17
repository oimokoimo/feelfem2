/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Function.hpp    
 *  Date     : 2002/09/12
 *  Modified : 
 *  
 *  Purpose  : User defined function
 *  
 *             Function.cpp is in Math/ directory
 */

#ifndef FEM_CLASS_FUNCTION
#define FEM_CLASS_FUNCTION

#include "string.hpp"

class Function {
public:
  Function(char *nm,int);
  ~Function();

  int isNameIs( const char *nm) {
    return(name == nm);
  }
  const char *GetName() {
    return(name);
  }
  int GetArguments(void) { return arguments; }
  int GetFunctionTCno();

private:
  string name;
  int    arguments;
  int    tcno;           // term convert no, set at the constructor by Object
};

#endif
