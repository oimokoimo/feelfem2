#include <stdio.h>
nonlinear_info_(iter,dnorm)
int *iter;
double *dnorm;
{
      if(*iter<=1) printf("Nonlinear Iteration Information\n");
      printf("[%d]%5.0e ",*iter,*dnorm);
      return;
}
