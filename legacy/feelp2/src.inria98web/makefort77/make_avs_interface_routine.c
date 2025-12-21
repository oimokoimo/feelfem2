/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_avs_interface_routine.c
 *      Date:   1998/09/03
 *   
 *   Purpose:   make interface function with AVS/Express
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

void make_avs_interface_routine(fp)
     FILE *fp;
{
  int i;
  int avsvariables;
  int type;
  

  PUT(fp,"      integer function %s(UCD_id,event_mask,seq_num)\n",
      DEFAULT_AVS_MODULENAME );
  COM;
 
  /* Include files */
  F77("* Include statements may need to be modified\n");
  COM;

  F77("      include 'avs/omf.inc'\n");
  F77("      include 'avs/fldf.inc'\n");
  COM;

  F77("      integer UCD_id(OIDSIZ),event_mask,seq_num\n");
  COM;

  F77("* avsint,avsdoulbe variables\n");
  avsvariables = how_many_avs_variables();
  for(i=0;i<avsvariables;i++) {
    put_nth_avs_feel_declare_fp(fp,i);
  }
  if(avsvariables) { F77("*\n"); }

  F77("* Get input values\n");

  /* meshonly option */
  F77("      if(OMFget_name_int_val(UCD_id,\n");
  F77("     $   OMFstr_to_name('meshonly'),meshonly) .NE. 1 )\n");  
  F77("     $   meshonly = 0\n");
  F77("*\n");


  for(i=0;i<avsvariables;i++) {
    type = get_nth_avs_feel_var_type(i);
    switch(type) {
    case INT:
      F77("      if(OMFget_name_int_val(UCD_id,\n");
      F77("     $   OMFstr_to_name('");
      put_nth_avs_real_name_fp(fp,i);
      F77("'),");
      put_nth_avs_feel_name_fp(fp,i);
      F77(") .NE.1 ) ");
      put_nth_avs_feel_name_fp(fp,i);
      F77("=");
      put_nth_avs_initial_val_fp(fp,i);
      F77("\n");
      break;

    case DOUBLE:
      F77("      if(OMFget_name_real8_val(UCD_id,\n");
      F77("     $   OMFstr_to_name('");
      put_nth_avs_real_name_fp(fp,i);
      F77("'),");
      put_nth_avs_feel_name_fp(fp,i);
      F77(") .NE.1 ) ");
      put_nth_avs_feel_name_fp(fp,i);
      F77("=");
      put_nth_avs_initial_val_fp(fp,i);
      F77("\n");
      break;

    default:
      SystemAbort("Illegal var type in make_avs_interface_routine");
    }
  }

  F77("*----------------------------------\n");
  F77("* call feel main routine\n");
  F77("*----------------------------------\n");
  F77("      call feel_main(UCD_id,event_mask,seq_num,OIDSIZ,meshonly");
  for(i=0;i<avsvariables;i++) {
    F77(",");
    put_nth_avs_feel_name_fp(fp,i);
  }
  F77(")\n");
  COM;

  PUT(fp,"      %s = 1\n", DEFAULT_AVS_MODULENAME );
  F77("      return\n");
  F77("      end\n");

  return;
}






  








