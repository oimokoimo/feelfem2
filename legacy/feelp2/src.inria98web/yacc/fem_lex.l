/*
 *    FESL lex program
 * 
 *    Filename             fem_lex.l
 *    Made                 1991/12/24
 *    LastModified         1992/01/24
 *    Version              0.2
 */
%{

#ifdef DEBUG

#include <assert.h>
main()
{
char *p;
assert(sizeof(int) >= sizeof (char *));
while(p=(char *)yylex())
printf("%-10.10s is \"%s\"\n",p,yytext);
}

s_lookup(){}
int yynerrs = 0;
#define token(x) (int) "x"


#else

#include "y.tab.h"
#define token(x)  x

#endif DEBUG

#define END(v) (v-1 + sizeof v / sizeof v[0])
extern push();

%}


letter           [$a-zA-Z_]
letter_or_digit  [$a-zA-Z_0-9]
digit            [0-9]
N                {digit}+
white_space      [ \t\n]
/* other            */
%%

"@"             return token(ATMARK);
"mesh"          return token(MESH);
"point"         return token(POINT);
"refine"        return token(REFINE);
"curve"         return token(CURVE);
"domain"        return token(DOMAIN);
"region"        return token(REGION);
"edge"          return token(EDGE);
"rectangle"     return token(RECTANGLE);
"nodes"         return token(NODES);
"showmesh"      return token(SHOWMESH);
"number"        return token(NUMBER);
"dimension"     return token(DIMENSION);
"subdomain"     return token(SUBDOMAIN);

"element"       return token(ELEMENT);
"quadrature"    return token(QUADRATURE);
"boundary"      return token(BOUNDARY);

"var"           return token(VAR);
"int"           return token(INT);
"avsint"        return token(AVSINT);
"const"         return token(CONST);
"fem"           return token(FEM);
"double"        return token(DOUBLE);
"avsdouble"     return token(AVSDOUBLE);
"ewise"         return token(EWISE);
"material"      return token(MATERIAL);
"function"      return token(FUNCTION);

"scheme"        return token(SCHEME);
"solve"         return token(SOLVE);
"method"        return token(METHOD);
"linear"        return token(LINEAR);
"isoparametric" return token(ISOPARAMETRIC);
"nonlinear"     return token(NONLINEAR);
"strategy"      return token(STRATEGY);
"initial"       return token(INITIAL_VALUE);
"set-eps"       return token(EPS);
"newton-factor"   return token(NEWTON_FACTOR);
"newton-times"    return token(NEWTON_TIMES);
"displacement"  return token(DISPLACEMENT);
"shape"         return token(SHAPE);
"symmetry"      return token(SYMMETRY);
"eq:"           return token(EQ);
"weq:"          return token(WEQ);
"func:"         return token(FUNC);
"eigen:"        return token(EIGEN);
"dbc:"          return token(DBC);
"nbc:"          return token(NBC);
"at"            return token(AT);
"on"            return token(ON);
"in"            return token(IN);
"goto"          return token(GOTO);
"let"           return token(LET);
"showvec"       return token(SHOWVEC);
"showvec-file"  return token(SHOWVEC_FILE);
"contour"       return token(CONTOUR);
"contour-file"  return token(CONTOUR_FILE);
"perspect"      return token(PERSPECT);
"write"         return token(WRITE);
"read"          return token(READ);
"xplot"         return token(XPLOT);
"plot-file"     return token(PLOT_FILE);
"if"            return token(IF);
"then"          return token(THEN);
"else"          return token(ELSE);
"endif"         return token(ENDIF);
"fwrite"        return token(FILE_WRITE);
"time-plot-file"    return token(TIME_PLOT_FILE);
"L2norm"        return token(L2NORM);
"MAXnorm"       return token(MAXNORM);
"adaptmesh"     return token(ADAPTMESH);
"avsoutput"     return token(AVSOUTPUT);
"avsnetwork"    return token(AVSNETWORK);

"{"             return token(lp);
"}"             return token(rp);
"["             return token(lk);
"]"             return token(rk);
"("             return token(lb);
")"             return token(rb);

"=="            return token(equal);
"<="            return token(le);
"<"             return token(lt);
">="            return token(ge);
">"             return token(gt);
"!="            return token(ne);

"="             return token(eq);
";"             return token(sc);
":"             return token(cc);
","             return token(co);
"+"             return token(pl);
"-"             return token(mi);
"*"             return token(mu);
"/"             return token(di);


{letter}{letter_or_digit}*          {  push(yytext);
                                       return token(IDENTIFIER);
                                    }

"'"[^']*"'"                         {  push(yytext);
                                       return token(STRING);
                                    }

"/*""/"*([^*/]|[^*]"/"|"*"[^/])*"*"*"*/"      ;


{N}"."({N}([deDE]("-")?{N})?)? {          push(yytext);
				       return token(num);
                                    }

{digit}{digit}*          {          push(yytext);
				       return token(num);
                                    }

"-"{digit}{digit}*          {          push(yytext);
				       return token(num);
                                    }

"-"{N}"."({N}([deDE]("-")?{N})?)? {          push(yytext);
				       return token(num);
                                    }

{white_space}+                       ;



%%

