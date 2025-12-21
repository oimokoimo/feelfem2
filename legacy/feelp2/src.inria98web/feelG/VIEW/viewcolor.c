#include "view.h"

void    ViewExtCreateColortable(id)
int             id;
{
        Vcolor  c;
        int             n = 0;

        c.r = 0.00; c.g = 0.00; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n ++;

        c.r = 1.00; c.g = 1.00; c.b = 1.00;
        ViewSetColor(&c,n,1,id); n ++;

/*                   nを22にする         */
        n = 22;

/*      magenta */
        c.r = 1.00; c.g = 0.00; c.b = 1.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 1.00; c.g = 0.00; c.b = 0.75;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 1.00; c.g = 0.00; c.b = 0.50;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 1.00; c.g = 0.00; c.b = 0.25;
        ViewSetColor(&c,n,1,id); n --;

/*      red     */
        c.r = 1.00; c.g = 0.00; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 1.00; c.g = 0.25; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 1.00; c.g = 0.50; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 1.00; c.g = 0.75; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

/*      yellow  */
        c.r = 1.00; c.g = 1.00; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.75; c.g = 1.00; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.50; c.g = 1.00; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.25; c.g = 1.00; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

/*      green   */
        c.r = 0.00; c.g = 1.00; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.00; c.g = 1.00; c.b = 0.25;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.00; c.g = 1.00; c.b = 0.50;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.00; c.g = 1.00; c.b = 0.75;
        ViewSetColor(&c,n,1,id); n --;

/*      cyan    */
        c.r = 0.00; c.g = 1.00; c.b = 1.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.00; c.g = 0.75; c.b = 1.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.00; c.g = 0.50; c.b = 1.00;
        ViewSetColor(&c,n,1,id); n --;

        c.r = 0.00; c.g = 0.25; c.b = 1.00;
        ViewSetColor(&c,n,1,id); n --;

/*      blue    */
        c.r = 0.00; c.g = 0.00; c.b = 1.00;
        ViewSetColor(&c,n,1,id); n --;
}

void    vect_(id)
int     *id;
{
        ViewExtCreateColortable(*id);
}

/*      グレイスケール  */
void    ViewExtCreateGraytable(id)
int             id;
{
        Vcolor  c;
        int     n = 0;

        c.r = 0.00; c.g = 0.00; c.b = 0.00;
        ViewSetColor(&c,n,1,id); n ++;

        c.r = 1.00; c.g = 1.00; c.b = 1.00;
        ViewSetColor(&c,n,1,id); n ++;

        for ( n=22; n>1; n-- ) {
                ViewSetColor(&c,n,1,id);
                c.r -= 1.0/21;
                c.g = c.r; c.b = c.r;
        }
}

void    vectg_(id)
int     *id;
{
        ViewExtCreateGraytable(*id);
}


