/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   boundary_data.c
 *      Date:   1993/12/06
 *   
 *   Purpose:   境界条件に関するデータの作成
 *              store_boundary_data()            get_mesh_data.cから呼ぶ
 *              make_boundary_data_for_bc_main() make_feel_data_file.cから呼ぶ
 *              
 *              make_DCOND_NSET_data()
 *              make_NCOND_EDAT_data()
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "boundary.h"
#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"
#include "../element/element.h"
#include "../mesh_exec/mesh_exec.h"


#define MAX_TMP_POINTS 1000

static Boundary2D *bd2d[MAX_LINES];
static int        bd2ds = 0;

void store_boundary_data(from,to,points,region_no,iptr)
     int  from,to,points,region_no;
     int *iptr;
{
    /* 
     * mesh_book_exec専用プログラム
     *
     * 制限がたくさんあります。
     *
     * domain は 一つ。
     * よって、節点パターンは全て同じ
     * 境界上の点は等分割が原則
     *
     */

    int i;

    bd2d[bd2ds] = (Boundary2D *)FEEL_GetMemory(sizeof(Boundary2D));
    
    bd2d[bd2ds]->points    = points;
    bd2d[bd2ds]->from      = from;
    bd2d[bd2ds]->to        = to;

    
    bd2d[bd2ds]->node_no   = iptr;
    bd2d[bd2ds]->region_no = region_no;


    /* Point ptr への反映 */
    put_point_node_no(from , *iptr             ,&(bd2d[bd2ds]->from_name) );
    put_point_node_no(to   , *(iptr + points-1),&(bd2d[bd2ds]->to_name  ) );

/*    fprintf(stderr,"登録  from %s to %s\n",bd2d[bd2ds]->from_name,
	                                   bd2d[bd2ds]->to_name);
*/

    bd2ds++;
    return;
}

Boundary2D *get_b2d_ptr_by_both_ends( from ,to )
     char *from,*to;
{
    int i;

/*    fprintf(stderr,"bd2ds = %d\n",bd2ds);
    fprintf(stderr,"from  = %s\n",from);
    fprintf(stderr,"to    = %s\n",to);
*/

    for(i=0;i<bd2ds;i++) {
/*	fprintf(stderr,"bd2d[%d]->from_name = %s , ->to_name = %s\n",
		i,bd2d[i]->from_name , bd2d[i]->to_name);
*/
	if(streq(bd2d[i]->from_name, from) &&
	   streq(bd2d[i]->to_name  ,to   )) {
	    return(bd2d[i]);
	}

	if(streq(bd2d[i]->from_name, to ) &&
	   streq(bd2d[i]->to_name  ,from)) {
	    return(bd2d[i]);
	}
    }
    
    SystemError_ss("境界要素 %s-%s が境界上にない",from,to);
    SystemAbort("対応するBoundary2D構造体が存在せず");
}

    

