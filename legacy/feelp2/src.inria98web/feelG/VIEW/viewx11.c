/************************************************************************/
/*                                                                      */
/* View Ver 2.0                                                         */
/* viewx11.c                                                            */
/* Copy rights - all rights reserved by NEC                             */
/*                                                                      */
/************************************************************************/

#include "view.h"

Display	*ViewX11GetDisplay(id)
int     id;
{
    return(viewdisp[id].disp);
}

Window  ViewX11GetWindow(id)
int     id;
{
    return(viewdisp[id].win);
}

GC      ViewX11GetGC(id)
int     id;
{
    return(viewdisp[id].gc);
}

Colormap    ViewX11GetColormap(id)
int     id;
{
    return(DefaultColormap(viewdisp[id].disp,0));
}

int     ViewX11GetWindowSize(nw,nh,id)
int	*nw,*nh;
int     id;
{
    *nw = viewport[id].width;
    *nh = viewport[id].height;
}




