/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : element_check.cpp
 *  Date     : 2001/03/27
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <iostream.h>

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNelement.hpp"
#include "../parser/Syntax/SNelementDoubleVar.hpp"
#include "../parser/Syntax/SNelementAssignment.hpp"
#include "../parser/Syntax/SNelementIntp.hpp"

#include "check_funcs.hpp"

int element_check(list <void *>&parseElementLst)
{
  int errors;
  //  int i;  i = 0;

  errors = 0;

  listIterator <void *>itr(parseElementLst);
  for(itr.init(); !itr ; ++itr) {
    int ret;
    SNelement *snePtr = (SNelement*)itr();
    //    cerr << "CHECK ELEMENT No." << i << endl;
    //    snePtr->print(cerr);
    //    cerr << "================="  << endl;

    // set etype
    ret = snePtr->setEtype();
    if(ret != 0) {
      SystemErrorANameA(snePtr,"Element definition ",", illegal shape name.");
      errors++;
      continue;    // skip another process
    }


    // Check consistency of node dimension
    ret = snePtr->CheckNodeDimension();
    if(ret != 0) {
      errors++;
      continue;    // skip another process
    }

    // variable definition check.
    // x1,x2,x3 etc. are inside, etc.
    // nx,ny,nz,
    ret = snePtr->CheckSystemVariables(); //error message generated inside
    if(ret != 0) {
      errors++;
    }

    ret = snePtr->EvalExpressions();    // error message generated inside
    if(ret != 0) {
      errors++;
    }

    snePtr->ParseInterpolates();

    // duplicate check   ??? what does it means???
    //    cerr << "Underconstruct : duplicate check(element_check.cpp)\n";
    
    // symmetry check
    //    cerr << "Underconstruct : symmetry check(element_check.cpp)\n";

    // here, node check....





    // check INTERP_TYPE, and set INTERP_TYPE at each SNelementIntp class
    if(snePtr->CheckInterpType() != 0) {
      errors++;
    }

    // set interpolates
    if(snePtr->GetNumberOfInterpolates() == 0) {
      SystemErrorNameA(snePtr," has no definition of a basis function.");
      errors++;
    }    
    
    // count nodes
    if(snePtr->GetNumberOfNodes() == 0) {
      SystemErrorANameA(snePtr,"Element "," has no nodes.");
      //      errors++;
      cerr << "THIS IS CAUSED NOT MADE ROUTINES FOR INTEPOLATEPARSE\n";
      // be careful errors is comment out.
    }    
      
  }  // iter for SNelement Ptr

  return(errors);
}
