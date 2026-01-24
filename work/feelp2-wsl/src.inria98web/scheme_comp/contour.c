/*
 *   feel  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   contour.c
 *      Date:   1993/12/15
 *   
 *   Purpose:   contour文の構文解析受け皿
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

void Contour_st() 
{
    char    *var;
    Contour *contour_struct;

    UseLibrary( CONTOUR ,NULL);

    var = PopString();

    contour_struct = (Contour *)FEEL_GetMemory( sizeof(Contour) );

    contour_struct -> var  = var;

    contour_struct -> yylineno  = yylineno_info();
    contour_struct -> window_id = get_new_window_id();

    /* DEFAULT値の設定 */
    contour_struct -> IFLG   = 2;    /* UMAX,UMINを自動設定 */
    contour_struct -> winsiz = DEFAULT_WINDOW_SIZE;  /* window size  */
    contour_struct -> xmin   = 0.0;  /* 自動設定する */
    contour_struct -> xmax   = 0.0;
    contour_struct -> ymin   = 0.0;
    contour_struct -> ymax   = 0.0;
    contour_struct -> umin    = 0.0;  
    contour_struct -> umax    = 0.0;
    contour_struct -> LOG_flag = 0;  /* (ITYP) normal 0 / LOG scale 1  */
    contour_struct -> mesh_flag = 1; /* (IMSH, メッシュを描く 1/ ない 0) */
    contour_struct -> divide    = 20; /* (IDIV 分割数) */
    contour_struct -> paint_flag = 0; /* (IOUT 塗り潰し 0 / 線のみ 1 )   */
    contour_struct -> scale_flag = 0; /* (ISCL スケール入り 1/ なし 0)   */
    contour_struct -> gray_flag  = 0; /* (GRAY スケール     0/1=on)      */
    contour_struct -> mesg = NULL;
    contour_struct -> subdomain = NULL;


    store_scheme( CONTOUR , contour_struct);

    return;

}


