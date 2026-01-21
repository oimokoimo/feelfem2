/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   domain.c
 *      Date:   1993/06/03 (Modified)
 *  Modified:   1993/07/06 1993/12/27
 *   
 *   Purpose:   domain文の処理
 *   Functions: domain_st()
 *              how_many_domains()
 *              Domain *get_nth_domain_ptr()
 *              get_domain_no_by_name()
 *              get_region_no_by_2names(region_name,domain_name)
 *              store_domain_edatno()  代表的なedat番号の登録
 *
 */
#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../system/system.h"
#include "mesh_comp.h"

static Domain *domain[MAX_DOMAINS];
static int  domains = 0;

void domain_st(parameters)
     int parameters;
{
    int i;
    char **region_name;
    int   *region_no;

    if(domains == MAX_DOMAINS) {
	if(english_mesg) {
	    SystemError("Too many domains specified.");
	}
	else {
	    SystemError("domain定義が多すぎる");
	}


	for(i=0;i<parameters;i++) pop();  /* cancel pushed stack */
	pop();                            /* cancel for name     */

	return;
    }

    region_name = (char **)FEEL_GetMemory( sizeof(char *) *parameters);
    region_no   = (int   *)FEEL_GetMemory( sizeof(int   ) *parameters);
    
    domain[domains] = (Domain *)FEEL_GetMemory( sizeof (Domain));
    
    for(i=0;i<parameters;i++) {
	*(region_name+i) = PopString();
    }
    
    domain[domains]->name  = PopString();
    domain[domains]->domain_no = domains+1;        /* domain番号は登録順 */
    domain[domains]->regions = parameters;
    domain[domains]->region_name = region_name;
    domain[domains]->region_no   = region_no;
    domain[domains]->edatno      = NO;             /* edat作成時に設定する */
    domain[domains]->yylineno = yylineno_info();

    if(get_mesh_name_type_by_name( domain[domains]->name)) {

	if(english_mesg) {
	    SystemError_s("domain name %s is already defined for other object's name.",domain[domains]->name);
	}
	else {
	    SystemError_s("domain名 %s は既に他の名前に使用されている",
			  domain[domains]->name);
	}

    }
    store_mesh_name( domain[domains]->name , MESH_DOMAIN );


    domains++;
    return;
}	      
	
int how_many_domains()
{
    return(domains);
}


Domain *get_nth_domain_ptr( n )
     int n;
{
    if(n < 0 || n >=domains) {
	SystemAbort("Illegal domain no(get_nth_domain_ptr)");
    }
    return( domain[n] );
}

int get_domain_NO_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<domains;i++) {
	if(streq(domain[i]->name,name)) {
	    return(i+1);                    /* NOが大文字のシリーズは
					       1から始まる番号を返す  */
	}
    }
    return(0);    /* これはエラーを意味する */
}

Domain *get_domain_ptr_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<domains;i++) {
	if(streq(domain[i]->name,name)) {
	    return(domain[i]);
	}
    }
    return(NULL);    /* これはエラーを意味する */
}


int get_domain_etype_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<domains;i++) {
	if(streq(domain[i]->name,name)) {
	    return(domain[i]->etype);
	}
    }
    return(NO);    /* これはエラーを意味する */
}


/* solve_chk_var.c にて、唯一のdomainに対しての場合の処理に使う */
char *get_domain_name_by_no( n )
     int n;
{
    if(n < 0 || n >= domains) {
	if(english_mesg) {
	    SystemAbort("INNER ERROR: attempt to get domain ptr with illegal No.");
	}
	else {
	    SystemAbort("変なdomain番号のdomain名称を得ようとした\n");
	}

    }

    return( domain[n]->name);
}


/* mesh_book_exec.c にregionの順番に関して関連する箇所あり */

int get_region_no_by_2names( region_name , domain_name )
     char *region_name;
     char *domain_name;
{
    int i;

    Domain *domain_ptr;

    domain_ptr = get_domain_ptr_by_name( domain_name );
    if(domain_ptr == NULL) {
	SystemAbort("DOMAIN_PTR NULL POINTER(get_region_no_by_2name)");
    }

    for(i=0;i<domain_ptr -> regions;i++) {
	if(streq(*(domain_ptr->region_name + i),region_name)) {
	    return(domain_ptr->regions - i);
	}
    }
    
    return(NO);  /* NO はエラーを意味する */
}

/* 代表節点要素集合番号の設定 */
void store_domain_edatno( domain_name, edatno )
     char *domain_name;
     int   edatno;
{
    Domain *domain_ptr;


/*    fprintf(stderr,"DOMAIN edat番号設定 %s %d\n",domain_name,edatno);
 */
    domain_ptr = get_domain_ptr_by_name ( domain_name );

    if(domain_ptr -> edatno == NO ) { /* 既に設定されていなければ… */
	
	domain_ptr -> edatno = edatno;
    }

    return;
}

/* 代表的なdomain edatno を返す */
int get_domain_edatno_by_name( domain_name )
     char *domain_name;
{
    Domain *domain_ptr;
    domain_ptr = get_domain_ptr_by_name( domain_name );
    
    return(domain_ptr -> edatno);
}


int get_domain_region_no(  domain_name , region_name )
     char *domain_name;
     char *region_name;
{
    int i;
    Domain *domain_ptr;

    domain_ptr = get_domain_ptr_by_name(domain_name);

    for(i=0;i<domain_ptr->regions;i++) {
	if(streq(region_name,*(domain_ptr->region_name+i))) {
	    return(*(domain_ptr->region_no + i));
	}
    }

    return(NO);   /* NO はエラーを意味する */
}

	
Region *get_region_ptr_by_domain_matno(domain_name, matno)
     char *domain_name;
     int matno;
{
    int i;
    Domain *domain_ptr;
    Region *region_ptr;
    
    domain_ptr = get_domain_ptr_by_name(domain_name);
    if(matno < 1 || matno > domain_ptr->regions) {
	SystemAbort("MATNO ERROR @ get_region_ptr_by_domain_matno");
    }

    for(i=0;i<domain_ptr->regions;i++) {
	if(matno == *(domain_ptr->region_no+i)) {
	    region_ptr = get_region_ptr_by_name(*(domain_ptr->region_name+i));
	    return(region_ptr);
	}
    }

    SystemAbort("NOT FOUND matno @ get_region_ptr_by_domain_matno");
}


	    
