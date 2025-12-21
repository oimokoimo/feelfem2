/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_MESH_REF_bamg.c
 *      Date:   1997/06/04
 *   
 *   Purpose:   make MESH REF data in BAMG_BTOF_FILE_
 *   Functions: 
 *              
 *              
 */


#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"
#include "../mesh_exec/mesh_exec.h"

make_MESH_REF_bamg(fp, mesh_edat_ptr , total_ptr )
     FILE *fp;
     ElemDat *mesh_edat_ptr;
     MidPoint2D *total_ptr;
{
    int i,j,k;

    int          domains;
    char        *domain_name;    /* 領域名  (一つだけを確認する為) */
    int          edats;          /* メッシュ生成のパターン数       */
    ElemDat     *edat_ptr;       /* そのパターンへのポインタ       */
    MidPoint2D   mid_point_2d;   /* 中間節点に関する情報を得る為   
				    ポインタでないことに注意！     */

    int          edge_points;        /* 辺上節点の数 */
    int          inner_points;       /* 内部節点の数 */

    int          total_edge_points;  /* 全節点に関する辺上節点の数 */
    int          total_inner_points; /* 全節点に関する内部節点の数 */

    int          edge_flag[MAX_MID_POINTS];   /* 辺上の点の使用フラグ   */
    int          inner_flag[MAX_MID_POINTS];  /* 要素内節点の使用フラグ */

    int          find_flag;

    domains = how_many_domains();
    if(domains != 1) {
	SystemWarning("現在のメッシュ生成によればdomainは一つ(make_MESH_REF)");
    }
    
    edats = how_many_mesh_edat_data();

    total_edge_points  = total_ptr -> edge_points;
    total_inner_points = total_ptr -> inner_points;


    /* 【要素節点データ集合数を書く】 */
    fprintf(fp,"%5d\n",edats);

    for(i=0;i<edats;i++) {
	edat_ptr = get_nth_mesh_edat_ptr(i);
	
	if(i == 0) {
	    domain_name = edat_ptr -> domain_name;
	}
	else {
	    if(!streq( domain_name , edat_ptr -> domain_name)) {
		SystemAbort("現在のメッシュ生成では、複数のdomainを指定できない");
	    }
	}

	/* edatnoの整合性の確認 */
	if(edat_ptr->edatno != i+1) {
	    /*
	    SystemAbort("edatnoの整合性が不正(make_MESH_REF)");
	    */


	}

/*	fprintf(stderr,"チェックライト edatnoの整合性 i+1=%d edatno=%d\n",
		i+1,edat_ptr->edatno);
*/


	/* 中間節点データの取得 */
	mid_info_for_meshbook( edat_ptr , &mid_point_2d);
	
	edge_points   = mid_point_2d.edge_points;
	inner_points  = mid_point_2d.inner_points;

	/* 【辺上中間節点情報を書く】*/
	fprintf(fp,"%5d\n",edge_points);
	
	if(edge_points != 0) {
	    for(j=0;j<edge_points;j++) {
		find_flag = NO;
		for(k=0;k<total_edge_points;k++) {
		    if(total_ptr->edge[k] == mid_point_2d.edge[j]) {
			find_flag = YES;
			/* 【辺上の使用節点番号を書く】*/
			fprintf(fp,"%5d",k+1);
			break;
		    }
		}
		if(find_flag == NO) {
		    SystemAbort("対応する辺上節点が全体節点データに無い(MESH.REF)");
		}
	    }
	    /* 【辺上使用節点リストの改行を書く】*/
	    fprintf(fp,"\n");
	}

	/* 【内部節点情報を書く 】 */
	fprintf(fp,"%5d\n",inner_points);

	if(inner_points != 0) {
	    for(j=0;j<inner_points;j++) {
		find_flag = NO;
		for(k=0;k<total_inner_points;k++) {
/* dbg:
		    printf("check x  y  %lf %lf <--> %lf %lf\n",
			   total_ptr->mid_x[k],total_ptr->mid_y[k],
			   mid_point_2d.mid_x[j],mid_point_2d.mid_y[j]);
*/
		    
		    if(total_ptr->mid_x[k] == mid_point_2d.mid_x[j] &&
		       total_ptr->mid_y[k] == mid_point_2d.mid_y[j]    ) {
			find_flag = YES;
			/* 【内部の使用節点番号を書く】*/
			fprintf(fp,"%5d",k+1);
			break;
		    }
		}

		if(find_flag == NO) {
		    SystemAbort("対応する内部節点が全体節点データに無い(MESH.REF)");
		}
	    }
	    /* 【内部使用節点リストの改行を書く】*/
	    fprintf(fp,"\n");
	}
    }
}
