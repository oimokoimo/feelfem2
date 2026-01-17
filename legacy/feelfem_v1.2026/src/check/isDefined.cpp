/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : isDefined.cpp
 *  Date     : 2002/01/21
 *  Modified : 2002/03/27 (add normal vector symbol, nx,ny,nz)
 *  
 *  Purpose  : isDefined check family.  Access to feelfemobj is
 *             limited within this function.
 *  
 */
#include "Object.hpp"
#include "feelfuncs.hpp"   // Object.GetSpaceDimension()
#include "check_funcs.hpp"

int isCoordinate( const char *nm )
{
  int dim;

  dim = feelfemobj.GetSpaceDimension();

  if(*(nm+1) != '\0') {
    return(NO);             // coordinate must be only one letter
  }

  if(*nm == 'x'           ) return(YES);
  if(*nm == 'y' && dim > 1) return(YES);
  if(*nm == 'z' && dim > 2) return(YES);

  return(NO);
}

int isCoordinate( string &nm )
{
  int dim;

  dim = feelfemobj.GetSpaceDimension();

  if(nm[1] != '\0') {
    return(NO);             // coordinate must be only one letter
  }

  if(nm[0] == 'x'           ) return(YES);
  if(nm[0] == 'y' && dim > 1) return(YES);
  if(nm[0] == 'z' && dim > 2) return(YES);

  return(NO);
}

int isCoordinateX( string &nm )
{
  int dim;

  dim = feelfemobj.GetSpaceDimension();

  if(nm[1] != '\0') {
    return(NO);             // coordinate must be only one letter
  }

  if(nm[0] == 'x'           ) return(YES);
  return(NO);
}

int isCoordinateY( string &nm )
{
  int dim;

  dim = feelfemobj.GetSpaceDimension();

  if(nm[1] != '\0') {
    return(NO);             // coordinate must be only one letter
  }

  if(nm[0] == 'y' && dim > 1 ) return(YES);
  return(NO);
}

int isCoordinateZ( string &nm )
{
  int dim;

  dim = feelfemobj.GetSpaceDimension();

  if(nm[1] != '\0') {
    return(NO);             // coordinate must be only one letter
  }

  if(nm[0] == 'z' && dim > 2 ) return(YES);
  return(NO);
}

// normals
int isNormalComponent( string &nm)
{
  return( isSystemNX(nm) || isSystemNY(nm) || isSystemNZ(nm));
}

int isSystemNX( string &nm )
{
  if(nm[2] != '\0' ) {
    return(NO);             // nx is two letters
  }
  if(nm[0] != 'n')            return(NO);
  if(nm[1] == 'x'           ) return(YES);
  return(NO);
}

int isSystemNY( string &nm )
{
  int dim;

  dim = feelfemobj.GetSpaceDimension();

  if(nm[2] != '\0') {
    return(NO);             // normals are two letters
  }

  if(nm[0] != 'n' ) return(NO);
  if(nm[1] == 'y' && dim > 1 ) return(YES);
  return(NO);
}

int isSystemNZ( string &nm )
{
  int dim;

  dim = feelfemobj.GetSpaceDimension();

  if(nm[2] != '\0') {
    return(NO);             // normals are two letters
  }

  if(nm[0] != 'n') return(NO);
  if(nm[1] == 'z' && dim > 2 ) return(YES);
  return(NO);
}

// variables
int isDefinedVariable(string &name )
{
  int ret;
 
  ret = feelfemobj.IsDefinedVariable( name );
  
  return(ret);
}

int isDefinedFEMVariable( string &name )
{
  int ret;
  
  ret = feelfemobj.IsDefinedFEMVariable( name );
  
  return(ret);
}

int isDefinedEWISEVariable(string &name )
{
  int ret;
  
  ret = feelfemobj.IsDefinedEWISEVariable (name);
  
  return(ret);
}

int isDefinedScalarVariable(string &name )
{
  int ret;
  
  ret = feelfemobj.IsDefinedScalarVariable (name);
  
  return(ret);

}

int isDefinedMaterialVariable(string &name)
{
  int ret;
  
  ret = feelfemobj.IsDefinedMaterialVariable (name );
  
  return(ret);
}

