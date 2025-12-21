/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   make_feel_fort77_modulef.c
 *      Date:   1998/11/02
 *   
 *   Purpose:   Making Modulef routine MAIN
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

void make_feel_fort77_modulef()
{

  int nopos;

  /* MAKING FUNDAMENTAL DATA FOR MAKING MODULEF */
  nopos = 1;

  /* Currently nopos must be 1.  To extent to full version  may be difficult */




  rep_proc("goto mf_make_main in make_feel_fort77_modulef");

  if(mf_module_mode) {
    mf_make_module_interface();
  }
  else {

    if(avs_mode) {
      fprintf(stderr,"AVS mode is not made yet.\n");

      /* mf_make_mfAVS(); */
    }
    else {
      mf_mk_feelmf();      /* Make MAIN ROUTINE for Modulef    */
    }

    mf_make_scheme(avs_mode);  /* This makes the real main routine */


    mf_make_library(); /* Make Library Routine for Modulef */


  }


  mf_make_solve_fort77();



  return;
}

  
