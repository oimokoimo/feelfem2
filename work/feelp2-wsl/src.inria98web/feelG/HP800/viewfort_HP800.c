/************************************************************************/
/*                                                                      */
/* View ver 2.0                                                         */
/* viewfort.c                                                           */
/* Copy rights - all rights reserved by NEC                             */
/*                                                                      */
/************************************************************************/

#include "view.h"

/*	£Ö£é£å£÷´ðËÜ¥é¥¤¥Ö¥é¥ê		*/

vopw(x,y,w,h,mg,id)
int	*x,*y,*w,*h,*mg,*id;
{
	ViewOpenWindow(*x,*y,*w,*h,*mg,*id);
}

vmpw(id)
int    *id;
{
       ViewMapWindow(*id);
}

vsbs(nf,id )
int	*nf,*id;
{
	ViewSetBackingStore(*nf,*id);
}

valw(sz,id)
int	*sz,*id;
{
	ViewAllocWindow(*sz,*id);
}

vclw(id)
int	*id;
{
	ViewClearWindow(*id);
}

vsrw(rt,rh,np,id)
double	*rt,*rh;
int	*np,*id;
{
	float	rrt,rrh;

	rrt = (float)*rt;
	rrh = (float)*rh;

	ViewSetRotateWindow(rrt,rrh,*np,*id);
}

vupd(id)
int	*id;
{
	ViewUpdate(*id);
}

vsbg(mc,id)
int	*mc,*id;
{
	ViewSetBackground(*mc,0,*id);
}

vslt(x,y,z,s,m,c,id)
double	*x,*y,*z,*s;
int	*m,*c,*id;
{
	Vpoint	p;
	float	rs;

	p.x = (float)(*x);
	p.y = (float)(*y);
	p.z = (float)(*z);

	rs = (float)(*s);

	ViewSetLight(&p,rs,*m,*c,*id);
}

vdlw(id)
int	*id;
{
	ViewDeleteWindow(*id);
}

vsvw(xmin,ymin,zmin,xmax,ymax,zmax,xref,yref,zref,id)
double	*xmin,*ymin,*zmin,*xmax,*ymax,*zmax,*xref,*yref,*zref;
int	*id;
{
	Vpoint	min,max,ref;

	min.x = (float)*xmin; 
	min.y = (float)*ymin; 
	min.z = (float)*zmin;
	max.x = (float)*xmax; 
	max.y = (float)*ymax; 
	max.z = (float)*zmax;
	ref.x = (float)*xref; 
	ref.y = (float)*yref; 
	ref.z = (float)*zref;

	ViewSetViewportWindow(&min,&max,&ref,*id);
}

vint(id)
int	*id;
{
	ViewInitialize(*id);
}

vinc(id)
int	*id;
{
	ViewInitializeColor(*id);
}

vscl(r,g,b,cid,nb,id)
double	*r,*g,*b;
int	*cid,*nb,*id;
{
	Vcolor	c;

	c.r = (float)*r; 
	c.g = (float)*g; 
	c.b = (float)*b;

	ViewSetColor(&c,*cid,*nb,*id);
}

vszb(mode,id)
int	*mode,*id;
{
	ViewSetZbuffer(*mode,*id);
}

vssd(mode,id)
int	*mode,*id;
{
	ViewSetShading(*mode,*id);
}

