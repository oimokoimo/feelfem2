/*
 * feel p2  configuration file    
 *
 * feel プロトタイプ第二版 属性設定ファイル
 *
 * Made  1993/05/25
 *
 * Last Modified: 1998/11/02
 */

#ifdef  _MSC_VER       /* Microsoft Visual C++ only */
#define MSDOS          /* Win32 version */
#endif


#define DEBUG
#ifdef DEBUG

#define DBGWRT  printf
#define FDBGWRT fprintf

#else

#define DBGWRT  nullwrt          /* main/debug.cにて定義 */

#endif


/*---------------------------------
   実行ファイル名、ファイル数
  ---------------------------------*/
#define MAX_FILES              900   /* feel fort77 のファイル数  */
#define EXENAME           "feelgo"   /* feel の実行時プログラム名 */
#define DEFAULT_DIMENSION        2   /* feel のデフォルト次元     */

/*----------------------------------
  ファイル種別  MakeMakefileにて利用
  ----------------------------------*/
#define SYSTEM_LIBRARY           0    /* システムが提供するライブラリ   */
#define USER_LIBRARY             1    /* ユーザ入力によって変化するもの */
/*---------------------------------
   一般シンボル定数
  ---------------------------------*/
#define NO       0
#define YES      1
#define NOTHING -1
#define UNDEFINED -1

#define OK       0     /* OKを表すシンボル値   */
#define ERR   -999     /* エラーを表すシンボル */

/* 節点に関するもの */
#define ISOLATE     0    /* 孤立点 */
#define EDGE        1    /* regionの外部境界上の点 */
#define INNER_EDGE  2    /* regionの内部境界上の点 */


/* 局所座標シンボル */
#define LOCAL_X_VAR   "r"
#define LOCAL_Y_VAR   "s"
#define LOCAL_Z_VAR   "t"


/* LISPの数式表現に関するもの */
#define LISP_EXP_ZERO   "0.0d0"       /* LISPのプログラムが0として出す値  */
#define EXPR_BUFSIZ     40000         /* 数式の一行の最大の長さ           */
#define LIMIT_LINE      100           /* formula maximum length in FORT77 */ 

/* 要素形状に関するもの */

#define LINE    1     /* 線分    */
#define TRI     2     /* 三角形  */
#define RECT    3     /* 四辺形  */
#define CUBE    4     /* 立方体  */
#define TETRA   5     /* 三角錐  */

#define MAX_MID_POINTS 50    /* 中間節点、内部節点の最大数 */

/* 領域形状に関する定数 */

#define MESH_LINE          1  
#define MESH_REGION        2
#define MESH_POINT         3
#define MESH_DOMAIN        4
#define MESH_ARC           5
#define MESH_SUBDOMAIN     6

#define LINE_STRING  "line"
#define TRI_STRING   "tri"
#define RECT_STRING  "rect"
#define CUBE_STRING  "cube"
#define TETRA_STRING "tetra"

/* 積分方法に関するもの (SolveElement構造体のquad_type) */
#define NUMERICAL   1
#define ANALYTICAL  2

/* 境界用ガウス数値積分点数の最大 */
#define MAX_GAUSS_POINTS 7

/* 形状関数に関するもの (solve_chk_shape_functionで指定) */
#define DEFAULT_LINE_SHAPE_FUNCTION  "L1"    /* １次元要素の形状関数既定値 */
#define DEFAULT_TRI_SHAPE_FUNCTION   "P1"    /* 三角形要素の形状関数既定値 */
#define DEFAULT_RECT_SHAPE_FUNCTION  "Q1"    /* 四角形要素の形状関数既定値 */
#define SHAPE_FUNCTION_SYMBOL        "shape-function" /* '-' を入れて他の
							 IDENTIFIERと区別  */

/* 解析的積分法の名称 */
#define ANALYTIC_QUAD   "analytic"

/* 数値積分法の種別 */
#define QUAD_NORMAL        1      /* 積分点とその重みのみの数値積分法 */
#define QUAD_INTERPOLATE   2      /* 内挿指定の変数付き               */

#define DEFAULT_BOUNDARY_GAUSS_POINTS  3  /* 境界積分のシステム規定積分点数 */


/* 連立一次方程式に関するもの */
#define DEFAULT_LINEAR_METHOD 1      /* デフォルトはスカイライン法 */
#define DEFAULT_MPP_LINEAR_METHOD 6  /* MPPのデフォルトはMPPSCG法  */
#define SKYLINE             1
#define PBCG                2
#define PCGS                3
#define BICGSTAB            4
#define ICCG                5
#define MPPSCG              6

#define SYMMETRY            1
#define NON_SYMMETRY        2
#define DIAGONAL            3

#define SYMMETRY_WORD  "symmetry"
#define DIAGONAL_WORD  "diagonal"


#define SKYLINE_METHOD  "skyline"
#define PBCG_METHOD     "pbcg"
#define PCGS_METHOD     "pcgs"
#define BICGSTAB_METHOD "bicgstab"
#define ICCG_METHOD     "iccg"
#define MPPSCG_METHOD   "mppscg"


