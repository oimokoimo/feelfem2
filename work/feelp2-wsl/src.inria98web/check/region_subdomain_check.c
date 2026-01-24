/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   region_subdomain_check.c
 *      Date:   1993/07/16
 *   
 *   Purpose:   各region名にダブリがないか？
 *              各regionを構成する点が存在するか？ 
 *
 *              各subdomainは同じetypeを持つregionにより構成されているか？
 *              subdomainへのetypeの代入
 *             
 *              各subdomainを構成するregionに対してregion番号を付加
 *             
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../mesh_comp/mesh_comp.h"

void region_subdomain_check()
{
    int ip;
    int i,j,k;
    int subdomains,regions;
    int edges;
    int points;
    int regions_in_subdomain;

    int etype;

    Subdomain *subdomain_ptr;
    Region *region_ptr;

    char **region_name;
    int   *region_no;

    regions = how_many_regions();
    subdomains = how_many_subdomains();

    if(subdomains == 0) return;   /* subdomain宣言が無い場合はcheckしない */

    /* regionの重複定義検査 */
    duplicate_init();

    for(i=0;i<regions;i++) {
	region_ptr = get_nth_region_ptr( i );
	duplicate_push(region_ptr->name);
    }

    for(i=0;i<regions;i++) {
	region_ptr = get_nth_region_ptr( i );
	if(is_duplicate(region_ptr->name)) {
	    
	    if(english_mesg) {
		SystemError_yy_s("Duplicate definition of region %s",
				 region_ptr->name,region_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("region %s は二重定義されている",
				 region_ptr->name,region_ptr->yylineno);
	    }
	}
    }


    /* subdomainの重複定義検査 */
    duplicate_init();

    for(i=0;i<subdomains;i++) {
	subdomain_ptr = get_nth_subdomain_ptr( i );
	duplicate_push(subdomain_ptr->name);
    }

    for(i=0;i<subdomains;i++) {
	subdomain_ptr = get_nth_subdomain_ptr( i );
	if(is_duplicate(subdomain_ptr->name)) {

	    if(english_mesg) {
		SystemError_yy_s("Duplicate definition of subdomain %s.",
				 subdomain_ptr->name,subdomain_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("subdomain %s は二重定義されています。\n",
				 subdomain_ptr->name,subdomain_ptr->yylineno);
	    }

	}
    }

    /* 各regionの構成pointの定義検査とetypeの代入 */
    for(i=0;i<regions;i++) {
	region_ptr = get_nth_region_ptr( i );

	/* etypeの代入 */

	/* 三角形 */
	if(streq(region_ptr->method,TRI_STRING)) {
	    region_ptr->etype = TRI;
	    if(what_dimension() != 2) {

		if(english_mesg) {
		    SystemError_s("Illegal mesh type for region %s.",
				region_ptr->name);
		}
		else {
		    SystemError_s("region %sに指定したメッシュ生成法と空間次元が矛盾している",region_ptr->name);
		}
 
	    }

	}
	/* 四辺形 */
	else if(streq(region_ptr->method,RECT_STRING)) {
	    region_ptr->etype = RECT;
	    if(what_dimension() != 2) {

		if(english_mesg) {
		    SystemError_s("Illegal mesh type for region %s.",
				region_ptr->name);
		}
		else {
		    SystemError_s("region %sに指定したメッシュ生成法と空間次元が矛盾している",region_ptr->name);
		}

	    }
	}
	/* 線分 */
	else if(streq(region_ptr->method,LINE_STRING)) {
	    region_ptr->etype = LINE;
	    if(what_dimension() != 1) {


		if(english_mesg) {
		    SystemError_s("Illegal mesh type for region %s.",
				region_ptr->name);
		}
		else {
		    SystemError_s("region %sに指定したメッシュ生成法と空間次元が矛盾している",region_ptr->name);
		}
	    }
	}
	else {

	    if(english_mesg) {
		SystemError_yy_s("Specified mesh type for region %s is not defined.",region_ptr->name,region_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("region %s に指定されているメッシュ生成方法は定義されていない",region_ptr->name,region_ptr->yylineno);
	    }

	}

	/* 構成点の定義の有無のチェック */
	edges = region_ptr -> edges;
	
	for(j=0;j<edges;j++) {
	    points = region_ptr->points[j];

	    for(k=0;k<points;k++) {
		if(get_point_ptr_by_name(region_ptr->compos[j][k]) == NULL) {

		    if(english_mesg) {
			SystemError_yy_ss("point %s in region %s is not defined.",region_ptr->compos[j][k],region_ptr->name,region_ptr->yylineno);
		    }
		    else {
			SystemError_yy_ss("region %sに指定されている点 %s は未定義",region_ptr->name,region_ptr->compos[j][k],region_ptr->yylineno);
		    }
		}
	    }
	}
    }

    /* subdomain etypeの代入と、構成regionの宣言の有無のチェック */
    for(i=0;i<subdomains;i++) {
	subdomain_ptr = get_nth_subdomain_ptr(i);
	regions_in_subdomain = subdomain_ptr->regions;
	
	region_name = subdomain_ptr->region_name;

	region_ptr = get_region_ptr_by_name( *region_name );
	if(region_ptr == NULL) {

	    if(english_mesg) {
		SystemError_yy_ss("region %s used in definition of subdomain %s is not defined.",*region_name,subdomain_ptr->name,subdomain_ptr->yylineno);
	    }
	    else {
		SystemError_yy_ss("subdomain %s で指定されているregion名 %sは未定義",subdomain_ptr->name,*region_name,subdomain_ptr->yylineno);

	    }
	    
	    continue;  /* 邪魔くさいのでこのsubdomainチェックはなし */
	}

	etype = region_ptr -> etype;
	subdomain_ptr -> etype = etype;

	/* 1から */
	for(j = 1; j < regions_in_subdomain; j++) {


	    region_ptr = get_region_ptr_by_name(*(region_name+j));
	    
	    if(region_ptr == NULL) {

		if(english_mesg) {
		    SystemError_yy_ss("region %s used in the definition of subdomain %s is undefined.",*(region_name+j),subdomain_ptr->name,subdomain_ptr->yylineno);
		}
		else {
		    SystemError_yy_ss("subdomain %sに指定されているregion %s は未定義",subdomain_ptr->name,*(region_name+j),subdomain_ptr->yylineno);
		}

	    }

	    if(region_ptr->etype != etype) {

		if(english_mesg) {
		    SystemError_yy_ss("region %s in subdomain %s does not have proper mesh type.",subdomain_ptr->name,*(region_name+j),subdomain_ptr->yylineno);
		}
		else {
		    SystemError_yy_ss("subdomain %sに指定されているregion %s は基本要素形状が異なる",subdomain_ptr->name,*(region_name+j),subdomain_ptr->yylineno);
		}

	    }
	}

	/* ここは、region番号をユーザ指定とする際に変更が必要 dbg: */

	/*===========================*/
	/* defaultのregion番号の付加 */
	/*          (matno)          */
	/*===========================*/	
	for(j=0;j < regions_in_subdomain; j++) {  /* 順序が逆になっていることに
						  注意する事                 */
	    *(subdomain_ptr -> region_no + j ) = regions_in_subdomain - j;
	}
	
    }

    
    return;
}

		

