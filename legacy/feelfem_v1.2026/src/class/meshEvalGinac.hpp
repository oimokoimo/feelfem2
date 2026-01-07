/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : meshEvalGinac.hpp
 *  Date     : 2001/03/14
 *  Modified : 
 *  
 *  Purpose  : mesh evaluation class
 *  
 */
#ifndef FEM_CLASS_MESHEVALGINAC
#define FEM_CLASS_MESHEVALGINAC

#include "ptrList.hpp"             // pointer list
#include "string.hpp"
#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNpoint.hpp"
#include "../parser/Syntax/SNmeshDoubleVar.hpp"
#include "../parser/Syntax/SNmeshAssignment.hpp"


class meshEvalGinac {
public:
  meshEvalGinac();
  ~meshEvalGinac();

  int meshDoubleVar(SNmeshDoubleVar *); /* return 0 no error
					          1 duplication declaration err
						  2 value cannot be evaluated 
					   */
  int meshAssignment(SNmeshAssignment *);
  int meshPoint(SNpoint *);

  int isAllAssingedEvalPairList(list <string> &);
  evalPair *getEvalPairByString(string &);
  
  friend class SNpedge;    // to access evalList while evaluate 

private:
  ptrList <evalPair *> evalList;
};

#endif
