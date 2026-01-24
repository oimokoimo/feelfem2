/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_comp.h
 *      Date:   1993/06/22
 *   
 *  Modified:   1998/09/03  (avsoutput extension)
 *              1999/03/17  (avsnetwork extension) 
 *   
 *   Purpose:   スキームブロックの構文解析の為の定義ファイル
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"

/*
 *  schemeの各文の情報を持っている
 *
 */

typedef struct _Scheme {
    int     type;          /* scheme文の種類 */
    void   *ptr;           /* ポインタ       */
} Scheme;


/*---------------------------------
 *   norm文
 *---------------------------------*/
typedef struct _Norm {
    char       *var_name;   /* ノルムを代入するスカラー変数 */
    Expression *expr;

    int         norm_type;

    /* 右辺に現れる変数の種類のリスト */
    int      sc_vars;

    int      int_vars;               /* 引き数用の宣言 */
    char   **int_var_name;

    int      dbl_vars;
    char   **dbl_var_name;

    int      fem_vars;
    char   **fem_var_name;

    int      ew_vars;
    char   **ew_var_name;

    int      xyz_vars;
    int      x_flag;
    int      y_flag;
    int      z_flag;

    int      fort_funcs;
    int      diff_ops;
    int      user_funcs;

    int      yylineno;
} Norm;

/*---------------------------------
 * adaptmesh
 *---------------------------------*/
typedef struct _Adaptmesh {
    Expression *expr;
    char    *option;

    int      sc_vars;
    char   **scalar_var_name;

    int      int_vars;               /* 引き数用の宣言 */
    char   **int_var_name;

    int      dbl_vars;
    char   **dbl_var_name;

    int      fem_vars;
    char   **fem_var_name;

    int      ew_vars;
    char   **ew_var_name;


    int      xyz_vars;
    int      x_flag;
    int      y_flag;
    int      z_flag;

    int      fort_funcs;
    int      diff_ops;
    int      user_funcs;

    int      yylineno;
} Adaptmesh;


/*---------------------------------
 *   let文
 *---------------------------------*/
typedef struct _Let {

    char    *var_name;               /* 変数名 */
    int      let_place;              /* let文の対象領域 */

    /* 次の二つはcheck系ルーチンで代入 */
    int      var_type;               /* 代入される変数のタイプ */
    int      let_type;               /* let文の種類別   */


    Expression *expr;
    
                                     
    int      regions;                /* 部分領域が指定されている場合 */
    char   **region_name;            /* 部分領域のリスト */

    /* 右辺に現れる変数の種類のリスト */
    int      sc_vars;

    int      int_vars;               /* 引き数用の宣言 */
    char   **int_var_name;

    int      dbl_vars;
    char   **dbl_var_name;

    int      fem_vars;
    char   **fem_var_name;

    int      ew_vars;
    char   **ew_var_name;

    int      xyz_vars;
    int      x_flag;
    int      y_flag;
    int      z_flag;

    int      fort_funcs;
    int      diff_ops;
    int      user_funcs;

    int      yylineno;               /* feel言語での位置 */
} Let;


/*---------------------------------
 *   goto文
 *---------------------------------*/
typedef struct _Goto {
    int      line_no;                /* 行番号(checkルーチンで代入) */
    char    *label;                  /* ラベル */
    int      yylineno;               /* feel言語での位置 */
} Goto;


/*---------------------------------
 *   label文
 *---------------------------------*/
typedef struct _Label {
    int      line_no;               /* 行番号(checkルーチンで代入) */
    char    *label;
    int      yylineno;
} Label;


/*---------------------------------
 *   showvec文
 *---------------------------------*/
