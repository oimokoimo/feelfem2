/***********************************************************************
*                                                                      *
* viewext.c ver 1.0                                                    *
* Copy rights - all rights reserved by NEC Cooroperation 1994.4.1      *
*                                                                      *
************************************************************************/

#include "view.h"

int     ViewExtColorBar(n,value,fg,mid,colorid,id)
float   *value;
int     *colorid,id;
int     fg,mid;
{
    int     hg,hg0;
    int     i;
    int     x0,x1,x2,y;
    char    val[100];

    Font    font;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    ViewGetGeometry(id);

    if (viewport[id].height < 100) {
        font = XLoadFont(viewdisp[id].disp,"5x8");
        hg = 8;
    }else if (viewport[id].height < 300) {
        font = XLoadFont(viewdisp[id].disp,"6x13");
        hg = 13;
    }else if (viewport[id].height < 500) {
        font = XLoadFont(viewdisp[id].disp,"7x14");
        hg = 14;
    }else if (viewport[id].height < 700) {
        font = XLoadFont(viewdisp[id].disp,"8x16");
        hg = 16;
    }else if (viewport[id].height < 900) {
        font = XLoadFont(viewdisp[id].disp,"10x20");
        hg = 20;
    }else{
        font = XLoadFont(viewdisp[id].disp,"12x24");
        hg = 24;
    }

    hg0 = hg;
    hg += 5;
    x0 = viewport[id].width  * 0.05 * 0.9;
    x1 = viewport[id].width  * 0.75;
    x2 = viewport[id].width  * 0.8;
    y  = viewport[id].height * 0.2;

    XSetFont(viewdisp[id].disp,viewdisp[id].gc,font);

    for (i = 0;i < n;i ++) {

        sprintf(val," % .3E",*value); value ++;
        XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                viewcolor[id][mid].color[0].pixel);
        XDrawString(viewdisp[id].disp,viewdisp[id].win,
            viewdisp[id].gc,x2,i * hg + y,val,strlen(val));
        
        if (fg == 0) {

            XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                viewcolor[id][*colorid].color[0].pixel); colorid ++;
            XFillRectangle(viewdisp[id].disp,viewdisp[id].win,
                viewdisp[id].gc,x1,i * hg + y - hg0,x0,hg0);

            XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                viewcolor[id][mid].color[0].pixel);
            XDrawRectangle(viewdisp[id].disp,viewdisp[id].win,
                viewdisp[id].gc,x1,i * hg + y - hg0,x0,hg0);

        }else{
            XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                  viewcolor[id][*colorid].color[0].pixel); colorid ++;
            XFillRectangle(viewdisp[id].disp,viewdisp[id].win,
                viewdisp[id].gc,x1,i * hg + y - hg0 - hg0 / 2,x0,hg0);

            XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                   viewcolor[id][mid].color[0].pixel);
            XDrawRectangle(viewdisp[id].disp,viewdisp[id].win,
                viewdisp[id].gc,x1,i * hg + y - hg0 - hg0 / 2,x0,hg0);
        }
    }

    if (fg == 1) {
        XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
            viewcolor[id][*colorid].color[0].pixel); colorid ++;
        XFillRectangle(viewdisp[id].disp,viewdisp[id].win,
            viewdisp[id].gc,x1,i * hg + y - hg0 - hg0 / 2,x0,hg0);

        XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
            viewcolor[id][mid].color[0].pixel);
        XDrawRectangle(viewdisp[id].disp,viewdisp[id].win,
            viewdisp[id].gc,x1,i * hg + y - hg0 - hg0 / 2,x0,hg0);
    }

    XFlush(viewdisp[id].disp);

    return( 1 );
}

