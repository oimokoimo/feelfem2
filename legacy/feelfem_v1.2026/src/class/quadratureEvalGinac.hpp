/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : quadratureEvalGinac.hpp  (Copy of meshEvalGinac.hpp)
 *  Date     : 2001/12/12
 *  Modified : 
 *  
 *  Purpose  : quadrature evaluation class  (final result is number)
 *  
 *             Different from meshEvalGinac, quadratureEvalGinac is 
 *             called from
 *  
 */
#ifndef FEM_CLASS_QUADRATUREVALGINAC
#define FEM_CLASS_QUADRATUREVALGINAC

#include "ptrList.hpp"             // pointer list
#include "string.hpp"
#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNquadratureDoubleVar.hpp"
#include "../parser/Syntax/SNquadratureAssignment.hpp"
#include "../parser/Syntax/SNquadrature.hpp"

class quadratureEvalGinac {
public:
  quadratureEvalGinac();
  ~quadratureEvalGinac();

  int quadratureDoubleVar(SNquadratureDoubleVar *); 
                                                /*  return 0 no error
					          1 duplication declaration err
						  2 value cannot be evaluated 
                                                 */
  int quadratureAssignment(SNquadratureAssignment *);

  int quadratureGaussP(SNquadratureGaussP *);

  int isAllAssingedEvalPairList(list <string> &);
  evalPair *getEvalPairByString(string &);
  

private:
  ptrList <evalPair *> evalList;
};

#endif
