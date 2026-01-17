/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNidentifierlist.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : Syntax identifierlist class (mostly for debugging use)
 *
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

#ifndef FEM_SYNTAX_IDENTIFIERLIST
#define FEM_SYNTAX_IDENTIFIERLIST

#include "SNunit.hpp"
#include "SNname.hpp"


class SNidentifierlist : public SNunit {
public:

  SNidentifierlist(int);
  ~SNidentifierlist();

  SNname *&operator[] (int i) { return contents[i]; }

  void print(std::ostream&);

  void StoreContentsInStringLst(list<string > &);

  int  GetNumberOfElements() { return elements; }
  

private:
  int      elements;
  SNname **contents;


};

#endif
