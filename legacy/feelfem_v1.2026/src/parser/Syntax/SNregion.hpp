/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNregion.hpp
 *  Date     : 2001/02/27
 *  Modified : 
 *  
 *  Purpose  : region class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_REGION
#define FEM_SYNTAX_REGION

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "../../class/string.hpp"
#include "../../class/list.hpp"

class PolygonalRegion;

class SNregion : public SNunit {
public:
  SNregion( char *nm, char *typ, int lists) 
    : name(nm),type(typ),SNunit("region",SN_REGION) {
    holes = lists -1 ;
    contents = new (SNunit *)[lists];
    for(int i=0;i<lists; i++) contents[i] = 0;

    return;
  }

  void print(ostream & ost) {
    ost << "region ";
    ost <<  name;
    ost << "[" << type << "]";
    for(int i=0;i<holes+1;i++) {
      contents[i]->print(ost);
    }
    return;
  }
  
  SNunit *&operator[] (int i) { return contents[i]; }

  void errWrtName(ostream &ost ) {
    ost << name;
    return;
  }

  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }
    
  // geometry
  PolygonalRegion *MakePolygonalRegionObj(void);
  

private:
  string  name;
  string  type;  /* line,tri,rect,tetra,....*/
  int     holes; /* number of holes */

  SNunit **contents;

};


#endif
