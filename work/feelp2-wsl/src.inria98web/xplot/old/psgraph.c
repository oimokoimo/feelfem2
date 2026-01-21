/***********************************************/
/*         psgraph.c                           */
/***********************************************/
#include <stdio.h>
#include <math.h>
#include "psgraph.h"
#include "PostScript.h"

#define CHRATE   0.6 
#define CHEIGHT  2.4   /* for title */ 
#define CHEIGHT_T 1.7  /* for xtitle*/
#define TMRATE   0.4
#define TIC1     8.0
#define TIC2     4.0 
#define XSTEP    2.0
#define DOT_RATE 1.5
#define LINESMAX 1000
#define FLAME_LINE 0.5
#define TIC_LINE1  0.5
#define TIC_LINE2  0.3
#define XAXIS_SHOW 1.7
#define YAXIS_SHOW 1.0
#define XUNIT_SHOW 3.0
#define YUNIT_SHOW 1.0


#define LOG10 2.3025850929940

extern double PosRate;

static double Xlen = 400.0;
static double Ylen = 400.0;
static double Xbase =100.0;
static double Ybase =100.0;
static int    Ifsize = 10; 
static double Dfsize = 10.0;
static int    Ifsize2 = 15;
static double Dfsize2 = 15.0;
static double Gray  = 0.0;
static double Lwidth = 0.5;
static double Rate   = 1.0;
static int    Xtype = NORMAL;
static int    Ytype = NORMAL;
static double Xmin,Xmax,Ymin,Ymax,Dx,Dy;

static char *fmts[] = {
    "%d","%f","%7.2f","%7.3f","%7.4f"
    };


figsize(x,y,xl,yl)
double x,y,xl,yl;
{
    Xbase = x;
    Ybase = y;

    Xlen = xl;
    Ylen = yl;

    Rate   = xl / 400.0;

    Dfsize = 10.0 * Rate;
    Ifsize = (int)Dfsize;

    if(Ifsize < 2) Ifsize = 2;
    Dfsize = (double)Ifsize;

    Dfsize2 = Dfsize * 1.5;
    Ifsize2 = (int)Dfsize2;
    Dfsize2 = (double)Ifsize2;

    return;
}
static void Gr_line(x)
double x;
{
    if( x == Lwidth) return;
    Lwidth = x;
    linewidth(x);
}

newpen(n)
int n;
{
    double x;
    static int pensize = 0;

    if(n<1 || n>20) {
	fprintf(stderr,"Ill operand, ignored.(newpen)\n");
	return;
    }
    if(n == pensize) return;
    pensize = n;

    x = (double)n / 10.0;
    Gr_line(x);
    return;
}

Number2(x,y,dat)
double x,y,dat;
{
    int idat,cod;

    char buf[10];
    char *cp;
    cp = buf;
    idat = dat;
    if((double)idat == dat) {
       cod = 0;
    }
    else {
       cod = 1;    /* proto-type */
    }
    switch(cod) {
	case 0:
	    sprintf(buf,fmts[cod],(int)dat);
	    break;
       default:
            sprintf(buf,fmts[cod],dat);
	    break;
    }

    while(*cp == ' ' && *cp != '\0') cp++;

    font(0,0,Ifsize);
    fposhow(x,y,cp,MIDDLE_SHOW);
    return;
}

Number3(x,y,dat)
double x,y,dat;
{
    int idat,cod;
    int len;
    char buf[10];
    char *cp;

    cp = buf;
    idat = dat;
    if((double)idat == dat) {
       cod = 0;
    }
    else {
       cod = 1;    /* proto-type */
    }
    switch(cod) {
	case 0:
	    sprintf(buf,fmts[cod],(int)dat);
	    break;
       default:
            sprintf(buf,fmts[cod],dat);
	    break;
    }

    while(*cp == ' ' && *cp != '\0') cp++;
    len = strlen(cp);
    y -= Dfsize * CHRATE /2.0 /PosRate;

    font(3,0,Ifsize);
    fposhow(x,y,cp,RIGHT_SHOW);
    return;
}

