/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Mesher.hpp
 *  Date     : 2002/03/24
 *  Modified : 
 *  
 *  Purpose  : Basic class for mesh generator
 *  
 */

#ifndef FEM_CLASS_MESHER
#define FEM_CLASS_MESHER

class Mesher {
public:
  Mesher();
  ~Mesher();

protected:
  int mesher_code;
};

#endif
