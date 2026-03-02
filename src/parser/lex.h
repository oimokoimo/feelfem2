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
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 */

void initLex();
extern "C" {
int  yylex();
void disposeString( char * );

}
void yyerror(const char *);

int  CRinCOMMENT(char *);

extern int  numberOfLines;   /* Initialized in initLex */


