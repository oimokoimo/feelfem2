/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_comp.h
 *      Date:   1993/06/21 
 *   
 *   
 *   Purpose:   solve文data structure 定義ファイル
 *              
 *              
 ********************************************************************
 *  構造体のtree図
 * ----------------
 *   Solve                   solve文構造体(feel言語を反映)
 *    |          
 *    |-> **SolveElement       SolveElement構造体
 *    | (solve_element_dat)
 *    |    |
 *    |    |->**Equation
 *    |    | (eq_data)
 *    |    |
 *    |    |->ElemDat 【今はまだなし】
 *    |    |
 *    |    |->*ElementFORT77 
 *    |    |  (elem77_dat) 
 *    |    |     |-> *ElemDat      上と同じもの
 *    |    |     |   (elem_dat)
 *    |          
 *    |-> *SolveFORT77
 *    |   (solve77_ptr)
 *    |    |->**ElementFORT77      SolveElementとまったく同じポインタの
 *    |    |  (element77_ptr)      配列(make_solve_ctrl77内で使用の為)
 *    |          
 *    |-> **DirichletData
 *    |   (d_dat)
 *    |          
 *    |-> **NeumannData
 *    |   (n_dat)
 */

#include "../feel_def/feel_def.h"
#include "../element/element.h"


/*--------------------------------------*/
/* 節点要素データ集合に関する情報構造体 */
/*   要素節点データを作成時に使用       */
/*--------------------------------------*/

/* 【注意】 メッシュ生成側の制約より、domainは一つ */

typedef struct _ElemDat {

    int edatno;         /* 節点要素集合データ番号 */
                        /* これは節点パターン番号 */
                        /* この番号が同じものは同じ節点パターンを持つ */

    int sub_edatno;     /* 部分節点要素集合データ番号
			   このデータは、実行時に作成される */
    int sub_mats;       /* 部分領域数    (matnoの数)     */
    int *sub_matnos;    /* 部分領域番号数(matnoのデータ) */

    char *domain_name;  /* domain名 */

    int etype   ;       /* 基本要素形状 */
    
    int nodes;          /* 節点数 */

    Node **node_ptrptr; /* 節点座標への配列 */

} ElemDat;


/*-----------------------
  構造体 FEMvarinfo
  各要素毎に対応するfem変数の局所節点番号などを
  いれる

  節点なし自由度はペンディング  dbg:
  -----------------------*/
typedef struct {
    char *fem_var_name;   /* shape関数に対しては、SHAPE_FUNCTION_SYMBOL 
			     名で登録している                           */ 
    char *element_name;
    int   freedom;
    int  *ienp;           /* n 番目の自由度と、局所節点番号との対応  */
    int  *iedp;           /* 局所節点での自由度の加算分              */

    /* dbg: エルミート要素については注意が必要、現在深く考慮したわけではない */
    /* つまりFEMvarinfo構造体自体は、基底関数のbasis順に自由度位置を割り当て
	     ているわけだが、全体の解のベクトルから、fem変数への値の展開時に
  	     は微分値と節点値とでは違うfem変数としてわりあてる。その際に
	     注意が必要    

	     ただし、ecalルーチン内での受け方は'変数名_通し番号’で受ける
	     しかし、esetルーチンからの呼び出しでは、微分値の自由度はその
	     fem変数をとばさないといけない */

    /* たとえば、要素 Q1 に対して、
       Q1_1  一番目の基底関数   *(ienp + 0) 対応要素節点番号  *(iedp+0) dest
       Q1_2  ........................................
       */
    
} FEMvarinfo;

/*-----------------------
 *  構造体 ElementFORT77
 *
 *  FORTRANプログラムを生成する為に作る情報構造体
 *      各要素単位にmake_????????   で作成
 *
 */



