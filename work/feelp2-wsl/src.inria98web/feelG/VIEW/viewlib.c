/************************************************************************/
/*                                                                      */
/* View Ver 2.0                                                         */
/* viewlib.c                                                            */
/* Copy rights - all rights reserved by NEC                             */
/*                                                                      */
/************************************************************************/

#include "view.h"

Vwindow				viewdisp[VIEW_MAX_DISP];
Vcolor_struct		viewcolor[VIEW_MAX_DISP][VIEW_MAX_COLOR];
Vviewport_struct	viewport[VIEW_MAX_DISP];
Vdraw_struct		*viewdraw[VIEW_MAX_DISP];

int					viewdraw_num[VIEW_MAX_DISP];
int					viewdraw_size[VIEW_MAX_DISP];
Vattr_struct		viewattr[VIEW_MAX_DISP];
Vlight_struct		viewlight[VIEW_MAX_DISP];

/*		ウインドウを大きさを入手		*/
int		ViewGetGeometry(id)
int		id;
{
    Display *disp;
    Window  win;

    Window          root;
    int             px,py;
    unsigned int    sx,sy,br,dp;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;

    XGetGeometry(disp,win,&root,&px,&py,&sx,&sy,&br,&dp);

    viewport[id].width  = sx;
    viewport[id].height = sy;

	return( 1 );
}

/*		ウインドウをオープンする		*/
int		ViewOpenWindow(sx,sy,sw,sh,mg,id)
int		sx,sy,sw,sh,mg,id;
{
    Display *disp;
    Window  win;
	GC		gc;
	XSetWindowAttributes	att;

	if (id < 0 || id > VIEW_MAX_DISP - 1) 	return( - 1 );

/*	ウインドウパラメータの設定	*/
	disp = XOpenDisplay(NULL);
    if(disp == NULL) {
       fprintf(stderr,"Cannot open display %s\n",getenv("DISPLAY"));
       exit(1);
    }

	win  = XCreateSimpleWindow(disp,RootWindow(disp,0),sx,sy,sw,sh,2,
							WhitePixel(disp,0),BlackPixel(disp,0));

	gc   = XCreateGC(disp,win,0,0);

/*	ウインドウマネージャの有無	*/
	if (mg != 0) {
		att.override_redirect = True;
		XChangeWindowAttributes(disp,win,CWOverrideRedirect,&att);
	}

    XSelectInput(disp,win,ExposureMask);

	XMapWindow(disp,win);

	XFlush(disp);

	viewdisp[id].disp = disp;
	viewdisp[id].win  = win;
	viewdisp[id].gc   = gc;

/*	ウインドウサイズの設定	*/
	viewport[id].width  = sw;
	viewport[id].height = sh;

/*	パラメータの初期化	*/
	if (ViewInitialize(id) < 0) 		return( - 1 );

/*	カラーテーブルの初期化	*/
	if (ViewInitializeColor(id) < 0) 	return( - 1 );

/*	背景色の設定	*/
    if (ViewSetBackground(0,0,id) < 0) 	return( - 1 );

	return( 1 );
}

/* 	ウインドウのバッキングストア	*/
int		ViewSetBackingStore(nf,id)
int		nf;
int		id;
{
    Display *disp;
    Window  win;
	XSetWindowAttributes	att;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;

/*  バッキングストアの設定  */
	if (nf == 1) att.backing_store = Always;
    else         att.backing_store = NotUseful;

    XChangeWindowAttributes(disp,win,CWBackingStore,&att);

	return( 1 );
}

/*	ウイジットとライブラリの接続	*/
int		ViewConnectWindow(disp,win,id)
Display	*disp;
Window	win;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

/*	ウインドウパラメータの設定	*/
	viewdisp[id].disp = disp;
	viewdisp[id].win  = win;
	viewdisp[id].gc   = XCreateGC(disp,win,0,0);

/*	ウインドウサイズの設定	*/
	ViewGetGeometry(id);

/*	パラメータの初期化	*/
	if (ViewInitialize(id) < 0) return( - 1 );

/*	カラーテーブルの初期化	*/
	if (ViewInitializeColor(id) < 0) return( - 1 );

/*	背景色の設定	*/
    if (ViewSetBackground(0,0,id) < 0) return( - 1 );

	return( 1 );
}

/*	ウインドウの表示確認	*/
int     ViewMapWindow(id)
int     id;
{
    Display *disp;
    XEvent e;

    disp = viewdisp[id].disp;

    XNextEvent(disp,&e);

    return( 1 );
}

/*	ウインドウの消去	*/
int		ViewDeleteWindow(id)
int		id;
{
    Display *disp;
    Window  win;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;

	XDestroyWindow(disp,win);

	return( 1 );
}

