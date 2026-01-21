/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   
 *      Date:   1993/06/03 (Modified)  Original 1992/08/11
 *   Modified:  1998/07/17 19:02  for web extension
 *   
 *   Purpose:   region文の処理
 *   Functions: region_st()
 *              region_with_meshmethod_st()
 *              how_many_regions()
 *              Region *get_nth_region_ptr()
 *              put_domain_data_to_region(Domain *)
 *              get_region_no_by_name()
 *              get_region_ptr_by_name()
 *              is_defined_region()
 *              is_rect()                  1998 extension for web
 *              
 */
#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../system/system.h"
#include "mesh_comp.h"


static Region *region[MAX_REGIONS];
static int  regions = 0;
static int  is_rect_flag=0;

void region_st(parameters)
     int parameters;
{
    int i;
    int inners,outers;
    char *cp;

    outers = 0;           /* counter for outer boundary points         */
    inners = 0;           /* counter for inner boundary ! (not points) */

    if(regions == MAX_REGIONS) {
	if(english_mesg) {
	    SystemError("Too many regions specified.");
	}
	else {
	    SystemError("region文が多すぎる");
	}


	for(i=0;i<parameters;i++) pop();   /* for points */
	pop();                             /* for name   */
	    
	return;
    }

    region[regions] = (Region *)FEEL_GetMemory(sizeof (Region));
    
    for(i=0;i<parameters;i++) {
	cp = PopString();
	if(strindex(cp,"[")) {           /* Inner edge */
	    inners++;
	    region[regions]->points[inners] = 
	      extract_inner_edge_list(cp,region[regions]->compos[inners]);
	    FEEL_FreeMemory(cp);
	}
	else {
	    region[regions]->compos[0][outers] = cp;
	    outers++;
	}
    }

    region[regions]->points[0] = outers;
    region[regions]->edges  = inners+1;
    region[regions]->method = NULL;
    region[regions]->name = PopString();
    region[regions]->yylineno = yylineno_info();
    region[regions]->region_no = regions + 1;

    if(get_mesh_name_type_by_name( region[regions]->name)) {

	if(english_mesg) {
	    SystemError_s("region name %s is already defined for other object's name.",region[regions]->name);
	}
	else {
	    SystemError_s("region名 %s は既に他の名前として定義されている",
			  region[regions]->name);
	}

    }
    store_mesh_name( region[regions]->name , MESH_REGION );


    ReverseStringArray(region[regions]->points[0],region[regions]->compos[0]);
 
    regions++;
    return;
}	      
	
void region_with_meshmethod_st(parameters)
     int parameters;
{
    int i;
    int inners,outers;
    char *cp;

    outers = 0;           /* counter for outer boundary points         */
    inners = 0;           /* counter for inner boundary ! (not points) */

    if(regions == MAX_REGIONS) {
	
	if(english_mesg) {
	    SystemError("Too many regions specified.");
	}
	else {
	    SystemError("regionの指定が多すぎる");
	}


	for(i=0;i<parameters;i++) pop();   /* for point data  */
	pop();                             /* for mesh mehod  */
	pop();                             /* for region name */

	return;
    }

    region[regions] = (Region *)FEEL_GetMemory(sizeof (Region));
    
    for(i=0;i<parameters;i++) {
	cp = PopString();
	if(strindex(cp,"[")) {           /* If Inner edge */
	    inners++;
	    region[regions]->points[inners] = 
	      extract_inner_edge_list(cp,region[regions]->compos[inners]);
	    FEEL_FreeMemory(cp);
	}
	else {
	    region[regions]->compos[0][outers] = cp;
	    outers++;
	}
    }

    region[regions]->points[0] = outers;
    region[regions]->edges  = inners+1;
    region[regions]->method = PopString();
    region[regions]->name   = PopString();
    region[regions]->region_no = regions + 1;
    
    region[regions]->yylineno = yylineno_info();

    /* メッシュの形チェック  line,tri,rectのはず */
    cp = region[regions]->method;                  /* cpはテンポラリuse */


/* web extension */
    if(streq(cp,RECT_STRING)) is_rect_flag = 1;

/* avs extension, almost same for is_rect_flag */
    if(streq(cp,RECT_STRING)) {
      avs_mesh_ref = 4;
    }
    else {
      avs_mesh_ref = 3;
      if(streq(cp,LINE_STRING)) SystemAbort("Unexpected in region.c");
    }

    if(!streq(cp,TRI_STRING) &&
       !streq(cp,RECT_STRING)&&
       !streq(cp,LINE_STRING)      ) {

	if(english_mesg) {
	    SystemError_ss("region %s's mesh method is illegal. (%s)",
			   region[regions]->name,cp);
	}
	else {
	    SystemError_ss("region %s に指定したメッシュ形状 %s は不正",
			   region[regions]->name,cp);
	}

    }

    if(get_mesh_name_type_by_name( region[regions]->name)) {
	if(english_mesg) {
	    SystemError_s("region name %s is already defined for other object's name.",region[regions]->name);
	}
	else {
	    SystemError_s("region名 %s は既に他で使用済み",
			  region[regions]->name);
	}

    }
    store_mesh_name( region[regions]->name , MESH_REGION );


    ReverseStringArray(region[regions]->points[0],region[regions]->compos[0]);
 
    regions++;

    return;
}	      


int how_many_regions()	
{
    return(regions);
}

Region *get_nth_region_ptr( n )
     int n;
{
    return( region[n] );
}

/*  domain文を、region名の集合体に変更したのでこの部分は不要

put_domain_data_to_region(domain)
     Domain *domain;
{
    int i,j;
    
    region[regions] = (Region *)FEEL_GetMemory(sizeof (Region));

    region[regions]->name   = domain->name;
    region[regions]->method = domain->method;
    region[regions]->edges  = domain->edges;
    for(i=0;i<domain->edges;i++) {
	region[regions]->points[i] = domain->points[i];
	for(j=0;j<domain->points[i];j++) {
	    region[regions]->compos[i][j] = domain->compos[i][j];
	}
    }

    regions++;
}
*/

int get_region_no_by_name( name )
     char *name;
{
    int i;
    
    for(i=0;i<regions;i++) {
	if(streq( name , region[i]->name)) return(i);
    }

    return(NOTHING);
}

/* エラーの場合はget_ptrシリーズはNULLポインタを返す */
Region *get_region_ptr_by_name( name )
     char *name;
{
    int no;
    
    no = get_region_no_by_name( name );
    if( no != NOTHING ) {
	return(region[no]);
    }
    else {

	/* printf("IN region.c  RETURN NULL POINTER\n"); */
	return(NULL);
    }
}

int is_defined_region( name )
     char *name;
{
    int i;

    for(i=0;i<regions;i++) {
	if(streq(region[i]->name,name)) {
	    return(YES);
	}
    }
    
    return(NO);
}


int is_rect()
{
   return(is_rect_flag);
}
