#include <stdio.h>

int yyerror(const char *s)
{
    fprintf(stderr, "FEEL parse error: %s\n", s);
    return 0;
}

