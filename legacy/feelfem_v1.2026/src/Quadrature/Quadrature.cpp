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
  cerr << "Quadrature default constructor called...(feelfemtest may call)\n";

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

Quadrature::~Quadrature()
{
  name.~string();
  return;
}

    
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

void Quadrature::testSetName(char *str)
{
  name = str;
  return;
}

void Quadrature::testSetQuadraturePoints(int n)
{
  cerr << "Quadrature::testSetQuadraturePoints(int n)" << endl;

  SetDimensionAndPoints( 2,  n);
  return;
}
