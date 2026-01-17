/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SurfaceObject.hpp
 *  Date     : 2002/03/14
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CLASS_SURFACEOBJECT
#define FEM_CLASS_SURFACEOBJECT

#include "feeldef.hpp"
#include "GeomObj.hpp"
#include "string.hpp"

class SurfaceObject : public GeomObj {

public:
  SurfaceObject(char *nm);
  // SurfaceObject(Surface *);   // no

  ~SurfaceObject();

  char *GetName() {
    return(name);
  }

private:
  static int surfaceNo;
  int no;

  // Surface *surfPtr;
};

#endif
