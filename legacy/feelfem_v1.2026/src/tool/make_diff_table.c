#include <stdio.h>

#define MAX 253
main()
{
  int i;
  char buf[BUFSIZ];

  for(i=0;i<MAX;i++) {
    printf("case %d:\n",i+1);

    printf("  e = e.diff(_m%d);\n",i+1);
    printf("  break;\n");
    printf("\n");
  }
}