/*	作業メモリの確保	*/
int		ViewAllocWindow(size,id)
int		size,id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	free(viewdraw[id]);

	if (size < 0) {
		size = 2;
		viewattr[id].dmode = VIEW_DRAW_INTC;
	}

	viewdraw[id] = (Vdraw_struct *)malloc(sizeof(Vdraw_struct) * size + 1);

	if (viewdraw[id] == (Vdraw_struct *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	viewdraw_size[id] = size;

	return( 1 );
}

/*	作業メモリの追加	*/
int		ViewAddAllocWindow(id)
int		id;
{
	Vdraw_struct	*tmp;
	int				i,j;

    if (viewattr[id].dmode == VIEW_DRAW_INTC) return( 1 );

	if (viewdraw_num[id] < viewdraw_size[id]) return( 1 );

	tmp = (Vdraw_struct *)malloc(sizeof(Vdraw_struct) * viewdraw_size[id] + 1);

	if (tmp == (Vdraw_struct *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < viewdraw_size[id];i ++) {
		tmp[i].type = viewdraw[id][i].type;
		tmp[i].att  = viewdraw[id][i].att;
		tmp[i].c_number = viewdraw[id][i].c_number;
		tmp[i].p_number = viewdraw[id][i].p_number;
        tmp[i].point = (Vpoint *)malloc(sizeof(Vpoint) * tmp[i].p_number);
		for (j = 0;j < tmp[i].p_number;j ++) {
			tmp[i].point[j].x = viewdraw[id][i].point[j].x;
			tmp[i].point[j].y = viewdraw[id][i].point[j].y;
			tmp[i].point[j].z = viewdraw[id][i].point[j].z;
		}
		strcpy(tmp[i].font,viewdraw[id][i].font);
		strcpy(tmp[i].text,viewdraw[id][i].text);
	}

	free(viewdraw[id]);

	viewdraw[id] = (Vdraw_struct *)malloc(sizeof(Vdraw_struct) 
                                       * viewdraw_size[id] * 2 + 1);
	if (viewdraw[id] == (Vdraw_struct *)NULL) {
		fprintf(stderr,"cant get memory again\n");
        exit(1);
	}

	for (i = 0;i < viewdraw_size[id];i ++) {
		viewdraw[id][i].type     = tmp[i].type;
		viewdraw[id][i].att      = tmp[i].att;
		viewdraw[id][i].c_number = tmp[i].c_number;
		viewdraw[id][i].p_number = tmp[i].p_number;
        viewdraw[id][i].point    = (Vpoint *)malloc(sizeof(Vpoint) 
                                           * viewdraw[id][i].p_number);
		for (j = 0;j < viewdraw[id][i].p_number;j ++) {
			viewdraw[id][i].point[j].x = tmp[i].point[j].x;
			viewdraw[id][i].point[j].y = tmp[i].point[j].y;
			viewdraw[id][i].point[j].z = tmp[i].point[j].z;
		}
		strcpy(viewdraw[id][i].text,tmp[i].text);
		strcpy(viewdraw[id][i].font,tmp[i].font);
	}

	viewdraw_size[id] *= 2;

	return( 1 );
}

/*	カラーテーブルの初期化	*/
int 	ViewInitializeColor(id)
int		id;
{
    Display *disp;
    int     	i;
    Colormap    cmap;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    disp = viewdisp[id].disp;
    cmap = DefaultColormap(disp,0);

	for (i = 0;i < VIEW_MAX_COLOR;i ++) viewcolor[id][i].bright = 1;

/*	カラーＩＤ  ０：黒	*/
    viewcolor[id][0].color[0].red   = (long)(MCN * 0.0);
    viewcolor[id][0].color[0].green = (long)(MCN * 0.0);
    viewcolor[id][0].color[0].blue  = (long)(MCN * 0.0);
	XAllocColor(disp,cmap,&viewcolor[id][0].color[0]);

/*	カラーＩＤ  １：白	*/
    viewcolor[id][1].color[0].red   = (long)(MCN * 1.0);
    viewcolor[id][1].color[0].green = (long)(MCN * 1.0);
    viewcolor[id][1].color[0].blue  = (long)(MCN * 1.0);
	XAllocColor(disp,cmap,&viewcolor[id][1].color[0]);

	return( 1 );
}

/*	パラメータの初期化	*/
int		ViewInitialize(id)
int		id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	if (ViewAllocWindow(-1,id) < 0) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	viewdraw_num[id] = 0;

	viewport[id].pln    = VIEW_XY_PLANE; 	/*	投影面：ＸＹ	*/
	viewport[id].zoom.x = 1.0; 				/*	倍率  ：1.0		*/
	viewport[id].zoom.y = 1.0;
	viewport[id].zoom.z = 1.0;
	viewport[id].move.nx = 0;
	viewport[id].move.ny = 0;

	viewattr[id].zbuff = VIEW_ZBUFF_OFF; 	/*	陰線処理：なし	*/
	viewattr[id].shade = VIEW_SHADE_OFF; 	/*	陰影処理：なし	*/
	viewattr[id].clip  = VIEW_CLIP_OFF; 	/*	クリップ：なし	*/
	viewattr[id].dmode = VIEW_DRAW_BUFF; 	/*	バッファ：なし	*/

	viewlight[id].mode = VIEW_LIGHT_DPND;   /*  光源設定：なし  */
	viewlight[id].cid  = 1;   				/*  光源色  ：白    */
	viewlight[id].s    = 1.0;   			/*  光源強度：1.0   */

/*	ビューポートの初期化	*/
	viewport[id].min.x = -1.0;
	viewport[id].min.y = -1.0;
	viewport[id].min.z = -1.0;
	viewport[id].max.x =  1.0;
	viewport[id].max.y =  1.0;
	viewport[id].max.z =  1.0;
	viewport[id].ref.x =  0.0;
	viewport[id].ref.y =  0.0;
	viewport[id].ref.z =  0.0;

/*	回転角の初期化	*/
	viewport[id].rot.x = 0.0;
	viewport[id].rot.y = 0.0; 
	viewport[id].rot.z = 0.0;
	viewport[id].pnt.x = 0.0;
	viewport[id].pnt.y = 0.0;
	viewport[id].pnt.z = 1.0;
	viewport[id].pln   = VIEW_XY_PLANE;
	viewport[id].pmax  = 0.0;

/*	クリッピングの初期化	*/
	viewport[id].cmin.x = -1.0;
	viewport[id].cmin.y = -1.0; 
	viewport[id].cmin.z = -1.0;
	viewport[id].cmax.x =  1.0;
	viewport[id].cmax.y =  1.0; 
	viewport[id].cmax.z =  1.0;

	return( 1 );
}

/*	光源の設定	*/
int		ViewSetLight(p,s,mode,cid,id)
Vpoint	*p;
float	s;
int		mode,cid,id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	viewlight[id].mode = mode;

	if (mode == VIEW_LIGHT_SELF) {
		viewlight[id].p.x  = p->x;
		viewlight[id].p.y  = p->y;
		viewlight[id].p.z  = p->z;
		viewlight[id].s    = s;
		viewlight[id].cid  = cid;
	}else{
		viewlight[id].s    = 1.0;
		viewlight[id].cid  = 1;
	}

	return( 1 );
}

