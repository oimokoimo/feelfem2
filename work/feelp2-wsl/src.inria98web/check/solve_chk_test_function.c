/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_test_function.c
 *      Date:   1993/10/26
 *              1993/11/09  Make restart
 *   
 *   Purpose:   試験関数を確定させる
 *
 *   Functions: 方程式がDIFFEQ,WEAKEQの場合に試験関数を確定させる。
 *              
 *              自由度が正しいかどうかの検査をする
 *              
 *              
 *              試験関数は指定されている場合は全てを指定すること
 *                全てが指定されている場合、自由度検査を行う
 *               (各solve_elementに対して:要素の重ね合わせでは
 *                全てのSolveElementが同一の未知変数を持つとは限らない)
 *              
 *              未指定はNULLのはず(solve.c)
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"           /* get_elem_name_by_ND()宣言 */
#include "../element/element.h"

solve_chk_test_function()
{
    int i,j,k;
    int solves;
    int solve_elements;
    int unknowns;
    int equations;
    
    int current_err_flag; /* このルーチン内部のエラーフラグ */
    
    int all_null_flag;
    
    int element_freedom;  /* 各SolveElementの自由度 */
    
    int test_freedom;     /* 試験関数の自由度 */
    int unknown_freedom;  /* 未知関数の自由度 */
    
    Solve         *solve_ptr;
    SolveElement  *solve_element_ptr;
    Equation      *eq_ptr;
    
    
    solves = how_many_solves();
    
    for(i=0;i<solves;i++) {
	
	solve_ptr = get_nth_solve_ptr(i);
	
	solve_elements = solve_ptr -> solve_elements;
	
	for(j=0;j<solve_elements;j++) {
	    
	    current_err_flag = NO;    /* エラー時Continueの為のフラグ */
	    
	    solve_element_ptr = *(solve_ptr -> solve_elem_dat + j);
	    equations = solve_element_ptr -> equations;
	    unknowns  = solve_element_ptr -> unknowns;
	    
	    if(equations != unknowns) {
		SystemAbort("現在、solve文とsolve_elementで未知変数が異なる場合は未対応");
	    }
	    
	    
	    /* 指定されている試験関数が定義されているかどうかの検査 */
	    for(k=0;k<equations;k++) {
		eq_ptr = *(solve_element_ptr -> eq_data + k);
		
		/* 試験関数が指定されていない */
		if(eq_ptr->test_function == NULL) continue;
		
		/* 試験関数が指定されている */
		if(get_element_ptr_by_name( eq_ptr -> test_function ) == NULL) {
		    if(english_mesg) {
			SystemError_yy_s("Specified test function type %s is not defined.",eq_ptr->test_function,
					 solve_element_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("指定されている試験関数 %s は未定義",
					 eq_ptr->test_function,
					 solve_element_ptr -> yylineno);
		    }
	    	    current_err_flag = YES; 
		}
	    }
	    if(current_err_flag != NO) continue;  /* 指定されている試験関数が存在せず */
	    
	    /* 試験関数の指定方法に関する検査 */
	    /* 全てを指定、または、全て未指定だけがOK */
	    all_null_flag = YES;

	    for(k=0;k<equations;k++) {
		eq_ptr = *(solve_element_ptr -> eq_data + k);

		/* 試験関数が指定されている */
		if(eq_ptr -> test_function != NULL ) {
		    
		    if(k == 0) {
			all_null_flag = NO;
			continue;
		    }
		    /* 最初の方程式でなく、以前までが未指定なのに
		       試験関数が指定されている                   */
		    if(all_null_flag == YES) {
			if(english_mesg) {
			    SystemError_yy("Not all test function specified.",
					   solve_element_ptr->yylineno);
			}
			else {
			    SystemError_yy("solve文内に試験関数の指定と未指定が混在",solve_element_ptr -> yylineno);
			}
			current_err_flag = YES;
			all_null_flag = NO;
			continue;
		    }
		}
		/* 試験関数が指定されていない */
		else {
		    /* これより前の式で試験関数が指定されている */
		    if(all_null_flag == NO) {
			if(english_mesg) {
			    SystemError_yy("Not all test function specified.",
					   solve_element_ptr->yylineno);
			}
			else {
			    SystemError_yy("solve文内に試験関数の指定と未指定が混在",solve_element_ptr -> yylineno);
			}
			current_err_flag = YES;

		    }	
		}
	    }
	    
	    if(current_err_flag == YES) {
		current_err_flag = NO;
		continue;             /* 各solve_elementループのcontinue */
	    }
	    /* エラー時には
	       試験関数の確定はしない */
	

	    
	    if(all_null_flag == YES) {
		
		/* 全ての試験関数が未指定の場合、
		   SolveElementの未知変数順に試験関数を指定する。
		   dbg: 現在はsolve文の指定をそのまま使っていることに注意
		   また、SolveElement内での未知変数順については仕様未定 */
		
		
		for(k=0;k<equations;k++) {
		    eq_ptr= *(solve_element_ptr -> eq_data + k);
		    eq_ptr->test_function = 
		      get_elem_name_by_ND(*(solve_element_ptr->
					    unknown_name   +     k) ,
					  solve_element_ptr->domain_name);
		    /* 未知関数の部分が今はsolve文の単なるコピー */
		}
	    }
	    else {
		
		/* 試験関数が全て指定されている場合
		   この場合は自由度のチェックのみを行う */
		unknown_freedom = 0;
		test_freedom = 0;
		
		/* まず未知関数の自由度を計る */
		for(k=0;k<unknowns;k++) {
		    unknown_freedom = unknown_freedom +
		      get_fem_var_freedom_by_ND(*(solve_element_ptr->
						  unknown_name   +     k) ,
						solve_element_ptr->domain_name);
		    
		}
		
		/* 試験関数の自由度を計る */
		for(k=0;k<equations;k++) {
		    eq_ptr= *(solve_element_ptr -> eq_data + k);
		    test_freedom = test_freedom +
		      get_freedom_by_element_name(eq_ptr->test_function);
		}
		
/*		FDBGWRT(stderr,"unknown freedom = %d (%d) test freedom = %d\n",
			unknown_freedom,unknowns,test_freedom);
*/
		
		if(unknown_freedom != test_freedom ) {
		    if(english_mesg) {
			SystemError_yy("Trial space degree of freedom doesn't match test space degree of freedom.",
				       solve_element_ptr->yylineno);
		    }
		    else {
			SystemError_yy("要素内の試験関数の自由度と未知変数の自由度が不一致",
				       solve_element_ptr->yylineno);
		    }
		}
	    }      /* all_null or not */
	}          /* solve_elements  */
    }              /* solves          */
    
    return;
}


