/*
 * FEEL system Prototype Version 2
 * 
 * File     is_number_string.c
 * Made     1992/09/22
 * Modified 
 * Version  0.0
 *
 * Purpose: judge given string is a number or not.
 *
 */

#include "../main/feel.h"

int is_number_string( term )
     char *term;
{
    int point_counter;
    int e_counter;
    int d_counter;
    int minus_counter;
    
    point_counter = 0;
    e_counter     = 0;
    d_counter     = 0;
    minus_counter = 0;

    while(*term) {
	if(*term >='0' && *term <= '9') {
	    term++;
	    continue;
	}

	if(*term == '.') {
	    point_counter++;
	    term++;
	    continue;
	}

	if(*term == 'e' || *term == 'E') {
	    term++;
	    e_counter++;
	    if(*term == '-') continue;
	    if(*term >= '0' && *term <= '9') continue;
	    
	    return(NO);
	}

	if(*term == 'd' || *term == 'D') {
	    term++;
	    d_counter++;
	    if(*term == '-') continue;
	    if(*term >= '0' && *term <= '9') continue;
	    
	    return(NO);
	}

	if(*term == '-') {
	    term++;
	    minus_counter++;
	    if(*term >= '0' && *term <= '9') continue;
	    return(NO);
	}
	return(NO);

    }
    return(YES);
}






  

