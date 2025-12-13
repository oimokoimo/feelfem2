/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure_Makefile.cpp
 *  Date     : 2003/01/16
 *  Modified : 
 *  
 *  Purpose  : 
 *  
 */

#include "feeldef.hpp"

#include "list.hpp"
#include "string.hpp"
#include "Configure.hpp"

void Configure::UseSolverLibrary( int n)
{
  if(solverLibraryNumeroLst.includes(n)) return;
  solverLibraryNumeroLst.addlast(n);
  return;
}


void Configure::StoreLIBSinMakefile( char *libName)
{
  LIBSinMakefileLst.addlast( libName );
  return;
}

void Configure::WriteLIBSinMakefile(FILE *fp) 
{
  listIterator <int>itrNo(solverLibraryNumeroLst);
  for(itrNo.init(); !itrNo ; ++itrNo) {
    switch(itrNo()) {
      
    case TYPE_FEELFEM90SMPIMUMPSCA:
      LIBSinMakefileLst.addlast( LIB_FOR_FEELFEM90SMPIMUMPSCA );
      break;
      

    default:
      assert(1==0);
    }
  }


  listIterator <string>itr(LIBSinMakefileLst);
  for(itr.init(); !itr ; ++itr) {
    fprintf(fp,"%s",(char *)itr());
  }
  return;
}

