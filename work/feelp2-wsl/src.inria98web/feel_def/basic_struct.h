/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   basic_struct.h
 *      Date:   1993/07/13
 *   
 *   Purpose:   基本的な構造体を定義する
 *   
 *   構造体     Frac          分数
 *              Expression    数式
 *              Node          節点
 *       
 *       
 */

/* 分数構造体 */

#ifndef BASIC_STRUCT
#define BASIC_STRUCT  


typedef struct Frac_ {
  int bunbo;
  int bunsi;
} Frac;

/* 数式構造体 */
typedef struct _Expression {     /* 数式の為の構造体 */

    char *expr;                   /* 数式 */

    char *expr_inf;               /* 中間置記法に変換された数式   */

    int    identifiers;           /* 数式に含まれるIDENTIFIERの数 */
    char **identifier;            /* 名前へのポインタの配列       */

    int    functions;             /* 数式に含まれる関数名の数     */
    char **function;              /* 名前へのポインタの配列       */

} Expression ;


/* 節点座標構造体 */
typedef struct {
    Frac r;               /* r 座標 */
    Frac s;               /* s 座標 */
    Frac t;               /* t 座標 */

    /* 以下の情報は要素節点データ集合時には使用されない(edat_make.cにおいて) */

    int freedom;          /* 節点自由度 */
    char **var_name_ptr;  /* 変数名へのポインタ */
    int *node_type;       /* 節点値意味 */

} Node;

extern Expression *get_expr_structure();

#endif
