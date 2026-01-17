//
// General string class
//
// From Classic Data Structures in C++
// by   Timothy A. Budd
//
// File:     stringMemberfunc.cpp
// Date:     1999/08/13
// Modified:
//
// Programmed (almost just typed (^^; ) by Hidehiro FUJIO
//
#include "string.hpp"

unsigned int string::length() const
{
  return( CstringLength(buffer) );
}


istream & string::getline(istream & in)
{
   in.getline( buffer, bufferlength );
   return in;
}


int string::contain(const char *text) const
{
   int strindex(const char *, const char *);
   return(strindex( buffer , text));
}

void string::lower(void)
{
  char *cp;
  cp = buffer;

  while(*cp) {
    if(*cp >= 'A' && *cp <= 'Z') {
      *cp = *cp -'A' + 'a';
    }
    cp++;
  }
  return;
}
