/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   main_declare_scalar.c
 *      Date:   1994/01/11
 *   
 *   Purpose:   mainルーチンにおけるスカラー変数の宣言
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../var_comp/var_comp.h"

#include "../parallel/parallel.h"

void main_declare_scalar( fp )
     FILE *fp;
{
    int i;
    int int_vars;
    int double_vars;
    int const_vars;

    Var *var_ptr;

    int_vars    = how_many_int_vars();
    double_vars = how_many_double_vars();
    const_vars  = how_many_const_vars();

    /* 整数変数 */
    for(i=0;i<int_vars;i++) {
	if(i == 0) COM;
	var_ptr = get_nth_int_ptr(i);
	F77("      integer ");
	PUT(fp,SCALAR_VAR_NAME77,var_ptr -> name);
	F77("\n");
    }

    
    /* 実数変数 */
    for(i=0;i<double_vars;i++) {
	if(i == 0) COM;
	var_ptr = get_nth_double_ptr(i);
	F77("      real*8 ");
	PUT(fp,SCALAR_VAR_NAME77,var_ptr -> name);
	F77("\n");
    }

    
    /* 定数変数 */
    for(i=0;i<const_vars;i++) {
	if(i == 0) COM;
	var_ptr = get_nth_const_ptr(i);
	F77("      real*8 ");
	PUT(fp,SCALAR_VAR_NAME77,var_ptr -> name);
	F77("\n");
    }


    if(parallel) {
	COM;
	F77("      integer p_size,p_status(mpi_status_size)\n");
    }

    
    return;
}

    





