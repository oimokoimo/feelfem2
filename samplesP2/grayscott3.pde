mesh {
  point a(0,0), b(2,0), c(2,2), d(0,2);
  region reg1[tri](a,b,c,d);
  edge dedge(a,b,c,d,a);
  domain dom1(reg1);
  nodes dom1(10000);
}

var {
  fem u[P1], un[P1], v[P1], vn[P1];

  double dt, dtr;
  double diffu, diffv;
  double feed, kill;
  int iptr;
}

scheme {

  dt    = 0.2;
  dtr   = 1.0/dt;

  diffu = 0.00002;
  diffv = 0.00001;

  feed  = 0.031;
  kill  = 0.057;

  iptr  = 0;

  /* ---- symmetry を崩した初期条件 ---- */
  un = 1.0
     - 0.60*exp(-28.0*(1.2*(x-1.02)*(x-1.02)+0.8*(y-0.98)*(y-0.98)))
     - 0.18*exp(-120.0*((x-0.82)*(x-0.82)+(y-1.10)*(y-1.10)))
     - 0.15*exp(-100.0*((x-1.22)*(x-1.22)+(y-0.92)*(y-0.92)))
     - 0.12*exp(-140.0*((x-0.95)*(x-0.95)+(y-0.78)*(y-0.78)));

  vn = 0.45*exp(-28.0*(1.2*(x-1.02)*(x-1.02)+0.8*(y-0.98)*(y-0.98)))
     + 0.14*exp(-120.0*((x-0.82)*(x-0.82)+(y-1.10)*(y-1.10)))
     + 0.12*exp(-100.0*((x-1.22)*(x-1.22)+(y-0.92)*(y-0.92)))
     + 0.10*exp(-140.0*((x-0.95)*(x-0.95)+(y-0.78)*(y-0.78)));

  contour[un](mesh=off);
  contour[vn](mesh=off);

iter:
  iptr = iptr + 1;

  solve[u] {
    linear method: skyline;
    quadrature method: tri4;

    weq: dtr*(u-un)*$
       + diffu*(dx(u)*dx($)+dy(u)*dy($))
       + (vn*vn)*u*$
       + feed*u*$
       - feed*$;

    dbc: u = 1.0, on dedge;
  }

  solve[v] {
    linear method: skyline;
    quadrature method: tri4;

    weq: dtr*(v-vn)*$
       + diffv*(dx(v)*dx($)+dy(v)*dy($))
       + (feed+kill)*v*$
       - un*vn*vn*$;

    dbc: v = 0.0, on dedge;
  }

    write(iptr);
    contour[u](mesh=off);
    contour[v](mesh=off);

  un = u;
  vn = v;

  if (iptr < 4000) goto iter;
}
