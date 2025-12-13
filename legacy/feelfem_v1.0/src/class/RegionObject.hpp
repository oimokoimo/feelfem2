/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : RegionObject.hpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  : Region
 *  
 */

#ifndef FEM_CLASS_REGIONOBJECT
#define FEM_CLASS_REGIONOBJECT

#include "string.hpp"
#include "GeomObj.hpp"
#include "list.hpp"

class PolygonalRegion;

class RegionObject  : public GeomObj {
public:
  RegionObject(char *nm);
  RegionObject(PolygonalRegion *);

  ~RegionObject();

  int   GetPropertyNo(void);

  void AddMaterialAttribute( string &);
  int  HasMaterialAttribute( string &);

  char *GetName() {
    return(name);
  }

private:
  int    no  ;    // used in generated program

  static int regionNo;

  PolygonalRegion *polygonalRegionPtr;

  list <string> materialAttributeStrLst;

};
#endif
