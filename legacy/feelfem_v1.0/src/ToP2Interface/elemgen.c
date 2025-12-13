/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : elemgen.c
 *  Date     : 1999/12/14
 *  Modified : 1999/12/14
 *  
 *  Purpose  : element data output routine
 *  
 */


#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"

FILE *GetFEELFEMFP();

void elemgen( no , solve_element_ptr )
     int no;                         
     SolveElement *solve_element_ptr;
{
    int i,j;

    ElementFORT77 *elem77_ptr;
    int            solve_no;
    int            equations;
    int            solve_element_unknowns;
    int            freedom;
    int            nodes;                /* 要素内節点数 */
    int            tmp;
    int            dimension;
    Equation      *eq_ptr;
    FEMvarinfo   **fem_varinfo_ptrptr;
    FEMvarinfo    *fem_varinfo_ptr;
    ElemDat       *elem_dat_ptr;
    EWISE_type    *ewise_type_ptr;
    char          *var_name;
    char          *domain_name;
    char         **chaptrptr;
    
    char fname[BUFSIZ];

    FILE *fp;


    elem77_ptr = solve_element_ptr -> elem77_dat;
    solve_no   = solve_element_ptr -> solve_no;
    solve_element_unknowns = solve_element_ptr -> unknowns;
    elem_dat_ptr = elem77_ptr->elem_dat;

    dimension = what_dimension();
    domain_name = solve_element_ptr -> domain_name;

    nodes = elem_dat_ptr -> nodes;


    fp = GetFEELFEMFP();

    equations = solve_element_ptr -> equations; 
    

    fprintf(fp,"*** elem data ***\n");
    fprintf(fp,"%4d%4d  solveNo,elemNo\n",solve_no,no);
    
    fprintf(fp,"%8d  nonlinear flag\n",solve_element_ptr->nonlinear_flag);

    if(solve_element_ptr->nonlinear_flag == YES) {
      fprintf(fp,"%8d  unknowns\n",solve_element_unknowns);
      for(i=0;i<solve_element_unknowns;i++) {
	fprintf(fp,"%s\n",*(solve_element_ptr ->unknown_name+i));
      }
    }
    else {
      fprintf(fp,"0   unknowns\n");
    }
    
    fprintf(fp,"%8d  fem knowns\n",solve_element_ptr->fem_knowns);
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	PUT(fp,"%s\n",*(solve_element_ptr->fem_known_name+i));
    }

    fprintf(fp,"%8d  ewise knowns\n",solve_element_ptr->ewise_knowns);
    for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
	PUT(fp,"%s\n",*(solve_element_ptr->ewise_known_name+i));
    }

    fprintf(fp,"%8d  scalar knowns\n",solve_element_ptr->scalar_knowns);
    for(i=0;i<solve_element_ptr->scalar_knowns;i++) {
	PUT(fp,"%s\n",*(solve_element_ptr->scalar_known_name+i));
    }    

    if(elem77_ptr -> subdomain_flag != NO) {
      fprintf(stderr,"Now subdomain is not supported to feelfem interface.\n");
      exit(1);
    }

    fprintf(fp,"%8d  NDF\n",elem77_ptr->elem_freedom);

    fprintf(fp,"%8d  quadrature methods\n",elem77_ptr->quad_methods);
    for(i=0;i<elem77_ptr->quad_methods;i++) {
	if(!streq(*(elem77_ptr->quad_name+i) , ANALYTIC_QUAD)) {
	  fprintf(fp,"%8d %s  (points, quadrature name)\n",
		  get_quad_nodes_by_name(*(elem77_ptr->quad_name + i)),
		  *(elem77_ptr->quad_name + i));
	}
    }

    
    fprintf(fp,"%8d  (NDF again for ienp)\n",elem77_ptr->elem_freedom);

    fem_varinfo_ptrptr = elem77_ptr -> fem_var_info_ptrptr;
    for(i=0;i<solve_element_unknowns;i++) {
	var_name = *(solve_element_ptr->unknown_name + i);
	tmp  = NO;   
	
	for(j=0;j<elem77_ptr->fem_vars;j++) {
	    fem_varinfo_ptr = *(fem_varinfo_ptrptr + j);

	    if(streq(var_name , fem_varinfo_ptr -> fem_var_name) ) {
		tmp = YES;
		break;
	    }
	}

	if(tmp == NO) {
	    SystemAbort("該当するFEMvarinfo構造体が不明[ienp](elem_fort77_main)");
	}
	
	freedom = fem_varinfo_ptr -> freedom;
	for(j=0;j<freedom;j++) {
	    if(j == 0) {
		PUT(fp,"%d\n",*(fem_varinfo_ptr->ienp+j));
	    }
	    else {
		PUT(fp,"%d\n",*(fem_varinfo_ptr->ienp+j));
	    }
	}
    }



    fprintf(fp,"%8d  (NDF again for iedp)\n",elem77_ptr->elem_freedom);
    fem_varinfo_ptrptr = elem77_ptr -> fem_var_info_ptrptr;
    for(i=0;i<solve_element_unknowns;i++) {

	var_name = *(solve_element_ptr->unknown_name + i);
	tmp  = NO;
	for(j=0;j<elem77_ptr->fem_vars;j++) {

	    fem_varinfo_ptr = *(fem_varinfo_ptrptr + j);

	    if(streq(var_name , fem_varinfo_ptr -> fem_var_name) ) {
		tmp = YES;
		break;
	    }
	}

	if(tmp == NO) {
	    SystemAbort("該当するFEMvarinfo構造体が不明[iedp](elem_fort77_main)");
	}
	
	freedom = fem_varinfo_ptr -> freedom;
	for(j=0;j<freedom;j++) {
	    if(j == 0) {
		PUT(fp,"%d\n",*(fem_varinfo_ptr->iedp+j));
	    }
	    else {
		PUT(fp,"%d\n",*(fem_varinfo_ptr->iedp+j));
	    }
	}
    }
	

    fprintf(fp,"%8d  nodes (for element nodes, calling ecals)\n",nodes);

    if(solve_element_ptr->nonlinear_flag == YES) {
      for(i=0;i<solve_element_ptr -> unknowns;i++) {
	var_name = *(solve_element_ptr->unknown_name+i);
	    
	freedom=get_fem_var_freedom_by_ND( var_name,
					   solve_element_ptr->domain_name);
	fem_varinfo_ptr = get_femvarinfo(var_name,
					 elem77_ptr->fem_var_info_ptrptr,
					 elem77_ptr->fem_vars);

	fprintf(fp,"%d  (arguments/freedom)\n",freedom);
	for(j=0;j<freedom;j++) {
	  PUT(fp,FEM_VAR_NAME77,var_name);
	  PUT(fp,"(ielem(%d,i))\n",*(fem_varinfo_ptr->ienp + j));
	}
      }
    }

    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	var_name = *(solve_element_ptr->fem_known_name + i);
	freedom = get_fem_var_freedom_by_ND(var_name,domain_name);
	fem_varinfo_ptr = get_femvarinfo(var_name,
					 elem77_ptr->fem_var_info_ptrptr,
					 elem77_ptr->fem_vars);

	fprintf(fp,"%d  (arguments/freedom)\n",freedom);
	for(j=0;j<freedom;j++) {
	    PUT(fp,FEM_VAR_NAME77,var_name);
	    PUT(fp,"(ielem(%d,i))\n",*(fem_varinfo_ptr->ienp + j));
	}
    }
    fprintf(fp,"00000000   (end of fem variable)\n");
    
    /* ewise変数の引き数への展開 */
    fprintf(fp,"%8d  (ewise_knowns)\n",solve_element_ptr->ewise_knowns);
    for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
	var_name = *(solve_element_ptr->ewise_known_name + i);
	
	PUT(fp,EWISE_VAR_NAME77,var_name);

	ewise_type_ptr = get_ewise_type_ptr_by_2name(var_name , domain_name);
	
	if(ewise_type_ptr->quadrature != NULL) {
	    /* 数値積分の積分点毎に自由度、ewise変数は２次元配列 */

	    /* subdomain expansion */
	    if(elem77_ptr -> subdomain_flag != NO) {
		F77("(1,isubew(i))");
		fprintf(stderr,"subdom err oimo1\n");
		exit(1);
	    }
	    else {
		F77("(1,i)\n");    
	    }
	}
	else {
	    /* subdomain expansion */
	    if(elem77_ptr -> subdomain_flag != NO) {
		F77("(isubew(i))");
		fprintf(stderr,"subdom err oimo2\n");
		exit(1);

	    }
	    else {
		F77("(i)\n");
	    }
	}
    }

    /* スカラー変数の引き数への展開 */
    fprintf(fp,"%8d  (scalars)\n",solve_element_ptr->scalar_knowns);
    for(i=0;i<solve_element_ptr->scalar_knowns;i++) {
	PUT(fp,SCALAR_VAR_NAME77,*(solve_element_ptr->scalar_known_name + i));
	F77("\n");
    }
    
    fprintf(fp,"owari\n");

    return;
}
