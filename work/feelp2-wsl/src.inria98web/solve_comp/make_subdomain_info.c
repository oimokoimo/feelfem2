/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_subdomain_info.c
 *      Date:   1995/12/08
 *   
 *   Purpose:   subdomain文に対する適用
 *   Functions: 関数目的   subdomainに対応した、EDAT番号をつける
 *                         構成するsubdomainのmatno配列を作成する
 *              
 *              subdomain構造体も
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

#include "solve_comp.h"
#include "../mesh_comp/mesh_comp.h"

#include "solve_comp_funcs.h"

int assign_subdomain_edatno( int subdomain_no, int edat_no);

static   int subdomain_patterns = 0;
static   int subdomain_pattern[MAX_SUBDOMAINS][3];

void make_subdomain_info()
{

    int i,j,k;
    int solves,domains,subdomains;

    int subdomain_edatno;
    int subdomain_regions;
    int subdomain_no;
    int *subdomain_region_no;

    int elemg;
    Solve *solve_ptr;
    SolveFORT77 *solve77_ptr;
    SolveElement *solve_element_ptr;
    ElementFORT77 **elem77_ptrptr,*elem77_ptr;
    ElemDat *elem_dat_ptr;

    Domain    *domain_ptr;
    Subdomain *subdomain_ptr;

    char *domain_name;
    char **region_name_ptr;
    char *region_name;



    subdomains = how_many_subdomains();

    if(parallel && subdomains != 0) {
	if(english_mesg) {
	    SystemWarning("subdomain functionality is not supported in parallel version");
	}
	else {
	    SystemWarning("並列処理版ではsubdomainは使用不可");
	}
    }

    domain_ptr  = get_nth_domain_ptr(0);
    domain_name = domain_ptr -> name;
    subdomains = how_many_subdomains();
    for(i=0;i<subdomains;i++) {
	subdomain_ptr = get_nth_subdomain_ptr(i);


	if(subdomain_ptr == NULL) {
	    SystemAbort("NULL for subdomain name(make_subdomain_info)");
	}
	
	/* assign nodeset number for ewise variable */
	subdomain_ptr -> ewise_nset_no = get_new_nodesetno();

	region_name_ptr   = subdomain_ptr -> region_name;
	subdomain_regions = subdomain_ptr -> regions;

	/* assign matno information array in Subdomain structure */
	subdomain_ptr -> region_matno =
	  (int *)FEEL_GetMemory(sizeof(int)*subdomain_regions);

	/* make matno array in subdomain structure */
	for(k=0;k<subdomain_regions;k++) {
	    *(subdomain_ptr->region_matno + k) =
	      get_domain_region_no(domain_name,
				   *(region_name_ptr + k));
	}
	
    }


    solves = how_many_solves();
    for(i=0;i<solves;i++) {

	/* 以下の配列は、本来ならば77以外を使うべきではあるが、
	   付けたし機能の為、直接77構造体に代入している        */
	solve_ptr         = get_nth_solve_ptr(i);
	solve77_ptr       = solve_ptr->solve77_ptr;
	elem77_ptrptr     = solve77_ptr -> elem77_ptrptr;
	elemg             = solve77_ptr -> elemg;

	
	if(elemg != 1) {
	    SystemAbort("make_subdomain_info(elemg is not 1)");
	}

	for(j=0;j<elemg;j++) {
	    /* SolveElementに、subregion名が定義されている*/
	    solve_element_ptr = *(solve_ptr->solve_elem_dat+j);

	    /* 情報はElement77構造体に代入する */
	    elem77_ptr        = *(elem77_ptrptr + j);
	    
	    /* if subdomain is not declared, set subregion_flag */
	    if(solve_element_ptr -> subdomain_name == NULL) {
		elem77_ptr -> subdomain_flag = NO;
		continue;
	    }
	    else { 
		elem_dat_ptr = elem77_ptr -> elem_dat;
		subdomain_no = 
		  get_subdomain_NO_by_name(solve_element_ptr
					   -> subdomain_name);
		subdomain_ptr = get_nth_subdomain_ptr(subdomain_no -1 );

		if(subdomain_no == 0) {
		  SystemAbort("Illegal subdomain NO.(make_subdomain_info)");
		}
		subdomain_edatno = 
		  assign_subdomain_edatno(subdomain_no        ,
					  elem_dat_ptr->edatno);
		
		/* 代表的なsubdomain EDAT集合番号をいれておく */
		subdomain_ptr -> edatno = subdomain_edatno;

		elem77_ptr -> subdomain_flag = YES;
		elem77_ptr -> sub_edat_no = subdomain_edatno;
		subdomain_flag = YES;                /* global flag */
	    }
	}
    }
    return;
}

int assign_subdomain_edatno( subdomain_no, edat_no)
     int subdomain_no;
     int edat_no;
{
    int i;
    int find_flag;
    int new_edat_no;

    find_flag = 0;

    for(i=0;i<subdomain_patterns;i++) {
	if(subdomain_no == subdomain_pattern[i][0] &&
	   edat_no      == subdomain_pattern[i][1]    ) {
	    return (subdomain_pattern[i][2]);
	}
    }

    new_edat_no =  get_new_edatno(); 

    subdomain_pattern[subdomain_patterns][0] = subdomain_no;
    subdomain_pattern[subdomain_patterns][1] = edat_no;
    subdomain_pattern[subdomain_patterns][2] = new_edat_no;

    subdomain_patterns++;

    return(new_edat_no);
}

	    
	

