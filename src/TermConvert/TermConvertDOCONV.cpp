/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvertDOCONV.cpp
 *  Date     : 2002/01/22
 *  Modified : 2002/04/01 (simple reverse)
 *  
 *  Purpose  : 
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


#include "TermConvert.hpp"

char *TermConvert::ReverseConvertExpressionString(const char *expr)
{
  char *ret;
  ret = reverseTC->convertExpressionStringDBL( expr );
  return(ret);
}

char *TermConvert::convertExpressionString(const char *expr)
{
  int ptr;       // reading pointer   
  ptr          = 0; // reading pointer initialize
  outputBufptr = 0; // writing pointer initialize

  int in_flag;              // identifier flag
  in_flag   = NO;

  while(expr[ptr]) {  // while character is continues...

    // for first letter
    if(in_flag == NO && is_number_exp_char( expr[ptr] ) == YES &&
       ptr == 0 && (!is_number_exp_char( expr[ptr]) )) {

      putChar(expr[ptr]);
      ptr++;

      continue;
    }


    if(in_flag == NO && is_number_exp_char( expr[ptr] ) == YES &&
       is_number(expr[ptr-1]) == YES) {
      
      putChar(expr[ptr]);
      ptr++;

      continue;
    }

    // find identifier starting position
    if(in_flag == NO && is_identifier_start_char( expr[ptr] )==YES) {
      
      in_flag = YES;
      ibufptr = 0;

      assert(ibufptr < BUFSIZ);
      ibuf[ibufptr] = expr[ptr];

      ibufptr++;
      ptr    ++;
      continue;
    }
    
    // in identifier, and still identifier
    if(in_flag == YES && is_identifier_char(expr[ptr]) == YES) {
      
      ibuf[ibufptr] = expr[ptr];

      ibufptr++;
      ptr    ++;

      continue;
    }

    // end of identifier
    if(in_flag == YES && is_identifier_char(expr[ptr]) == NO) {
      
      putIdentifier();
      putChar( expr[ptr] );
      ptr++;
      in_flag = NO;

      continue;
    }

    putChar( expr[ptr] );
    ptr++;
  }

  // final identifier
  if(in_flag == YES) {
    putIdentifier();
  }

  putChar( '\0' );
  return(outputBuf);
}


char *TermConvert::convertExpressionStringDBL(const char *expr)
{
  int ptr;       // reading pointer   
  ptr          = 0; // reading pointer initialize
  outputBufptr = 0; // writing pointer initialize

  int in_flag;              // identifier flag
  in_flag   = NO;

  int in_num_flag;
  in_num_flag = NO;

  while(expr[ptr]) {  // while character is continues...


    // for first letter
    if(in_flag == NO && is_number_exp_char( expr[ptr] ) == YES &&
       ptr == 0) {
      
      in_num_flag = YES;
      nbuf[nbufptr] = expr[ptr];

      // kokokara

      putChar(expr[ptr]);
      ptr++;

      continue;
    }

    // numbers
    if(in_flag == NO && is_number_exp_char( expr[ptr] ) == YES &&
       is_number(expr[ptr-1]) == YES) {
      
      
      putChar(expr[ptr]);
      ptr++;

      continue;
    }

    // find identifier starting position
    if(in_flag == NO && is_identifier_start_char( expr[ptr] )==YES) {
      
      in_flag = YES;
      ibufptr = 0;

      assert(ibufptr < BUFSIZ);
      ibuf[ibufptr] = expr[ptr];

      ibufptr++;
      ptr    ++;
      continue;
    }
    
    // in identifier, and still identifier
    if(in_flag == YES && is_identifier_char(expr[ptr]) == YES) {
      
      ibuf[ibufptr] = expr[ptr];

      ibufptr++;
      ptr    ++;

      continue;
    }

    // end of identifier
    if(in_flag == YES && is_identifier_char(expr[ptr]) == NO) {
      
      putIdentifier();
      putChar( expr[ptr] );  // this is a character after identifier
      ptr++;
      in_flag = NO;

      continue;
    }

    putChar( expr[ptr] );
    ptr++;
  }

  // final identifier
  if(in_flag == YES) {
    putIdentifier();
  }

  putChar( '\0' );
  return(outputBuf);
}

// reverse version (2002/04/01)
char *TermConvert::SimpleReverseConvertExpressionString(const char *expr)
{
  int ptr;       // reading pointer   
  ptr          = 0; // reading pointer initialize
  outputBufptr = 0; // writing pointer initialize

  int in_flag;              // identifier flag
  in_flag   = NO;

  while(expr[ptr]) {  // while character is continues...

    if(in_flag == NO && is_number_exp_char( expr[ptr] ) == YES &&
       is_number(expr[ptr-1]) == YES) {
      
      putChar(expr[ptr]);
      ptr++;

      continue;
    }

    // find identifier starting position
    if(in_flag == NO && is_identifier_start_char( expr[ptr] )==YES) {
      
      in_flag = YES;
      ibufptr = 0;

      assert(ibufptr < BUFSIZ);
      ibuf[ibufptr] = expr[ptr];

      ibufptr++;
      ptr    ++;
      continue;
    }
    
    // in identifier, and still identifier
    if(in_flag == YES && is_identifier_char(expr[ptr]) == YES) {
      
      ibuf[ibufptr] = expr[ptr];

      ibufptr++;
      ptr    ++;

      continue;
    }

    // end of identifier (reverse version)
    if(in_flag == YES && is_identifier_char(expr[ptr]) == NO) {
      
      putIdentifierReverse();
      putChar( expr[ptr] );
      ptr++;
      in_flag = NO;

      continue;
    }

    putChar( expr[ptr] );
    ptr++;
  }

  // final identifier (reverse version) 
  if(in_flag == YES) {
    putIdentifierReverse();
  }

  putChar( '\0' );
  return(outputBuf);
}