int     ViewExtMessage(argv,argc,colorid,id)
char    argv[100][100];
int     argc;
int     colorid,id;
{
    Font    font;
    int     i;
    int     hg;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    ViewGetGeometry(id);

    if (viewport[id].height < 100) {
        font = XLoadFont(viewdisp[id].disp,"5x8");
        hg = 8;
    }else if (viewport[id].height < 300) {
        font = XLoadFont(viewdisp[id].disp,"6x13");
        hg = 13;
    }else if (viewport[id].height < 500) {
        font = XLoadFont(viewdisp[id].disp,"7x14");
        hg = 14;
    }else if (viewport[id].height < 700) {
        font = XLoadFont(viewdisp[id].disp,"8x16");
        hg = 16;
    }else if (viewport[id].height < 900) {
        font = XLoadFont(viewdisp[id].disp,"10x20");
        hg = 20;
    }else{
        font = XLoadFont(viewdisp[id].disp,"12x24");
        hg = 24;
    }

    hg += 5;

    XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                viewcolor[id][colorid].color[0].pixel);
    XSetFont(viewdisp[id].disp,viewdisp[id].gc,font);

    for (i = 0;i < argc;i ++) {
        XDrawString(viewdisp[id].disp,viewdisp[id].win,
            viewdisp[id].gc,10,(i + 1) * hg,argv[i],strlen(argv[i]));
    }

    XFlush(viewdisp[id].disp);

    return( 1 );
}

