/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *  関数名、サブルーチン名、プログラムファイル名、データファイル名
 *  モード番号
 */

/* feel fort77 の制限定義 */

#define FEEL_ARRAY_SIZE  40000



/* モード定義 */

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

/* 関数名、ファイル名定義 */

#define INPUT_FILE      "feel_dat"
#define OUTPUT_FILE     "feel_out"

#define FEEL_MAIN       "feel_main.f"  /* メインプログラムのファイル名   */
#define PROG_FEEL_MAIN  "feel_main"    /* メインプログラムのモジュール名 */

#define FILSET          "filset.f"     /* ファイル装置番号設定プログラムファイル名 */
#define PROG_FILSET     "filset"       /* モジュール名 */


#define DATINP_MAIN       "datinp.f"   /* データ入力プログラム メインルーチン */
#define PROG_DATINP_MAIN  "datinp"  

#define INP_NODE          "dat_node.f" /* 節点データ入力プログラム            */
#define PROG_INP_NODE     "dat_node"
#define KEY_NODE          "'NODE'"     /* 節点データキーワード */


#define INP_ELEM          "dat_elem.f" /* 要素データ入力プログラム            */
#define PROG_INP_ELEM     "dat_elem" 
#define KEY_ELEM          "'ELEM'"

#define INP_NSET          "dat_nodeset.f" /* 節点集合データ入力プログラム     */
#define PROG_INP_NSET     "dat_nodeset"
#define KEY_NSET          "'NSET'"

#define INP_COMT_COMT     "dat_comment.f" /* コメント印字プログラム */
#define PROG_INP_COMT     "dat_comment"
#define KEY_COMT          "'COMT'"

#define INP_NUM           "dat_num.f"  /* 関数値データ入力プログラム          */
#define PROG_INP_NUM      "dat_num"  
#define KEY_NUM           "'NUM '"

#define KEY_END           "'END '"     /* 入力ファイルの終了キーワード */

