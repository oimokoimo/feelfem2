/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   AVSoutput.c
 *      Date:   1998/09/03   
 *   
 *  Modified:   1999/03/23  return avsdouble/avsint to the panel included
 *   
 *   Purpose:   avsoutput statements
 *   Functions: 
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "scheme_comp.h"

static int avsoutputs = 0;
static AVSoutput *avsoutput_ptr[MAX_AVSOUTPUT];

char *get_nth_uniq_item();
int get_nth_avsoutput_parameters( int n );

void AVSoutput_st(parameters)
     int parameters;
{
    int i;
    AVSoutput *avsoutput_struct;
    
    char **var_name;

    avsoutput_struct = (AVSoutput *)FEEL_GetMemory(sizeof(AVSoutput));

    avs_mode   = 1;    /* strongly... */
    avsoutputs++;
    
    var_name = (char **)FEEL_GetMemory(sizeof(char *)*parameters);

    /* ΩÁ»÷ƒÃ§Í */
    for(i=0;i<parameters;i++) {
	*(var_name + parameters - i - 1) = PopString();
    }

    if(avsoutputs > MAX_AVSOUTPUT) {
      SystemError("Too many avsoutput statements");
      return;
    }
    
    avsoutput_struct -> parameters = parameters;
    avsoutput_struct -> fem_name   = var_name;
    avsoutput_struct -> yylineno   = yylineno_info();

    avsoutput_ptr[avsoutputs-1] = avsoutput_struct;

    return;
}


int how_many_avsoutputs()
{
  return(avsoutputs);
}


AVSoutput *get_nth_avsoutput_ptr( n )
     int n;
{
  if(n <0 || n >= avsoutputs) {
    SystemAbort("Too big number for get_nth_avsoutput_ptr\n");
  }

  return(avsoutput_ptr[n]);
}


int get_nth_avsoutput_parameters( n )
     int n;
{
  if(n <0 || n >= avsoutputs) {
    SystemAbort("Too big number for get_nth_avsoutput_parameters");
  }
  return(avsoutput_ptr[n]->parameters);
}

char *get_ijth_avsoutput_femname( i,j )
     int i,j;
{
  if(i <0 || i >= avsoutputs) {
    SystemAbort("Too big number for get_ijth_avsoutput_femname[i]");
  }
  if(j < 0 || j >= avsoutput_ptr[i]->parameters){
    SystemAbort("Too big number for get_ijth_avsoutput_femname[j]");
  }
  return(*(avsoutput_ptr[i]->fem_name +j));
}

void listup_avsoutput_in_main_fp(fp)
     FILE *fp;
{
  int i,j;
  int parameters;
  int  items;
  char *name;
  char **fem_name;
  int avsparams;
  
  uniq_list_init();
  for(i=0;i<avsoutputs;i++) {
    parameters = avsoutput_ptr[i]->parameters;
    fem_name   = avsoutput_ptr[i]->fem_name;
    for(j=0;j<parameters;j++) {
      put_uniq_name(*(fem_name+j));
    }
  }

  items = how_many_uniq_items();
  for(i=0;i<items;i++) {
    name = get_nth_uniq_item(i);
    fprintf(fp,",feel(");
    fprintf(fp,NP_FEM_VAR,name);    /* duplicate is NOT allowed */
    fprintf(fp,")");
  }


  avsparams = how_many_avs_variables();
  for(i=0;i<avsparams;i++) {
    F77(",");
    put_nth_avs_feel_name_fp(fp,i);
  }


  return;
}

void listup_avsoutput_in_sub_fp(fp)
     FILE *fp;
{
  int i,j;
  int parameters;
  char **fem_name;
  int  items;
  char *name;
  int  avsparams;
  
  uniq_list_init();
  for(i=0;i<avsoutputs;i++) {
    parameters = avsoutput_ptr[i]->parameters;
    fem_name   = avsoutput_ptr[i]->fem_name;

    for(j=0;j<parameters;j++) {
      put_uniq_name(*(fem_name+j));
    }
  }

  items = how_many_uniq_items();
  for(i=0;i<items;i++) {
    name = get_nth_uniq_item(i);
    fprintf(fp,",");
    fprintf(fp,FEM_VAR_NAME77,name);    /* duplicate is not allowed */
  }

  avsparams = how_many_avs_variables();
  for(i=0;i<avsparams;i++) {
    F77(",");
    put_nth_avs_feel_name_fp(fp,i);
  }

  return;
}


void listup_avsoutput_declare_fp(fp)
     FILE *fp;
{
  int i,j;
  int parameters;
  char **fem_name;
  int  items;
  char *name;
  int  avsparams;
  int  type;
  
  uniq_list_init();  
  for(i=0;i<avsoutputs;i++) {
    parameters = avsoutput_ptr[i]->parameters;
    fem_name   = avsoutput_ptr[i]->fem_name;


    for(j=0;j<parameters;j++) {
      put_uniq_name(*(fem_name+j));
    }
  }

  items = how_many_uniq_items();
  for(i=0;i<items;i++) {
    name = get_nth_uniq_item(i);
    fprintf(fp,"      real*8 ");
    fprintf(fp,FEM_VAR_NAME77,name);    /* duplicate is allowed */
    fprintf(fp,"(*)\n");
  }

  avsparams = how_many_avs_variables();
  if(avsparams) F77("*\n");
  for(i=0;i<avsparams;i++) {
    type = get_nth_avs_feel_var_type(i);
    switch(type) {
    case INT:
      fprintf(fp,"      integer ");
      break;
    case DOUBLE:
      fprintf(fp,"      real*8 ");
      break;
    default:
      SystemAbort("Illegal type in AVSoutput.c(avs variable declare)");
    }
    put_nth_avs_feel_name_fp(fp,i);
    F77("\n");
  }

  return;
}




