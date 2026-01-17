/*
 *  feel prototype version 2
 *
 *  Data structure for Declare block     1993/03/30
 */
#include "../feel_def/feel_def.h"

typedef struct _FEM_var_st {       /* FEM変数情報の構造体 */

    char *name;       /* 名称 小文字ベース、_を含む名前 */
    int   type;       /* データタイプ(変更される)       */

} FEM_var_st;



typedef struct _EWISE_var_st {     /* 要素指向変数情報の構造体 */

    char *name;              /* 名称  小文字ベース、_を含む名前 */
    int   domain_no;         /* 定義されているdomain番号        */
    int   points;            /* 要素内の対応節点数              */
    int   *r,*s,*t;          /* 基準要素での節点座標            */

} EWISE_var_st;

