/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : pairClass.hpp
 *  Date     : 2001/09/17
 *  Modified : 
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Notes:
 *   - Parser and language spec are carried over from feelfem 1.0.
 *   - Back-end and build system are updated for modern C++ toolchains.
 *
 *  
 *  Purpose  : various pair class
 *  
 */

#ifndef FEM_CLASS_PAIRCLASS
#define FEM_CLASS_PAIRCLASS

#include <iostream>

#include "string.hpp"

class IntIntPair {
public:
  IntIntPair( int , int );
  ~IntIntPair(void)=default; 

  friend int operator ==(const IntIntPair &, const IntIntPair &);


private:
  int first;
  int second;
};


class StrIntPair {
public:
  StrIntPair(const char *, int);
  ~StrIntPair(void);

  int getCode(void) { return code; }
  void setName(string &setStr ) { setStr = name;  return; }

  // This comparison is only for the string component
  friend int operator == (const StrIntPair &, const char *);

  // THIS COMPARISON IS FOR ptrList (comparison is only for the string compo.)
  friend int operator == (const StrIntPair &, const StrIntPair &);  
  
  
private:
  string name;
  int    code;
};


class StrStrPair {
public:

  StrStrPair(const char *,const char *);   // constructor
  StrStrPair(const char *);

  ~StrStrPair(void);                       // destructor

  int IsMatchFirstComponent( string &str) {
    return( str == first );
  }

  int IsMatchSecondComponent( string &str) {
    return( str == second );
  }

  void SetSecond( const char *str) {
    second = str;
    return;
  }

  void SetArgStringWithFirst( string &argStr ) {
    argStr = first;
    return;
  }

  void SetArgStringWithSecond( string &argStr ) {
    argStr = second;
    return;
  }

  string &GetFirst(void) {
    return first;
  }
  string &GetSecond(void) {
    return second;
  }

  // If both are the same,,,,,
  friend int operator == (const StrStrPair &, const StrStrPair &);  // ptrList

  void print(std::ostream &ost);

private:
  string first;
  string second;
};


class StrStrIntPair {
public:

  StrStrIntPair(const char *,const char *, int);   // constructor
  ~StrStrIntPair(void);                       // destructor

  int GetCode(void) { return code; }

  // for ptrList.includes  (only string components are tested)
  friend int operator == (const StrStrIntPair &, const StrStrIntPair &);  

private:
  string first;
  string second;
  int    code;

};

#endif
