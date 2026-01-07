/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmaterialVar_CHECK.cpp
 *  Date     : 2002/08/23
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNmaterialVar.hpp"
#include "Expression.hpp"
#include "ginac_funcs.hpp"

#include "SNoption.hpp"

#include "GeometryObject.hpp"
#include "feelfuncs.hpp"

#include "../../check/check_funcs.hpp"


int SNmaterialVar::CheckPairs(void)
{
  int errors = 0;

  pairs  = optionLst.getNumberOfElements();
  if(pairs == 0) {
    SystemErrorStrA(this,name," has no value.");
    errors++;
    return(errors);
  }
  values = new double[pairs];

  int counter = 0;

  list <string> duplicateCheckStrLst;  // for materials defined here


  listIterator <SNoption *>itrOpt(optionLst);
  for(itrOpt.init(); !itrOpt ; ++itrOpt ) {
    
    char exprbuf[MAX_EXPRPRINT_BUF];
    exprbuf[0] = '\0';

    Expression *exprPtr = itrOpt()->GetExprPtr();
    string      matname = itrOpt()->GetOptionName();

    // duplication check  material m(a=10,a=20);  etc.
    if(duplicateCheckStrLst.includes(matname)) {
      SystemErrorStrA(this,matname," has multiple entries.");
      errors++;
    }
    else {
      duplicateCheckStrLst.addlast(matname);
    }
    
    if(exprPtr->howManyIdentifiers()           != 0 ||
       exprPtr->howManyNotIntrinsicFunctions() != 0    ) {
      
      SystemErrorAStrA(this,"Value for ",matname," is not numeric.");
      errors++;
      continue;
    }

    exprPtr->exprPrint(exprbuf,EXPRPRINT_NORMAL,0,0);

    setExprGinacEvaluate( exprbuf );

    if(!isExprGinacNumeric()) {   // ginac told it is not numeric

      string name = itrOpt()->GetOptionName();
      
      SystemErrorAStrA(this,"Specified value for ",name," is not numeric."); 

      errors++;
      continue;
    }

    *(values+counter) = getDoubleExprGinac();
    counter++;
  }

  return(errors);
}


int SNmaterialVar::CheckRegions(void)
{
  int errors = 0;


  list <string> duplicateCheckRegionStrLst;  // for region check

  listIterator <SNoption *>itrOpt(optionLst);
  for(itrOpt.init(); !itrOpt ; ++itrOpt ) {

    list <string>     associateRegionStrLst;
    string  matname = itrOpt()->GetOptionName();


    feelfemgeomobj.StoreAssociateMaterialRegionStrLst( matname,
						       associateRegionStrLst);
    
    listIterator<string>itr(associateRegionStrLst);

    //    cerr << "material var " << name << " for " << matname << " [";
    //    for(itr.init(); !itr; ++itr) {
    //      cerr << " " << itr();
    //    }
    //    cerr << " ]" << endl;

    for(itr.init(); !itr ; ++itr) {
      string rname = itr();
      if(duplicateCheckRegionStrLst.includes( rname ) ) {
	SystemErrorAStrA(this,"region ",rname," has multiple entries for this material var.");
	errors++;
      }
      else {
	duplicateCheckRegionStrLst.addlast(rname);
      }
    }
    
    associateRegionStrLst.deleteAllValues();
  }
  return(errors);
}
