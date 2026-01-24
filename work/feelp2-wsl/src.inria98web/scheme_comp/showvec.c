/*
 *   feel  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   showvec.c
 *      Date:   1993/12/15
 *   
 *   Purpose:   showvec文の構文解析受け皿
 *   Functions: 
 *              
 *              
 */

#include <stdlib.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "scheme_comp.h"

void Showvec_st() 
{
    char    *var;
    Showvec *showvec_struct;

    UseLibrary( SHOWVEC ,NULL);


    showvec_struct = (Showvec *)FEEL_GetMemory( sizeof(Showvec) );

    showvec_struct -> y  = PopString();
    showvec_struct -> x  = PopString();
    showvec_struct -> window_id = get_new_window_id();

    showvec_struct -> yylineno  = yylineno_info();

    /* DEFAULT値の設定 */
    showvec_struct -> winsiz = DEFAULT_WINDOW_SIZE;      /* window size  */
    showvec_struct -> IFLG   =   2;  /* VMAXを自動設定するのがデフォルト */
    showvec_struct -> USE_EDATRANGE_flag = YES;
    showvec_struct -> mono_flag = NO;
    showvec_struct -> xmin   = 0.0;  /* 自動設定する(EDATRANGEで) */
    showvec_struct -> xmax   = 0.0;
    showvec_struct -> ymin   = 0.0;
    showvec_struct -> ymax   = 0.0;
    showvec_struct -> vmax   = 0.0;  /* 自動設定する */
    showvec_struct -> mesh_flag =  1; /* (IMSH, メッシュを描く 1/ ない 0) */
    showvec_struct -> vm     = 1.0;   /* ベクトルの倍率 */
    showvec_struct -> gray_flag =  0; /* 0 = color  1 = gray scale */
    showvec_struct -> ITYPE  = 1;
    showvec_struct -> mesg   = NULL;
    showvec_struct -> subdomain = NULL;

    store_scheme( SHOWVEC , showvec_struct);
    
    return;

}