Number2e(x,y,dat)
double x,y,dat;
{
    int nt;
    char buf[20],buf2[20];
    char *cp;

    cp = buf;

    font(3,0,Ifsize);
    sprintf(buf,"%10.7e",dat);
    sscanf(buf+10,"%d",&nt); 

    cp += 8;
    while(*cp == '0') cp --;
    if(*cp == '.') cp++;
    cp++;

    sprintf(cp,"\\26410%c",'\0');
    sprintf(buf2,"%d",nt);

    fsupshow(x,y,buf,buf2,MIDDLE_SHOW);
    return;

}


Number3e(x,y,dat)
double x,y,dat;
{
    int nt;
    char buf[20],buf2[20];
    char *cp;

    cp = buf;

    font(3,0,Ifsize);
    sprintf(buf,"%10.7e",dat);
    sscanf(buf+10,"%d",&nt); 

    cp += 8;
    while(*cp == '0') cp --;
    if(*cp == '.') cp++;
    cp++;

    sprintf(cp,"\\26410%c",'\0');
    sprintf(buf2,"%d",nt);

    x -= Dfsize * CHRATE / PosRate;
    fsupshow(x,y,buf,buf2,RIGHT_SHOW);
    return;

}


flame(type)
int type;
{
    Gr_line(FLAME_LINE);

    switch(type) {
	case BOX:
	    fbox(Xbase,Ybase,Xbase+Xlen,Ybase+Ylen);
	    break;
        case AXIS:
	    fline(Xbase,Ybase,Xbase+Xlen,Ybase);
	    fline(Xbase,Ybase,Xbase,Ybase+Ylen);
            break;
    }
    return;
}

set_xdefarea(xmin,xmax,type)
double xmin,xmax;
int type;
{
    Xmin = xmin;
    Xmax = xmax;
    Dx   = Xmax - Xmin;
    Xtype = type;
    return;
}

set_xaxis(xmin,xmax,step,type)
double xmin,xmax,step;
int type;
{
    double x,y,xdat;
    double log(),Tensup();
    int i;

    set_xdefarea(xmin,xmax,type);

    y    = Ybase - Dfsize * XAXIS_SHOW * CHRATE;

    switch(type) {
	case NORMAL:
	   xdat = xmin;
	   while(xdat <= xmax) {
	       x = (xdat - xmin)/Dx * Xlen + Xbase;
	       Number2(x,y,xdat);
	       fline(x,Ybase,x,Ybase+TIC1*Rate);
               xdat += step;
           }
	   break;
        case LOG:
	   xdat = (double)((int)(xmin - 1.0));
	   while(xdat <= xmax) {
	       for(i=0;i<100;i+=10) {
		   if( i ) {
		       x = xdat + log((double)i )/log(10.0) - 1.0;
                   }
		   else {
		       x = xdat;
                   }
		   if(x < Xmin || x > Xmax) continue;
		   x = (x - Xmin)/Dx * Xlen + Xbase;
		   if( i != 0 ) {
		       Gr_line(TIC_LINE2);
		       fline(x, Ybase,x,Ybase+TIC2*Rate);
                   }
		   else {
		       Number2e(x,y,Tensup(xdat));
		       Gr_line(TIC_LINE1);
		       fline(x, Ybase,x,Ybase+TIC1);
                   }
              
             }
	     xdat += 1.0;
        }
        break;
    }
    return;
}

static double Tensup(x)
double x;
{
    double exp();
    return( exp(x * LOG10));
}

set_ydefarea(ymin,ymax,type)
double ymin,ymax;
int type;
{
    Ymin = ymin;
    Ymax = ymax;
    Dy   = Ymax - Ymin;
    Ytype = type;
    return;
}

