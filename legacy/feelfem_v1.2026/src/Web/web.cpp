/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : web.cpp
 *  Date     : 2002/08/23
 *  Modified : 
 *  
 *  Purpose  : post process for web
 *  
 */

#include "Object.hpp"
#include "feelfuncs.hpp"
#include "feelfem.hpp"

void web_tar();

void web(void)
{

  if(feelfem_web == YES) {

    web_tar();

    printf("web:NORMAL\n");
  }

  return;
}
