/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   ewise_var_check
 *      Date:   1993/12/24
 *   
 *   Purpose:   ewise_typeの完成
 *   Functions: 
 *              pointsの設定(座標指示型では既に値が入っている)
 *              座標指示型では範囲チェック
 *              数値積分法が指定されている場合の座標の設定
 *              domain名が存在しているかどうか(etypeを設定)
 *
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"
#include "../mesh_comp/mesh_comp.h"
#include "../quadrature/quadrature.h"

void ewise_var_check()
{
    int i,j;
    int ewise_types;
    EWISE_type *ewise_type_ptr;
    Quadrature *quad_ptr;

    ewise_types = how_many_ewise_types();

    for(i=0;i<ewise_types;i++) {
	ewise_type_ptr = get_nth_ewise_type_ptr(i);

	if(ewise_type_ptr->points == 0) {

	    /* domainが宣言されているかどうか */
	    if(ewise_type_ptr->domain_name == NULL) {
		if(english_mesg) {
		    SystemError_yy_s("No domain specification for ewise variable '%s'",ewise_type_ptr->name,ewise_type_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("ewise変数%sのdomain宣言がない",ewise_type_ptr ->name,ewise_type_ptr -> yylineno);
		}

	    }
	    else {
		if(get_domain_ptr_by_name(ewise_type_ptr->domain_name) == NULL) {
		    if(english_mesg) {
			SystemError_yy_ss("Specified domain name '%s' for ewise variable '%s' is not defined.",ewise_type_ptr->domain_name,ewise_type_ptr->name,ewise_type_ptr->yylineno);
		    }
		    else  {
			SystemError_yy_ss("ewise変数宣言%sに指定されたdomain %sは未定義",ewise_type_ptr->name,ewise_type_ptr->domain_name,ewise_type_ptr->yylineno);
		    }
		    continue;
		}
		ewise_type_ptr -> etype  = get_domain_etype_by_name( ewise_type_ptr -> domain_name);
		if(ewise_type_ptr -> etype == NO) {

		    if(english_mesg) {
			SystemAbort_s("No etype definition for domain %s(INNER ERROR).",ewise_type_ptr->domain_name);
		    }
		    else {
			SystemAbort_s("domain %sにetype設定無し(ewise_var_check)",ewise_type_ptr->domain_name);
		    }
		    
		}
	    }
	    
/*
	    fprintf(stderr,"ewise check!");
	    fprintf(stderr,"quad = %s\n",ewise_type_ptr->quadrature);
	    fprintf(stderr,"points = %d\n",ewise_type_ptr->points);
*/
	    
	    if(ewise_type_ptr -> quadrature == NULL) {
		ewise_type_ptr->points = 1;
/*		fprintf(stderr,"ewise_type_ptr->points TO 1！！！\n"); */
	    }
	    else {

		if(!is_defined_quadrature( ewise_type_ptr->quadrature)) {

		    if(english_mesg) {
			SystemError_yy_ss("Specified quadrature method '%s' for ewise variable '%s' is not defined.",ewise_type_ptr->quadrature,ewise_type_ptr->name,ewise_type_ptr->yylineno);
		    }
		    else {
			SystemError_yy_ss("ewise変数%sに指定の数値積分法%sは未定義"
					  ,ewise_type_ptr-> name , 
					  ewise_type_ptr->quadrature,
					  ewise_type_ptr->yylineno);
		    }
		    continue;
		}

		quad_ptr = 
		  get_quadrature_ptr_by_name(ewise_type_ptr -> quadrature);
		
		ewise_type_ptr -> points = quad_ptr -> nodes;
	    }
	}
	else {
	    /* (dbg:)ここで、指定した範囲が要素内にあるかどうかの判定 */
	    j = j;
	}
    }
    return;
}
	
		    
		
