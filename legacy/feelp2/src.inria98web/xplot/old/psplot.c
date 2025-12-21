/*********************************************/
/*   psplot.c  UNIX plot compatible routine  */
/*                                           */
/*        s80540  1988/11/22                 */
/*********************************************/

#define PSDEF_FILE    "/usr1/fujio/s80540/PostScript/PsDef"

#include <stdio.h>

#include "PostScript.h"

#define CWIDTH  6.0   /*  This size is for 10 point font */
#define CHRATE  0.6   /*  rate of avobe value            */
#define CLINES  64
#define AMIGRAY 0.9
#define MaxConnectedLine 200
#define MAXLINE 200   /*  maximum characters in one line */

static int px0 = 0;
static int py0 = 0;
static int px1 = XDOT;
static int py1 = YDOT;
static int XLEN = XDOT;
static int YLEN = YDOT;
static int AREAX = XDOT,AREAY = YDOT;  /*  segment length */
static int APX  ,APY  ;  /*  segment origin */

#define GFACTOR 100
#define LFACTOR 100
static int GRAY =  0;      /*  0 to GFACTOR */
static int LINE = LFACTOR; /*  0 to LFACTOR */
static double RATE  = 1.0; 
static double Fontsize = CHRATE * 10.0;

static int Currentfont = 10; /*   Times Roman 10 point font*/

static int PAGE ;

static int Dashpattern = 0;
#define DASHMAX   7 
static char *Dashes[] = {
    "3 1","6 1","9 1",      /* ten sen     */
    "3"  ,"6","9"  ,        /* ten sen 2   */
    "6 2 1 2"               /* 1 ten sasen */
   }; 


static FILE *fpps;


/****************************************************
   PostScript file header write routine.
****************************************************/
static initps()
{
    FILE *fp;
    char username[100],homedir[100];
    char date[100];
    char buf[512];

    fprintf(fpps,"%%!\n");
    fprintf(fpps,"%%!PS-Adobe-1.0\n");

    gethd(getuid(),username,homedir);
    fprintf(fpps,"%%%%Creater:%s\n",username);

    if((fp = popen("date","r")) != NULL ) {
	fgets(date,sizeof date,fp);
	pclose(fp);
        fprintf(fpps,"%%%%Date   :%s",date    );
    }

    fprintf(fpps,"%%%%EndComments\n");

    PAGE = 1;
    fprintf(fpps,"%% Page %d\n",PAGE);

    if((fp = fopen(PSDEF_FILE,"r")) == NULL ) {
	fprintf(stderr,"Cannot open Definition file for PostScript.\n");
	exit(1);
    }
    while(fgets(buf,sizeof buf,fp)){
	fprintf(fpps,"%s",buf);
    }
    fclose(fp);
}

/*********************************************************
   PostScript output file open/close routine.
*********************************************************/
openpl(s)
char *s;
{
    if(strlen(s) == 0 || strlen(s) > 15 || strindex(s,"stdout") ) {
	fpps = stdout;
    }
    else {
	if((fpps = fopen(s,"w")) == NULL ) {
	    fprintf(stderr,"Cannot open PS output file %s\n",s);
	    exit(1);
        }
    }
    initps();
}
openplfp(fp)
FILE *fp;
{
    fpps = fp;
    initps();
}
closepl()
{
    fprintf(fpps,"showpage\n");
    if(fpps != stdout ) fclose(fpps);
}
closeplfp()
{
    fprintf(fpps,"showpage\n");
    return;
}
/*************************************************************
    space() routine;
*************************************************************/
space(x0,y0,x1,y1)
int x0,y0,x1,y1;
{
    int dx,dy;
    if(x1 == x0 || y1 == y0 || x0>x1 || y0 >y1) {
	fprintf(stderr,"space: Invalid parameter.\n");
	exit(1);
    }
    dx = x1 - x0;
    dy = y1 - y0;
    px0 = x0; py0 = y0;
    if(dy/dx > YDOT/XDOT) {
        py1 = y1;
	px1 = x0 + dy * XDOT / YDOT;
    }
    else {
	px1 = x1;
	py1 = y0 + dx * YDOT / XDOT;
    }
    XLEN = px1 - px0;
    YLEN = py1 - py0;
    RATE = (double)XDOT / (double)XLEN;

}

