/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PointObject.hpp
 *  Date     : 2002/03/14
 *  Modified : 
 *  
 *  Purpose  : Point
 *  
 */

#ifndef FEM_CLASS_POINTOBJECT
#define FEM_CLASS_POINTOBJECT

#include "string.hpp"
#include "GeomObj.hpp"

class Point;

class PointObject : public GeomObj {
public:
  PointObject(char *nm); 
  PointObject(Point *);

  ~PointObject();
  
  char *GetName() {
    return(name);
  }

private:
  int    no  ;    // used in generated program

  static int pointNo;

  Point *pPtr;    // if Geometry is defined inside

};
#endif
