/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : var_material_region_check.cpp
 *  Date     : 2002/09/03
 *  Modified : 
 *  
 *  Purpose  : all region must be assigned a material
 *  
 */

#include <stdio.h>

#include "feeldef.hpp"
#include "feelfem.hpp"
#include "feelfuncs.hpp"
#include "Object.hpp"
#include "GeometryObject.hpp"
#include "Variable.hpp"
#include "RegionObject.hpp"

int var_material_region_check(void)
{
  int errors = 0;

  if(feelfemobj.HowManyMaterialVars() == 0 ) return(0);

  listIterator <Variable *>itrMatV(feelfemobj.GetMaterialVarList());
  listIterator <RegionObject *> itrReg(feelfemgeomobj.GetRegionObjectPtrList());

  // check all region definitions
  for(itrReg.init(); !itrReg; ++itrReg) {

    RegionObject *roPtr = itrReg();

    // check all material variables
    for(itrMatV.init(); !itrMatV; ++itrMatV ) {
      
      if(itrMatV()->HasDefinedForThisRegionPtr(roPtr) ) {
	continue;
      }
      else {
	errors++;

	if(feelfem_web) {
	  fprintf(stdout,"Error: Region %s has no associate material type for var %s\n",
		  roPtr->GetName(),
		  itrMatV()->GetName());
	}
	else {

	  fprintf(stderr,"Error: Region %s has no associate material type for var %s\n",
		  roPtr->GetName(),
		  itrMatV()->GetName());
	}
      }
    }
  }
  return(errors);
}



    
