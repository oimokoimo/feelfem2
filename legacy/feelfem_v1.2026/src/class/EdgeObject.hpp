/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EdgeObject.hpp
 *  Date     : 2002/03/14
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CLASS_EDGEOBJECT
#define FEM_CLASS_EDGEOBJECT

#include "feeldef.hpp"
#include "string.hpp"

#include "GeomObj.hpp"
class Edge;

class EdgeObject : public GeomObj {

public:  
  EdgeObject(char *);
  EdgeObject(Edge *);

  ~EdgeObject();

  char *GetName() {
    return(name);
  }
    
private:
  static int edgeNo;
  int no;

  Edge *edgePtr;
};

#endif
