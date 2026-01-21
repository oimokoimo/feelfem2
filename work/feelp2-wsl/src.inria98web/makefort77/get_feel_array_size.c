/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_feel_array_size.c
 *      Date:   1994/01/27
 *   
 *   Purpose:   配列feelのサイズを設定する
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

static int  feel_size  = FEEL_ARRAY_SIZE;

void change_feel_array_size( n )
     int n;
{
    feel_size = n;
    return;
}

int get_feel_array_size()
{
    return(feel_size);
}

