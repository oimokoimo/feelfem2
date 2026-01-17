/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_known_eval_var.c
 *      Date:   1993/10/27
 *   
 *   Purpose:   既知fem変数に対する展開式を作成する
 *   Functions: 
 *              
 *   制限       dbg: エルミート要素に対する考慮はペンディング
 *                  
 *              ただし、この仕様でも将来可。その際、
 *              ecalへの呼びだし時に、fem変数の適当なメンバーを
 *              assignすること。
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

make_known_eval_var( fp  , name , domain_name )
     FILE *fp;
     char *name;
     char *domain_name;
{
    int i;
    int freedom;
    char *element_name;

    element_name  =get_elem_name_by_ND( name , domain_name );
    
    freedom = get_freedom_by_element_name(element_name);

    /* dbg: 注意:エルミート要素等は考慮せず */

    LISP_SEND_s(fp,"(setq %s '(+ ",name);
    for(i=0;i<freedom;i++) {
	LISP_SEND_sdsd(fp,"(* %s_%d %s_%d) ",name,i+1,element_name,i+1);
    }
    LISP_SEND(fp,") )\n");

    return;
}
