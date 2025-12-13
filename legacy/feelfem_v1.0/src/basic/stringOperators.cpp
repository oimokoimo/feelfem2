//
// General string class
//
// From Classic Data Structures in C++
// by   Timothy A. Budd
//
// File:     stringOperators.cpp
// Date:     1999/08/13
// Modified:
// Purpose:  string operator overloads
//
// Programmed (almost just typed (^^; ) by Hidehiro FUJIO
//
#include <assert.h>
#include "string.hpp"

int operator <(const string &left, const string &right)
{
  char *l = left.buffer;
  char *r = right.buffer;

  while(*l) {
    if(*l != *r) {
      return(*l < *r);
    }
    l++; r++;
  }
  return(*l < *r);
}


int operator ==(const string &left, const string &right)
{
  char *l = left.buffer;
  char *r = right.buffer;

  while(*l) {
    if(*l != *r) {
      return(0);
    }
    l++; r++;
  }
  return(*l == *r);
}


void string::operator = ( const string & right )
{
  const int rightLength = right.length();

  if(rightLength >= bufferlength) {
    delete [] buffer;

    bufferlength = 1 + rightLength;
    checkLength(bufferlength);
  
    buffer = new char[bufferlength];
    assert( buffer != 0);
  }

  int i;
  for(i=0; right.buffer[i] != '\0' ; i++) {
    buffer[i] = right.buffer[i];
  }
  buffer[i] = '\0';

  return;
}

static char nothing;
char & string::operator [] ( unsigned int index) const
{
  if( index >= CstringLength(buffer)) {
    nothing = '\0';
    return nothing;
  }
  
  return buffer[index];
}


// conversion operator

string::operator const char * () const
{
   return buffer;
}

string::operator char * () 
{
   return buffer;
}

// != operator for string and const char *

int operator !=(const string &left, const char *right)
{
  if(CstringLength(left) != CstringLength(right)) {
    return(1);
  }

  for(int i=0;i<CstringLength(right);i++) {
    if(left[i] != *(right+i)) {
      return(1);
    }
  }

  return(0);
}


int operator ==(const string &left, const char *right)
{
  if(CstringLength(left) != CstringLength(right)) {
    return(0);
  }

  for(int i=0;i<CstringLength(right);i++) {
    if(left[i] != *(right+i)) {
      return(0);
    }
  }

  return(1);
}
