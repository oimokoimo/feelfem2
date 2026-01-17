/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1993/07/14
 *   
 *   Purpose:   節点を合成する,節点毎の自由度,未知変数のリストも作成
 *   Functions: store_element_node_init(name,etype) 要素形状の入力と初期化
 *              store_element_node(r,s,t,変数名,変数type,自由度の有無)
 *              make_element_node_dat() データ作成実行
 *              
 *              store_element_node()の改造
 *                自由度が無い節点についても記録する
 *                これは、既知fem変数の節点番号を得る為  改造93/11/01
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../element/element.h"    /* eval_関数のdouble宣言読み込みの為 */

#include "solve_comp.h"


static int  nodes;
static Frac r[MAX_NODES_PER_ELEMENT];
static Frac s[MAX_NODES_PER_ELEMENT];
static Frac t[MAX_NODES_PER_ELEMENT];

static double val[MAX_NODES_PER_ELEMENT];   /* 節点準位重み値 */

static int   freedom[MAX_NODES_PER_ELEMENT];
static char *var_name[MAX_NODES_PER_ELEMENT][MAX_EQUATIONS];
static int   node_type[MAX_NODES_PER_ELEMENT][MAX_EQUATIONS];
static int   order[MAX_NODES_PER_ELEMENT];

static int   basic_shape_type;
static char *domain_name;

store_element_node_init( name,etype )
     char *name;  /* 領域名 */
     int etype;
{
    int i;

    /* 自由度初期化 */
    for(i=0;i<MAX_NODES_PER_ELEMENT;i++) {
	freedom[i] = 0;   
    }

    switch(etype) {
      case TRI:
      case RECT:
      case LINE:
	break;

      default:
	SystemAbort("未対応の要素形状が指定されました.(store_element)\n");
    }

    domain_name      = name;
    basic_shape_type = etype;
    nodes = 0;

    return;
}

store_element_node(ra,sa,ta,name,type,free_flag)
     Frac ra,sa,ta;    /* 節点座標値 */
     char *name;       /* 未知変数名 */
     int   type;       /* 未知変数種 */
     int   free_flag;  /* 自由度フラグ YES:自由度あり NO:自由度なし(既知変数)*/
     /* 既知変数の節点も登録するように改造 */
{
    int i;
    double now_val;
    int    deg;


/*
    STRESS;
    printf("store_element_nodeにやって来ました\n");
    printf("変数名 %s   free_flag[%d] ",name,free_flag);
    prt_frac_image_2d(ra,sa); printf("\n");
    NORMAL;
*/
    

    if(nodes == MAX_NODES_PER_ELEMENT) {
	SystemAbort("異常終了001(store_element_node)\n");
    }

    /* 節点順位評価値の計算 */


    switch( basic_shape_type ) {
      case TRI:
	now_val = (double)tri_eval_frac(ra,sa);
	break;

      case RECT:
	now_val = (double)rect_eval_frac(ra,sa);
	break;

      case LINE:
	now_val = (double)line_eval_frac(ra);
	break;

      default:
	SystemAbort("指定された要素タイプは不可(store_element_node)\n");
    }

    /* 同一節点の発見 */
    for(i=0;i<nodes;i++) {
	if(now_val == val[i]) {
	    if(free_flag == NO) {  /* 自由度が無い場合は何もしない */
		/* DBGWRT("now_val = %f  i=%d\n",now_val,i); */
		return;
	    }

	    deg = freedom[i];
	    freedom[i] = deg + 1;
	    var_name[i][deg] = name;
	    node_type[i][deg] = type; /* DN,DX,などエルミート要素 */
	    return;
	}
    }
    
    r[nodes].bunsi = ra.bunsi;
    s[nodes].bunsi = sa.bunsi;
    t[nodes].bunsi = ta.bunsi;

    r[nodes].bunbo = ra.bunbo;
    s[nodes].bunbo = sa.bunbo;
    t[nodes].bunbo = ta.bunbo;

    if(free_flag == YES) {              /* 自由度が設定されている節点に
					   対しては、その自由度内容を記録 */
	var_name[nodes][0] =  name;
	node_type[nodes][0] = type;  
	freedom[nodes] =         1;
    }

    val[nodes] =       now_val;

    nodes++;

/*    DBGWRT("nodes++ -> %d  now_val = %f\n",nodes,now_val); */

    return;
}


/* メッシュ生成時に、必要な節点パターンを計算する為に
   用いる関数                                          */

