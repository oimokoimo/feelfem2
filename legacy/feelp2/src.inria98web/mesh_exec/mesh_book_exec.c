/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   mesh_book_exec.c
 *      Date:   1993/09/06
 *   
 *   Purpose:   メッシュ生成を行う
 *              
 *              現在は、引き数ElemDat構造体からメッシュを生成
 *              
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"

#include "mesh_exec.h"

static MidPoint2D total;

extern int recursive_mesh_div;

mesh_book_exec( mesh_edat_ptr )
     ElemDat *mesh_edat_ptr;
{
    int i,j;

    FILE *fp;

    int solve_elements;
    ElemDat *edat_ptr;

    int domains;             /* これは今回使用せず */
    char *domain_name;       
    Domain *domain_ptr;

    int regions,inner_regions;
    Region *region_ptr;

    int points;
    int isolate_points;
    Point *point_ptr;
    int *mesh_no_order_ptr;

    int etype;
    int matno;
    int nodes;


    /* 将来 mesh_edat_ptrがループになる */

/*
    STRESS;
    DBGWRT("MESH生成が始まりました\n");   
    NORMAL;
*/

    fp = OpenFileToWrite("MESH.GEO");
    StoreDeletefile("MESH.GEO");

    domain_name = mesh_edat_ptr -> domain_name;

    
    
    domain_ptr = get_domain_ptr_by_name( domain_name );

    etype = domain_ptr -> etype;
    nodes = get_region_nodes( domain_ptr -> name );
    
    if(nodes == 0) {
	SystemWarning_s("domain %s の節点数が指定されていません",
			domain_ptr-> name);
	nodes = DEFAULT_NODES;   /* これは今２００ */
    }
    
    regions = domain_ptr->regions;
    if(regions == 0) {
	SystemAbort("領域が設定されていません(regions=0)\n");
    }

    inner_regions = 0;
    for(i=0;i<regions;i++) {
	region_ptr = get_region_ptr_by_name(*(domain_ptr->region_name+i));
	inner_regions = inner_regions + region_ptr->edges -1;
    }

    /* 【第一行】 */
    /* 領域数、内部領域数 */

    /* DBGWRT("領域数  %d   内部領域数 %d\n",regions,inner_regions); */
    fprintf(fp,"%4d%4d\n",regions,inner_regions);

    /* 【第二行】 */
    /*  領域の外部節点の個数 */
    for(i=0;i<regions;i++) {
	region_ptr = get_region_ptr_by_name(*(domain_ptr->region_name+regions-i-1));
	/* DBGWRT("%d-%d ",i+1,region_ptr->points[0]); */
	fprintf(fp,"%4d ",region_ptr->points[0]);

	/* メッシュ生成時のmatnoの格納 */
	/* region_ptr -> mesh_matno = i + 1; 廃止*/
	
    }
    fprintf(fp,"\n");
    /* DBGWRT("\n"); */

    /* 【第三行】 */
    /* 内部境界の構成点数 */
    if(inner_regions != 0) {
	for(i=0;i<regions;i++) {
	    /* point_ptr->mesh_no と対応していないと駄目 */
	    /* このmesh_noは、point_checkで実行している、ここと整合性を取っている */
	    /*                                               ↓この順番に統一(94/02/14)*/
	    region_ptr = get_region_ptr_by_name(*(domain_ptr->region_name+regions-i-1));
	    
	    for(j=1;j<region_ptr->edges;j++) {
		/* DEBWRT("%d-%d ",tmp+1,region_ptr->points[j]); */
		    fprintf(fp,"%4d ",region_ptr->points[j]);
	    }
	}
	fprintf(fp,"\n");
	/* DBGWRT("\n"); */
    }
    else {
	/* 内部境界のが無い場合 */
	/* fprintf(fp,"    0\n");            1993/12/22渡辺さんに聞いて変更 */
	/* DBGWRT("内部境界は無し\n"); */
    }
	
    /*==============*/
    /* 外周点の指定 */
    /*==============*/
    for(i=0;i<regions;i++) {
	/* matnoからregion_ptrを呼び出す
	 * domain dom(reg1,reg2)としたときに、reg1,reg2の順になる
	 * ようにする  (1993/12/21)
	 *  ↑ これはMESH.GEOの第一regionが連続番号の必要の要請から
	 *
	 */

	matno = i + 1;    /* matnoが連番でなければ変更を要する dbg: */

	region_ptr = get_region_ptr_by_domain_matno(domain_ptr->name,
						    matno             );

/*	fprintf(stderr,"DOMAIN %s MATNO %d  -> REGION %s\n",
		domain_ptr->name,matno,region_ptr->name);
*/

	points = region_ptr->points[0];

	for(j=0;j<points;j++) {
	    /* 【注意】 mesh_bookでは向きが逆だってさ */
	    point_ptr = get_point_ptr_by_name(region_ptr->compos[0][points-j-1]);
	    /* DBGWRT(" %3d",point_ptr->mesh_no); */
	    fprintf(fp," %3d",point_ptr->mesh_no);
	}
	/* DBGWRT("\n"); */
	fprintf(fp,"\n");
    }

    /* 初期節点数、孤立節点数の指定 */
    points = how_many_outer_edge_points() + how_many_inner_edge_points();


    /* DBGWRT("%4d",points); */
    fprintf(fp,"%4d",points);

    isolate_points = how_many_isolate_points();

    /* DBGWRT("%4d\n",isolate_points); */
    fprintf(fp,"%4d\n",isolate_points);


    /* メッシュ生成用節点座標 */
    /* 注意 point_check.cで、孤立節点番号を、外側、内部の後に
       連番で登録している。そのため、次の様なことが可能。
     */
    points = points + isolate_points;  
    mesh_no_order_ptr = get_mesh_point_no_order_ptr();

    for(i=0;i<points;i++) {
	point_ptr = get_nth_point_ptr(*(mesh_no_order_ptr+i));
	/* DBGWRT("%d  %f %f\n",point_ptr->mesh_no,point_ptr->x,point_ptr->y); */
	fprintf(fp,"%f %f\n",point_ptr->x,point_ptr->y);
    }


    /* メッシュのタイプ */
    switch( etype ) {
      case TRI:
	fprintf(fp,"%d\n",3);
	/* DBGWRT("生成メッシュは三角形\n"); */
	break;

      case RECT:
	fprintf(fp,"%d\n",4);
	/* DBGWRT("生成メッシュは四角形\n"); */
	break;

      default:
	SystemAbort("mesh_book_exec()  予期しない基本要素形状\n");
    }

    
    /* 節点数をかく */
    nodes = get_region_nodes( domain_name );
    if(nodes == 0) {
	nodes = DEFAULT_NODES;
	SystemWarning_d("節点数は既定値 %d を採用した",nodes);
    }
    fprintf(fp,"%d\n",nodes);
    /* printf("節点数 %d\n",nodes); */
    

    fclose(fp);

    /*=====================================*/
    /*  MESH.PRM の作成                    */
    /*=====================================*/

    /* 中間節点情報の整理 */

    mid_info_for_meshbook( mesh_edat_ptr, &total);
    
    fp = OpenFileToWrite("MESH.PRM");
    StoreDeletefile("MESH.PRM");
    StoreDeletefile("MESH.MID");
    StoreDeletefile("MESH.PLN");


    fprintf(fp,"%5d\n",total.edge_points);

    if(total.edge_points > 0) {
	for(i=0;i<total.edge_points;i++) {
	    fprintf(fp,"%lf ",total.edge[i]);
	}
	fprintf(fp,"\n");
    }

    fprintf(fp,"%5d\n",total.inner_points);
    
    if(total.inner_points > 0 ) {
	for(i=0;i<total.inner_points;i++) {
	    fprintf(fp,"%lf %lf\n",total.mid_x[i],total.mid_y[i]);
	}
    }
    
    fclose(fp);

    /*=====================================*/
    /*  MESH.REF の作成                    */
    /*=====================================*/

    make_MESH_REF( mesh_edat_ptr, &total);
    
    fprintf(stderr,"MESH Generation starts...");  /* dbg: */

    switch(etype) {
      case RECT:
	system(MESH_EXEC_COMMAND_TRI);

	for(i=0;i<recursive_mesh_div;i++) {
	    system(MESH_EXEC_COMMAND_DIV);
	}

	system(MESH_EXEC_COMMAND_QUA);
	system(MESH_EXEC_COMMAND_MID);
	system(MESH_EXEC_COMMAND_FIN);
	break;
	
      case TRI:
	system(MESH_EXEC_COMMAND_TRI);

	for(i=0;i<recursive_mesh_div;i++) {
	    system(MESH_EXEC_COMMAND_DIV);
	}

	system(MESH_EXEC_COMMAND_MID);
	system(MESH_EXEC_COMMAND_FIN);
	break;

      default:
	SystemAbort("@mesh_book_exec");
	break;
    }

    fprintf(stderr,"done\n");

    /*======================*/
    /*  境界、節点情報取得  */
    /*======================*/
    get_mesh_data(); /* Point構造体の,Point -> node_no の設定
			境界構造体の作成                      */

    return;
}
