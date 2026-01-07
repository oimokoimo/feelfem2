/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : quadrature_check_eval.cpp 
 *  Date     : 2001/12/12   (copy of mesh_check_eval.cpp)
 *  Modified : 
 *  
 *  Purpose  : quadrature value evaluation
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
#include "../parser/Syntax/SNquadrature.hpp"
#include "../parser/Syntax/SNquadratureDoubleVar.hpp"
#include "../parser/Syntax/SNquadratureAssignment.hpp"


int quadrature_check_eval( SNquadrature *snqPtr )
{

  s


  quadratureEvalGinac evaluator;

  int errorFlag,ret;

  errorFlag = 0;

  listIterator <SNunit *>itr(dbl
  
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

      



	//	SystemErrorName(((SNunit *)itrMesh())," is already defined.");
	//	break;
	//      }
	//      ((SNmeshDoubleVar *)itrMesh())->add_strlist(duplicate_check);
	//      break;





/*    case SN_DIMENSION:
      case SN_EDGE:
      case SN_PEDGE:
      case SN_REGION:
      case SN_DOMAIN:
      case SN_VERTICES:
      case SN_MESHASSIGNMENT:

      break;

    default:
      abortExit("check_mesh_vars.cpp unknown SN_MESH code");
*/

  