void make_boundary_data_for_bc_main( fp )
     FILE *fp;
{
    int i,j,k,l;
    int find_flag;
    int no,no2;
    int istart,iend;
    int solves;
    int dconds,nconds;
    int boundaries;

    int node_set_no;

    Solve *solve_ptr;
    SolveElement  *solve_element_ptr;
    ElementFORT77 *elem77_ptr;
    FEMvarinfo    **fem_varinfo_ptrptr,*fem_varinfo_ptr;

    DirichletData **d_ptrptr,*d_ptr;
    NeumannData   **n_ptrptr,*n_ptr;

    ElemDat *mesh_edat_ptr;
    ElemDat *elem_edat_ptr;

    int      type;
    Point   *point_ptr;
    Line    *line_ptr;
    char    **b_name,*name;

    MidPoint2D  mesh_midpoint;
    MidPoint2D  elem_midpoint;

    int line_points;            /* LINE文内の点の数     */

    int boundary_points;        /* 境界の点の最小集合数 */
    int use_points;             /* 境界の点の使用点数   */
    int corner_points;          /* 端点の名前登録用、二重に定義しないよう… */
    char *corner_name[MAX_TMP_POINTS][2]; /* 端点の名前登録用 
					 変数名、点の名称を入れる
				     ほんとうは、MAX_POINTS+1必要だが… 
				     これは各solve文内で、
				     dbc:  u = ... , on ab;  <-  点bについて
				     dbc:  u = ... , on bd;  <-  重複
				     に対し、先着優先にする */


    int total_points;           /* 全体の  要素内節点数 */
    int total_edge_points;      /* 全体の  境界節点数   */
    int total_inner_points;     /* 全体の  内部節点数   */
    int elem_points;            /* 指定要素の  要素内節点数 */
    int elem_edge_points;       /* 指定要素の  境界節点数 */
    int elem_inner_points;      /* 指定要素の  内部節点数 */

    int var_edge_points;

    int edge_points;                     /* 境界ONEユニットの数 */
    int use_flag[MAX_POINTS_IN_LINE];    /* これは端を含む */
    int eq_plus [MAX_POINTS_IN_LINE]; 

    /* まず下の'elem_edge_***'ルーチンでの設定の後に上の配列に代入処理する */
    /* 下のルーチンに対応する辺上中間節点はmid_info構造体に情報があるから…*/
    int elem_edge_use_points;
    int elem_edge_use_flag[MAX_NODES_PER_ELEMENT]; /* 各要素節点(elem_edat)
						      でのfem変数の使用状況 */
    int elem_edge_use_plus[MAX_NODES_PER_ELEMENT];

    Element *element_ptr; 
    char *element_name;   

    char *domain_name;        /* 複数domain可能時に要チェック 現在無使用 */
    Domain *domain_ptr;       /* 複数domain可能時に要チェック 現在無使用 */
    char *fem_var_name;
    


    /*
     * 制限  domainは一つ  ←  節点パターンが一つ
     *
     */

    /* 将来複数domain拡張時には、指定の境界がsolve文内のどの
     * domainに所属しているか、求める必要がある
     * これは、1: solve文内に複数のSolveElementひいてはdomainがある場合
     *         2: 異なったsolve文で異なったdomainがある場合にわかれる
     *     dbg:
     *     現在はdomainは一つだけなので、その唯一の節点パターンを以て来る
     */
    
    mesh_edat_ptr  = get_nth_domain_elem_dat_ptr( 0 );
    /*====================*/
    /* domainの           */
    /* 中間節点情報を得る */
    /*====================*/
    mid_info_for_meshbook( mesh_edat_ptr , &mesh_midpoint);
    total_points      = mesh_edat_ptr -> nodes;
    total_edge_points = mesh_midpoint.edge_points;
    total_inner_points= mesh_midpoint.inner_points;

    domain_name   = "しりまへんがな";

    /*===========================*/
    /* 先ずは、Dirichlet境界から */
    /*===========================*/
    solves = how_many_solves();
    for(i=0;i<solves;i++) {

	/* Dirichlet条件先着優先指定配列の初期化 
	 *   目的 [1] LINE境界点一致(これは複数のdbc:にまたがる場合
	 *        [2] LINEが複数の線分要素からなる場合
	 */
	corner_points =0;   /* 端点名、関連変数名登録カウンタ */
	   

	solve_ptr = get_nth_solve_ptr(i);

	if(solve_ptr-> solve_elements != 1) {
	    SystemAbort("現在境界条件設定プログラムは複数domainに未対応です");
	}
	solve_element_ptr  = *(solve_ptr -> solve_elem_dat + 0);
	/*     dbg: +0 に注意               ^^^^^^^^^^^^^^^^^^ */

	elem77_ptr         = solve_element_ptr ->elem77_dat;
	elem_edat_ptr      = elem77_ptr -> elem_dat;
	/*====================*/
	/* 各SolveElementの   */
	/* 中間節点情報を得る */
	/*====================*/	
	mid_info_for_meshbook( elem_edat_ptr , &elem_midpoint);
	elem_points      = elem_edat_ptr->nodes;
	elem_edge_points = elem_midpoint.edge_points;
	elem_inner_points= elem_midpoint.inner_points;

	fem_varinfo_ptrptr = elem77_ptr ->fem_var_info_ptrptr;
	
	dconds   = solve_ptr -> d_conditions;
	d_ptrptr = solve_ptr -> d_dat;

	for(j=0;j<dconds;j++) {
	    d_ptr        = *(d_ptrptr + j);
	    boundaries   = d_ptr -> boundaries;

	    fem_var_name = d_ptr -> var;
	    node_set_no  = d_ptr -> b_nodeset;

	    /* FEMvarinfo構造体を得る */
	    for(k=0;k<elem77_ptr->fem_vars;k++) {
		fem_varinfo_ptr = *(fem_varinfo_ptrptr+k);
		if(streq(fem_varinfo_ptr -> fem_var_name,
			 fem_var_name)) {
		    break;
		}
		fem_varinfo_ptr = NULL;
	    }
	    if(fem_varinfo_ptr == NULL) {
		SystemAbort("対応するfemvarinfoデータが無い@boundary_data");
	    }

	    /* ここからは、feel.meshにかなり特殊化した作る
	     * 境界はlineのみ
	     * lineは点の集合
	     */

	    /* elem_edat_ptrの境界節点で、fem_varがどの境界中間節点を
	     * 使っているか調べる
             *
             *   elem_edge_use_points   使用個数
	     *   elem_edge_use_flag[]   使用フラグ
	     *     [0] は端  [1],...[n] が中間点
             */
	    
	    /* まず、elem_edge_use_points に境界中間点が無い場合 */
	    if(elem_edge_points == 0) {
		if(*(fem_varinfo_ptr->ienp) != 1) { /* 頂点自由度なし */
		    SystemAbort("It is impossible to set boundary condition to inner node only element");
		}
		elem_edge_use_points  = 1;
		elem_edge_use_flag[0] = YES;  /* 端 */
		elem_edge_use_plus[0] = 
		  *(fem_varinfo_ptr->iedp + 0);  /* 方程式番号へのincrement */
	    }
	    else {
		switch(elem_edat_ptr -> etype) {
		  case RECT:
		    istart = 5;
		    break;

		  case TRI:
		    istart = 4;
		    break;

		  default:
		    SystemAbort("へんなElemDat->etype!@boundary_data.c");
		}

		iend = istart + elem_edge_points - 1;  /* -1 を引くのは
							* あとで<=で評価するため
							*/

/*		fprintf(stderr,"istart = %d  iend = %d\n",istart,iend);
*/
		elem_edge_use_points = 0;

		/*
		 * dbg: エルミート要素に対する考慮はペンディング
		 *
		 */

		/* まず配列を初期化 */
		for(k=0;k<elem_edge_points+1;k++) { /* 端を含む */
		    elem_edge_use_flag[k] = NO;
		    eq_plus[k]            = 999;  /* dummy 識別用 */
		}
		    
		for(k=0;k<fem_varinfo_ptr->freedom;k++) {
		    no = *(fem_varinfo_ptr->ienp + k);  /* noは対応する
							   ElemDatでの
							   局所節点番号 */

/*		    fprintf(stderr,"no = %d\n",no); */
		    /* 端点を含む場合 */
		    if( no == 1 ) {
			if(elem_edge_use_flag[0] != NO) {
			    SystemAbort("エルミート要素(同一節点同一関数複数自由度)には未対応@boundary_data.c");
			}
			elem_edge_use_flag[0] = YES;
			elem_edge_use_plus[0] = *(fem_varinfo_ptr->iedp+k);
			elem_edge_use_points++;

			if(k != 0) {
			    SystemAbort("なんか変ですナッ！@boundary_data");
			}
		    }
		    if( no >= istart && no <= iend) {

			no2 = no - istart + 1;     /* 端を含みますから… */
/*			fprintf(stderr,"no2 = %d\n",no2); */
			
			if(elem_edge_use_flag[no2] != NO) {
			    SystemAbort("エルミート要素(同一節点同一関数複数自由度)には未対応@boundary_data.c(2)");
			}
			elem_edge_use_flag[no2] = YES;
			elem_edge_use_plus[no2] = *(fem_varinfo_ptr->iedp+k);
			elem_edge_use_points++;
		    }
		}
	    }
	    /* 変数 elem_edge_use_points 
	       配列 elem_edge_use_flag[],elem_edge_use_plus[] の作成終了 */

	    /* ここから
	       配列 use_flag[],eq_plus[]の作成 */
	    use_flag[0] = elem_edge_use_flag[0];  /* 端は必ずある */
	    eq_plus[0]  = elem_edge_use_plus[0];  /* 上と同じ…   */
	    if(use_flag[0] == YES) {
		edge_points = 1;    /* edge_pointはdirichlet条件節点数 */
	    }                       /*                                 */
	    else {
		edge_points = 0;
	    }
	    
	    for(k=0;k<total_edge_points;k++) {

		find_flag = NO;

		for(l=0;l<elem_edge_points;l++) {
		    if(elem_midpoint.edge[l] == mesh_midpoint.edge[k]) {
			use_flag[k+1] = elem_edge_use_flag[l+1];
			eq_plus[k+1]  = elem_edge_use_plus[l+1];
			find_flag = YES;
			break;
		    }
		}
		if(find_flag == NO) {
		    use_flag[k+1] = NO;
		    eq_plus[k+1]  = 9999;
		}
		if(use_flag[k+1] == YES) {
		    edge_points++;
		}
	    }

	    /* デバッグ */
	    /*
	    fprintf(stderr,"----------------\nuse_flag,eq_plus,のデバッグ \n");
	    fprintf(stderr,"          ");
	    for(k=0;k<total_edge_points+1;k++) {
		fprintf(stderr," [%1d]",k);
	    }
	    fprintf(stderr,"\nuse_flag :");
	    for(k=0;k<total_edge_points+1;k++) {
		fprintf(stderr,"%4d",use_flag[k]);
	    }
	    fprintf(stderr,"\neq-plus  :");
	    for(k=0;k<total_edge_points+1;k++) {
		fprintf(stderr,"%4d",eq_plus[k]);
	    }
	    fprintf(stderr,"\n");
	    */
	    
	    b_name = d_ptr -> b_name;    /* 境界名称へのポインタ (char **) */

	    push_boundary_nset_reset();

	    for(k=0;k<boundaries;k++) { 
		/* Point, Line だけ サポート */
		name = *(b_name + k);
		type = get_mesh_name_type_by_name( name );
		switch(type) {
		  case MESH_POINT:
		    /* これは節点上に自由度が無いとだめ、
		       あと、first節点自由度はエルミート型でないこと。
		       (他がエルミートに対応していないので無意味な記述
		        ではあるが、将来の為にこう書いといた)
			*/
		    if(*(fem_varinfo_ptr -> ienp) != 1) {
			/* 図形基本節点に自由度が無い
			   pointは図形基本節点にしか設定出来ない */
			SystemWarning_s("変数%dへのディリクレ条件の点での設定は、頂点に自由度がない為不可(無視しました)");
			continue;
		    }
		    push_boundary_nset_point(fem_var_name, 
					     name ,*(fem_varinfo_ptr ->iedp),
					     corner_name    ,
					     corner_points      );

		    /* corner_name への登録 */
		    corner_points = 
		      add_corner_name( fem_var_name , name ,
				       corner_name,corner_points);
		     
		    break;
		    
		  case MESH_LINE:
		    
    		    line_ptr = get_line_ptr_by_name( name );
		    line_points = line_ptr->points;

		    for(l=0;l<line_points-1;l++ ) {
			push_boundary_nset_line(fem_var_name,
						line_ptr->compos[l],
						line_ptr->compos[l+1],
						use_flag,eq_plus,
						total_edge_points+1,
						corner_name,
						corner_points);
			/* corner pointへの登録 */
			corner_points = 
			  add_corner_name(fem_var_name , 
					  line_ptr->compos[l],
					  corner_name,
					  corner_points);

			corner_points = 
			  add_corner_name(fem_var_name , 
					  line_ptr->compos[l+1],
					  corner_name,
					  corner_points);
		    }
		    break;

		  default:
		    SystemAbort("境界名称のtypeがおかしい(boundary_data)");
		

		} /* switch ( type ) の終わり */
	    } /* boundariesに関するループの終わり */

	    make_boundary_nset(fp,node_set_no);
	} /* d_conditionに関するループの終わり */

    }  /* solves に関するループの終わり */

    /*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
    /*========================================*/
    /* ノイマン境界条件に関する境界要素の作成 */
    /* ここでは、境界辺要素を作成し、境界隣接 */
    /* 要素はサポートしていない               */
    /* 当然、境界上にない節点に関する基底関数 */
    /* は、境界上では恒等的に０でないとだめ。 */
    /*========================================*/
    for(i=0;i<solves;i++) {

	solve_ptr = get_nth_solve_ptr(i);
	if(solve_ptr->solve_elements != 1) {
	    SystemAbort("ノイマン境界要素作成ルーチンは複数domainに未対応");
	}
	
    
	nconds   = solve_ptr -> n_conditions;
	n_ptrptr = solve_ptr -> n_dat;
	
	for(j=0;j<nconds;j++) {
	    n_ptr      = *(n_ptrptr + j );

	    b_name     = n_ptr -> b_name;

	    /* ここで境界名から対応するSolveElementを探さないといけない */
	    solve_element_ptr = *(solve_ptr -> solve_elem_dat + 0);
	    /*   dbg +0 に注意                 ^^^^^^^^^^^^^^^^^^  */
	    elem77_ptr    = solve_element_ptr -> elem77_dat;
	    elem_edat_ptr = elem77_ptr -> elem_dat;

	    /* 各SolveElementの中間節点情報を得る */
	    mid_info_for_meshbook(elem_edat_ptr ,&elem_midpoint);
	    elem_edge_points  = elem_midpoint.edge_points;

	    /*============================*/
	    /* 境界要素の境界節点数の設定 */
	    /*============================*/
	    n_ptr -> boundary_points =  elem_edge_points + 2;
	    
	    boundaries = n_ptr ->boundaries;

	    switch(elem_edat_ptr -> etype) {
	      case RECT:
		istart = 5;
		break;
		
	      case TRI:
		istart = 4;
		break;

	      default:
		SystemAbort("未対応形状＠ノイマン境界作成");
	    }

	    /* この要素での節点使用状況配列の初期化 */
	    edge_points = 1;
	    use_flag[0] = YES;  /* 端点はかならずある */
	    for(k=0;k<total_edge_points;k++) {
		use_flag[k+1] = NO;
	    }

	    for(k=0;k<total_edge_points;k++) {

		for(l=0;l<elem_edge_points;l++) {
		    if(elem_midpoint.edge[l] == mesh_midpoint.edge[k]) {
			use_flag[k+1] = YES; /* +1 は端点を含むから */
			edge_points++;
		    }
		}
	    }
	    if(edge_points != elem_edge_points+1) {
		SystemAbort("データ不正＠ノイマン境界作成＠edge_points");
	    }
	    
	    boundary_edat_reset();
	    
	    for(k=0;k<boundaries;k++) {
		/* LINEでなければならない */
		name = *(b_name + k);
		type = get_mesh_name_type_by_name( name );
		if(type != MESH_LINE) {
		    SystemAbort("ノイマン境界辺がLINEでない(@boundary_data)");
		}

		line_ptr = get_line_ptr_by_name( name );
		line_points = line_ptr -> points;

		for(l=0;l<line_points-1;l++) {
		    push_boundary_edat_line(line_ptr->compos[l],
					    line_ptr->compos[l+1],
					    use_flag,
					    edge_points,
					    total_edge_points+1   );
		}
	    }
	    make_boundary_edat(fp,n_ptr -> belem_no,edge_points);

	}/* ノイマン条件に関するループの終わり */
	
    }/* ノイマン境界の solvesループの終わり */

    return;
}

int add_corner_name( var_name,name ,name_ptr , n)
     char *var_name;
     char *name;
     char *name_ptr[][2];
     int   n;
{
    int i;

    
    if(n == MAX_TMP_POINTS) {
	SystemAbort("NSET作成時、ディリクレ境界条件指定節点数が多すぎる(boundary_data)");
    }

    /* fixed 1998/11/24 */
    for(i=0;i<n;i++) {
	if(streq(var_name,name_ptr[i][0]) && streq(name, name_ptr[i][1])) {
	    return;
	}
    }

/*    fprintf(stderr,"ADD corner %s for %s\n",name,var_name);
*/
    
    name_ptr[n][0] = var_name;
    name_ptr[n][1] = name;
    n++;

    return(n);
}

