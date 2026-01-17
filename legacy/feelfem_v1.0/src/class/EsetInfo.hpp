/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EsetInfo.hpp
 *  Date     : 2002/03/01
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CLASS_ESETINFO
#define FEM_CLASS_ESETINFO

#include "list.hpp"
#include "string.hpp"

class EsetInfo {

public:
  EsetInfo();
  ~EsetInfo();
  
  int HasDependency(void);
  list <string>&GetArgStrList();

private:
  int dependencyFlag;
  list <string> argStrLst;
};

#endif
