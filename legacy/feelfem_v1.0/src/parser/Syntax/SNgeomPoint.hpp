/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomPoint.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : geomPoint class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_GEOMPOINT
#define FEM_SYNTAX_GEOMPOINT

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "string.hpp"


class SNgeomPoint : public SNunit {
public:
  SNgeomPoint( SNidentifierlist *ptr) : SNunit("geomPoint",SN_GEOMPOINT) {
    identifierLst = ptr;
    return;
  }

  void print(ostream & ost) {
    ost << "geomPoint ";
    identifierLst->print(ost);
  }

  virtual int Check(void);
  virtual int InfoGenerate();

private:
  SNidentifierlist *identifierLst;
};

#endif