/**************************************************************
     line routine
**************************************************************/
line(x1,y1,x2,y2)
int x1,y1,x2,y2;
{
    pspos(&x1,&y1); pspos(&x2,&y2);

    fprintf(fpps,"N %d %d moveto %d %d lineto ",x1,y1,x2,y2);
    line_stroke();
}
fline(x1,y1,x2,y2)
double x1,y1,x2,y2;
{
    fpspos(&x1,&y1);
    fpspos(&x2,&y2);
    fprintf(fpps,"N %7.2f %7.2f moveto \n",x1,y1);
    fprintf(fpps,"%7.2f %7.2f lineto ",x2,y2);
    line_stroke();
}

flines(xs,ys,n)
double xs[],ys[];
int n;
{
    int i;
    double x,y;
    if(n > MaxConnectedLine) {
	fprintf(stderr,"Too many points to connect(psplot)\n");
	fprintf(stderr,"Ignored.\n");
	return;
    }
    for(i=0;i<n;i++) {
	x = xs[i];   y = ys[i];
	fpspos(&x,&y);
	if( i ) {
	    fprintf(fpps,"%7.2f %7.2f LT\n",x,y);
        }
	else {
	    fprintf(fpps,"N %7.2f %7.2f MT\n",x,y);
        }
    }
    line_stroke();
}

fpolygon(x,y,n,type)
double x[],y[];
int n,type;
{
    double xx,yy,x0,y0;
    int i,atype;

    if(type < 0) atype = -type;
    else         atype =  type;

    if(atype > 10 ) {
	fprintf(stderr,"Parameter error density %d (fpolygon)\n",type);
	return;
    }

    for(i=0;i<n;i++) {
	if(i) {
	    xx = x[i]; yy = y[i];
	    fpspos(&xx,&yy);
	    fprintf(fpps,"%7.2f %7.2f LT\n",xx,yy);
        } else {
	    xx = x[0]; yy = y[0];
	    fpspos(&xx,&yy);
	    x0 = xx; y0 = yy;
	    fprintf(fpps,"N %7.2f %7.2f MT\n",xx,yy);
        }
    }
    fprintf(fpps,"%7.2f %7.2f LT closepath\n",x0,y0);

    if(type) {
	fprintf(fpps,"gsave\n");
	setgray((double)((double)(10-atype)/10.0));
        fprintf(fpps,"fill grestore\n");
    }
    if(type >= 0 ) {
	line_stroke();
    }
}
	
fbox(x1,y1,x2,y2)
double x1,y1,x2,y2;
{
    fpspos(&x1,&y1);
    fpspos(&x2,&y2);
    fprintf(fpps,"N %7.2f %7.2f moveto \n",x1,y1);
    fprintf(fpps," %7.2f %7.2f  lineto \n",x2,y1);
    fprintf(fpps," %7.2f %7.2f  lineto \n",x2,y2);
    fprintf(fpps," %7.2f %7.2f  lineto \n",x1,y2);
    fprintf(fpps," %7.2f %7.2f  lineto \n",x1,y1);
    fprintf(fpps," closepath ");
    line_stroke();
}
setdash(n)
int n;
{
    if(n > DASHMAX || n < 0) {
	fprintf(stderr,"Dashpattern No.%d is not registered.\n",n);
	return;
    }
    Dashpattern = n;
}
static line_stroke()
{
    if(Dashpattern) {
	fprintf(fpps,"[%s] centerdash stroke\n",Dashes[Dashpattern-1]);
    }
    else {
	fprintf(fpps,"stroke\n");
    }
}

/**************************************************************
    cordinate system tranformation
**************************************************************/	
pspos(x,y)
int *x,*y;
{
   *x = (*x - px0) * XDOT / XLEN + GX;
   *y = (*y - py0) * YDOT / YLEN + GY;
}
fpspos(x,y)
double *x,*y;
{
   *x = (*x - (double)px0) * RATE + (double)GX; 
   *y = (*y - (double)py0) * RATE + (double)GY;
}
psrate(r)
int *r;
{
    *r = (double)(*r) * RATE;
}

/*************************************************
    circle routine
*************************************************/
circle(x,y,r)
int x,y,r;
{
    pspos(&x,&y);
    psrate(&r);
    fprintf(fpps,"%d %d %d 0 360 arc stroke\n",x,y,r);
}