int     ViewExtAxis(colorid,id)
int     colorid,id;
{
    Vpoint  x0[2],y0[2],z0[2];
    Vpoint  xt,yt,zt;

    float   viewsize;
    float   pos;
    float   rx,ry,rz;

    float   pxx[2],pxy[2],pyx[2],pyy[2],pzx[2],pzy[2];
    float   pxtx,pxty,pytx,pyty,pztx,pzty;

    float   rxx[2],rxy[2],ryx[2],ryy[2],rzx[2],rzy[2];
    float   rxtx,rxty,rytx,ryty,rztx,rzty;

    int     winsize;

    Font    font;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    ViewGetGeometry(id);

    if ((viewport[id].max.x - viewport[id].min.x) >
        (viewport[id].max.y - viewport[id].min.y)) {
        viewsize = viewport[id].max.x - viewport[id].min.x;
    }else{
        viewsize = viewport[id].max.x - viewport[id].min.y;
    }

    if (viewport[id].width < viewport[id].height) {
        winsize = viewport[id].width;
    }else{
        winsize = viewport[id].height;
    }

    pos = viewsize * 0.05;

    x0[0].x = 0.0; x0[0].y = 0.0; x0[0].z = 0.0;
    x0[1].x = pos / viewport[id].zoom.x; x0[1].y = 0.0; x0[1].z = 0.0;
    y0[0].x = 0.0; y0[0].y = 0.0; y0[0].z = 0.0;
    y0[1].x = 0.0; y0[1].y = pos / viewport[id].zoom.y; y0[1].z = 0.0;
    z0[0].x = 0.0; z0[0].y = 0.0; z0[0].z = 0.0;
    z0[1].x = 0.0; z0[1].y = 0.0; z0[1].z = pos / viewport[id].zoom.z;

    pos = viewsize * 0.05 * 1.001;

/*
    xt.x = pos; xt.y = 0.0; xt.z = 0.0;
    yt.x = 0.0; yt.y = pos; yt.z = 0.0;
    zt.x = 0.0; zt.y = 0.0; zt.z = pos;
*/
    xt.x = pos / viewport[id].zoom.x; xt.y = 0.0; xt.z = 0.0;
    yt.x = 0.0; yt.y = pos / viewport[id].zoom.y; yt.z = 0.0;
    zt.x = 0.0; zt.y = 0.0; zt.z = pos / viewport[id].zoom.z;

    rx = viewport[id].rot.x;
    ry = viewport[id].rot.y;
    rz = viewport[id].rot.z;

    ViewRotatePoint(&pxx[0],&pxy[0],x0[0].x,x0[0].y,x0[0].z,rx,ry,rz,id);
    ViewRotatePoint(&pxx[1],&pxy[1],x0[1].x,x0[1].y,x0[1].z,rx,ry,rz,id);
    ViewRotatePoint(&pyx[0],&pyy[0],y0[0].x,y0[0].y,y0[0].z,rx,ry,rz,id);
    ViewRotatePoint(&pyx[1],&pyy[1],y0[1].x,y0[1].y,y0[1].z,rx,ry,rz,id);
    ViewRotatePoint(&pzx[0],&pzy[0],z0[0].x,z0[0].y,z0[0].z,rx,ry,rz,id);
    ViewRotatePoint(&pzx[1],&pzy[1],z0[1].x,z0[1].y,z0[1].z,rx,ry,rz,id);

    ViewRotatePoint(&pxtx,&pxty,xt.x,xt.y,xt.z,rx,ry,rz,id);
    ViewRotatePoint(&pytx,&pyty,yt.x,yt.y,yt.z,rx,ry,rz,id);
    ViewRotatePoint(&pztx,&pzty,zt.x,zt.y,zt.z,rx,ry,rz,id);

    rxx[0] =   pxx[0] / viewsize * winsize + viewport[id].width  * 0.9;
    rxy[0] =   viewport[id].height
             - pxy[0] / viewsize * winsize - viewport[id].height * 0.1;
    rxx[1] =   pxx[1] / viewsize * winsize + viewport[id].width  * 0.9;
    rxy[1] =   viewport[id].height
             - pxy[1] / viewsize * winsize - viewport[id].height * 0.1;
    ryx[0] =   pyx[0] / viewsize * winsize + viewport[id].width  * 0.9;
    ryy[0] =   viewport[id].height
             - pyy[0] / viewsize * winsize - viewport[id].height * 0.1;
    ryx[1] =   pyx[1] / viewsize * winsize + viewport[id].width  * 0.9;
    ryy[1] =   viewport[id].height
             - pyy[1] / viewsize * winsize - viewport[id].height * 0.1;
    rzx[0] =   pzx[0] / viewsize * winsize + viewport[id].width  * 0.9;
    rzy[0] =   viewport[id].height
             - pzy[0] / viewsize * winsize - viewport[id].height * 0.1;
    rzx[1] =   pzx[1] / viewsize * winsize + viewport[id].width  * 0.9;
    rzy[1] =   viewport[id].height
             - pzy[1] / viewsize * winsize - viewport[id].height * 0.1;

    rxtx   =   pxtx / viewsize * winsize + viewport[id].width  * 0.9;
    rxty   =   viewport[id].height
             - pxty / viewsize * winsize - viewport[id].height * 0.1;
    rytx   =   pytx / viewsize * winsize + viewport[id].width  * 0.9;
    ryty   =   viewport[id].height
             - pyty / viewsize * winsize - viewport[id].height * 0.1;
    rztx   =   pztx / viewsize * winsize + viewport[id].width  * 0.9;
    rzty   =   viewport[id].height
             - pzty / viewsize * winsize - viewport[id].height * 0.1;

    font = XLoadFont(viewdisp[id].disp,"7x13");
    XSetFont(viewdisp[id].disp,viewdisp[id].gc,font);
    XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                    viewcolor[id][colorid].color[0].pixel);

    XSetLineAttributes(viewdisp[id].disp,viewdisp[id].gc,1,
        LineSolid,CapButt,JoinMiter);

    XDrawLine(viewdisp[id].disp,viewdisp[id].win,viewdisp[id].gc,
        (int)rxx[0],(int)rxy[0],(int)rxx[1],(int)rxy[1]);
    XDrawLine(viewdisp[id].disp,viewdisp[id].win,viewdisp[id].gc,
        (int)ryx[0],(int)ryy[0],(int)ryx[1],(int)ryy[1]);
    XDrawLine(viewdisp[id].disp,viewdisp[id].win,viewdisp[id].gc,
        (int)rzx[0],(int)rzy[0],(int)rzx[1],(int)rzy[1]);

    XDrawString(viewdisp[id].disp,viewdisp[id].win,viewdisp[id].gc,
        (int)rxtx,(int)rxty,"x",1);
    XDrawString(viewdisp[id].disp,viewdisp[id].win,viewdisp[id].gc,
        (int)rytx,(int)ryty,"y",1);
    XDrawString(viewdisp[id].disp,viewdisp[id].win,viewdisp[id].gc,
        (int)rztx,(int)rzty,"z",1);

    XFlush(viewdisp[id].disp);

    return( 1 );
}

int        ViewExtTriangleStrip(p,n,att,cid,id)
Vpoint     *p;
int        n,att,cid,id;
{
    int       i,j,k;
    Vpoint    rp[3];
    Vpoint    *pp;

    if (id < 0 || id > VIEW_MAX_DISP - 1)     return( - 1 );

    for (i = 0;i < n - 2;i ++) {
        pp = p;
        for (j = 0;j < 3;j ++) {
            rp[j].x = pp->x;
            rp[j].y = pp->y;
            rp[j].z = pp->z;
            pp ++;
        }

        ViewSetPolygon(rp,3,att,cid,id);

        p ++;
    }

    return( 1 );
}
        
