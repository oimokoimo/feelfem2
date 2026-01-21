/*
 *      FEEL utility function
 *
 *
 */

#include <string.h>

int streq(s,t)
char *s,*t;
{
    if(strlen(s) != strlen(t)) return(0);
    while(*s) {
      if(*s != *t) return(0);
      s++;
      t++;
    }
    return(1);
}


int streq2(s,t)
char *s,*t;
{
    if(strlen(s) != strlen(t)) return(0);
    while(*s) {
      if((*s | 32) != (*t | 32)) return(0);
      s++;
      t++;
    }
    return(1);
}
