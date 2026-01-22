/*
 *    分数で表された節点座標の検査
 * 
 *
 */
#include "../feel_def/feel_def.h"
#include <math.h>
#include <stdlib.h>
#include "element.h"

void SystemAbort(char *);

int GCD(x,y)               /* 最大公約数の計算 */
     int x,y;
{
    int t;
    while(y) {
	t = x % y;
	x = y;
	y = t;
    }
    return(x);
}

void reduce_fraction(r)        /* 約分処理 */
     Frac *r;
{
    int gcd;
    if(r->bunbo == 0) {
	SystemAbort("Cordinate causes 0 divide.\n");
    }

    gcd = GCD(abs(r->bunsi),abs(r->bunbo));

    if(gcd == 0 || gcd == 1) return;
    r->bunbo = r->bunbo /gcd;
    r->bunsi = r->bunsi /gcd;
    return;
}


int line_node_cordinate_check(r)   /* add project-1dim */
     Frac r;
{
    double x;

    x = (double)(r.bunsi) / (double)(r.bunbo);

    if(x < 0.0 || x  > 1.0) {
	return(ERR);
    }
    else {
	return(OK);        /* OK は ０ を返す */

    }

}

int tri_node_cordinate_check(r,s)
     Frac r,s;
{
    double x,y;

    x = (double)(r.bunsi) / (double)(r.bunbo);
    y = (double)(s.bunsi) / (double)(s.bunbo);

    if(x < 0.0 || y < 0.0 || x + y > 1.0) {
	return(ERR);
    }
    else {
	return(OK);        /* OK は ０ を返す */

    }

}


/* 四辺形に対する節点座標検査 */

int rect_node_cordinate_check(r,s)
     Frac r,s;
{
    double x,y;

    x = (double)(r.bunsi) / (double)(r.bunbo);
    y = (double)(s.bunsi) / (double)(s.bunbo);

    if(x < -1.0 || y < -1.0 || x  > 1.0 || y > 1.0) {
	return(ERR);
    }
    else {
	return(OK);        /* OK は ０ を返す */

    }
}