set_yaxis(ymin,ymax,step,type)
double ymin,ymax,step;
int type;
{
    double x,y,ydat;
    int i;

    set_ydefarea(ymin,ymax,type);

    x    = Xbase - Dfsize * CHRATE * YAXIS_SHOW;

    switch(type) {
	case NORMAL:
	   ydat = ymin;
	   while(ydat <= ymax) {
	       y = (ydat - ymin)/Dy * Ylen + Ybase;
	       Number3(x,y,ydat);
	       fline(Xbase,y,Xbase+TIC1*Rate,y);
               ydat += step;
           }
	   break;

        case LOG:
	   ydat = ymin - 1.0;
	   while(ydat <= ymax) {
	       for(i=0;i<100;i+=10) {
		   if( i ) {
		       y = ydat + log((double)i)/ LOG10 - 1.0;
                   }
		   else {
		       y = ydat;
                   }
		   if(y < Ymin || y > Ymax) continue;
		   y = (y - Ymin)/Dy * Ylen + Ybase;
		   if( i != 0 ) {
		       Gr_line(TIC_LINE2);
		       fline(Xbase,y,Xbase+TIC2*Rate,y);
                   }
		   else {
		       Number3e(x,y,Tensup(ydat)); 
		       Gr_line(TIC_LINE1);
		       fline(Xbase,y,Xbase+TIC1*Rate,y);
                   }
              
             }
	     ydat += 1.0;
        }
        break;

    }
    return;
}

drawgraph(func,xmin,xmax)
double (*func)();
double xmin,xmax;
{
    double x,y,pxx,pyy,xx,yy,step;
    double fx,fy;
    double exp();
    int i;

    setdash(0);  /* this is necessary */

    x = xmin;
    i = 0;

    step = (Xmax-Xmin)* XSTEP / Xlen;

    while(x < xmax) {
    
        switch(Xtype) {
	    case LOG:
	        fx = exp(LOG10 * x);
		break;
	    default:
		fx = x;
	        break;
	}
	
        fy = (*func)(fx);
	
	switch(Ytype) {
	    case LOG:
	        y = log(fy) / LOG10; 
		break;
	    default:
		y = fy;
	        break;
	}
	
	xx = (x - Xmin)/Dx * Xlen + Xbase;
	yy = (y - Ymin)/Dy * Ylen + Ybase;
        if( i == 0) {
	    pxx = xx;
	    pyy = yy;
	    i++;
	    continue;
        }
	fline(pxx,pyy,xx,yy);
	pxx = xx;
	pyy = yy;
	i++;
	x += step;
    }

}

drawfuncn(func,n,xmin,xmax)
double (*func)();
int n;
double xmin,xmax;
{
    double x,y,pxx,pyy,xx,yy,step;
    double fx,fy;
    double exp();
    int i;

    x = xmin;
    i = 0;

    step = (Xmax-Xmin)* XSTEP / Xlen;

    while(x < xmax) {
    
        switch(Xtype) {
	    case LOG:
	        fx = exp(LOG10 * x);
		break;
	    default:
		fx = x;
	        break;
	}
	
        fy = (*func)(n,fx);
	
	switch(Ytype) {
	    case LOG:
	        y = log(fy) / LOG10; 
		break;
	    default:
		y = fy;
	        break;
	}
	
	xx = (x - Xmin)/Dx * Xlen + Xbase;
	yy = (y - Ymin)/Dy * Ylen + Ybase;
        if( i == 0) {
	    pxx = xx;
	    pyy = yy;
	    i++;
	    continue;
        }
	fline(pxx,pyy,xx,yy);
	pxx = xx;
	pyy = yy;
	i++;
	x += step;
    }
}

drawfunc1(func,t,xmin,xmax)
double (*func)();
double t,xmin,xmax;
{
    double x,y,pxx,pyy,xx,yy,step;
    double fx,fy;
    double exp();
    int i;

    x = xmin;
    i = 0;

    step = (Xmax-Xmin)* XSTEP / Xlen;

    while(x < xmax) {
    
        switch(Xtype) {
	    case LOG:
	        fx = exp(LOG10 * x);
		break;
	    default:
		fx = x;
	        break;
	}
	
        fy = (*func)(t,fx);
	
	switch(Ytype) {
	    case LOG:
	        y = log(fy) / LOG10; 
		break;
	    default:
		y = fy;
	        break;
	}
	
	xx = (x - Xmin)/Dx * Xlen + Xbase;
	yy = (y - Ymin)/Dy * Ylen + Ybase;
        if( i == 0) {
	    pxx = xx;
	    pyy = yy;
	    i++;
	    continue;
        }
	fline(pxx,pyy,xx,yy);
	pxx = xx;
	pyy = yy;
	i++;
	x += step;
    }
}

