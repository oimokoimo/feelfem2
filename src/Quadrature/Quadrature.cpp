/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Quadrature.cpp
 *  Date     : 1999/12/15
 *  Modified : 1999/12/15
 *  
 *  Purpose  : Quadrature Function
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
#include "feelfuncs.hpp"    // stringLength
#include "Quadrature.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNquadrature.hpp"
#include "../parser/Syntax/SNquadratureDoubleVar.hpp"
#include "../parser/Syntax/SNquadratureAssignment.hpp"
#include "../parser/Syntax/SNquadratureGaussP.hpp"

//Quadrature::Quadrature(SNquadrature *snqPtr)
//{
//  name             = snqPtr->name;
//  elementEtype     = snqPtr->etype;
//  quadraturePoints = snqPtr->gaussPoints;
//
//  return;
//}

Quadrature::Quadrature()
{
	std::cerr << "Quadrature default constructor called...(feelfemtest may call)\n";

  return;
}

Quadrature::Quadrature(string &nm,int etype,int dim,int pts)
{
  name             = nm;
  dimension        = dim;
  elementEtype     = etype;

  SetDimensionAndPoints( dimension, pts );  // including allocation

  return;
}

Quadrature::~Quadrature() = default;

    
//int Quadrature::GetQuadraturePoints(void)
//{
//  return(quadraturePoints);
//}


const char *Quadrature::GetName(void)
{
  return(name);
}


//  Test...
//  testSetName(char *),testSetQuadraturePoints(int)

void Quadrature::testSetName(const char *str)
{
  name = str;
  return;
}

void Quadrature::testSetQuadraturePoints(int n)
{
	std::cerr << "Quadrature::testSetQuadraturePoints(int n)" << std::endl;

  SetDimensionAndPoints( 2,  n);
  return;
}
