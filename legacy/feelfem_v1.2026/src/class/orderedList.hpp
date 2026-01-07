/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : orderedList.hpp
 *  Date     : 1999/??/??
 *  Modified : 2002/01/08  (rename orderdList -> orderedList)
 *  
 *  Purpose  : ordered list for direct comparison (not pointer comparison)
 *             c.f. ptrOrderedList.hpp
 */

#ifndef FEM_CLASS_ORDEREDLIST
#define FEM_CLASS_ORDEREDLIST

#include "list.hpp"

template <class T> class orderedList : public list<T> {
  public:
    virtual void add(T value);
};

template <class T> void orderedList<T>::add(T val)
{
  listIterator<T> itr(*this);
  for(itr.init(); !itr; ++itr) {
   if(val < itr()) {
     itr.addBefore(val);
     return;
   }
  }
  itr.addBefore(val);
}   

#endif
