/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_let_check.c
 *      Date:   1993/12/17
 *   
 *   Purpose:   let文に関する検査を実行する
 *   Functions: 
 *              let_ptr -> xyz_vars,x_flag,ew_vars等の処理を行う
 *              
 *              let文の種別
 *              
 *  LET_SC_SC       スカラー変数 ＝ スカラー変数  
 *  LET_SC_SCF      スカラー変数 ＝ スカラー関数
 *                                  FEM変数等を引き数に持つ物も含む
 *              
 *  LET_FEM_FEM     fem変数      ＝ fem変数
 *  LET_FEM_DIFF                            微分作用素付 fem 変数式
 *              
 *  LET_EW_SC
 *  LET_EW_EW       ewise変数    ＝ ewise変数(同一domain,同一タイプ)
 *                                  微分作用素付 fem 変数式
 *              
 *              
 *              
 *              現在複数domain指定時のFEM変数詳細検査は付加せず
 *                                  EWISE変数は未完成
 *              
 *              検査すべき項目      FEM,EWISE変数の定義域の妥当性
 *              
 *              検査済み項目        EWISE変数のregion指定代入時の
 *                                  region検査(指定domainのregionか？)
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"
#include "../scheme_comp/scheme_comp.h"
#include "../mesh_comp/mesh_comp.h"

