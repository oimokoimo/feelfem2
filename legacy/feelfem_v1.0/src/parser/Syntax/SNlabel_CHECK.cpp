/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNlabel_CHECK.cpp
 *  Date     : 2002/07/18
 *  Modified : 
 *  
 *  Purpose  : duplicate check
 *  
 */

#include "list.hpp"
#include "string.hpp"

#include "SNlabel.hpp"

#include "../../check/check_funcs.hpp"

int SNlabel::duplicate_check(list <string>&strLst)
{
  if(strLst.includes(val)) {
    SystemErrorAStrA(this,"Label ",val," is multiply defined.");
    return(1);
  }
  
  strLst.add(val);

  return(0);
}
