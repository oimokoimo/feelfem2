/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_ip_data.c
 *      Date:   1994/02/0
 *   
 *   Purpose:   mesh生成時節点番号と実節点番号対応データ作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"

void make_ip_data( fp )
     FILE *fp;
{
    int i;
    int columns;
    int points;
    int *point_no_ptr;
    Point *point_ptr;

    fprintf(fp,"%s\n",KEY_IP_REAL);   /* 最初のキーワード作成 */

    points       = how_many_points();
    point_no_ptr = get_mesh_point_no_order_ptr();  /* 初期節点->Point構造体
						      番号対応配列 */

    columns = 0;
    for(i=0;i<points;i++) {
	point_ptr = get_nth_point_ptr(*(point_no_ptr + i));
	if(point_ptr->mesh_no != i+1) {
	    SystemAbort("illegal data @ make_ip_data");
	}
	fprintf(fp,"%8d",point_ptr->node_no);
	columns++;
	if(columns == 8) {
	    fprintf(fp,"\n");
	    columns=0;
	}
    }

    if(columns != 0) fprintf(fp,"\n");

    return;
}

	

