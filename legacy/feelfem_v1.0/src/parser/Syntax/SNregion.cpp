/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNregion.cpp
 *  Date     : 2001/04/04
 *  Modified : 
 *  
 *  Purpose  : Make Region object
 *  
 */

#include "../../class/feelfuncs.hpp"

#include "SNunit.hpp"
#include "SNregion.hpp"
#include "SNidentifierlist.hpp"
#include "SNname.hpp"

#include "../../class/Polygon.hpp"
#include "../../class/Edge.hpp"
#include "../../class/PolygonalRegion.hpp"
#include "../../class/Geometry.hpp"

PolygonalRegion *SNregion::MakePolygonalRegionObj(void)
{
  PolygonalRegion  *prPtr;
  Polygon          *polygonPtr;
  SNidentifierlist *sniLstPtr;

  int err;

  list <string> strLst;

  sniLstPtr = (SNidentifierlist *)contents[0];
  sniLstPtr->StoreContentsInStringLst( strLst );


  // Make outer Polygon
  listIterator <string>itr(strLst);
  polygonPtr = new Polygon(TYPE_POLYGON_NORMAL,name);

  err = polygonPtr->AddObjectByStrLst(strLst);
  if(err) {
    abortExit("In SNregion.cpp/making outer Polygon, AddObjectByStrLst err");
  }
  prPtr = new PolygonalRegion(name,polygonPtr);

  for(int i=0;i<holes;i++) {
    strLst.deleteAllValues();
    sniLstPtr = (SNidentifierlist *)contents[i+1];
    sniLstPtr->StoreContentsInStringLst( strLst );

    polygonPtr = new Polygon(TYPE_POLYGON_HOLE,name);
    err = polygonPtr->AddObjectByStrLst(strLst);
    if(err) {
      abortExit("In SNregion.cpp/making hole Polygon, AddObjectByStrLst err");
    } 
    err = prPtr->AddHolePolygonPtr(polygonPtr);
    if(err) {
      abortExit("In SNregion.cpp/add hole PolygonPtr error(may be intersect)");
    }
  }
  strLst.deleteAllValues();  
  return(prPtr);
}
