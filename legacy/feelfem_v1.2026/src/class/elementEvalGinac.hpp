/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : elementEvalGinac.hpp  (Copy of quadratureEvalGinac.hpp)
 *  Date     : 2001/12/29
 *  Modified : 
 *  
 *  Purpose  : element evaluation class
 *  
 *             Different from meshEvalGinac, elementEvalGinac is 
 *             called from EvalExpressions()...
 *  
 */
#ifndef FEM_CLASS_ELEMENTEVALGINAC
#define FEM_CLASS_ELEMENTEVALGINAC

#include "ptrList.hpp"             // pointer list
#include "string.hpp"
#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNelementDoubleVar.hpp"
#include "../parser/Syntax/SNelementAssignment.hpp"
#include "../parser/Syntax/SNelementIntp.hpp"
#include "../parser/Syntax/SNelement.hpp"

class elementEvalGinac {
public:
  elementEvalGinac();
  ~elementEvalGinac();

  void vertexDefaults(int);

  int evalInterpolationNode( SNelementIntp *);

  int elementDoubleVar(SNelementDoubleVar *); 
                                                /*  return 0 no error
					          1 duplication declaration err
						  2 value cannot be evaluated 
                                                 */
  int elementAssignment(SNelementAssignment *);

  int elementIntp(SNelementIntp *);

  int isAllAssingedEvalPairList(list <string> &);
  evalPair *getEvalPairByString(string &);
  

private:
  ptrList <evalPair *> evalList;
};

#endif