/* Newton-Raphson Iteration */
#define DEFAULT_EPS                   "1.0E-10"
#define DEFAULT_NONLINEAR_MIS_RATE    "0.5"
#define DEFAULT_NONLINEAR_MIS_TIMES    3

/* MESH GENERATION BAMG  bamg System interface  BAMG was developed in INRIA */
/* #define BAMG_COMMAND_NAME     "bamg-g >/dev/null" */

#ifdef MSDOS
#define BAMG_COMMAND_NAME     "bamg.exe  >NUL"
#define BAMG_FDAT_COMMAND     "feel.bamg.exe"
#define BAMG_ADPT_COMMAND     "feel.bamg.adpt.exe %d"
#else
#define BAMG_COMMAND_NAME     "bamg  >/dev/null"
#define BAMG_FDAT_COMMAND     "feel.bamg.exe"
#define BAMG_ADPT_COMMAND     "feel.bamg.adpt %d"
#endif

#define BAMG_DEFAULT_OPTION   "-splitpbedge -nbv 2000000"
#define BAMG_RECT_OPTION      "-thetaquad 30.0 -2q"
#define BAMG_ADAPT_DEFAULT    "-AbsError"                /* for avs_def_file */
#define BAMG_ADPT_DEFAULT_OPTION   "-AbsError -err 0.05"
#define BAMG_GEOM_FILE        "bamg.geom"
#define BAMG_MESH_FILE        "bamg.mesh"
#define BAMG_BTOF_FILE        "bamg.feel"
#define BAMG_FTOB_FILE        "feel.bamg"
#define BAMG_ADPT_FILE        "bamg.adpt.%d"
#define BAMG_DEFAULT_ERR      "0.01"





/* エルミート要素に関するキーワード */
#define D0      0
#define DX      1
#define DY      2
#define DZ      3
#define DN      4
#define DXX     5
#define DYY     6
#define DZZ     7
#define DXY     8
#define DYZ     9
#define DZX    10

#define DX_KEY   "dx"
#define DY_KEY   "dy"
#define DZ_KEY   "dz"
#define DN_KEY   "dn"
#define DXX_KEY  "dxx"
#define DYY_KEY  "dyy"
#define DZZ_KEY  "dzz"
#define DXY_KEY  "dxy"
#define DYZ_KEY  "dyz"
#define DZX_KEY  "dzx"

/* 要素タイプに関するもの */

#define LAGRANGE  1   /* ラグランジェ要素 */
#define HELMITE   2   /* エルミート要素   */

/* 問題のタイプ */
#define LINEAR         0    /* 線形定常問題   */
#define NONLINEAR      1    /* 非線形定常問題 */
#define TIME_LINEAR    2    /* 線形非定常問題 */
#define TIME_NONLINEAR 3    /* 非線形非定常   */


/*------------------------------------------------------
  feelがライブラリとして持つ要素、数値積分法に関する定義
  ------------------------------------------------------*/
#define MAX_SYSTEM_ELEMENT       30
#define MAX_SYSTEM_QUADRATURE    30

/*------------------------------------
   feelの制限値
  ------------------------------------*/
#define MAX_NODES_PER_ELEMENT    50  /* 要素内の最大節点数 */
#define MAX_BASIS_PER_ELEMENT    50  /* 要素内の最大基底関数数 */
#define MAX_RESTRAINS            10  /* 拘束fem変数の最大数 */
#define MAX_EXPRESSIONS        2000  /* LISPで前置記法から変換する際の
					スタックの大きさ(cf. pre-to-inf) */

#define DUPLICATE_CHECK          99  /* 重複定義検査の為の配列の大きさ 
					check/duplicate_check.cで使用    */
#define MAX_UNIQ_ITEMS           99  /* 利用変数表作成の為の配列の大きさ
					system/uniq_list.cで利用         */

/*------------------------------------
   feel言語の設定可能最大パラメータ数
  ------------------------------------*/

/* feelの情報各文の最大数 ------宣言文関係------*/

#define MAX_VARIABLES     100   /* 変数の最大値 */
#define MAX_ELEMENT        30   /* element文の最大数 */
#define MAX_ELEMENT_SCALAR 20   /* element文で使用可能なスカラー変数の最大数 */
#define MAX_ELEMENT_LETS   20   /* element文で使用可能な代入文の最大数 */
#define MAX_USERFUNCS      20   /* ユーザ指定関数の最大数 */

#define MAX_QUADRATURE     10   /* quadrature文の最大数         */
#define MAX_QUAD_POINTS    30   /* 積分点数の最大数             */
#define MAX_QUAD_RVARS     20   /* 数値積分関数への引き数       */
#define MAX_QUAD_INTERPOLATES 20   /* 内挿値を指定する変数の数  */
#define MAX_QUAD_CONSTS    20   /* 積分計算に用いる定数変数の数 */
#define MAX_QUAD_DOUBLES   20   /* 積分計算に用いる実数変数の数 */
#define MAX_QUAD_LETS      30   /* 積分計算に用いる代入文の数   */

