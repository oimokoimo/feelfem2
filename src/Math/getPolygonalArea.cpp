/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Uwe Jaekel
 *
 *  Filename : getPolygonalArea.cpp
 *  Date     : 2001/04/23
 *  Modified : 
 *  
 *  Purpose  : calculate polygonal area
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

double getPolygonalArea(double x[], double y[], int n) {
  double startX, startY, endX, endY, area;

  area = 0.0;
  
  for(int i = 0; i < n; i++) {
    // starting point is x[i], y[i]
    startX = x[i];
    startY = y[i];
    // if i < n-1,
    if(i < n-1) {
      // end point will be x[i+1], y[i+1]
      endX = x[i+1];
      endY = y[i+1];
    } else {
      // end point is first point of closed polygon
      endX = x[0];
      endY = y[0];
    }
    // add -\int y dx
    area -= 0.5*(startY + endY)*(endX - startX);
    // add \int x dy
    area += 0.5*(startX + endX)*(endY - startY);
  }
  return 0.5*area;
}