/*	背景色の設定	*/
int		ViewSetBackground(colorid,bright,id)
int		colorid,bright,id;
{
    Display *disp;
    Window  win;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;

	XSetWindowBackground(disp,win,viewcolor[id][colorid].color[bright].pixel);

	XClearWindow(disp,win);

	XFlush(disp);

	return( 1 );
}

/*	カラーテーブルの作成	*/
int		ViewSetColor(color,colorid,bright,id)
Vcolor	*color;
int		colorid,bright,id;
{
    Display *disp;
	int			i;
	float		r,g,b;
	float		dr,dg,db;
    Colormap    cmap;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    disp = viewdisp[id].disp;

	if (bright > VIEW_MAX_BRIGHT || bright < 1) return( - 1 );

    cmap = DefaultColormap(disp,0);

	r = color->r * MCN;
	g = color->g * MCN;
	b = color->b * MCN;

	dr = r / (float)bright;
	dg = g / (float)bright;
	db = b / (float)bright;

    viewcolor[id][colorid].bright = bright;

	for (i = 0;i < bright;i ++) {
    	viewcolor[id][colorid].color[i].red   = (long)(r - dr * i);
    	viewcolor[id][colorid].color[i].green = (long)(g - dg * i);
    	viewcolor[id][colorid].color[i].blue  = (long)(b - db * i);
		XAllocColor(disp,cmap,&viewcolor[id][colorid].color[i]);
	}

	return( 1 );
}

/*	陰線処理モードの設定	*/
int		ViewSetZbuffer(mode,id)
int		mode,id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	viewattr[id].zbuff = mode;

	return( 1 );
}

/*	陰影処理モードの設定	*/
int		ViewSetShading(mode,id)
int		mode,id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	viewattr[id].shade = mode;

	return( 1 );
}

/*	クリッピングの設定	*/
int		ViewSetClip(min,max,id)
Vpoint	*min,*max;
int		id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	viewport[id].cmin.x = min->x;
	viewport[id].cmin.y = min->y; 
	viewport[id].cmin.z = min->z;
	viewport[id].cmax.x = max->x;
	viewport[id].cmax.y = max->y; 
	viewport[id].cmax.z = max->z;

	viewattr[id].clip  = VIEW_CLIP_ON; 	/*	1994.5.26 追加 */

	return( 1 );
}

/*	クリッピングの判定	*/
int		ViewClipPoint(p,n,id)
Vpoint	*p;
int		n;
int		id;
{
	int		i;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( -1 );

	if (viewattr[id].clip != VIEW_CLIP_ON) return( 1 ); /*  1994.5.26 追加 */

	for (i = 0;i < n;i ++) {
		if (p[i].x < viewport[id].cmin.x || p[i].x > viewport[id].cmax.x ||
		    p[i].y < viewport[id].cmin.y || p[i].y > viewport[id].cmax.y ||
		    p[i].z < viewport[id].cmin.z || p[i].z > viewport[id].cmax.z) {
			return ( -1 );
		}
	}

	return( 1 );
}

/*	ビューポートの設定	*/
int		ViewSetViewportWindow(min,max,ref,id)
Vpoint	*min,*max,*ref;
int		id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

/*	最大値	*/
	viewport[id].max.x = max->x;
	viewport[id].max.y = max->y;
	viewport[id].max.z = max->z;

/*	最小値	*/
	viewport[id].min.x = min->x;
	viewport[id].min.y = min->y;
	viewport[id].min.z = min->z;

/*	参照点	*/
	viewport[id].ref.x = ref->x;
	viewport[id].ref.y = ref->y;
	viewport[id].ref.z = ref->z;

	viewport[id].cmin.x = min->x;
	viewport[id].cmin.y = min->y; 
	viewport[id].cmin.z = min->z;
	viewport[id].cmax.x = max->x;
	viewport[id].cmax.y = max->y; 
	viewport[id].cmax.z = max->z;

	return( 1 );
}

