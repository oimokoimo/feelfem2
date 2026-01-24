/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   avs_check.c
 *      Date:   1998/09/03
 *   
 *  Modified:   1999/03/17  avsnetwork check
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"

#include "check.h"

void avs_check()
{
  int i,j;
  int    parameters;
  int    yylineno;
  int    var_type;

  int avsoutputs;
  AVSoutput *avsoutput_ptr;
  AVSoutput *get_nth_avsoutput_ptr();
  char **fem_name;

  int avsnetworks;
  AVSnetwork *avsnetwork_ptr;
  AVSnetwork *get_nth_avsnetwork_ptr();
  char **item_name;
  
  
  
  if(avs_mode == 0) return;

  avsoutputs = how_many_avsoutputs();
  if(avsoutputs == 0) {
    SystemError("No avsoutput statement in avs mode");
    return;
  }

  
  /* confirm every parameter in avsoutput should be fem variable */
  for(i=0;i<avsoutputs;i++) {
    
    avsoutput_ptr = get_nth_avsoutput_ptr(i);
    parameters = avsoutput_ptr->parameters;
    fem_name   = avsoutput_ptr->fem_name;
    yylineno   = avsoutput_ptr->yylineno;

    for(j=0;j<parameters;j++) {
      var_type = get_var_kind( *(fem_name+j) );
      
      if(var_type != FEM ) {
	SystemError_yy_s("%s is not fem variable in avsoutput statement.",
			 *(fem_name+j),
			 yylineno);
      }
    }
  }    


  avsnetworks = how_many_avsnetworks();
  for(i=0;i<avsnetworks;i++) {
    
    avsnetwork_ptr = get_nth_avsnetwork_ptr(i);
    parameters     = avsnetwork_ptr->parameters;
    item_name      = avsnetwork_ptr->item_name;

    for(j=0;j<parameters;j++) {
      if(is_avsnetwork_member(*(item_name+j)) != YES) {
	SystemError_yy_s("%s is not avsnetwork identifier.",
			 *(item_name+j),
			 avsnetwork_ptr->yylineno);
      }
    }
  }

  return;
}






