//
// General string class
//
// From Classic Data Structures in C++
// by   Timothy A. Budd
//
// File:     string.hpp
// Date:     1999/08/12
// Modified:
//
// Programmed (almost just typed (^^; ) by Hidehiro FUJIO
//
#ifndef FEM_CLASS_STRING
#define FEM_CLASS_STRING

#include <iostream.h>

int CstringLength(const char *);

class string 
{

  private:
    static int         totalObjects;
    static long        totalAssignedBufferLength;
    static int         maxBufferLength;
    unsigned short int bufferlength;
    char *             buffer;

  public:

// constructors

  string();                // default constructor
  string(char);            // one character constructor
  string(int);             // buffer length defined constructor
  string(const char *);    // initialization constructor
  string(const string &);  // copy constructor

// destructor   
  
  ~string();

// check routines (for debug)
  void checkLength(int);
  void checkReport(void); 

// line input
  istream &   getline(istream &);
  


// assignement and connection of strings

  void operator =  ( const string & right);
  friend int operator < (const string &left, const string &right);
  friend int operator != (const string & , const char *);
  friend int operator == (const string &left, const char *);
  friend int operator == (const string &left, const string &right);
//  void operator += ( const string & right);

  char & operator [] (unsigned int) const;
  void lower(void);


// convert into char * object
  operator const char * () const;
  operator       char * ()      ;

// member functions
  unsigned int length() const;
  int          contain(const char *) const;

};

ostream & operator << ( ostream &, const string &);
istream & operator >> ( istream &, string &);

#endif
