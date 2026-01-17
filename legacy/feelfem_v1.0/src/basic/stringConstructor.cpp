//
// General string class
//
// From Classic Data Structures in C++
// by   Timothy A. Budd
//
// Filename: stringConstructor.cpp
// Date:     1999/08/12
// Modified:
// Purpose:  constructor and destructor
//
// Programmed (almost just typed (^^; ) by Hidehiro FUJIO
//

#include <assert.h>
#include "string.hpp"

// initialize static private members
int  string::maxBufferLength           = 0;
int  string::totalObjects              = 0;
long string::totalAssignedBufferLength = 0;

string::string(int size)
{
  assert(size >= 0);

  cout << "string(" << size << ") constructor\n";
  
  // for null character at the end
  bufferlength = 1 + size;
  checkLength(bufferlength);

  // assign memory and confirm
  buffer = new char[bufferlength];
  assert( buffer != 0);

  // initialize
  for(int i=0; i<bufferlength; i++) {
    *(buffer+i) = '\0';
  }

  return;
}

string::string(const char * initialtext)
{
  // calculate length

  bufferlength = 1 + CstringLength(initialtext);
  checkLength(bufferlength);
  
  // allocate memory
  
  buffer = new char[bufferlength];
  assert( buffer != 0);

  // copy the contents, last character is null string

  int i;
  for(i=0; initialtext[i] != '\0'; i++) {
    *(buffer+i) = *(initialtext+i);
  }
  buffer[i] = '\0';

  return;
}

string::string(const string & initialstring)
{
  bufferlength = 1 + CstringLength(initialstring.buffer);
  checkLength(bufferlength);

  buffer = new char[bufferlength];
  assert(buffer != 0);

  int i;
  for(i=0; initialstring.buffer[i] != '\0'; i++) {
    buffer[i] = initialstring.buffer[i];
  }
  buffer[i] = '\0';

  return;
}


string::string( char c)
{
  bufferlength = 2;
  checkLength(bufferlength);

  buffer = new char[bufferlength];
  assert(buffer != 0);

  buffer[0] = c;
  buffer[1] = '\0';

  return;
}

// default constructor

string::string(void)
{
  bufferlength = 1;
  checkLength(bufferlength);

  buffer = new char[bufferlength];
  assert(buffer != 0);

  buffer[0] = '\0';

  return;

}

// destructor

string::~string()
{
  //  cerr << "DELETE " << buffer <<endl;   // for check destructor...

  delete [] buffer;
  buffer = 0;
}
