/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   quadrature.h
 *      Date:   1993/07/10
 *  Modified:   1993/08/19
 *   
 *   Purpose:   数値積分法情報定義構造体
 *              
 */

/*==========================*/
/* 積分点、重みへのポインタ */
/*==========================*/
typedef struct QuadWeight_ {   
    Expression *r;           /* r 節点座標 */
    Expression *s;           /* s 節点座標 */
    Expression *t;           /* t 節点座標 */

    Expression *weight;      /* 各積分点における重み */

} QuadWeight;


/*==================================*/
/* 各内挿値付き変数の内挿法の構造体 */
/*==================================*/
typedef struct QuadInterpolate_ { 
    
    char        *var_name;            /* 内挿変数名 */
    int          var_type;            /* FEM,EWISE,SCALAR */
    char        *elem_type;           /* FEM変数の場合の要素名 */

    int          nodes;
    int         *node_no;             /* 対応する積分点番号 */
    Expression **interpolate_expr;    /* 内挿方法の数式     */

} QuadInterpolate;


/*==================*/
/* 数値積分法構造体 */
/*==================*/
typedef struct Quadrature_ {

    char *name;          /* 数値積分法の名称     */
    int type;            /*                      */
    int etype;           /* 形状タイプ1:line 2:tri 3:rect 4:tetra 5:cube 6: */
    int dimension;       /* 次元 */

    int rvars;           /* 引き数の数 */
    char **rvar_name;    
    char **rvar_type;    /* fem変数の場合は基底関数名、scalarの場合は
			    NULLとなる                                */
    
    int nodes;           /* 総積分点数   */
    
    QuadWeight **quad_weight_ptrptr;  /* 重み関数へのポインタ */
    
    int consts;              /* 定数値 */
    char **const_var;        /* 定数名 */
    Expression **const_val;  /* 定数式 */

    int doubles;             /* 実数変数値 */
    char **double_var;       /* 実数変数名 */
    Expression **double_val; /* 実数初期値 これは、要素毎に再計算する
				NULLの場合は初期値が設定されていない場合 */
			      
    int          quad_lets;  /* 代入文の数       */
    char       **let_var;    /* 代入される変数名                        */
    int      *let_var_type;  /* 代入される変数名のタイプ parse時に設定  */
    Expression **let_val;    /* 代入文右辺       */


    int interpolates;                         /* 内挿法が指定されているもの */
    QuadInterpolate **quad_interpolate_ptr;   /* 内挿方法構造体への配列 */

    /* dbg: CAUTION:  quad_interpolates は未設定(93/11/19発見) */

    int  yylineno;        /* feelソース中のこの文の開始位置 */
    
} Quadrature;



/*====================
  関数プロトタイプ宣言
  ==================== */
extern Quadrature *get_nth_quad_ptr();       /* quadrature.c */
extern int         how_many_quads();         /* quadrature.c */

extern Quadrature *get_quadrature_ptr_by_name(); /* 個別ファイル */
