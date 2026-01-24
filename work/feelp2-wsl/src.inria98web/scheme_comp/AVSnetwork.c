/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   AVSnetwork.c
 *      Date:   1999/03/17
 *   
 *   Purpose:   avsnetwork statements
 *   Functions: 
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "scheme_comp.h"

static int avsnetworks = 0;
static AVSnetwork *avsnetwork_ptr[MAX_AVSNETWORK];


void AVSnetwork_st(parameters)
     int parameters;
{
    int i;
    AVSnetwork *avsnetwork_struct;
    
    char **item_name;

    avsnetwork_struct = (AVSnetwork *)FEEL_GetMemory(sizeof(AVSnetwork));

    avsnetworks++;
    
    item_name = (char **)FEEL_GetMemory(sizeof(char *)*parameters);

    for(i=0;i<parameters;i++) {
	*(item_name + parameters - i - 1) = PopString();
    }

    if(avsnetworks > MAX_AVSNETWORK) {
      SystemError("Too many avsnetwork statements");
      return;
    }
    
    avsnetwork_struct -> parameters = parameters;
    avsnetwork_struct -> item_name  = item_name;
    avsnetwork_struct -> yylineno   = yylineno_info();

    avsnetwork_ptr[avsnetworks-1] = avsnetwork_struct;

    return;
}


int how_many_avsnetworks()
{
  return(avsnetworks);
}


AVSnetwork *get_nth_avsnetwork_ptr( n )
     int n;
{
  if(n <0 || n >= avsnetworks) {
    SystemAbort("Too big number for get_nth_avsnetwork_ptr\n");
  }

  return(avsnetwork_ptr[n]);
}

