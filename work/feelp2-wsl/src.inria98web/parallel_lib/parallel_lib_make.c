/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   parallel_lib_make.c
 *      Date:   1995/09/20
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"
#include "../parallel/parallel.h"

parallel_lib_make()
{
    /* 並列計算プログラムの生成 */

    /* ライブラリ化 */
    return;


    /* メインルーチン上から呼ばれる並列処理サブルーチン群 */
    lib_p_close_file();   /* 並列処理関連のファイルを閉じる */

    

    /* mk_pdat.fから呼ばれる関数群(これは、dat.PE@@@.Xを読み込む為) */
    lib_p_calc_eqno();/* 部分領域毎の方程式番号の最大値を求める(旧eq_make)   */
    lib_p_make_eqno();/* 部分領域毎の方程式番号配列を作成する(旧data_neqcomp)*/
    lib_p_read_pedatA();/* PEデータを読み込む(主処理)        (旧data_da)     */
    lib_p_read_pedatB();/* PEデータを読み込む(節点番号集合)  (旧data_aiin)   */
    lib_p_read_pedatC();/* 送信/受信用の節点番号を読む       (旧se222+re222) */
    lib_p_read_rdat();  /* 受信用のデータ読み込みコントロール(旧read_re2)    */
    lib_p_read_sdat();  /* 送信用のデータ読み込みコントロール(旧read_se2)    */
    lib_p_make_sreq();  /* 送信/受信用の節点データを方程式番号データに変換   */
    lib_p_read_prdat(); /* 内積用節点データの読み込み                        */
    lib_p_read_d_nset();/* ディリクレ条件データ読み込みCoルーチン
			   p_read_ddat@@から呼ばれる                         */
    lib_p_read_ndat();  /* ノイマン条件読み込みルーチン(ライブラリ化した)    */
    lib_p_read_n_edat();/* ノイマン条件読み込みCoルーチン                    */


    lib_data_nodsub();  /* 各部分領域の座標値を読む  */



    /* solve文に関するライブラリ群 */
    lib_p_solve_pmset(); /* solve文からicons,ipdatのデータを設定する為に呼ぶ*/
    lib_p_make_srbuff(); /* SEND/RECV領域のバッファサイズの計算 */
    lib_p_memory_move(); /* ブロックデータの移動 */
    lib_p_set_MJ();      /* バンド幅の算出 */


    /* MPPSCGソルバー関連 */
    lib_p_solve_plset();   /* data_plusの呼び出しルーチン      */
    lib_data_plus();     /* プロセッサ間共有データの足し込み */
    lib_p_get_band();    /* 行列の格納の最適化               */

    lib_p_unsym_mscg();  /* ソルバー呼び出しルーチン */
    lib_p_msbicg_stab(); /* ソルバー本体 */

    return;
}

