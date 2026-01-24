/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   var_fem_ewise_datmake.c
 *      Date:   1993/06/29
 *   
 *   Purpose:   FEM_type,EWISE_type 構造体より FEM_var,EWISE_var構造体を
 *              作成する。
 */

#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../var_comp/var_comp.h"
#include "../system/system.h"

#include "check.h"

void store_fem_type_2_var( char *name , FEM_type *fem_type_ptr );
void store_fem_type_2_var_add(char *name ,FEM_type *fem_type_ptr );
void store_ewise_type_2_var( char *name , EWISE_type *ewise_type_ptr );
void store_ewise_type_2_var_add( char *name , EWISE_type *ewise_type_ptr );
/*  tree図
 *
 *  |-feel_data_check  [check.c]
 *  |      |
 *  |      |-var_fem_ewise_datmake()
 *
 *  FEM_type,EWISE_type 構造体より FEM_var,EWISE_var構造体を作成する
 */

void var_fem_ewise_datmake()
{
    int i,j,k;
    int no;

    Var *var_ptr;

    int fem_types;
    FEM_var  *fem_ptr;
    FEM_type *fem_type_ptr;

    int ewise_types;
    EWISE_var  *ewise_ptr;
    EWISE_type *ewise_type_ptr;
    

    fem_types   = how_many_fem_types();    
    ewise_types = how_many_ewise_types();

    for(i=0;i<fem_types;i++) {
	
	fem_type_ptr = get_nth_fem_type_ptr(i);

	no = get_fem_var_no_byname(fem_type_ptr->name);

	if(no == NOTHING) {
	    store_fem_type_2_var( fem_type_ptr -> name , fem_type_ptr );
	}
	else {
	    int err_flag;

	    err_flag = NO;

	    var_ptr = get_nth_fem_ptr(no);
	    fem_ptr = (FEM_var *)var_ptr -> val;

	    for(j = 0; j < fem_ptr->basis_types; j++) {
		if(fem_ptr->fem_type_ptr[j]->etype ==
		   fem_type_ptr->etype) {
		    if(english_mesg) {
			SystemError_s("In fem %s, you defined duplicated basis functions.",fem_type_ptr->name);
		    }
		    else {
			SystemError_s("fem %s は同じ要素形状に対して複数の基底関数を宣言している.",fem_type_ptr->name);
		    }
		    err_flag = YES;
		    break;
		}
	    }
	    if(err_flag == NO) {
		store_fem_type_2_var_add(fem_type_ptr->name ,fem_type_ptr );
	    }
	}
    }

/* 次はewise変数について処理する */

    for(i=0;i<ewise_types;i++) {
	ewise_type_ptr = get_nth_ewise_type_ptr(i);

	no = get_ewise_var_no_byname(ewise_type_ptr->name);

	if(no == NOTHING) {
	    store_ewise_type_2_var( ewise_type_ptr -> name , ewise_type_ptr );
	}
	else {
	    int err_flag;

	    err_flag = NO;
	    
	    var_ptr   = get_nth_ewise_ptr(no);
	    ewise_ptr = (EWISE_var *)var_ptr->val;

	    for(j = 0; j < ewise_ptr->ewise_types; j++) {

		printf("ここでは、region名にダブリが無いかどうか調べる。\n");

	    }
	    if(err_flag == NO) {
		store_ewise_type_2_var_add(ewise_type_ptr->name ,ewise_type_ptr );
	    }
	}
    }
	
    
}



