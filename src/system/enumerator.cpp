/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : enumerator.cpp
 *  Date     : 2001/03/09
 *  Modified : 
 *  
 *  Purpose  : Supply unique number
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
static int PointNo  = 0;
static int EdgeNo   = 0;
static int RegionNo = 0;

int getNextPointNo(void)
{
  PointNo++;
  return(PointNo);
}

int getNextEdgeNo(void)
{
  EdgeNo++;
  return(EdgeNo);
}

int getNextRegionNo(void)
{
  RegionNo++;
  return(RegionNo);
}

