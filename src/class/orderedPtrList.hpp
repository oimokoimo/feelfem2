/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : orderedPtrList.hpp
 *  Date     : 2001/02/02
 *  Modified : 2002/01/08 ( uniqAdd(T val))
 *  
 *  Purpose  : Pointer list to be valid opeator <
 *             uniqAdd may require == operator implementation for class T
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 */


#ifndef FEM_CLASS_ORDEREDPTRLIST
#define FEM_CLASS_ORDEREDPTRLIST

#include "ptrList.hpp"       // 2002/01/08 (formerly, include list.hpp
                             // inorder to evaluate .includes() function,
                             // change to ptrList.hpp and public ptrList<T>

template <class T> class orderedPtrList : public ptrList<T> {
  public:
  //    virtual void add(T value);
  void add( T value);
  void uniqAdd( T value );
};

template <class T> void orderedPtrList<T>::add(T val)
{

  //  cout << "COME TO orderedPtrList add [" << *val << "]\n";

  listIterator<T> itr(*this);
  for(itr.init(); !itr; ++itr) {
    if(*val < *itr()) {                  // !!!  Here Pointed Value comparison
     itr.addBefore(val);
     return;
   }
  }
  itr.addBefore(val);
}   

template <class T> void orderedPtrList<T>::uniqAdd(T val)
{

  //  cout << "COME TO orderedPtrList add [" << *val << "]\n";

  listIterator<T> itr(*this);
  for(itr.init(); !itr; ++itr) {
    if(*val == *itr()) return;
    if(*val < *itr()) {                  // !!!  Here Pointed Value comparison
     itr.addBefore(val);
     return;
   }
  }
  itr.addBefore(val);
}   

#endif