vspt(x,y,z,n,nf,cid,id)
double	*x,*y,*z;
int	*n,*nf,*cid,*id;
{
	int	i;
	Vpoint	*p;

	p = (Vpoint *)malloc(sizeof(Vpoint) * (*n));
	if (p == (Vpoint *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *n;i ++) {
		p[i].x = (float)*x; 
		p[i].y = (float)*y; 
		p[i].z = (float)*z;
		x ++;        
		y ++;        
		z ++;
	}

	ViewSetPoint(p,*n,*nf,*cid,*id);

	free(p);
}

vsln(x,y,z,n,nf,cid,id)
double	*x,*y,*z;
int	*n,*nf,*cid,*id;
{
	int	i;
	Vpoint	*p;

	p = (Vpoint *)malloc(sizeof(Vpoint) * (*n));
	if (p == (Vpoint *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *n;i ++) {
		p[i].x = (float)*x; 
		p[i].y = (float)*y; 
		p[i].z = (float)*z;
		x ++;        
		y ++;        
		z ++;
	}

	ViewSetLine(p,*n,*nf,*cid,*id);
	free(p);
}

vspg(x,y,z,n,nf,cid,id)
double	*x,*y,*z;
int	*n,*nf,*cid,*id;
{
	int	i;
	Vpoint	*p;

	p = (Vpoint *)malloc(sizeof(Vpoint) * (*n));
	if (p == (Vpoint *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *n;i ++) {
		p[i].x = (float)*x; 
		p[i].y = (float)*y; 
		p[i].z = (float)*z;
		x ++;        
		y ++;        
		z ++;
	}

	ViewSetPolygon(p,*n,*nf,*cid,*id);
	free(p);
}

vstx(x,y,z,text,font,cid,id)
double	*x,*y,*z;
char	*text,*font;
int	*cid,*id;
{
	Vpoint	p;

	p.x = (float)*x; 
	p.y = (float)*y; 
	p.z = (float)*z;

	ViewSetText(&p,text,font,*cid,*id);
}

vszm(x,y,z,id)
double	*x,*y,*z;
int	*id;
{
	Vpoint	p;

	p.x = (float)(*x);
	p.y = (float)(*y);
	p.z = (float)(*z);

	ViewSetZoom(&p,*id);
}

vsmv(x,y,id)
int	*x,*y,*id;
{
	ViewSetMove(*x,*y,*id);
}

vscp( xmin , ymin , zmin , xmax , ymax , zmax , id )
double	*xmin,*ymin,*zmin,*xmax,*ymax,*zmax;
int	*id;
{
	Vpoint	min,max;

	min.x = *xmin; min.y = *ymin; min.z = *zmin;
	max.x = *xmax; max.y = *ymax; max.z = *zmax;

	ViewSetClip(&min,&max,*id);
}

/*	£Ö£é£å£÷»Ù±ç¥é¥¤¥Ö¥é¥ê		*/

vuvt(ox,oy,oz,ix,iy,iz)
double	*ox,*oy,*oz,*ix,*iy,*iz;
{
	Vpoint	out,in;

	in.x = (float)*ix; 
	in.y = (float)*iy; 
	in.z = (float)*iz;

	ViewUtilVector(&out,&in);

	*ox = (double)out.x; 
	*oy = (double)out.y; 
	*oz = (double)out.z;
}

vudt(px1,py1,pz1,px2,py2,pz2,d)
double	*px1,*py1,*pz1,*px2,*py2,*pz2,*d;
{
	Vpoint	p1,p2;

	p1.x = (float)*px1; 
	p1.y = (float)*py1; 
	p1.z = (float)*pz1;
	p2.x = (float)*px2; 
	p2.y = (float)*py2; 
	p2.z = (float)*pz2;

	*d = ViewUtilDistance(&p1,&p2);
}

vuip(px1,py1,pz1,px2,py2,pz2,v)
double	*px1,*py1,*pz1,*px2,*py2,*pz2,*v;
{
	Vpoint	p1,p2;

	p1.x = (float)*px1; 
	p1.y = (float)*py1; 
	p1.z = (float)*pz1;
	p2.x = (float)*px2; 
	p2.y = (float)*py2; 
	p2.z = (float)*pz2;

	*v = ViewUtilInnerProduct(&p1,&p2);
}

vunr(ix,iy,iz,ox,oy,oz)
double	*ix,*iy,*iz,*ox,*oy,*oz;
{
	Vpoint	out,in;

	in.x = (float)*ix; 
	in.y = (float)*iy; 
	in.z = (float)*iz;

	ViewUtilNormal(&in,&out);

	*ox = (double)out.x; 
	*oy = (double)out.y; 
	*oz = (double)out.z;
}
	
/*	£Ö£é£å£÷³ÈÄ¥¥é¥¤¥Ö¥é¥ê		*/

vemg(argv,argc,cid,id)
char	argv[100][100];
int	*argc,*cid,*id;
{
	ViewExtMessage(argv,*argc,*cid,*id);
}

veax(cid,id)
int	*cid,*id;
{
	ViewExtAxis(*cid,*id);
}

vets(x,y,z,n,nf,cid,id)
double	*x,*y,*z;
int	*n,*nf,*cid,*id;
{
	int	i;
	Vpoint	*p;

	p = (Vpoint *)malloc(sizeof(Vpoint) * (*n));
	if (p == (Vpoint *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *n;i ++) {
		p[i].x = (float)*x; 
		p[i].y = (float)*y; 
		p[i].z = (float)*z;
		x ++;        
		y ++;        
		z ++;
	}

	ViewExtTriangleStrip(p,*n,*nf,*cid,*id);
	free(p);
}

vetc(x,y,z,s,n,nf,cid,cv,nc,id)
double	*x,*y,*z,*s,*cv;
int	*n,*nf,*cid,*nc,*id;
{
	int		i;
	Vpoint_struct	*p;
	float		*rcv;

	p = (Vpoint_struct *)malloc(sizeof(Vpoint_struct) * (*n));
	if (p == (Vpoint_struct *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *n;i ++) {
		p[i].point.x = (float)*x;
		p[i].point.y = (float)*y;
		p[i].point.z = (float)*z;
		p[i].scalar  = (float)*s;
		x ++; y ++; z ++; s ++;
	}

	rcv = (float *)malloc(sizeof(float) * (*nc));
	if (rcv == (float *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *nc;i ++) {
		rcv[i] = (float)*cv;
		cv ++;
	}

	ViewExtTriangleContour(p,*n,*nf,cid,rcv,*nc,*id);
	free(p);
	free(rcv);
}

veqs(x,y,z,m,n,nf,cid,id)
double	*x,*y,*z;
int	*m,*n,*nf,*cid,*id;
{
        int     i;
        Vpoint  *p;

	p = (Vpoint *)malloc(sizeof(Vpoint) * (*m) * (*n));
	if (p == (Vpoint *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

        for (i = 0;i < (*m) * (*n);i ++) {
                p[i].x = (float)*x; 
		p[i].y = (float)*y; 
		p[i].z = (float)*z;
                x ++;        
		y ++;        
		z ++;
        }

        ViewExtQuadrateStrip(p,*m,*n,*nf,*cid,*id);
	free(p);
}

veqc(x,y,z,s,m,n,nf,cid,cv,nc,id)
double	*x,*y,*z,*s,*cv;
int	*m,*n,*nf,*cid,*nc,*id;
{
	int		i;
	Vpoint_struct	*p;
	float		*rcv;

	p = (Vpoint_struct *)malloc(sizeof(Vpoint_struct) * (*m) * (*n));
	if (p == (Vpoint_struct *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < (*m) * (*n);i ++) {
		p[i].point.x = (float)*x;
		p[i].point.y = (float)*y;
		p[i].point.z = (float)*z;
		p[i].scalar  = (float)*s;
		x ++; 
		y ++; 
		z ++; 
		s ++;
	}

	rcv = (float *)malloc(sizeof(float) * (*nc));
	if (rcv == (float *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *nc;i ++) {
		rcv[i] = (float)*cv;
		cv ++;
	}

	ViewExtQuadrateContour(p,*m,*n,*nf,cid,rcv,*nc,*id);
	free(p);
	free(rcv);
}

vesp(x,y,z,r,n,nf,cid,id)
double	*x,*y,*z,*r;
int	*n,*nf,*cid,*id;
{
	Vpoint	p;
	float	rr;

	p.x = (float)*x; 
	p.y = (float)*y; 
	p.z = (float)*z;
	rr  = (float)*r;

	ViewExtSphere(&p,rr,*n,*nf,*cid,*id);
}

vewt(id)
int	*id;
{
	ViewExtWait(*id);
}

vecb(n,value,fg,mid,cid,id)
double  *value;
int	*n,*fg,*mid,*cid,*id;
{

	float	*rcv;
	int	i;

	rcv = (float *)malloc(sizeof(float) * (*n));
	if (rcv == (float *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *n;i ++) {
		rcv[i] = (float)value[i];
	}

	ViewExtColorBar(*n,rcv,*fg,*mid,cid,*id);
	free(rcv);
}

vecb2(nx,ny,n,value,fg,mid,cid,id)
int     *nx,*ny;
double  *value;
int     *n,*fg,*mid,*cid,*id;
{

        float   *rcv;
        int     i;

        rcv = (float *)malloc(sizeof(float) * (*n));
        if (rcv == (float *)NULL) {
                fprintf(stderr,"cant get memory\n");
                exit(1);
        }

        for (i = 0;i < *n;i ++) {
                rcv[i] = (float)value[i];
        }

        ViewExtColorBar2(*nx,*ny,*n,rcv,*fg,*mid,cid,*id);
	free(rcv);
}


vevt(x,y,z,u,v,w,np,sz,vm,nf,nc,cv,cid,id)
double	*x,*y,*z,*u,*v,*w,*sz,*vm,*cv;
int	*np,*nc,*nf,*cid,*id;
{
	int		i;
	Vpoint_struct	*p;
	float		*rv;
	float		rm;
	float		rs;

	p = (Vpoint_struct *)malloc(sizeof(Vpoint_struct) * (*np));
	if (p == (Vpoint_struct *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

	for (i = 0;i < *np;i ++) {
		p[i].point.x      = (float)*x;
		p[i].point.y      = (float)*y;
		p[i].point.z      = (float)*z;
		p[i].vector.x_val = (float)*u;
		p[i].vector.y_val = (float)*v;
		p[i].vector.z_val = (float)*w;
		x ++;y ++;z ++;u ++;v ++;w ++;
	}

	rv = (float *)malloc(sizeof(float) * (*nc));
	if (rv == (float *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}
	
	for (i = 0;i < *nc;i ++) {
		rv[i] = (float)*cv;
		cv ++;
	}

	rs = (float)*sz;
	rm = (float)*vm;

	ViewExtVector(p,*np,rs,rm,*nf,*nc,rv,cid,*id);
	free(p);
	free(rv);
}

void    vepa(xmin,xmax,ymin,ymax,nx,ny,npy,cid,id)
double  *xmin,*xmax,*ymin,*ymax;
int     *nx,*ny,*npy,*cid,*id;
{
        float   xxmin,xxmax,yymin,yymax;

        xxmin = (float)*xmin;
        xxmax = (float)*xmax;
        yymin = (float)*ymin;
        yymax = (float)*ymax;

        ViewExtPlotAxis(xxmin,xxmax,yymin,yymax,*nx,*ny,*npy,*cid,*id);
}

void    vepl(px,py,np,xmin,xmax,ymin,ymax,cid,id)
double  *px,*py;
double  *xmin,*xmax,*ymin,*ymax;
int     *np;
int     *cid,*id;
{
        float   xxmin,xxmax,yymin,yymax;
        float   *rpx,*rpy;
        int     i;

        xxmin = (float)*xmin;
        xxmax = (float)*xmax;
        yymin = (float)*ymin;
        yymax = (float)*ymax;

        rpx = (float *)malloc(sizeof(float) * (*np));
	if (rpx == (float *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

        rpy = (float *)malloc(sizeof(float) * (*np));
	if (rpy == (float *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

        for (i = 0;i < *np;i ++) {
                rpx[i] = (float)*px;
                rpy[i] = (float)*py;
                px ++; py ++;
        }

        ViewExtPlotLine(rpx,rpy,*np,xxmin,xxmax,yymin,yymax,*cid,*id);
	free(rpx);
	free(rpy);
}

void    vepm(px,py,np,xmin,xmax,ymin,ymax,mid,cid,id)
double  *px,*py;
double  *xmin,*xmax,*ymin,*ymax;
int     *np;
int     *mid,*cid,*id;
{
        float   xxmin,xxmax,yymin,yymax;
        float   *rpx,*rpy;
        int     i;

        xxmin = (float)*xmin;
        xxmax = (float)*xmax;
        yymin = (float)*ymin;
        yymax = (float)*ymax;

        rpx = (float *)malloc(sizeof(float) * (*np));
	if (rpx == (float *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

        rpy = (float *)malloc(sizeof(float) * (*np));
	if (rpy == (float *)NULL) {
		fprintf(stderr,"cant get memory\n");
		exit(1);
	}

        for (i = 0;i < *np;i ++) {
                rpx[i] = (float)*px;
                rpy[i] = (float)*py;
                px ++; py ++;
        }

        ViewExtPlotMarker(rpx,rpy,*np,xxmin,xxmax,yymin,yymax
                                        ,*mid,*cid,*id);
	free(rpx);
	free(rpy);
}

void    vepx(xmin,xmax,ymin,ymax,nx,ny,fg)
double  *xmin,*xmax,*ymin,*ymax;
int     *nx,*ny,*fg;
{
        float   fxmin,fxmax,fymin,fymax;

        fxmin = (float)*xmin;
        fxmax = (float)*xmax;
        fymin = (float)*ymin;
        fymax = (float)*ymax;

        ViewExtPlotMinMax(&fxmin,&fxmax,&fymin,&fymax,nx,ny,*fg);

        *xmin = (double)fxmin;
        *xmax = (double)fxmax;
        *ymin = (double)fymin;
        *ymax = (double)fymax;
}

void    vepx2(min,max,n,fg)
double  *min,*max;
int     *n,*fg;
{
        float   fmin,fmax;

        fmin = (float)*min;
        fmax = (float)*max;

        ViewExtPlotMinMax2(&fmin,&fmax,n,*fg);

        *min = (double)fmin;
        *max = (double)fmax;
}

void	vetw(title,id)
char	*title;
int	*id;
{
	ViewExtTitleWindow(title,*id);
}

/*	£Ö£é£å£÷£Ø£±£±¥é¥¤¥Ö¥é¥ê	*/

vxgs(nw,nh,id)
int	*nw,*nh,*id;
{
	ViewX11GetWindowSize(nw,nh,*id);
}
