/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   element.h
 *      Date:   1993/05/25
 *  Modified:   1993/06/28
 *   
 *   Purpose:   要素情報定義構造体
 *              
 */

#include "../feel_def/basic_struct.h"

#ifndef ELEMENT_INCLUDE

#define ELEMENT_INCLUDE

typedef struct Scalar_ {  /* 要素内で用いられる変数のマクロ宣言の為の構造体 */

    int         type;     /* DOUBLE or CONST */
    char       *name;     /* 変数名 */
    Expression *expr;     /* 数式情報へのポインタ */
} Scalar;
    

typedef struct Element_ {
    char *name;          /* 要素の名前           */
    int type;            /* 1 Lagrange  2 Elmite */
    int etype;           /* 形状タイプ1:line 2:tri 3:rect 4:tetra 5:cube 6: */
    int restrains;       /* 拘束条件  NO=0:なし  n:拘束fem変数の数 */
    int quad_type;       /* 要素形状の条件  0 初期化は一回だけでよい
			  *                 1 各要素行列生成毎にesetを呼ぶ  */

    int scalar_vars;     /* 計算の為のスカラー変数の宣言 */
    int doubles;         /* スカラー変数の内、double変数宣言の個数 */
    int consts;          /* スカラー変数の内、const変数宣言の個数 */

    Scalar *scalar_var;  /* スカラー構造体配列へのポインタ(連続領域に格納) */

    int    element_lets; /* 計算式の数 */
    char **let_var_name; /* 計算式の代入変数名 */
    int   *let_var_type; /* 代入変数のタイプ(CONSTまたはDOUBLE)
			    parse時に代入とエラー検査                      */
    Expression 
      **let_expr;        /* 代入文の右辺 */

    
    char **rest_var_name;
    char **rest_var_type;

    int nodes;           /* 総節点数 */
    int basis;           /* 基底関数の数 */

    Frac *r_frac;        /* r 節点座標 */
    Frac *s_frac;        /* s 節点座標 */
    Frac *t_frac;        /* t 節点座標 */
    int  *ntype;         /* 節点値の意味 */

    Expression **expr;   /* 基底関数系 */

    int  yylineno;        /* feelソース中のこの文の開始位置 */
    
} Element;


extern Element *get_element_ptr_by_name();
extern Element *get_nth_element_ptr();

/* 節点順位評価関数 */
extern double  line_eval_frac();
extern double  tri_eval_frac(); 
extern double  rect_eval_frac(); 
extern double  *cube_eval_frac();
extern double  *tetra_eval_frac();

#endif
