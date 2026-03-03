geom { 
  problem sample;

  dimension 3;
  mesher gid;

  surface( fixed, water);
  point (pa);
  region ( normal, steel );
}

var {
  fem u[T1];
  double dk;
  ewise  rho;
  double fixtemp     = 100.0;
  double steel_rho = 200.0;
}

scheme {

  rho =  52.0;
  rho = steel_rho, in steel;
  dk = 750.0;

  solve[u;tu] {
   solver skyline;
   quadrature tet3;

   weq: integral(rho*(dx(u)*dx(tu)+dy(u)*dy(tu)+dz(u)*dz(tu)))=-bintegral(g * tu);
   dbc: u = fixtemp, on fixed;
   nbc: g = dk*(u-0), on water;
  }
  
/*  output[u*200.0](gid,label=temperature,step=i);
  i= i+1;
  goto iteration;
*/
}
