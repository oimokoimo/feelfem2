/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File: refine.c
 *      Date: 1997/07/28
 *   
 *   Purpose: refine statement
 *            
 */

#include "../feel_def/feel_def.h" 
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../feel_def/feel_msg.h"    /* modernize 2026/01/21 */
#include "../system/system.h"
#include "mesh_comp.h"

static Refine *refine[MAX_POINTS];
static int     refine_points = 0;

void refine_st()
{
  int i;
  double fact;
  char *cp;

  Refine *refine_ptr;

  if(refine_points == MAX_POINTS) {
    if(english_mesg) {
      SystemError("Too many refine points specified.");
    }
    else {
      SystemError("refine point指定が多すぎる");
    }

    pop(); pop(); 
    return;
  }

  fact = PopDouble();
  cp   = PopString();


  refine[refine_points] = (Refine *)FEEL_GetMemory( sizeof( Refine) );

  refine[refine_points]->factor = fact;
  refine[refine_points]->name = cp;
  refine[refine_points]->yylineno = yylineno_info();

  for(i=0;i<refine_points;i++) {
    refine_ptr = refine[i];

    if(streq(cp,refine_ptr->name)) {
      SystemError_s("Refine point %s is multiply defined.",cp);
    }
  }
  refine_points++;

  return;
}


int how_many_refine_points()
{
  return(refine_points);
}

Refine *get_nth_refine_ptr( n ) 
     int n;
{
  if(n < 0 || n > refine_points-1) {
    SystemAbort("get_nth_refine_ptr Inner error");
  }
  
  return(refine[n]);
}

  
