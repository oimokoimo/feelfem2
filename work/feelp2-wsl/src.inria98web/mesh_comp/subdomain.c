/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   subdomain.c
 *      Date:   1995/12/08
 *  Modified:   
 *   
 *   Purpose:   subdomain文の処理
 *   Functions: subdomain_st()
 *              how_many_subdomains()
 *              Subdomain *get_nth_subdomain_ptr()
 *              get_subdomain_no_by_name()
 *              get_region_no_by_2names(region_name,subdomain_name)
 *              store_subdomain_edatno()  代表的なedat番号の登録
 *
 */
#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../system/system.h"
#include "mesh_comp.h"

static Subdomain *subdomain[MAX_SUBDOMAINS];
static int  subdomains = 0;

subdomain_st(parameters)
     int parameters;
{
    int i;
    char **region_name;
    int   *region_no;

    if(subdomains == MAX_SUBDOMAINS) {
	if(english_mesg) {
	    SystemError("Too many subdomains specified.");
	}
	else {
	    SystemError("subdomain定義が多すぎる");
	}


	for(i=0;i<parameters;i++) pop();  /* cancel pushed stack */
	pop();                            /* cancel for name     */

	return;
    }

    region_name = (char **)FEEL_GetMemory( sizeof(char *) *parameters);
    region_no   = (int   *)FEEL_GetMemory( sizeof(int   ) *parameters);
    
    subdomain[subdomains] = (Subdomain *)FEEL_GetMemory( sizeof (Subdomain));
    
    for(i=0;i<parameters;i++) {
	*(region_name+i) = PopString();
    }
    
    subdomain[subdomains]->name  = PopString();
    subdomain[subdomains]->subdomain_no = subdomains+1;  /* subdomain番号は
							    登録順 */
    subdomain[subdomains]->regions = parameters;
    subdomain[subdomains]->region_name = region_name;
    subdomain[subdomains]->region_no   = region_no;
    subdomain[subdomains]->region_matno = NULL;

    subdomain[subdomains]->edatno        = 0;   
    subdomain[subdomains]->ewise_nset_no = 0;
    
    subdomain[subdomains]->yylineno = yylineno_info();

    if(get_mesh_name_type_by_name( subdomain[subdomains]->name)) {

	if(english_mesg) {
	    SystemError_s("subdomain name %s is already defined for other object's name.",subdomain[subdomains]->name);
	}
	else {
	    SystemError_s("subdomain名 %s は既に他の名前に使用されている",
			  subdomain[subdomains]->name);
	}

    }
    store_mesh_name( subdomain[subdomains]->name , MESH_SUBDOMAIN );


    subdomains++;
    return;
}	      
	
int how_many_subdomains()
{
    return(subdomains);
}


Subdomain *get_nth_subdomain_ptr( n )
     int n;
{
    if(n < 0 || n >=subdomains) {
	SystemAbort("Illegal subdomain no(get_nth_subdomain_ptr)");
    }
    return( subdomain[n] );
}

int get_subdomain_NO_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<subdomains;i++) {
	if(streq(subdomain[i]->name,name)) {
	    return(i+1);                    /* NOが大文字のシリーズは
					       1から始まる番号を返す  */
	}
    }
    return(0);    /* これはエラーを意味する */
}

Subdomain *get_subdomain_ptr_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<subdomains;i++) {
	if(streq(subdomain[i]->name,name)) {
	    return(subdomain[i]);
	}
    }
    return(NULL);    /* これはエラーを意味する */
}

int get_subdomain_etype_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<subdomains;i++) {
	if(streq(subdomain[i]->name,name)) {
	    return(subdomain[i]->etype);
	}
    }
    return(NO);    /* これはエラーを意味する */
}


/* solve_chk_var.c にて、唯一のsubdomainに対しての場合の処理に使う */
char *get_subdomain_name_by_no( n )
     int n;
{
    if(n < 0 || n >= subdomains) {
	if(english_mesg) {
	    SystemAbort("INNER ERROR: attempt to get subdomain ptr with illegal No.");
	}
	else {
	    SystemAbort("変なsubdomain番号のsubdomain名称を得ようとした\n");
	}

    }

    return( subdomain[n]->name);
}


/* mesh_book_exec.c にregionの順番に関して関連する箇所あり */
/* 関数get_region_no_by_2namesは削除 Project-subdomain     */

	    