int        ViewExtTriangleContour(p,n,att,cid,cv,cn,id)
Vpoint_struct    *p;
int              n,att,*cid,cn,id;
float            *cv;
{
    int              i,j,k;
    Vpoint_struct    rp[3];
    Vpoint_struct    *pp;

    if (id < 0 || id > VIEW_MAX_DISP - 1)     return( - 1 );

    for (i = 0;i < n - 2;i ++) {
        pp = p;
        for (j = 0;j < 3;j ++) {
            rp[j].point.x = pp->point.x;
            rp[j].point.y = pp->point.y;
            rp[j].point.z = pp->point.z;
            rp[j].scalar  = pp->scalar;
            pp ++;
        }

        ViewContour(rp,att,cn,cv,cid,id);

        p ++;
    }

    return( 1 );
}

int        ViewExtQuadrateStrip(p,m,n,att,cid,id)
Vpoint     *p;
int        m,n,att,cid,id;
{
    int       i,j,k;
    Vpoint    rp[4];

    if (id < 0 || id > VIEW_MAX_DISP - 1)     return( - 1 );

    for (i = 0;i < m * (n - 1);i ++) {
        if ((i + 1) % m != 0) {

            rp[0].x = p[i].x;
            rp[0].y = p[i].y;
            rp[0].z = p[i].z;
            rp[1].x = p[i+1].x;
            rp[1].y = p[i+1].y;
            rp[1].z = p[i+1].z;
            rp[2].x = p[m+i+1].x;
            rp[2].y = p[m+i+1].y;
            rp[2].z = p[m+i+1].z;
            rp[3].x = p[m+i].x;
            rp[3].y = p[m+i].y;
            rp[3].z = p[m+i].z;

            ViewSetPolygon(rp,4,att,cid,id);
        }

    }

    return( 1 );
}
        
