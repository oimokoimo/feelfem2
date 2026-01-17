/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomEdge_check.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNgeomEdge.hpp"
#include "SNidentifierlist.hpp"
#include "SNname.hpp"

#include "../../check/check_funcs.hpp"

#include "Configure.hpp"
#include "GeometryObject.hpp"
#include "feelfuncs.hpp"
#include "string.hpp"

int SNgeomEdge::Check()
{
  int errors;

  errors = 0;

  for(int i=0;i<identifierLst->GetNumberOfElements(); i++) {
    string nm = (*identifierLst)[i]->GetName();

    int ret;
    ret = feelfemgeomobj.IsUsedName( nm );
    
    if(ret == YES) {
      SystemErrorStrA((SNunit *)this,nm," is used already.");
      errors++;
    }
    else {
      feelfemgeomobj.AddUsedNameLst( nm );
    }
  }

  return(errors);
}
