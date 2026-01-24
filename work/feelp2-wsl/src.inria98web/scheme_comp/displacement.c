/*
 *   feel  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   displacement.c
 *      Date:   1994/11/11
 *   
 *   Purpose:   displacement文の構文解析受け皿
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

void Displacement_st() 
{
    char    *u_var,*v_var;
    Displacement *displacement_struct;

    UseLibrary( DISPLACEMENT ,NULL);

    v_var = PopString();
    u_var = PopString();


    displacement_struct =(Displacement *)FEEL_GetMemory( sizeof(Displacement));

    displacement_struct -> u_var  = u_var;
    displacement_struct -> v_var  = v_var;
    displacement_struct -> p_var  = NULL;   /* 標準ではメッシュのみ */
    displacement_struct -> fact   = 100.0;

    displacement_struct -> yylineno  = yylineno_info();
    displacement_struct -> window_id = get_new_window_id();

    /* DEFAULT値の設定 */
    displacement_struct -> IFLG   = 2;    /* UMAX,UMINを自動設定 */
    displacement_struct -> winsiz = DEFAULT_WINDOW_SIZE;  /* window size  */
    displacement_struct -> xmin   = 0.0;  /* 自動設定する */
    displacement_struct -> xmax   = 0.0;
    displacement_struct -> ymin   = 0.0;
    displacement_struct -> ymax   = 0.0;
    displacement_struct -> umin    = 0.0;  
    displacement_struct -> umax    = 0.0;
    displacement_struct -> LOG_flag = 0;  /*(ITYP) normal 0 / LOG scale 1  */
    displacement_struct -> mesh_flag = 0; /*(IMSH, メッシュを描く 1/ ない 0) */
    displacement_struct -> divide    = 20; /*(IDIV 分割数) */
    displacement_struct -> paint_flag = 0; /*(IOUT 塗り潰し 0 / 線のみ 1 )   */
    displacement_struct -> scale_flag = 0; /*(ISCL スケール入り 1/ なし 0)   */
    displacement_struct -> gray_flag  = 0; /*(GRAY スケール     0/1=on)      */
    displacement_struct -> mesg  = NULL;
    displacement_struct -> subdomain  = NULL;
       
    store_scheme( DISPLACEMENT , displacement_struct);

    return;
}


