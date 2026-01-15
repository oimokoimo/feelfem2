/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfuncs.hpp
 *  Date     : 1999/10/27
 *  Modified : 1999/10/27
 *  Modified : 2001/01/31 strindex declaration
 *  
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Purpose: extern function definitions
 *
 *  Notes:
 *   - Parser and language spec are carried over from feelfem 1.0.
 *   - Back-end and build system are updated for modern C++ toolchains.
 *
 *
 *  Purpose  : General function prototype declarations
 *  
 */

#ifndef FEM_FEELFUNCS
#define FEM_FEELFUNCS

#include <iostream>

char *getdate(void);   // system/getdate.cpp(1999/10/27)
int   streq(const char *,const char *);
void  dbgGeneratorReport( char *, char *);  // 2000/03/24
int   getSpaceDimension(void);              // 2000/10/20
int   stringLength(const char *);           // 2000/12/26 strlen
int   strindex(const char *,const char *);  // 2001/01/31 strindex
void  abortExit(int);                       // 2000/12/26 abort function
void  abortExit(char *);                    // 2001/01/31 with message

FILE *fileOpenToWrite(const char *);

// External informations
class Object;
class Geometry;
class Configure;
class Procedure;
class GeometryObject;

extern Object    feelfemobj;      // FEM parts information
extern Procedure feelfemproc;     // used in Main constructor
extern Configure feelfemconf;     // mostly relating feelfem-languages
extern Geometry  feelfemgeom;     // geometry information
extern GeometryObject feelfemgeomobj; // geometry object

// Error message functions
void storeSourceFileName( const char *);          // check/SystemErrorFilename.cpp
int  currentSourceFileNo( void  );
void wrtErrSourceFilename(std::ostream &os,int line);

// Enumerator functions
int getNextPointNo(void);                   // 
int getNextEdgeNo(void);
int getNextRegionNo(void);



// Ginac related functions
template <class T> class ptrList;
class evalPair;

//#include "ptrList.hpp"
//#include "evalPair.hpp"  // name change 010326


double evaluateBufGinac(char *,ptrList<evalPair *>*,int &);


#endif