void store_element_node_for_mesh(ra,sa,ta,name,type)
     Frac ra,sa,ta;  /* 節点座標値 */
     char *name;     /* 未知変数名 */
     int   type;     /* 未知変数種 */
{
    int i;
    double now_val;
    int    deg;


    if(nodes == MAX_NODES_PER_ELEMENT) {
	SystemAbort("何か変だよぉ〜ん(store_element_node)\n");
    }

    /* 節点順位評価値の計算 */

    switch( basic_shape_type ) {
      case TRI:
	now_val = (double)tri_eval_frac(ra,sa);
	break;

      case RECT:
	now_val = (double)rect_eval_frac(ra,sa);
	break;

      case LINE:
	now_val = (double)line_eval_frac(ra);
	break;


      default:
	SystemAbort("指定された要素タイプは不可(store_element_node)\n");
    }
    
    /* 同一節点の発見 */
    for(i=0;i<nodes;i++) {
	if(now_val == val[i]) {
	    return;              /* 同じ節点の時は何もしなくてもよい */
	}
    }
    
    r[nodes].bunsi = ra.bunsi;
    s[nodes].bunsi = sa.bunsi;
    t[nodes].bunsi = ta.bunsi;

    r[nodes].bunbo = ra.bunbo;
    s[nodes].bunbo = sa.bunbo;
    t[nodes].bunbo = ta.bunbo;

    var_name[nodes][0] =  name;
    node_type[nodes][0] = type;  
    val[nodes] =       now_val;
    freedom[nodes] =         1;


    nodes++;
    return;
}


ElemDat *make_element_node_dat()
{
    int i,j;

    /* ElemDat構造体を作成する為に使用 */
    ElemDat *elem_dat_ptr;
    Node **node_ptr_ptr,*node_ptr;
    char **var_name_ptr;
    int  *node_type_ptr;

    Frac f_swap;
    int i_swap;
    char *cp_swap;

    for(i=0;i<nodes;i++) {

/*	DBGWRT("%d  val=%lf\n",i,val[i]);  */

	if(val[i] == 0.0) DBGWRT("節点座標評価値が0？(make_element_node_dat)\n");
	order[i] = i;
    }

    /* val[*] を利用して順序付け */
    for(i=0;i<nodes;i++) {
	for(j=i+1;j<nodes;j++) {

	    if(val[order[i]]<val[order[j]]) {
		i_swap = order[i];
		order[i] = order[j];
		order[j] = i_swap;
	    }
	    else if( val[order[i]] == val[order[j]]) {
		SystemAbort("どっひゃ〜んohmygod99\n");
	    }
	}
    }
    
    /* ElemDat構造体の作成 */ 
      
    elem_dat_ptr = (ElemDat *)FEEL_GetMemory(sizeof(ElemDat));

    elem_dat_ptr -> edatno = 0;
    elem_dat_ptr -> nodes  = nodes;

    elem_dat_ptr -> domain_name = domain_name;
    elem_dat_ptr -> etype = basic_shape_type;

    node_ptr_ptr =  (Node **)FEEL_GetMemory(sizeof(Node *) * nodes);
    elem_dat_ptr -> node_ptrptr = node_ptr_ptr;

    for(i=0;i<nodes;i++) {


	node_ptr = (Node *)FEEL_GetMemory(sizeof(Node));
	var_name_ptr=(char **)FEEL_GetMemory(sizeof(char *)*freedom[order[i]]);
	node_type_ptr = (int *)FEEL_GetMemory(sizeof(int)*freedom[order[i]]);

	*(node_ptr_ptr+i) = node_ptr;

	node_ptr->freedom = freedom[order[i]];
	node_ptr->var_name_ptr = var_name_ptr;
	node_ptr->node_type = node_type_ptr;

	/* Node構造体の局所節点座標の代入 */
	node_ptr->r.bunsi = r[order[i]].bunsi;
	node_ptr->s.bunsi = s[order[i]].bunsi;
	node_ptr->t.bunsi = t[order[i]].bunsi;

	node_ptr->r.bunbo = r[order[i]].bunbo;
	node_ptr->s.bunbo = s[order[i]].bunbo;
	node_ptr->t.bunbo = t[order[i]].bunbo;


	for(j=0;j<freedom[order[i]];j++) {
	    *(var_name_ptr  + j) = var_name[order[i]][j];
	    *(node_type_ptr + j) = node_type[order[i]][j];
	}
    }



    return(elem_dat_ptr);
}
