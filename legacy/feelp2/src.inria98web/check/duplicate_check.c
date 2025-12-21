/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   duplicate_check.c
 *      Date:   1993/07/05
 *   
 *   Purpose:   文字列に対して、スタックに積む形式で重複の調査を行う。
 *   Functions: duplicate_init()          初期化 
 *              duplicate_push( char *)   変数名の登録
 *              is_duplicate( char *)     重複しているかの検査
 *              
 */
#include "../feel_def/feel_def.h"

static int words = 0;
static char *word[DUPLICATE_CHECK];

duplicate_init()
{
    words = 0;

    return;
}

duplicate_push( name )
     char *name;
{
    if(words == DUPLICATE_CHECK) {
	if(english_mesg) {
	    SystemAbort("INNER ERROR: duplicate_check.c");
	}
	else {
	    SystemAbort("重複定義検査プログラムのDUPLICATE_CHECKで引っ掛かりました。\n");
	}

    }

    word[words] = name;
    words++;

    return;
}

is_duplicate( name )
     char *name;
{
    int i;
    int match;

    match = 0;

    for(i=0;i<words;i++) {
	if(streq(word[i],name)) match++;
    }

    if(match == 1) return(NO);

    if(match == 0) {
	if(english_mesg) {
	    SystemAbort("INNER ERROR: duplicate_check.c(2)");
	}
	else {
	    SystemAbort("duplicateルーチンで登録されてないよ〜ん");
	}
    }

    return(YES);
}



