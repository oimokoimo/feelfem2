#include "xplot.h"


number(x,y,n)
     int x,y,n;
{
    char buf[BUFSIZ];
    
    sprintf(buf,"%d",n);
    symbol(x,y,buf);
}

fnumber(x,y,n)
     double x,y;
     int n;
{
    char buf[BUFSIZ];
    
    sprintf(buf,"%d",n);
    fsymbol(x,y,buf);
}

