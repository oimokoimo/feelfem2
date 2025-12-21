/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   uniq_list.c
 *      Date:   1993/07/10
 *   
 *   Purpose:   IDENTIFIER等の一意リストを作る為の関数
 *   Functions: uniq_list_init()         初期化 
 *              put_uniq_name()           登録  
 *              how_many_uniq_items()     情報  
 *              get_nth_uniq_name()       情報  
 *              
 */

#include "../feel_def/feel_def.h"

static char *uniq_item[MAX_UNIQ_ITEMS];
static int   uniq_items;

void uniq_list_init()
{
    uniq_items = 0;
    return;
}

void put_uniq_name( name )
     char *name;
{
    int i;
    
    /* 同じ名前があれば記録はしない。*/
    for(i=0;i<uniq_items;i++) {
	if(streq(name,uniq_item[i])) return;
    }

    if(uniq_items == MAX_UNIQ_ITEMS) {
	SystemAbort("Internal Error: UNIQ ITEMが多すぎるぅ〜！\n");
    }

    uniq_item[uniq_items] = name;  /* 領域はそのまま使います。*/

    uniq_items++;

    return;
}

int how_many_uniq_items()
{
    return(uniq_items);
}

char *get_nth_uniq_item( n )
     int n;
{
    if(n<0 || n >= uniq_items) {
	SystemAbort("uniq_itemでオーマイガァ！\n");
    }

    return(uniq_item[n]);
}