typedef struct _ElementFORT77 {
    int  solve_no;      /* 親のsolve番号を持つ */
    int  element_no;    /* 要素番号     (SolveElementよりコピーする) */

    int  edat_no;       /* 要素節点集合データ番号                    */

    int  subdomain_flag;/* subdomainを使ったかどうか？ */
    int  sub_edat_no;   /* subdomainのedat番号集合     */

    int  nodes;         /* 要素内節点数                              */
    int *node_freedom;  /* 各節点自由度                              */

    /*=【注意】以下、現在make_elem_lisp内で設定している==============*/
    int  quad_methods;  /* 積分法の数 (make_elem_lisp() 内で設定)    */
    int *quad_type;     /* 積分法の種別(make_elem_lisp() 内で領域確保
			                               および設定    */
    char **quad_name;   /* 積分法の名称(make_elem_lisp() 内で領域確保
			                               および設定    */
    int  *quad_points;  /* 各数値積分法の積分点数                    */
    int  elem_freedom;  /* 要素内総自由度(make_elem_lisp() 内設定    */
    /*===============================================================*/
    
    /*---------------------------------------------------------------*/

    /*=【注意】以下、現在、make_elem_commonsで設定===================*/
    int *quad_terms;    /* COMMONブロックに宣言必要な配列変数の数    */
    char ***quad_term_var_aptr;  /* 配列名への配列                   */
    char ***quad_term_expr_aptr; /* LISPが出力した定義式への配列     */
    int  **quad_term_type_aptr;  /* LISPが出力した定義式のタイプ     */
    int *quad_consts;   /* COMMONブロックに宣言する定数変数の数      */
    char ***quad_const_var_aptr; /* 変数名への配列                   */
    int  *x_flag,*y_flag,*z_flag;/* 空間変数が含まれているかのフラグ */
    /*===============================================================*/

    int  nodeless_freedom; /* 節点無し自由度   */

    /* 以下各要素の節点数と */
    int  fem_vars;                        /* fem変数の数              */
    FEMvarinfo **fem_var_info_ptrptr;     /* 特定要素のfem変数情報    */
    
    FEMvarinfo *shape_var_info_ptr;       /* 形状関数のためのvarinfo  */
    /* CAUTION: dbg: 現在このメンバは未使用。将来形状関数の中間節点が
       補間関数の節点では無い場合(たとえばsuper parametric要素の場合
       おこりうる)は必要となる         */
    
    ElemDat *elem_dat;  /* 要素節点データ構造体へのポインタ */
     
} ElementFORT77;


/*-----------------------
 *  構造体 SolveFORT77
 *
 *  FORTRANプログラムを生成する為に作る情報構造体
 *     solveブロック
 */
typedef struct _SolveFORT77 {
    int solve_no;       /* solve文通し番号 */

    int elemg;          /* 要素グループ数 */
    int max_nodes;      /* 最大要素内節点数(FORTRANの配列の大きさ確定の為) */

    int linear_method;  /* 連立一次方程式解法 */
    
    int    fem_vars;        /* fem変数 */
    char **fem_var_name;    /* fem変数の名称 */

    int    ewise_vars;
    char **ewise_var_name;

    int    scalar_vars;
    char **scalar_var_name;

    /* 【注意】
       ElementFORT77 は、各SolveElement内で作成、定義したものを、
       make_solve_ctrl77()にて使い易いように以下の部分にコピーする。
     */
    
    ElementFORT77 **elem77_ptrptr;  /* 要素構成情報へのポインタ */
                                    /* 要素グループ数だけある   */

} SolveFORT77;

    

/*-----------------------
 * 構造体 Equation 
 *        
 *        方程式を記録する構造体
 *
 */
typedef struct Equation_ {

    int type;    /* EQ(偏微分方程式),WEQ(弱形式),FUNC(汎関数停留値問題) */

    int equation_terms;   /* 方程式の項数 */
    int boundary_terms;   /* 境界項の項数 */

    Expression **eq_term;  /* 方程式本体                             */  
    Expression **bd_term;  /* 境界項                                 */

    /*【注意】 解析的積分法は、??_method が NULLとなる */
    char **eq_method;     /* 方程式の各項に対する数値積分法 */
    char **bd_method;     /* 境界項の各項に対する数値積分法 */

    char *test_function;  /* 試験関数 */
    
    int yylineno;         /* feelソース上の位置 */

} Equation;



/*-----------------------
 *  構造体 SolveElement この構造体が有限要素法の基本構成の問題を定義する
 *
 *  Solve --
 *         |- デフォルトの数値積分法、計算領域、連立一次方程式解法
 *         |- SolveElement 1
 *         |- SolveElement 2
 *         |- SolveElement 3
 *         |-    ......
 *         |
 *         |- ディリク
 *         |- ノイマン条件
 *
 *
 *
 */
