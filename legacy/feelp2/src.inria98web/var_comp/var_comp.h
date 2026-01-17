/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   var_comp.h
 *      Date:   1993/06/03 (Modified)
 *      
 *  Modified:   1998/09/03 Add AVS mode
 *              1999/02/23 AVS initial value
 *   
 *   Purpose:   変数定義情報構造体定義
 *              
 *              
 */

typedef struct _Var {
    int     type;           /* 変数種別       */
    int     avsmode;        /* AVS mode (98/09/03) */
    int     DS_B_niv;       /* B data structure level no. 
n			       (98/12/17, set in modulef/fort77/mf_make_scheme_femalloc.c
			                         modulef/fort77/mf_make_scheme_ewisealloc.c)
			    */
    char   *name;           /* 変数名         */
    int     initial;        /* 初期値が定義されているか  */
    char   *val;            /* 値または基底関数のタイプ  */
    int     yylineno;       /* yylineno            */
}  Var;

typedef struct _MATERIAL_var {
    int      materials;     /* 物質種別の数 */
    double  *val;           /* その値       */
} MATERIAL_var;


typedef struct _EWISE_type {
    char *name;       /* ewise 変数名 */

    char *domain_name;    /* ewise変数の定義場所(領域名,数値積分法名)   */
    int   etype;          /* 定義domainに対応するetype番号              */
    int   edatno;         /* 代表edat番号  domainの代表edat番号を持とう */
    int   domain_no;
    char *quadrature;     /* 数値積分法の名称による評価点の指定時に使用 
			     数値積分法以外の節点指定の場合はNULL       
			     →make_ecal等で判定材料となっている      */
    int   points;         /* 要素内の節点数 */

    double r[MAX_NODES_FOR_EWISE];  /* 基準座標での節点位置 */
    double s[MAX_NODES_FOR_EWISE];
    double t[MAX_NODES_FOR_EWISE];

    int    yylineno;      /* feelソースでの位置 */

} EWISE_type;


typedef struct _FEM_type {
    char  *name;          /* fem変数名 */

    char  *domain_name;   /* 定義領域名 */

    char  *type;          /* 基底関数の名前 */
    int    etype;         /* 定義されている図形要素(check系ルーチンで代入) */
    int    restrictions;  /* 拘束変数の数   */
    char **restrict_var;  /* 拘束変数名     */
    char **restrict_type; /* 拘束変数の種別 */
    int    yylineno;      /* feelソースでの位置 */
} FEM_type;


typedef struct _FEM_var {
    char *name;           /*  fem変数名 */
    int   basis_types;    /* 指定されている基底関数の数 */
    FEM_type *fem_type_ptr[MAX_FEM_VARIATION];

} FEM_var;


typedef struct _EWISE_var {

    char *name;           /*  ewise変数名 */
    int   ewise_types;    /*  このewise変数名に対応している種類数 */

    EWISE_type *ewise_type_ptr[MAX_EWISE_VARIATION];
} EWISE_var;



/* 外部関数プロトタイプ宣言 */

extern Var * get_nth_var_ptr();
extern Var * get_nth_int_ptr();
extern Var * get_nth_double_ptr();
extern Var * get_nth_const_ptr();
extern Var * get_nth_fem_ptr();
extern Var * get_nth_ewise_ptr();
extern Var * get_nth_material_ptr();
extern Var * get_var_ptr_by_name();         /* addition for modulef to get B niveau
					       1998/12/17                           */

extern EWISE_type *get_nth_ewise_type_ptr();
extern FEM_type   *get_nth_fem_type_ptr();
extern EWISE_var  *get_ewise_ptr_by_name();
extern FEM_var    *get_fem_ptr_by_name();

extern EWISE_type *get_ewise_type_ptr_by_name();

extern FEM_type *get_fem_type_ptr_by_2name();
extern EWISE_type *get_ewise_type_ptr_by_2name();
extern int get_fem_etype_by_2name();
extern Var *get_var_ptr_by_name();

/* ユーザ定義関数名 */
extern char *get_nth_userfunc_name();
extern char *get_domain_name_by_no();


/* avs 99/02/23 */
extern Var *get_nth_avs_feel_var_ptr();
