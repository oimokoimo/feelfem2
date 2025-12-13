/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EwiseQuadEcalInfo.cpp
 *  Date     : 2002/07/29
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <iostream.h>
#include <assert.h>

#include "EwiseQuadEcalInfo.hpp"
#include "EwiseQuadTC.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

EwiseQuadEcalInfo::EwiseQuadEcalInfo(void)
{
  letNo = 0;

  useX = 0;
  useY = 0;
  useZ = 0;

  useXval = 0;
  useYval = 0;
  useZval = 0;

  quadraturePtr     = 0;
  parametricElemPtr = 0;

  return;
}

EwiseQuadEcalInfo::~EwiseQuadEcalInfo()
{

}

void EwiseQuadEcalInfo::SetConvertedUserFuncStrList(EwiseQuadTC &tc)
{
  tc.GetConvertedUserFuncStrInReverseList( usedUserFuncStrLst );
  return;
}

void EwiseQuadEcalInfo::SetConvertedIdentifierList(EwiseQuadTC &tc)
{
  tc.GetConvertedIdentifierInReverseList( identifierLst );
  return;
}

void EwiseQuadEcalInfo::AddVariablePtr(Variable *ptr)
{
  varPtrLst.add(ptr);
  return;
}

void EwiseQuadEcalInfo::SetParametricElementPtr(Element *pePtr)
{
  parametricElemPtr = pePtr;

  assert(parametricElemPtr != 0);
  return;
}

void EwiseQuadEcalInfo::InfoGenerate(void)
{
  // Make element list
  int first_diff_flag = NO;

  // Add parametric element ptr
  AddUniqElementPtrList(parametricElemPtr);    

  listIterator <Variable *>itrV(varPtrLst);
  
  listIterator <string>itr(identifierLst);
  for(itr.init();!itr;++itr) {

    string name = itr();
    
    if(name=="qx") { useX = YES; useXval = YES; continue; }
    if(name=="qy") { useY = YES; useYval = YES; continue; }
    if(name=="qz") { useZ = YES; useZval = YES; continue; }

    //  fem variable
    //  qfem_NAME, qfem_NAME_x,qfem_NAME_y,qfem_NAME_z
    //
    //  ewise material
    //  ew_NAME_m
    //
    //  ewise quad (must be same quadrature)
    //  ew_NAME_q
    //
    //  ewise fem
    //  qew_NAME, qew_NAME_x,qew_NAME_y,qew_NAME_z
    //

    assert(name.length() >3);


    char namebuf[BUFSIZ];
    int  ipt,n; 

    // scalar variable
    //  scalar  (int,const,double)
    //  sc_NAME
    if(name[0] == 's' && name[1] =='c' && name[2] =='_') {
      ipt = 3;
      n = 0;
      while(name[ipt+n] != '\0' ) {
	namebuf[n] = name[ipt+n];
	n++;
      }
      namebuf[n] = '\0';      
      Variable *vPtr = feelfemobj.GetVariablePtrWithName(namebuf);
      
      VariableEvalPair *vepPtr = new VariableEvalPair( vPtr, TYPE_DIFF_ZERO);
      vPairLst.addlast( vepPtr );
      
      continue;
    }

    // material varaible 
    if(name[0] == 'm' && name[1] =='_') {
      ipt = 2;
      n = 0;
      while(name[ipt+n] != '\0' ) {
	namebuf[n] = name[ipt+n];
	n++;
      }
      namebuf[n] = '\0';      
      Variable *vPtr = feelfemobj.GetVariablePtrWithName(namebuf);
      
      VariableEvalPair *vepPtr = new VariableEvalPair( vPtr, TYPE_DIFF_ZERO);
      vPairLst.addlast( vepPtr );
      
      continue;
    } 
      
    //  ewise material
    //  ew_NAME_m
    //
    //  ewise quad (must be same quadrature)
    //  ew_NAME_q
    if(name[0] == 'e' && name[1] == 'w' && name[2] == '_') {
      ipt = 3;
      n = 0;
      
      int len = name.length();

      assert( name[len-2] == '_');
      assert( name[len-1] == 'm' || name[len-1] == 'q');

      len = len -2;
      while(ipt+n < len ) {
	namebuf[n] = name[ipt+n];
	n++;
      }
      namebuf[n] = '\0';      
      Variable *vPtr = feelfemobj.GetVariablePtrWithName(namebuf);
      
      VariableEvalPair *vepPtr = new VariableEvalPair( vPtr, TYPE_DIFF_ZERO);
      vPairLst.addlast( vepPtr );
      
      continue;
    }      


    if(name[1] == 'f') {
      ipt = 5;             // qfem_X
    }
    else if(name[1] == 'e') {
      ipt = 4;            //  qew_X
    }
    else {

      cerr << "NAME = " << name << endl;
      assert(20==0);      // vfem variable?
    }

    int len = name.length();
    if(  name[len-2] == '_') {
      if(name[len-1] == 'x' || 
	 name[len-1] == 'y' || 
	 name[len-1] == 'z'    ) {  // differential symbol
	// only 1st order differential                 EXPAND_DIFF1
	 
	len = len - 2;
      }
    }
    // 2nd order diff, will be here
	
    n = 0;
    while(ipt+n < len) {
      namebuf[n] = name[ipt+n];
      n++;
    }
    namebuf[n] = '\0';


    Variable *vPtr = feelfemobj.GetVariablePtrWithName(namebuf);
    Element  *ePtr = vPtr->GetElementPtr();

    
    if(name[ipt+n] == '\0') {
      AddUniqElementPtrList(ePtr);    // normal

      VariableEvalPair *vepPtr = new VariableEvalPair( vPtr, TYPE_DIFF_ZERO);
      vPairLst.addlast( vepPtr );
    }
    else if(name[ipt+n+1] == 'x') {
      AddUniqD1ElementPtrList(ePtr);  // dx

      VariableEvalPair *vepPtr = new VariableEvalPair( vPtr, TYPE_DIFF_X);
      vPairLst.addlast( vepPtr );
    }
    else if(name[ipt+n+1] == 'y') {
      AddUniqD1ElementPtrList(ePtr);  // dy

      VariableEvalPair *vepPtr = new VariableEvalPair( vPtr, TYPE_DIFF_Y);
      vPairLst.addlast( vepPtr );
    }
    else if(name[ipt+n+1] == 'z') {
      AddUniqD1ElementPtrList(ePtr);  // dz

      VariableEvalPair *vepPtr = new VariableEvalPair( vPtr, TYPE_DIFF_Z);
      vPairLst.addlast( vepPtr );
    }
    else {
      assert(30==0);
    }

  }

  // check for parametric element is used for Jacobian
  if(IsUseElementDerivative()) {
    AddUniqD1ElementPtrList(parametricElemPtr);// for coordinate transformation
  }    

  return;


}

void EwiseQuadEcalInfo::AddUniqElementPtrList(Element *ePtr)
{
  if(usedElementPtrLst.includes(ePtr)) return;
  usedElementPtrLst.add(ePtr);
  return;
}

void EwiseQuadEcalInfo::AddUniqD1ElementPtrList(Element *ePtr)
{
  if(usedD1ElementPtrLst.includes(ePtr)) return;
  usedD1ElementPtrLst.add(ePtr);
  return;
}

int EwiseQuadEcalInfo::IsUseElementDerivative(void)
{
  if(usedD1ElementPtrLst.getNumberOfElements() >0 ) {
    return(YES);
  }
  else {
    return(NO);
  }
}



