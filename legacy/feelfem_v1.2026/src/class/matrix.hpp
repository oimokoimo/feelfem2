/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : matrix.hpp
 *  Date     : 2002/02/06
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CLASS_MATRIX
#define FEM_CLASS_MATRIX

#include <assert.h>

template <class T> class matrix {
public:
  matrix( unsigned int rows_ini, unsigned int columns_ini) {
    assert (rows_ini > 0);
    assert (columns_ini > 0);
    
    data = new T[rows_ini*columns_ini];
    assert(data != 0);

    rows = rows_ini;
    columns = columns_ini;
    return;
  }
    
  virtual ~matrix() {
    delete []data;
  }

  T& val(unsigned int i, unsigned int j) const {
    //    assert(i >= 0);
    //    assert(j >= 0);
    assert(i <  rows);
    assert(j <  columns);
    return( data[i*columns + j] );
  }

protected:
  T *data;
  unsigned int rows,columns;
};

#endif
