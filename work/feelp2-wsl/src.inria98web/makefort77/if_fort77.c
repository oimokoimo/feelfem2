/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   if_fort77.c
 *      Date:   1994/02/09
 *   
 *   Purpose:   if文グループを作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"

static char *from[MAX_VARIABLES];
static char *to[MAX_VARIABLES];

void if_fort77( fp, if_ptr )
     FILE    *fp;
     IFblock *if_ptr;
{
    
    switch( if_ptr->iftype ) {
	
      case ELSE:
	F77("        else\n");
	break;

      case ENDIF:
	F77("        endif\n");
	break;

      case IF_THEN:
	F77("      if( ");

	/* 左側を書く */
	if_write_sc_expression(fp,if_ptr->left);

	switch( if_ptr->condition_type ) {

	  case 1:
	    F77(" .EQ. ");
	    break;

	  case 2:
	    F77(" .LE. ");
	    break;

	  case 3:
	    F77(" .LT. ");
	    break;
	    
	  case 4:
	    F77(" .GE. ");
	    break;
	    
	  case 5:
	    F77(" .GT. ");
	    break;
	    
	  case 6:
	    F77(" .NE. ");
	    break;
	}

	/* 右側を書く */
	if_write_sc_expression(fp,if_ptr->right);


	F77(" ) then\n");
	break;

      case IF_GOTO:
	F77("      if( ");

	/* 左側を書く */
	if_write_sc_expression(fp,if_ptr->left);

	switch( if_ptr->condition_type ) {

	  case 1:
	    F77(" .EQ. ");
	    break;

	  case 2:
	    F77(" .LE. ");
	    break;

	  case 3:
	    F77(" .LT. ");
	    break;
	    
	  case 4:
	    F77(" .GE. ");
	    break;
	    
	  case 5:
	    F77(" .GT. ");
	    break;
	    
	  case 6:
	    F77(" .NE. ");
	    break;
	}

	/* 右側を書く */
	if_write_sc_expression(fp,if_ptr->right);


	PUT(fp," ) goto %d\n",if_ptr->lineno);
	break;

      default:
	SystemAbort("Illegal iftype(@if_fort77)");
    }
    return;
}

if_write_sc_expression(fp,expr_ptr)
     FILE *fp;
     Expression *expr_ptr;
{
    int i;
    int max_buf;
    int term_converts;
    char *name;
    char name_buf[80],name_buf2[80];

    max_buf = MAX_VARIABLES;
    term_converts = 0;

    /*=======================*/
    /* scの expression 書く  */
    /*                       */
    /* term_convertの作成    */
    /*=======================*/
    for(i=0;i<expr_ptr -> identifiers;i++) {
	name = *(expr_ptr->identifier + i);

	switch(get_var_kind( name ) ) {
	  case INT:
	  case DOUBLE:
	  case CONST:
	    /* term_convert用バッファ作成 */
	    if(term_converts == max_buf) {
		SystemAbort("term_buffer 不足(@if_fort77)");
	    }

	    sprintf(name_buf,SCALAR_VAR_NAME77,name);
	    to[term_converts] = MakeStringCopy(name_buf);
	    from[term_converts] = name;
	    term_converts++;
	    
	    break;

	  case SYSTEM_VAR:   /* 小文字x,y,z */
	  case FEM:
	  case EWISE:
	  case MATERIAL:
	    SystemAbort("Illegal variable in if_fort77");
	    break;

	  default:
	    SystemAbort("Unknown code@let_fem_fem");
	    break;
	}
    }


    PUT(fp,"%s",term_convert(expr_ptr->expr_inf,from,to,term_converts));

    return;
}

