/*
 *   PostScript plot routine
 *
 *   Include FILE
 */

#include <stdio.h>

#define YES   1
#define NO    0
#define NONE -1

#define MAX_PS_FILES    11

#define MAX_PS_FONTS    10

#define DEFAULT_XLEN   600
#define DEFAULT_YLEN   600

#define MAX_POLYGON_POINTS 38

#define DEFAULT_FONT_PS  "/Times-Roman"
#define FONT_SIZE_PS     10
#define LINE_WIDTH_PS     5

/*
 *    Printer definitions
 */  

/* Apple Laser-Writer Plus */
/*
#define XDOT   574
#define YDOT   776
#define XMAX   612
#define YMAX   792
#define GX      18
#define GY       8
*/

/* NEC PC-602PS, PR-3000PS  */
#define XDOT   574
#define YDOT   776
#define XMAX   612
#define YMAX   792
#define GX      24
#define GY      15




typedef struct _PSplot {
    FILE     *fp;
    double  rate;
    
    int     xlen,ylen;

    int           spx0,spy0;   /* integer base point  */
    int           spdx,spdy;   /* integer edge length */
    double      dspx0,dspy0;   /* double  base point  */
    double      dspdx,dspdy;   /* double  edge length */

    int             cpx,cpy;   /* integer current point */
    double        dcpx,dcpy;   /* double  current point */

} PSplot;
    

extern int     PSplot_plane_no;
extern PSplot *PSplot_win[];
extern int     Xplot_PostScript;

extern int     PSplot_font_size[];
extern int     PSplot_font_ptr;
extern int     PSplot_fonts;
extern char*   PSplot_font_name;
extern int     PSplot_linewidth;

