/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementIntp_InfoGenerate.cpp
 *  Date     : 2002/03/04
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

#include "Interpolation.hpp"
#include "SNelementIntp.hpp"

Interpolation *SNelementIntp::GenerateInterpolationDat()
{
  Interpolation *iPtr;

  iPtr = new Interpolation();
  
  iPtr->SetType( type );

  char buf[MAX_EXPRPRINT_BUF];
  buf[0] = '\0';
  
  exprPtr->exprPrint(buf,EXPRPRINT_NORMAL ,0,0);
  iPtr->SetExprStr(buf);
  iPtr->SetNodePtr( generateNodeClass() );

  return(iPtr);
}
