/************************************************************************/
/*                                                                      */
/* View ver 2.0                                                         */
/* viewtype.h                                                           */
/* Copy rights - all rights reserved by NEC                             */
/*                                                                      */
/************************************************************************/

#define VIEW_MAX_DISP           10	/*	ウインドウ数	*/
#define VIEW_MAX_COLOR          50	/*	色数		*/
#define VIEW_MAX_BRIGHT         50	/*	輝度		*/
#define VIEW_MAX_POINT          100
#define VIEW_MAX_CHAR           100

#define MCN                     65500

#define	VIEW_PI					3.141592654

#define	VIEW_POINT				0
#define	VIEW_LINE				1
#define	VIEW_POLYGON			2
#define	VIEW_TEXT				3
#define	VIEW_ARC				4

#define	VIEW_SOLID				0
#define	VIEW_WIRE				1

#define	VIEW_ARC_ALL			0
#define	VIEW_ARC_SUB			1

#define	VIEW_POINT_POINT		0
#define	VIEW_POINT_ARC			1
#define	VIEW_POINT_FILL			2

#define	VIEW_ZBUFF_OFF			0
#define	VIEW_ZBUFF_ON			1

#define	VIEW_SHADE_OFF			0
#define	VIEW_SHADE_ON			1

#define	VIEW_CLEAR_OFF			0
#define	VIEW_CLEAR_ON			1

#define	VIEW_CLIP_OFF			0	/* 1994.5.26 追加 */
#define	VIEW_CLIP_ON			1	/* 1994.5.26 追加 */

#define	VIEW_XY_PLANE			1
#define	VIEW_YZ_PLANE			2
#define	VIEW_ZX_PLANE			3
#define	VIEW_YX_PLANE		    -1
#define	VIEW_ZY_PLANE		    -2
#define	VIEW_XZ_PLANE		    -3

#define	VIEW_DRAW_BUFF			0
#define	VIEW_DRAW_INTC			1

#define	VIEW_LIGHT_DPND			0
#define	VIEW_LIGHT_SELF			1

typedef struct	{

	float	x;
	float	y;
	float	z;

}Vpoint;

typedef struct	{

	int	nx;
	int	ny;
	int	nz;

}VpointInt;

typedef struct	{

	float	x_val;
	float	y_val;
	float	z_val;

}Vvector;

typedef struct	{

	Vpoint	point;
	float	scalar;
	Vvector	vector;

}Vpoint_struct;

typedef struct  {

	float	r,g,b;

}Vcolor;

typedef	struct {

	Vpoint	    min;
	Vpoint	    max;
	Vpoint	    ref;
	Vpoint	    rot;
	Vpoint	    pnt;
	int	        width;
	int	        height;
	int	        pln;
	Vpoint	    zoom;
	float	    pmax;
	VpointInt	move;
	Vpoint	    cmin;
	Vpoint	    cmax;

}Vviewport_struct;

typedef	struct {

	int		type;
	int		att;
	int		c_number;
	int		p_number;
	Vpoint	*point;
	char	text[VIEW_MAX_CHAR];
	char	font[VIEW_MAX_CHAR];

}Vdraw_struct;

typedef	struct {

	int		zbuff;
	int		shade;
	int		dmode;
	int		clip;	/* 1994.5.26 追加 */

}Vattr_struct;

typedef	struct {
	
	int		mode;
	Vpoint	p;
	int		cid;
	float	s;

}Vlight_struct;

typedef struct  {

    Display *disp;
    Window  win;
    GC  gc;
    Pixmap  pmap;

}Vwindow;

typedef struct  {

    XColor  color[VIEW_MAX_BRIGHT];
    int     bright;

}Vcolor_struct;

