geom {

 problem neumann_test;

 mesher gid;
 dimension 3;

 surface ( outer, koimo );
 region ( reg1,reg2 );
}

var {

  fem u[T1];
  fem v[TEST1];

  double s,d;
  ewise a;
}

element TEST1[tetra] {
  (0,0,0): 1-r-s-t;
  (1,0,0): r;
  (0,1,0): s;
  (0,0,1): t;
}

scheme {

 ProgramModel feelfem90;

 solve[u,v;tu,tv] {
   solver skyline;
   parametric T2;

   weq: integral(v*dx(u)*dx(tu)+dy(u)*dy(tu)+dz(u)*dz(tu)) = integral(-6 * tu)+bintegral(g*tu*s);
   weq: integral(v*dx(u)*dx(tv)+dy(u)*dy(tv)+dz(u)*dz(tv)) = integral(-6 * tu)+bintegral(g*tu*s);
   dbc: u = x*x+y*y+z*z, on  outer,koimo;
   nbc: g = v*nx*x*d-u,on koimo; 
 }
}

