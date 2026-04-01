mesh {
  point a(0,0),b(2,0),c(2,2),d(0,2);
  region reg1[tri](a,b,c,d);
  edge dedge(a,b,c,d,a);
  domain dom1(reg1);
  nodes dom1(6000);
}

var {
  fem u[P1],un[P1],w[P1],wn[P1];

  double dt,dtr;
  double diffu,diffw;
  double alpha,beta,gam;
  double a1,b1;
}

scheme {

  dt    = 0.001;
  dtr   = 1.0/dt;
  

  diffu = 0.0005;
  diffw = 0.01;

  alpha = 18.0;
  beta  = 0.8;
  gam = 10.0;

  a1    = 0.18;
  b1    = 0.58;

/*  !
  ! 非対称な初期値
  ! 中央付近に「大1個＋小2個」を斜め配置
  ! glider の種っぽいものを狙う
  !
*/


un = 1.2*exp(x);

/*
+(y-1.05)*(y-1.05))) + 0.9*exp(m140*((x-1.08)*(x-1.08)+(y-0.92)*(y-0.92))) + 0.7*exp(m140*((x-0.88)*(x-0.88)+(y-0.86)*(y-0.86)));
un = 1.2*exp(m80*((x+0.95)*(x+0.95)+(y-1.05)*(y-1.05))) + 0.9*exp(m140*((x-1.08)*(x-1.08)+(y-0.92)*(y-0.92))) + 0.7*exp(m140*((x-0.88)*(x-0.88)+(y-0.86)*(y-0.86)));
*/


 contour[un];

iter:

 /* !
  ! step 1: 近傍平均っぽい補助場 w
  !         -diffw Δw + w = un
  !
*/
  solve[w] {
    linear method: skyline;
    quadrature method: tri4;

    weq: diffw*(dx(w)*dx($)+dy(w)*dy($)) + w*$ - un*$;
    dbc: w = 0, on dedge;
  }

/*  !
  ! step 2: u の時間発展
  !
  !   (u-un)/dt - diffu Δu
  !      = alpha*w*(w-a1)*(b1-w) - beta*u - gam*w*u
  !
  ! 中密度で誕生、過密で死ぬ
  !
*/
  solve[u] {
    linear method: skyline;
    quadrature method: tri4;

    weq: dtr*(u-un)*$
       + diffu*(dx(u)*dx($)+dy(u)*dy($))
       - alpha*w*(w-a1)*(b1-w)*$
       + beta*u*$
       + gam*w*u*$;

    dbc: u = 0, on dedge;
  }

  contour[u](mesh=off);

  un = u;
  wn = w;

  goto iter;
}