int        ViewExtQuadrateContour(p,m,n,att,cid,cv,cn,id)
Vpoint_struct    *p;
int              m,n,att,*cid,cn,id;
float            *cv;
{
    int              i,j,k;
    Vpoint_struct    r;
    Vpoint_struct    r0[10];
    Vpoint_struct    rp[10];

    if (id < 0 || id > VIEW_MAX_DISP - 1)     return( - 1 );

    for (i = 0;i < m * (n - 1);i ++) {
        if ((i + 1) % m != 0) {

            r0[0].point.x = p[i].point.x;
            r0[0].point.y = p[i].point.y;
            r0[0].point.z = p[i].point.z;
            r0[0].scalar  = p[i].scalar;
            r0[1].point.x = p[i+1].point.x;
            r0[1].point.y = p[i+1].point.y;
            r0[1].point.z = p[i+1].point.z;
            r0[1].scalar  = p[i+1].scalar;
            r0[2].point.x = p[m+i+1].point.x;
            r0[2].point.y = p[m+i+1].point.y;
            r0[2].point.z = p[m+i+1].point.z;
            r0[2].scalar  = p[m+i+1].scalar;
            r0[3].point.x = p[m+i].point.x;
            r0[3].point.y = p[m+i].point.y;
            r0[3].point.z = p[m+i].point.z;
            r0[3].scalar  = p[m+i].scalar;

            r.point.x = (r0[0].point.x + r0[1].point.x 
                       + r0[2].point.x + r0[3].point.x) / 4.0;
            r.point.y = (r0[0].point.y + r0[1].point.y 
                       + r0[2].point.y + r0[3].point.y) / 4.0;
            r.point.z = (r0[0].point.z + r0[1].point.z 
                       + r0[2].point.z + r0[3].point.z) / 4.0;
            r.scalar  = (r0[0].scalar  + r0[1].scalar 
                       + r0[2].scalar  + r0[3].scalar) / 4.0;

            rp[0].point.x = r.point.x;
            rp[0].point.y = r.point.y;
            rp[0].point.z = r.point.z;
            rp[0].scalar  = r.scalar;
            rp[1].point.x = r0[0].point.x;
            rp[1].point.y = r0[0].point.y;
            rp[1].point.z = r0[0].point.z;
            rp[1].scalar  = r0[0].scalar;
            rp[2].point.x = r0[1].point.x;
            rp[2].point.y = r0[1].point.y;
            rp[2].point.z = r0[1].point.z;
            rp[2].scalar  = r0[1].scalar;
            ViewContour(rp,att,cn,cv,cid,id);

            rp[0].point.x = r.point.x;
            rp[0].point.y = r.point.y;
            rp[0].point.z = r.point.z;
            rp[0].scalar  = r.scalar;
            rp[1].point.x = r0[1].point.x;
            rp[1].point.y = r0[1].point.y;
            rp[1].point.z = r0[1].point.z;
            rp[1].scalar  = r0[1].scalar;
            rp[2].point.x = r0[2].point.x;
            rp[2].point.y = r0[2].point.y;
            rp[2].point.z = r0[2].point.z;
            rp[2].scalar  = r0[2].scalar;
            ViewContour(rp,att,cn,cv,cid,id);

            rp[0].point.x = r.point.x;
            rp[0].point.y = r.point.y;
            rp[0].point.z = r.point.z;
            rp[0].scalar  = r.scalar;
            rp[1].point.x = r0[2].point.x;
            rp[1].point.y = r0[2].point.y;
            rp[1].point.z = r0[2].point.z;
            rp[1].scalar  = r0[2].scalar;
            rp[2].point.x = r0[3].point.x;
            rp[2].point.y = r0[3].point.y;
            rp[2].point.z = r0[3].point.z;
            rp[2].scalar  = r0[3].scalar;
            ViewContour(rp,att,cn,cv,cid,id);

            rp[0].point.x = r.point.x;
            rp[0].point.y = r.point.y;
            rp[0].point.z = r.point.z;
            rp[0].scalar  = r.scalar;
            rp[1].point.x = r0[3].point.x;
            rp[1].point.y = r0[3].point.y;
            rp[1].point.z = r0[3].point.z;
            rp[1].scalar  = r0[3].scalar;
            rp[2].point.x = r0[0].point.x;
            rp[2].point.y = r0[0].point.y;
            rp[2].point.z = r0[0].point.z;
            rp[2].scalar  = r0[0].scalar;
            ViewContour(rp,att,cn,cv,cid,id);

        }
    }

    return( 1 );
}

int        ViewExtSphere(p,r,step,att,cid,id)
Vpoint     *p;
float      r;
int        step,att,cid,id;
{
    Vpoint   dp[4];
    int      t,s;
    float    dt,ds;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    dt = VIEW_PI / step;
    ds = VIEW_PI / step;

    for (s = 0;s < step;s ++) {
        for (t = 0;t < step * 2;t ++) {
            if (s == 0) {
                dp[0].x = r * sin(s * ds) * sin(t * dt) + p->x;
                dp[0].y = r * sin(s * ds) * cos(t * dt) + p->y;
                dp[0].z = r * cos(s * ds) + p->z;

                dp[1].x = r * sin((s+1) * ds) * sin(t * dt) + p->x;
                dp[1].y = r * sin((s+1) * ds) * cos(t * dt) + p->y;
                dp[1].z = r * cos((s+1) * ds) + p->z;

                dp[2].x = r * sin((s+1) * ds) * sin((t+1) * dt) + p->x;
                dp[2].y = r * sin((s+1) * ds) * cos((t+1) * dt) + p->y;
                dp[2].z = r * cos((s+1) * ds) + p->z;

                ViewSetPolygon(dp,3,att,cid,id);

            }else if (s == step - 1) {

                dp[0].x = r * sin(s * ds) * sin(t * dt) + p->x;
                dp[0].y = r * sin(s * ds) * cos(t * dt) + p->y;
                dp[0].z = r * cos(s * ds) + p->z;

                dp[1].x = r * sin(s * ds) * sin((t+1) * dt) + p->x;
                dp[1].y = r * sin(s * ds) * cos((t+1) * dt) + p->y;
                dp[1].z = r * cos(s * ds) + p->z;

                dp[2].x = r * sin((s+1) * ds) * sin(t * dt) + p->x;
                dp[2].y = r * sin((s+1) * ds) * cos(t * dt) + p->y;
                dp[2].z = r * cos((s+1) * ds) + p->z;

                ViewSetPolygon(dp,3,att,cid,id);

            }else{

                dp[0].x = r * sin(s * ds) * sin(t * dt) + p->x;
                dp[0].y = r * sin(s * ds) * cos(t * dt) + p->y;
                dp[0].z = r * cos(s * ds) + p->z;

                dp[1].x = r * sin((s+1) * ds) * sin(t * dt) + p->x;
                dp[1].y = r * sin((s+1) * ds) * cos(t * dt) + p->y;
                dp[1].z = r * cos((s+1) * ds) + p->z;
             
                dp[2].x = r * sin((s+1) * ds) * sin((t+1) * dt) + p->x;
                dp[2].y = r * sin((s+1) * ds) * cos((t+1) * dt) + p->y;
                dp[2].z = r * cos((s+1) * ds) + p->z;

                dp[3].x = r * sin(s * ds) * sin((t+1) * dt) + p->x;
                dp[3].y = r * sin(s * ds) * cos((t+1) * dt) + p->y;
                dp[3].z = r * cos(s * ds) + p->z;

                ViewSetPolygon(dp,4,att,cid,id);

            }
        }
    }

    return( 1 );
}