#define MAX_EWISE          20   /* ewise変数の最大数(feel fort77でも使用する)*/
#define MAX_EWISE_TYPES    60   /* ewise_typeのスタック＝ewise文の最大値！   */

#define MAX_FEM_TYPES      60   /* fem_typeのスタック＝fem文の最大値！ */
#define MAX_FEM_VARIATION    10 /* 一つのfem変数に対応付ける基底関数名の最大 */
#define MAX_EWISE_VARIATION  10 /* 一つのfem変数に対応付ける基底関数名の最大 */

#define MAX_NODES_FOR_EWISE 10  /* ewise変数の要素内節点の最大数 */

#define MAX_TERM_VARS      38   /* quadrature,element等でterm_convertで
				   必要になる変数名バッファの大きさ     */
/********************************/
/*#define MAX_FEM            20 */   /* fem変数の最大数 */
/*#define MAX_DOUBLE         20 */  /* double変数の最大数 */
/********************************/


/* feelの情報各文の最大数 ------領域定義関係------*/

#define MAX_MESH_NAMES     200       /* メッシュ生成に関する名称
					の最大数                 */
#define MAX_DOMAINS          5       /* DOMAIN文の最大数         */
#define MAX_SUBDOMAINS      11       /* DOMAIN文の最大数         */
#define MAX_REGIONS         38       /* REGION文の最大数         */
#define MAX_NODES           16       /* nodes文の最大数 上２つ   */
#define MAX_BOUNDARIES      11       /* 境界構成点               */
#define MAX_LINES          100       /* LINES文の最大数          */
#define MAX_POINTS         100       /* POINTS文の最大数         */
#define MAX_CURVE_POINTS    99       /* MAX CURVE ELEMENT POINTS */

#define MAX_POINTS_IN_LINE  99       /* MAX POINTS PER AN LINE   */
#define MAX_POINTS_IN_EDGE  99       /* MAX POINTS PER AN EDGE   */
#define MAX_CURVE           10       /* MAX CURVE statement      */
#define MAX_RECT            20       /* MAX RECT statement       */

#define DEFAULT_NODES      200       /* システムの節点既定値     */
#define DEFAULT_DIMENSION    2       /* 次元のデフォルト         */

#define MAX_CONC_REGIONS    10

/* feel言語schemeブロックの制限 */

#define MAX_SCHEMES            100   /* scheme文の最大数             */
#define MAX_SOLVE               38   /* solve文の最大数              */
#define MAX_EQUATIONS           38   /* 要素グループ内equationのmax  */
                                     /* これは未知変数数でもある     */
#define MAX_SOLVE_ELEMENT       38   /* SolveElementの総数           */
#define MAX_EQUATION_TERMS      11   /* 一つの方程式の分割数         */
#define MAX_BCONDS              38   /* solve文中の各境界条件数      */
#define MAX_NEUMANN_ARGS        11   /* ノイマン条件での仮変数の最大 */


#define MAX_RW_ARGS             10   /* Read文,Write文における引き数の最大 */


/*-----------------------------------
 *  AVS/Express extension 
 *  1998/09/03
 *
 *-----------------------------------*/
#define MAX_AVSOUTPUT           10   /* number of maximum avsoutput
					statements                   */
#define MAX_AVSNETWORK          10   /* number of maximum avsnetwork
					statements                   */

#define DEFAULT_AVS_MODULENAME  "feelavs"    /* Module name called by AVS*/
#define DEFAULT_AVS_MODULE_FILE "feelavs.f"  /* Program file             */
#define AVS_OUTPUT_SUBFUNC      "feelavsout"

#define AVS_TEMPLATE_V_NAME     "templ.v"        /* templ.v (system name) */
#define AVS_UCD_V_FNAME         "feel.v"         /* feel.v     */
#define AVS_MACRO_V_FNAME       "feelmacro.v"    /* macro.v    */
#define AVS_FEELMESH_V_FNAME    "feelmesh.v"     /* feelmesh.v */
#define AVS_ADAPTMESH_V_FNAME   "feeladapt.v"    /* feeladapt.v*/
#define AVS_FEELNET_V_FNAME     "feelnet.v"      /* feelnet.v  */

#define DEFAULT_AVS_VMODULE_NAME "Feel"       /* module name in v */
#define DEFAULT_AVS_DIR_NAME     "feel"       /* build directory name */
#define DEFAULT_AVS_OUTPUT_PORT  "feelucd"    /* Output port name         */
#define DEFAULT_AVS_FORT77_NAME  "feel.f"     /* one packed name */
#define AVS_FEELMESH_FNAME       "feelmesh.c" /* mesh interface  */

/*------------------------------------
   feel言語変数宣言ブロックシンボル
  ------------------------------------*/
#define CONST                1
#define INT                  2
#define DOUBLE               3
#define FEM                  4
#define EWISE                5
#define MATERIAL             6
#define SYSTEM_FEM           7
#define SYSTEM_EWISE         8
#define SYSTEM_VAR           9  /* 空間変数 x,y,z */
#define TEST_VAR            10  /* 試験関数を表すシンボル $ */
/*------------------------------------
   feel言語スキームブロックシンボル
  ------------------------------------*/

