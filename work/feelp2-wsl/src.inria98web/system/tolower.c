/*
 * FEEL system Prototype Version 2
 * 
 * File     tolower.c
 * Made     1992/09/24
 * Modified 
 * Version  0.0
 *
 * Purpose: make all character lower
 *
 */


void tolower_buf( buf )
     char *buf;
{
    while(*buf) {
	if(*buf >= 'A' && *buf <= 'Z') {
	    *buf = *buf - 'A' + 'a';
	}

	buf++;
    }

    return;
}
