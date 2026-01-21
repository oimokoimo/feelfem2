/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_rw_check.c
 *      Date:   1993/07/06
 *   
 *   Purpose:   read文、write文の変数が適当かどうかを判定する
 *              また、pre_to_inf関数に数式を登録しておく。
 *              
 */
#include "../feel_def/feel_def.h"
#include "../scheme_comp/scheme_comp.h"
#include "../system/system.h"


void scheme_rw_avs_warning()
{
  SystemWarning("In AVS mode, read/write is not available.");
  return;
}


void scheme_rw_check()
{
    int i,j,k;
    int schemes;
    int reads,writes;
    Scheme *scheme_ptr;
    Read   *read_ptr;
    Write  *write_ptr;
    Expression *expr;
    char   *name;

    /* dbg: 現在のバージョンではread文、write文の詳細検査はしていません */

    schemes = how_many_schemes();
    for(i=0;i<schemes;i++) {

	scheme_ptr = get_nth_scheme_struct(i);

	switch(scheme_ptr -> type) {

	  case READ:

	    if(avs_mode) { scheme_rw_avs_warning(); }

	    read_ptr = (Read *)scheme_ptr->ptr;

	    for(j=0;j<read_ptr->args;j++) {
		name = *(read_ptr->var_name+j);

		switch(get_var_kind(name)) {
		  case DOUBLE:
		  case INT:
		    break;

		  case CONST:
		    if(english_mesg) {
			SystemError_yy_s("constant variable %s is not allowd in read.",name,read_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("read文にconst変数 %s を指定した",
					 name,read_ptr->yylineno);
		    }
		    break;
		    
		  case FEM:
		  case SYSTEM_VAR:
		    if(english_mesg) {
			SystemError_yy_s("FEM variable %s is not allowed in read.",name,read_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("read文にFEM変数 %s を指定した",
					 name,read_ptr->yylineno);
		    }
		    break;		    

		  case EWISE:
		    if(english_mesg) {
			SystemError_yy_s("EWISE variable %s is not allowd in read.",name,read_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("read文にEWISE変数 %s を指定した",
					 name,read_ptr->yylineno);
		    }
		    break;		    

		  default:
		    SystemError_yy_s("%s is not defined.",
				     name,read_ptr->yylineno);
		    break;		    
		}


	    }
	    break;

	  case WRITE:

	    if(avs_mode) { scheme_rw_avs_warning(); }

	  case FILE_WRITE:
	    write_ptr = (Write *)scheme_ptr->ptr;

	    k = 0;
	    for(j=0;j<write_ptr->args;j++) {
		if(*(write_ptr->kind+j) != EXPR) continue;
		expr = (write_ptr->expr)+k;

		rw_expr_check( expr , WRITE , write_ptr->yylineno);

		k++;

		pre_to_inf_push(expr->expr,&(expr->expr_inf));
	    }
	    break;

	  default:
	    break;
	}
    }

    return;
}



rw_expr_check( expr , type , yylineno)
     Expression *expr;
     int type;
     int yylineno;
{
    int i;
    int    identifiers;
    char **identifier;

    identifiers = expr -> identifiers;
    identifier  = expr -> identifier;

    if(identifiers != 1 && type == READ) {
	SystemError_yy("formula is not allowd in read.",yylineno);
	return;
    }
    if(type == READ) {
	switch(get_var_kind( *(identifier))) {
	  case DOUBLE:
	  case INT:
	    return;

	  case FEM:
	    SystemError_yy("You use FEM variable in read.",yylineno);
	    return;

	  case EWISE:
	    SystemError_yy("You try to use ewise var in read.",yylineno);
	    return;
	    
	  default:
	    SystemError_yy("Illegal read sentence.",yylineno);	    
	    return;
	}
    }
    
    /* 以後、WRITE文のみ */

    for(i=0;i<identifiers;i++) {
	switch( get_var_kind( *(identifier+i))) {
	  case DOUBLE:
	  case INT:
	  case CONST:
	    break;

	  case FEM:
	  case SYSTEM_VAR:
	    if(english_mesg) {
		SystemError_yy_s("FEM varaible %s is not allowd in write.",
				 *(identifier+i),yylineno);
	    }
	    else {
		SystemError_yy_s("write文でFEM変数 %s を指定した",*(identifier+i),
				 yylineno);
	    }
	    break;

	  case EWISE:
	    if(english_mesg) {
		SystemError_yy_s("Ewise variable %s is not allowd in write.",
				 *(identifier+i),yylineno);
	    }
	    else {
		SystemError_yy_s("write文でEWISE変数 %s を指定した",
				 *(identifier+i),yylineno);
	    }
	    break;
	    
	  default:
	    SystemError_yy_s("INTERNAL ERR.  %s is mistery!", *(identifier+i),yylineno);
	    break;
	}
    }

    return;
}



		
		
	
