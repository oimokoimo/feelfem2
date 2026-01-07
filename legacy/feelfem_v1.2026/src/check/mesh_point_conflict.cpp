/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : mesh_point_conflict.cpp
 *  Date     : 2001/04/02
 *  Modified : 
 *  
 *  Purpose  : point coordinate conflict check
 *  
 */

#include <stream.h>

#include "ptrList.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "Point.hpp"            // Geometry class

#include "check_funcs.hpp"

#include "../parser/Syntax/SNpoint.hpp"

int mesh_point_conflict( list <void *>&parseMeshLst )
{
  listIterator <void *>itrMesh(parseMeshLst);
  int errors;

  SNpoint *snpPtr;
  Point   *pPtr;
  

  ptrList <Point *>  pointPtrLst;
  list    <string>   nameLst;

  
  errors    = 0;
  
  int pos;

  for(itrMesh.init(); !itrMesh; ++itrMesh) {

    switch(((SNunit *)itrMesh())->GetType()) {

    case SN_POINT:
      snpPtr = (SNpoint *)itrMesh();
      pPtr   = snpPtr->MakePointObj();   // refNo not set at this time

      pos = pointPtrLst.getPosition( pPtr );
      if(pos == 0) {
	pointPtrLst.addlast(pPtr);
	snpPtr->nameAddLastToStringLst( nameLst );
      }
      else {
	// error! 
	errors++;
	string tmp = nameLst.getNthElement(pos);
	SystemErrorANameAStr((SNunit*)itrMesh(),tmp,
			     "point "," is identical to ");
	tmp.~string();
			   
      }
      break;

    default:
      break;
    }
  }
  pointPtrLst.deleteAllValues();
  nameLst.deleteAllValues();
  
  return(errors);
}