int        ViewExtWait(id)
int        id;
{
    XEvent        e;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    XSelectInput(viewdisp[id].disp,viewdisp[id].win,ButtonPressMask);

    while(1) {
        XNextEvent(viewdisp[id].disp,&e);
        switch(e.type) {
            case    ButtonPress:
                    return( 1 );
        }
    }

}

int        ViewExtVector(p,np,size,vm,nf,nc,cv,cid,id)
Vpoint_struct    *p;
float            size,vm,*cv;
int              np,nf,nc,*cid,id;
{
    int      i,j,k,ij;
    float    rx,ry,rz;
    float    len;
    Vpoint   pt,vt;
    Vpoint   vp[5][4];
    Vpoint   dp[5][4];
    float    ratio,scale;
    int      co;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    ratio = 8.0;

    vp[0][0].x = - size; vp[0][0].y =   size; vp[0][0].z = 0.0;
    vp[0][1].x =   size; vp[0][1].y =   size; vp[0][1].z = 0.0;
    vp[0][2].x =   size; vp[0][2].y = - size; vp[0][2].z = 0.0;
    vp[0][3].x = - size; vp[0][3].y = - size; vp[0][3].z = 0.0;

    vp[1][0].x = - size; vp[1][0].y =   size; vp[1][0].z = 0.0;
    vp[1][1].x =    0.0; vp[1][1].y =    0.0; vp[1][1].z = size * ratio;
    vp[1][2].x =   size; vp[1][2].y =   size; vp[1][2].z = 0.0;

    vp[2][0].x =   size; vp[2][0].y =   size; vp[2][0].z = 0.0;
    vp[2][1].x =    0.0; vp[2][1].y =    0.0; vp[2][1].z = size * ratio;
    vp[2][2].x =   size; vp[2][2].y = - size; vp[2][2].z = 0.0;

    vp[3][0].x =   size; vp[3][0].y = - size; vp[3][0].z = 0.0;
    vp[3][1].x =    0.0; vp[3][1].y =    0.0; vp[3][1].z = size * ratio;
    vp[3][2].x = - size; vp[3][2].y = - size; vp[3][2].z = 0.0;

    vp[4][0].x = - size; vp[4][0].y = - size; vp[4][0].z = 0.0;
    vp[4][1].x =    0.0; vp[4][1].y =    0.0; vp[4][1].z = size * ratio;
    vp[4][2].x = - size; vp[4][2].y =   size; vp[4][2].z = 0.0;

    for (i = 0;i < np;i ++) {

        pt.x = p->point.x;
        pt.y = p->point.y;
        pt.z = p->point.z;
        vt.x = p->vector.x_val;
        vt.y = p->vector.y_val;
        vt.z = p->vector.z_val;

        p ++;

        len = sqrt((double)(vt.x) * (double)(vt.x)
                 + (double)(vt.y) * (double)(vt.y)
                 + (double)(vt.z) * (double)(vt.z));
 
/*
        if (fabs(len) / (double)vm < 1.0e-02) return ( - 1 );

        if (ViewVector(&vt,len,&rx,&ry,&rz) < 0) return;
*/

        if (fabs(len) / (double)vm < 1.0e-02) continue;

        ViewVector(&vt,len,&rx,&ry,&rz);

        scale = len / vm;

        co = 0;
        if (cv[0] >= len) {
            co = 0;
        }else{
            for (j = 0;j < nc - 1;j ++) {
                if (cv[j] < len && cv[j + 1] >= len) {
                    co = j + 1;
                    break;
                }
            }
            if (cv[nc - 1] < len) {
                co = nc;
            }
        }

        for (j = 0;j < 5;j ++) {
            if (j != 0) ij = 3;
            else        ij = 4;
            for (k = 0;k < ij;k ++) {
                ViewUtilRotateXYZ(&dp[j][k],&vp[j][k],rx,ry,rz);
                dp[j][k].x = dp[j][k].x * scale + pt.x; 
                dp[j][k].y = dp[j][k].y * scale + pt.y; 
                dp[j][k].z = dp[j][k].z * scale + pt.z; 
            }
            ViewSetPolygon(dp[j],ij,nf,cid[co],id);
        }
    }

    return( 1 );
}

