/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   elem_dat_make.c
 *      Date:   1993/07/15
 *   
 *   Purpose:   ElementFORT77作成の為のデータを作る
 *              
 *              ○ElemDat構造体を作成し、要素節点集合データテーブルへ
 *                登録する。(関数store_edat(ElemDat*)、この関数はedat番号
 *                           を返すので記録する)
 *              
 *                節点の登録は未知fem変数  及び
 *                            既知fem変数  に対して行う(93/11/1 付加機能)
 *                ※副作用に注意！
 *              
 *              
 *              この関数は、solve_dat_make()から、各ElementSolve毎に
 *              呼び出される。
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "solve_comp.h"
#include "../var_comp/var_comp.h"
#include "../element/element.h"

#include "solve_comp_funcs.h"

void elem_dat_make_main(solve_ptr,solve_element_ptr, elem77_ptr)
     Solve         *solve_ptr;
     SolveElement  *solve_element_ptr;
     ElementFORT77 *elem77_ptr;
{
    int i,j;

    int unknowns;
    char **unknown_name;
    int knowns;
    char **known_name;

    char *name;

    ElemDat  *elem_dat_ptr;
    Element  *element_ptr;
    FEM_type *fem_type_ptr;

    int basis;
    int nodes;

    Node *node_ptr;

    Frac r,s,t;
    
    int ntype;   /* 節点値の意味 */

    int edat_no; /* 要素節点集合データ番号 */

    elem77_ptr -> solve_no = solve_ptr->solve_no; /* solve番号設定 */
    
    /* メッシュ分布データの作成 -> elem_dat に情報構造体を代入 */
    
    store_element_node_init( solve_element_ptr -> domain_name ,
  			    solve_element_ptr -> etype);
    
    unknowns     = solve_element_ptr->unknowns;
    unknown_name = solve_element_ptr->unknown_name;
    knowns       = solve_element_ptr->fem_knowns;
    known_name   = solve_element_ptr->fem_known_name;
    

    /* 未知変数をElemDat用のスタックに積む */

    for(i=0;i<unknowns;i++) {

	name = *(unknown_name + i);
	/* 次に用いた関数はget_element_ptr_NDとだぶっている見たいやねぇ〜 */
	fem_type_ptr = 
	  get_fem_type_ptr_by_2name(name,solve_element_ptr->domain_name);

	if(fem_type_ptr == NULL) {
	    SystemAbort_s("対応するfem変数%sのFEM_type構造体を獲得できません\n" , name);
	}

	element_ptr = get_element_ptr_by_name(fem_type_ptr->type);

	if(element_ptr == NULL) {
	    SystemAbort_s("対応するfem変数%sのElement構造体を獲得できません\n" , name);
	}

	basis = element_ptr->basis; /* element_ptr->nodesは設定されていない */

	for(j=0;j<basis;j++) {
	    r.bunsi = element_ptr->r_frac[j].bunsi;
	    s.bunsi = element_ptr->s_frac[j].bunsi;
	    t.bunsi = element_ptr->t_frac[j].bunsi;
	    
	    r.bunbo = element_ptr->r_frac[j].bunbo;
	    s.bunbo = element_ptr->s_frac[j].bunbo;
	    t.bunbo = element_ptr->t_frac[j].bunbo;

	    ntype = element_ptr->ntype[j];
	    
	    /* 実際に節点情報をスタックへ積む */
	    store_element_node(r,s,t,name,ntype,YES); /* YES は自由度有の意 */
	}
    }

    /* 既知変数に関して節点座標をスタックへ積む */
    /* スタックへ積む際に、未知変数として積まないようにする */
    for(i=0;i<knowns;i++) {

	name = *(known_name + i);
	fem_type_ptr = 
	  get_fem_type_ptr_by_2name(name,solve_element_ptr->domain_name);

	if(fem_type_ptr == NULL) {
	    SystemAbort_s("対応するfem変数%sのFEM_type構造体を獲得できません\n" , name);
	}

	element_ptr = get_element_ptr_by_name(fem_type_ptr->type);

	if(element_ptr == NULL) {
	    SystemAbort_s("対応するfem変数%sのElement構造体を獲得できません\n" , name);
	}

	basis = element_ptr->basis; /* element_ptr->nodesは設定されていない */

	for(j=0;j<basis;j++) {
	    r.bunsi = element_ptr->r_frac[j].bunsi;
	    s.bunsi = element_ptr->s_frac[j].bunsi;
	    t.bunsi = element_ptr->t_frac[j].bunsi;
	    
	    r.bunbo = element_ptr->r_frac[j].bunbo;
	    s.bunbo = element_ptr->s_frac[j].bunbo;
	    t.bunbo = element_ptr->t_frac[j].bunbo;

	    ntype = element_ptr->ntype[j];
	    
	    /* 実際に節点情報をスタックへ積む */
	    store_element_node(r,s,t,name,ntype,NO); /* NO は自由度無しの意 */
	}

    }
    
    /*    形状関数に関する節点座標を積む
     *    既知FEM変数と同じ扱でよいと信じたい  dbg: dbg: CAUTION:
     */
    element_ptr = get_element_ptr_by_name(solve_element_ptr->shape_func);
    
    if(element_ptr == NULL) {
	SystemAbort_s("対応する形状変換関数%sのElement構造体を獲得できません\n" , name);
    }
    
    basis = element_ptr->basis; /* element_ptr->nodesは設定されていない */
    
    for(j=0;j<basis;j++) {
	r.bunsi = element_ptr->r_frac[j].bunsi;
	s.bunsi = element_ptr->s_frac[j].bunsi;
	t.bunsi = element_ptr->t_frac[j].bunsi;
	
	r.bunbo = element_ptr->r_frac[j].bunbo;
	s.bunbo = element_ptr->s_frac[j].bunbo;
	t.bunbo = element_ptr->t_frac[j].bunbo;
	
	ntype = element_ptr->ntype[j];
	
	/* 実際に節点情報をスタックへ積む */
	store_element_node(r,s,t,name,ntype,NO); /* NO は自由度無しの意 */
    }
    

    /* 本のメッシュ生成専用ルーチン */
    /* 要素節点情報の生成 */
    elem_dat_ptr = make_element_node_dat(); /* この構造体は各々のSolveElement
					       で別個に保持する           */
    edat_no = store_edat( elem_dat_ptr );

    elem_dat_ptr -> edatno = edat_no;    /* edat_no は節点パターンに対する
					    通し番号                      */

    /* domainに対して代表的なdomain-edatno番号を付加する */
    store_domain_edatno( solve_element_ptr -> domain_name , edat_no);

    elem77_ptr -> elem_dat = elem_dat_ptr;

    nodes = elem_dat_ptr -> nodes;

    /* elem77_ptr内、節点数の設定 */
    elem77_ptr -> nodes    = nodes;

    /* elem77_ptr内、節点毎自由度の設定 */
    elem77_ptr -> node_freedom = (int *)FEEL_GetMemory(sizeof(int) * nodes);
    for(i=0;i<nodes;i++) {
	node_ptr = *(elem_dat_ptr -> node_ptrptr + i);
	*(elem77_ptr -> node_freedom + i ) = node_ptr -> freedom;
    }

/*
    STRESS;
    printf("elem_dat_make.c での ElemDat検査 \n");
    NORMAL;
    dbg_show_elem_dat(elem_dat_ptr);
*/

    return;
}
