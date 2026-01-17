#include <stdio.h>

static char ret[4];
char *zerozeronum( n )
     int n;
{
  if(n > 999 || n < 1) {
    SystemAbort("Illegal number to zerozeronum");
  }

  if(n < 10 ) {
    sprintf(ret,"00%d",n);
  }
  else {
    if(n < 100) {
      sprintf(ret,"0%2d",n);
    }
    else {
      sprintf(ret,"%3d",n);
    }
  }

  return(ret);
}

  
