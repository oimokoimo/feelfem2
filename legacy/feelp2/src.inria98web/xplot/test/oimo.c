#include <stdio.h>

main()
{
   int i;

   openplps("oimo.ps");
   space(-1,-1,101,101);

   for(i=0;i<100;i+=10) {
      move(0,i);  cont(100,i);
      move(i,0);  cont(i,100);
   }

   closepl();
}

