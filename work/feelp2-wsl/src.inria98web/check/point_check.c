/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   point_check.c
 *      Date:   1993/09/07
 *   
 *   Purpose:   点に関するチェックと、情報付加
 *
 *               ○点の種別の登録
 * 	           →外部境界点、内部境界点、孤立点
 * 	         ○点のmeshno(メッシュ生成時番号)付加
 *                 →連番号付加
 *
 * Functions:   point_check()
 *              int *get_mesh_point_no_order_ptr() 初期節点番号→point構造体
 *                                                 変換テーブルを返す
 *                         
 *              int how_many_outer_edge_points() region外部境界節点数
 *              int how_many_inner_edge_points() region内部境界節点数
 *              int how_many_isolate_points() 孤立節点数
 *              
 */      

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"

static int *mesh_point_no_order;
static int outer_edge_points;
static int inner_edge_points;
static int isolate_points;

void point_check_order()
{
    int i,j,k,l;

    Domain *domain_ptr;
    int domains;

    Region *region_ptr;
    int regions;

    Point *point_ptr;
    int points;
    int edge_points;

    int edges;
    
    int point_no;



    /* 領域情報→節点種別の確定 */
    domains = how_many_domains();
    for(i=0;i<domains;i++) {
	domain_ptr = get_nth_domain_ptr(i);
	regions = domain_ptr->regions;
	
	
	for(j=0;j<regions;j++){


	    region_ptr = get_region_ptr_by_name(*(domain_ptr->region_name + 
						  regions -j - 1 ));

	    if(region_ptr == NULL) continue;   /* これは、domain宣言内の
						  regionが未定義の時起こる */
		
	    edges = region_ptr->edges;

	    for(k=0;k<edges;k++) {
		points = region_ptr->points[k];

		for(l=0;l<points;l++) {
		    point_ptr = get_point_ptr_by_name( region_ptr->compos[k][l] );

		    if(k == 0 ) {  /* 外部境界点 */
			if(point_ptr->point_type == INNER_EDGE) {

			    if(english_mesg)
			      SystemWarning_s("Point %s is defined as both inner and outer region point",point_ptr->name);
			    else
			      SystemWarning_s("点 %sは、regionの内部および外部境界点として定義されている",point_ptr->name);

			}
			point_ptr-> point_type = EDGE;
		    }

		    else {         /* 内部境界点 */
			if(point_ptr->point_type  == EDGE) {
			    if(english_mesg) 
			      SystemWarning_s("Point %s is defined both inner and outer region point",point_ptr->name);
			    else
			      SystemWarning_s("点 %sは、regionの内部および外部境界点として定義されている",point_ptr->name);

			}
			point_ptr-> point_type = INNER_EDGE;
		    }
		}
	    }
	}
    }


    /* 点番号付加 region外部境界点,region内部境界点,孤立点の順で番号を付加 */

    
    points = how_many_points();
    point_no = 0;

    outer_edge_points = 0;
    inner_edge_points = 0;
    isolate_points    = 0;

    /* 先ずはregion外部境界点 */

    domains = how_many_domains();
    for(i=0;i<domains;i++) {
	domain_ptr = get_nth_domain_ptr(i);
	regions = domain_ptr->regions;
	for(j=0;j<regions;j++) {                /* 第一region ↓ ！！！！！ (94/02/14) */
	    region_ptr = get_region_ptr_by_name(*(domain_ptr->region_name+regions -j-1));

	    if(region_ptr==NULL) continue;   /* これは、domain定義のregionが
						未定義の時に起こり得る       */

	    edge_points = region_ptr->points[0];   /* [0] は外部境界を意味している */
	    for(k=0;k<edge_points;k++) {
		point_ptr = get_point_ptr_by_name(region_ptr->compos[0][k]);

		if(point_ptr->mesh_no != NO) continue;  /* 既に設定済み */

		point_no++;
		point_ptr->mesh_no = point_no;          /* 初期節点番号設定 */

		outer_edge_points++;
	    }
	}
    }


    /*======================================================*/
    /* 次にregion内部境界点                                 */
    /* メッシュ生成上、穴が含まれるregionの順番が極めて重要 */
    /*======================================================*/
    

    for(i=0;i<domains;i++) {
	domain_ptr = get_nth_domain_ptr(i);
	regions = domain_ptr->regions;
	for(j=0;j<regions;j++) {                /* 第一region ↓ ！！！！！ (94/02/14) */
	    region_ptr = get_region_ptr_by_name(*(domain_ptr->region_name+regions -j-1));


	    if(region_ptr == NULL) continue;
	    /* これは、domain定義内region名が未定義の時に起こる */

	    edges = region_ptr->edges;
	    for(l = 1; l < edges;l++) {            /*  1 からはじまるのは内部境界だから*/
		edge_points = region_ptr->points[l];   /* [l] 内部境界を意味している */
		for(k=0;k<edge_points;k++) {
		    int tmp;
		    tmp = edge_points - k - 1;     /* mesh_book_execで内部境界が正の向き
						      の為の処置 */
		    point_ptr = get_point_ptr_by_name(region_ptr->compos[l][tmp]);

		    if(point_ptr->mesh_no != NO) {
			if(english_mesg) {
			    SystemError_s("Duplicated point name in inner boundary(name: %s)",point_ptr->name);
			}
			else {
			    SystemError_s("内部境界上の点が重複している(重複名称%s)",point_ptr->name);
			}
		    }
		    point_no++;
		    point_ptr->mesh_no = point_no;          /* 初期節点番号設定 */
		    
		    
		    inner_edge_points++;
		}
	    }
	}
    }


    /* 最後に孤立点 */
    for(i=0;i<points;i++) {
	point_ptr = get_nth_point_ptr(i);
	
	if(point_ptr->point_type == ISOLATE) {
	    point_no++;
	    point_ptr->mesh_no = point_no;
	    isolate_points++;
	}
    }

    if(points != point_no) {
	if(english_mesg) {
	    SystemAbort("Inner ERROR at point_check.c");
	}
	else {
	    SystemAbort("点番号付加内部エラー");
	}
    }

/*
    STRESS;
    printf("outer %d  inner %d  isolate %d\n",outer_edge_points,
	                                      inner_edge_points,
	                                      isolate_points);
    NORMAL;
*/

    mesh_point_no_order = (int *)FEEL_GetMemory(points * sizeof(int));
    
    
    /* 領域 mesh_point_no_orderに、mesh生成時点番号→point構造体番号の変換
       テーブルを作成する */
    for(i=0;i<points;i++) {
	point_ptr = get_nth_point_ptr(i);
	
	*(mesh_point_no_order + point_ptr->mesh_no - 1) = i;
    }

    return;
}

int  point_nth_to_point_order_no( no ) /* This is for bamg/refine statement */
     int no;
{
  int i;
  int points;

  points = outer_edge_points + inner_edge_points + isolate_points;

  for(i=0;i<points;i++) {
    if(*(mesh_point_no_order+i) == no) {
      return(i);
    }
  }
  SystemAbort("Inner Error point_nth_to_point_order_no");
}


int *get_mesh_point_no_order_ptr()
{
    return(mesh_point_no_order);
}
/*regionの外部境界の点数を返す */
int how_many_outer_edge_points()
{
    return(outer_edge_points);
}

/* regionの内部境界の点数を返す */
int how_many_inner_edge_points()
{
    return(inner_edge_points);
}



int how_many_isolate_points()
{
    return(isolate_points);
}