typedef struct SolveElement_ {  

    int type;        /* EQ(偏微分方程式),WEQ(弱形式),FUNC(汎関数停留値問題) */

    int nonlinear_flag; /* 非線形問題か否かのフラグ */

    char *domain_name;       /* 領域名   */
    char *subdomain_name;    /* sub領域名*/

    int   solve_no;     /* solve文番号 (solve_dat_make.cで定義)*/
    int   element_no;   /* 要素番号    (solve_dat_make.cで定義)*/

    int etype;          /* 要素基本形状  check_var_vs_domainで代入 */

    int quad_type;      /* 数値積分時に要素毎再計算が必要か？フラグ */
    int element_types;  /* SolveElementで使われている要素種数       */
    Element **elem_ptrptr; /* 使用するelementへの構造体リストへのポインタ */

    char *shape_func;   /* 形状変換関数   */
    
    int unknowns;      /* 未知変数の数(いまのところは親のSolveの内容と同一 */

    int fem_knowns;    /* 既知変数の数(いまのところは親のSolveの内容と同一 */
    int ewise_knowns;  /* 既知変数の数(いまのところは親のSolveの内容と同一 */
    int scalar_knowns; /* 既知変数の数(いまのところは親のSolveの内容と同一 */

    char **unknown_name;      /* 未知変数の名前(この順番で扱う) */
    char **fem_known_name;    /* 既知fem変数の名前 */
    char **ewise_known_name;  /* 既知ewise変数の名前 */
    char **scalar_known_name; /* 既知scalar変数の名前 */

    /* 境界積分項に関する情報 */
    int bd_fem_knowns;   /* 既知変数の数(いまのところは親のSolveの内容と同一 */
    int bd_ewise_knowns; /* 既知変数の数(いまのところは親のSolveの内容と同一 */
    int bd_scalar_knowns;/* 既知変数の数(いまのところは親のSolveの内容と同一 */

    char **bd_unknown_name;      /* 未知変数の名前(この順番で扱う) */
    char **bd_fem_known_name;    /* 既知fem変数の名前 */
    char **bd_ewise_known_name;  /* 既知ewise変数の名前 */
    char **bd_scalar_known_name; /* 既知scalar変数の名前 */

    ElementFORT77 *elem77_dat;   /* fortranプログラム生成の為の
				    情報構造体                   */

    int equations;        /* 連立方程式の本数             */
    Equation  **eq_data;  /* 方程式のデータへのポインタ   */

    /*【注意】 次のメンバは、solve_chk_varで設定する     */
    int    nbc_args;       /* ノイマン条件用仮変数の数   */
    char **nbc_arg_name;   /* ノイマン条件用仮変数の名前 */

    /* ノイマン条件設定式(nbc: の右辺)にのみ現れる既知fem変数の登録 */
    /* solve_chk_only_neumann.c にて設定 */
    int    ndata_fem_knowns;
    char **ndata_fem_name;


    int yylineno;

} SolveElement;


/* ファイルによるディリクレ条件の設定はpending! */

typedef struct DirichletData_        /* ディリクレ条件データ構造体 */
{
    char *var;          /* 境界条件を設定する変数名 */
    Expression *expr;   /* 境界条件式 */

    int   numset;       /* 境界条件に指定する、数値データ集合番号 */
    
    int   boundaries;   /* この境界条件を設定する境界のグループ数 */
    char **b_name;      /* 境界の名前                             */

    int   b_nodeset;    /* 境界条件設定の節点集合データ番号       
			 * 複数の境界辺が指定されていても 
			 * make_boundary_dataでまとめる
			 * (boundariesに対応して(int *)でないわけ)
			 * solve_comp/set_boundary_no.c 内で領域確保および設定
			 */

    int    fem_vars;     /* fem変数の個数 */
    char **fem_var_name; /* fem変数の名前 */
    
    int    scalar_vars;     /* scalar変数の個数 */
    char **scalar_var_name; /* scalar変数の名前 */
    
    int yylineno;
    
} DirichletData;


/*==================================================*/
/* Neumann境界にかかわる基底関数を格納するstructure */
/*==================================================*/
typedef struct {
    char *element_name;   /* 基底関数名                           */
    int   basis;          /* 境界に節点を持つ基底関数の個数       */
    int  *basis_no;       /* その位置(これは、0,1,2で０から始める 
			   * これは、基底関数番号(要素内節点番号とも
			   * 異なることに注意                        */
    
    /*====================================*/
    /* 以下は、make_ncond_skyline内で作る */
    /*====================================*/

    int  *ienp;           /* 対応する境界要素内局所節点番号 */
    int  *iedp;           /* その点における方程式番号への＋α分(未知変数のみ)*/

} EdgeBasis;



/*====================*/
/* ノイマン条件構造体 */
/*====================*/

