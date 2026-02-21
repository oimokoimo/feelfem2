/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : isEtypeName.cpp
 *  Date     : 2002/11/06
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

#include "string.hpp"
#include "feeldef.hpp"

int isEtypeName(string &name)
{
  if(name == ETYPE_POINT_NAME) return(YES);
  if(name == ETYPE_LINE_NAME ) return(YES);
  if(name == ETYPE_TRI_NAME  ) return(YES);
  if(name == ETYPE_RECT_NAME ) return(YES);
  if(name == ETYPE_TETRA_NAME) return(YES);
  if(name == ETYPE_CUBE_NAME ) return(YES);

  return(NO);
}


