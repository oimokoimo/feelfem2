/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   ctrl77_subdomain.c
 *      Date:   1995/12/15
 *   
 *   Purpose:   subdomain expansion
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"

void ctrl77_subdomain(fp,elemg,solve_ptr,elem77_ptrptr)
     FILE *fp;
     int elemg;
     Solve *solve_ptr;
     ElementFORT77 **elem77_ptrptr;
{
    int i;
    SolveElement   *solve_element_ptr;
    ElementFORT77  *elem77_ptr;
    Subdomain      *subdomain_ptr;
    
    int nset_no;

    for(i=0;i<elemg;i++) {
	solve_element_ptr = *(solve_ptr->solve_elem_dat + i);
	elem77_ptr = *(elem77_ptrptr + i);
	
	if(elem77_ptr -> subdomain_flag == NO) continue;
	
	subdomain_ptr = get_subdomain_ptr_by_name(solve_element_ptr->
						  subdomain_name);
	nset_no = subdomain_ptr -> ewise_nset_no;
	
	F77("c ---------------------------------------\n");
	PUT(fp,"c SUBDOMAIN [%s] ewise-nodeset\n",subdomain_ptr->name);
	F77("c ---------------------------------------\n");
	PUT(fp,"      nodes = n_nset(%d,1)\n",nset_no);
	PUT(fp,"      np    = n_nset(%d,2)\n",nset_no);
	PUT(fp,"      call f_alloc(np_subewise%d,'ewise subdomain',",i+1);
	PUT(fp,"nodes*np,0,0)\n");
	PUT(fp,"      iunit = %d + io_node - 1\n",nset_no);
	PUT(fp,"      call get_inset(iunit,feel(np_subewise%d),nodes,np)\n",i+1);
	F77("c ---------------------------------------\n");
    }
    return;
}	
	    