typedef struct NeumannData_          /* ノイマン条件データ構造体 */
{
    int   args;               /* ノイマン条件に指定される定義式の数 */

    char **left_var;          /* 境界条件式  左辺  変数名 */
    Expression **expr_right;  /* 境界条件式  右辺         */
    
    int    boundaries;   /* この境界条件を設定する境界のグループ数 */
    char **b_name;       /* 境界の名前                             */

    int    belem_flag;  /* 境界辺要素か、接境界要素か             */
    int    belem_no;    /* 境界要素番号 データ形式は ElemDat 
			   内部の要素節点データ集合と同じforamtで格納 */

    int    boundary_points; /* 境界節点数 */
    /*------------------------------------*/
    /* 境界構造体 make_ncond_lisp内で設定 */
    /*------------------------------------*/
    EdgeBasis  **unknown_basis;   /* 対応するSolveElementの未知変数に対する
				   * 基底関数に対応する                     */

    EdgeBasis  **fem_known_basis; /* 既知fem変数  */
    EdgeBasis   *shape_basis;     /* 形状変換関数 */

    /*-------------------------------------------*/
    /* check系ルーチンで代入する                 */
    /* 境界名の検査はchk_boundaryで              */
    /* ノイマン仮変数はchk_boundary_varで        */
    /* 下の代入は      chk_NeumannDataでやります */
    /*-------------------------------------------*/
    int    gauss_points; /* Gauss数値積分点の数 */

    int    unknown_vars; /* 未知fem変数の個数 */
    char **unknown_name; /* 未知fem変数の名前 */

    int    fem_vars;     /* 既知fem変数の個数 */
    char **fem_var_name; /* 既知fem変数の名前 */

    int    scalar_vars;     /* scalar変数の個数 */
    char **scalar_var_name; /* scalar変数の名前 */

    int yylineno;
    
} NeumannData;


/*-----------------------------------
 *             Solve構造体
 *-----------------------------------*/

typedef struct Solve_ {

    int solve_no;             /* solve番号           */

    int solve_eigen_flag;     /* 固有値問題かどうかのフラグ */

    int linear_method;        /* 一次方程式解法番号  */
    int symmetry_flag;        /* 対称行列フラグ      */
    int nonlinear_flag;       /* 非線形方程式フラグ  */

    int boundary_gauss_points;/* 境界積分項におけるガウス積分点数 */

    int initial_settings;     /* 初期値設定の数      */
    char  **initial_name;     /* 初期値設定の名前    */
    int    *initial_yylineno; /* 初期値設定の行番号  */
    Expression **initial_expr;/* 初期値              */

    char   *eps_setting;      /* 非線形収束判定条件 */

    Expression *newton_factor;/* 緩和係数            */
    int      yy_newton_factor;/* ソース行での位置    */

    Expression *newton_times;/* Newton-times expression */
    int      yy_newton_times;/* Newton-times line     */


    int solve_elements;             /* 要素グループの数 */
    SolveElement  **solve_elem_dat; /* 各要素データ */

    /* 以下の変数名に関するデータは、SolveFORT77にコピーされ、
       FORTRANプログラム生成時の引き数生成に使われる          
       これらの変数名には境界項にのみ含まれる諸変数も
       入っていることに注意すること                           */
    int unknowns;             /* 未知変数の数           */
    int fem_knowns;           /* 既知fem変数の数        */
    int ewise_knowns;         /* 既知ewise変数の数      */
    int scalar_knowns;        /* スカラー変数の数(既知) */

    char **unknown_name;      /* 未知変数の名称         */
    char **fem_known_name;    /* 既知fem変数の名前      */
    char **ewise_known_name;  /* 既知ewise変数の名前    */
    char **scalar_known_name; /* スカラー変数の名前     */

    int d_conditions;         /* ディリクレ条件式の数   */
    DirichletData **d_dat;

    int n_conditions;         /* ノイマン条件式の数     */
    NeumannData   **n_dat;

    SolveFORT77   *solve77_ptr; /* プログラム生成の為の情報構造体 */


    int yylineno;

} Solve;


extern Solve *get_nth_solve_ptr();   /* solveへの構造体を返す */
extern SolveFORT77 *get_nth_solvefort77_ptr(); /* solve_fort77への構造体 */
extern ElemDat *make_element_node_dat(); /* 要素のElemDat情報を返す */
extern ElemDat *get_nth_mesh_edat_ptr(); /* メッシュ生成の為のElemDatポインタを
					    返す */
extern FEMvarinfo *get_femvarinfo();     /* 変数名からFEMvarinfo構造体を返す */
extern FEMvarinfo *get_femvarinfo_ptr_by_name();   /* solve_fort77内 */

extern ElemDat *get_nth_domain_elem_dat_ptr(); /* make_mesh_ctrl_data.c内
						  境界情報の為のセーブ    */

extern EdgeBasis *make_edge_basis();   /* solve_fort77内の関数 */
