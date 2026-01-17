mesh {
  dimension 2;

  double length = 1000;
  double r = length*0.5*0.5;
  double or = length / 2.0;
  double cx = length/2.0, cy = length/2.0;

  double pe = 8;
  double pr = 0.3;
 
/*   point a(0,0),b(length,0),c(length,length),d(0,length); */
 
/*  pedge hole[(r*cos(t)+cx,r*sin(t)+cy),t=0,6.28,30]; */
  pedge hole[((r+r*cos(pe*t)*pr)*cos(t)+cx,(r+r*cos(pe*t)*pr)*sin(t)+cy),t=0,6.28];
  pedge outer[(or*cos(t)+cx,or*sin(t)+cy),t=0,6.28];

  region reg1[tri](outer:[hole]);

  domain dom(reg1);
  vertices (10000);
}
