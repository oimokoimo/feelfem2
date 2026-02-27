// yyerror.cpp
#include <cstdio>

extern "C" int yylineno;     // bison/flexで使うなら
extern "C" char* yytext;     // flexで使うなら

extern "C" void yyerror(const char* s)
{
  std::fprintf(stderr, "parse error: %s", s);
  if (yytext)   std::fprintf(stderr, " near '%s'", yytext);
  if (yylineno) std::fprintf(stderr, " at line %d", yylineno);
  std::fprintf(stderr, "\n");
}
