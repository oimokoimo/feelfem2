/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BGeom.hpp
 *  Date     : 2002/03/15
 *  Modified : 
 *  
 *  Purpose  : numerate condition object
 *  
 */

#ifndef FEM_CLASS_BGEOM
#define FEM_CLASS_BGEOM

#include "string.hpp"

#include "GeomObj.hpp"

class BGeom {
public:
  BGeom(int,GeomObj *);

  int GetCondType(void) {
    return(condType);
  }

  int GetBGeomNo(void) {
    return(bgeomNo);
  }
  
  char * GetName(void) {
    return(goPtr->GetName());
  }

  int    GetGeomType(void) {
    return(goPtr->GetType());
  }

  int IsNameIs( string &);

  int IsBothCondition(void);   // used GID  ( for .BAS file )

protected:
  GeomObj   *goPtr;
  int        bgeomNo ;
  int        condType;    //BGEOM_DIRICHLET or BGEOM_NEUMANN ...

private:
  static int bgeoms;

};

#endif
