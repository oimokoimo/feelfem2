//
// General string class
//
// From Classic Data Structures in C++
// by   Timothy A. Budd
//
// File:     streamOperator.cpp
// Date:     1999/08/13
// Modified:
// Purpose:  Stream I/O operator for string class
//
// Programmed (almost just typed (^^; ) by Hidehiro FUJIO
//

#include <iostream.h>
#include "string.hpp"

ostream & operator<< (ostream &cout, const string & str )
{
  for(int i=0; i < str.length(); i++) {
    cout << str[i];
  }
  return cout;
}

istream & operator>> (istream &cin, string & str)
{
  char inputString[1000];
  cin >> inputString;

  str = inputString;
  return cin;
}