typedef struct _Showvec {

    char    *x;
    char    *y;

    /* check系ルーチンで設定 */
    char    *domain_name;               /* 領域名       */
    char    *subdomain;            /* subdomain指定時 */

    int    etype;

    char    *filename;                  /* showvec_file用ファイル名 */
    int      file_io_no;

    int  window_id;

    /* パラメータ */
    /*
     * winsiz = 600    ウインドウサイズ 
     * xmin            表示ｘ座標の最小値
     * xmax            表示ｘ座標の最大値
     * ymin            表示ｙ座標の最小値
     * ymax            表示ｙ座標の最大値
     * mesh   = on/off メッシュを描くか  (=0 (off)  = 1 (on))
     * factor = num    ベクトルの倍率
     * scale  = on/off
     * gray   = on/off
     *
     */
    int  winsiz;
    int  IFLG;                   /* 0: 全てを自動設定
				    1: XMIN,XMAX,YMIN,YMAXを自動設定
				    2: VMAX を自動設定
				    3: 全てをユーザ設定              */
    int  mono_flag;
    int  ITYPE;                  /* 節点上(ITYPE=1) 要素上(ITYPE=0)  */
    double xmin,xmax,ymin,ymax;  /* 表示領域 */
    double vmax;
    double vm;                   /* 倍率デフォルトは 1.0 */

    int USE_EDATRANGE_flag;      /* EDATRANGEを使うかどうかのフラグ */
    int mesh_flag;
    int gray_flag;

    int      yylineno;

    char *mesg;
} Showvec;

/*---------------------------------
 *   contour文
 *---------------------------------*/
typedef struct _Contour {
    char    *var;
    int      yylineno;
    char    *filename;                  /* contour_file用ファイル名 */
    int      file_io_no;
    int      window_id;

    /* checkルーチンで設定するもの */
    char    *domain_name;               /* 領域名       */
    char    *subdomain;            /* サブ領域指定時*/

    int      etype;                     /* 基本要素形状 */
    int      edat_no;                   /* edat番号     */
    int      nodes;                     /* 上記edatの要素内節点数
					   これは、必ずしも *varと一致せず */

    /* パラメータ */
    /*
     * IFLG            xmin等の値設定フラグ 0 自動 1 XMIN,XMAXの設定
     *                                             2 UMIN,UMAX
     *                                             3 全て手動設定
     * winsiz = 600    ウインドウサイズ 
     * xmin            表示ｘ座標の最小値
     * xmax            表示ｘ座標の最大値
     * ymin            表示ｙ座標の最小値
     * ymax            表示ｙ座標の最大値
     * min             物性値の最小値(自動指定)
     * max             物性値の最大値(自動指定)
     * LOG    = on/off 対数  off(=0)
     * mesh   = on/off メッシュを描くか  (=0 (off)  = 1 (on))
     * divide = num    分割数(デフォルトは20)
     * paint  = on     既定値     
     * line   = on     線だけ
     * scale  = on/off
     * gray   = on/off
     */
    
    int set_flag;

    int IFLG;
    int  winsiz;
    double xmin,xmax,ymin,ymax;
    double umin,umax;
    int LOG_flag;
    int mesh_flag;
    int divide;
    int paint_flag;
    int scale_flag;
    int gray_flag;

    char *mesg;
     
} Contour;



/*---------------------------------
 *   displacement文
 *---------------------------------*/
typedef struct _Displacement {
    char    *u_var,*v_var;              /* displacement を示す量         */
    char    *p_var;                     /* displacement 表示時に用いる量 */
    double   fact;                    /* 変位のファクター */

    int      yylineno;
    char    *filename;                  /* displacement_file用ファイル名 */
    int      file_io_no;
    int      window_id;

    /* checkルーチンで設定するもの */
    char    *domain_name;               /* 領域名       */
    char    *subdomain;            /* subdomain指定時 */

    int      etype;                     /* 基本要素形状 */
    int      edat_no;                   /* edat番号     */
    int      nodes;                     /* 上記edatの要素内節点数
					   これは、必ずしも *varと一致せず */

    /* パラメータ */
    /*
     * IFLG            xmin等の値設定フラグ 0 自動 1 XMIN,XMAXの設定
     *                                             2 UMIN,UMAX
     *                                             3 全て手動設定
     * winsiz = 600    ウインドウサイズ 
     * xmin            表示ｘ座標の最小値
     * xmax            表示ｘ座標の最大値
     * ymin            表示ｙ座標の最小値
     * ymax            表示ｙ座標の最大値
     * min             物性値の最小値(自動指定)
     * max             物性値の最大値(自動指定)
     * LOG    = on/off 対数  off(=0)
     * mesh   = on/off メッシュを描くか  (=0 (off)  = 1 (on))
     * divide = num    分割数(デフォルトは20)
     * paint  = on     既定値     
     * line   = on     線だけ
     * scale  = on/off
     * gray   = on/off
     */

    int set_flag;

    int IFLG;
    int  winsiz;
    double xmin,xmax,ymin,ymax;
    double umin,umax;
    int LOG_flag;
    int mesh_flag;
    int divide;
    int paint_flag;
    int scale_flag;
    int gray_flag;

    char *mesg;

} Displacement;