#define NOT_DEFINED          0
#define LABEL                1
#define GOTO                 2
#define LET                  3


#define READ                 6
#define WRITE                7
#define SOLVE                8
#define NONLINEAR_SOLVE      9
#define IF                  10
#define WHILE               11
#define CONTOUR             12
#define AVS_CONTOUR         13
#define PERSPECT            14
#define SHOWVEC             15
#define PLOT_FILE           16
#define CONTOUR_FILE        17
#define SHOWVEC_FILE        18
#define IF_THEN             19
#define IF_GOTO             20
#define ELSE                21
#define ENDIF               22
#define FILE_WRITE          23
#define TIME_PLOT_FILE      24
#define PERSPECT_FILE       25
#define XPLOT               26
#define DISPLACEMENT        27
#define DISPLACEMENT_FILE   28
#define NORM                29    /* これはNORMシリーズの代表番号 */
#define L2NORM              30
#define MAXNORM             31
#define ADAPTMESH           32

/* solver flag (for -lfeelG option)*/
#define ITERATIVE_SOLVER   100
#define MPP_SOLVER         200


/* LET文の詳細 */
#define NORMAL_LET           1
#define LET_AT               2
#define LET_ON               3
#define LET_IN               4

/* 代入関係の記号 */
#define LET_SC_SC            1
#define LET_SC_FEMEWISE      2

#define LET_FEM_SC           11
#define LET_FEM_FEM          12
#define LET_FEM_FEMEWISE     13
#define LET_FEM_OPERATOR     14

#define LET_EWISE_SC         21
#define LET_EWISE_FEM        22
#define LET_EWISE_EWISE      23
#define LET_EWISE_FEMEWISE   24
#define LET_EWISE_OPERATOR   25

#define DIFFEQ               1    /* 偏微分方程式で与えられる問題 */
#define WEAKEQ               2    /* 弱形式で与えられる問題       */
#define FUNCTIONAL           3    /* 汎関数の停留値問題として与えられる問題 */

/* Write文で使用する */

#define EXPR                 1
#define STRING               2

/***********************************************
 *         FEEL FORT77 に関する定義            *
 ***********************************************/

/* feel fort77 の制限定義 */

#define FEEL_ARRAY_SIZE  10000

#define MAX_DOMAIN          10  /* 最大domain数          */
#define MAX_EDATSET         38  /* 最大要素節点データ数  */
#define MAX_NODESET         20  /* 節点集合データの最大数 */
#define MAX_NUMSET          10  /* 数値データ集合の最大数 */
/* #define MAX_EWISE        10  これは、feel言語の定義に含まれる */
#define MAX_EWISE_INFO      12  /* = MAX_DOMAIN + 2 (要素グループデータ,要素内節点数 */

/* モード定義 */

/*  feel_solのn_make(*)に関するモード */
#define MAKE_ALL         0    /* 累積節点自由度、LU分解何れも無し     */
#define MAKE_MATRIX      1    /* 累積節点自由度有り、MATRIXは作り直し */
#define MAKE_NONE        2    /* 全てファイルから読み込み             */

/*  mode_ex  実行モード */
#define NORMAL_EXEC      0    /* 通常実行モード */
#define CHECK_DATA       1    /* ヤコビアン等が０にならないか徹底的に調べる */
                              /* このモードはif文の嵐になる                 */
                              /* チェック項目  ヤコビアン、面積の非正値等   */
#define READ_DATA_ONLY   2    /* データを呼んで書くだけ                     */

/*  mode_output 表示関係モード */
#define NORMAL_OUTPUT    0    /* 普通の出力 */
#define IGNORE_GRAPH     1    /* Graphic 出力の抑制 */
#define IGNORE_FILE      2    /* ファイル出力の抑制 */
#define IGNORE_BOTH      3    /* graphic,ファイル双方の出力抑制 */


/*===========================================================*/
/*   並列計算機に関する設定  Parallel version defines        */
/*===========================================================*/
#define CENJU_MAX_PE    64


/* 並列計算機PE別データ作成時のデータ配列の大きさ */
#define MAX_PARA_NCONT_1  20   /* 共通ヘッダーの大きさ */
#define MAX_PARA_NCONT_2  80   /* PE内変数数           */


/*===========================================================*/

/* 生成LISPプログラム ファイル */

#define LISP_EXEC_FILE  "feel.l"

/* LISPプログラム用のone sentence の長さ */
#define LISP_BUFSIZ     1024

/* プログラム名の長さ */
#define FNAME_SIZE        80    /* ファイル名は80字まで */


/* 生成FORTRANプログラム関数名、ファイル名定義 */

#define TMP_FORTFILE    "oimotmp"  /* 72カラムチェック時のtemporary file */

#define INPUT_FILE      "feel_dat"
#define OUTPUT_FILE     "feel_out"

#define FEEL_MAIN       "feel_main.f"  /* メインプログラムのファイル名   */
#define PROG_FEEL_MAIN  "feel_main"    /* メインプログラムのモジュール名 */

