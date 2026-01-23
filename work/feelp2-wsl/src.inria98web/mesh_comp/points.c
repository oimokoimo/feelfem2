/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File: points.c
 *      Date: 1993/06/03(Modified)
 *   
 *   Purpose: point文の処理
 *            
 */

#include "../feel_def/feel_def.h" 
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../feel_def/feel_msg.h"    /* modernize 2026/01/21 */
#include "../system/system.h"
#include "mesh_comp.h"

static Point *point[MAX_POINTS];
static int    points = 0;
int is_same_point( double x, double y, char *name);
   

void point_2d_st()
{
    double x,y;
    char *cp;

    if(points == MAX_POINTS) {
	if(english_mesg) {
	    SystemError("Too many points specified.");
	}
	else {
	    SystemError("point指定が多すぎる");
	}

	pop(); pop(); pop();
	return;
    }

    y  = PopDouble();
    x  = PopDouble();
    cp = PopString();

    is_same_point(x,y,cp); /* Make Error Message */

    point[points] = (Point *)FEEL_GetMemory( sizeof( Point) );

    point[points]->x = x;
    point[points]->y = y;
    point[points]->name = cp;

    point[points]->concern_regions = 0;
    point[points]->node_no    =  NO;
    point[points]->mesh_no    =  NO;        /* メッシュ生成時番号の初期化 */
    point[points]->point_type =  ISOLATE;   /* 節点種別の初期化 */
    
    point[points]->yylineno = yylineno_info();

    if(get_mesh_name_type_by_name( point[points]->name)) {

	if(english_mesg) {
	    SystemError_yy_s("point name %s is already defined for other object's name.",point[points]->name,yylineno_info());
	}
	else {
	    SystemError_yy_s("point名 %s は既に使用されています",point[points]->name,yylineno_info());
	}

    }
    store_mesh_name( point[points]->name , MESH_POINT );


    points += 1;

    return;
}

Point *get_point_ptr_by_name( name )
     char *name;
{
    int i;

    for(i=0;i<points;i++) {
	if(streq(name,point[i]->name)) {
	    return( point[i] );
	}
    }
    return(NULL) ;
}


int is_same_point( x, y, name)
     double x,y;
     char   *name;
{
    int i;
    int ret_flag;

    ret_flag = NO;

    for(i=0;i<points;i++) {
	if(point[i]->x == x && point[i]->y == y) {
	    if(english_mesg) {
		SystemError_ss("point %s and %s is identical.",name,point[i]->name);
	    }
	    else {
		SystemError_ss("point %s と %s は同じ座標である",name,point[i]->name);
	    }


	    ret_flag = YES;
	}
    }
    return(ret_flag);
}


get_point_xy_by_name( name ,x , y)
     char *name;
     double *x,*y;
{
    int i;

    for(i=0;i<points;i++) {
	if(streq(name,point[i]->name)) {
	    *x = point[i]->x;
	    *y = point[i]->y;
	    return;
	}
    }

    SystemAbort_s("Point %s is not defined.",name);
}


int how_many_points()
{
    return(points);
}

Point *get_nth_point_ptr( n )
    int n;
{
    if(n < 0 || n >= points) {
        SystemAbort("Illegal nth point ptr request.");
    }
    return(point[n]);
}

int get_point_number_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<points;i++) {
	if(streq(name,point[i]->name)) return(i);
    }
    SystemAbort_s("Point %s is not defined.",name);
    
}


void put_point_node_no( mesh_no , node_no , name )
     int mesh_no;  /* 一時番号     */
     int node_no;  /* 最終節点番号 */
     char **name;  /* 名称をいれとく(Boundary2D構造体に) */
{
    int i;

    for(i=0;i<points;i++) {
	if(point[i]->mesh_no == mesh_no) {

	    /* Boundary2D構造体のメンバに反映 */
	    *name = point[i]-> name; 

	    if(point[i]->node_no == node_no) return;  /* 既に登録済み */
	    
	    if(point[i]->node_no != NO ) {

		if(english_mesg) {
		    SystemWarning("There are conflict between the final node number and the number at mesh generation(put_point_node_no)");
		}
		else {
		    SystemWarning
		      ("最終節点番号とmesh生成時番号に矛盾(put_point_node_no)");
		}

		return;
	    }

	    point[i]->node_no = node_no;

/*	    fprintf(stderr,"point %s は最終番号%d\n",point[i]->name,node_no);
*/
	    return;
	}
    }

    if(english_mesg) {
	SystemAbort("No correspoinding point while mesh generating(points.c)");
    }
    else {
	SystemAbort("mesh生成時番号に相当する点が無い(points.c)");
    }

    return;
}

	
