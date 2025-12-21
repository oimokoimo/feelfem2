/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_solv_dat.c
 *      Date:   2000/04/26
 *
 *   Purpose:   Make 'solv_dat' problem specification file
 *              
 *              
 * PROB    (the begining of problem definition)
 * 
 * MEDT    (keyword for main EDAT number)
 * 1
 * 
 * REDT    (Regional Edats)
 * 2
 * dddd dddd    (EDAT number list)
 * 
 * BEDT    (Boundary Edats)
 * n
 * dddd dddd    (EDAT number list)
 * 
 * 
 * SLVS    (Number of solve data)
 * 1
 * 
 * SOLV
 * 1       (Solve number)
 * edatno  (EDAT Number)
 * n       (Number of Boundary-EDATs)
 * m       (Number of Boundary-NSETs)
 * xxxxxx  (B-EDAT list)
 * xxxxxx  (B-NSET list)
 * 
 * ENDE    (True end of file)
 * 
 * 
 *
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"

void make_solv_dat( )
{
    int i,j,k;
    int solves;
    int dconds,nconds;
    int no;

    Solve           *solve_ptr;
    SolveElement    *solve_elem_ptr;
    SolveFORT77     *solve77_ptr;

    ElementFORT77 **elem77_ptrptr,*elem77_ptr;
    ElemDat        *elem_dat_ptr;
    
    DirichletData   *dcond_ptr,**dcond_ptrptr;
    NeumannData     *ncond_ptr,**ncond_ptrptr;


    FILE *fp;

    int no_edat,no_nset;

    int region_edats;
    int boundary_edats;
    int region_edat_lst[MAX_EDATSET];
    int boundary_edat_lst[MAX_EDATSET];
    

    rep_proc("Start of make_solv_dat");

    solves = how_many_solves();

    if(solves == 0) {
	SystemWarning("No solve statement.");
	return;    
    }

    region_edats   = 0;
    boundary_edats = 0;



    for(i=0;i<solves;i++) {

/*      fprintf(stderr,"\ni=%d\n",i); */
      

	solve_ptr   = get_nth_solve_ptr(i);
	solve77_ptr = solve_ptr->solve77_ptr;
	elem77_ptrptr = solve77_ptr ->elem77_ptrptr;
	elem77_ptr    = *(elem77_ptrptr+0);
	elem_dat_ptr  = elem77_ptr -> elem_dat;
	
	dconds       = solve_ptr -> d_conditions;
	dcond_ptrptr = solve_ptr -> d_dat;
	
	nconds       = solve_ptr -> n_conditions;
	ncond_ptrptr = solve_ptr -> n_dat;

/*	fprintf(stderr,"dconds= %d    nconds=%d\n",dconds,nconds); */
	
	
	if(elem77_ptr->subdomain_flag == YES) {
	  SystemWarning("solv_dat does not support subdomain");
	}

	no_edat =  elem_dat_ptr->edatno;


/*	fprintf(stderr,"Region edat=%d\n",no_edat); */
	
/*	fprintf(stderr,"region edats=%d\n",region_edats); */
	

	for(j=0;j<region_edats;j++) {
	  if(region_edat_lst[j] == no_edat) no_edat = 0;
	}

	if(no_edat != 0) {
	  
/*	  fprintf(stderr,"Register EDAT no. %d\n",no_edat); */

	  region_edat_lst[region_edats] = no_edat;
	  region_edats++;
	}

	/* fprintf(stderr,"goto nconds section (nconds = %d)\n",nconds); */
	
	for(j=0;j<nconds;j++) {
	  ncond_ptr = *(ncond_ptrptr+j);
	  no_edat = ncond_ptr->belem_no;

/*	  fprintf(stderr,"no_edat(ncond) =%d\n",no_edat); */
	  
/*	  fprintf(stderr,"boundary_edats=%d\n",boundary_edats); */
	  

	  for(k=0;k<boundary_edats;k++) {
	    if(boundary_edat_lst[k] == no_edat) no_edat= 0;
	  }

	  if(no_edat == 0) {
	    SystemWarning("OKashii ne-");
	  }
	  else {
	    boundary_edat_lst[boundary_edats] = no_edat;
	    boundary_edats ++;
	  }
	}
    }
    
/*    fprintf(stderr,"goto open file\n"); */
    

    fp = fopen("solv_dat","w");
    if(fp == NULL) {
      SystemAbort("Cannot open solv_dat to write");
    }

    fprintf(fp,"PROB\n");

    /* MEDT */
    fprintf(fp,"MEDT\n");
    fprintf(fp,"%8d\n",1);

    /* REDT */
    fprintf(fp,"REDT\n");
    fprintf(fp,"%8d\n",region_edats);
    for(i=0;i<region_edats;i++) {
      if(i >0 && i % 8 == 0) fprintf(fp,"\n");
      fprintf(fp,"%8d",region_edat_lst[i]);
    }
    fprintf(fp,"\n");

    /* BEDT */
    fprintf(fp,"BEDT\n");
    fprintf(fp,"%8d\n",boundary_edats);
    for(i=0;i<boundary_edats;i++) {
      if(i >0 && i % 8 == 0) fprintf(fp,"\n");
      fprintf(fp,"%8d",boundary_edat_lst[i]);
    }
    if(boundary_edats>0) {  
      fprintf(fp,"\n");    
    }

    /* SLVS */
    fprintf(fp,"SLVS\n");
    fprintf(fp,"%8d\n",solves);
    

    for(i=0;i<solves;i++) {
	solve_ptr   = get_nth_solve_ptr(i);
	solve77_ptr = solve_ptr->solve77_ptr;
	elem77_ptrptr = solve77_ptr ->elem77_ptrptr;
	elem77_ptr    = *(elem77_ptrptr+0);
	elem_dat_ptr  = elem77_ptr -> elem_dat;
	
	dconds       = solve_ptr -> d_conditions;
	dcond_ptrptr = solve_ptr -> d_dat;
	
	nconds       = solve_ptr -> n_conditions;
	ncond_ptrptr = solve_ptr -> n_dat;


	fprintf(fp,"SOLV\n");
	fprintf(fp,"%8d     (Solve Number)\n",i+1);
	
	no_edat =  elem_dat_ptr->edatno;

	fprintf(fp,"%8d     (EDAT Number)\n",no_edat);
	fprintf(fp,"%8d     (Boundary EDAT)\n",nconds);
	fprintf(fp,"%8d     (Boundary NSET)\n",dconds);
	
	for(j=0;j<nconds;j++) {
	  ncond_ptr = *(ncond_ptrptr+j);
	  no_edat = ncond_ptr->belem_no;
	  
	  if(j>0 && j % 8 == 0) fprintf(fp,"\n");
	  fprintf(fp,"%8d",no_edat);
	}
	if(nconds >0) fprintf(fp,"\n");


	for(j=0;j<dconds;j++) {
	  dcond_ptr = *(dcond_ptrptr+j);
	  no_nset = dcond_ptr->b_nodeset;
	  
	  if(j>0 && j % 8 == 0) fprintf(fp,"\n");
	  fprintf(fp,"%8d",no_nset);
	}
	if(dconds >0) fprintf(fp,"\n");
    }

    fclose(fp);
    

    rep_proc("End of make_solv_dat");
    return;
}

