/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : lex.h
 *  Date     : 1999/07/20
 *  Modified : 1999/07/20
 *  
 *  Purpose  : include header for lexical parser
 *  
 */

void initLex();
extern "C" {
int  yylex();
void disposeString( char * );

}
void yyerror(char *);

int  CRinCOMMENT(char *);

extern int  numberOfLines;   /* Initialized in initLex */


