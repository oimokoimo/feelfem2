/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ptrList.hpp
 *  Date     : 2001/02/02
 *  
 *  Purpose  : Pointer list to be valid opeator <
 *  
 */


#ifndef FEM_CLASS_PTRLIST
#define FEM_CLASS_PTRLIST

#include "list.hpp"       // 2001/02/02

template <class T> class ptrList : public list<T> {
  public:
  //    virtual void add(T value);
  int includes( T value) const;              // pointer 
  int getPosition( T value) const;           // pointer 

  void deleteAllPointedValues( );            // delete pointed value also

};



template <class T> int ptrList<T>::includes(T val) const
{
  for (link<T> * p = ptrToFirstLink; p; p = p->ptrToNextLink)
    if (*val == *(p->value))
      return 1;

    // not found
  return 0;
}

template <class T> int ptrList<T>::getPosition(T v) const
{
  // loop to test each element
  int no = 1;
  for (link<T> * p = ptrToFirstLink; p; p = p->ptrToNextLink) {
    if (*v == *(p->value)) {
      return no;
    }
    no++;
  }

    // not found
  return 0;
}


template <class T> void ptrList<T>::deleteAllPointedValues()
{
  // clear all items from the list
  link<T> * next;

  for (link<T> * p = ptrToFirstLink; p != 0; p = next)
    {
      // delete the element pointed to by p
      next = p->ptrToNextLink;
      p->ptrToNextLink = 0;

      delete p->value;    // delete also Pointed value
      delete p;
    }

  // mark that the list contains no elements
  ptrToFirstLink = 0;
    
  return;
}


#endif
