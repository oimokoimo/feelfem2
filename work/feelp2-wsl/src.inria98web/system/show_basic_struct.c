/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   show_basic_struct.c
 *      Date:   1993/09/03
 *   
 *   Purpose:   基本的な構造体の画面イメージを返す
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

static char buf[64];

char *frac_image(r)
     Frac r;
{
    if(r.bunbo == 1) {
	sprintf(buf,"%d",r.bunsi);
    }
    else {
	sprintf(buf,"%d/%d",r.bunsi,r.bunbo);
    }
    
    return(buf);
}

prt_frac_image_2d(r,s)
Frac r,s;
{
    printf("(%s,",frac_image(r));
    printf("%s)",frac_image(s));
    return;
}
