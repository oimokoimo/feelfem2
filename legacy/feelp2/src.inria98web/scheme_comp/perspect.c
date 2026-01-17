/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   perspect.c
 *      Date:   1993/06/22 
 *   
 *   Purpose:   perspect文の構文解析
 *   Functions: 
 *              
 *              
 */


#include "../system/system.h"
#include "scheme_comp.h"

Perspect_st() 
{
    char    *var;
    Perspect *perspect_struct;

    var = PopString();
    UseLibrary( PERSPECT );

    perspect_struct = (Perspect *)FEEL_GetMemory( sizeof(Perspect) );

    perspect_struct -> var  = var;

    perspect_struct -> yylineno  = yylineno_info();
    perspect_struct -> window_id = get_new_window_id();


    /* DEFAULT値の設定 */
    perspect_struct -> IFLG   = 2;    /* UMAX,UMINを自動設定 */
    perspect_struct -> USE_EDATRANGE_flag = YES;
    perspect_struct -> winsiz = DEFAULT_WINDOW_SIZE;  /* window size  */
    perspect_struct -> xmin   = 0.0;  /* 自動設定する */
    perspect_struct -> xmax   = 0.0;
    perspect_struct -> ymin   = 0.0;
    perspect_struct -> ymax   = 0.0;
    perspect_struct -> umin    = 0.0;  
    perspect_struct -> umax    = 0.0;
    perspect_struct -> mesg    = NULL;
    perspect_struct -> subdomain    = NULL;
       

    store_scheme( PERSPECT , perspect_struct);

    return;

}


void Perspect_st_with_setting(settings) 
     int settings;
{
    int i;
    char    *var;
    Perspect *perspect_struct;
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

    UseLibrary( PERSPECT );

    perspect_struct = (Perspect *)FEEL_GetMemory( sizeof(Perspect) );

    perspect_struct -> window_id = get_new_window_id();

    /* DEFAULT値の設定 */
    perspect_struct -> IFLG   = 2;    /* UMAX,UMINを自動設定 */
    perspect_struct -> USE_EDATRANGE_flag = YES;

    perspect_struct -> winsiz = DEFAULT_WINDOW_SIZE;  /* window size  */
    perspect_struct -> xmin   = 0.0;  /* 自動設定する */
    perspect_struct -> xmax   = 0.0;
    perspect_struct -> ymin   = 0.0;
    perspect_struct -> ymax   = 0.0;
    perspect_struct -> umin    = 0.0;  
    perspect_struct -> umax    = 0.0;
    perspect_struct -> mesg   = NULL;
    perspect_struct -> subdomain   = NULL;

    for(i=0;i<settings;i++) {
	num = PopString();
	key = PopString();

	if(streq(key,"winsiz")) {
	    winsiz = atoi(num);
	    if(winsiz <= 0 || winsiz > 2000) {
		SystemWarning_yy("perspect文での画面サイズ不正");
	    }
	    perspect_struct -> winsiz = winsiz;
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

	if(streq(key,"mesg")) {
	    perspect_struct->mesg = num;
	    continue;
	}

	if(streq(key,"subdomain")) {
	    perspect_struct->subdomain = num;
	    continue;
	}

	SystemError_yy_s("perspect文詳細指定キーワード%sは未定義",key,
			 yylineno_info());

    }
    var = PopString();

    /* 指定の検査 */
    urange_flag = umin_flag + umax_flag;
    xyrange_flag = xmin_flag + ymin_flag + xmax_flag + ymax_flag;
    if(xyrange_flag != NO) { 
	if( ymax <= ymin || xmax <= xmin) {
	    SystemError_yy("perspect表示領域指定に誤りがある",yylineno_info());
	}
    }
    if(urange_flag != NO) {
	if( umax <= umin ) {
	    SystemError_yy("perspect値範囲指定に誤りがある",yylineno_info());
	}
    }

    if(urange_flag != 0 && urange_flag != 2) {
	SystemError_yy("perspect値範囲指定に過不足がある",yylineno_info());
    }
    if(urange_flag == 2 && umin_flag * umax_flag != YES * YES) {
	SystemError_yy("perspect値範囲指定に過不足がある",yylineno_info());
    }	

    if(xyrange_flag != 0 && xyrange_flag != 4) {
	SystemError_yy("perspect表示範囲指定に過不足がある",yylineno_info());
    }
    if(xyrange_flag == 4 && xmin_flag * xmax_flag *
                          ymin_flag * ymax_flag != YES * YES * YES * YES) {
	SystemError_yy("perspect表示範囲指定に過不足がある",yylineno_info());
    }	

    if(urange_flag != NO) {
	perspect_struct -> IFLG = 3;  /* 全てマニュアル指定 */
	perspect_struct -> umin = umin;
	perspect_struct -> umax = umax;
    }

    if(xyrange_flag != NO) {
	perspect_struct -> USE_EDATRANGE_flag = NO;
	perspect_struct -> ymin = ymin;
	perspect_struct -> xmin = xmin;
	perspect_struct -> ymax = ymax;
	perspect_struct -> xmax = xmax;
    }

    perspect_struct -> var  = var;
    perspect_struct -> yylineno  = yylineno_info();

    store_scheme( PERSPECT , perspect_struct);

    return;

}