void Contour_st_with_setting(settings) 
     int settings;
{
    int i;
    char    *var;
    Contour *contour_struct;
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

    UseLibrary( CONTOUR ,NULL);

    contour_struct = (Contour *)FEEL_GetMemory( sizeof(Contour) );

    contour_struct -> window_id = get_new_window_id();

    /* DEFAULT値の設定 */
    contour_struct -> IFLG   = 2;    /* UMAX,UMINを自動設定 */

    contour_struct -> winsiz = DEFAULT_WINDOW_SIZE;  /* window size  */
    contour_struct -> xmin   = 0.0;  /* 自動設定する */
    contour_struct -> xmax   = 0.0;
    contour_struct -> ymin   = 0.0;
    contour_struct -> ymax   = 0.0;
    contour_struct -> umin    = 0.0;  
    contour_struct -> umax    = 0.0;
    contour_struct -> LOG_flag = 0;  /* (ITYP) normal 0 / LOG scale 1  */
    contour_struct -> mesh_flag = 1; /* (IMSH, メッシュを描く 1/ ない 0) */
    contour_struct -> divide    = 20; /* (IDIV 分割数) */
    contour_struct -> paint_flag = 0; /* (IOUT 塗り潰し 0 / 線のみ 1 )   */
    contour_struct -> scale_flag = 0; /* (ISCL スケール入り 1/ なし 0)   */
    contour_struct -> gray_flag  = 0; /* (GRAY スケール ) */
    contour_struct -> mesg       = NULL;
    contour_struct -> subdomain  = NULL;

    for(i=0;i<settings;i++) {
	num = PopString();
	key = PopString();

	if(streq(key,"winsiz")) {
	    winsiz = atoi(num);
	    if(winsiz <= 0 || winsiz > 2000) {
		SystemWarning_yy("Illegal Windowsize in contour",
				 yylineno_info());
	    }
	    contour_struct -> winsiz = winsiz;
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
		contour_struct->paint_flag = 0; /* 塗り潰し */
		continue;
	    }
	    if(streq(num,"off")) {
		contour_struct->paint_flag = 1; /* 線だけ */
		continue;
	    }
	    if(english_mesg) {
		SystemError_yy("paint option must be on or off",
			       yylineno_info());
	    }
	    else {
		SystemError_yy("contour文キーワードpaintにはon/offを指定",
			       yylineno_info());
	    }
	    continue;
	}


	if(streq(key,"gray")) {
	    if(streq(num,"on")) {
		contour_struct->gray_flag = 1; /* Gray スケールON */
		continue;
	    }
	    if(streq(num,"off")) {
		contour_struct->gray_flag = 0; /* 線だけ */
		continue;
	    }
	    if(english_mesg) {
		SystemError_yy("contour keyword for gray must be on or off",
			       yylineno_info());
	    }
	    else {
		SystemError_yy("contour文キーワードgrayにはon/offを指定",
			       yylineno_info());
	    }
	    continue;
	}

	if(streq(key,"mesh")) {
	    if(streq(num,"on")) {
		contour_struct->mesh_flag = 1; /* メッシュを描く */
		continue;
	    }
	    if(streq(num,"off")) {
		contour_struct->mesh_flag = 0; /* メッシュを描かない */
		continue;
	    }
	    SystemError_yy("contour option for mesh must be on or off",
			 yylineno_info());
	    continue;
	}

	if(streq(key,"mesg")) {
	    contour_struct->mesg = num;
	    continue;
	}
	
	if(streq(key,"subdomain")) {
	    contour_struct->subdomain = num;
	    continue;
	}

	if(streq(key,"mono")) {
	    if(streq(num,"on")) {
		contour_struct->paint_flag = 2; /* 白黒 */
		continue;
	    }
	    if(streq(num,"off")) {
		/* do nothing */
		continue;
	    }
	    SystemError_yy("contour option for mono must be on or off.",
			 yylineno_info());
	    continue;
	}
	SystemError_yy_s("Invalid option %s for contour",key,
			 yylineno_info());

    }
    var = PopString();

    /* 指定の検査 */
    urange_flag = umin_flag + umax_flag;
    xyrange_flag = xmin_flag + ymin_flag + xmax_flag + ymax_flag;
    if(xyrange_flag != NO) { 
	if( ymax <= ymin || xmax <= xmin) {
	    SystemError_yy("Illegal region specified for contour.",yylineno_info());
	}
    }
    if(urange_flag != NO) {
	if( umax <= umin ) {
	    SystemError_yy("Illegal value range specified in contour.",yylineno_info());
	}
    }

    if(urange_flag != 0 && urange_flag != 2) {
	SystemError_yy("contour値範囲指定に過不足がある",yylineno_info());
    }
    if(urange_flag == 2 && umin_flag * umax_flag != YES * YES) {
	SystemError_yy("contour値範囲指定に過不足がある",yylineno_info());
    }	

    if(xyrange_flag != 0 && xyrange_flag != 4) {
	SystemError_yy("contour表示範囲指定に過不足がある",yylineno_info());
    }
    if(xyrange_flag == 4 && xmin_flag * xmax_flag *
                          ymin_flag * ymax_flag != YES * YES * YES * YES) {
	SystemError_yy("contour表示範囲指定に過不足がある",yylineno_info());
    }	

    if(urange_flag != NO) {
	contour_struct -> IFLG = 3;  /* 全てマニュアル指定 */
	contour_struct -> umin = umin;
	contour_struct -> umax = umax;
    }

    if(xyrange_flag != NO) {
	contour_struct -> ymin = ymin;
	contour_struct -> xmin = xmin;
	contour_struct -> ymax = ymax;
	contour_struct -> xmax = xmax;
    }

    /*  10の位は値指定、1の位は表示範囲指定 */
    contour_struct-> set_flag = 10 * umin_flag + xmin_flag;

    contour_struct -> var  = var;

    contour_struct -> yylineno  = yylineno_info();

    store_scheme( CONTOUR , contour_struct);

    return;

}
