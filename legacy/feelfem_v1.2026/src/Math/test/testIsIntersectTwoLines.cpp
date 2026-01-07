#include <iostream.h>

int isIntersectTwoLines(double,double,double,double,
			double,double,double,double);

int main(void)
{
   double x1,y1,x2,y2;
   double s1,t1,s2,t2;



   cout << "x1 = ";
   cin  >> x1;

   cout << "y1 = ";
   cin  >> y1;

   cout << "x2 = ";
   cin  >> x2;

   cout << "y2 = ";
   cin  >> y2;


   cout << "s1 = ";
   cin  >> s1;

   cout << "t1 = ";
   cin  >> t1;

   cout << "s2 = ";
   cin  >> s2;

   cout << "t2 = ";
   cin  >> t2;

   cout << "ret = " << isIntersectTwoLines(x1,y1,x2,y2,s1,t1,s2,t2);

}


