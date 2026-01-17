/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNoutput_InfoGenerate.cpp
 *  Date     : 2002/04/23 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>

#include "SNoutput.hpp"
#include "SNoption.hpp"
#include "Output.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

#include "../../check/check_funcs.hpp"

int SNoutput::InfoGenerate(void)
{
  outputPtr = new Output();

  feelfemobj.StoreOutput(outputPtr);

  components = snIdentifierlistPtr->GetNumberOfElements();
  for(int i=0;i<components;i++) {
    SNname *snnPtr;

    snnPtr     = (*snIdentifierlistPtr)[i];
    string str = snnPtr->GetName();

    outputPtr->AddIdentifier(str);

    if(isCoordinate( str )) continue;
    
    if(isDefinedFEMVariable(str)) {
      Variable *vPtr;
      vPtr = feelfemobj.GetVariablePtrWithName( str );
      outputPtr->AddVariablePtr(vPtr);
      continue;
    }

    if(isDefinedEWISEVariable(str)) {
      Variable *eVarPtr;
      eVarPtr = feelfemobj.GetVariablePtrWithName( str );
      outputPtr->AddVariablePtr(eVarPtr);

      Quadrature *qPtr = eVarPtr->GetQuadraturePtr();
      outputPtr->SetQuadraturePtr(qPtr);
      continue;
    }

    if(isDefinedScalarVariable(str)) {
      Variable *vPtr;
      vPtr = feelfemobj.GetVariablePtrWithName( str );
      outputPtr->AddVariablePtr(vPtr);
      continue;
    }

    // VFEM is not supported now.
    assert(1==0);
  }


  // add options
  
  listIterator <SNoption *>itrOpt(optionLst);
  for(itrOpt.init(); !itrOpt ; ++itrOpt) {
    string key = itrOpt()->GetOptionName();
    string val;
    itrOpt()->GetValueAsString(val);
    outputPtr->AddOption( key, val);
  }
  return(0);
}
