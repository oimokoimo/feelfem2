/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_initial.c
 *      Date:   1994/05/13
 *   
 *   Purpose:   非線形方程式での、INITIAL文の検査
 *                                NEWTON-FACTOR文の検査
 *
 *                                NEWTON-TIMES CHECK (99/04/05)
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"

void solve_chk_initial()
{
  int i,j,k;
  int err_flag;
  int solves;
  int initial_settings;
  Solve      *solve_ptr;
  Expression *newton_factor;
  Expression *expr_ptr;

  Expression *newton_times;
  Expression *times_expr_ptr;


  char *name,*name2;

  int unknowns;
  int unknown_flag_init[MAX_VARIABLES];

  int identifiers;
  char **identifier;
  int functions;
  char **function;

  solves = how_many_solves();

  for(i=0;i<solves;i++) {
    solve_ptr = get_nth_solve_ptr(i);

    /* 線形問題で、初期値が設定される場合を撥ねる */
    if(solve_ptr->nonlinear_flag == NO ) {
	    
      if(solve_ptr->initial_settings != 0) {
	if(english_mesg) {
	  SystemError_yy("Initial value is only for nonlinear case.",
			 *(solve_ptr->initial_yylineno+0));
	}
	else {
	  SystemError_yy("線形solve文内で初期値を設定しようとした",
			 *(solve_ptr->initial_yylineno+0));
	}
      }

      /* newton factor */
      if(solve_ptr->newton_factor    != NULL) {
	if(english_mesg) {
	  SystemError_yy("Newton factor is only for nonlinear problem.",solve_ptr->yy_newton_factor);
	}
	else {
	  SystemError_yy("線形solve文内で緩和係数を設定している",
			 solve_ptr->yy_newton_factor);
	}
      }
      /* newton times */
      if(solve_ptr->newton_times    != NULL) {
	if(english_mesg) {
	  SystemError_yy("Newton times is available for nonlinear problem.",solve_ptr->yy_newton_factor);
	}
	else {
	  SystemError_yy("線形solve文内でNewton-times係数を設定している",
			 solve_ptr->yy_newton_factor);
	}
      }

      continue;
    }


    /* 緩和係数がスカラー式かどうかを検査 */
    if(solve_ptr -> newton_factor != NULL) {
      newton_factor = solve_ptr->newton_factor;
      pre_to_inf_push(newton_factor->expr,&(newton_factor->expr_inf));
	    
      identifiers = newton_factor -> identifiers;
      identifier  = newton_factor -> identifier;
	    
      for(j=0;j<identifiers;j++) {
	switch(get_var_kind(*(identifier+j))) {
	case FEM:
	  if(english_mesg) {
	    SystemError_yy_s("FEM variable %s cannot be used in newton factor.",*(identifier+j),
			     solve_ptr->yy_newton_factor);
	  }
	  else {
	    SystemError_yy_s("緩和係数にFEM変数%sが含まれている",
			     *(identifier+j),
			     solve_ptr->yy_newton_factor);
	  }
	  break;
	case EWISE:
	  if(english_mesg) {
	    SystemError_yy_s("EWISE variable %s cannot be used in newton factor.",*(identifier+j),
			     solve_ptr->yy_newton_factor);
	  }
	  else {
	    SystemError_yy_s("緩和係数にEWISE変数%sが含まれている",
			     *(identifier+j),
			     solve_ptr->yy_newton_factor);
	  }
	  break;
	case SYSTEM_VAR:
	  if(english_mesg) {
	    SystemError_yy_s("Coordinate variable %s cannot be used in newton factor.",*(identifier+j),
			     solve_ptr->yy_newton_factor);
	  }
	  else {
	    SystemError_yy_s("緩和係数に空間変数%sが含まれている",
			     *(identifier+j),
			     solve_ptr->yy_newton_factor);
	  }
	  break;

	case TEST_VAR:
	  SystemError_yy("Test function cannot be used here.",
			 solve_ptr->yy_newton_factor);
	  break;
		    
	case INT:
	case CONST:
	case DOUBLE:
	  break;
		    
	default:
	  SystemError_yy_s("Variable %s is not defined.",
			   *(identifier+j),
			   solve_ptr->yy_newton_factor);
	  break;
	}
      }     		   
    }



    /* newton-times係数がスカラー式かどうかを検査 */
    if(solve_ptr -> newton_times != NULL) {
      newton_times = solve_ptr->newton_times;
      pre_to_inf_push(newton_times->expr,&(newton_times->expr_inf));
	    
      identifiers = newton_times -> identifiers;
      identifier  = newton_times -> identifier;
	    
      for(j=0;j<identifiers;j++) {
	switch(get_var_kind(*(identifier+j))) {
	case FEM:
	  if(english_mesg) {
	    SystemError_yy_s("FEM variable %s cannot be used in newton times.",*(identifier+j),
			     solve_ptr->yy_newton_times);
	  }
	  else {
	    SystemError_yy_s("Newton-times係数にFEM変数%sが含まれている",
			     *(identifier+j),
			     solve_ptr->yy_newton_times);
	  }
	  break;
	case EWISE:
	  if(english_mesg) {
	    SystemError_yy_s("EWISE variable %s cannot be used in newton times.",*(identifier+j),
			     solve_ptr->yy_newton_times);
	  }
	  else {
	    SystemError_yy_s("Newton-timesにEWISE変数%sが含まれている",
			     *(identifier+j),
			     solve_ptr->yy_newton_times);
	  }
	  break;
	case SYSTEM_VAR:
	  if(english_mesg) {
	    SystemError_yy_s("Coordinate variable %s cannot be used in newton times.",*(identifier+j),
			     solve_ptr->yy_newton_times);
	  }
	  else {
	    SystemError_yy_s("Newton-timesに空間変数%sが含まれている",
			     *(identifier+j),
			     solve_ptr->yy_newton_times);
	  }
	  break;

	case TEST_VAR:
	  SystemError_yy("Test function cannot be used here.",
			 solve_ptr->yy_newton_times);
	  break;
		    
	case INT:
	case CONST:
	case DOUBLE:
	  break;
		    
	default:
	  SystemError_yy_s("Variable %s is not defined.",
			   *(identifier+j),
			   solve_ptr->yy_newton_times);
	  break;
	}
      }     		   
    }
	    





    for(j=0;j<solve_ptr->unknowns;j++) {
      unknown_flag_init[j] = 0;
    }

    /* 設定された初期値が文法的に誤りが無いか検査する */
    initial_settings = solve_ptr->initial_settings;
	
    for(j=0;j<initial_settings;j++) {
      name = *(solve_ptr->initial_name + j);
      err_flag = YES;
	    
      /* 初期値が未知変数かどうかの検査 */
      for(k=0;k<solve_ptr->unknowns;k++) {
	if(streq(name,*(solve_ptr->unknown_name+k))) {
	  if(unknown_flag_init[k] == 1 ) {
	    SystemError_yy_s("Duplicated initial value setting for %s.",name,*(solve_ptr->initial_yylineno + j));
	  }
	  unknown_flag_init[k] = unknown_flag_init[k] + 1;
	  err_flag = NO;
	  break;
	}
      }
      if(err_flag == YES) {
	SystemError_yy_s("Variable %s is not unknown variable.",
			 name,*(solve_ptr->initial_yylineno+j));
	continue;
      }


      /* 初期値指定値にEWISE変数が含まれていないかどうかを調べる */
	    
      expr_ptr = *(solve_ptr->initial_expr + j);
      /* PRE_TO_INF関数に登録する */
      pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));

      identifiers = expr_ptr -> identifiers;
      identifier  = expr_ptr -> identifier;


      for(k=0;k<identifiers;k++) {
	name2 = *(identifier + k);
	switch(get_var_kind( name2 )) {
	case EWISE:
	  SystemError_yy_ss("Try to set initial value for %s with EWISE variable %s.",name,name2,*(solve_ptr->initial_yylineno + j));
	  break;

	case FEM:
	case DOUBLE:
	case INT:
	case CONST:
	case SYSTEM_VAR:
	  break;

	default:    /* 未定義変数を使用した */
	  SystemError_yy_ss("You try to set %s with undefined variable %s.",name,name2,*(solve_ptr->initial_yylineno + j));
	  break;
	}
      }
    }

  }

  return;
}
