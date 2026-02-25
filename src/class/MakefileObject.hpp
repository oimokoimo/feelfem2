/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MakefileObject.hpp
 *  Date     : 2000/11/21
 *  Modified : 2000/11/21
 *  
 *  Purpose  : makefile object
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


#include <cstdio>
#include "feeldef.hpp"
#include "string.hpp"
#include "orderedPtrList.hpp"

#ifndef FEM_MAKEFILEOBJECT_CLASS
#define FEM_MAKEFILEOBJECT_CLASS

class MakefileObject {
  
public:
  MakefileObject();
  MakefileObject(const char *, int);
  ~MakefileObject();

  // for orderedPtrList <MakefileObject *> objPtrLst  comparison
  friend int operator <  (const MakefileObject &, const MakefileObject &);  // no const
  friend int operator == (const MakefileObject &, const MakefileObject &);

  int getLanguageType(void);  // return language type
  int getMakeFlag(void);      // return makeFlag

  int getObjectNameLength(void);
  void putFPObjectName(FILE *);

  const char *getObjectName(void);



private:
  string sourceName;
  string objectName;

  int  getLanguageType( const char *);
  void convertObj( string & , int );

  int    language;
  int    makeFlag;

};

std::ostream & operator << ( std::ostream &, MakefileObject &);

#endif
