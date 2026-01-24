/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_if_check.c
 *      Date:   1994/02/08
 *  Modified:   1994/12/20  if文に数式が入る様拡張した
 *                          if_check_expressionでは右と左で重複がある
 *   
 *   Purpose:   if文に関する検査
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"

#include "check.h"


static char *sc_name_buf[MAX_VARIABLES];

void if_expression_check(IFblock *if_ptr,Expression *left,Expression *right);

void scheme_if_check()
{
    int i,j;
    int schemes;

    int in_if_flag;
    int in_else_flag;
    int last_if;

    Scheme *scheme_ptr;
    IFblock  *if_ptr;
    
    Expression *right,*left;

    in_if_flag   = 0;
    last_if      = 0;

    schemes = how_many_schemes();
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);
	if_ptr     =(IFblock *)scheme_ptr -> ptr;

	switch( scheme_ptr->type ) {
	  case IF_THEN:
	    last_if = IF_THEN;
	    in_if_flag++;

	    left  = if_ptr -> left;
	    right = if_ptr -> right;

	    if_expression_check(if_ptr,left,right);
	    break;

	  case IF_GOTO:
	    
	    if_ptr->lineno = get_label_lineno( if_ptr->label );
	    if(if_ptr->lineno == 0) {
		if(english_mesg) {
		    SystemError_yy_s("Specified label is undefined in if-goto block.", if_ptr->label,if_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("if goto 文指定のlabel %sは未定義",
				     if_ptr->label,if_ptr->yylineno);
		}

	    }

	    left  = if_ptr -> left;
	    right = if_ptr -> right;

	    if_expression_check(if_ptr,left,right);

	    break;
	    
	  case ELSE:
	    if(in_if_flag <= 0) {
		if(english_mesg) {
		    SystemError_yy("No corresponding if sentence for else.",
				   if_ptr->yylineno);
		}
		else {
		    SystemError_yy("else文に対応するif文がない",
				   if_ptr->yylineno);
		}

	    }
	    else {
		if(last_if == ELSE) {
		    if(english_mesg) {
			SystemError_yy("Duplicated else sentence.",
				       if_ptr->yylineno);
		    }
		    else {
    			SystemError_yy("else文が重複している",
				       if_ptr->yylineno); 
		    }

		}
	    }
	    last_if = ELSE;
	    break;

	  case ENDIF:
	    if(in_if_flag <= 0) {
		
		if(english_mesg) {
		    SystemError_yy("No if sentence corresponding 'else'.",
				   if_ptr->yylineno);
		}
		else {
		    SystemError_yy("else文に対応するif文がない",
				   if_ptr->yylineno);
		}

	    }
	    in_if_flag--;
	    break;
	}
    }
    if(in_if_flag != 0) {
	if(english_mesg) {
	    SystemError("if and endif don't match.");
	}
	else {
	    SystemError("if文とendif文個数が不整合");
	}
    }

    return;
}

int is_number_iikagen( s ) 
     char *s;
{
    if(*s >= '0' && *s <= '9') return(YES);
    return(NO);
}

int is_scalar_var( name )
     char *name;
{
    switch(get_var_kind( name )) {
      case DOUBLE:
      case INT:
      case CONST:
	return(YES);
	
      default:
	return(NO);
    }
}


