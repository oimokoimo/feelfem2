/*
 *   X11 Window Drawing routines   
 *
 *   Include FILE
 */

#include <stdio.h>
#include <X11/Xlib.h>



#define YES   1
#define NO    0
#define NONE -1

#define MAX_WINDOWS       11
#define POOLS_IN_A_BLOCK  38

#define MAX_POLYGON_POINTS 38

#define SCALE_COLORS      50

/* #define USE_BACKINGSTORE  */

#define DEFAULT_BG  "antiquewhite2"
#define DEFAULT_FG  "black"

#define DEFAULT_XLEN   600
#define DEFAULT_YLEN   600

#define DEFAULT_FONT "-adobe-courier-medium-r-normal--11-80-100-100-m-60-iso8859-1"
#define FONT_SIZE    11

#define DD         1
#define II         2
#define S          3
#define DDS        4
#define IIS        5
#define DDDD       6
#define IIII       7

#define MOVE       1
#define FMOVE      2
#define CONT       3
#define FCONT      4
#define SPACE      5
#define FSPACE     6
#define LINE       7
#define FLINE      8

typedef struct _DblDbl {
    double a,b;
} DblDbl;

typedef struct _IntInt {
    int    a,b;
} IntInt;

typedef struct _Str {
    char *a;
} Str;

typedef struct _DblDblStr {
    double  a,b;
    char   *c;
} DblDblStr;

typedef struct _IntIntStr {
    int     a,b;
    char   *c;
} IntIntStr;


typedef struct _Pool {
    int     type;
    union PoolUnion{
	IntInt      intint;
	DblDbl      dbldbl;
	Str         str;
	DblDblStr   dbldblstr;
	IntIntStr   intintstr;
    };
} Pool;

typedef struct _PoolBlock {
    int elems;
    Pool pool[POOLS_IN_A_BLOCK];
    struct _PoolBlock  *next_ptr;
} PoolBlock;



typedef struct _Xplot {

    Display            *dpy;
    Window             root;
    Window              win;
    GC                   gc;
    Colormap           cmap;
    int              screen;
    int                  fg;
    int                  bg;

    int           xlen,ylen;   /* window edge length */

    int           spx0,spy0;   /* integer base point  */
    int           spdx,spdy;   /* integer edge length */
    double      dspx0,dspy0;   /* double  base point  */
    double      dspdx,dspdy;   /* double  edge length */

    int             cpx,cpy;   /* integer current point */
    double        dcpx,dcpy;   /* double  current point */

    int         FONTcomeyet;
    Font               font;

    int         pool_blocks;
    PoolBlock      *pb__ptr;
    

}  Xplot;


/*
 *  Extern variables
 */

extern int Xplot_plane_no;
extern Xplot *Xplot_win[];

extern int Xplot_win_xlen;
extern int Xplot_win_ylen;

extern int Xplot_PostScript;
extern int Xplot_X11;

extern int Xplot_font_size;

extern char *Xplot_bg_name;
extern char *Xplot_fg_name;

/*
 *  External functions
 */


unsigned long xplot_mycolor();