#define FILSET          "filset.f"     /* ファイル装置番号設定プログラムファイル名 */

#define PROG_CLOSE_FILE "close_file"   /* モジュール名 */
#define CLOSE_FILE      "close_file.f" /* ファイルクローズルーチン */

#define PROG_FILSET     "filset"       /* モジュール名 */


#define DATINP_MAIN       "datinp.f"   /* データ入力プログラム メインルーチン */
#define PROG_DATINP_MAIN  "datinp"  

#define KEY_FEEL          "'FEEL'"     /* FEEL用入力データの先頭を示す */

#define INP_NODE          "dat_node.f" /* 節点データ入力プログラム            */
#define PROG_INP_NODE     "dat_node"
#define KEY_NODE          "'NODE'"     /* 節点データキーワード */
#define KEY_NODE_REAL     "NODE"


#define INP_EDAT          "dat_edat.f" /* 要素データ入力プログラム            */
#define PROG_INP_EDAT     "dat_edat" 
#define KEY_EDAT          "'EDAT'"
#define KEY_EDAT_REAL     "EDAT"

#define INP_NSET          "dat_nodeset.f" /* 節点集合データ入力プログラム     */
#define PROG_INP_NSET     "dat_nodeset"
#define KEY_NSET          "'NSET'"
#define KEY_NSET_REAL     "NSET"

#define INP_COMT_COMT     "dat_comment.f" /* コメント印字プログラム */
#define PROG_INP_COMT     "dat_comment"
#define KEY_COMT          "'COMT'"
#define KEY_COMT_REAL     "COMT"

#define INP_NUM           "dat_num.f"  /* 関数値データ入力プログラム          */
#define PROG_INP_NUM      "dat_num"  
#define KEY_NUM           "'NUM '"
#define KEY_NUM_REAL      "NUM "

#define INP_IP            "dat_ip.f"
#define KEY_IP            "'IP  '"
#define KEY_IP_REAL       "IP  "
#define PROG_INP_IP       "dat_ip"


#define KEY_END           "'END '"     /* 入力ファイルの終了キーワード */
#define KEY_END_REAL      "END "

/*-------------------------------------------------------------
  scheme文に関するプログラム名、ファイル名
  -------------------------------------------------------------*/
#define ADAPTMESH_FNAME   "adaptmesh%d.f"
#define ADAPTMESH_NAME    "adaptmesh%d"

#define CONTOUR_FNAME     "contr%d.f"
#define CONTOUR_NAME      "contr%d"

#define PERSPECT_FNAME     "perspect%d.f"
#define PERSPECT_NAME      "perspect%d"

#define SHOWVEC_FNAME     "showvec%d.f"
#define SHOWVEC_NAME      "showvec%d"

#define CONTOUR_FILE_FNAME     "contrf%d.f"
#define CONTOUR_FILE_NAME      "contrf%d"

#define DISPLACEMENT_FNAME  "dsplc%d.f"
#define DISPLACEMENT_NAME   "dsplc%d"

#define SHOWVEC_FILE_FNAME     "showvecf%d.f"
#define SHOWVEC_FILE_NAME      "showvecf%d"

/*-------------------------------------------------------------
  solve文に関するプログラム名、ファイル名
  -------------------------------------------------------------*/

#define ELEM_MAIN_FNAME   "elem%d_%d.f"  /* solve_element のmainに相当 */
#define ELEM_MAIN_NAME    "elem%d_%d"    /* 上記ルーチンのプログラム名 */

#define ELEM_SET_FNAME    "eset%d_%d_%d.f"  /* 各solve_elementに対応する
					       初期化プログラムファイル名 */
#define ELEM_SET_NAME     "eset%d_%d_%d"    /* 上記ルーチンのプログラム名 */

#define ELEM_CAL_FNAME    "ecal%d_%d.f"  /* 各solve_elementに対応する実際の
					    要素計算プログラムファイル名    */
#define ELEM_CAL_NAME     "ecal%d_%d"    /* 上記ルーチンのプログラム名      */
#define ELEM_CAL_DAT_NAME "ecal%d-%d-%d.dat"  /* LISP出力のデータファイル名 */

#define ELEM_DEV_FNAME    "edev%d_%d.f"     /* 連立一次方程式解を
					       fem変数に分割                */
#define ELEM_DEV_NAME     "edev%d_%d"       /* 上記ルーチンのプログラム名   */

#define ELEM_NDEV_FNAME    "nedev%d_%d.f"   /* 非線形方程式の逐次近似における
					       fem変数の更新                */
#define ELEM_NDEV_NAME     "nedev%d_%d"     /* 上記ルーチンのプログラム名   */

#define DCOND_NAME        "dcond%d_%d"      /* Dirichlet条件ルーチン */
#define DCOND_FNAME       "dcond%d_%d.f"    /* 上記ルーチンのプログラム名 */

#define DCOND_CO_NAME     "dcMPP%d_%d"      /* MPPSCG時の孫サブルーチン名   */
#define DCOND_CO_FNAME    "dcMPP%d_%d.f"    /* 上記ルーチンのプログラム名 */

