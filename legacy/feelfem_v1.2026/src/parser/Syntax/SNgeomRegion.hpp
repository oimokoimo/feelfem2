/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomRegion.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : geomRegion class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_GEOMREGION
#define FEM_SYNTAX_GEOMREGION

#include "feeldef.hpp"
#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "string.hpp"


class SNgeomRegion : public SNunit {
public:
  SNgeomRegion( SNidentifierlist *ptr) : SNunit("geomRegion",SN_GEOMREGION){
    identifierLst = ptr;
    return;
  }

  void print(ostream & ost) {
    ost << "geomRegion ";
    identifierLst->print(ost);
  }

  virtual int Check();
  virtual int InfoGenerate();

private:
  SNidentifierlist *identifierLst;

};

#endif

