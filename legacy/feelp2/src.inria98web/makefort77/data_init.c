/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *  data initialize
 */

#include "MainProgram.h"
#include "../feel_def/feel_def.h"

MainProgram  main_dat;
Variables    vars_dat;

extern char *feel_user;
extern char *feel_date;




void data_initialize() 
{
    get_user_info();      /* feel_user,feel_dateの設定 */

    /* feel_def.h で定義された定数値を変数に代入 */
    main_dat.prog_name   = PROG_FEEL_MAIN;     
    main_dat.max_domain  = MAX_DOMAIN;
    main_dat.max_edatset = MAX_EDATSET;
    main_dat.max_nodeset = MAX_NODESET;
    main_dat.max_numset  = MAX_NUMSET;
    main_dat.max_ewise   = MAX_EWISE;
    main_dat.max_ewise_info = MAX_EWISE_INFO;

    return;
}

void system_default()          /* システムのdefault値の設定 */
{
    main_dat.max_feel_size = get_feel_array_size();

    /* 空間次元の決定 */
    main_dat.ndim = what_dimension();

    return;
}



