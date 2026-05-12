mesh { point a(0,0), b(20,0), c(20,20), d(0,20); region reg1[tri](a,b,c,d); edge dedge(a,b,c,d,a); domain dom1(reg1); nodes dom1(6000); }
var {
  fem u[P2], un[P2];
  fem w[P2], zz[P2];

  double dt, dtr;
  double pi = 3.1415926535;
  int iptr;
}

scheme {

  dt  = 0.0000001;
  dtr = 1.0/dt;

  iptr = 0;

  un = 0.05*sin(2.0*pi*x/20.0)
     + 0.04*sin(2.0*pi*y/20.0)
     + 0.02*sin(2.0*pi*(x+y)/20.0);

loop:

  iptr = iptr + 1;
  write(iptr);

  solve[w,zz,u] {

    linear method: skyline;
    quadrature method: tri4;

    /* w = -Δu */
    weq:
        w*$
      - dx(u)*dx($)
      - dy(u)*dy($);

    /* z = -Δw = Δ²u */
    weq:
        zz*$
      - dx(w)*dx($)
      - dy(w)*dy($);

    /* 6次KS */
    weq:
        dtr*u*$ - dtr*un*$

      + un*dx(u)*$

      - w*$

      - dx(w)*dx($)
      - dy(w)*dy($)

      + dx(zz)*dx($)
      + dy(zz)*dy($);
  }

  un = u;

  contour[u](mesh=off);

goto loop;

}
