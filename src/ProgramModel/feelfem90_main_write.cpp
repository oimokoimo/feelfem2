/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2002/11/23
 *  Modified : 
 *  
 *  Purpose  :
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include "feeldef.hpp"

#include "PM_feelfem90.hpp"
#include "Write.hpp"
#include "TermConvert.hpp"
#include "Object.hpp"
#include "feelfuncs.hpp"
#include "Variable.hpp"

void PM_feelfem90::DoMainScheme_write(Main *mPtr, Write *wPtr)
{
  com();

  TermConvert tc;
  
  listIterator <Variable *>itrV(wPtr->GetVarPtrList());
  for(itrV.init(); !itrV; ++itrV) {
    char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
    char bto  [VARIABLE_TERMCONVERT_BUFSIZ];

    switch(itrV()->GetType()) {
    case VAR_INT:
    case VAR_DOUBLE:
    case VAR_CONST:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"sc_%s%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    default:
      assert(1==0);
    }
  }


  pushSource("write(*,*) ");
  
  listIterator <string>itrStr(wPtr->GetItemStrList());
  listIterator <int>   itrType(wPtr->GetItemTypeList());

  itrType.init();

  int start = 0;
  for(itrStr.init(); !itrStr ; ++itrStr ) {

    switch(itrType()) {
    case SN_STRING:
      if(start == 0) {
	start = 1;
      }
      else {
	pushSource(",");
      }
      pushSource("'");
      pushSource( itrStr() );
      pushSource("'");

      break;

    case SN_EXPR:

      if(start == 0) {
	start = 1;
      }
      else {
	pushSource(",");
      }
      {
	string exprF90Str = tc.convertExpressionString(itrStr());
	pushSourceHAT( exprF90Str );
      }

      break;

    default:
      assert(1==0);
    }

    ++itrType;
  }
  flushSource();
  com();
}
