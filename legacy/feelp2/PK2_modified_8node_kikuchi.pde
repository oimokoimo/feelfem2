mesh {
  point a(0,0),b(100,0),c(100,10),d(0,10);

  region reg1[rect](a,b,c,d);

  edge left(d,a);
  edge right(b,c);
  edge up(c,d);

  domain dom1(reg1); 
  nodes dom1(100);
}

var {
  double a,b,c;
  double ub,uc,e,myu;
  double  f;
  double  xf,yf;
  int     k;
  double dc,dL;
  double rdc,rdL;
  
  fem u[PK2];  /* Using Kikuchi's 8-node modified serendipity element defined below */
  fem v[PK2];
  fem uex[PK2],vex[PK2];
  fem sa[PK2];
}

element PK2[rect]
{
    double d1;
    double d2;
    double d3;
    double d4;

    double t1;
    double t2;
    double t3;
    double t4;
    double t5;
    double t6;
    double t7;
    double t8;

    d1 = (x2-x1)*(y4-y1)-(x4-x1)*(y2-y1);
    d2 = (x3-x2)*(y1-y2)-(x1-x2)*(y3-y2);
    d3 = (x4-x3)*(y2-y3)-(x2-x3)*(y4-y3);
    d4 = (x1-x4)*(y3-y4)-(x3-x4)*(y1-y4);

    t1 = (d1 - d3 )/(d1 + d3)/8.0;
    t2 = (d2 - d4 )/(d2 + d4)/8.0;
    t3 = (d3 - d1 )/(d3 + d1)/8.0;
    t4 = (d4 - d2 )/(d4 + d2)/8.0;

    t5 = (d4 - d1 )/(d1 + d3)/4.0;
    t6 = (d1 - d2 )/(d2 + d4)/4.0;
    t7 = (d2 - d3 )/(d3 + d1)/4.0;
    t8 = (d3 - d4 )/(d4 + d2)/4.0;

   (-1,-1):  (r- 1)*(1-s)*(1+s+r)*0.25 + t1 * (1-r*r)*(1-s*s);
   ( 1,-1):  -(1+r)*(1-s)*(1-r+s)*0.25 + t2 * (1-r*r)*(1-s*s);
   ( 1, 1):  -(1+r)*(1+s)*(1-s-r)*0.25 + t3 * (1-r*r)*(1-s*s);
   (-1, 1):  (r- 1)*(1+s)*(1+r-s)*0.25 + t4 * (1-r*r)*(1-s*s);

   ( 0,-1):  (1-r*r)*(1-s)*0.5         + t5 * (1-r*r)*(1-s*s);
   ( 1, 0):  (1+r)*(1-s * s)*0.5       + t6 * (1-r*r)*(1-s*s);
   ( 0, 1):  (1- r*r)*(1+s)*0.5        + t7 * (1-r*r)*(1-s*s);
   (-1, 0):  (1-r)*(1- s*s)*0.5        + t8 * (1-r*r)*(1-s*s);
}

scheme {

  e = 1.0d7;
  dL = 100.0d0;  rdL = 1.0d0/dL;
  dc = 10.0d0;   rdc = 1.0d0/dc;

  uex = 120.0*x*x*y - 92.0*y*y*y- 60.0*dc*x*x  - 240.0*dL*y*x +
	138.0*dc*y*y+120.0*dL*dc*x - 46*dc*dc*y;
  uex = uex / e /dc / dL; 

  vex = -40.0*x*x*x - 36.0*x*y*y + 120.0*dL*x*x + 36.0*dc*x*y +
        36.0*dL*y*y +46*dc*dc*x  - 36.0*dc*dL*y;
  vex = vex / e /dc / dL;


  iter:

  e = 1.0d7;
  myu = 0.3;
  write ('input E(Elasc modulus)',e);
  write ('input myu(Poisson Ratio)',myu);

  a   = e / ( 1 - myu * myu);
  b   = e / (2 * ( 1 + myu));
  c   = a * myu;

/*  yy = y;
    xx = x; */

  write('input fuou xf,yf ');
  read(xf,yf);
  write('xf=',xf,'  yf=',yf); 


  solve[u,v]{
/*   domain: dom; */
   linear method: skyline;
   quadrature method: gauss3x3;  
   boundary quadrature: 6;

  weq:  a * dx(u)*dx($) + b*dy(u)*dy($) + c * dy(v)*dx($) + 
	b * dx(v)*dy($),<- Tx * xf * $>;

  weq:  b * dx(v)*dx($) + a*dy(v)*dy($) + c * dx(u)*dy($) + 
	b * dy(u)*dx($),<- Ty * yf * $>;

   dbc: u = 0, on left;
   dbc: v = 0, on a;
   nbc: Ty = 0 , Tx = -1.0*(240.0d0*y*rdc - 120.0d0), on right;
  }

  contour[u](mesh=off,mesg='PK2');
  contour[uex](mesh=off,mesg='exact');
  sa = u- uex;
  perspect[sa];
}