void Showvec_st_with_setting(settings) 
     int settings;
{
    int i;
    char    *var;
    Showvec *showvec_struct;
    char   **cptr;

    char    *key;
    char    *num;

    int    winsiz;

    int xyrange_flag;
    int vmax_flag   ;
    int xmin_flag,ymin_flag,xmax_flag,ymax_flag;
    double xmin,xmax,ymin,ymax;
    double vmax;


    xyrange_flag = NO;
    vmax_flag    = NO;

    xmin_flag = ymin_flag = xmax_flag = ymax_flag = NO;

    UseLibrary( SHOWVEC ,NULL);

    showvec_struct = (Showvec *)FEEL_GetMemory( sizeof(Showvec) );

    showvec_struct -> window_id = get_new_window_id();

    /* DEFAULT値の設定 */
    showvec_struct -> winsiz = DEFAULT_WINDOW_SIZE;  /* window size  */
    showvec_struct -> IFLG   =   2;  /* VMAXは自動設定する */
    showvec_struct -> USE_EDATRANGE_flag = YES;
    showvec_struct -> mono_flag = NO;

    showvec_struct -> xmin   = 0.0;  /* edatrangeで自動設定する */
    showvec_struct -> xmax   = 0.0;
    showvec_struct -> ymin   = 0.0;
    showvec_struct -> ymax   = 0.0;
    showvec_struct -> mesh_flag =  1; /* (IMSH, メッシュを描く 1/ ない 0) */
    showvec_struct -> vm     = 1.0;   /* ベクトルの倍率 */
    showvec_struct -> vmax   = 0.0;
    showvec_struct -> gray_flag =  0;
    showvec_struct -> ITYPE  = 1;
    showvec_struct -> mesg   = NULL;
    showvec_struct -> subdomain = NULL;

    for(i=0;i<settings;i++) {
	num = PopString();
	key = PopString();

	if(streq(key,"winsiz")) {
	    winsiz = atoi(num);
	    if(winsiz <= 0 || winsiz > 2000) {
		SystemWarning_yy("showvec文での画面サイズ不正",yylineno_info());
	    }
	    showvec_struct -> winsiz = winsiz;
	    continue;		
	}

	if(streq(key,"xmin")) {
	    xmin_flag = YES;
	    xmin      = myatof(num);
	    continue;
	}

	if(streq(key,"ymin")) {
	    ymin_flag = YES;
	    ymin      = myatof(num);
	    continue;
	}

	if(streq(key,"xmax")) {
	    xmax_flag = YES;
	    xmax      = myatof(num);
	    continue;
	}

	if(streq(key,"mesg")) {
	    showvec_struct -> mesg = num;
	    continue;
	}

	if(streq(key,"subdomain")) {
	    showvec_struct -> subdomain = num;
	    continue;
	}

	if(streq(key,"ymax")) {
	    ymax_flag = YES;
	    ymax      = myatof(num);
	    continue;
	}

	if(streq(key,"vmax")) {
	    vmax_flag = YES;
	    vmax      = myatof(num);
	    continue;
	}


	if(streq(key,"factor")) {
	    showvec_struct -> vm  = myatof(num);
	    if(showvec_struct -> vm  == 0.0) {
		SystemError_yy("showvecのfactorに0を指定",yylineno_info());
	    }
	    continue;
	}

	if(streq(key,"mesh")) {
	    if(streq(num,"on")) {
		showvec_struct->mesh_flag = 1; /* メッシュを描く */
		continue;
	    }
	    if(streq(num,"off")) {
		showvec_struct->mesh_flag = 0; /* メッシュを描かない */
		continue;
	    }
	    SystemError_yy("showvec文キーワードmeshにはon/offを指定",
			 yylineno_info());
	    continue;
	}


	if(streq(key,"mono")) {
	    if(streq(num,"on")) {
		showvec_struct->mono_flag = 1; /* 白黒 */
		continue;
	    }
	    if(streq(num,"off")) {
		showvec_struct->mono_flag = 0; /* カラー */
		continue;
	    }
	    SystemError_yy("showvec文キーワードmonoにはon/offを指定",
			 yylineno_info());
	    continue;
	}

	if(streq(key,"gray")) {
	    if(streq(num,"on")) {
		showvec_struct->gray_flag = 1; /* gray scale on */
		continue;
	    }
	    if(streq(num,"off")) {
		showvec_struct->gray_flag = 0; /* メッシュを描かない */
		continue;
	    }
	    SystemError_yy("showvec文キーワードmeshにはon/offを指定",
			 yylineno_info());
	    continue;
	}

	SystemError_yy_s("showvec文詳細キーワード%sは未定義",key,yylineno_info());
	


    }

    xyrange_flag = xmin_flag + ymin_flag + xmax_flag + ymax_flag;
    if(xyrange_flag != NO) { 
	if( ymax <= ymin || xmax <= xmin) {
	    SystemError_yy("showvec表示領域指定に誤りがある",yylineno_info());
	}
    }
    if(xyrange_flag != 0 && xyrange_flag != 4) {
	SystemError_yy("showvec表示範囲指定に過不足がある",yylineno_info());
    }
    if(xyrange_flag == 4 && xmin_flag * xmax_flag *
                          ymin_flag * ymax_flag != YES * YES * YES * YES) {
	SystemError_yy("showvec表示範囲指定に過不足がある",yylineno_info());
    }	

    if(xyrange_flag != NO) {

	if(vmax_flag == YES) {

	showvec_struct -> IFLG =    3;  /* edatrangeではなく、構造体を使用 */
	showvec_struct -> USE_EDATRANGE_flag = NO;
	showvec_struct -> ymin = ymin;
	showvec_struct -> xmin = xmin;
	showvec_struct -> ymax = ymax;
	showvec_struct -> xmax = xmax;
	showvec_struct -> vmax = vmax;
        }
	else {
	showvec_struct -> IFLG =    2;  /* edatrangeではなく、構造体を使用 */
	showvec_struct -> USE_EDATRANGE_flag = NO;
	showvec_struct -> ymin = ymin;
	showvec_struct -> xmin = xmin;
	showvec_struct -> ymax = ymax;
	showvec_struct -> xmax = xmax;
        }
    }
    else {
	if(vmax_flag == YES) {           /* xmin等はEDATRANGEで設定 */
	    showvec_struct -> IFLG = 3;
	    showvec_struct -> vmax = vmax;
	}
    }


    showvec_struct -> y  = PopString();
    showvec_struct -> x  = PopString();

    showvec_struct -> yylineno  = yylineno_info();

    store_scheme( SHOWVEC , showvec_struct);

    return;

}