void if_expression_check(if_ptr,left,right)
     IFblock *if_ptr;
     Expression *left,*right;
{
    int i,j;
    int sc_vars;
    int fort_funcs,user_funcs;

    Expression *expr_ptr;
    int  identifiers,functions;
    char **identifier,**function;

    /* PRE_TO_INFに積む */
    pre_to_inf_push(left->expr,&(left->expr_inf));
    pre_to_inf_push(right->expr,&(right->expr_inf));

    sc_vars  = 0;
    fort_funcs = 0;
    user_funcs = 0;

    /* まず左の検査 */
    expr_ptr = left;
    
    identifiers = expr_ptr -> identifiers;
    identifier  = expr_ptr -> identifier;

    functions   = expr_ptr -> functions;
    function    = expr_ptr -> function;

    for(j=0;j<identifiers;j++) {
	switch( get_var_kind( *(identifier+j))) {
		
	  case INT:
	  case CONST:
	  case DOUBLE:
	    if(sc_vars == MAX_VARIABLES) {

		if(english_mesg) {
		    SystemError_yy("Too complicated formula in if sentence.",
				   if_ptr->yylineno);
		}
		else {
		    SystemError_yy("if文での式が複雑すぎる",if_ptr->yylineno);
		}

		return;
	    }
	    sc_name_buf[sc_vars] = *(identifier + j);
	    sc_vars++;
	    break;
	    
	    
	  case SYSTEM_VAR: /* 現在空間変数(var_check.c)ならば… */
	  case FEM:
	  case EWISE:
	  case TEST_VAR:

	    if(english_mesg) {
		SystemError_yy_s("Variable %s cannot be used in if sentence",
				 *(identifier+j),if_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("変数%sはif文に使用不可",*(identifier+j),
				 if_ptr->yylineno);
	    }

	    break;
	    
	  case NO:
	    
	    if(english_mesg) {
		SystemError_yy_s("Variable %s in if sentence is undefined.",
				 *(identifier+j),if_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("if文中の変数%sは宣言されていない",
				 *(identifier+j),if_ptr->yylineno);
	    }

	    break;
	}
    }
    
    for(j=0;j<functions;j++) {
	if(is_feel_user_func(*(function + j))) {
	    ;
	}
	else if(is_fort77_func(*(function + j))) {
	    ;
	}
	else if(is_diff_op(*(function + j))) {
	    
	    if(english_mesg) {
		SystemError_yy("Differential operator cannot be used in if block.",if_ptr->yylineno);
	    }
	    else {
		SystemError_yy("if文に微分演算子は使用不可",if_ptr->yylineno);
	    }

	}
	else {
	    if(english_mesg) {
		SystemError_yy_s("Function %s is undefined.",
				 *(function + j),if_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("if文中の関数%sは未定義",
				 *(function + j),if_ptr->yylineno);
	    }
	}
    }
    
    /* 次に右の検査 */
    expr_ptr = right;
    
    identifiers = expr_ptr -> identifiers;
    identifier  = expr_ptr -> identifier;
    
    functions   = expr_ptr -> functions;
    function    = expr_ptr -> function;
    
    for(j=0;j<identifiers;j++) {
	switch( get_var_kind( *(identifier+j))) {
	    
	  case INT:
	  case CONST:
	  case DOUBLE:
	    if(sc_vars == MAX_VARIABLES) {
		
		if(english_mesg) {
		    SystemError_yy("Too complicated formula in if block.",
				   if_ptr->yylineno);
		}
		else {
		    SystemError_yy("if文での式が複雑すぎる",if_ptr->yylineno);
		}

		return;
	    }
	    sc_name_buf[sc_vars] = *(identifier + j);
	    sc_vars++;
	    break;
		
		
	  case SYSTEM_VAR: /* 現在空間変数(var_check.c)ならば… */
	  case FEM:
	  case EWISE:
	  case TEST_VAR:
	    
	    if(english_mesg) {
		SystemError_yy_s("Variable %s cannot be used in if block.",
				 *(identifier+j),if_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("変数%sはif文に使用不可",*(identifier+j),
				 if_ptr->yylineno);
	    }

	    break;

	  case NO:
	    
	    if(english_mesg) {
		SystemError_yy_s("Variable %s is undefined.",
				 *(identifier+j),if_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("if文中の変数%sは宣言されていない",
				 *(identifier+j),if_ptr->yylineno);
	    }

	    break;
	}
    }

    for(j=0;j<functions;j++) {
	if(is_feel_user_func(*(function + j))) {
	    ;
	}
	else if(is_fort77_func(*(function + j))) {
	    ;
	}
	else if(is_diff_op(*(function + j))) {
	    if(english_mesg) {
		SystemError_yy("Differential operators cannot be used in if block.",if_ptr->yylineno);
	    }
	    else {
		SystemError_yy("if文に微分演算子は使用不可",if_ptr->yylineno);
	    }		

	}
	else {
	    if(english_mesg) {
		SystemError_yy_s("Function %s is undefined.",
				 *(function + j),if_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("if文中の関数%sは未定義",
				 *(function + j),if_ptr->yylineno);
	    }
	}
    }

    if_ptr->sc_vars = sc_vars;
    if_ptr->sc_var_name = (char **)FEEL_GetMemory(sizeof(char *)*sc_vars);
    for(j=0;j<sc_vars;j++) {
	*(if_ptr->sc_var_name + j) = sc_name_buf[j];
    }

    return;
}
