/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Write.hpp
 *  Date     : 2002/11/22
 *  Modified : 
 *  
 *  Purpose  : write statement
 *  
 */

#ifndef FEM_WRITE_CLASS
#define FEM_WRITE_CLASS


#include "orderedPtrList.hpp"
#include "string.hpp"
#include "Variable.hpp"

class ostream;
class SNwrite;


class Write {
public:
  Write(void);   // label name and number
  ~Write();

  void AddLastItem(char *);
  void AddLastItemType( int );

  list <string>&GetItemStrList(void)   { return itemStrLst ;} 
  list <int>   &GetItemTypeList(void)  { return itemTypeLst;} 
  orderedPtrList <Variable *>&GetVarPtrList(void){ return varPtrLst;} 

  friend class SNwrite;

private:
  list <string>itemStrLst;
  list <int>   itemTypeLst;
  orderedPtrList <Variable *>varPtrLst;
  
};

#endif
