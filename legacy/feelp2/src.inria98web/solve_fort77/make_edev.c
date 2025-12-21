/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_edev.c
 *      Date:   1993/11/23(祝)
 *              1996/05/16 並列版拡張
 *   
 *   Purpose:   連立一次方程式解を要素毎にfem変数に分解する(スカイライン法)
 *   Functions: 
 *              
 *              このプログラムもエルミート拡張時に変更が必要
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../parallel/parallel.h"

#include "../solve_comp/solve_comp.h"


void make_edev( solve_no, elem_no , solve_element_ptr )
     int solve_no;
     int elem_no;
     SolveElement *solve_element_ptr;
{
    int i,j;

    ElementFORT77 *elem77_ptr;
    FEMvarinfo   **fem_varinfo_ptrptr;
    FEMvarinfo    *fem_varinfo_ptr;
    int fem_vars;

    char *var_name;
    int freedom;


    char fname[80];
    FILE *fp;

    /* 各種変数設定 */
    elem77_ptr = solve_element_ptr -> elem77_dat;

    fem_varinfo_ptrptr = elem77_ptr-> fem_var_info_ptrptr;
    fem_vars           = elem77_ptr-> fem_vars;
    

    /* ファイルオープン */
    sprintf(fname,ELEM_DEV_FNAME,solve_no,elem_no);

    StoreMakefile( fname ,USER_LIBRARY);
    fp = OpenFileToWrite( fname );

    
    F77("      subroutine ");
    PUT(fp,ELEM_DEV_NAME,solve_no, elem_no );
    F77("(VFG,IPD,ielem,");

    /* 並列版拡張 */
    if(parallel) {  F77("nloglo,"); }

    F77("nelem,np");

    /* 並列版拡張 */
    if(parallel) {  F77(",npmaxsub"); }


    /* fem未知変数 */
    for(i=0;i<solve_element_ptr->unknowns;i++) {
	F77(",");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name+i));
    }

    F77(")\n");

    /*==========*/
    /* 定形宣言 */
    /*==========*/
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);
    COM;

    F77("      dimension VFG(*),IPD(*)\n");
    F77("      dimension ielem(np,nelem)\n");
    
    /* 並列版拡張 */
    if(parallel) {
	F77("      dimension nloglo(npmaxsub)\n");
    }

    for(i=0;i<solve_element_ptr->unknowns;i++) {
	F77("      dimension ");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name+i));
	F77("(*)\n");
    }

    COM;    

    for(i=0;i<solve_element_ptr->unknowns;i++) {
	var_name = *(solve_element_ptr->unknown_name + i);
	fem_varinfo_ptr = get_femvarinfo(var_name,fem_varinfo_ptrptr,fem_vars);
	
	freedom = fem_varinfo_ptr -> freedom;

	/* 小行列←→局所節点番号 */
	PUT(fp,"      dimension  ienp_%s(%d)\n",var_name,freedom); 

	/* 自由度のdenstination   */
	PUT(fp,"      dimension  iedp_%s(%d)\n",var_name,freedom); 
    }
    

    
 
    COM;

    for(i=0;i<solve_element_ptr->unknowns;i++) {
	var_name = *(solve_element_ptr->unknown_name + i);
	fem_varinfo_ptr = get_femvarinfo(var_name,fem_varinfo_ptrptr,fem_vars);
	freedom = fem_varinfo_ptr -> freedom;

	PUT(fp,"      data ienp_%s/ ",var_name);
        
	for(j=0;j<freedom;j++) {
	    if(j == 0) {
		PUT(fp,"%d",*(fem_varinfo_ptr->ienp+j));
	    }
	    else {
		PUT(fp,",%d",*(fem_varinfo_ptr->ienp+j));
	    }
	}
	F77("/\n");	

	PUT(fp,"      data iedp_%s/ ",var_name);
        
	for(j=0;j<freedom;j++) {
	    if(j == 0) {
		PUT(fp,"%d",*(fem_varinfo_ptr->iedp+j));
	    }
	    else {
		PUT(fp,",%d",*(fem_varinfo_ptr->iedp+j));
	    }
	}
	F77("/\n");	
    }

    comment1(fp);

    COM;

    F77("      do 100 i=1,nelem\n");

    for(i=0;i<solve_element_ptr->unknowns;i++) {
	var_name = *(solve_element_ptr->unknown_name + i);
	fem_varinfo_ptr = get_femvarinfo(var_name,fem_varinfo_ptrptr,fem_vars);
	freedom = fem_varinfo_ptr -> freedom;

	COM;
	PUT(fp,"      do %d j=1,%d\n",110+i,freedom);
	PUT(fp,"      ");
	PUT(fp,FEM_VAR_NAME77,var_name);

	/* 並列版拡張 */
	if(parallel) {
	    PUT(fp,"(nloglo(ielem(ienp_%s(j),i))) = VFG(IPD(ielem(ienp_%s(j),i))+iedp_%s(j))\n",
		var_name,var_name,var_name);
	}
	else {
	    PUT(fp,"(ielem(ienp_%s(j),i)) = VFG(IPD(ielem(ienp_%s(j),i))+iedp_%s(j))\n",
		var_name,var_name,var_name);
	}
	PUT(fp,"%5d  continue\n",110+i);
    }
    
    comment1(fp);

    F77("  100 continue\n");
	
    COM;
    F77("      return\n");
    F77("      end\n");
    
    CloseFile(fp);

    return;
}
