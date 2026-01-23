/*
 * FEEL system Prototype Version 2
 * 
 * File     DangerCode.c
 * Made     1992/09/07
 * Modified 
 * Version  0.0
 *
 * Purpose: Output Coding warnning.
 *
 */

#include <stdio.h>
#include "system.h"

#define STRESS  fprintf(stderr,"%c[5m",27)
#define NORMAL  fprintf(stderr,"%c[0m",27)

#define BUG_MAX  256

int danger_codes = 0;

char *bug_title[BUG_MAX];
int   bug_count[BUG_MAX];

DangerCode( s )
     char *s;
{
    int i;

    for(i=0;i<danger_codes;i++) {
	if(streq(s,bug_title[i])) {
	    bug_count[i] += 1;
	    return;
	}
    }
    bug_title[danger_codes] = (char *)MakeStringCopy(s);
    bug_count[danger_codes] = 1;

    danger_codes++;

    return;
}

DangerCodeReport()
{
    int i;
    STRESS;
    printf("-----------------------------------------------------\n");
    printf("バグっているかもしれないレポート\n");

    for(i=0;i<danger_codes;i++) {
	printf("[%3d]  %s\n",bug_count[i],bug_title[i]);
    }
    printf("-----------------------------------------------------\n");
    NORMAL;
    
    return;
}




