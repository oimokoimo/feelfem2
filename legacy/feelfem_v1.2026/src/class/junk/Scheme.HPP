/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Scheme.hpp
 *  Date     : 2000/04/25
 *  Modified : 2000/04/25
 *  
 *  Purpose  : Scheme Condition class
 *  
 */

#ifndef FEM_CLASS_Scheme
#define FEM_CLASS_Scheme

class Scheme {

public:
  Scheme();
  Scheme(void *,int);
  ~Scheme();

  
private:
  int schemeType;
  void *ptr;

};

#endif