drawlines(x,y,n)
double x[],y[];
int n;
{    
    int i;
    double xx[LINESMAX],yy[LINESMAX];
    double log();
    double xt,yt;
 
    if(n > LINESMAX) {
	fprintf(stderr,"Too many lines.(drawlines)\n");
	fprintf(stderr,"No written.\n");
	return;
    }

    for(i=0;i<n;i++) {

	xt = x[i]; yt = y[i];

        if(Xtype == LOG ) {
            xt = log(xt)/LOG10;
        }
        if(Ytype == LOG ) {
	    yt = log(yt)/LOG10;
        }

	xx[i] = (xt - Xmin)/Dx * Xlen + Xbase;
	yy[i] = (yt - Ymin)/Dy * Ylen + Ybase;
    }
    flines(xx,yy,n);
    return;
}

drawpoint(x,y,code)
double x,y;
int code;
{
    double log();
    if(Xtype == LOG ) {
	x = log(x)/LOG10;
    }
    if(Ytype == LOG ) {
	y = log(y)/LOG10;
    }

    x = (x - Xmin)/Dx * Xlen + Xbase;
    y = (y - Ymin)/Dy * Ylen + Ybase;

    fdot(x,y,code,(double)DOT_RATE*Rate);
    return;
}

disptitle(s)
char *s;
{
    int len;
    double x,y;

    len = strlen(s);
    font(1,2,Ifsize2);

    x = Xbase +  Xlen/2.0;
    y = Ybase - Dfsize * XAXIS_SHOW * CHRATE;  
    y -= Dfsize  * CHEIGHT * CHRATE;
    y -= Dfsize2 * CHEIGHT * CHRATE;

    fposhow(x,y,s,MIDDLE_SHOW);

    return;
}

dispxunit(s)
char *s;
{
     double x,y;
     x = Xbase + Xlen + XUNIT_SHOW * Dfsize * CHRATE;
     y = Ybase - Dfsize * XAXIS_SHOW * CHRATE;

     font(0,0,Ifsize);
     fsymbol(x,y,s);
}

dispyunit(s)
char *s;
{
     double x,y;
     y = Ybase + Ylen + YUNIT_SHOW * Dfsize * CHRATE;
     x = Xbase - Dfsize * YAXIS_SHOW * CHRATE;

     font(0,0,Ifsize);
     fposhow(x,y,s,RIGHT_SHOW);
}

dispxtitle(s)
char *s;
{
    double x,y;
    x = Xbase + Xlen/2.0;
    y = Ybase - Dfsize * ( XAXIS_SHOW * CHRATE + CHEIGHT_T);

    font(0,3,Ifsize);
    fposhow(x,y,s,MIDDLE_SHOW);
}

mesh(x1,y1,x2,y2,xstep,ystep)
double x1,y1,x2,y2,xstep,ystep;
{
    double xx,yy;
    int i;

    Gr_line(0.2);

    xx = x1;
    yy = y1;
 
    if(x1>x2 || y1>y2 || xstep<=0.0 || ystep <=0.0) {
        fprintf(stderr,"mesh(psgraph) illegal parameter\n");
	return;
    }

    setgray(0.6);
    while(xx <= x2 + xstep/2.0) {
	fline(xx,y1,xx,y2);
	xx += xstep;
    }
    while(yy <= y2 + ystep/2.0) {
	fline(x1,yy,x2,yy);
        yy += ystep;
    }

    setgray(0.0);

    xx = x1;
    yy = y1;
     i = 0;

    while(xx <= x2 + xstep/2.0) {
        if(xstep >= 0.00001  && xx < 999999.9) {
	    numberx(xx,y1-Dfsize*XAXIS_SHOW/PosRate*CHRATE,xx);
	}
	else {
	    numberxe(xx,y1-Dfsize*XAXIS_SHOW/PosRate*CHRATE,xx);
        }
        i++;

	xx = xstep * (double)i + x1;
    }

    i = 0;
    while(yy <= y2 + ystep/2.0) {
	if(ystep >= 0.00001  && yy < 999999.9 ) {
	    numbery(x1-Dfsize*CHRATE/PosRate,yy,yy);
        }
	else {
	    numberye(x1-Dfsize*CHRATE/PosRate,yy,yy);
        }
        i++;
        yy = ystep * (double)i + y1;
    }

    Gr_line(FLAME_LINE);
    fbox(x1,y1,x2,y2);

}


