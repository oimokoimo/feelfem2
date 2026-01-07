/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem.lex
 *  Date     : 1999/07/20
 *  Modified : 2000/11/28
 *  Modified : 2001/02/18
 *  
 *  Purpose  : lexical parser for feelfem
 *  
 */

%{

  /* #include <math.h> */
#include <stdlib.h>

typedef int SNname;
typedef int SNunit;
typedef int SNidentifierlist;
typedef int Expression;
 
#include "y.tab.h"
#include "lex.h" 
 
 int eNumberOfLines;   /* Lines processed by lex */

 char *eFreshString(char *);   

%}


Digit           [0-9]
Exp             [Ee][-+]?{Digit}+

%START ELEMENT_EXPECTED

%%

"//"*          ;

"=="		return(Equal);
"!="		return(Nequal);
">="		return(GE);
"=<"		return(LE);
"&&"		return(And);
"||"		return(Or);
"!|"		return(Xor);

"/*""/"*([^*/]|[^*]"/"|"*"[^/])*"*"*"*/"      ;  


{Digit}*"."{Digit}+({Exp})? {
                                yylval.asDouble
                                    = atof(yytext[1] == 'd' ? yytext + 2
                                                            : yytext);
                                return(Double);
                            }                      

[A-Za-z][A-Za-z0-9_]* {  yylval.asString = eFreshString(yytext);
                         return(Identifier);
                      }

[0-9]* {        yylval.asInteger = atol(yytext);
                return(Integer);
                }

"("             return('(');
")"             return(')');
"{"             return('{');
"}"             return('}');
"["             return('[');
"]"             return(']');
"="             return('=');
"+"             return('+');
"-"             return('-');
"*"             return('*');
"/"             return('/');
"<"             return('<');
">"             return('>');
";"             return(';');
":"             return(':');
","             return(',');
"@"             return('@');
"!"             return('!');
"'"             return('\'');
"$"             return('$');
[ \t]+          ;
\n              numberOfLines++;
%%

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>


void eInitLex()
{
  eNumberOfLines = 1;  /* Initialize for each input files */

  return;
}

char *eFreshString(char *source)
{
    char* newString = (char*)malloc(strlen(source) + 1);
    if (newString == 0) {
        perror("In function eFreshString()");
        exit(1);
    }
    return strcpy(newString, source);
}
 
void eDisposeString(char *target)    /* never used */
{
    free(target);
}            
