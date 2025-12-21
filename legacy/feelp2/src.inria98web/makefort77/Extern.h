/*
 * feel prototype version 2
 * 
 * extern variables
 *
 */

#include "../makefort77/MainProgram.h"

extern MainProgram   main_dat;  /* メイン関数に関するストラクチャ */
extern Variables     vars_dat;  /* 変数に関するstructure   */


/* feelユーザに関する情報、data_initで初期化する */
extern char *feel_user;         /* ユーザ名 used in get_user_info.c */
extern char *feel_date;         /* 生成時間 used in get_user_info.c */

