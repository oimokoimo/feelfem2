/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   plot.c
 *      Date:   1994/01/12
 *   
 *   Purpose:   plot文の処理
 *   Functions: 
 *              一番目はファイル名
 *              ２番目はline名
 *              ３番目以降が変数データ名
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "scheme_comp.h"

static int plots = 0;

void plot_st(parameters)
     int parameters;
{
    int i;
    Plot *plot_struct;
    
    char **var_name;
    int    vars;

    if(parameters < 2) {
	SystemError_yy("plot文の引き数が足りない",yylineno_info());
	for(i=0;i<parameters;i++) {
	    pop();
	}
	return;
    }
    
    plot_struct = (Plot *)FEEL_GetMemory(sizeof(Plot));


    /* ファイル装置番号を得る */
    plot_struct -> file_io_no = get_data_file_number();


    plot_struct -> type = PLOT_FILE;
    
    vars = parameters - 1;

    var_name = (char **)FEEL_GetMemory(sizeof(char *)*vars);

    /* 順番通り */
    for(i=0;i<vars;i++) {
	*(var_name + vars - i - 1) = PopString();
    }

    /* プロット番号(fortranプログラムのサブルーチン名に使用) */
    plots++;

    plot_struct -> name = PopString();     /* line名 */
    
    /* ファイル名処理 */
    plot_struct -> filename = PopString(); /* file名 */
    plot_struct -> numdat_no = NO;         /* checkルーチンでの判定に使用 */
    plot_struct -> items  = vars;
    plot_struct -> plot_no  = plots;
    plot_struct -> var_name = var_name;
    plot_struct -> yylineno = yylineno_info();
    plot_struct -> mesg     = NULL;

    store_scheme( PLOT_FILE , plot_struct);
    

/*    fprintf(stderr,"ファイル名 %s\n",plot_struct->filename);
    fprintf(stderr,"line名     %s\n",plot_struct->name);
    fprintf(stderr,"表示変数   ",plot_struct->name);
    
    for(i=0;i<plot_struct->items;i++) {
	fprintf(stderr,"%s ",*(plot_struct->var_name + i));
    }
    fprintf(stderr,"\n");
*/

    return;
}

void Xplot_st(parameters)
     int parameters;
{
    int i;
    Plot *plot_struct;
    
    char **var_name;
    int    vars;

    if(parameters < 2) {
	SystemError_yy("plot文の引き数が足りない",yylineno_info());
	for(i=0;i<parameters;i++) {
	    pop();
	}
	return;
    }
    
    plot_struct = (Plot *)FEEL_GetMemory(sizeof(Plot));


    /* ファイル装置番号を得る(SX,SY領域保存の為) */
    plot_struct -> file_io_no = get_data_file_number();
    
    /* X-Window IDを割り振る */
    plot_struct -> window_id  = get_new_window_id();


    plot_struct -> type = XPLOT;

    UseLibrary(XPLOT,"xplot");

    plot_struct -> IWW  = 600;
    plot_struct -> IWH  = 600;
    
    vars = parameters - 1;

    var_name = (char **)FEEL_GetMemory(sizeof(char *)*vars);

    /* 順番通り */
    for(i=0;i<vars;i++) {
	*(var_name + vars - i - 1) = PopString();
    }

    /* プロット番号(fortranプログラムのサブルーチン名に使用) */
    plots++;

    plot_struct -> name = PopString();     /* line名 */

    /* プロットオプション */
    plot_struct -> IFLG = NO;              /* use default */
    
    /* ファイル名処理 */
    plot_struct -> filename = NULL;        /* file名 */
    plot_struct -> numdat_no = NO;         /* checkルーチンでの判定に使用 */
    plot_struct -> items  = vars;
    plot_struct -> plot_no  = plots;
    plot_struct -> var_name = var_name;
    plot_struct -> yylineno = yylineno_info();
    plot_struct -> mesg = NULL;

    store_scheme( XPLOT , plot_struct);
    

/*    fprintf(stderr,"ファイル名 %s\n",plot_struct->filename);
    fprintf(stderr,"line名     %s\n",plot_struct->name);
    fprintf(stderr,"表示変数   ",plot_struct->name);
    
    for(i=0;i<plot_struct->items;i++) {
	fprintf(stderr,"%s ",*(plot_struct->var_name + i));
    }
    fprintf(stderr,"\n");
*/

    return;
}


