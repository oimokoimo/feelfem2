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

  /* ---- Gray-Scott parameters ---- */
  dt    = 0.2;
  dtr   = 1.0/dt;

  diffu = 0.00002;
  diffv = 0.00001;

  feed  = 0.04;
  kill  = 0.06;

  iptr  = 0;

  /* ---- Initial condition ----
     u is almost 1 everywhere,
     v has a few localized seeds
  */
  un = 1.0
     - 0.50*exp(-80.0*((x-1.00)*(x-1.00)+(y-1.00)*(y-1.00)))
     - 0.20*exp(-120.0*((x-0.78)*(x-0.78)+(y-1.16)*(y-1.16)))
     - 0.20*exp(-120.0*((x-1.20)*(x-1.20)+(y-0.82)*(y-0.82)));

  vn = 0.40*exp(-80.0*((x-1.00)*(x-1.00)+(y-1.00)*(y-1.00)))
     + 0.18*exp(-120.0*((x-0.78)*(x-0.78)+(y-1.16)*(y-1.16)))
     + 0.18*exp(-120.0*((x-1.20)*(x-1.20)+(y-0.82)*(y-0.82)));

  contour[un](mesh=off);
  contour[vn](mesh=off);

iter:
  iptr = iptr + 1;

  /* ---- Step 1 : update u ----
     u_t = diffu * Laplacian(u) - u*vn^2 + feed*(1-u)

     Linearized by using vn from previous step:
     u_t = diffu * Laplacian(u) - (vn^2)u + feed - feed*u
  */
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

  /* ---- Step 2 : update v ----
     v_t = diffv * Laplacian(v) + un*vn^2 - (feed+kill)*v

     Nonlinear production term is treated explicitly
     with old values un, vn.
  */
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

  if (iptr < 2000) goto iter;
}
