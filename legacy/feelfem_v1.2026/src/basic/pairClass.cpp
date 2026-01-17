/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : pairClass.cpp
 *  Date     : 2001/10/26
 *  Modified : 
 *  
 *  Purpose  : pair class for list
 *  
 */

#include <iostream.h>

#include "pairClass.hpp"

StrIntPair::StrIntPair( const char *strData, int dat)
{
  name = strData;
  code = dat;
  
  return;
}

StrIntPair::~StrIntPair( )
{
  name.~string();
  return;
}


int operator ==(const StrIntPair &siPair, const char *dat)
{
  string right;
  right = dat;

  return( siPair.name == dat ) ;
}

// Only string component is checked.
int operator ==(const StrIntPair &left, const StrIntPair &right )
{
  return( right.name == left.name);
}



// String String Pair  

StrStrPair::StrStrPair(const char *pgName, const char *libName)
{ 
  first  = pgName;
  second = libName;

  return;
}

StrStrPair::StrStrPair(const char *pre)
{ 
  first  = pre;

  return;
}

StrStrPair::~StrStrPair()
{
  first.~string();
  second.~string();
  return;
}

void StrStrPair::print(ostream &ost)
{
  ost << first << " " << second;
  return;
}


// This function is used in ptrLst::includes function.
// in pairList classed, first item must be uniq
int operator ==(const StrStrPair &left, const StrStrPair &right )
{

  // in StrStrPair, both element must be the same
  return( right.first == left.first && right.second == left.second ) ;
}



// String String Integer Pair  
StrStrIntPair::StrStrIntPair(const char *pgName, const char *libName, int c)
{ 
  first  = pgName;
  second = libName;
  code   = c;

  return;
}

StrStrIntPair::~StrStrIntPair()
{
  first.~string();
  second.~string();
}


// for used at ptrList.includes()   only string components are checked
int operator ==(const StrStrIntPair &left, const StrStrIntPair &right )
{
  // in StrStrPair, both element must be the same
  return( right.first == left.first && right.second == left.second ) ;
}

