/*
 *  feel prototype version 2
 *
 *  Data structure for SolveBlock
 */

typedef struct _SolveBlock {

    int element_type;  /* 要素のタイプ */
    int element_node;  /* (連立した意味で)要素内の節点数 */

    int integral_method; /* 積分方法           */
    int linear_method;   /* 連立一次方程式解法 */

    int symmetric_flag;  /* 対称行列か否か */

    int unkowns;    /* 未知変数の数 */
    int knowns;     /* 既知変数の数 */
    int elemvars;   /* 要素指向変数の名前 */

    char **unknown_name;  /* 未知変数の名前 */
    char **known_name;    /* 既知変数の名前 */
    char **elemvar_name;  /* 要素指向変数の名前 */

    char **unknown_type;   /* 未知関数の近似基底関数種 */
    char **known_type;     /* 既知関数の近似基底関数種 */
    
    int Dirichlet_conditions; /* ディリクレ境界条件の数 */
    int Neumann_conditions;   /* ノイマン境界条件の数   */
    
    char **Dirichlet_data;    /* ディリクレ境界条件dataへのポインタ */
    char **Neumann_data;      /* ノイマン境界条件dataへのポインタ   */

} SolveBlock;

typedef struct _DirichletData {
    
