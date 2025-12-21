/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File: expression_term.c
 *      Date: 1993/06/03  
 *   
 *   Purpose: yaccでexpressionに蓄えられたIDENTIFIERの補助データを
 *            作成する。
 */

#include "../system/system.h"

typedef struct Expression_term_
{
    char *name;
    struct Expression_term_ *next;
} Expression_term;

static int terms = 0;
static Expression_term first;

void put_exp_term( name )
     char *name;
{
    int i;
    char *cp;
    Expression_term *ptr,*new_ptr;

    if(terms == 0) {
	terms++;

	cp = MakeStringCopy(name);  /* 名前の記憶領域はこのルーチン
                                       で独立にとる                 */
	first.name = cp;
	first.next = NULL;
	
	return;
    }
	
    ptr = &first;

    for(i=1;i<terms;i++) {
	if(streq(ptr->name,name)) return;  /* 既に登録済み */
	ptr = ptr->next;                    /* 読み飛ばし */
    }

    cp = MakeStringCopy(name);  /* 名前の記憶領域はこのルーチン
				   で独立にとる                 */

    new_ptr = (Expression_term *)FEEL_GetMemory(sizeof(Expression_term));

    ptr->next     = new_ptr;
    new_ptr->name = cp;
    new_ptr->next = NULL;

    terms++;

    return;
}
