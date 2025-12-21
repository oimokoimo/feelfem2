mesh {
  point a(0,0),b(1,0),c(1,1),d(0,1);

  domain dom(a,b,c,d);
  line abcd(a,b,c,d);
  line da(d,a);
}

var {
  fem u[P1];  /* 四辺形一次要素 */
}

scheme {


  solve[u]{

   eq: lap(u) = -4;
   dbc: u = x*x+y*y,on abcd;
   dbc: u = x*x+y*y,on da;
  }
  perspect[u];

}
