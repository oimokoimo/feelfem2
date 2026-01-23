/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   term_convert.c
 *      Date:   1993/11/15
 *   
 *   Purpose:   式中の変数を別の変数名に変換する
 *   Functions: 
 *              
 *              
 */

#include <string.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

int is_delimiter( char ) ;
int is_member_str( char *identifier , char *from[] , int terms );

char *term_convert( expr , from , to , terms )
     char expr[];   /* 数式の文字列 */
     char *from[]; /* 変換すべき変数名の配列 */
     char *to[];   /* 変換後の変数名の配列   */
     int terms;    /* 変換すべき変数名の数   */
{
    int i;
    char *cp;
    int ptr;
    int now;
    int no;
    int wrt_ptr;
    int i_ptr;
    int in_flag;   /* 変数名の中を走査していることを示すフラグ */

    char buf[EXPR_BUFSIZ];
    char identifier[BUFSIZ];

    if(strlen(expr) > EXPR_BUFSIZ / 2 ) {        /* 2 は安全係数 */
	SystemWarning( expr );
	SystemAbort("Too long expression(term_convert)");
    }
    
    in_flag = NO;

    ptr     = 0;
    wrt_ptr = 0;
    i_ptr   = 0;

    while(expr[ptr]) {
	
	if(in_flag == NO && is_delimiter(expr[ptr])) {
	    buf[wrt_ptr] = expr[ptr];
	    wrt_ptr++;
	    ptr++;
	    continue;
	}

	if(in_flag == YES && is_delimiter(expr[ptr])) {

	    /* is_member_str はLISPの関数と同じく、fromのリストに
	       identifierと同じ文字列が見つかった時にその番号を返す
	       戻り値は、0 見つからない n n番目と同じ                */

	    identifier[i_ptr] = '\0';
	    no = is_member_str( identifier , from , terms);
	    
	    /* 見つかったidentifierが、置換文字列では無い */
	    if(no == 0) {
		for(i=0;i<i_ptr;i++) {
		    buf[wrt_ptr] = identifier[i];
		    wrt_ptr++;
		}

		buf[wrt_ptr] = expr[ptr];
		wrt_ptr++;
		ptr++;
		in_flag = NO;
		continue;
	    }
	    /* 見つかったidentifierが、置換文字列 */
	    for(i=0;i<strlen(to[no-1]);i++) {
		buf[wrt_ptr] = *(to[no-1] + i);
		wrt_ptr++;
	    }
	    buf[wrt_ptr] = expr[ptr];
	    wrt_ptr++;
	    ptr++;
	    in_flag = NO;
	    continue;
	}

	/* identifier の始まり */
	if(in_flag == NO && !is_delimiter(expr[ptr])) {
	    i_ptr = 0;
	    identifier[i_ptr] = expr[ptr];
	    i_ptr++;
	    ptr++;
	    in_flag = YES;
	    continue;
	}

	if(in_flag == YES && !is_delimiter(expr[ptr])) {
	    identifier[i_ptr] = expr[ptr];
	    i_ptr++;
	    ptr++;
	    continue;
	}
	    
	SystemAbort("Logical Error(term_convert)");
    }

    /* exprの最後がidentifierで終わっている場合の処理 */
    if(in_flag == YES) {
	identifier[i_ptr] = '\0';
	no = is_member_str( identifier , from , terms);
	    
	/* 見つかったidentifierが、置換文字列では無い */
	if(no == 0) {
	    for(i=0;i<i_ptr;i++) {
		buf[wrt_ptr] = identifier[i];
		wrt_ptr++;
	    }
	    
	    buf[wrt_ptr] = expr[ptr];
	    wrt_ptr++;
	}
	else {
	/* 見つかったidentifierが、置換文字列 */
	    for(i=0;i<strlen(to[no-1]);i++) {
		buf[wrt_ptr] = *(to[no-1] + i);
		wrt_ptr++;
	    }
	    buf[wrt_ptr] = expr[ptr];
	    wrt_ptr++;
	    ptr++;
	}
    }

    buf[wrt_ptr] = '\0';

    if(wrt_ptr >= EXPR_BUFSIZ - 1) SystemAbort("Too long Expression");

    return(MakeStringCopy( buf ));
}

int is_member_str( identifier , from , terms ) 
    char *identifier;
    char *from[];
    int terms;
{
    int i;
    
    for(i=0;i<terms;i++) {
	if(streq2(identifier, from[i])) {
	    return( i + 1);
	}
    }

    return(0);
}

static int is_identifier_char( c )
     char c;
{
    if('a' <= c && c <= 'z') return(YES);
    if('A' <= c && c <= 'Z') return(YES);
    if('0' <= c && c <= '9') return(YES);
    if(c == '_' ) return(YES);
    if(c == '.' ) return(YES);

    return(NO);
}

static int is_number( c )
     char c;
{
    if('0' <= c && c <= '9') return(YES);
    if(c == '.') return(YES);

    return(NO);
}


int is_delimiter( c )     /* modernize 2026/01/21 */
     char c;
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

