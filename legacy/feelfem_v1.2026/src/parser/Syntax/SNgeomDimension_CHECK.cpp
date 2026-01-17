/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomDimension_Check.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "../../check/check_funcs.hpp"
#include "Object.hpp"

#include "SNunit.hpp"
#include "SNgeomDimension.hpp"

int SNgeomDimension::Check()
{
  if(dim < 2 || dim >3) {
    SystemErrorA((SNunit *)this,"Dimension error.");
    return(1); // error
  }

  int currentDimension = feelfemobj.GetSpaceDimension();
  
  feelfemobj.SetSpaceDimension( dim );
  return(0);   // no error
}

