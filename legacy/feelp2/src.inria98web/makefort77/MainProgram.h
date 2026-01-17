/*
 *  feel prototype version 2
 *
 *  Data structure for Main Program
 */

#include "DeclareBlock.h"

typedef struct _MainProgram {
    
    int ndim;              /* 空間次元                     */

    char  *prog_name;      /* program名                    */       
    
    int max_feel_size;     /* 配列 feel の大きさ(定数的)   */

    int max_domain;        /* 最大domain数 */
    int max_edatset;       /* 要素グループの最大数(定数的) */
    int max_numset;        /* 数値データの最大数(定数的)   */
    int max_nodeset;       /* 節点データの最大数(定数的)   */
    int max_ewise;         /* ewise変数の最大数(定数的)    */
    int max_ewise_info;    /* ewise変数の情報配列最大数(定数的)    */

 
    int max_scheme_block;  /* scheme ブロックの最大数      */

    int *scheme_type;      /* 各scheme文の種類をいれる配列 */

    char **scheme_data;    /* 各scheme data structure へのポインタ */

}  MainProgram;


typedef struct _Variables {

    int         FEM_vars;          /* FEM変数の数          */
    FEM_var_st *FEM_var;           /* FEM変数情報への配列  */

    int           EWISE_vars;      /* 要素指向変数の数          */
    EWISE_var_st *EWISE_var;       /* 要素指向変数情報への配列  */

    int           SYSTEM_EWISE_vars;   /* システム要素指向変数の数          */
    EWISE_var_st *SYSTEM_EWISE_var;    /* システム要素指向変数情報への配列  */

    /* システム要素指向変数はたとえば節点なし自由度が指定された時に取る */

} Variables;
