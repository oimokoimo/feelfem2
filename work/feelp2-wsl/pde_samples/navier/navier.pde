mesh {

  point a(0,0),b(1.5,0),c(1.5,2),d(2.8,2.5);
  point e(2.8,5.5),f(1.5,6),g(1.5,7),h(3,7);
  point i(3,0),j(8,0),k(8,6),l(8.5,6);
  point m(8.5,0),n(10,0),o(10,10),p(8.5,10);
  point q(8.25,8),r(8,10);
  point s(6.5,10),t(6.5,3),u(4.5,2);
  point v(6,3.5),w(6,5.5),x(4.5,6);
  point y(4.5,7),z(6,7),za(6,10),zb(0,10);


  region reg1[tri](a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,za,zb);

  edge inflow(a,b),outflow(m,n);
  edge bottom(b,c,d,e,f,g,h,i,j,k,l,m); 
  edge upper(n,o,p,q,r,s,t,u,v,w,x,y,z,za,zb,a);

  domain dom1(reg1); 
  nodes dom1(2000);

}

element P1b[tri]
{
(0,0): 1-r-s;
(1,0): r;
(0,1): s;
(1/3,1/3): (1-r-s)*r*s;
}

var {

  double e,e2,ev;
  double ee;
  double re;
  int    step;
  
  fem u[P2],v[P2],u0[P2],v0[P2]; 
  fem p[P1],p0[P1],perr[P1]; 

  fem up[P2],vp[P2],pp[P2],pperr[P1];
  fem uerr[P2];

  fem w[P2],s[P1];

  double pata,patm;

  double umax,ugmax,vmax,vgmax,pmax,pgmax;
}


scheme {

  
  u  = 0;      /* Initial value both for solve and u0,v0,p0 */
  v  = 0;
  p  = 0; 

  re = 0.01;   /* Reynolds Number */ 

  e  = 0.0; 
  e2 = 0.01;
  ev = 1.0/0.00001;
  ee = e - e2;
  step = 0;



  iter:
   p0 = p;
   u0 = u;
   v0 = v;

  step = step + 1;
  write('step=',step);
  solve[u,v,p]{
   linear method: skyline;
   quadrature method: tri4; 
   initial u = u;
   initial v = v;
   initial p = p;
   nonlinear;

   weq:re*dx(u)*dx($)+re*dy(u)*dy($)+u*dx(u)*$+v*dy(u)*$  + dx(p) * $  ;
   weq:re*dx(v)*dx($)+re*dy(v)*dy($)+u*dx(v)*$+v*dy(v)*$  + dy(p) * $;
   weq: dx(u)*$ + dy(v)*$ - e2 * p * $  - ee * p0 * $;

   dbc: u =  0,on inflow,outflow,bottom,upper;
   dbc: v =   0.5625 - (x- 0.75)*(x- 0.75),on inflow;
   dbc: v =  -0.5625 + (x- 9.25)*(x- 9.25),on outflow;
   dbc: v =  0, on bottom,upper;

  }

/*  MAXnorm[pmax,p0 - p];  MAXnorm[pgmax, p];
  MAXnorm[umax,u - u0];  MAXnorm[ugmax, u];
  MAXnorm[vmax,v - v0];  MAXnorm[vgmax, v];
*/

/*  pgmax = pmax/pgmax;
  ugmax = umax/ugmax;
  vgmax = vmax/vgmax;
*/

  write('pmax/pgmax ',pgmax);
  write('umax/ugmax ',ugmax);
  write('vmax/vgmax ',vgmax);

  perspect[p];
  showvec[u,v];

/*  if(pgmax > 1.0e-8) goto iter;
  if(ugmax > 1.0e-8) goto iter;
  if(vgmax > 1.0e-8) goto iter;
*/

  /* calculate UZUDO and stream function */
  solve[w] {
    quadrature method: tri4;
    weq: w *$ - dx(v)*$ + dy(u)*$;
  }

  solve[s] {
    quadrature method: tri4;
    weq: dx($)*dx(s) + dy($)*dy(s) - w * $,<g * $>;
    dbc: s = 0, on bottom;
    dbc: s = 0.75*0.75*0.75*2.0/3.0, on upper;
  }

  contour[s];

  adaptmesh[u*u+v*v];

}
