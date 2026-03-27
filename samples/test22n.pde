mesh {
  point a(0,0),b(0.6,0),e(0.6,0.2);
  point c(0.6,1),d(0,1);

  region reg1[tri](a,b,e,c,d);

  edge bc(b,e,c),cd(c,d);

  edge ab(a,b);

  domain dom1(reg1);
 vertices(100);

}

var {
  fem u[P2];
  double dk;
  double ue;
}

scheme {

  dk = 750;

  solve[u;tu] {
   solver skyline;
   quadrature tri4;

   weq: integral(52* dx(u)*dx(tu)+ 52*dy(u)*dy(tu))=-bintegral(g * tu);

   dbc: u = 100, on ab;
   nbc: g = dk*u, on bc,cd;
  }
}
   

