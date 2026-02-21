/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : VariableObject.cpp
 *  Date     : 1999/11/29
 *  Modified : 2000/12/27   abortExit
 *  
 *  Purpose  : Object record for Variables
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

#include "feelfuncs.hpp"
#include "Object.hpp"

#include "Main.hpp"

int streq(const char*,const char *);

void Object::StoreVariable(Variable val)
{
  variables++;

  // main StoreVariable is (Variable *val) below! (2001/03/29)
  std::cerr << "===========================================\n";
  std::cerr << "THIS IS OLD StoreVariable(Variable val) for\n";
  std::cerr << "ReadCtrl77dat.cpp\n";
  std::cerr << "===========================================\n";
  if(varPtrLst.isEmpty()) {
    Variable *new_ptr = new Variable( val );
    varPtrLst.add(new_ptr);
    return;
  }

  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(streq(itr()->GetName(), val.GetName()) && 
       itr()->GetType() == val.GetType()) {
#ifdef DBG
	    std::cerr << "Variable " << val.GetName() << " already defined.\n";
#endif
      return;
    }
  }

  Variable *new_ptr = new Variable( val );
  varPtrLst.add(new_ptr);

  return;
}

void Object::StoreVariable(Variable *vPtr)
{
  variables++;

  varPtrLst.add(vPtr);

  return;
}

int Object::GetVariableTypeWithName(const char *name)
{
  Variable *vPtr = GetVariablePtrWithName( name );
  return(vPtr->GetType());
}

int Object::GetVariableTypeWithName( string &name )
{
  Variable *vPtr = GetVariablePtrWithName( (const char *)name );
  return(vPtr->GetType());
}

Variable * Object::GetVariablePtrWithNameType(const char *name, int type)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(name)  && itr()->GetType() == type) {
      Variable *ret = itr();
      return ret;
    }
  }
  
  std::cerr << "Cannot find variable name="<<name << "  type ="<<type <<"\n";
  abortExit("GetVariablePtrWithNameType");
  return 0;  // never comes here
} 


Variable * Object::GetVariablePtrWithName(const char *name)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(name)) {
      Variable *ret = itr();
    }
  }
  
  std::cerr << "Cannot find variable name="<<name << "\n";
  abortExit("GetVariablePtrWithName");
  return 0; // never fome tis
}



int Object::IsDefinedVariable( const char *name )
{
  listIterator <Variable *>itr(varPtrLst);
  
  for(itr.init(); !itr ; ++itr ) {
    if( itr()->isNameIs( name ) ) {
      return(YES);
    }
  }
  return(NO);
}


int Object::IsDefinedFEMVariable( const char *name )
{
  listIterator <Variable *>itr(varPtrLst);
  
  for(itr.init(); !itr ; ++itr ) {
    if( itr()->isNameIs( name ) ) {

      if(itr()->GetType() == VAR_FEM) {   // currently, VAR_VFEM is not
	return(YES);
      }
    }
  }
  return(NO);
}


int Object::IsDefinedEWISEVariable( const char *name )
{
  listIterator <Variable *>itr(varPtrLst);
  
  for(itr.init(); !itr ; ++itr ) {
    if( itr()->isNameIs( name ) ) {

      if(itr()->GetType() == VAR_EWISE   ||
	 itr()->GetType() == VAR_EWISE_A   ) {   // currently, VAR_VFEM is not
	return(YES);
      }
    }
  }

  return(NO);
}


int Object::IsDefinedMaterialVariable( const char *name )
{
  listIterator <Variable *>itr(varPtrLst);
  
  for(itr.init(); !itr ; ++itr ) {
    if( itr()->isNameIs( name ) ) {

      if(itr()->GetType() == VAR_MATERIAL  ) {  
	return(YES);
      }
    }
  }

  return(NO);
}


int Object::IsDefinedUnknownVariable( const char *name )
{
  listIterator <Variable *>itr(varPtrLst);
  
  if(IsDefinedFEMVariable( name ) == YES) {
    return(YES);
  }

  for(itr.init(); !itr ; ++itr ) {
    if( itr()->isNameIs( name ) ) {

      if( itr()->GetType()      == VAR_EWISE_A &&
	  itr()->GetEwiseType() == EWISE_TYPE_INTERPOLATION ) {
	return(YES);
      }
      else {
	return(NO);
      }
    }
  }
  return(NO);
}


int Object::IsDefinedScalarVariable( const char *name )
{
  listIterator <Variable *>itr(varPtrLst);
  
  for(itr.init(); !itr ; ++itr ) {
    if( itr()->isNameIs( name ) ) {

      if(itr()->GetType() == VAR_DOUBLE ||
	 itr()->GetType() == VAR_INT    || 
	 itr()->GetType() == VAR_CONST     ) {   // currently, VAR_VFEM is not
	return(YES);
      }
    }
  }
  return(NO);
}

void Object::MakeVarLstForMain( Main *mPtr)
{
  listIterator <Variable *>itr(varPtrLst);
  
  for(itr.init(); !itr ; ++itr ) {
    mPtr->AddVariablePtr( itr() );
  }

  return;
}

void Object::StoreInitialDouble(Variable *vPtr)
{
  if(!initialDblVarPtrLst.includes(vPtr)) {
    initialDblVarPtrLst.addlast(vPtr);
    initialDoubles++;
  }

  return;
}


void Object::StoreInitialInteger(Variable *vPtr)
{
  if(!initialIntVarPtrLst.includes(vPtr)) {
    initialIntVarPtrLst.addlast(vPtr);
    initialIntegers++;
  }

  return;
}

void Object::StoreMaterialVar(Variable *vPtr)
{
  if(!materialVarPtrLst.includes(vPtr)) {
    materialVarPtrLst.addlast(vPtr);
    numberOfMaterialVars++;
  }

  return;
}