#define NCOND_NAME        "ncond%d_%d"      /* Neumann条件ルーチン          */
#define NCOND_FNAME       "ncond%d_%d.f"    /* 上記ルーチンのプログラム名   */

#define NCOND_CO_NAME     "ncMPP%d_%d"      /* MPPSCG時の孫サブルーチン名   */
#define NCOND_CO_FNAME    "ncMPP%d_%d.f"    /* 上記ルーチンのプログラム名 */

#define NCONDA_NAME       "nconda%d_%d"     /* 要素型Neumann条件            */
#define NCONDA_FNAME      "nconda%d_%d.f"   /* 上記ルーチンのプログラム名   */

#define LET_NAME          "let%d"           /* LET文に対応するルーチン名称  */
#define CO_LET_NAME       "colet%d"         /* LET文補助ルーチン名称        */
#define ONE_LET_FNAME     "let.f"           /* まとめる場合のlet文          */

#define NORM_NAME         "norm%d"          /* NORM文に対応するルーチン名称 */

#define PLOT_NAME         "feelpt%d"       /* PLOT文に対応するルーチン名称 */
#define CO_PLOT_NAME      "coplot%d"       /* PLOT文補助ルーチン名称       */
#define PLOT_FNAME        "feelpt%d.f"     /* 上記ルーチンのプログラム名   */


/*-------------------------------------------------------------
  並列処理に関するプログラムファイル
  -------------------------------------------------------------*/
#define BLOCK_DATA_NAME    "mk_pdat%d"   /* サブルーチン名(solve文毎にある) */
#define BLOCK_DATA_FNAME   "mk_pdat.f"   /* 共通ファイル名   */

/*-------------------------------------------------------------
  ライブラリ名
  -------------------------------------------------------------*/
#define EWS4800_CONTOUR_LIB        "-lfeelG"
#define EWS4800_R4000_CONTOUR_LIB  "-lfeelG_R4000"
#define DEC_ALPHA_CONTOUR_LIB      "-lfeelG"
#define CONVEX_CONTOUR_LIB         "-lfeelG"
#define IRIS_CONTOUR_LIB           "-L/usr/people/sgi1_4/fujio/lib -lfeelG"
#define HP700_CONTOUR_LIB          "/net/tetrodon/home1/fujio/lib/libfeelG.a"
#define SPARC_CONTOUR_LIB          "-lfeelG"
/* #define FreeBSD_CONTOUR_LIB        "-L/home/fujio/feel/lib.intel -lfeelG" */
#define FreeBSD_CONTOUR_LIB        "-L/usr/people/sun1/fujio/lib -lfeelG"
#define Cenju3_CONTOUR_LIB         "-lpfeelG"
#define Linux_CONTOUR_LIB          "-L/home/fujio/lib -lfeelG"

#define R4000_LIB                  "-Kmips2"

#define EWS4800_X11_LIB            "-lX11 -lsocket -lnsl"
#define DEC_ALPHA_X11_LIB          "-lX11"
#define CONVEX_X11_LIB             "-lX11"
#define IRIS_X11_LIB               "-lX11"
#define SPARC_X11_LIB              "-lX11"
#define HP700_X11_LIB              "-lX11 -lm"
/* #define FreeBSD_X11_LIB            "-L/usr/X11R6/lib -lX11" */
#define FreeBSD_X11_LIB            "-L/usr/X11R6/lib -lX11"
#define Linux_X11_LIB            "-L/usr/X11R6/lib -lX11"

/* MPI ライブラリ */
#define Cenju3_MPI_LIB             "/usr/nec/cenju-3/lib/libmmpi.a"

/*-------------------------------------------------------------
  マシン名
  -------------------------------------------------------------*/
#define EWS4800        1
#define EWS4800_R4000  2
#define SX3            3
#define SX2            4
#define CONVEX         5
#define CENJU3         6
#define IRIS           7
#define SPARC          8
#define HP700          9
#define DEC_ALPHA     10
#define FreeBSD       11
#define Windows       12
#define Linux         13
/*-------------------------------------------------------------
  MESH生成実行コマンド
  -------------------------------------------------------------*/
#ifdef MSDOS
#define MESH_EXEC_COMMAND_TRI "feel.Tri.exe >NUL"
#define MESH_EXEC_COMMAND_QUA "feel.Qua.exe >NUL"
#define MESH_EXEC_COMMAND_MID "feel.Mid.exe >NUL"
#define MESH_EXEC_COMMAND_FIN "feel.Fin.exe >NUL"
#define MESH_EXEC_COMMAND_DIV "feel.Div.exe >NUL"
#else
#define MESH_EXEC_COMMAND_TRI "feel.Tri.exe"
#define MESH_EXEC_COMMAND_QUA "feel.Qua.exe"
#define MESH_EXEC_COMMAND_MID "feel.Mid.exe"
#define MESH_EXEC_COMMAND_FIN "feel.Fin.exe"
#define MESH_EXEC_COMMAND_DIV "feel.Div.exe"
#endif


