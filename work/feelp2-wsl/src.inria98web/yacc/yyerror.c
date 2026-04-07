#include <stdio.h>

extern int yylineno;

int yyerror(const char *s)
{
    fprintf(stderr, "FEEL parse error:(%d)  %s\n",yylineno, s);
    return 0;
}

