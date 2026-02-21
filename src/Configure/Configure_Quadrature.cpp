/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure_Quadrature.cpp
 *  Date     : 2002/02/08
 *  Modified : 
 *  
 *  Purpose  :
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
#include <iostream>

#include "feelfuncs.hpp"
#include "Configure.hpp"
#include "Object.hpp"
#include "Quadrature.hpp"

#include "string.hpp"

Quadrature *Configure::GetDefaultQuadraturePtrByEtype( int etype )
{
  string name;
  switch(etype) {
  case ELEMENT_TYPE_POINT:
	  std::cerr << "Configure::GetDefaultQuadraturePtrByEtype for POINT is called.\n";
    assert(1==0);
    
  case ELEMENT_TYPE_LINE:
    name = DEFAULT_QUADRATURE_LINE;

  case ELEMENT_TYPE_TRI:
    name = DEFAULT_QUADRATURE_TRI;
    break;
    
  case ELEMENT_TYPE_RECT:
    name = DEFAULT_QUADRATURE_RECT;
    break; 

  case ELEMENT_TYPE_TETRA:
    name = DEFAULT_QUADRATURE_TETRA;
    break;

  case ELEMENT_TYPE_CUBE:
    name = DEFAULT_QUADRATURE_CUBE;
    break;
    
  default:
    std::cerr << "Illegal etype code at GetDefaultQuadraturePtrByEtype." << std::endl;
    assert(1==0);
  }

  if(feelfemobj.IsDefinedQuadratureName( name ) == NO) {
	  std::cerr << "Default quadrature for etype " << etype <<" is "<<
      name << ", but not defined." << std::endl;

    assert(1==0);
  }

  Quadrature *qPtr;
  qPtr = feelfemobj.GetQuadraturePtrByName( name );
  
  return(qPtr);
}


int Configure::GetBoundaryEtypeFromEtype(int etype)
{
  switch(etype) {
  case ELEMENT_TYPE_POINT:
    assert(1==0);
    return(ELEMENT_TYPE_POINT);

  case ELEMENT_TYPE_LINE:
    return(ELEMENT_TYPE_POINT);

  case ELEMENT_TYPE_TRI:
    return(ELEMENT_TYPE_LINE);

  case ELEMENT_TYPE_RECT:
    return(ELEMENT_TYPE_LINE);

  case ELEMENT_TYPE_TETRA:
    return(ELEMENT_TYPE_TRI);
    
  case ELEMENT_TYPE_CUBE:
    return(ELEMENT_TYPE_RECT);

  default:
    assert(1==0);
  }
  assert(1==0);
  return(0);
}

Quadrature *Configure::GetDefaultBoundaryQuadFromRegionEtype(int etype)
{
  string      name;  

  switch(etype) {

  case ELEMENT_TYPE_POINT:
    assert(1==0);
    break;

  case ELEMENT_TYPE_LINE:      // bad for 1d problem
    assert(1==0);
    break;
    
  case ELEMENT_TYPE_TRI:
    name = DEFAULT_BOUNDARY_QUADRATURE_TRI;
    break;
    
  case ELEMENT_TYPE_RECT: 
    name = DEFAULT_BOUNDARY_QUADRATURE_RECT;
    break;

  case ELEMENT_TYPE_TETRA: 
    name = DEFAULT_BOUNDARY_QUADRATURE_TETRA;
    break;

  case ELEMENT_TYPE_CUBE: 
    name = DEFAULT_BOUNDARY_QUADRATURE_CUBE;
    break;

  default:
    assert(1==0);
  }
  
  if(feelfemobj.IsDefinedQuadratureName( name ) == NO) {
	  std::cerr << "Default boundary quadrature for etype " << etype <<" is "<<
      name << ", but not defined." << std::endl;

    assert(1==0);
  }

  Quadrature *qPtr;
  qPtr = feelfemobj.GetQuadraturePtrByName( name );
  
  return(qPtr);
}
