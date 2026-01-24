/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_mesh_ctrl_data.c
 *      Date:   1993/08/12
 *    Remake:   1993/09/01
 *  Modified:   1993/12/03
 *   
 *   Purpose:   メッシュに関するデータの作成
 *              
 *                各domain毎に、節点のorデータを作成する。
 * 
 *              【注意】現在、domainは一つだけ
 * 
 *                element_nodeプログラムを活用する。
 *              
 *              【注意】
 *                現在、各domainに対して基本要素形状の異なるメッシュ生成
 *                は対応していない。この点に注意を要する。
 *                
 *                domainはregionの集合体
 *                各regionには重なりが無いものとする
 *                
 *                今は、全部のORをとろう！(各節点パターンの)
 *              
 *              【注意】
 *                このプログラム中で作成した各domain毎の節点情報ポインタ
 *                ElemDat 構造体をガメッておく(境界データ作成の為)
 *               
 *              
 *              
 *              
 *              
 *              
 *              【注意】
 *                このプログラムから、境界条件データ作成プログラムを
 *                呼び出す。  ←  ほんまかいな…(笑)
 *              
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "solve_comp.h"

#include "solve_comp_funcs.h"

static ElemDat *domain_elem_dat[MAX_DOMAINS];
static int      save_domains = 0;

extern int      feel_dim;

void mesh_exec_1D(ElemDat *mesh_elem_dat_ptr);
void mesh_book_exec(ElemDat *mesh_elem_dat_ptr);
void mesh_bamg_exec(ElemDat *mesh_elem_dat_ptr);

void make_mesh_ctrl_data()
{
    /* 暫定版  基本要素形状はただ一つのみ
               全節点のORをとる
     */

    int i,j,k,l,m,n;
    
    Solve             *solve_ptr;
    SolveElement      *solve_element_ptr;
    ElementFORT77     *elem77_ptr;
    ElemDat           *elem_dat_ptr;
    Node              *node_ptr;

    Domain *domain_ptr;

    int domains;      /* domainが節点パターン作成
			 (メッシュ作成の基本要素になる)  

			 region → matnoの対象、regionは重なりを許さない

			 domain → regionの集合、
			   重なりを許す → region がメッシュ生成の基本単位
			   許さない     → domain がメッシュ生成の基本単位

			   【LOOK！】
			   現在は後者の許さないバージョンを作成する
			   regionは単にmatnoを指定する為の領域となる。
			 */
    char *domain_name;
    

    int etype;
    int solves;
    int solve_elements;
    int nodes;

    Frac r,s,t;

    ElemDat *mesh_elem_dat_ptr;


    domains = how_many_domains();
    if(domains != 1) {
	SystemAbort("RESTRICTION: 今domainはひとつだけ！\n");
    }

    solves = how_many_solves();


    /* dbg: 本ちゃんでは、各domain毎に節点パターンを作成する */


    for(i=0;i<domains;i++) {  /* このループは将来の使用の為 */

	domain_ptr  = get_nth_domain_ptr( i );
	
	domain_name = domain_ptr -> name;

	etype = domain_ptr -> etype;

	/* DBGWRT("CHECK: メッシュCTRL   %s  etype=%d\n",domain_name,etype); */

	/* メッシュ生成用データ作成初期化処理 */
	store_element_node_init( domain_name, etype);

	for(j=0;j<solves;j++) {

	    solve_ptr = get_nth_solve_ptr( j );

	    solve_elements = solve_ptr ->solve_elements;


	    for(k=0;k<solve_elements;k++) {



		solve_element_ptr = *(solve_ptr->solve_elem_dat + k);
		
		if(!streq(domain_name,solve_element_ptr->domain_name)) {
		    SystemError("RESTRICTION: domainは一つだけ");
		    continue;
		}
	    
		elem77_ptr = solve_element_ptr->elem77_dat;
		
		if(elem77_ptr == NULL) {
		    DBGWRT("おっといけねぇ、elem77_ptrがNULLだよ〜ん.\n");
		}

		elem_dat_ptr = elem77_ptr -> elem_dat;

		nodes = elem_dat_ptr -> nodes;

		for(m=0;m<nodes;m++) {


		    node_ptr = *(elem_dat_ptr -> node_ptrptr+m);

		    r = node_ptr->r;
		    s = node_ptr->s;
		    t = node_ptr->t;

		    /* メッシュ生成時専用の element_node 保存関数を呼び出す */
		    store_element_node_for_mesh(r,s,t,"mesh",0);

		}
	    }
	}
	mesh_elem_dat_ptr = make_element_node_dat();


	/* 境界条件向け節点データ作成の為、
         * mesh_elem_dat_ptr はセーブしておく
	 */

	domain_elem_dat[save_domains] = mesh_elem_dat_ptr;
	save_domains++;

	
/*	printf("make_mesh_ctrl_data.c  end.===================\n");
	
	dbg_show_elem_dat(mesh_elem_dat_ptr);
*/
	
    }

    switch(feel_dim) {
      case 1:
	mesh_exec_1D(mesh_elem_dat_ptr);
	break;

      case 2:
        if(bamg_mode == 0) {
          mesh_book_exec(mesh_elem_dat_ptr);  
        }
        else {
          mesh_bamg_exec(mesh_elem_dat_ptr);
        }
	break;
   
      default:
	SystemAbort("Mesh executable dimension is 1D and 2D only\n");
	break;
    }


    return;
}


ElemDat *get_nth_domain_elem_dat_ptr( n )
     int n;
{
    if(n < 0 || n > save_domains) {
	SystemAbort("そんなdomain番号は無い(get_nth_domain_elem_dat_ptr)");
    }

    return( domain_elem_dat[n]);
}


