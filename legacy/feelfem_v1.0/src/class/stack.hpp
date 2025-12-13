/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : stack.hpp
 *  Date     : 2001/02/21
 *  Modified : 
 *  
 *  Purpose  : stack list template(push,pop)
 *  
 */

#ifndef FEM_CLASS_STACK
#define FEM_CLASS_STACK

#include "list.hpp"

template <class T> class stack : public list<T> {

public:
  T pop() {

    assert(ptrToFirstLink != 0);

    T ret;
    ret = firstElement();
    removeFirst();
    
    return ret;
  }

  void push(T value) {
    add(value);
  }

};




#endif

