/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_gotolabel_check.c
 *      Date:   1993/07/05
 *   
 *   Purpose:   goto文、label文の対応を検査し、行番号を割り振る
 *              
 *   Functions: solveブロック以外では関数部分もこのプログラム中から
 *              作成プログラムを呼び出す。
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../scheme_comp/scheme_comp.h"
#include "../system/system.h"

scheme_gotolabel_check()
{
    int i,j;
    int schemes;
    int ok_flag;
    
    int line_number;

    Scheme *scheme_ptr;
    Label  *label_ptr;
    Goto   *goto_ptr;

    schemes = how_many_schemes();
    line_number = LINENO_FOR_GOTO;
    
    duplicate_init();

    /* label文への行番号の割り当て */
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);

	if(scheme_ptr->type != LABEL) continue;
	
	label_ptr = (Label *)scheme_ptr->ptr;
	duplicate_push( label_ptr->label );    /* 重複チェックプログラムに
						 名前を登録               */

	label_ptr -> line_no = line_number;
	line_number += LINENO_FOR_GOTO_STEP;
    }

    /* 重複定義のチェック */
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);
	if(scheme_ptr->type != LABEL) continue;
	
	label_ptr = (Label *)scheme_ptr->ptr;

	if(is_duplicate( label_ptr->label )) {
	    if(english_mesg) {
		SystemError_s("label %s is duplicated.",label_ptr->label);
	    }
	    else {
		SystemError_s("label名%sが重複して定義されています。",
			      label_ptr->label);
	    }

	}
    }

    /* goto文への行番号の割り当て */
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);
	if(scheme_ptr->type != GOTO) continue;

	goto_ptr = (Goto *)scheme_ptr->ptr;
	ok_flag  = NO;
	
	for(j=0;j<schemes;j++) {
	    scheme_ptr = get_nth_scheme_struct(j);
	    if(scheme_ptr->type != LABEL) continue;

	    label_ptr = (Label *)scheme_ptr->ptr;

	    if(streq(label_ptr->label,goto_ptr->label)) {
		goto_ptr->line_no = label_ptr -> line_no;
		ok_flag = YES;
		break;
	    }
	}

	if(ok_flag == NO) {
	    if(english_mesg) {
		SystemError_s("No corresponding label for goto %s.",
			      goto_ptr->label);
	    }
	    else {
		SystemError_s("goto %sに対応するlabel文が定義されていません.",
			      goto_ptr->label);
	    }

	}
    }

    return;
}
