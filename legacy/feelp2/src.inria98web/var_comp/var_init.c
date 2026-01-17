/*
 * FEEL system Prototype Version 2
 * 
 * File     
 * Made     1992/09/08
 * Modified 
 * Version  0.0
 *
 * Purpose: Initialize Variable 
 *
 */
#include <stdio.h>

char *feel_key_word[] = {
    "dx","dy","lap","DX","DY","LAP","x","X","y","Y",
    "L1","L2","L3","L4","tri","rect","line","t","T","nil","NIL",
    NULL
  };

char *feel_fem_func[] = {
    "dnorm",  NULL
  };


char *fort77_func[] = {
    "dsin","dcos","dtan","dexp","dlog","dlog10" ,
    "dsqrt",
    NULL
  };

char fort77_mark[] = {
    '(' , ')','+','-','*','/','\0'
  };