linewidth(d)
double d;
{
    char st[20];
    sprintf(st,"%5.1f setlinewidth%c",d,'\0');
    fprintf(fpps,"%s\n",st);
    LINE = (int)(d * (double)LFACTOR + .5);
}
setgray(d)
double d;
{
    char st[20];
    sprintf(st,"%5.1f setgray%c",d,'\0');
    fprintf(fpps,"%s\n",st);
    GRAY = d * GFACTOR;
}
/************************************************
   Symbol write routine
************************************************/
symbol(x,y,s)
int x,y;
char *s;
{
    pspos(&x,&y);
    fprintf(fpps,"%d %d moveto (",x,y);
    while(*s) {
	if(*s == '\n') {
	    s++;
	    continue;
        }
	if(*s == '(' || *s == ')') putc('\\',fpps);
	if(*s == '\\') putc('\\',fpps);
	putc(*s++,fpps);
    }
    fprintf(fpps,") show\n");
}

fsymbol(x,y,s)
double x,y;
char *s;
{
    char *str_adjust();

    fpspos(&x,&y);
    fprintf(fpps,"%7.2f %7.2f moveto\n",x,y);
    fprintf(fpps,"(%s) show\n",str_adjust(s));
    return;
}

static char *str_adjust(s)
char *s;
{
    char *cp;
    static char adjust[MAXLINE];
    
    cp = adjust;
    while(*s) {
	if(*s == '\n') {
	    s++;
	    continue;
        }
	if(*s == '(' || *s == ')' || *s == '\\') *cp++ = '\\';
	*cp++ = *s++;
    }
    *cp = '\0';
    return(adjust);
}
    
    
fcharacter(x,y,n)
double x,y;
int n;
{
    fpspos(&x,&y);
    fprintf(fpps,"%7.2f %7.2f moveto (\\%d) show\n",x,y,n);
}

fposhow(x,y,s,type)
double x,y;
char *s;
int type;
{
    char *as;
    char *str_adjust();

    as = str_adjust(s);

    fpspos(&x,&y);
    switch(type) {
        case RIGHT_SHOW:
	    fprintf(fpps,"%7.2f %7.2f ",x,y);
	    fprintf(fpps,"(%s) RightShow\n",as);
	    break;
 	case MIDDLE_SHOW:
	    fprintf(fpps,"%7.2f %7.2f ",x,y);
	    fprintf(fpps,"(%s) MiddleShow\n",as);
	    break;
	case LEFT_SHOW:
	default:
	    fprintf(fpps,"%7.2f %7.2f moveto (%s) show\n",x,y,as);
	    break;
    }
}

fsupshow(x,y,s1,s2,type)
double x,y;
char *s1,*s2;
int type;
{
    char *str_adjust();

    fpspos(&x,&y);
    switch(type) {
	case RIGHT_SHOW:
	    fprintf(fpps,"%7.2f %7.2f (%s) (%s) %7.2f SupRightShow\n",x,y,s1,s2,Fontsize);
	    break;
        case MIDDLE_SHOW:
	    fprintf(fpps,"%7.2f %7.2f (%s) (%s) %7.2f SupMiddleShow\n",x,y,s1,s2,Fontsize);
	    break;
        case LEFT_SHOW:
        default:
	    fprintf(fpps,"%7.2f %7.2f (%s) (%s) %7.2f SupShow\n",x,y,s1,s2,Fontsize);
	    break;
    }
    return;
}

