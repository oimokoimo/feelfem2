//======================================================================
//  File:        iterator.h
//  Author:      Timothy A. Budd
//  Description: This file contains the iterator template class
//
//  Copyright (c) 1992 by Timothy A. Budd.  All Rights Reserved.
//	may be reproduced for any non-commercial purpose
//======================================================================

#ifndef ITERATOR_H
#define ITERATOR_H



//----------------------------------------------------------------------
//	class iterator
//		define the protocol to be used by all iterators
//		subclasses must implement each of the five
//		iterator methods
//----------------------------------------------------------------------

template <class T> class iterator
{
public:
    // initialization
    virtual int  init() = 0;

    // test if there is a current element
    virtual int  operator !() = 0;

    // current element
    virtual T    operator ()() = 0;

    // find next element
    virtual int  operator ++() = 0;

    // change current element
    virtual void operator =(T newValue) = 0;
};

#endif
