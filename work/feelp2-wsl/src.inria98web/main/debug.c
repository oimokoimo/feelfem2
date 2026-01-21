/*
 * FEEL system Prototype Version 2
 * 
 * File     debug.c
 * Made     1992/09/04
 * Modified 
 * Version  0.0
 *
 * Purpose: DEBUG code
 *
 */

#include "../geom2d/geom2d.h"

extern int debug_mode;

#define YES 1
#define NO  0

/*                       現在デバッグプログラムは ../yacc/debug_start.cです
debug_start()
{
    if(debug_mode == NO) return;

    openpl();
    fspace(-0.1,-0.1,2.0,2.0);

    return;
}
*/


debug_terminate()
{
    if(debug_mode == NO) return;
    
/*    closepl();
*/
}

is_debug_mode() {
    return(debug_mode);
}

/*
debug_draw_po(po)
     POLYGON po;
{
    int i;

    if(debug_mode == NO) return;


    fmove(*(po.x),*(po.y));

    for(i=1;i<po.n;i++) {
	fcont(*(po.x+i),*(po.y+i));
    }
    fcont(*(po.x),*(po.y));
}

debug_hako_point(o)
     POINT o;
{
    if(debug_mode == NO) return;

    fhako(o.x,o.y);
}

debug_xwait()
{
    if(debug_mode == NO) return;

    xwait();
}

*/




nullwrt()
{
    /* do nothing */
    return;
}
