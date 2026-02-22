/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Variable_Material.cpp
 *  Date     : 2002/09/03
 *  Modified : 
 *  
 *  Purpose  : Material related Variable class routines
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

#include <cassert>
#include "Variable.hpp"

#include "feelfuncs.hpp"
#include "GeometryObject.hpp"
#include "RegionObject.hpp"

void Variable::SetMaterialKinds(int n)
{
  assert(n>0);

  pairs          = 0;
  materialValues = new double[n];

  assert(materialValues != 0);

  return;
}

void Variable::SetMaterialValuePair(string &nm, double val)
{
  assert(pairs == materialStrLst.getNumberOfElements());

  *(materialValues + pairs) = val;
  materialStrLst.addlast( nm );

  pairs++;
  
  return;
}

double Variable::GetMaterialValueByName( const char *nm )
{
  string sname = nm;
  int n = materialStrLst.getPosition( sname );
  assert(n>0 && n <= pairs);
  
  return( *(materialValues + (n-1) ) );
}

double Variable::GetMaterialValueByRegionName(string &regName)
{
  assert(varType == VAR_MATERIAL);

  listIterator <string> itr(materialStrLst);

  RegionObject *roPtr = feelfemgeomobj.GetRegionObjectPtrByName(regName);

  int ctr = 0;

  for(itr.init(); !itr ;++itr) {
    string nm = itr();

    if(roPtr->HasMaterialAttribute(nm)) {
      return(*(materialValues + ctr ) );
    }
    
    ctr++;
  }
  assert(1==0);
  return(1.0);
}

void Variable::GetMaterialNameByRegionName(string &regName,string &matName)
{
  assert(varType == VAR_MATERIAL);

  listIterator <string> itr(materialStrLst);

  RegionObject *roPtr = feelfemgeomobj.GetRegionObjectPtrByName(regName);

  int ctr = 0;

  for(itr.init(); !itr ;++itr) {
    string nm = itr();
    if(roPtr->HasMaterialAttribute( nm )) {
      matName = itr();
      return;
    }
    
    ctr++;
  }
  assert(1==0);
  return;

}


// This is CHECK function
int Variable::HasDefinedForThisRegionPtr(RegionObject *roPtr)
{
  assert(varType == VAR_MATERIAL);

  listIterator <string> itr(materialStrLst);

  for(itr.init(); !itr ;++itr) {
    string nm = itr();

    if(roPtr->HasMaterialAttribute(nm)) {
      return(1);
    }
  }
  return(0);     // error, no material is assigned for this material var for roPtr
}