void Xplot_st_with_setting(parameters,settings)
     int parameters;
     int settings;
{
    int i;
    Plot *plot_struct;
    
    char **var_name;
    int    vars;

    double umin,umax;
    int    umin_flag,umax_flag;

    int    winsiz;
    int    winsiz_flag;

    char *num,*key;

    plot_struct = (Plot *)FEEL_GetMemory(sizeof(Plot));


    winsiz_flag = NO;
    umin_flag   = NO;
    umax_flag   = NO;

    plot_struct -> mesg = NULL;

    for(i=0;i<settings;i++) {
	num = PopString();
	key = PopString();

	if(streq(key,"winsiz")) {
	    winsiz = atoi(num);
	    if(winsiz <= 0 || winsiz > 2000) {
		SystemWarning_yy("xplot文での画面サイズ不正");
	    }
	    winsiz_flag = YES;
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

	if(streq(key,"mesg")) {
	    plot_struct -> mesg = num;
	    continue;
	}

	SystemError_yy_s("xplot文詳細指定キーワード%sはだめ",key,
			 yylineno_info());

    }


    if(parameters < 2) {
	SystemError_yy("plot文の引き数が足りない",yylineno_info());
	for(i=0;i<parameters;i++) {
	    pop();
	}
	return;
    }
    
    /* ファイル装置番号を得る(SX,SY領域保存の為) */
    plot_struct -> file_io_no = get_data_file_number();
    
    /* X-Window IDを割り振る */
    plot_struct -> window_id  = get_new_window_id();


    plot_struct -> type = XPLOT;

    UseLibrary(XPLOT,"xplot");

    if(winsiz_flag == YES) {
	plot_struct -> IWW = winsiz;
	plot_struct -> IWH = winsiz;
    }
    else {
	plot_struct -> IWW  = 600;
	plot_struct -> IWH  = 600;
    }

    if(umin_flag == YES && umax_flag == YES) {
	plot_struct -> umin = umin;
	plot_struct -> umax = umax;
	if(umin >= umax) {
	    SystemError_yy("xplotの上下界値設定に誤り",yylineno_info());
	}
	plot_struct -> IFLG = YES;
    }
    else {
	if(umin_flag == YES || umax_flag == YES) {
	    SystemError_yy("xplotの上下界値設定は両方指定しなければならない",
			   yylineno_info());
	}
	else {
	    plot_struct -> IFLG = NO;
	}
    }
    
    vars = parameters - 1;

    var_name = (char **)FEEL_GetMemory(sizeof(char *)*vars);

    /* 順番通り */
    for(i=0;i<vars;i++) {
	*(var_name + vars - i - 1) = PopString();
    }

    /* プロット番号(fortranプログラムのサブルーチン名に使用) */
    plots++;

    plot_struct -> name = PopString();     /* line名 */
    
    /* ファイル名処理 */
    plot_struct -> filename = NULL;        /* file名 */
    plot_struct -> numdat_no = NO;         /* checkルーチンでの判定に使用 */
    plot_struct -> items  = vars;
    plot_struct -> plot_no  = plots;
    plot_struct -> var_name = var_name;
    plot_struct -> yylineno = yylineno_info();

    store_scheme( XPLOT , plot_struct);
    

/*    fprintf(stderr,"ファイル名 %s\n",plot_struct->filename);
    fprintf(stderr,"line名     %s\n",plot_struct->name);
    fprintf(stderr,"表示変数   ",plot_struct->name);
    
    for(i=0;i<plot_struct->items;i++) {
	fprintf(stderr,"%s ",*(plot_struct->var_name + i));
    }
    fprintf(stderr,"\n");
*/

    return;
}


void time_plot_st(parameters)
     int parameters;
{
    int i;
    Plot *plot_struct;
    
    char **var_name;
    int    vars;

    if(parameters < 1) {
	SystemError_yy("time-fplot文の引き数が足りない",yylineno_info());
	for(i=0;i<parameters;i++) {
	    pop();
	}
	return;
    }
    
    plot_struct = (Plot *)FEEL_GetMemory(sizeof(Plot));

    plot_struct -> type = TIME_PLOT_FILE;

    /* ファイル装置番号を得る */
    plot_struct -> file_io_no = get_data_file_number();

    vars = parameters ;

    var_name = (char **)FEEL_GetMemory(sizeof(char *)*vars);

    /* 順番通り */
    for(i=0;i<vars;i++) {
	*(var_name + vars - i - 1) = PopString();
    }

    /* プロット番号 */
    plots++;
    
    /* ファイル名処理 */
    plot_struct -> filename = PopString(); /* file名 */
    plot_struct -> numdat_no = NO;         /* checkルーチンでの判定に使用 */
    plot_struct -> items  = vars;
    plot_struct -> plot_no  = plots;
    plot_struct -> var_name = var_name;
    plot_struct -> yylineno = yylineno_info();
    plot_struct -> mesg     = NULL;

    store_scheme( TIME_PLOT_FILE , plot_struct);
    

/*    fprintf(stderr,"ファイル名 %s\n",plot_struct->filename);
    fprintf(stderr,"line名     %s\n",plot_struct->name);
    fprintf(stderr,"表示変数   ",plot_struct->name);
    
    for(i=0;i<plot_struct->items;i++) {
	fprintf(stderr,"%s ",*(plot_struct->var_name + i));
    }
    fprintf(stderr,"\n");
*/

    return;
}

    
int how_many_plots()
{
    return(plots);
}

