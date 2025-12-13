/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : FunctionObject.cpp
 *  Date     : 2002/09/12
 *  Modified :
 *  
 *  Purpose  : user function object
 *  
 */

#include <iostream.h>

#include "feeldef.hpp"

#include "Object.hpp"
#include "Function.hpp"

void Object::StoreUserFunction(Function *ptr)
{
  numberOfUserFunctions++;
  userFunctionPtrLst.addlast(ptr);
  return;
}

int Object::IsUsedUserFunctionName( string &name )
{
  listIterator <Function *>itr(userFunctionPtrLst);
  for(itr.init();!itr;++itr) {

    if(itr()->isNameIs( name )) return(YES);
  }
  return(NO);
}

Function * Object::GetFunctionPtrByName( string &name ) 
{
  listIterator <Function *>itr(userFunctionPtrLst);
  for(itr.init();!itr;++itr) {

    if(itr()->isNameIs( name )) return( itr() );
  }

  cerr << "FUNCTION NAME Not stored " << name << endl;
  assert(1==0);
  return(0);
}


int Object::GetUserFunctionTCno(int args)
{
  switch(args) {
  case 1:
    arg1Functions++;
    return(GUFTCN2(arg1Functions,args));

  case 2:
    arg2Functions++;
    return(GUFTCN2(arg2Functions,args));

  case 3:
    arg3Functions++;
    return(GUFTCN2(arg3Functions,args));

  default:
    cerr << "User function must has 1 to 3 argument(s)." << endl;
  }
  return(0);
}

int Object::GUFTCN2(int funcs,int args)
{
  if(funcs < 10) {
    return(funcs+10*args);
  }

  // now user function for each arguments (1,2,3) only 5
  assert(1==0);

  return(0);
}