#define MESH_EXEC_COMMAND3   "feel.mesh3"
#define MESH_EXEC_COMMAND4   "feel.mesh4"

/*-------------------------------------------------------------
  MPI ヘッダーファイル
  -------------------------------------------------------------*/
#define MPI_HEADER_FILE      "'mpi.incl'"

/*-------------------------------------------------------------
  LISPプログラムのテンポラリーファイルの名称
  -------------------------------------------------------------*/
#define DEFAULT_DOS_FEEL_DIR  "c:\\feel"
#define DOS_LISP_COMMAND      "%s\\lisp -M %s\\lispinit.mem"
#define DOS_LISP_TMP          "$lisp.l"

#define DEFAULT_DOS_EXPRESS_DIR  "c:\\Express"
#define DEFAULT_UNIX_EXPRESS_DIR "/usr/express"
#define DEFAULT_CURRENT_DIR      "   "

#define LISP_COMMAND "/usr/bin/sbcl"     /* ubuntu */
/* #define LISP_COMMAND   "/home/fujio/bin/saved_gcl >/dev/null" */  /* kartoffel/LINUX */ 
/* #define LISP_COMMAND   "/usr/local/bin/lisp >/dev/null" */ /* potato.csl.cl.nec.co.jp/LINUX */
/* #define LISP_COMMAND   "/net/tetrodon/home1/fujio/bin/saved_gcl /net/tetrodon/home1/fujio/bin/ >/dev/null" */  /* anchois.inria.fr */
/* #define LISP_COMMAND   "/demo/people/guest/feel/bin/saved_gcl /demo/people/guest/feel/bin/ >/dev/null" */  /* indy1.kubota.co.jp */
/* #define LISP_COMMAND   "/usr/people/sun1/fujio/bin/saved_gcl /home/fujio/bin/ >/dev/null" */   /* congre.inria.fr */
/* #define LISP_COMMAND   "/net/congre/home/fujio/bin/saved_gcl /home/fujio/bin/ >/dev/null" */   /* congre.inria.fr */
/* #define LISP_COMMAND   "/usr/lib/gcl-2.2/unixport/saved_gcl /usr/lib/gcl-2.2/unixport/ >/dev/null" */   /* pc10.ima.umn.edu */
/* #define LISP_COMMAND   "/user05/fujio/gcl/gcl-2.2.1/unixport/saved_gcl /user05/fujio/gcl/gcl-2.2.1/unixport/ >/dev/null" */  /* i11.ima.umn.edu */
/* #define LISP_COMMAND   "/oimo/gcl/gcl-2.2.2/unixport/saved_gcl /oimo/gcl/gcl-2.2.2/unixport/  >/dev/null"*/  /* globus */
/* #define LISP_COMMAND   "/usr/people/sgi1_4/fujio/bin/saved_gcl /usr/people/sgi1_4/fujio/bin/  >/dev/null"*/  /* sgi3.ccrl-nece.technopark.gmd.de */
/* #define LISP_COMMAND   "/usr/local/lib/gcl-2.0/unixport/saved_gcl /usr/local/lib/gcl-2.0/unixport/ >/dev/null" */ /* FreeBSD */
/* #define LISP_COMMAND   "/usr/local/lib/kcl/saved_kcl /usr/local/lib/kcl/ >/dev/null" */  /* For EWS4800/csle11 */
/* #define LISP_COMMAND   "/usr/local/lib/kcl/saved_kcl /usr/local/lib/kcl/ >/dev/null " */  /* For EWS4800/csle11 */
/*  #define LISP_COMMAND      "/usr1/chobi/Alpha/kcl/unixport/saved_kcl /usr1/chobi/Alpha/kcl/unixport/ >/dev/null" */

#define LISP_OUT_FILE     "lisp_out.l"
#define EST_DAT_FILE      "est%d-%d-%d.dat"  /* 要素積分データファイル */

/*-------------------------------------------------------------
  LISPプログラムの格納ディレクトリ
  -------------------------------------------------------------*/
#define LISP_LIB_DIR      "/usr/feel/feel_p2/src/lisp"
#define LISP_EXE_DIR      "/usr/feel/feel_p2/src/lisp_exec"

/*-------------------------------------------------------------
  関数名のfeel/fort77での実現方法
  -------------------------------------------------------------*/
#define SOLVE_NAME77_A        "solve0%d"     /* solve番号 1-9 */
#define SOLVE_NAME77_B        "solve%d"      /* solve番号 10- */



/*-------------------------------------------------------------
  変数名のfeel/fort77での実現方法
  -------------------------------------------------------------*/

#define FEM_VAR_NAME77      "fem_%s"
#define EWISE_VAR_NAME77    "ew_%s"
#define SCALAR_VAR_NAME77   "sc_%s"

#define NP_FEM_VAR          "npf_%s"
#define NP_EWISE_VAR        "npe_%s"

/* 数値積分法関係 */


