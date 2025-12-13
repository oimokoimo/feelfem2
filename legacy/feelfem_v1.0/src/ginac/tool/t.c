#include <stdio.h>

void main(argc,argv)
     int argc;
     char *argv[];
{
  int i;
  int n;

  if(argc != 2) {
    fprintf(stderr,"Usage : %s number\n",argv[0]);
    exit(1);
  }


  n = atoi(argv[1]);
  if(n < 1) {
    fprintf(stderr,"%s : argument must be positive number\n",argv[0]);
    exit(1);
  }

  for(i=1;i<n+1;i++) {
    if(i<10) {
      printf("  symbol a0%d(\"a0%d\");\n", i,i);
    }
    else {
      printf("  symbol a%d(\"a%d\");\n", i,i);      
    }
  }

  printf("\n");
  printf("\n");
  printf("\n");

  for(i=1;i<n+1;i++) {
    if(i != 1 ) printf(",");
    if(i<10) {
      printf("a0%d", i);
    }
    else {
      printf("a%d", i);      
    }
  }

}

    