/*---------------------------------
 *   perspect文
 *---------------------------------*/
typedef struct _Perspect {
    char    *var;
    int      yylineno;

    char    *filename;                  /* contour_file用ファイル名 */
    int      file_io_no;
    int      window_id;

    /* checkルーチンで設定するもの */
    char    *domain_name;               /* 領域名       */
    char    *subdomain;                 /* subdomain指定時 */

    int      etype;                     /* 基本要素形状 */
    int      edat_no;                   /* edat番号     */
    int      nodes;                     /* 上記edatの要素内節点数
					   これは、必ずしも *varと一致せず */

    /* パラメータ */
    /*
     * IFLG            xmin等の値設定フラグ 0 自動 1 XMIN,XMAXの設定
     *                                             2 UMIN,UMAX
     *                                             3 全て手動設定
     * winsiz = 600    ウインドウサイズ 
     * xmin            表示ｘ座標の最小値
     * xmax            表示ｘ座標の最大値
     * ymin            表示ｙ座標の最小値
     * ymax            表示ｙ座標の最大値
     * min             物性値の最小値(自動指定)
     * max             物性値の最大値(自動指定)
     */
    
    int set_flag;

    int IFLG;               /* 0 すべて  自動設定  1  XY-RANGE 自動設定
			       2 U-RANGE 自動設定  3  すべて   手動設定 */
    int USE_EDATRANGE_flag;
    int  winsiz;
    double xmin,xmax,ymin,ymax;
    double umin,umax;

    char *mesg;

} Perspect;


/*---------------------------------
 *   avs-contour文
 *---------------------------------*/
typedef struct _AVScontour {
    char    *var;
    int      yylineno;
} AVScontour;

/*---------------------------------
 *   read文
 *---------------------------------*/
typedef struct _Read {

    int     args;           /* 引き数の数       */

    char   **var_name;      /* 数式へのポインタ */

    int  yylineno;
} Read;

/*---------------------------------
 *   write文
 *---------------------------------*/
typedef struct _Write {

    int  args;  /* write文で指定された引き数の数 */
    char *filename;
    int   file_io_no;
    
    int *kind;  /* 各引き数のタイプ(EXPRESSION or STRING) */

    Expression   *expr;      /* sequentialに処理を行う為、個別の個数は必要無 */
    char        **string;

    int yylineno;
} Write;

/*---------------------------------
 *   plot文
 *---------------------------------*/
typedef struct _Plot {
    int   type;              /* PLOT文の種別     */
    char *filename;          /* 出力先ファイル名 */

    int   file_io_no;        /* ファイル出力装置番号 */
    int   window_id;         /* XPLOT時のWindow ID   */

    char *name;              /* 位置名称 (line名を想定)    */
    int   numdat_no;         /* 対応する節点集合データ番号 */

    int   plot_no;           /* プロット番号(gnuplotプログラム名に使用) */

    int    items;             /* 出力対象変数の数 */
    char **var_name;          /* 変数名リスト     */

    /* XPLOT時 の設定 */
    int    IFLG;
    int    IWW,IWH;            /* window サイズ */
    double umin,umax;

    int yylineno;

    char *mesg;
} Plot;


/*---------------------------------
 *   avsoutput statement (98/09/03)
 *---------------------------------*/

typedef struct AVSoutput_ {
  int    type;                /* future reservation */
  int    parameters;          /* number of parameters to output */
  char **fem_name;
  int    yylineno;
} AVSoutput;

typedef struct AVSnetwork_ {
  int    parameters;
  char **item_name;
  int    yylineno;
} AVSnetwork;

/*---------------------------------
 *   if文関係
 *---------------------------------*/
typedef struct {
    int   iftype;            /* if文のタイプ IF_THEN,IF_GOTO,ELSE,ENDIF */

    char *label;             /* IF_GOTO時のラベル        */
    int   lineno;            /* IF_GOTO時の行き先        */

    Expression *left;
    Expression *right;
    
    int      sc_vars;
    char   **sc_var_name;


    int   condition_type;    /* 条件式の種類             */

    int yylineno;
} IFblock;



/*[ external functions for scheme_comp routines] */
    
char *convert_let_expression();
char *convert_fem_let_expression();

Scheme *get_nth_scheme_struct();