void scheme_let_check()
{
    int i,j;
    int schemes;

    int int_vars,dbl_vars;          /* int,doubleを区別する為 */
    int sc_vars,fem_vars,ew_vars;   /* 右辺に現れる変数の種類 */
    int xyz_vars;
    int fort_funcs;
    int diff_ops;  
    int user_funcs;
    int var_type;

    int domains;

    char *fem_name_buf[MAX_VARIABLES];
    char *ew_name_buf[MAX_VARIABLES];
    char *int_name_buf[MAX_VARIABLES];
    char *dbl_name_buf[MAX_VARIABLES];

    Scheme *scheme_ptr;
    Let    *let_ptr;
    char  **region_name;
    int     regions;

    EWISE_var  *ewise_var_ptr;
    EWISE_type *ewise_type_ptr;
    FEM_var    *fem_var_ptr;
    FEM_type   *fem_type_ptr;
    Expression *expr_ptr;

    char *var_name;

    int  identifiers,functions;
    char **identifier,**function;

    schemes = how_many_schemes();
    domains = how_many_domains();

    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);

	if(scheme_ptr->type != LET) continue;
	
	let_ptr  = (Let *)scheme_ptr->ptr;

	var_name = let_ptr->var_name;

	var_type = get_var_kind( var_name );
	switch(var_type) {
	  case SYSTEM_VAR:
	  case TEST_VAR:
	    SystemError_yy_s("変数%sに代入はできない",var_name,
			   let_ptr->yylineno);
	    continue;

	  case NO:
	    SystemError_yy_s("変数%sは宣言されていない",var_name,
			   let_ptr->yylineno);
	    continue;

    /* 各変数の場合には、それぞれのポインタをガメル */
	  case FEM:
	    
	  case EWISE:
	  case DOUBLE:
	    break;

	  case CONST:
	    if(english_mesg) {
		SystemError_yy_s("Changing value for constant %s is not allowd.",var_name,let_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("定数変数%sには代入できない",var_name,
				 let_ptr->yylineno);
	    }
	    continue;

	  case INT:
	    break;

	  default:
	    if(english_mesg) {
		SystemAbort("INNER ERROR: Illegal code detected.(scheme_let_check)");
	    }
	    else {
		SystemAbort("変なコードを検出(scheme_let_check)");
	    }
	    break;

	}

	expr_ptr = let_ptr -> expr;
	
	/* PRE_TO_INFに積む */
	pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));

	int_vars = 0;
	dbl_vars = 0;
	sc_vars  = 0;
	fem_vars = 0;
	ew_vars  = 0;
	xyz_vars = 0;
	fort_funcs = 0;
	user_funcs = 0;
	diff_ops   = 0;

	let_ptr -> x_flag = NO;
	let_ptr -> y_flag = NO;
	let_ptr -> z_flag = NO;


	identifiers = expr_ptr -> identifiers;
	identifier  = expr_ptr -> identifier;

	functions   = expr_ptr -> functions;
	function    = expr_ptr -> function;

	for(j=0;j<identifiers;j++) {

	    switch( get_var_kind( *(identifier+j))) {
	      case FEM:
		fem_name_buf[fem_vars] = *(identifier+j);
		fem_vars++;
		break;
		
	      case EWISE:
		ew_name_buf[ew_vars] = *(identifier+j);
		ew_vars++;
		break;
		
	      case CONST:
	      case DOUBLE:
		dbl_name_buf[dbl_vars] = *(identifier + j);
		dbl_vars++;
		sc_vars++;
		break;
		
	      case INT:
		int_name_buf[int_vars] = *(identifier + j);
		int_vars++;
		sc_vars++;
		break;
		
	      case SYSTEM_VAR: /* 現在空間変数(var_check.c)ならば… */

		if(streq(*(identifier+j),"x") || streq(*(identifier+j),"X")){
		    let_ptr->x_flag = YES;
		}
		if(streq(*(identifier+j),"y") || streq(*(identifier+j),"Y")){
		    let_ptr->y_flag = YES;
		}
		if(streq(*(identifier+j),"z") || streq(*(identifier+j),"Z")){
		    let_ptr->z_flag = YES;
		}

		xyz_vars++;
		break;

	      case TEST_VAR:
		if(english_mesg) {
		    SystemError_yy_s("Variable %s cannot be used in let sentence.",*(identifier+j),let_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("変数%sは代入文に使用不可",*(identifier+j),
				     let_ptr->yylineno);
		}
		break;

	      case NO:
		if(english_mesg) {
		    SystemError_yy_s("Variable %s is not defined.",
				     *(identifier+j),let_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("変数%sは宣言されていない",*(identifier+j),
				     let_ptr->yylineno);
		}
		break;
	    }
	}

	for(j=0;j<functions;j++) {
	    if(is_feel_user_func(*(function + j))) {
		user_funcs++;
	    }
	    else if(is_fort77_func(*(function + j))) {
		fort_funcs++;
	    }
	    else if(is_diff_op(*(function + j))) {
		diff_ops++;
	    }
	    else {
		if(english_mesg) {
		    SystemError_yy_s("Function %s is not defined.",
				     *(function + j),let_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("代入文中の関数%sは未定義",
				     *(function + j),let_ptr->yylineno);
		}
	    }
	}


/*
	fprintf(stderr,"変数名 %s\n",var_name);
	fprintf(stderr,"fem    %d\n",fem_vars);
	fprintf(stderr,"ew     %d\n",ew_vars);
	fprintf(stderr,"sc     %d\n",sc_vars);
	fprintf(stderr,"x,y,z  %d\n",xyz_vars);
	fprintf(stderr,"user   %d\n",user_funcs);
	fprintf(stderr,"fort   %d\n",fort_funcs);
	fprintf(stderr,"diff   %d\n",diff_ops);
*/


	let_ptr -> fem_vars = fem_vars;
	let_ptr -> ew_vars  = ew_vars;
	let_ptr -> sc_vars  = sc_vars;
	let_ptr -> int_vars = int_vars;
	let_ptr -> dbl_vars = dbl_vars;
	let_ptr -> xyz_vars = xyz_vars;
	let_ptr -> user_funcs = user_funcs;
	let_ptr -> fort_funcs = fort_funcs;
	let_ptr -> diff_ops   = diff_ops;

	if(fem_vars) {
	    let_ptr -> fem_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      fem_vars);
	    for(j=0;j<fem_vars;j++) {
		*(let_ptr->fem_var_name + j) = fem_name_buf[j];
	    }
	}
	else {
	    let_ptr -> fem_var_name = NULL;
	}

	if(ew_vars) {
	    let_ptr -> ew_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      ew_vars);
	    for(j=0;j<ew_vars;j++) {
		*(let_ptr->ew_var_name + j) = ew_name_buf[j];
	    }
	}
	else {
	    let_ptr -> ew_var_name = NULL;
	}

	if(int_vars) {
	    let_ptr -> int_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      int_vars);
	    for(j=0;j<int_vars;j++) {
		*(let_ptr->int_var_name + j) = int_name_buf[j];
	    }
	}
	else {
	    let_ptr -> int_var_name = NULL;
	}

	if(dbl_vars) {
	    let_ptr -> dbl_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      dbl_vars);
	    for(j=0;j<dbl_vars;j++) {
		*(let_ptr->dbl_var_name + j) = dbl_name_buf[j];
	    }
	}
	else {
	    let_ptr -> dbl_var_name = NULL;
	}


		
	/* 代入文の種類判定  SC_TO_SC など */
	switch(var_type) {
	  case INT:
	  case DOUBLE:

	    if(ew_vars == 0 &&  diff_ops == 0 ) {

		if(fem_vars != 0 || xyz_vars != 0) {
		    if( let_ptr->let_place != LET_AT) {
			if(english_mesg) {
			    SystemError_yy_s("Value for %s must be one point fem variable.",let_ptr->var_name,let_ptr->yylineno);
			}
			else {
			    SystemError_yy_s("スカラー変数 %s に節点固定以外のfem変数を指定した",let_ptr->var_name,let_ptr->yylineno);
			}
			break;
		    }
		}

		let_ptr -> let_type = LET_SC_SC;

		break;
	    }

	    if(english_mesg) {
		SystemWarning("Some Let sentence is not allowed.");
	    }
	    else {
		SystemWarning("現在LET文のほとんど未対応");
	    }
	    break;

	  case EWISE:

/*	    fprintf(stderr,"EWISE 代入 %d(ew)  %d(fem)  %d(diff)\n",
		    ew_vars,fem_vars,diff_ops);   */
	    /* スカラー系のewiseへの単なる代入 */
	    if(ew_vars == 0 && fem_vars == 0 && diff_ops == 0) {  
		let_ptr -> let_type = LET_EWISE_SC;
		break;
	    }
	    if(fem_vars == 0 && diff_ops == 0) {
		let_ptr -> let_type = LET_EWISE_EWISE;
		/* domain文は一つしか無いはずですから… */
		break;
	    }
	    if(english_mesg) {
		SystemWarning("This type of ewise variable for let sentence is not supported now.");
	    }
	    else {
		SystemWarning("[EWISE]現在LET文のほとんど未対応");
	    }
	    break;

	  case FEM:
	    if(ew_vars == 0 && diff_ops == 0 && 
	       (let_ptr->let_place == NORMAL_LET ||
		let_ptr->let_place == LET_AT)       ) {

		/* 場所指定付の場合は、matnoが必要となる為
		   FEM_FEMでも、FEM_FEMEWISEでの取扱が必要 
		   ここも、multi-domain時には変更必要      */

		let_ptr -> let_type = LET_FEM_FEM;
		break;
	    }
	    if(english_mesg) {
		SystemWarning("Let sentence for FEM variable is not fully supported now.");
	    }
	    else {
		SystemWarning("現在LET文のほとんど未対応");
	    }
	    break;
	    
	  defulat:
	    SystemAbort("Illegal Code(scheme_let_check)");
	}


	/* 場所指定付きLET文のエラー判定 */

	regions     = let_ptr -> regions;         /* 指定領域数 */
	region_name = let_ptr -> region_name;     /* 指定領域名 */

	switch( let_ptr -> let_place ) {
	  case NORMAL_LET:

	    break;
	    
	  case LET_AT:  /* 点への代入 */
	    if(var_type == INT || var_type == DOUBLE) {

		if(regions != 1) {
		    if(english_mesg) {
			SystemError_yy_s("Illegal number of points specified in let sentence for %s.",let_ptr->var_name,let_ptr->yylineno);
		    }
		    else {
    			SystemError_yy_s("スカラー変数 %s の節点位置代入文で複数節点を指定した",let_ptr->var_name,let_ptr->yylineno);
		    }
		}
	    }

	    if(var_type == EWISE ) {
		if(english_mesg) {
		    SystemError_yy_s("Let sentence for EWISE variable %s with one point value is not allowed.",var_name,let_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("EWISE変数%sに対して節点代入文を指定",
				     var_name,let_ptr->yylineno);
		}
		continue;
	    }

	    for(j=0;j<regions;j++) {
		switch(get_mesh_name_type_by_name( *(region_name + j) )) {
		  case 0:   /* 定義されないメッシュ形状 */
		    if(english_mesg) {
			SystemError_yy_s("Region name for %s is not defined.",
					 *(region_name+j),
					 let_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("代入位置指定形状名 %s は未定義",
					 *(region_name+j),
					 let_ptr -> yylineno);
		    }
		    break;
		    
		  case MESH_POINT:
		    if(get_point_ptr_by_name( *(region_name + j)) == NULL) {
			if(english_mesg) {
			    SystemError_yy_s("Point %s is not defined.",
					     *(region_name+j),
					     let_ptr->yylineno);
			}
			else {
			    SystemError_yy_s("点 %s は未定義(大文字小文字問題？)",
					     *(region_name+j),
					     let_ptr -> yylineno);
			}
		    }
		    break;
		    
		  default:
		    if(english_mesg) {
			SystemError_yy_s("%s is not boundary name.",
					 *(region_name+j),
					 let_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("代入指定形状名 %s は境界形状ではない",
					 *(region_name+j),
					 let_ptr -> yylineno);
		    }
		    break;
		}
		       
	    }
	    
	    break;
	    
	  case LET_ON:  /* 境界線等への代入 (二次元のみ)*/
	    if(var_type == INT || var_type == DOUBLE) {
		if(english_mesg) {
		    SystemError_yy_s("Scalar variable %s with on is not allowed.",var_name,let_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("スカラー変数%sに対して位置指定代入文を実行",
				     var_name,let_ptr->yylineno);
		}
		continue;
	    }
	    
	    if(var_type == EWISE ) {
		if(english_mesg) {
		    SystemError_yy_s("EWISE variable %s with on is not allowed.",var_name,let_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("EWISE変数%sに対して境界代入文を指定",
				 var_name,let_ptr->yylineno);
		}
		continue;
	    }
	    
	    for(j=0;j<regions;j++) {
		switch(get_mesh_name_type_by_name( *(region_name + j) )) {
		  case 0:   /* 定義されないメッシュ形状 */
		    if(english_mesg) {
			SystemError_yy_s("Region name %s is not defined.",
					 *(region_name+j),
					 let_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("代入位置指定形状名 %s は未定義",
					 *(region_name+j),
					 let_ptr -> yylineno);
		    }
		    break;
		    
		  case MESH_LINE:
		    break;
		    
		  default:
		    if(english_mesg) {
			SystemError_yy_s("Name %s is not boundary name.",
					 *(region_name+j),
					 let_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("代入指定形状名 %s は境界形状ではない",
					 *(region_name+j),
					 let_ptr -> yylineno);
		    }
		    break;
		}
		       
	    }
	    break;
	    
	  case LET_IN:
	    if(var_type == INT || var_type == DOUBLE) {
		if(english_mesg) {
		    SystemError_yy_s("Scalar variable %s with in is not allowed.",var_name,let_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("スカラー変数%sに対して位置指定代入文を実行",
				     var_name,let_ptr->yylineno);
		}
		continue;
	    }

	    for(j=0;j<regions;j++) {
		switch(get_mesh_name_type_by_name( *(region_name + j) )) {
		  case 0:   /* 定義されないメッシュ形状 */
		    if(english_mesg) {
			SystemError_yy_s("Name %s is not defined.",
					 *(region_name+j),let_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("代入位置指定形状名 %s は未定義",
					 *(region_name+j),
					 let_ptr -> yylineno);
		    }
		    break;
		    
		  case MESH_REGION:
		    /* 指定されているregionがewiseで定義された
		       domainのregionか調べる                  */
		    if(var_type == EWISE) {
			ewise_type_ptr = get_ewise_type_ptr_by_name(var_name);
			if(ewise_type_ptr == NULL) {
			    SystemError_s("EWISE variable %s cannot be handled in let sentence.....",
					  var_name);
			    break;
			}
			if(get_region_no_by_2names(*(region_name + j),
						   ewise_type_ptr->domain_name)
			   == NO) {
			    SystemError_yy_ss("region %s is not EWISE variable %s definition domain",*(region_name+j),var_name,let_ptr->yylineno);
			    break;
			}
		    }

		    break;
		    
		  default:
		    SystemError_yy_s("Name %s is not region name",
				     *(region_name+j),
				     let_ptr -> yylineno);
		    break;
		}
	    }
	    break;
		       
	  default:
	    SystemAbort("Illegal code in scheme_let_check");
	}

    }

    return;
}
