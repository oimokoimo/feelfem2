/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : discretizeAssignment
 *  Date     : 2002/07/24
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>

#include "feelfuncs.hpp"

#include "list.hpp"
#include "parseExternals.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNassignment.hpp"

#include "Assign.hpp"

void EwiseQuadAssign(Assign *);  // in FiniteElement directory

void discretizeAssignment(SNassignment *snasPtr)
{
  Assign *asPtr = snasPtr->GetAssignPtr();

  
  switch(asPtr->GetLeftVarAssignType()) {

  case  AS_VAR_TYPE_SCALAR:      // 1 // scalar, 
    //  case  AS_VAR_TYPE_INTEGER   1 // scalar, integer (Not use integer info)
    //  case  AS_VAR_TYPE_DOUBLE    1 // scalar, double  (Not use double  info)
  case  AS_VAR_TYPE_EWISE_M:     // 3     // ewise,  material
  case  AS_VAR_TYPE_EWISE_I:     // 5     // ewise,  integerpolation
  case  AS_VAR_TYPE_FEM_NODE:    // 6     // fem,    node based 
  case  AS_VAR_TYPE_FEM_HELMITE: // 7     // fem,    helmite
  case  AS_VAR_TYPE_VFEM_V:      // 8     // vfem,   variant
  case  AS_VAR_TYPE_VFEM_CV:     // 9     // vfem,   contravariant
    //  case  AS_VAR_TYPE_DOUBLE_BINTEGRAL 11
    //  case  AS_VAR_TYPE_DOUBLE_MAX       12
    //  case  AS_VAR_TYPE_DOUBLE_MIN       13
    //  case AS_VAR_TYPE_EWISE_G:
    break;

  case  AS_VAR_TYPE_EWISE_G:         // 4  ewise,  gauss point
    asPtr->EwiseQuadDiscretize();    // in Assign
    break;

  case  AS_VAR_TYPE_DOUBLE_INTEGRAL:
    asPtr->EwiseQuadDiscretize();    // in Assign
    break;

  defaulat:
    assert(1==0);
    // no necessity
    break;
  }


  return;
}
