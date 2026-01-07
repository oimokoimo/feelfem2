//
// General string class
//
// From Classic Data Structures in C++
// by   Timothy A. Budd
//
// File:     stringCheck.cpp 
// Date:     1999/08/12
// Modified:
// Purpose:  mostly debug purposes 
//
// Programmed (almost just typed (^^; ) by Hidehiro FUJIO
//

#include <iostream.h>
#include <assert.h>
#include "string.hpp"

void string::checkLength( int length )
{
  assert(length >= 0);

  if(length > maxBufferLength) {
    maxBufferLength = length;
  }
  totalObjects++;
  totalAssignedBufferLength += length;

  return;
}


void string::checkReport( void )
{
  cout << "total objects = " << totalObjects << '\n';
  cout << "total memory  = " << totalAssignedBufferLength << '\n';
 
  return;
}