csymbol(cx,cy,s)
int cx,cy;
char *s;
{
    double x,y;
    x = (double)cx * CWIDTH;
    y = (CLINES-cy) * CWIDTH * 2.0;
    fsymbol(x,y,s);
}
cfill(cx,cy,n)
int cx,cy,n;
{
    double x,y;
    x = (double)cx * CWIDTH;
    y = (CLINES - cy)  * CWIDTH * 2.0 -1.0;
    ffill(x,y,x+(double)n * CWIDTH,y + CWIDTH + 2.0,(double)AMIGRAY);
    setgray((double)0.0);
    return;
}
ffill(x1,y1,x2,y2,gray)
double x1,y1,x2,y2,gray;
{
    fpspos(&x1,&y1);
    fpspos(&x2,&y2);
    setgray(gray);
    fprintf(fpps,"%7.2f %7.2f moveto\n",x1,y1);
    fprintf(fpps,"%7.2f %7.2f lineto\n",x2,y1);
    fprintf(fpps,"%7.2f %7.2f lineto\n",x2,y2);
    fprintf(fpps,"%7.2f %7.2f lineto\n",x1,y2);
    fprintf(fpps,"%7.2f %7.2f lineto\n",x1,y1);
    fprintf(fpps,"closepath fill\n");
    return;
}
/*************************************************
      font routine
************************************************/
font(fk,kind,psize)
int fk,kind,psize;
{
    int code,i;
    char buf[5];
    static int fonts = 0;
    static int fontcode[100];
    static char *fontname[] = {
	"Times",
	"Helvetica",
	"Courier",
	"Symbol"
    };
    static char *kindname[] = {
	"-Roman",
	"-Italic",
	"-Bold",
	"-BoldItalic",
	"",
	"-Oblique",
	"-Bold",
	"-BoldOblique"
    };
    fontcode[0] = 10;
    if(fk <0 || fk >3 || kind <0 || kind >3 || psize <0 ) {
	fprintf(stderr,"Font change ignored (%d,%d,%d)\n",fk,kind,psize);
        return;
    }
    code = fk * 1000 + kind * 100 + psize;
    Fontsize = (double)psize * CHRATE;
    if( code == Currentfont ) return;
    else Currentfont = code;
    for(i=0;i<fonts+1;i++) {
	if( code == fontcode[i]) {
	    makeno(i,buf);
	    fprintf(fpps,"Font%s setfont\n",buf);
	    return;
        }
    }

    if (fk >0) {
	kind = kind + 4;
    }
    if(fonts < 98 ) {
	fonts++;
	fontcode[fonts] = code;
	makeno(fonts,buf);
	fprintf(fpps,"/Font%s /%s%s findfont %d scalefont def\n",buf,fontname[fk],kindname[kind],psize);
	fprintf(fpps,"Font%s setfont\n",buf);
    }
    else {
        fprintf(fpps,"/%s%s  findfont %d scalefont setfont\n",fontname[fk],kindname[kind],psize);
    }

    return;

}

newpage()
{
    PAGE ++;
    fprintf(fpps,"showpage\n");
    fprintf(fpps,"\n");
    fprintf(fpps,"%% Page %d\n",PAGE);
}
/*************************************
    function dot(x,y,n,drate)
    point with assigned marker
 n=    0  peke maru 
       1  black circle
       2  black triangle
       3  black square
       4  white circle
       5  white triangle
       6  white square
*************************************/
dot(xx,yy,n,drate)
int xx,yy,n;
double drate;
{
    int linesave,graysave;
    double r;
    double x,y;

    linesave = LINE;
    graysave = GRAY;

    if(n<0 || n > 6) n = 0;
    r = 3.0 * AREAX / XDOT;
    if(drate > 0.1 || drate <5.0) r = r * drate;
    pspos(&xx,&yy);
    x = xx; y = yy;

    switch(n) {
	case 0:
	    fprintf(fpps,"N %7.2f %7.2f moveto \n",x - r/2.0,y-r/2.0);
	    fprintf(fpps,"%5.2f %5.2f rlineto stroke\n",r,r);
	    fprintf(fpps,"N %7.2f %7.2f moveto\n",x + r/2.0,y-r/2.0);
	    fprintf(fpps,"%5.2f %5.2f rlineto\n",-r,r);
	    break;
	case 1:
	case 4:
	    fprintf(fpps,"N %7.2f %7.2f %5.2f 0 360 arc ",x,y,r/2.0);
            break;
        case 2:
	case 5:
	    fprintf(fpps,"N %7.2f %7.2f moveto \n",x-r/2,y-r/2);
	    fprintf(fpps,"%5.2f 0 rlineto 0 %5.2f rlineto\n",r,r);
	    fprintf(fpps,"%5.2f 0 rlineto 0 %5.2f rlineto\n",-r,-r);
	    break;
        case 3:
	case 6:
	    fprintf(fpps,"N %7.2f %7.2f moveto \n",x,y+r/2);
	    fprintf(fpps,"%5.2f %5.2f rlineto \n",r/2,-r);
	    fprintf(fpps,"%5.2f 0 rlineto \n",-r);
	    fprintf(fpps,"%5.2f %5.2f rlineto ",r/2,r);
	    break;
        }
   if(n > 3 || n == 0) {
	if(LINE != 1) {
	    linewidth((double)0.1);
        }
	fprintf(fpps," stroke\n");
	if(linesave != 1) {
	    linewidth((double)((double)linesave/(double) LFACTOR));
        }
    }
    else {
	if(GRAY != 0) {
	    setgray((double)0.0);
        }
	fprintf(fpps," closepath fill\n");
	if(graysave) {
	    setgray((double)((double)graysave/(double)GFACTOR));
        }
    }
}
    
