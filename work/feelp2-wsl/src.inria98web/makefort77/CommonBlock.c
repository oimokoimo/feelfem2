/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *  common block definition
 */

#include <stdio.h>

#include "../system/system.h"
#include "../parallel/parallel.h"

void CommonBlock( fp )
     FILE *fp;
{
/*
 *   COMMON ブロックの説明  
 *
 *   C 中で、CommonBlock(fp);  でCOMMONブロックを生成
 *
 *   名前なしcommon block      配列feel用
 *
 *   [feel_geo]  ndim        空間次元
 *               npmax       総節点数
 *  領域に関する nelemg      要素グループの数
 *  COMMON       nodeset     節点集合の数(ディリクレ条件等に用いる)
 *               numset      数値データ集合の数(節点集合とペア)
 *           
 *   [feel_ctl]  mode_ex     解析モード(1 入力データcheckのみ、2 解析実行)
 *               mode_output 出力モード(これは未定だけど、出力量の抑制を行う)
 *               idble_word  倍精度と単精度とのワード差
 *               max_heap    feel変数の最大使用値
 *           
 *   [feel_var]  nvars_fem   fem変数の総数
 *               nvars_ewise ewise変数の総数
 *               np_fem      feel変数中、fem変数の開始位置     
 *               np_ewise    feel変数中、ewise変数の開始位置     
 *               np_heap     feel変数の配列の大きさ(np_heap = MAX_FEEL と設定)
 *         
 *   [feel_fil]  io_in       データファイルのユニット番号
 *               io_tmp      臨時出力データファイル番号
 *               io_out      出力データファイル番号
 *               io_elem     要素データの基準ファイルユニット番号
 *               io_node     節点値データの基準ファイルユニット番号
 *               io_num      数値データの基準ファイルユニット番号
 *               io_stderr   標準エラー出力のファイルユニット番号        
 * 
 * [feel_dat]  n_domain(*) 各domainの要素数
 *             n_edat(*,3) 各要素集合の要素数，要素内節点数,domain番号はやめ
 *             n_nset(*,2) 各節点集合データの節点数,データ配列数
 *             n_num(*)    各数値データに対応する節点集合データ番号
 *             n_ewise(*,1)  各ewise変数に関連するedatの番号
 *             n_ewise(*,2)  各ewise変数の要素当りの節点数
 *             ※ewiseは、Ewise_type毎に、FORTRANプログラムに反映する
 *
 *
 * [feel_sol]  n_sstat(*)  各solve文の配列情報を作るかセーブされている
 *                         ものを読み込むかの制御配列
 *                           = 0 の時  全てを作り直し
 *                           = 1 スカイライン情報配列、累積節点以外作り直し
 *                           = 3 LU分解済み(線形問題など)
 *           
 *             n_smaxp(*)  並列計算時、各solve文の情報配列の最大値
 *           
 *
 *
 * [feel_para] npe         プロセッサ数
 *             p_rank      自分のプロセッサ番号
 *             
 *
 */

    /* 並列処理用 */
    if(parallel != 0)  {
	comment1(fp);
	fprintf(fp,"      integer p_rank\n");
    }


    comment1(fp);

    fprintf(fp,"      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip\n");
    fprintf(fp,"      common /feel_ctl/mode_ex,mode_output,max_heap\n");
    fprintf(fp,"      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,\n");
    fprintf(fp,"     &                 np_fem,np_ewise,np_heap\n");
    fprintf(fp,"      common /feel_fil/io_in,io_tmp,io_out,io_stderr,\n");
    fprintf(fp,"     &                 io_edat,io_node,io_num,io_fem\n");
    fprintf(fp,"      common /feel_dat/n_edat(MAX_EDATSET,3),\n");
    fprintf(fp,"     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),\n");
    fprintf(fp,"     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)\n");
    fprintf(fp,"      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)\n");

    if(parallel != 0) {
	fprintf(fp,"      common /feel_para/npe,p_rank,ncont1,ncont2\n");
    }
    return;
}
