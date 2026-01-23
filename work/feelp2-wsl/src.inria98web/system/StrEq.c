/*
 *      FEEL utility function
 *
 *
 */
#include <stdio.h>
int streq(s,t)
char *s,*t;
{
    if(s == NULL || t == NULL) return 0;
    while (*s && *t) {
        if (*s != *t) return 0;
        ++s; ++t;
    }
    return (*s == '\0' && *t == '\0');
}

int streq2(s,t)
char *s,*t;
{
    if(s == NULL || t == NULL) return 0;
    while (*s && *t) {
        if ( (*s | 32) != (*t | 32) ) return 0; /* ASCII限定 */
        ++s; ++t;
    }
    return (*s == '\0' && *t == '\0');
}