/*	３次元座標から２次元座標へ変換	*/
void    ViewRotatePoint(rtx,rty,x0,y0,z0,rx,ry,rz,id)
float   *rtx,*rty,x0,y0,z0,rx,ry,rz;
int		id;
{
    float   x1,y1,z1,x2,y2,z2,x3,y3,z3;

	x0 *= viewport[id].zoom.x;
	y0 *= viewport[id].zoom.y;
	z0 *= viewport[id].zoom.z;

	switch(viewport[id].pln) {
		case	VIEW_XY_PLANE:
		case	VIEW_YX_PLANE:
		case	VIEW_ZX_PLANE:
		case	VIEW_XZ_PLANE:
    		x1 =   x0 * cos((double)ry) + z0 * sin((double)ry);
    		y1 =   y0;
    		z1 =   z0 * cos((double)ry) - x0 * sin((double)ry);
    		x2 =   x1;
    		y2 =   y1 * cos((double)rx) - z1 * sin((double)rx);
    		z2 =   z1 * cos((double)rx) + y1 * sin((double)rx);
    		x3 =   x2 * cos((double)rz) - y2 * sin((double)rz);
    		y3 =   y2 * cos((double)rz) + x2 * sin((double)rz);
    		z3 =   z2;
			break;
		case	VIEW_YZ_PLANE:
		case	VIEW_ZY_PLANE:
    		x1 =   x0;
    		y1 =   y0 * cos((double)rx) - z0 * sin((double)rx);
  			z1 =   z0 * cos((double)rx) + y0 * sin((double)rx);
    		x2 =   x1 * cos((double)rz) - y1 * sin((double)rz);
    		y2 =   y1 * cos((double)rz) + x1 * sin((double)rz);
    		z2 =   z1;
    		x3 =   x2 * cos((double)ry) + z2 * sin((double)ry);
    		y3 =   y2;
    		z3 =   z2 * cos((double)ry) - x2 * sin((double)ry);
			break;
        default:
            fprintf(stderr,"Error : undefined plane id\n");
    		x1 =   x0 * cos((double)0.0) + z0 * sin((double)0.0);
    		y1 =   y0;
    		z1 =   z0 * cos((double)0.0) - x0 * sin((double)0.0);
    		x2 =   x1;
    		y2 =   y1 * cos((double)0.0) - z1 * sin((double)0.0);
    		z2 =   z1 * cos((double)0.0) + y1 * sin((double)0.0);
    		x3 =   x2 * cos((double)0.0) - y2 * sin((double)0.0);
    		y3 =   y2 * cos((double)0.0) + x2 * sin((double)0.0);
    		z3 =   z2;
			viewport[id].pln = VIEW_XY_PLANE;
			break;
	}

	switch(viewport[id].pln) {
		case	VIEW_XY_PLANE:
    		*rtx = x3;
    		*rty = y3;
			break;
		case	VIEW_YX_PLANE:
    		*rtx = y3;
    		*rty = x3;
			break;
		case	VIEW_YZ_PLANE:
    		*rtx = y3;
    		*rty = z3;
			break;
		case	VIEW_ZY_PLANE:
    		*rtx = z3;
    		*rty = y3;
			break;
		case	VIEW_ZX_PLANE:
    		*rtx = z3;
    		*rty = x3;
			break;
		case	VIEW_XZ_PLANE:
    		*rtx = x3;
    		*rty = z3;
			break;
        default:
            fprintf(stderr,"Error : undefined plane id\n");
    		*rtx = x3;
    		*rty = y3;
			viewport[id].pln = VIEW_XY_PLANE;
			break;
	}
}

/*	実座標（２次元）からウインドウ座標へ変換	*/
void    ViewWindowPoint(rx,ry,x,y,id)
float   *rx,*ry,x,y;
int		id;
{
    float   vs,refx,refy;
    int     ws,ox,oy;
	float	sx,sy,sz;

	ws = ViewUtilMin((float)viewport[id].width,(float)viewport[id].height);

	ox = viewport[id].width  / 2;
	oy = viewport[id].height / 2;

	sx = fabs(viewport[id].max.x - viewport[id].min.x);
	sy = fabs(viewport[id].max.y - viewport[id].min.y);
	sz = fabs(viewport[id].max.z - viewport[id].min.z);

	vs = ViewUtilMax(sx,sy);
	vs = ViewUtilMax(vs,sz);

	ViewRotatePoint(&refx,&refy,
		viewport[id].ref.x,viewport[id].ref.y,viewport[id].ref.z,
		viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);

	*rx = x / vs * ws - refx / vs * ws + ox;
	*ry = viewport[id].height 
		- y / vs * ws + refy / vs * ws - oy;

	*rx += viewport[id].move.nx;
	*ry += viewport[id].move.ny;

}

/*	倍率の設定		*/
int		ViewSetZoom(rp,id)
Vpoint	*rp;
int		id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	viewport[id].zoom.x = rp->x;
	viewport[id].zoom.y = rp->y;
	viewport[id].zoom.z = rp->z;

	return( 1 );
}

/*	移動量の設定		*/
int		ViewSetMove(nx,ny,id)
int		nx,ny;
int		id;
{
	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	viewport[id].move.nx = nx;
	viewport[id].move.ny = ny;

	return( 1 );
}

