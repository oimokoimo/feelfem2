/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNwrite_InfoGenerate.cpp
 *  Date     : 2002/11/22  (copy from SNif_InfoGenerate.cpp)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>
#include <assert.h>

#include "SNstring.hpp"
#include "SNexpr.hpp"

#include "SNwrite.hpp"
#include "Write.hpp"

int SNwrite::InfoGenerate(void)
{
  writePtr = new Write();

  listIterator <SNunit *>itr(writeSNunitPtrLst);

  for(itr.init(); !itr ; ++itr) {
    switch(itr()->GetType()) {
    case SN_STRING:
      {
	SNstring *snStrPtr = (SNstring *)itr();
	string str = snStrPtr->GetString();
	writePtr->AddLastItem(str);
	writePtr->AddLastItemType( SN_STRING );
      }
      break;

    case SN_EXPR:
      {
	SNexpr *snExprPtr = (SNexpr *)itr();
	Expression *exprPtr = snExprPtr->GetExpr();
	
	char buf[MAX_EXPRPRINT_BUF];
	buf[0] = '\0';
	exprPtr->exprPrint(buf,EXPRPRINT_NORMAL,0,0);

	exprPtr->MakeVariablePtr(writePtr->varPtrLst);

	writePtr->AddLastItem(buf);
	writePtr->AddLastItemType( SN_EXPR );
      }
      break;

    default:
      assert(1==0);
    }
  }
  return(0);
}