fdot(x,y,n,drate)
double x,y;
int n;
double drate;
{
    int linesave,graysave;
    double r;

    linesave = LINE;
    graysave = GRAY;

    if(n<0 || n > 6) n = 0;
    r = 3.0 * AREAX / XDOT;
    if(drate > 0.1 && drate <5.0) r = r * drate;

    fpspos(&x,&y);

    switch(n) {
	case 0:
	    fprintf(fpps,"N %7.2f %7.2f moveto \n",x - r/2.0,y-r/2.0);
	    fprintf(fpps,"%5.2f %5.2f rlineto\n",r,r);
	    fprintf(fpps,"0 %5.2f rlineto\n",-r);
	    fprintf(fpps,"%5.2f %5.2f rlineto\n",-r,r);
	    break;
	case 1:
	case 4:
	    fprintf(fpps,"N %7.2f %7.2f %5.2f 0 360 arc ",x,y,r/2.0);
            break;
        case 2:
	case 5:
	    fprintf(fpps,"N %7.2f %7.2f moveto \n",x-r/2,y-r/2);
	    fprintf(fpps,"%5.2f 0 rlineto 0 %5.2f rlineto\n",r,r);
	    fprintf(fpps,"%5.2f 0 rlineto 0 %5.2f rlineto\n",-r,-r);
	    break;
        case 3:
	case 6:
	    fprintf(fpps,"N %7.2f %7.2f moveto \n",x,y+r/2);
	    fprintf(fpps,"%5.2f %5.2f rlineto \n",r/2,-r);
	    fprintf(fpps,"%5.2f 0 rlineto \n",-r);
	    fprintf(fpps,"%5.2f %5.2f rlineto ",r/2,r);
	    break;
        }
   if(n > 3 || n == 0) {
	if(LINE != 1) {
	    linewidth((double)0.1);
        }
	fprintf(fpps," stroke\n");
	if(linesave != 1) {
	    linewidth((double)((double)linesave/(double) LFACTOR));
        }
    }
    else {
	if(GRAY != 0) {
	    setgray((double)0.0);
        }
	fprintf(fpps," closepath fill\n");
	if(graysave) {
	    setgray((double)((double)graysave/(double)GFACTOR));
        }
    }
}








#define BSIZE 512
#define HOMED 5
#define UNAME 4

gethd(uid,uname,dir)
int uid;
char *uname,*dir;
{
    char buf[BSIZE];
    FILE *fp;

    if( (fp = fopen("/etc/passwd","r")) == NULL ) {
	printf("Cannot open /etc/passwd.(gethd)\n");
	exit(1);
    }

    while(fgets(buf,BSIZE,fp) ) {
	if(uid == bgetuid(buf) ) {
	    bgethd(buf,dir,HOMED);
	    bgethd(buf,uname,UNAME);
	    return;
        }
    }
    strcpy(dir,"?????");
    return;
}
bgetuid(buf)
char *buf;
{
    int i;
    char num[100];
    i = 0;
    while(i < 2) {
	if(*buf == ':' ) i++;
	buf++;
    }
    i = 0;
    while(*buf != ':') {
	num[i] = *buf++;
	i++;
    }
    num[i] = '\0';
    return(atoi(num));
}
bgethd(buf,dir,po)
char *buf,*dir;
int po;
{
    int i;
    i = 0;
    while(i < po ) {
	if(*buf == ':' ) i++;
	buf++;
    }
    while(*buf != ':' ) {
	*dir = *buf;
	dir++;  buf++;
    }
    *dir = '\0';
}


makeno(i,buf)
int i;
char *buf;
{
    i = i % 100;
    *buf++ = (i/10)+'0';
    *buf++ = (i % 10) + '0';
    *buf = '\0';
}
