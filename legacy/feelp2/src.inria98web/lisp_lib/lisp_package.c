/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   lisp_package.c
 *      Date:   1993/11/30
 *   
 *   Purpose:   send LISP execution source to pipe
 *   Functions: many functions below....
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

lisp_package( fp )
     FILE *fp;
{
    lisplib_diff( fp );
    lisplib_diff_fmla_m( fp );
    lisplib_do_d_formula( fp );
    lisplib_fs_dep( fp );
    lisplib_fs_term_bind( fp );
    lisplib_fs_sort( fp );
    lisplib_expand( fp );
    lisplib_fs( fp );
    lisplib_make_fem_term_list( fp );
    lisplib_make_linear_integrand( fp );
    lisplib_make_linear_weak( fp );
    lisplib_make_load_integrand( fp );
    lisplib_make_num_int_matrix_dat( fp );
    lisplib_make_num_integral( fp );
    lisplib_make_num_integral_term( fp );
    lisplib_minus_convert( fp );
    lisplib_replace_string( fp );
    lisplib_replace_test_func( fp );
    lisplib_symbol_eval_replace( fp );
    lisplib_trans_num_int_integrand( fp ); 
    lisplib_exp_print( fp );
}