int	ViewExtTitleWindow(title,id)
char	*title;
int	id;
{
	XStoreName(viewdisp[id].disp,viewdisp[id].win,title);
	XFlush(viewdisp[id].disp);
}

int     ViewExtColorBar2(x,y,n,value,fg,mid,colorid,id)
int     x,y;
float   *value;
int     *colorid,id;
int     fg,mid;
{
    int     i;
    int     hg,hg0,hg1,hg2,hg3;
    int	    wt,wt0,wt1;
    int	    x0,y0,x1,y1;
    char    val[100];

    Font    font;

    if (id > VIEW_MAX_DISP - 1 || id < 0) return( - 1 );

    ViewGetGeometry(id);

    if (viewport[id].height < 100 || viewport[id].width < 100) {
        font = XLoadFont(viewdisp[id].disp,"5x8");  hg = 8;
    }else if (viewport[id].height < 300 || viewport[id].width < 300) {
        font = XLoadFont(viewdisp[id].disp,"6x13"); hg = 13;
    }else if (viewport[id].height < 500 || viewport[id].width < 500) {
        font = XLoadFont(viewdisp[id].disp,"7x14"); hg = 14;
    }else{
        font = XLoadFont(viewdisp[id].disp,"8x16"); hg = 16;
    }

    hg0 = hg;
    hg1 = hg + 2;
    hg2 = hg1 * (n - 1) + y * 2; 
    if (fg == 1) hg3 = hg1 *  n      + (hg0 / 2 + y) * 2;
    else         hg3 = hg1 * (n - 1) + (hg0     + y) * 2; 

    wt = hg * 2;
    wt0 = wt;
    wt1 = wt + 5;

    XSetFont(viewdisp[id].disp,viewdisp[id].gc,font);

    for (i = 0;i < n;i ++) {

        x0 = x;
        y0 = y + i * hg1;
        XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                viewcolor[id][*colorid].color[0].pixel); colorid ++;
        XFillRectangle(viewdisp[id].disp,viewdisp[id].win,
                                     viewdisp[id].gc,x0,hg2-y0,wt0,hg0);

        XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                                viewcolor[id][mid].color[0].pixel);
        XDrawRectangle(viewdisp[id].disp,viewdisp[id].win,
                                     viewdisp[id].gc,x0,hg2-y0,wt0,hg0);
        x0 = x + wt1;
        if (fg == 1) y0 = y + (i + 1) * hg1 + hg0 / 2;
        else         y0 = y +  i      * hg1 + hg0;

        if (i != n - 1 || fg == 0) {
            sprintf(val," % .3E",*value); value ++;
            XSetForeground(viewdisp[id].disp,viewdisp[id].gc,
                                viewcolor[id][mid].color[0].pixel);
            XDrawString(viewdisp[id].disp,viewdisp[id].win,
                    viewdisp[id].gc,x0,hg3-y0,val,strlen(val));
        }
    }

    XFlush(viewdisp[id].disp);

    return( 1 );
}