/*	回転角の設定	*/
int		ViewSetRotateWindow(r1,r2,pln,id)
float	r1,r2;
int		pln;
int		id;
{
	Vpoint	sp0,sp,fp;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );
	
	viewport[id].pln = pln;

	switch(pln) {
		case	VIEW_XY_PLANE:
			viewport[id].rot.x =   r1;
			viewport[id].rot.y = - r2;
			viewport[id].rot.z =   0.0; 
			viewport[id].pnt.x =   cos(r1) * sin(r2);
			viewport[id].pnt.y =   sin(r1);
			viewport[id].pnt.z =   cos(r1) * cos(r2);
			break;
		case	VIEW_YX_PLANE:
			viewport[id].rot.x = - r2;
			viewport[id].rot.y =   r1;
			viewport[id].rot.z =   0.0; 
			viewport[id].pnt.x =   cos(r2) * sin(r1);
			viewport[id].pnt.y =   sin(r2);
			viewport[id].pnt.z = - cos(r2) * cos(r1);
			break;
		case	VIEW_YZ_PLANE:
			viewport[id].rot.x =   0.0; 
			viewport[id].rot.y =   r1;
			viewport[id].rot.z = - r2;
			viewport[id].pnt.x =   cos(r1) * cos(r2);
			viewport[id].pnt.y =   cos(r1) * sin(r2);
			viewport[id].pnt.z =   sin(r1);
			break;
		case	VIEW_ZY_PLANE:
			viewport[id].rot.x =   0.0; 
			viewport[id].rot.y = - r2;
			viewport[id].rot.z =   r1;
			viewport[id].pnt.x = - cos(r2) * cos(r1);
			viewport[id].pnt.y =   cos(r2) * sin(r1);
			viewport[id].pnt.z =   sin(r2);
			break;
		case	VIEW_ZX_PLANE:
			viewport[id].rot.x = - r2;
			viewport[id].rot.y =   0.0; 
			viewport[id].rot.z =   r1;
			viewport[id].pnt.x =   sin(r1);
			viewport[id].pnt.y =   cos(r1) * cos(r2);
			viewport[id].pnt.z =   cos(r1) * sin(r2);
			break;
		case	VIEW_XZ_PLANE:
			viewport[id].rot.x =   r1;
			viewport[id].rot.y =   0.0; 
			viewport[id].rot.z = - r2;
			viewport[id].pnt.x =   sin(r2);
			viewport[id].pnt.y = - cos(r2) * cos(r1);
			viewport[id].pnt.z =   cos(r2) * sin(r1);
			break;
		default:
			fprintf(stderr,"Error: undefined plane id\n");
            viewport[id].rot.x =   0.0;
            viewport[id].rot.y =   0.0;
            viewport[id].rot.z =   0.0;
            viewport[id].pnt.x =   cos((double)0.0) * sin((double)0.0);
            viewport[id].pnt.y =   sin((double)0.0);
            viewport[id].pnt.z =   cos((double)0.0) * cos((double)0.0);
			viewport[id].pln   = VIEW_XY_PLANE;
			break;
	}

	return( 1 );
}

/*	ウインドウのクリア	*/
int		ViewClearWindow(id)
int		id;
{
    Display *disp;
    Window  win;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;

	XClearWindow(disp,win);

	XFlush(disp);

	return( 1 );
}

/*	点列の作成	*/
int		ViewSetPoint(p,n,att,cid,id)
Vpoint	*p;
int		n,att,cid,id;
{
	int		i;
	int		st;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	if (ViewAddAllocWindow(id) < 0) return( -1 );

	st = viewdraw_num[id];

	viewdraw[id][st].type     = VIEW_POINT;
	viewdraw[id][st].att      = att;
	viewdraw[id][st].c_number = cid;
	viewdraw[id][st].p_number = n;

	viewdraw[id][st].point = (Vpoint *)malloc(sizeof(Vpoint) * n);

	for (i = 0;i < n;i ++) {
		viewdraw[id][st].point[i].x = p->x;
		viewdraw[id][st].point[i].y = p->y;
		viewdraw[id][st].point[i].z = p->z;
		if (viewport[id].pmax < fabs(p->x)) viewport[id].pmax = fabs(p->x);
		if (viewport[id].pmax < fabs(p->y)) viewport[id].pmax = fabs(p->y);
		if (viewport[id].pmax < fabs(p->z)) viewport[id].pmax = fabs(p->z);
		p ++;
	}

	if (viewattr[id].dmode == VIEW_DRAW_INTC) {
		ViewDrawPoint(id,viewdraw_num[id]);
		return( 1 );
	}

	viewdraw_num[id] ++;

	return( 1 );
}

/*	点列の表示	*/
int		ViewDrawPoint(id,st)
int		id,st;
{
    Display *disp;
    Window  win;
    GC      gc;

	int		i;
	float	x0,y0,z0;
	float	px0,py0,rx0,ry0;

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;
    gc   = viewdisp[id].gc;

    XSetForeground(disp,gc,viewcolor[id][viewdraw[id][st].c_number].color[0].pixel);

	XSetLineAttributes(disp,gc,1,LineSolid,CapButt,JoinMiter);

	for (i = 0;i < viewdraw[id][st].p_number;i ++) {

		if (ViewClipPoint(&viewdraw[id][st].point[i],1,id) < 0) return ( 1 );

		x0 = viewdraw[id][st].point[i].x;
		y0 = viewdraw[id][st].point[i].y;
		z0 = viewdraw[id][st].point[i].z;

		ViewRotatePoint(&px0,&py0,x0,y0,z0,
        	viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);

		ViewWindowPoint(&rx0,&ry0,px0,py0,id);

		switch(viewdraw[id][st].att) {

			case	VIEW_POINT_ARC:
				XDrawArc(disp,win,gc,(int)rx0-4,(int)ry0-4,8,8,0,360*64);
				break;

			case	VIEW_POINT_FILL:
				XFillArc(disp,win,gc,(int)rx0-4,(int)ry0-4,8,8,0,360*64);
				break;

			default:
				XDrawPoint(disp,win,gc,(int)rx0,(int)ry0);
				break;
		}
	}
}
int		ViewSetArc(p,n,att,cid,id)
Vpoint	*p;
int		n,att,cid,id;
{	
	int		i;
	int		st;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	if (ViewAddAllocWindow(id) < 0) return( -1 );

	st = viewdraw_num[id];

	viewdraw[id][st].type     = VIEW_ARC;
	viewdraw[id][st].att      = att;
	viewdraw[id][st].c_number = cid;
	viewdraw[id][st].p_number = n;

	viewdraw[id][st].point = (Vpoint *)malloc(sizeof(Vpoint) * n);

	for (i = 0;i < n;i ++) {
		viewdraw[id][st].point[i].x = p->x;
		viewdraw[id][st].point[i].y = p->y;
		viewdraw[id][st].point[i].z = p->z;
		if (viewport[id].pmax < fabs(p->x)) viewport[id].pmax = fabs(p->x);
		if (viewport[id].pmax < fabs(p->y)) viewport[id].pmax = fabs(p->y);
		if (viewport[id].pmax < fabs(p->z)) viewport[id].pmax = fabs(p->z);
		p ++;
	}

	if (viewattr[id].dmode == VIEW_DRAW_INTC) {
		ViewDrawArc(id,viewdraw_num[id]);
		return( 1 );
	}

	viewdraw_num[id] ++;

	return( 1 );
}						

