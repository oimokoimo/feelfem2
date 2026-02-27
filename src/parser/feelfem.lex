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
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Purpose: main program
 *
 *  Notes:
 *   - Parser and language spec are carried over from feelfem 1.0.
 *   - Back-end and build system are updated for modern C++ toolchains.
 */

%{

  /* #include <math.h> */
#include <stdlib.h>

typedef int SNname;
typedef int SNunit;
typedef int SNidentifierlist;
typedef int Expression;
typedef int SNweqTerms;
typedef int SNweqTerm;
typedef int SNsolveNeumannPairs;
 
#include "feelfem.tab.h"
#include "lex.h" 
 
 int numberOfLines;   /* Lines processed by lex */
 int yylineno = 1;

 char *freshString(char *);   

%}


Digit           [0-9]
Exp             [Ee][-+]?{Digit}+
SimpleEsc       \\[nt\\\'\"]
StrChar         ([^\\\"])

%START ELEMENT_EXPECTED

%%

"//"*          ;

geom            return(GEOM);
mesher          return(MESHER);
problem         return(PROBLEM);
mesh            return(MESH);
dimension       return(DIMENSION);
point           return(POINT);
edge            return(EDGE);
pedge           return(PEDGE);        /* parameter edge */
surface         return(SURFACE);
volume          return(VOLUME);
subdomain       return(SUBDOMAIN);
region          return(REGION);
domain          return(DOMAIN);
vertices        return(VERTICES);
generator       return(GENERATOR);

element         return(ELEMENT);
quadrature      return(QUADRATURE);

var             return(VAR);
int             return(INT);
double          return(DOUBLE);
const           return(CONST);
fem             return(FEM);
vfem            return(VFEM);
ewise           return(EWISE);
material        return(MATERIAL);
function        return(FUNCTION);

scheme          return(SCHEME);
ProgramModel    return(PROGRAMMODEL);
ElementType     return(ELEMENTTYPE);
if              return(IF);
then            return(THEN);
else            return(ELSE);
where           return(WHERE);
goto            return(GOTO);
return          return(RETURN);
while           return(WHILE);

write           return(WRITE);

perspect        return(PERSPECT);
output          return(OUTPUT);

solve           return(SOLVE);
solver          return(SOLVER);
parametric      return(PARAMETRIC);
nonlinear       return(NONLINEAR);
method          return(METHOD);
weq:            return(WEQ);
integral        return(INTEGRAL);
bintegral       return(BINTEGRAL);
dbc:            return(DBC);
nbc:            return(NBC);
in              return(IN);
at              return(AT);
on              return(ON);

"=="		return(Equal);
"!="		return(Nequal);
">="		return(GE);
"<="		return(LE);
"&&"		return(And);
"||"		return(Or);
"!|"		return(Xor);

"/*""/"*([^*/]|[^*]"/"|"*"[^/])*"*"*"*/"   numberOfLines+=CRinCOMMENT(yytext);


{Digit}*"."{Digit}+({Exp})? {
                                yylval.asDouble
                                    = atof(yytext[1] == 'd' ? yytext + 2
                                                            : yytext);
                                return(Double);
                            }                      

\"{StrChar}*\"        {  yytext[yyleng - 1] = '\0';
                         yylval.asString = freshString(yytext+1);
                         return(String);
}

"'"{StrChar}*"'"      {  yytext[yyleng - 1] = '\0';
                         yylval.asString = freshString(yytext+1);
                         return(String);
}

[A-Za-z][A-Za-z0-9_]* {  yylval.asString = freshString(yytext);
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
\n              numberOfLines++; yylineno++;
%%

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>


void initLex()
{
  numberOfLines = 1;  /* Initialize for each input files */

  return;
}

char *freshString(char *source)
{
    char* newString = (char*)malloc(strlen(source) + 1);
    if (newString == 0) {
        perror("In function freshString()");
        exit(1);
    }
    return strcpy(newString, source);
}
 
void disposeString(char *target)
{
    free(target);
}

int CRinCOMMENT( char *target )
{
  int   n  = 0;
  char *cp = target;
  while (*cp) {
    if(*cp == '\n') n++;
    cp++;
  }

  return(n);
}