void TermConvert::putChar(char c)
{
  assert(outputBufptr < TERMCONVERT_EXPRESSION_BUFLEN);
  outputBuf[outputBufptr] = c;
  outputBufptr ++;

  return;
}

void TermConvert::putIdentifier(void)
{
  assert(ibufptr>0);
  ibuf[ibufptr] = '\0';
  
  string str(ibuf);

  listIterator <StrStrPair *>itr(ssPairPtrLst);
  for(itr.init(); !itr ; ++itr ) {
    if( itr()->IsMatchFirstComponent( str ) ) {
      string second;
      itr()->SetArgStringWithSecond( second );
      putStr(second);

      // 2002-02-21 (make converted identifier list)
      if(!convertedStrLst.includes(second)) {
	convertedStrLst.add(second);
      }

      return;
    }
  }

  putStr(ibuf);
  return;
}

void TermConvert::putIdentifierReverse(void)
{
  assert(ibufptr>0);
  ibuf[ibufptr] = '\0';
  
  string str(ibuf);

  listIterator <StrStrPair *>itr(ssPairPtrLst);
  for(itr.init(); !itr ; ++itr ) {
    if( itr()->IsMatchSecondComponent( str ) ) {
      string first;
      itr()->SetArgStringWithFirst( first );
      putStr(first);

      // no necessity for reverse conversion 2002-04-01
      //
      // 2002-02-21 (make converted identifier list)
      //      if(!convertedStrLst.includes(second)) {
      //	convertedStrLst.add(second);
      //      }

      return;
    }
  }

  putStr(ibuf);
  return;
}


void TermConvert::putStr(const char *b)
{
  while(*b) {
    putChar(*b);
    b++;
  }
  return;
}

int TermConvert::is_identifier_char( char c )
{
    if('a' <= c && c <= 'z') return(YES);
    if('A' <= c && c <= 'Z') return(YES);
    if('0' <= c && c <= '9') return(YES);
    if(c == '_' ) return(YES);

    return(NO);
}

int TermConvert::is_identifier_start_char( char c )
{
    if('a' <= c && c <= 'z') return(YES);
    if('A' <= c && c <= 'Z') return(YES);
    if(c == '_' ) return(YES);
    return(NO);
}

int TermConvert::is_number( char c )
{
    if('0' <= c && c <= '9') return(YES);
    if(c == '.') return(YES);

    return(NO);
}


int TermConvert::is_delimiter( char c )
{
    switch(c) {
      case ' ':             /* この扱に注意が必要 */
      case '+':
      case '-':
      case '/':
      case '*':
      case '(':
      case ')':
      case '^':
	return(YES);
	
      default:
	break;
    }

    return(NO);
}

int TermConvert::is_number_exp_char(char c)
{
  if(c == 'e') return(YES);
  if(c == 'E') return(YES);
  if(c == 'd') return(YES);
  if(c == 'D') return(YES);

  return(NO);
}

void TermConvert::StoreIgnoreSymbolLstForConvertedStrLst(const char *nm)
{
  reverseTC->ignoreConvertedStrLst.add(nm);   // now called from EwiseTC
  return;
}

// for user function defines
void TermConvert::GetConvertedUserFuncStrList(list <string>&funcStrLst)
{
  listIterator <string>itr(usedUserFuncSymbolStrLst);
  for(itr.init(); !itr ; ++itr) {
    funcStrLst.addlast(itr());
  }
  return;
}

// for ecal procedures...
void TermConvert::GetConvertedIdentifierList( list<string>&identifierLst )
{
  listIterator <string> itr(convertedStrLst);
  
  for(itr.init(); !itr ; ++itr ){

    // this is for canceling user function symbol(02/09/16)
    if(ignoreConvertedStrLst.includes(itr())) {
      if(!usedUserFuncSymbolStrLst.includes(itr())) {  //02/09/18 add 
	usedUserFuncSymbolStrLst.add(itr());
      }
      continue;
    }

    if(identifierLst.includes(itr())) continue;
    
    identifierLst.add(itr());
  }
  
  return;
}

void TermConvert::GetConvertedUserFuncStrInReverseList( list <string>&funcLst)
{
  assert(reverseTC != 0);
  reverseTC->GetConvertedUserFuncStrList( funcLst );
  return;
}

void TermConvert::GetConvertedIdentifierInReverseList(list<string>&identifierLst )
{
  assert(reverseTC != 0);
  reverseTC->GetConvertedIdentifierList(identifierLst);
  
  return;
}

void TermConvert::GetConvertedElementPtrList( list <Element *>&ePtrLst)
{
  listIterator <Element *>itr(elementPtrLst);

  for(itr.init(); !itr ; ++itr) {

    if(ePtrLst.includes(itr())) continue;

    ePtrLst.addlast( itr() );
  }
  return;
}
