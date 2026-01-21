/*
 *   ps_init.c
 */

#include "psplot.h"

PSplot *PSplot_win[MAX_PS_FILES] = {
    NULL,NULL,NULL,NULL,NULL,NULL,
    NULL,NULL,NULL,NULL,NULL };

int PSplot_plane_no = -1;

char *PSplot_font_name = DEFAULT_FONT_PS;
int   PSplot_font_size[MAX_PS_FONTS];
int   PSplot_font_ptr  = 0;
int   PSplot_fonts     = 1;

int   PSplot_linewidth = LINE_WIDTH_PS;

init_ps()
{
    int i;
    PSplot *nowp;


    char *get_date();
    char *get_user_name();

    nowp = PSplot_win[PSplot_plane_no];

    for(i=0;i<MAX_PS_FONTS;i++) PSplot_font_size[i] = 0;
    PSplot_font_ptr = 0;
    PSplot_fonts    = 1;
    PSplot_font_size[PSplot_font_ptr] = 10;
    
 
    fprintf(nowp->fp,"%%!\n");
    fprintf(nowp->fp,"%%!PS-Adobe-1.0\n");

    fprintf(nowp->fp,"%%%%Creater:%s\n",get_user_name());
    fprintf(nowp->fp,"%%%%Date   :%s\n",get_date());

    fprintf(nowp->fp,"%%%%EndComments\n");

    ps_header(nowp->fp);  /* PostScript Header File */

    return;

}




    
