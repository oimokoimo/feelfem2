mesh {
  dimension 2;

  double len= 100;
  double cx = 0, cy = 0;

  point a(cx,cy),b(cx+len,cy),c(cx+len,cy+len),d(cx,cy+len);
/*  point h(cx+len*1.5,cy+len*0.5);  */
/*  edge ab(a,b); */
  edge bc(b,c);

/*  pedge oimo(a,b)[(t,t*(100.0-t)*0.03),t=0,100,20];  */
  pedge oimo(a,b)[(t,-sin(t*3.14/50)*30),t=cx+10,len,20];  

  point ha(80,50);
  point hb(50+cos(6.0)*10,50+sin(6.0)*10); 

  point h(cx+len*1.5,cy+len*0.5);

  double r = 20;
/*  pedge hole(ha,hb)[(50+r*cos(t),50+r*sin(t)),t=0,6.0,20];  */
  pedge hole(,ha)[(50+r*cos(t),50+r*sin(t)),t=0,6.0,20];  

/*  region reg1[tri](a,oimo,b,c,d:[ha,hole,hb]); */
  region reg1[tri](a,oimo,b,c,d:[hole]);



  region reg2[tri](b,h,c); 
  domain dom1(reg1,reg2);
  vertices (500);

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
   (-1, 1)[DX]:  (r- 1)*(1+s)*(1+r-s)*0.25 + t4 * (1-r*r)*(1-s*s);

}

/* quadrature oimo[oimo]
{
 double a;
}
*/


var {
  double a,b;
  double c;
  const ca=40;
  const cb=40.5;
  const cc=40.0;

  fem u[P1],v[P1];
  fem p[P2];
/*  vfem pv[P2];
  vfem uv[P1],vv[P1]; */

  ewise o[P1],g[gauss3x3],d,e;
  
}

scheme {
  ProgramModel feelfem90;
  /* A ProgramModel feelfem90; */


  itr:

  a = 20;
  b = 2* 4, at a,b,c;
  c = 20*sin(20,20), on face1,face2;
  d = b*c, in region1;
/*  e = 10, where(c > 10); */
  g = sin(20*k,20*k);











  solve [u,v;tu,tv] {
    solver oimo;  
    quadrature koimo;
    nonlinear Newton;

    weq: integral(a*x*k*dx(u)*dx(tf)*p+y*k*dy(u)*dy(tf)*q) -
        integral[oimo](u*tf)=bintegral(g*tf); 
 
   dbc: u = -1,on left,right;
   nbc: g = b*(10-u),q=100, on right;
  }

}
