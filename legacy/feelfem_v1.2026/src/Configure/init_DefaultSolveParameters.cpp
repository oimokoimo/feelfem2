/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : init_DefaultSolveParameters.cpp
 *  Date     : 2002/03/07
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "Configure.hpp"
#include "feeldef.hpp"

void Configure::init_DefaultSolveParameters()
{
  /*=============================================*/
  /* Store default solver for each program model */
  /*=============================================*/
  StoreDefaultPM_LIB( NAME_PM_FEELP2,         NAME_LIB_SKYLINE);
  StoreDefaultPM_LIB( NAME_PM_FEELP2DRAMA,    NAME_LIB_PCG    );
  StoreDefaultPM_LIB( NAME_PM_FEELFEM90,      NAME_LIB_PCG    );
  StoreDefaultPM_LIB( NAME_PM_FEELFEM90DRAMA, NAME_LIB_AMG    );

  return;
}
