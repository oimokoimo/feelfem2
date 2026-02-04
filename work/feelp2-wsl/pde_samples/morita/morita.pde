mesh {
  point a00(25.000,0),b00(25.000,100);
  point a01(25.521,0),b01(25.521,100);
  point a02(26.042,0),b02(26.042,100);
  point a03(26.562,0),b03(26.562,100);
  point a04(27.083,0),b04(27.083,100);
  point a05(27.604,0),b05(27.604,100);
  point a06(28.125,0),b06(28.125,100);
  point a07(28.646,0),b07(28.646,100);
  point a08(29.167,0),b08(29.167,100);
  point a09(29.687,0),b09(29.687,100);
  point a10(30.208,0),b10(30.208,100);
  point a11(30.729,0),b11(30.729,100);
  point a12(31.250,0),b12(31.250,100);
  point a13(31.771,0),b13(31.771,100);
  point a14(32.292,0),b14(32.292,100);
  point a15(32.812,0),b15(32.812,100);
  point a16(33.333,0),b16(33.333,100);
  point a17(33.854,0),b17(33.854,100);
  point a18(34.375,0),b18(34.375,100);
  point a19(34.896,0),b19(34.896,100);
  point a20(35.417,0),b20(35.417,100);
  point a21(35.938,0),b21(35.938,100);
  point a22(36.458,0),b22(36.458,100);
  point a23(36.979,0),b23(36.979,100);
  point a24(37.500,0),b24(37.500,100);
  point a25(38.021,0),b25(38.021,100);
  point a26(38.542,0),b26(38.542,100);
  point a27(39.063,0),b27(39.063,100);
  point a28(39.583,0),b28(39.583,100);
  point a29(40.104,0),b29(40.104,100);
  point a30(40.625,0),b30(40.625,100);
  point a31(41.146,0),b31(41.146,100);
  point a32(41.667,0),b32(41.667,100);
  point a33(42.188,0),b33(42.188,100);
  point a34(42.708,0),b34(42.708,100);
  point a35(43.229,0),b35(43.229,100);
  point a36(43.750,0),b36(43.750,100);
  point a37(44.271,0),b37(44.271,100);
  point a38(44.792,0),b38(44.792,100);
  point a39(45.313,0),b39(45.313,100);
  point a40(45.833,0),b40(45.833,100);
  point a41(46.354,0),b41(46.354,100);
  point a42(46.875,0),b42(46.875,100);
  point a43(47.396,0),b43(47.396,100);
  point a44(47.917,0),b44(47.917,100);
  point a45(48.438,0),b45(48.438,100);
  point a46(48.958,0),b46(48.958,100);
  point a47(49.479,0),b47(49.479,100);
  point a48(50.000,0),b48(50.000,100);

  region reg1[rect](
    a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,
    a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,
    a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,
    a30,a31,a32,a33,a34,a35,a36,a37,a38,a39,
    a40,a41,a42,a43,a44,a45,a46,a47,a48,
    b48,b47,b46,b45,b44,b43,b42,b41,b40,b39,
    b38,b37,b36,b35,b34,b33,b32,b31,b30,b29,
    b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,
    b18,b17,b16,b15,b14,b13,b12,b11,b10,b09,
    b08,b07,b06,b05,b04,b03,b02,b01,b00  );

  edge la(
    a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,
    a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,
    a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,
    a30,a31,a32,a33,a34,a35,a36,a37,a38,a39,
    a40,a41,a42,a43,a44,a45,a46,a47,a48  );

  edge lb(
    b00,b01,b02,b03,b04,b05,b06,b07,b08,b09,
    b10,b11,b12,b13,b14,b15,b16,b17,b18,b19,
    b20,b21,b22,b23,b24,b25,b26,b27,b28,b29,
    b30,b31,b32,b33,b34,b35,b36,b37,b38,b39,
    b40,b41,b42,b43,b44,b45,b46,b47,b48  );

  edge lc(a00,b00);

  edge ld(a48,b48);

  domain dom1(reg1);
  nodes dom1(1);

}
var {                                    
  double t1,t2; /* thermal */
  double d1,d2; /* coeficient */
  double d3,d4,d5; /* coeficient */
  double e,mu; /* young's rate, poisson's rate */
  double g; /* strain rate */
  double alpha; /* heat derivative rate */
  double r1,r2; /* axial length */
  
  fem  u[Q2], v[Q2];  /* 8-node serendipity element */
  fem ex[Q2],ey[Q2];  /* for strain */
  fem sx[Q2],sy[Q2];  /* for stress */
  fem ti[Q2];   /* thermal */
  fem xi[Q2];   /* 1/x */

}

scheme {
  t1 = 350;
  t2 = 300;
  r1 = 25;
  r2 = 50;
  e = 21000000000;
  mu = 0.3;
  g = e / 2 / ( 1 + mu );
  alpha = 0.00001;
  d1 = e * ( 1 - mu ) / ( 1 + mu ) / ( 1 - 2*mu );
  d2 = e * mu / ( 1 + mu ) / ( 1 - 2*mu );
  d3 = alpha * e / ( 1 - 2*mu );
  d4 = ( t2 - t1 ) / ( dlog(r2) - dlog(r1) );
  d5 = t1 - d4 * dlog(r1);

  ti = d3 * ( d5 + d4 * dlog(x) );
  xi = 1 / x;

  solve[u,v]{        
   linear method: skyline;
   quadrature method: gauss3x3; 
   weq: d1*dx(u)*dx($) + d2*u*xi*dx($) + d2*dy(v)*dx($)
      + g*dy(u)*dy($) + g*dx(v)*dy($) - ti*dx($)
      - 2*g*xi*dx(u)*$ + 2*g*u*xi*xi*$, <-Tx*$>;
   weq: g*dy(u)*dx($) + g*dx(v)*dx($) + d2*dx(u)*dy($)
      + d2*u*xi*dy($) + d1*dy(v)*dy($) - ti*dy($)
      - g*xi*dy(u)*$ - g*xi*dx(v)*$, <-Ty*$>;
   dbc: v = 0, on la;
   dbc: v = 0, on lb;
   nbc: Tx = 0, Ty = 0, on lc;
   nbc: Tx = 0, Ty = 0, on ld;
  }
  solve[ex] {
    linear method:skyline;
    quadrature method: gauss3x3;
    weq: ex * $ - dx(u)*$;
  }
  solve[ey] {
    linear method:skyline;
    quadrature method: gauss3x3;
    weq: ey * $ - dy(v)*$;
  }
  sx = d1*ex + d2*u/x + d2*ey - ti;
  sy = d2*ex + d2*u/x + d1*ey - ti;

  /* display result */
  xplot[la,x,sx](winsiz=800);
  displacement[u,v](mesh=off,val=sx,winsiz=800,fact=20.0);
}

