/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNvarlist.hpp
 *  Date     : 2001/02/21
 *  Modified : 
 *  
 *  Purpose  : Syntax varlist class (mostly for debugging use)
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#ifndef FEM_SYNTAX_VARLIST
#define FEM_SYNTAX_VARLIST

#include "SNunit.hpp"


class SNvarlist : public SNunit {
public:

  SNvarlist(int);
  ~SNvarlist();

  SNunit *&operator[] (int i) { return contents[i]; }

  void print(std::ostream&);
  

private:
  int      elements;
  SNunit **contents;


};

#endif
