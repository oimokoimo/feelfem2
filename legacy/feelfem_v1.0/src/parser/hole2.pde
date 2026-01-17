mesh {
  dimension 2;

  double length = 1000;
  double r = length*0.5*0.5;
  double or = length / 2.0;
  double ir = length / 8.0;
  double cx = length/2.0, cy = length/2.0;

  double pe = 6;
  double pr = 0.3;
  double pi = 3.14159265;
 
  pedge hole[((r+r*cos(pe*t)*pr)*cos(t)+cx,(r+r*cos(pe*t)*pr)*sin(t)+cy),t=0,6.28];
  pedge inner[((ir+ir*cos(pe*t)*pr)*cos(t+pi/pe)+cx,(ir+ir*cos(pe*t)*pr)*sin(t+pi/pe)+cy),t=0,6.28];

  pedge outer[((or+or*cos(pe*t)*pr)*cos(t+pi/pe)+cx,(or+or*cos(pe*t)*pr)*sin(t+pi/pe)+cy),t=0,6.28];

  region reg1[tri](outer:[hole]);
  region reg2[tri](inner);
 

  domain dom(reg1,reg2);
  vertices (20000);
}
