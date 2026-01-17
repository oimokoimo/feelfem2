/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   YaccExpression.h
 *      Date:   1993/06/29
 *   
 *   Purpose:   Expression 構造体の宣言
 */


typedef struct _Expression {     /* 数式の為の構造体 */

    char *expr;                   /* 数式 */

    char *expr_inf;               /* 中間置記法に変換された数式   */

    int    identifiers;           /* 数式に含まれるIDENTIFIERの数 */
    char **identifier;            /* 名前へのポインタの配列       */

    int    functions;             /* 数式に含まれる関数名の数     */
    char **function;              /* 名前へのポインタの配列       */

} Expression ;


extern Expression *get_expr_structure();