#define X_IN_QUAD  "qx"        /* 数値積分に現れる空間変数 x */
#define Y_IN_QUAD  "qy"        /* 数値積分に現れる空間変数 y */
#define Z_IN_QUAD  "qz"        /* 数値積分に現れる空間変数 z */

  
#define GX_NAME77  "gx_%d"     /* 数値積分点用 (積分番号) */
#define GY_NAME77  "gy_%d"     /* 数値積分点用 (積分番号) */
#define GZ_NAME77  "gz_%d"     /* 数値積分点用 (積分番号) */

#define QUAD_CONST_NAME77 "qc%d_%s"  /* 数値積分時のconst変数用 
					 (積分番号,変数名)       */
#define QUAD_DOUBLE_NAME77 "qd%d_%s" /* 数値積分時のconst変数用 
					 (積分番号,変数名)       */
#define WEIGHT_NAME77     "w%d"      /* 数値積分時の重み用 
					 (積分番号)              */

#define ELEMENT_DOUBLE_NAME77  "ed%d_%s"  /* 要素double変数のeset内の変数名
					   要素番号(eset内の局所的な番号)
					   変数名  
					   これは、同じ名前のdouble変数名
					   が複数の要素に現れる可能性の為 */

					   
#define ELEMENT_CONST_NAME77   "ec%d_%s"
/*-------------------------------------------------------------
  表示用X-Windowの規格
  -------------------------------------------------------------*/
#define MAX_X_WINDOWS            10  /* 開ける最大のX-window数 */
#define DEFAULT_WINDOW_SIZE   600

/*-------------------------------------------------------------
  行番号の規約
  -------------------------------------------------------------*/
#define LINENO_FOR_LOOP       100  /* DOループ用  */
#define LINENO_FOR_L0OP_END  6999 
#define LINENO_FOR_LOOP_STEP   10

#define LINENO_FOR_GOTO      8000  /* GOTO文用    */
#define LINENO_FOR_GOTO_END  8899
#define LINENO_FOR_GOTO_STEP   10

#define LINENO_FOR_ERR       8900  /* error分岐用 */
#define LINENO_FOR_ERR_END   8999
#define LINENO_FOR_ERR_STEP     5

#define LINENO_FOR_IO        9000  /* 入出力用    */
#define LINENO_FOR_IO_END    9999
#define LINENO_FOR_IO_STEP      5

/*-----------------------------------------------------------------
   Excecution error Number for imode  (it must be negative integer)
  -----------------------------------------------------------------*/
#define ERROR_IMODE_NONLINEAR_DIVERGENT    -1


/*-------------------------------------------------------------
   Extern宣言された変数  エラーフラグ類
  -------------------------------------------------------------*/
extern int  status_lisp_debug;
extern int  status_no_delete;
extern char *lisp_debug_fp;
extern int  mesh_only;
extern int  english_mesg;
extern int  web_mode;
extern int  bamg_mode;            /* mesh generation for BANG  97/06/02 */
extern int  subdomain_flag;
extern int  skyline_flag;
extern int  avs_mode;             /* avs mode for AVS/Express  98/09/03 */
extern int  avs_64bit;            /* avs 64 bit mode for sg6   99/04/21 */
extern int  avs_mesh_ref;         /* for Tri/Quad reference in avsoutput*/
extern int  modulef_mode;         /* Prototype 3 Modulef MODE */
extern int  mf_module_mode;   
extern char *pde_src_name;        /* PDE source file name (the first one) */
/*--------------------------------------------------*/
/* [Extern variable,functions]                      */
/*--------------------------------------------------*/

/*  変数名チェック関係(var_comp/var_init.cにて定義される */
extern char *feel_key_word[];
extern char *feel_fem_func[];
extern char *fort77_func[];
extern char  fort77_mark[];

extern char *get_const_value();

/*  feelユーザ関係情報  main/feel_exec_main.c にて定義・初期化される */
extern char *feel_user;
extern char *feel_date;
extern char *feel_time;

/*  システム変数 */
extern int   MACHINE;     /* yacc/YaccMain.cにて宣言、定義 (feelより受け渡し)*/
extern int   LIMIT_FILE;  /* yacc/YaccMain.cにて宣言、定義 (feelより受け渡し)*/


/* 文字列強調の為 */
#ifdef MSDOS

#define STRESS  
#define NORMAL  

#else

#define STRESS  if(!web_mode)fprintf(stderr,"%c[5m",27)
#define NORMAL  if(!web_mode)fprintf(stderr,"%c[0m",27)
#endif

/* コードを文字列に逆変換する関数群[system/reverse_code_convert.c] */
extern char *etype_no_to_name();


/* 構造体の画面イメージを返す関数群[system/show_basic_struct.c] */
extern char *frac_image();


/* LISPプログラムを作成する為のサービスプログラム
   bufferに書き込みアドレスを更新                  */
extern char *make_list_st();

/* comp_var関係extern宣言 */
extern char *get_elem_name_by_ND(); /* 変数名、領域名から基底関数名を引く */

/* その他 */
extern double myatof();  /* わしが作ったatof */
extern double   *gauss_weight();  /* 1〜7点までのガウス積分点重みを返す */
extern double   *gauss_point();   /* 1〜7点までのガウス積分点座標を返す */
