#include <stdio.h>
#include <iostream.h>

#include "matrix.hpp"
#include "string.hpp"

main()
{

  matrix <string> *ptr;
  ptr = new  matrix <string> (3,3);

  for(int i=0;i<3;i++) {
    for(int j=0;j<3;j++) {
      char buf[BUFSIZ];
      sprintf(buf," I am %d  %d",i+1,j+1);
      ptr->val(i,j) = buf;
    }
  }

  for(int i=0;i<3;i++) {
    for(int j=i;j<3;j++) {
      ptr->val(i,j) = ptr->val(j,i);
    }
  }

  for(int i=0;i<3;i++) {
    for(int j=0;j<3;j++) {
            cout << "(" << i << ","<<j<<")  "<< ptr->val(i,j) << endl;
    }
  }

  ptr->~matrix();

  return(0);
}
