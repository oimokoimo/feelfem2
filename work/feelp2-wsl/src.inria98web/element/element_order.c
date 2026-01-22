/*
 *  feel p2  element_order.c
 *
 *  要素内の節点番号の順番を一意に確定させる
 *
 *
 *  Made 1993/05/25  
 *
 *
 */
#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "element.h"

void SystemAbort(char *);
int tri_node_order(Frac,Frac,int,Frac,Frac,int);
int rect_node_order(Frac,Frac,int,Frac,Frac,int);
int line_node_order(Frac,int,Frac,int);

void element_order(etype , basis, r,s,t,ntype,expr)
     int etype;      /* 要素形状 */
     int basis;     /* 基底関数の数 */
     Frac r[],s[],t[];
     int ntype[];
     Expression *expr[];

{
    int   i,j;
    int   i_swap;
    Frac  f_swap;
    char *c_swap;
    char **cc_swap;
    Expression *e_swap;

    switch (etype) {

	/* 三角形形状に対するもの */
      case TRI:
	for(i=0;i<basis-1;i++) {
	    for(j=i+1;j<basis;j++) {
		if(i == j) continue;
		if(tri_node_order(r[i],s[i],ntype[i],      /*  > の時NO  */
				  r[j],s[j],ntype[j] )) {  /*  < の時YES */
		    f_swap = r[i];
		    r[i] = r[j];
		    r[j] = f_swap;
		    f_swap = s[i];
		    s[i] = s[j];
		    s[j] = f_swap;

		    e_swap = expr[i];
		    expr[i] = expr[j];
		    expr[j] = e_swap;

		    i_swap = ntype[i];
		    ntype[i] = ntype[j];
		    ntype[j] = i_swap;
		}
	    }
	}
	break;

      case RECT:
	for(i=0;i<basis-1;i++) {
	    for(j=i+1;j<basis;j++) {
		if(i == j) continue;
		if(rect_node_order(r[i],s[i],ntype[i],      /*  > の時NO  */
				  r[j],s[j],ntype[j] )) {  /*  < の時YES */
		    f_swap = r[i];
		    r[i] = r[j];
		    r[j] = f_swap;
		    f_swap = s[i];
		    s[i] = s[j];
		    s[j] = f_swap;

		    e_swap = expr[i];
		    expr[i] = expr[j];
		    expr[j] = e_swap;

		    i_swap = ntype[i];
		    ntype[i] = ntype[j];
		    ntype[j] = i_swap;
		}
	    }
	}
	break;



      case LINE:                             /* add project-1dim */
	for(i=0;i<basis-1;i++) {
	    for(j=i+1;j<basis;j++) {
		if(i == j) continue;
		if(line_node_order(r[i],ntype[i],      /*  > の時NO  */
				   r[j],ntype[j] )) {  /*  < の時YES */
		    f_swap = r[i];
		    r[i] = r[j];
		    r[j] = f_swap;

		    e_swap = expr[i];
		    expr[i] = expr[j];
		    expr[j] = e_swap;

		    i_swap = ntype[i];
		    ntype[i] = ntype[j];
		    ntype[j] = i_swap;
		}
	    }
	}
	break;



      default:
	SystemAbort("現在要素形状として指定できるのはtri(三角形)とrect(四辺形)だけです。\n");

    }

    return;
}


/*
 *  １次元線分要素節点順序の一意化
 */
double line_eval_frac(r)          /* プレevaluate関数 */
     Frac r;
{

    return((double)(r.bunsi)/(double)(r.bunbo)* -100+1100);

}

int line_node_order(r1,n1,r2,n2)
     Frac r1;
     int  n1;                 /*  > の時NO  */
     Frac r2;                 /*  < の時YES */
     int  n2;                 
{
    double eval1,eval2;

    eval1 = line_eval_frac(r1);   /* 節点座標によってプレevaluateを行う */
    eval2 = line_eval_frac(r2);   /* eval の点数が高いほど前 */

/*    DBGWRT("(%d/%d,%d/%d)[%d]%lf  (%d/%d,%d/%d)[%d]%lf\n",
	   r1.bunsi,r1.bunbo,s1.bunsi,s1.bunbo,n1,eval1,
	   r2.bunsi,r2.bunbo,s2.bunsi,s2.bunbo,n2,eval2);
*/

    if(eval1 < eval2) return(YES);
    if(eval1 > eval2) return(NO);

    if(n1 < n2) return( NO );
    if(n1 > n2) return( YES );

    SystemAbort("Same node basis is used.(in line element)\n");
    return -1;

}



/*
 *  ２次元三角形要素節点順序の一意化
 */
double tri_eval_frac(r,s)          /* プレevaluate関数 */
     Frac r,s;
{
    if((s.bunsi) == 0 ) {
	if((r.bunsi) == 0) return(6000.0);                      /* at (0,0) */
	if((r.bunsi) == 1 && (r.bunbo) == 1) return(5000.0);    /* at (1,0) */
	return(3000.0+1.0 -(double)(r.bunsi)/(double)(r.bunbo));/* at (x,0) */
    }

    if((r.bunsi) == 0 ) {
	if((s.bunsi) == 1 && (s.bunbo) == 1) return(4000.0);    /* at (0,1) */
	return(1000.0 + (double)(s.bunsi)/(double)(s.bunbo));   /* at (0,y) */
    }

    if((r.bunsi)*(s.bunbo)+(s.bunsi)*(r.bunbo) == (r.bunbo)*(s.bunbo)) {
	return(2000.0 + (double)(r.bunsi)/(double)(r.bunbo));
    }

    return((double)(r.bunsi)/(double)(r.bunbo) * 100.0 +
	   (double)(s.bunsi)/(double)(s.bunbo)   );
}

