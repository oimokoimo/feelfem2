/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   mesh_exec_1D.c
 *      Date:   1994/11/4
 *   
 *   Purpose:   make 1-dimensional mesh data file 
 *   Functions: 
 *              
 *              計画: １次元メッシュはここですべて必要なデータを作成
 *                    し、その都度データを構成する。
 *              
 *              
 */
#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"


#define MAX_NODEP_1D  20  /* 一要素あたりの最大節点数 */
#define MAX_SEGMENT   20  /* 一領域あたりの最大線分数 */

typedef struct {   /* 1-dimensional mesh generation */
    char *region_name;   /* region名                 */  
    int      segments;   /* region内線分数           */
    int region_points;   /* regionに割り当てる要素数 */

    double     length;   /* region半径 */
    
    int   segment_points[MAX_SEGMENT];   /* 各線分の要素数             */
    char *segment_name[MAX_SEGMENT][2];  /* 各線分の端点の点の名称     */
    int   segment_node[MAX_SEGMENT][2];  /* 各線分の端点の最終節点番号 */
    double segment_cord[MAX_SEGMENT][2]; /* 各線分のｘ座標 */
    double segment_length[MAX_SEGMENT];
    
    int   matno;   /* 要素物性番号 */

} RegionSegment;

static RegionSegment rsdata[MAX_REGIONS];


mesh_exec_1D( mesh_edat_ptr )
     ElemDat *mesh_edat_ptr;
{
    int i,j,k;
    int points;

    int nodes;         /* 全節点数             */
    int node_points;   /* 各要素あたりの節点数 */


    char   *domain_name;
    Domain *domain_ptr;
    double  domain_length;   /* 領域の長さ */

    int     regions;
    Region *region_ptr;

    Node   *node_ptr;
    double node_cord[MAX_NODEP_1D];    /* 節点の局所座標 */
    Frac r;

    domain_name = mesh_edat_ptr -> domain_name;
    domain_ptr = get_domain_ptr_by_name(domain_name);

    /* 節点数の取得 */
    nodes = get_region_nodes(domain_ptr -> name);
    if(nodes == 0) {
	SystemWarning_s("domain %s の節点数が指定されていません",
			domain_ptr->name);
	nodes = DEFAULT_NODES;
    }

    regions = domain_ptr->regions;
    if(regions == 0) {
	SystemAbort("regionが無い(mesh_exec_1D)");
    }

    if(mesh_edat_ptr -> etype != LINE) {
	SystemAbort("mesh_exec_1DにLINE以外のmesh_edat_ptrが…");
    }

    node_points = mesh_edat_ptr->nodes;  /* 要素内節点数 */

    if(node_points > MAX_NODEP_1D) {
	SystemAbort("Too many nodes for LINE element(mesh_exec_1D)");
    }
    
    for(i=0;i<node_points;i++) {
	node_ptr = *(mesh_edat_ptr->node_ptrptr + i);
	r = node_ptr->r;

	if(node_ptr->freedom != 1) {
	    SystemAbort("エルミート要素系には未対応(LINE element)");
	}

	if(*(node_ptr->node_type) != D0) {
	    SystemAbort("エルミート要素系には未対応(LINE element)");
	}

	node_cord[i] = (double)(r.bunsi)/(double)(r.bunbo);
	fprintf(stderr,"i=%d  %f\n",i,node_cord[i]);
    }

    /* RegionSegmentデータの第一段階の設定 */
    domain_length = 0.0;
    for(i=0;i<regions;i++) {
	region_ptr = get_region_ptr_by_name( *(domain_ptr->region_name + i));

	set_rsdata(domain_ptr,region_ptr,&rsdata[i]);

	domain_length = domain_length + rsdata[i].length;
    }

    fprintf(stderr,"domain length = %f\n",domain_length);

    /* 各regionへの、要素数の割り振り */
    /* ここは、もしメッシュの疎密をサポートする場合は書き換えないといけない */
    for(i=0;i<regions;i++) {
	rsdata[i].region_points = (int) ((double)nodes*rsdata[i].length
					              /domain_length);
	fprintf(stderr,"SUB領域 %s への 要素数割り当て %d\n",
		rsdata[i].region_name,rsdata[i].region_points);
    }

    /* 各regionの各segmentに対する要素数の割り振り */
    for(i=0;i<regions;i++) {
	points = rsdata[i].region_points;
	for(j=0;j<rsdata[i].segments;j++) {
	    rsdata[i].segment_points[j] = (int) ((double)points*
						 rsdata[i].segment_length[j]
						 /rsdata[i].length);
 /* fprintf(stderr,"segment %d-%d   %d\n",i,j,rsdata[i].segment_points[j]); */
	}
    }
    
    return;
}


/* 個々のRegion Segmentデータ作成・格納する */
set_rsdata(domain_ptr,region_ptr,rs_ptr)
     Domain *domain_ptr;
     Region *region_ptr;
     RegionSegment *rs_ptr;
{
    int i,j;
    int points;
    int matno;

    double length;
    double x,y;
    double x1,x2;

    points = region_ptr -> points[0];
    rs_ptr -> region_name = region_ptr -> name;           /* 領域名 */
    rs_ptr -> segments    = region_ptr -> points[0] - 1;  /* 線分数 */
    
    if(region_ptr -> edges != 1) {
	SystemAbort("Illegal region specification(mesh 1D)");
    }


    /* 1次元 region 線分の各要素の計算 */
    length = 0.0;

    for(i=0;i<points-1;i++) {
	rs_ptr->segment_name[i][0] = region_ptr -> compos[0][i];
	rs_ptr->segment_name[i][1] = region_ptr -> compos[0][i+1];

	get_point_xy_by_name( region_ptr -> compos[0][i],&x1,&y);
	rs_ptr -> segment_cord[i][0] = x1;

	get_point_xy_by_name( region_ptr -> compos[0][i+1],&x2,&y);
	rs_ptr -> segment_cord[i][1] = x2;
	
	rs_ptr -> segment_length[i] = x2 - x1;

	if(x2 - x1 <= 0) {
	    SystemAbort("点の指定が正の向きになっていない");
	}
	length += (x2 - x1);
    }

    matno = get_domain_region_no(domain_ptr->name,region_ptr->name);
    rs_ptr->matno  = matno;
    rs_ptr->length = length;
    fprintf(stderr,"region %s  matno  = %d\n",region_ptr->name,matno);
    fprintf(stderr,"region %s  length = %f\n",region_ptr->name,length);

    return;
}












