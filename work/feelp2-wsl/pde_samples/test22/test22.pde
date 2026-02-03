mesh {
  point a(0,0),b(0.6,0),e(0.6,0.2);
  point c(0.6,1),d(0,1);

  region reg1[tri](a,b,e,c,d);

  edge bc(b,e,c),cd(c,d);

  edge ab(a,b);

  domain dom1(reg1);
  nodes dom1(5000);

}

var {
  fem u[P2];
  double dk;
  double ue;
  double h;
}

scheme {
  dk = 750;

  solve[u] {
   linear method: skyline;
   quadrature method: tri4;

   weq: 52 * dx(u)*dx($)+ 52*dy(u)*dy($),<g * $>;

   dbc: u = 100, on ab;
   nbc: g = dk*u, on bc,cd;
  }
 
  contour[u];
  perspect[u];
}
   

