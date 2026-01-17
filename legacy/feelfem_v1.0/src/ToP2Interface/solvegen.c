/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : This is P2 module to write out solve and solve fort77 Struct.
 *  Date     : 1999/11/25
 *  Modified : 1999/11/25
 *  
 *  Purpose  : 
 *  
 */

#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "../feel_def/basic_struct.h"
#include "../solve_comp/solve_comp.h"

void solveStructWriter( solve_ptr, solve77_ptr)
     Solve       *solve_ptr;
     SolveFORT77 *solve77_ptr;
{
  int i,j;
  int flag;
    
  int solve_no;
    
  int elemg;   /* 要素グループの個数、SolveElementの数 */
  int solve_elements;  /* 上と重複しているが… */
  SolveElement *solve_element_ptr;

  int max_nodes;
  int dconds,nconds;
    
  FILE *fp;
    
  ElementFORT77 **elem77_ptrptr,*elem77_ptr;   
  ElemDat        *elem_dat_ptr;
  DirichletData **d_ptrptr,*d_ptr; 
  NeumannData   **n_ptrptr,*n_ptr;
    
  char fname[30];
  FILE *GetFEELFEMFP();
    
  /* 基本変数コピー */
  solve_no      = solve77_ptr -> solve_no;
  elemg         = solve77_ptr -> elemg;
  solve_elements= solve_ptr   -> solve_elements;
  elem77_ptrptr = solve77_ptr -> elem77_ptrptr;
  max_nodes     = solve77_ptr -> max_nodes;
    
    
  dconds   = solve_ptr -> d_conditions;
  d_ptrptr = solve_ptr -> d_dat;
    
  nconds   = solve_ptr -> n_conditions;
  n_ptrptr = solve_ptr -> n_dat;

  /*-----------------*/
  /* subdomain check */
  /*-----------------*/
  for(i=0;i<elemg;i++) {
    solve_element_ptr = *(solve_ptr->solve_elem_dat + i);
    elem77_ptr = *(elem77_ptrptr + i);
    if(elem77_ptr -> subdomain_flag != NO) {
      fprintf(stderr,"subdomain is not supported now! in solvegen.c\n");
      exit(1);
    }
  }


  fp = GetFEELFEMFP();

  /* LINE : solve number variables */
  fprintf(fp,"%8d   (solve number---SOLVE DATA START)\n",solve_no);


  /* LINE : number of fem variables */
  fprintf(fp,"%8d   (number of fem variables)\n",solve77_ptr->fem_vars);

  /* LINE : name list of fem variables */
  for(i=0;i<solve77_ptr->fem_vars;i++) {
    fprintf(fp,"%s\n",*(solve77_ptr->fem_var_name+i));
  }

  /* LINE : number of ewise variables */
  fprintf(fp,"%8d   (number of ewise variables)\n",solve77_ptr->ewise_vars);

  /* LINE : name list of ewise variables */
  for(i=0;i<solve77_ptr->ewise_vars;i++) {
    fprintf(fp,"%s\n",*(solve77_ptr->ewise_var_name+i));
  }

  /* LINE : number of scalar variables */
  fprintf(fp,"%8d   (number of scalar variables)\n",solve77_ptr->scalar_vars);
  
  /* LINE : name list of ewise variables */
  for(i=0;i<solve77_ptr->scalar_vars;i++) {
    fprintf(fp,"%s\n",*(solve77_ptr->scalar_var_name+i));
  }

  /* LINE : number of element groups */
  fprintf(fp,"%8d   (number of element groups)\n",elemg);

  /* LINE : number of max nodes */
  fprintf(fp,"%8d   (number of max nodes, following is IPD)\n",max_nodes);

  /* LINE : nedtno data */
  elem77_ptr = *(elem77_ptrptr + 0);  /* P2 limit */
  elem_dat_ptr = elem77_ptr->elem_dat;
  fprintf(fp,"%8d   (nedtno data P2 limit only 1)\n",elem_dat_ptr->edatno);


  /* LINE : NENFRE array */
  for(i=0;i<elemg;i++) {
    elem77_ptr = *(elem77_ptrptr + i);
    for(j=0;j<max_nodes;j++) {
      if(j >= elem77_ptr->nodes) {
	F77("0"); continue;
      }
      fprintf(fp,"%d\n",*(elem77_ptr->node_freedom + j));
    }
  }

  /* LINE : number of dirichlet conditions */
  fprintf(fp,"%8d   (= dconds, following, data nsetno/.../)\n",dconds);
  
  if(dconds != 0) {
    for(i=0;i<dconds;i++) {
      d_ptr = *(d_ptrptr + i);
      fprintf(fp,"%d\n",d_ptr->b_nodeset);
    }
  }

  /* LINE : number of neumenn conditions */
  fprintf(fp,"%8d   (= nconds, following, data nbedtno/.../)\n",nconds);
  
  if(nconds != 0) {
    for(i=0;i<nconds;i++) {
      n_ptr = *(n_ptrptr + i);
      fprintf(fp,"%d\n",n_ptr->belem_no);
    }
  }


  /* ecal routine control */
  for(i=0;i<elemg;i++) {
    solve_element_ptr = *(solve_ptr->solve_elem_dat + i);
    elem77_ptr        = *(elem77_ptrptr+i);
    
    fprintf(fp,"elem %d %d\n",solve_no,i+1);
    
    fprintf(fp,"%8d  nonlinear_flag\n",solve_element_ptr->nonlinear_flag);
    fprintf(fp,"%8d  unknowns in case of nonlinear problem\n",
	    solve_element_ptr-> unknowns);
    if(solve_element_ptr -> nonlinear_flag == YES) {
      for(j=0;j<solve_element_ptr->unknowns;j++) {
	fprintf(fp,"%s\n",*(solve_element_ptr->unknown_name+j));
      }
    }

    /* known fem variables */
    fprintf(fp,"%8d  (known fem variables)\n",solve_element_ptr->fem_knowns);
    for(j=0;j<solve_element_ptr->fem_knowns;j++) {
      PUT(fp,"%s\n",*(solve_element_ptr->fem_known_name+j));
    }

    fprintf(fp,"%8d  (known ewise variables)\n",
	    solve_element_ptr->ewise_knowns);
    for(j=0;j<solve_element_ptr->ewise_knowns;j++) {
      fprintf(fp,"%s\n",*(solve_element_ptr->ewise_known_name+j));
    }

    fprintf(fp,"%8d  (scalar variables)\n",solve_element_ptr->scalar_knowns);
    for(j=0;j<solve_element_ptr->scalar_knowns;j++) {
      fprintf(fp,"%s\n",*(solve_element_ptr->
			  scalar_known_name+j));
    }
  }
  /* LINE : number of neumenn conditions */
  fprintf(fp,"%8d   (number of neumannconditions)\n",nconds);
  
  for(i=0;i<nconds;i++) {
    n_ptr = *(n_ptrptr + i);
    fprintf(fp,"%8d   (%dth neumann condition fem_vars)\n",
	    n_ptr -> fem_vars,i+1);
    for(j=0;j<n_ptr -> fem_vars;j++) {
      fprintf(fp,*(n_ptr->fem_var_name + j));
      fprintf(fp,"\n");
    }

   fprintf(fp,"%8d   (%dth neumann condition scalar_vars)\n",
	    n_ptr -> scalar_vars,i+1);
   for(j=0;j<n_ptr->scalar_vars;j++) {
     fprintf(fp,"%s\n",*(n_ptr->scalar_var_name + j));
   }
  }

  /* LINE : number of neumenn conditions */
  fprintf(fp,"%8d   (number of dirichlet conditions)\n",dconds);
  for(i=0;i<dconds;i++) {
    d_ptr = *(d_ptrptr + i);

    fprintf(fp,"%8d   (%dth dirichlet condition fem_vars)\n",
	    d_ptr -> fem_vars,i+1);

    for(j=0;j<d_ptr -> fem_vars;j++) {
      PUT(fp,"%s\n",*(d_ptr->fem_var_name + j));
    }

    fprintf(fp,"%8d   (%dth dirichlet condition scalar_vars)\n",
	    d_ptr -> scalar_vars,i+1);

    for(j=0;j<d_ptr->scalar_vars;j++) {
      fprintf(fp,"%s\n",*(d_ptr->scalar_var_name + j));
    }
  }

  /* unknowns */
  fprintf(fp,"%8d  (unknowns for edev)\n",solve_element_ptr->unknowns);
  for(j=0;j<solve_element_ptr->unknowns;j++) {
    fprintf(fp,"%s\n",*(solve_element_ptr->unknown_name + j));
  }

  fprintf(fp,"owari\n");
  return;
}



  
