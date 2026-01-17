/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : vector.hpp
 *  Date     : 2001/08/17
 *  Modified : 
 *  
 *  Purpose  : array template
 *  
 */

#ifndef FEM_CLASS_VECTOR
#define FEM_CLASS_VECTOR

#include <assert.h>

template <class T> class vector {

public:

  vector (unsigned int numberOfElements);  // constructor
  
  virtual ~vector();

  T & operator [] (unsigned int index) const;

  unsigned int length () const;

protected:
  T *          data;
  unsigned int size;
};

template<class T> vector<T>::vector(unsigned int numberOfElements)
  : size(numberOfElements)
{
  data = new T[size];

  assert(data != 0);
}

template <class T> vector<T>::~vector()
{
  delete [] data;
  data = 0;
  size = 0;
}

template <class T> T & vector<T>::operator[] (unsigned int index) const
{
  assert(index < size);
  
  return data[index];
}

template <class T>unsigned int vector<T>::length() const
{
  return ( size );
}

#endif