mesh2(x1,y1,x2,y2,xstep,ystep)
double x1,y1,x2,y2,xstep,ystep;
{
    double xx,yy;
    int i;

    Gr_line(0.2);

    xx = x1;
    yy = y1;
 
    if(x1>x2 || y1>y2 || xstep<=0.0 || ystep <=0.0) {
        fprintf(stderr,"mesh(psgraph) illegal parameter\n");
	return;
    }

    setgray(0.6);
    while(xx <= x2 + xstep/2.0) {
	fline(xx,y1,xx,y2);
	xx += xstep;
    }
    while(yy <= y2 + ystep/2.0) {
	fline(x1,yy,x2,yy);
        yy += ystep;
    }

    setgray(0.0);

    Gr_line(FLAME_LINE);
    fbox(x1,y1,x2,y2);

}

numberx(x,y,dat)
double x,y,dat;
{
    char *cp,*numake();

    cp = numake(dat);

    font(0,0,Ifsize);
    fposhow(x,y,cp,MIDDLE_SHOW);
    return;
}

numbery(x,y,dat)
double x,y,dat;
{
    char *cp,*numake();

    cp = numake(dat);

    y -= Dfsize * CHRATE /2.0 /PosRate;

    font(3,0,Ifsize);
    fposhow(x,y,cp,RIGHT_SHOW);
    return;
}

numberxe(x,y,dat)
double x,y,dat;
{
    int nt;
    char buf[20],buf2[20];
    char *cp;

    cp = buf;

    font(3,0,Ifsize);
    sprintf(buf,"%10.7e",dat);
    sscanf(buf+10,"%d",&nt); 

    cp += 8;
    while(*cp == '0') cp --;
    if(*cp == '.') cp++;
    cp++;

    sprintf(cp,"\\26410%c",'\0');
    sprintf(buf2,"%d",nt);

    fsupshow(x,y,buf,buf2,MIDDLE_SHOW);
    return;

}


numberye(x,y,dat)
double x,y,dat;
{
    int nt;
    char buf[20],buf2[20];
    char *cp;

    cp = buf;

    font(3,0,Ifsize);
    sprintf(buf,"%10.7e",dat);
    sscanf(buf+10,"%d",&nt); 

    cp += 8;
    while(*cp == '0') cp --;
    if(*cp == '.') cp++;
    cp++;

    sprintf(cp,"\\26410%c",'\0');
    sprintf(buf2,"%d",nt);

    x -= Dfsize * CHRATE / PosRate;
    fsupshow(x,y,buf,buf2,RIGHT_SHOW);
    return;

}

double dabs(x)
double x;
{
    if(x < 0.0) return(-x);
    else        return( x);
}
    
char *numake(x)
double x;
{
    unsigned long ix;
    double y,dabs();
    int len,kt;
    static char num[100];
    char fmt[100];
    char *cp;

    if(dabs(x) < 1.0e-7) x = 0.0;

    y = dabs(x);
    kt = 0;

    while(kt<8) {
        if( y < 1.0e-7) {
            x = 0.0;
            break;
        }

	ix = (unsigned long)(y + 0.1);

/* fprintf(stderr,"%ld  %lf  %le\n",ix,y,dabs(y-(double)ix)/y);
*/

	if( dabs(y - (double)ix)/y < 1.0e-5) break;
	y = y * 10.0;
	kt++;
    }
    if(kt>=8) return("********");

    sprintf(fmt,"%%20.%df",kt);
    sprintf(num,fmt,x);

    cp = num;

    while(*cp == ' ') cp++;
    len = strlen(cp);
    if(*(cp+len-1) == '.') *(cp+len-1) = '\0';

    return(cp);
}
