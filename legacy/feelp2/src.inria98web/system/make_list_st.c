/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_list_st.c
 *      Date:   1993/10/26
 *   
 *   Purpose:   LISPプログラム作成の為のサービスプログラム
 *              
 * Functions:   char *make_list_st(buf, s)
 *              void  end_list_st(buf)
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"


char *make_list_st( buf , s )
     char *buf;    /* buf バッファ         */
     char *s;      /* s コピーすべき文字列 */
{

    while(*s) {
	*buf = *s;
	buf++;
	s++;
    }
    return(buf);
}
      
void end_list_st( buf )
     char *buf;
{
    *buf = '\0';
    return;
}

