/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Label.hpp
 *  Date     : 2002/07/18
 *  Modified : 
 *  
 *  Purpose  : Label
 *  
 */

#ifndef FEM_LABEL_CLASS
#define FEM_LABEL_CLASS

#include "string.hpp"

class ostream;

class SNlabel;

class Label {
public:
  Label(const char *);
  ~Label();

  int GetLabelNo();
  
private:
  static int labels;
  string name;
  int    labelNo;
};

#endif