int		ViewDrawArc(id,st)
int		id,st;
{
    Display *disp;
    Window  win;
    GC      gc;
	int		i,j;
	float	r,c;
	Vpoint	rp;
	Vpoint	u1,u2,u3,u4;
	Vpoint	d[2];
	float	x0,y0,z0,x1,y1,z1;
	float	px0,py0,rx0,ry0;
	float	px1,py1,rx1,ry1;
	float	prx,pry,rrx,rry;
	XPoint	dr[3];

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;
    gc   = viewdisp[id].gc;

	XSetForeground(disp,gc,viewcolor[id][viewdraw[id][st].c_number].color[0].pixel);

	if (ViewUtilArcCenter(&rp,&r,viewdraw[id][st].point) < 0) return( -1 );

	ViewRotatePoint(&prx,&pry,rp.x,rp.y,rp.z,
       	viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);

	ViewWindowPoint(&rrx,&rry,prx,pry,id);

	u1.x = (viewdraw[id][st].point[0].x - rp.x) / r;
	u1.y = (viewdraw[id][st].point[0].y - rp.y) / r;
	u1.z = (viewdraw[id][st].point[0].z - rp.z) / r;

	u2.x = (viewdraw[id][st].point[2].x - rp.x) / r;
	u2.y = (viewdraw[id][st].point[2].y - rp.y) / r;
	u2.z = (viewdraw[id][st].point[2].z - rp.z) / r;

	c = u2.x * u1.x + u2.y * u1.y + u2.z * u1.z;

	u3.x = u2.x - c * u1.x;
	u3.y = u2.y - c * u1.y;
	u3.z = u2.z - c * u1.z;
	
	ViewUtilVector(&u4,&u3);
	
	for (i = 0;i < 48;i ++) {
		j = i + 1;
		x0 = r * cos(i * VIEW_PI / 24) * u1.x 
		   + r * sin(i * VIEW_PI / 24) * u4.x
		   + rp.x;
		y0 = r * cos(i * VIEW_PI / 24) * u1.y 
		   + r * sin(i * VIEW_PI / 24) * u4.y
		   + rp.y;
		z0 = r * cos(i * VIEW_PI / 24) * u1.z 
		   + r * sin(i * VIEW_PI / 24) * u4.z
		   + rp.z;
		x1 = r * cos(j * VIEW_PI / 24) * u1.x 
		   + r * sin(j * VIEW_PI / 24) * u4.x
		   + rp.x;
		y1 = r * cos(j * VIEW_PI / 24) * u1.y 
		   + r * sin(j * VIEW_PI / 24) * u4.y
		   + rp.y;
		z1 = r * cos(j * VIEW_PI / 24) * u1.z 
		   + r * sin(j * VIEW_PI / 24) * u4.z
		   + rp.z;

		ViewRotatePoint(&px0,&py0,x0,y0,z0,
        	viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);
		ViewRotatePoint(&px1,&py1,x1,y1,z1,
        	viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);

		ViewWindowPoint(&rx0,&ry0,px0,py0,id);
		ViewWindowPoint(&rx1,&ry1,px1,py1,id);

		switch(viewdraw[id][st].att) {
			case	1:
				dr[0].x = rx0;
				dr[0].y = ry0;
				dr[1].x = rx1;
				dr[1].y = ry1;
				dr[2].x = rrx;
				dr[2].y = rry;
				XFillPolygon(disp,win,gc,dr,3,Convex,CoordModeOrigin);
				break;
			
			default	:
				XDrawLine(disp,win,gc,(int)rx0,(int)ry0,(int)rx1,(int)ry1);
				break;
		}
	}
}
		
int		ViewSetLine(p,n,att,cid,id)
Vpoint	*p;
int		n,att,cid,id;
{	
	int		i;
	int		st;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	if (ViewAddAllocWindow(id) < 0) return( -1 );

	st = viewdraw_num[id];

	viewdraw[id][st].type     = VIEW_LINE;
	viewdraw[id][st].att      = att;
	viewdraw[id][st].c_number = cid;
	viewdraw[id][st].p_number = n;

	viewdraw[id][st].point = (Vpoint *)malloc(sizeof(Vpoint) * n);

	for (i = 0;i < n;i ++) {
		viewdraw[id][st].point[i].x = p->x;
		viewdraw[id][st].point[i].y = p->y;
		viewdraw[id][st].point[i].z = p->z;
		if (viewport[id].pmax < fabs(p->x)) viewport[id].pmax = fabs(p->x);
		if (viewport[id].pmax < fabs(p->y)) viewport[id].pmax = fabs(p->y);
		if (viewport[id].pmax < fabs(p->z)) viewport[id].pmax = fabs(p->z);
		p ++;
	}

	if (viewattr[id].dmode == VIEW_DRAW_INTC) {
		ViewDrawLine(id,viewdraw_num[id]);
		return( 1 );
	}

	viewdraw_num[id] ++;

	return( 1 );
}						
							
