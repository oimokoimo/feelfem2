mesh {
  point a(0,0), b(2,0), c(2,2), d(0,2);
  region reg1[tri](a,b,c,d);
  edge dedge(a,b,c,d,a);
  domain dom1(reg1);
  nodes dom1(6000);
}

var {
  fem u[P1], un[P1];
  fem w[P1], wn[P1];

  double dt, dtr;
  double pi = 3.1415926535;
  int iptr;
}

scheme {

  dt  = 0.001;
  dtr = 1.0/dt;

  iptr = 0;

  /* --- 初期条件（軽く対称性を壊す） --- */
  un = 0.05*sin(2.0*pi*x)
     + 0.04*sin(2.0*pi*y)
     + 0.02*sin(2.0*pi*(x+y))
     + 0.01*exp(-40.0*((x-1.05)*(x-1.05)
                      +(y-0.93)*(y-0.93)));

  wn = 0.0;

  u = un;
  w = wn;
}

scheme {
    iptr = 0;

    loop:
    iptr = iptr +1;
    write(iptr);

/* まず既知 un から w = -Δun を作る */
solve[w] {
  weq: w*$ - dx(un)*dx($) - dy(un)*dy($);
}

/* その w を使って u を進める */
solve[u] {
  weq: dtr*u*$ - dtr*un*$
     + un*dx(u)*$
     - dx(u)*dx($) - dy(u)*dy($)
     + dx(w)*dx($) + dy(w)*dy($);
}


    un = u;
    wn = w;
 
    contour[u](mesh=off); 

  goto loop;
}

