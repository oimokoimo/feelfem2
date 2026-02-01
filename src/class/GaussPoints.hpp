/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GaussPoints
 *  Date     : 2002/01/03   (formerly, inside Quadrature.hpp)
 *  Modified : 
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
 *
 *
 *  Purpose  :
 *  
 */
#ifndef FEM_CLASS_GAUSSPOINTS
#define FEM_CLASS_GAUSSPOINTS

class GaussPoints {
public:
  GaussPoints();
  ~GaussPoints();
  
  int  GetQuadraturePoints(void);

  void SetDimensionAndPoints(int dim,int pts);    // and allocation

  void SetIthWeight(int,double);

  void SetIthCoordinate(int,double);
  void SetIthCoordinate(int,double,double);
  void SetIthCoordinate(int,double,double,double);

  double GetIthWeight(int);

  int GetDimension(void);

  double GetIthXi(int);
  double GetIthEta(int);
  double GetIthZeta(int);
  
private:                     // GaussPoints class
  int dimension;
  int points;

  double *x;
  double *y;
  double *z;

  double *w;   // weight
};

#endif