int		ViewDrawLine(id,st)
int		id,st;
{
    Display *disp;
    Window  win;
    GC      gc;

	int		i;
	float	x0,y0,z0,x1,y1,z1;
	float	px0,py0,rx0,ry0;
	float	px1,py1,rx1,ry1;

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;
    gc   = viewdisp[id].gc;

	if (ViewClipPoint(viewdraw[id][st].point,
		viewdraw[id][st].p_number - 1,id) < 0) return ( 1 );

	XSetForeground(disp,gc,viewcolor[id][viewdraw[id][st].c_number].color[0].pixel);

	switch(viewdraw[id][st].att) {

		case	VIEW_WIRE:

			XSetLineAttributes(disp,gc,1,LineOnOffDash,CapButt,JoinMiter);
			break;

		default:
			XSetLineAttributes(disp,gc,1,LineSolid,CapButt,JoinMiter);
	}

	for (i = 0;i < viewdraw[id][st].p_number - 1;i ++) {

		x0 = viewdraw[id][st].point[i].x;
		y0 = viewdraw[id][st].point[i].y;
		z0 = viewdraw[id][st].point[i].z;
		x1 = viewdraw[id][st].point[i+1].x;
		y1 = viewdraw[id][st].point[i+1].y;
		z1 = viewdraw[id][st].point[i+1].z;

		ViewRotatePoint(&px0,&py0,x0,y0,z0,
        	viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);
		ViewRotatePoint(&px1,&py1,x1,y1,z1,
        	viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);

		ViewWindowPoint(&rx0,&ry0,px0,py0,id);
		ViewWindowPoint(&rx1,&ry1,px1,py1,id);

		XDrawLine(disp,win,gc,(int)rx0,(int)ry0,(int)rx1,(int)ry1);
	}

	return( 1 );
}

int		ViewSetPolygon(p,n,att,cid,id)
Vpoint	*p;
int		n,att,cid,id;
{	
	int		i;
	int		st;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	if (ViewAddAllocWindow(id) < 0) return( -1 );

	st = viewdraw_num[id];

	viewdraw[id][st].type     = VIEW_POLYGON;
	viewdraw[id][st].att      = att;
	viewdraw[id][st].c_number = cid;
	viewdraw[id][st].p_number = n;

	viewdraw[id][st].point = (Vpoint *)malloc(sizeof(Vpoint) * n);

	for (i = 0;i < n;i ++) {
		viewdraw[id][st].point[i].x = p->x;
		viewdraw[id][st].point[i].y = p->y;
		viewdraw[id][st].point[i].z = p->z;
		if (viewport[id].pmax < fabs(p->x)) viewport[id].pmax = fabs(p->x);
		if (viewport[id].pmax < fabs(p->y)) viewport[id].pmax = fabs(p->y);
		if (viewport[id].pmax < fabs(p->z)) viewport[id].pmax = fabs(p->z);
		p ++;
	}

	if (viewattr[id].dmode == VIEW_DRAW_INTC) {
		ViewDrawPolygon(id,viewdraw_num[id]);
		return( 1 );
	}

	viewdraw_num[id] ++;

	return( 1 );
}						
int		ViewDrawPolygon(id,st)
int		id,st;
{
    Display *disp;
    Window  win;
    GC      gc;

	int		i,j,k;
	Vpoint	vp,vp0;
	Vpoint	pp[VIEW_MAX_POINT+1],rpp;
	float	x0,y0,z0;
	float	px0,py0;
	float	rx0,ry0;
	float	inner;
	XPoint	pt[VIEW_MAX_POINT+1];
	int		brid;
	Pixmap	p;

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;
    gc   = viewdisp[id].gc;

	if (ViewClipPoint(viewdraw[id][st].point,
		viewdraw[id][st].p_number,id) < 0) return ( 1 );

	if (viewlight[id].mode == VIEW_LIGHT_DPND) {
		vp0.x = - viewport[id].pnt.x;
		vp0.y = - viewport[id].pnt.y;
		vp0.z = - viewport[id].pnt.z;
	}else{
		vp0.x = - viewlight[id].p.x;
		vp0.y = - viewlight[id].p.y;
		vp0.z = - viewlight[id].p.z;
	}

	ViewUtilVector(&vp,&vp0);

	for (i = 0;i < viewdraw[id][st].p_number;i ++) {
		x0 = viewdraw[id][st].point[i].x;
		y0 = viewdraw[id][st].point[i].y;
		z0 = viewdraw[id][st].point[i].z;

		pp[i].x = x0;
		pp[i].y = y0;
		pp[i].z = z0;

		ViewRotatePoint(&px0,&py0,x0,y0,z0,
        	viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);
		ViewWindowPoint(&rx0,&ry0,px0,py0,id);

		pt[i].x = (int)rx0;
		pt[i].y = (int)ry0;

		if (i == 0) {
			pt[viewdraw[id][st].p_number].x = (int)rx0;
			pt[viewdraw[id][st].p_number].y = (int)ry0;
		}
	}

	switch(viewattr[id].shade) {

		case	VIEW_SHADE_ON:
			ViewUtilNormal(pp,&rpp);
			inner = fabs(ViewUtilInnerAngle(&rpp,&vp));
			brid = viewcolor[id][viewdraw[id][st].c_number].bright 
				 * (1.0 - inner) - 1;
			if (brid < 0) brid = 0;
			XSetForeground(disp,gc,
                viewcolor[id][viewdraw[id][st].c_number].color[brid].pixel);
			break;

		default:
			XSetForeground(disp,gc,
				viewcolor[id][viewdraw[id][st].c_number].color[0].pixel);
	}

	switch(viewdraw[id][st].att) {

		case	VIEW_WIRE:
			XDrawLines(disp,win,gc,
                pt,viewdraw[id][st].p_number + 1,CoordModeOrigin);
			break;

		default:
			XFillPolygon(disp,win,gc,
				pt,viewdraw[id][st].p_number,Convex,CoordModeOrigin);
	}
}
		
