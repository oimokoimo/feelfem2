/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   MakeMemoryCopy.c
 *      Date:   1993/07/13
 *   
 *   Purpose:   メモリの領域取得とコピー
 *              
 */

#include "../system/system.h"

char *MakeMemoryCopy( ptr , size )
     char *ptr;
     int  size;
{
    char *ret_ptr;

    ret_ptr = (char *)FEEL_GetMemory( size );

    while(size) {
	*ret_ptr = *ptr;
	ret_ptr++;
	ptr++;

	size--;
    }

    return(ret_ptr);
}
