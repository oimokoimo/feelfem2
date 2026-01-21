/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   is_member.c
 *      Date:   1993/07/10
 *   
 *   Purpose:   is_member(char * ,char **, n)
 *   Functions: char *の文字列が、n個のchar*の配列char**に含まれているか
 *              どうかを判定する。
 *              
 */

#include "../feel_def/feel_def.h"

is_member( name , ptr , n)
     char  *name;
     char **ptr;
     int    n;
{
    int i;

    for(i=0;i<n;i++) {
	if(streq(name,*(ptr+i))) return(YES);
    }

    return(NO);
}