int		ViewSetText(p,text,font,cid,id)
Vpoint	*p;
char	*text,*font;
int		cid,id;
{	
	int		i;
	int		st;

	if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

	if (ViewAddAllocWindow(id) < 0) return( -1 );

	st = viewdraw_num[id];

	viewdraw[id][st].type     = VIEW_TEXT;
	viewdraw[id][st].c_number = cid;

	strcpy(viewdraw[id][st].font,font);
	strcpy(viewdraw[id][st].text,text);

	viewdraw[id][st].point = (Vpoint *)malloc(sizeof(Vpoint) * 1);

	viewdraw[id][st].point[0].x = p->x;
	viewdraw[id][st].point[0].y = p->y;
	viewdraw[id][st].point[0].z = p->z;
	if (viewport[id].pmax < fabs(p->x)) viewport[id].pmax = fabs(p->x);
	if (viewport[id].pmax < fabs(p->y)) viewport[id].pmax = fabs(p->y);
	if (viewport[id].pmax < fabs(p->z)) viewport[id].pmax = fabs(p->z);

	if (viewattr[id].dmode == VIEW_DRAW_INTC) {
		ViewDrawText(id,viewdraw_num[id]);
		return( 1 );
	}

	viewdraw_num[id] ++;

	return( 1 );
}						

int		ViewDrawText(id,st)
int		id,st;
{
    Display *disp;
    Window  win;
    GC      gc;

    float   px0,py0;
    float   rx0,ry0;
    float   x0,y0,z0;
    Font    font;

    disp = viewdisp[id].disp;
    win  = viewdisp[id].win;
    gc   = viewdisp[id].gc;

	if (ViewClipPoint(&viewdraw[id][st].point[0],1,id) < 0) return ( 1 );

	x0 = viewdraw[id][st].point[0].x; 
	y0 = viewdraw[id][st].point[0].y; 
	z0 = viewdraw[id][st].point[0].z; 

    font = XLoadFont(disp,viewdraw[id][st].font);

	ViewRotatePoint(&px0,&py0,x0,y0,z0,
       	viewport[id].rot.x,viewport[id].rot.y,viewport[id].rot.z,id);
	ViewWindowPoint(&rx0,&ry0,px0,py0,id);

	XSetFont(disp,gc,font);
	XSetForeground(disp,gc,viewcolor[id][viewdraw[id][st].c_number].color[0].pixel);

    XDrawString(disp,win,gc,
        (int)rx0,(int)ry0,viewdraw[id][st].text,strlen(viewdraw[id][st].text)); 
}

void	ViewCreateZbuffer(num,len,id)
int		*num;
float	*len;
int		id;
{
	int		i,j,n;
	float	ln;

	for (i = 0;i < viewdraw_num[id];i ++) {

		num[i] = i;

		switch(viewdraw[id][i].type) {

			case	VIEW_LINE:
			case	VIEW_POLYGON:
			case	VIEW_POINT:
			case	VIEW_ARC:

				ln  = 0.0;
				n  = viewdraw[id][i].p_number;

				for (j = 0;j < n;j ++) {
					ln += ViewUtilDistance(&viewdraw[id][i].point[j],
												&viewport[id].pnt);
				}
				len[i] = ln / n;
				break;

			case	VIEW_TEXT:

				len[i] = ViewUtilDistance(&viewdraw[id][i].point[0],
												&viewport[id].pnt);
				break;

		}
	}
}


int		ViewUpdate(id)
int		id;
{
    Display *disp;

	int		i,j;
	int		*zbuff_num;
	float	*zbuff_len;
    Window          root;
    int             px,py;
    unsigned int    sx,sy,br,dp;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    disp = viewdisp[id].disp;

	if (viewattr[id].dmode == VIEW_DRAW_INTC) {
		XFlush(disp);
		return( 1 );
	}

	ViewGetGeometry(id);

	viewport[id].pnt.x *= viewport[id].pmax * 10.0;
	viewport[id].pnt.y *= viewport[id].pmax * 10.0; 
	viewport[id].pnt.z *= viewport[id].pmax * 10.0;

	switch(viewattr[id].zbuff) {

		case	VIEW_ZBUFF_ON:

			zbuff_num = (int *)malloc(sizeof(int) * viewdraw_size[id] + 1);
			zbuff_len = (float *)malloc(sizeof(float) * viewdraw_size[id] + 1);

			ViewCreateZbuffer(zbuff_num,zbuff_len,id);

			ViewUtilQuickSort(zbuff_num,zbuff_len,0,viewdraw_num[id] - 1);

			for (i = 0;i < viewdraw_num[id];i ++) {

				switch(viewdraw[id][zbuff_num[i]].type) {
					case	VIEW_LINE:	
						ViewDrawLine(id,zbuff_num[i]);
						break;
					case	VIEW_POLYGON:	
						ViewDrawPolygon(id,zbuff_num[i]);
						break;
					case	VIEW_TEXT:	
						ViewDrawText(id,zbuff_num[i]);
						break;
					case	VIEW_POINT:	
						ViewDrawPoint(id,zbuff_num[i]);
						break;
					case	VIEW_ARC:	
						ViewDrawArc(id,i);
						break;
				}
			}

			break;

		default:

			for (i = 0;i < viewdraw_num[id];i ++) {
				switch(viewdraw[id][i].type) {
					case	VIEW_LINE:	
						ViewDrawLine(id,i);
						break;
					case	VIEW_POLYGON:	
						ViewDrawPolygon(id,i);
						break;
					case	VIEW_TEXT:	
						ViewDrawText(id,i);
						break;
					case	VIEW_POINT:	
						ViewDrawPoint(id,i);
						break;
					case	VIEW_ARC:	
						ViewDrawArc(id,i);
						break;
				}
			}
	}

	XFlush(disp);

	return( 1 );
}


