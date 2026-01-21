/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   main_subdomain.c
 *      Date:   1995/12/14
 *   
 *   Purpose:   mainルーチンでsubdomain拡張時のデータファイル作成プログラムの
 *              呼び出し
 *   Functions:
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"


#include "../solve_comp/solve_comp.h"
#include "../mesh_comp/mesh_comp.h"

void main_subdomain(fp)
     FILE *fp;
{
    int i,j;
    int solves;
    int elemg;

    int subdomains;
    int subdomain_no;
    int NSET_no;
    int regions;
    int *region_matno;

    Solve *solve_ptr;
    SolveFORT77 *solve77_ptr;
    SolveElement *solve_element_ptr;
    ElementFORT77 **elem77_ptrptr,*elem77_ptr;
    ElemDat *elem_dat_ptr;
    Subdomain *subdomain_ptr;


    if(subdomain_flag == NO) return;    /* do nothing 
		        		   if subdomain is not used */

    /*====================*/
    /* Make ewise NODESET */
    /*====================*/
    subdomains = how_many_subdomains();
    for(i=0;i<subdomains;i++) {
	subdomain_ptr = get_nth_subdomain_ptr(i);
	NSET_no = subdomain_ptr->ewise_nset_no;
	PUT(fp,"*---------------------------------------------\n");
	PUT(fp,"* Make ewise subdomain NSET data for[%s]\n",
	    subdomain_ptr->name);
	PUT(fp,"*---------------------------------------------\n");

	regions = subdomain_ptr -> regions;
	region_matno = subdomain_ptr->region_matno;
	for(j = 0; j< regions;j++) {
	    PUT(fp,"      matnos(%d)=%d\n",j+1,*(region_matno+j));
	}
	PUT(fp,"      mats     = %d\n",regions);
	/* 次のEDAT集合から作る */
	PUT(fp,"      neg_org  = 1\n");
	    /* 次のNSET集合を新たに作る */
	PUT(fp,"      nset_no  = %d\n",NSET_no);
	PUT(fp,"      call mk_subdomain_nset");
	PUT(fp,"(feel,neg_org,nset_no,mats,matnos)\n");
    }

    /*===============*/
    /* Make EDAT set */
    /*===============*/
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
	    elem_dat_ptr      = elem77_ptr -> elem_dat;
	    
	    /* if subdomain is not declared, set subregion_flag */
	    if(elem77_ptr -> subdomain_flag == NO) continue;

	    subdomain_no   = 
	      get_subdomain_NO_by_name(solve_element_ptr->subdomain_name);
	    subdomain_ptr  =
	      get_nth_subdomain_ptr(subdomain_no-1);
	    
	    PUT(fp,"*-----------------------------------\n");
	    PUT(fp,"* set for subregion [%s]\n",subdomain_ptr->name);
	    PUT(fp,"*-----------------------------------\n");
	    
	    regions = subdomain_ptr -> regions;
	    region_matno = subdomain_ptr->region_matno;
	    
	    for(j = 0; j< regions;j++) {
		PUT(fp,"      matnos(%d)=%d\n",j+1,*(region_matno+j));
	    }
	    PUT(fp,"      mats     = %d\n",regions);
	    /* 次のEDAT集合から作る */
	    PUT(fp,"      neg_org  = %d\n",elem_dat_ptr -> edatno);
	    /* 次のEDAT集合を新たに作る */
	    PUT(fp,"      neg      = %d\n",elem77_ptr -> sub_edat_no);
	    PUT(fp,"      call mk_subdomain_edat");
	    PUT(fp,"(feel,neg_org,neg,mats,matnos)\n");
	}
    }

    PUT(fp,"      call report('SUBDOMAIN PREPARATION COMPLETE')\n");
    return;
}