void Displacement_st_with_setting(settings) 
     int settings;
{
    int i;
    char    *u_var,*v_var;
    Displacement *displacement_struct;
    char   **cptr;

    char    *key;
    char    *num;

    int    winsiz;
    double xmin,xmax,ymin,ymax;
    double umin,umax;
    int LOG_flag,MESH_flag,divide,paint_flag,line_flag,scale_flag;

    int urange_flag;
    int xyrange_flag;

    int xmin_flag,ymin_flag,xmax_flag,ymax_flag;
    int umin_flag,umax_flag;

    urange_flag = xyrange_flag = NO;
    xmin_flag = ymin_flag = xmax_flag = ymax_flag = NO;
    umin_flag = umax_flag = NO;

    UseLibrary( DISPLACEMENT ,NULL);

    displacement_struct = (Displacement *)FEEL_GetMemory( sizeof(Displacement) );

    displacement_struct -> window_id = get_new_window_id();

    /* DEFAULT値の設定 */
    displacement_struct -> p_var  = NULL;
    displacement_struct -> fact = 100.0;


    displacement_struct -> IFLG   = 2;    /* UMAX,UMINを自動設定 */
    displacement_struct -> winsiz = DEFAULT_WINDOW_SIZE;  /* window size  */
    displacement_struct -> xmin   = 0.0;  /* 自動設定する */
    displacement_struct -> xmax   = 0.0;
    displacement_struct -> ymin   = 0.0;
    displacement_struct -> ymax   = 0.0;
    displacement_struct -> umin    = 0.0;  
    displacement_struct -> umax    = 0.0;
    displacement_struct -> LOG_flag = 0;  /* (ITYP) normal 0 / LOG scale 1  */
    displacement_struct -> mesh_flag = 1; /* (IMSH, メッシュを描く 1/ ない 0) */
    displacement_struct -> divide    = 20; /* (IDIV 分割数) */
    displacement_struct -> paint_flag = 0; /* (IOUT 塗り潰し 0 / 線のみ 1 )   */
    displacement_struct -> scale_flag = 0; /* (ISCL スケール入り 1/ なし 0)   */
    displacement_struct -> gray_flag  = 0; /* (GRAY スケール ) */
    displacement_struct -> mesg = NULL;
    displacement_struct -> subdomain = NULL;

    for(i=0;i<settings;i++) {
	num = PopString();
	key = PopString();

	if(streq(key,"winsiz")) {
	    winsiz = atoi(num);
	    if(winsiz <= 0 || winsiz > 2000) {
		SystemWarning_yy("displacement文での画面サイズ不正",yylineno_info());
	    }
	    displacement_struct -> winsiz = winsiz;
	    continue;		
	}

	if(streq(key,"fact")) {
	    displacement_struct->fact = myatof(num);
	    continue;
	}

	if(streq(key,"mesg")) {
	    displacement_struct->mesg = num;
	    continue;
	}

	if(streq(key,"subdomain")) {
	    displacement_struct->subdomain = num;
	    continue;
	}


	if(streq(key,"umax")) {
	    umax_flag = YES;
	    umax      = myatof(num);
	    continue;
	}

	if(streq(key,"umin")) {
	    umin_flag = YES;
	    umin      = myatof(num);
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

	if(streq(key,"ymax")) {
	    ymax_flag = YES;
	    ymax      = myatof(num);
	    continue;
	}

	if(streq(key,"paint")) {
	    if(streq(num,"on")) {
		displacement_struct->paint_flag = 0; /* 塗り潰し */
		continue;
	    }
	    if(streq(num,"off")) {
		displacement_struct->paint_flag = 1; /* 線だけ */
		continue;
	    }
	    SystemError_yy("displacement文キーワードpaintにはon/offを指定",
			 yylineno_info());
	    continue;
	}


	if(streq(key,"gray")) {
	    if(streq(num,"on")) {
		displacement_struct->gray_flag = 1; /* Gray スケールON */
		continue;
	    }
	    if(streq(num,"off")) {
		displacement_struct->gray_flag = 0; /* 線だけ */
		continue;
	    }
	    SystemError_yy("displacement文キーワードgrayにはon/offを指定",
			 yylineno_info());
	    continue;
	}

	if(streq(key,"mesh")) {
	    if(streq(num,"on")) {
		displacement_struct->mesh_flag = 1; /* メッシュを描く */
		continue;
	    }
	    if(streq(num,"off")) {
		displacement_struct->mesh_flag = 0; /* メッシュを描かない */
		continue;
	    }
	    SystemError_yy("displacement文キーワードmeshにはon/offを指定",
			 yylineno_info());
	    continue;
	}


	if(streq(key,"val")) {
	    displacement_struct -> p_var  =  MakeStringCopy(num);
	    continue;
	}
	SystemError_yy_s("displacement文詳細指定キーワード%sはだめ",key,
			 yylineno_info());

    }
    v_var = PopString();
    u_var = PopString();

    /* 指定の検査 */
    urange_flag = umin_flag + umax_flag;
    xyrange_flag = xmin_flag + ymin_flag + xmax_flag + ymax_flag;
    if(xyrange_flag != NO) { 
	if( ymax <= ymin || xmax <= xmin) {
	    SystemError_yy("displacement表示領域指定に誤りがある",yylineno_info());
	}
    }
    if(urange_flag != NO) {
	if( umax <= umin ) {
	    SystemError_yy("displacement値範囲指定に誤りがある",yylineno_info());
	}
    }

    if(urange_flag != 0 && urange_flag != 2) {
	SystemError_yy("displacement値範囲指定に過不足がある",yylineno_info());
    }
    if(urange_flag == 2 && umin_flag * umax_flag != YES * YES) {
	SystemError_yy("displacement値範囲指定に過不足がある",yylineno_info());
    }	

    if(xyrange_flag != 0 && xyrange_flag != 4) {
	SystemError_yy("displacement表示範囲指定に過不足がある",yylineno_info());
    }
    if(xyrange_flag == 4 && xmin_flag * xmax_flag *
                          ymin_flag * ymax_flag != YES * YES * YES * YES) {
	SystemError_yy("displacement表示範囲指定に過不足がある",yylineno_info());
    }	

    if(urange_flag != NO) {
	displacement_struct -> IFLG = 3;  /* 全てマニュアル指定 */
	displacement_struct -> umin = umin;
	displacement_struct -> umax = umax;
    }
    if(xyrange_flag != NO) {
	displacement_struct -> ymin = ymin;
	displacement_struct -> xmin = xmin;
	displacement_struct -> ymax = ymax;
	displacement_struct -> xmax = xmax;
    }


    /*  10の位は値指定、1の位は表示範囲指定 */
    displacement_struct-> set_flag = 10 * umin_flag + xmin_flag;

    displacement_struct -> u_var  = u_var;
    displacement_struct -> v_var  = v_var;

    displacement_struct -> yylineno  = yylineno_info();

    store_scheme( DISPLACEMENT , displacement_struct);

    return;

}
