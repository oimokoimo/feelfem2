/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_make_solve_fort77.c
 *      Date:   1998/11/02
 *   
 *   Purpose:   Make solve routine with Modulef DS
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../../solve_comp/solve_comp.h"

void mf_make_solve_fort77()
{
  int i,j;
  int solves;
  int dconds,nconds;
  int no;

  Solve           *solve_ptr;
  SolveElement    *solve_elem_ptr;
  SolveFORT77     *solve77_ptr;
  int etype;
    
  DirichletData   *dcond_ptr,**dcond_ptrptr;
  NeumannData     *ncond_ptr,**ncond_ptrptr;

  solves = how_many_solves();

  if(solves == 0) {
    SystemWarning("solve文が指定されていません");
    return;    
  }

  /* get etype information */
  
  solve_ptr      =   get_nth_solve_ptr( 0 );
  solve_elem_ptr = *(solve_ptr->solve_elem_dat + 0);
  etype          =   solve_elem_ptr->etype;

  /*==========================*/
  /* LISP Program execution   */
  /*                          */
  /* CAUTION: This is SAME    */
  /*==========================*/
  FDBGWRT(stderr,"LISP procedures start ...");

  rep_proc("make_solve_lisp");
  make_solve_lisp();                 /* in solve_fort77 main directory */

  FDBGWRT(stderr,"done\n");

  /* make_solve_lisp() 内で確定するデータ要素
       
     ElementFORT77->quad_methods   積分法の数  を設定

  */

  /*==========================*/
  /* subroutine data generate */
  /*  (SAME AS ORIGINAL FEEL) */
  /*==========================*/

  rep_proc("make_solve77_data");
  make_solve77_data(); 

  /*===================================*/
  /* Generate Library control routines */
  /*                                   */
  /*     PNRAID                        */
  /*     PNSECM                        */ 
  /*                                   */
  /*     DOBPER                        */
  /*===================================*/
  rep_proc("mf_mk_pnraid");
  mf_mk_pnraid(solves);


  rep_proc("mf_mk_dobper");
  mf_mk_dobper(solves,etype);  /* in this function , etype is assumed to be just one type */





  /* 1: Generate numerical integration data
   */
  /*===========================*/
  /* Generate solve subroutine */
  /*                           */
  /*  SOLVE STATEMENT LOOP     */
  /*===========================*/
  for(i=0;i<solves;i++) {
    rep_proc_no("make solve routine",i+1);

    solve_ptr = get_nth_solve_ptr(i);

    solve77_ptr = solve_ptr->solve77_ptr;

    /* GENERATE solveXX.f */
    if(solve_ptr -> nonlinear_flag == NO) {

      /* In Modulef, there is no change in this stage */
      rep_proc("mf_make_solve_ctrl77");
      mf_make_solve_ctrl77( solve_ptr , solve77_ptr );
    }
    else {
      /* Nonlinear */
      fprintf(stderr,"Nonlinear problem BY Modulef (Not yet) \n");
    }

    /* GENERATE solveXXmaco.f  */
    rep_proc("mf_mk_solve_maco");
    mf_mk_solve_maco(solve_ptr, solve77_ptr );


    /* GENERATE solveXXmili.f  */
    rep_proc("mf_mk_solve_mili");
    mf_mk_solve_mili(solve_ptr, solve77_ptr ); 

    rep_proc("mf_mk_milieu");
    mf_mk_milieu(solve_ptr, solve77_ptr ); 


    /* GENERATE solveXXtae.f  */
    rep_proc("mf_mk_solve_tae ");
    mf_mk_solve_tae (solve_ptr, solve77_ptr );

    /* GENERATE prs00X.f      */
    rep_proc("mf_mk_elem_pr");
    mf_mk_elem_pr( solve_ptr, solve77_ptr);



  }  /* LOOP i for solve state ment */

  return;
}
