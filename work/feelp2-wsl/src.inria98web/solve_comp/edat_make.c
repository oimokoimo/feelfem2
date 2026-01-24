/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   edat_make.c
 *      Date:   1993/07/13
 *   
 *   Purpose:   要素節点集合データの作成(solve文用)
 *   Functions: is_equal_edat( ElemDat * , ElemDat *) ElemDatの同一性判定
 *
 *              push_edat( ElemDat *) ElemDatデータの格納(内部関数)
 *                   【重要】         および此処で要素節点データ番号付加
 *
 *              int store_edat( ElemDat *)ElemDatをストアし対応する要素節点
 *                                        データ番号を返す。既に同じ要素節点
 *                                        データが存在する場合は、その要素
 *                                        節点番号を返す、なお、記憶場所は
 *                                        新たに割り付けないので注意。
 *                                        要するに、代表の要素のElemDatが
 *                                        要素節点データの情報として割り付け
 *                                        られる。
 *
 *              make_or_edat_data()       
 *
 *
 *
 *              int how_many_mesh_edat_data() メッシュ生成の要素節点データの
 *                                            数を返す
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "solve_comp.h"

int get_new_edatno();

static int edats = 0;               /* メッシュ生成の為の要素節点データ数 */

static ElemDat *edat[MAX_EDATSET];
static int edat_flag[MAX_EDATSET];  /* メッシュ生成データを作ったかどうかの
				       フラグ                               */

static ElemDat *domain_edat[MAX_DOMAIN]; /* 領域メッシュ生成の為の構造体 */
static int domain_edats = 0;


int how_many_mesh_edat_data()
{                                   /* メッシュ生成が必要なデータ数 */
    return(edats);
}

ElemDat *get_nth_mesh_edat_ptr( n )     /* メッシュ生成の為のElemDatポインタを
					   返す             
					 */
     int n;
{
    if(n < 0 || n >= edats) {
	SystemAbort("INNER ERROR: get_nth_mesh_edat_ptr()");
    }
    
    return(edat[n]);
}



/* 与えられた二つのElemDatが同一かどうか調べる   */
/* 同一である定義は、節点パターンが同一かどうかということであり
   内部の未知変数の自由度が違ってもそれは見ない                 */
is_equal_edat( edat_ptr_a, edat_ptr_b )
     ElemDat *edat_ptr_a;
     ElemDat *edat_ptr_b;
{
    int i;

    int etype,nodes;

    Frac r,s,t;
    double val_a,val_b;
    Node *node_ptr;

    /* 要素形状が異なっている */
    if(edat_ptr_a -> etype != edat_ptr_b -> etype) {
	return(NO);
    }

    /* 節点数が異なっている */
    if(edat_ptr_a -> nodes != edat_ptr_b -> nodes) {
	return(NO);
    }

    /* 定義domainが異なっている */
    if(!streq(edat_ptr_a ->domain_name,edat_ptr_b->domain_name)) {
	return(NO);
    }

    etype = edat_ptr_a -> etype;
    nodes = edat_ptr_a -> nodes;

    for(i=0;i< nodes;i++) {

	node_ptr = *(edat_ptr_a -> node_ptrptr + i);
	
	r.bunsi = node_ptr->r.bunsi;
	r.bunbo = node_ptr->r.bunbo;

	s.bunsi = node_ptr->s.bunsi;
	s.bunbo = node_ptr->s.bunbo;

	t.bunsi = node_ptr->t.bunsi;
	t.bunbo = node_ptr->t.bunbo;

/* 	fprintf(stderr,"etype = %d  LINE = %d\n",etype,LINE); */

	switch( etype ) {
	  case TRI:
	    val_a = tri_eval_frac(r,s);
	    break;

	  case RECT:
	    val_a = rect_eval_frac(r,s);
	    break;

	  default:
	    SystemAbort("まだimplementされていないetypeが指定されました(is_equal_edat)\n");
	}


	node_ptr = *(edat_ptr_b -> node_ptrptr + i);
	
	r.bunsi = node_ptr->r.bunsi;
	r.bunbo = node_ptr->r.bunbo;

	s.bunsi = node_ptr->s.bunsi;
	s.bunbo = node_ptr->s.bunbo;

	t.bunsi = node_ptr->t.bunsi;
	t.bunbo = node_ptr->t.bunbo;

	switch( etype ) {
	  case TRI:
	    val_b = tri_eval_frac(r,s);
	    break;

	  case RECT:
	    val_b = rect_eval_frac(r,s);
	    break;

	  default:
	    SystemAbort("まだimplementされていないetypeが指定されました(is_equal_edat)\n");
	}

	if(val_a != val_b) return(NO);
    }

    return(YES);
}

/* 要素節点集合データを格納するルーチン */	    
/* およびここで要素節点集合データ番号を割り付ける */
/* また、要素節点データ番号も返す */
/* 【関数内の静的な関数】 */
static int push_edat( edat_ptr )
     ElemDat *edat_ptr;
{
    int edatno;

    if(edats == MAX_EDATSET) {
	SystemAbort("要素節点データ種数が多すぎます。\n");
    }

    edatno = get_new_edatno();
    edat[edats] = edat_ptr;
    edat[edats]-> edatno = edatno;

    edats++;

    return(edatno);
}


int store_edat( edat_ptr )
     ElemDat *edat_ptr;
{
    int i;
    int edatno;

    for(i=0;i<edats;i++) {
	if(is_equal_edat( edat_ptr, edat[i])) {
	    return( edat[i] -> edatno ) ;
	}
    }
    
    edatno = push_edat( edat_ptr );

    return(edatno);
}
