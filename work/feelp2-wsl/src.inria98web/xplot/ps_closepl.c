/*
 *  closepl,closeplv     psplot routine
 *
 *  close the window
 *
 */

#include "psplot.h"


closepl_ps()   /* Destroy window after mouse click */
{
    closeplv_ps(0);
    return;
}



closeplv_ps(n)
     int n;
{
    PSplot *nowp;

    if(is_psplot_plane_err("closeplv")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];
    fprintf(nowp->fp,"showpage\n");
    fclose(nowp->fp);

    free(nowp);
    PSplot_win[PSplot_plane_no] = NULL;

    return;

}


