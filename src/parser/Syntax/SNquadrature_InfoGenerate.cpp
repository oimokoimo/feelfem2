/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadrature_InfoGenerate.cpp
 *  Date     : 2001/12/10
 *  Modified : 
 *  
 *  Purpose  : Generate Quadrature class from SN information
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
#include "feeldef.hpp"
#include "list.hpp"

#include "SNquadrature.hpp"
#include "SNquadratureGaussP.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

int SNquadrature::InfoGenerate(void)    // int for virtual definition
{

  int errors;

  // allocate Quadrature
  quadPtr = new Quadrature(name,etype,dimension,gaussPoints);

  /*--*/

  listIterator <SNquadratureGaussP *> itr(gaussPPtrLst);


  int counter;
  
  counter = 0;
   
  for(itr.init();!itr; ++itr) {
    double xx,yy,zz,weight;
    switch(dimension) {
    case 1:
      itr()->getCoordinate(xx);
      quadPtr->SetIthCoordinate( counter, xx );
      break;

    case 2:
      itr()->getCoordinate(xx,yy);
      quadPtr->SetIthCoordinate( counter, xx ,yy);
      break;
      
    case 3:
      itr()->getCoordinate(xx,yy,zz);
      quadPtr->SetIthCoordinate( counter, xx ,yy , zz);
      break;

    default:
      assert(1==0);
    }

    weight = itr()->getWeight();
    quadPtr->SetIthWeight( counter, weight);

    counter++;
  }

  feelfemobj.StoreQuadrature( quadPtr );

  return(0);   // This is int function because of virtual declaration

};
