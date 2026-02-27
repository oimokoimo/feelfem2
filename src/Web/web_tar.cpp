/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : web_tar.cpp
 *  Date     : 2002/08/23
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

#include <cassert>

#include <cstdlib>  // system()

#include <iostream>

#include "feelfuncs.hpp"
#include "Object.hpp"

void web_tar(void)
{
  char buf[BUFSIZ];
  listIterator <string>itr( feelfemobj.GetFileObjectStrList() );


  sprintf(buf,"tar cvf feelfem_src.tar %c",'\0');

  for(itr.init(); !itr ; ++itr) {
    string fname = itr();
    int length = stringLength(buf);
    int add    = stringLength( (const char *)fname);
    assert(length+add+2 < BUFSIZ);

    sprintf(buf+length," %s%c",(const char *)fname,'\0');
  }

  int length = stringLength(buf);
  assert(length+20< BUFSIZ);
  sprintf(buf+length," usr.pde >/dev/null%c",'\0');

  system(buf);
  system("gzip feelfem_src.tar");


  for(itr.init(); !itr ; ++itr) {
    string fname = itr();

    sprintf(buf,"rm %s%c",(const char *)fname,'\0');
    system(buf);
  }

  listIterator<string>itr2(feelfemobj.GetTmpFileObjectStrList() );
  for(itr2.init(); !itr2; ++itr2) {
    string fname = itr2();
    
    sprintf(buf,"rm %s%c",(const char *)fname,'\0');
    system(buf);
  }



  return;
}
