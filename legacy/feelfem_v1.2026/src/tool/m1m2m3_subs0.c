#include <stdio.h>

#define MAX 253
main()
{
  int i;

  for(i=0;i<MAX;i++) {
    
    printf("  case %d:\n",i+1);
    printf("    e = e.subs(_m%d == 0);\n",i+1);
    printf("    break;\n");
    printf("\n");
  }
}

  