int tri_node_order(r1,s1,n1,r2,s2,n2)
     Frac r1,s1;
     int  n1;                 /*  > の時NO  */
     Frac r2,s2;              /*  < の時YES */
     int  n2;                 
{
    double eval1,eval2;

    eval1 = tri_eval_frac(r1,s1);   /* 節点座標によってプレevaluateを行う */
    eval2 = tri_eval_frac(r2,s2);   /* eval の点数が高いほど前 */

/*    DBGWRT("(%d/%d,%d/%d)[%d]%lf  (%d/%d,%d/%d)[%d]%lf\n",
	   r1.bunsi,r1.bunbo,s1.bunsi,s1.bunbo,n1,eval1,
	   r2.bunsi,r2.bunbo,s2.bunsi,s2.bunbo,n2,eval2);
*/

    if(eval1 < eval2) return(YES);
    if(eval1 > eval2) return(NO);

    if(n1 < n2) return( NO );
    if(n1 > n2) return( YES );

    SystemAbort("Same node basis is used.(in tri element)\n");
    return -1;

}

/*-------------------------------------------------------
 *  ２次元四辺形要素節点順序の一意化
 *          
 *          
 *             5700pts                 5800pts
 *             (-1,1)   2100pts        (1,1)
 *               ┌──────────┐
 *               │                    │
 *               │                    │
 *               │                    │
 *       1100pts │ 内部は             │3100pts
 *               │ (x+1.0)*100+ y+1.0 │
 *               │                 pts│
 *               │                    │
 *               │                    │
 *               └──────────┘
 *             (-1,-1)    4100pts     (1,-1)
 *             6000pts                5900pts
 *
 *
 *---------------------------------------------------------*/
/*
double rect_eval_frac(r,s)
     Frac r,s;
{
    double rect_eval_frac2(),ret;
    ret = rect_eval_frac2(r,s);
    printf("eval ");
    prt_frac_image_2d(r,s);
    printf("  val = %f\n",ret);
    return(ret);
}
*/

double rect_eval_frac(r,s)          /* プレevaluate関数 */
     Frac r,s;
{

    /* 辺 y=-1 上の場合の処理 */
    if((s.bunsi)*(s.bunbo) == -1) {   /* s = -1 */
	if((r.bunsi)*(r.bunbo) == -1) { /* at (-1,-1) */
	    return(6000.0);
	}
	if((r.bunsi)*(r.bunbo) ==  1) { /* at ( 1,-1) */
	    return(5900.0);
	}
	/* 辺y=-1上に有り */
	return(4100.0 - (double)(r.bunsi)/(double)(r.bunbo));
    }

    /* 辺 y= 1 上の場合の処理 */
    if((s.bunsi)*(s.bunbo) ==  1) {   /* s =  1 */
	if((r.bunsi)*(r.bunbo) == -1) { /* at (-1, 1) */
	    return(5700.0);
	}
	if((r.bunsi)*(r.bunbo) ==  1) { /* at ( 1, 1) */
	    return(5800.0);
	}
	/* 辺y=1上に有り */
	return(2100.0 + (double)(r.bunsi)/(double)(r.bunbo));
    }

    /* 辺 x = -1上の場合の処理 */
    if((r.bunsi)*(r.bunbo) == -1) {
	return(1100.0 + (double)(s.bunsi)/(double)(s.bunbo));
    }

    /* 辺 x =  1上の場合の処理 */
    if((r.bunsi)*(r.bunbo) ==  1) {
	return(3100.0 - (double)(s.bunsi)/(double)(s.bunbo));
    }

    return((double)(r.bunsi)/(double)(r.bunbo) * 100.0  +
	   (double)(s.bunsi)/(double)(s.bunbo)   );
}

/* 四辺形評価関数 */
int rect_node_order(r1,s1,n1,r2,s2,n2)
     Frac r1,s1;
     int  n1;                 /*  > の時NO  */
     Frac r2,s2;              /*  < の時YES */
     int  n2;                 
{
    double eval1,eval2,rect_eval_frac();

    eval1 = rect_eval_frac(r1,s1);   /* 節点座標によってプレevaluateを行う */
    eval2 = rect_eval_frac(r2,s2);   /* eval の点数が高いほど前 */

/*
    DBGWRT("(%d/%d,%d/%d)[%d]%lf  (%d/%d,%d/%d)[%d]%lf\n",
	   r1.bunsi,r1.bunbo,s1.bunsi,s1.bunbo,n1,eval1,
	   r2.bunsi,r2.bunbo,s2.bunsi,s2.bunbo,n2,eval2);
*/

    if(eval1 < eval2) return(YES);
    if(eval1 > eval2) return(NO);

    if(n1 < n2) return( NO );
    if(n1 > n2) return( YES );

    SystemAbort("Same node basis is used.(in rect element)\n");
    return -1;

}







