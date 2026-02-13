/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNedge.cpp
 *  Date     : 2001/04/04
 *  Modified : 
 *  
 *  Purpose  : Make Edge object
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

#include "../../class/feelfuncs.hpp"

#include "SNunit.hpp"
#include "SNedge.hpp"
#include "SNidentifierlist.hpp"
#include "SNname.hpp"

#include "../../class/Point.hpp"
#include "../../class/Edge.hpp"
#include "../../class/Geometry.hpp"

Edge *SNedge::MakeEdgeObj(void)
{
  Edge *egPtr = new Edge(name,TYPE_EDGE_NORMAL);
  list <string> strLst;

  ((SNidentifierlist *)identifierLst)->StoreContentsInStringLst( strLst );

  listIterator <string>itr(strLst);
  for(itr.init(); !itr; ++itr) {
    Point *pPtr;

    pPtr = feelfemgeom.GetPointPtrByName( itr() );
    if(pPtr == NULL) {
      // this situation must be checked in advance.
      abortExit("NULL POINTER in Edge *SNedge::MakeEdgeObj(void)");
    }
    
    egPtr->AddPointPtr(pPtr);
  }

  strLst.deleteAllValues();
  
  return(egPtr);
}
