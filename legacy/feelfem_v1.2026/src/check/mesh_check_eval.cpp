/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : check_mesh_eval.cpp
 *  Date     : 2001/03/08
 *  Modified : 2001/03/09
 *  
 *  Purpose  : mesh variable check and confirm evaluation is correct
 *  
 */

#include <stream.h>

#include "list.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "check_funcs.hpp"

// ginac
#include "meshEvalGinac.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNpoint.hpp"
#include "../parser/Syntax/SNmeshDoubleVar.hpp"


int mesh_check_eval( list <void *>&parseMeshLst )
{
  listIterator <void *>itrMesh(parseMeshLst);

  meshEvalGinac evaluator;

  int errorFlag,ret;

  errorFlag = 0;
  
  for(itrMesh.init(); !itrMesh; ++itrMesh) {

    switch(((SNunit *)itrMesh())->GetType()) {

    case SN_MESHDOUBLEVAR:
      ret = evaluator.meshDoubleVar( (SNmeshDoubleVar *)itrMesh() );
      errorFlag += ret;
      break;

    case SN_MESHASSIGNMENT:
      ret = evaluator.meshAssignment( (SNmeshAssignment *)itrMesh());
      if(ret) {
	SystemErrorANameA(((SNunit *)itrMesh()),"Assignment of ",
			  " cannot be evaluated.");
      }
      errorFlag += ret;
      break;

    case SN_POINT:
      ret = evaluator.meshPoint( (SNpoint *)itrMesh());
      if(ret) {
	SystemErrorANameA(((SNunit *)itrMesh()),
			  "Calculation of coordinate of point ",
			  " cannot be evaluated.");
      }
      errorFlag += ret;
      break;

    default:
      break;
    }
  }

  return(errorFlag);
}
