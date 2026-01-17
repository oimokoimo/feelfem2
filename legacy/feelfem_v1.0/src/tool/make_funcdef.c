#include <stdio.h>

static char *diffsymbol[] = {
  "_dx","_dy","_dz"
};


static void strarg_ginac_dim_const( ndim )
     int ndim;
{
  switch(ndim) {
  case 1:
    printf("(const ex &x)");
    break;
  case 2:
    printf("(const ex &x,const ex &y)");
    break;
  case 3:
    printf("(const ex &x,const ex &y,const ex &z)");
    break;
  default:
    fprintf(stderr,"Ooops!!!\n");
    exit(1);
  }
  return;
}

static void strarg_ginac_dim_const_deriv( ndim )
     int ndim;
{
  switch(ndim) {
  case 1:
    printf("(const ex &x, unsigned deriv_param)");
    break;
  case 2:
    printf("(const ex &x,const ex &y, unsigned deriv_param)");
    break;
  case 3:
    printf("(const ex &x,const ex &y,const ex &z, unsigned deriv_param)");
    break;
  default:
    fprintf(stderr,"Ooops!!!\n");
    exit(1);
  }
  return;
}

static void strarg_ginac_dim_normal( ndim )
     int ndim;
{
  switch(ndim) {
  case 1:
    printf("(x)");
    break;
  case 2:
    printf("(x,y)");
    break;
  case 3:
    printf("(x,y,z)");
    break;
  default:
    fprintf(stderr,"Ooops!!!\n");
    exit(1);
  }
  return;
}


void make_derivopdef()
{
  printf("// definition of dx\n");
  printf("DECLARE_FUNCTION_1P(dx)\n");
  printf("\n");
  printf("symbol dx_dx("dx_dx");\n");
  printf("\n");
  printf("static ex dx_eval(const ex &t)\n");
  printf("{\n");
  printf("  ex f = t;\n");
  printf("  return( f.diff(x) );\n");
  printf("}\n");
  printf("\n");
  printf("static ex dx_evalf(const ex &t)\n");
  printf("{\n");
  printf("  return(dx(t));\n");
  printf("}\n");
  printf("\n");
  printf("static ex dx_deriv(const ex &x, unsigned deriv_param)\n");
  printf("{\n");
  printf("  if(deriv_param == 0)\n");
  printf("   return(dx_dx);\n");
  printf("  cerr <<"Illegal deriv_param\n";\n");
  printf("}\n");
  printf("REGISTER_FUNCTION(dx,\n");
  printf("                  eval_func(dx_eval).\n");
  printf("                  evalf_func(dx_evalf).\n");
  printf("                  derivative_func(dx_deriv))\n");
  printf("\n");
  printf("///////////\n");
  printf("// definition of dy\n");
  printf("DECLARE_FUNCTION_1P(dy)\n");
  printf("\n");
  printf("symbol dy_dx("dy_dx");\n");
  printf("\n");
  printf("static ex dy_eval(const ex &t)\n");
  printf("{\n");
  printf("  ex f = t;\n");
  printf("  return( f.diff(y) );\n");
  printf("}\n");
  printf("\n");
  printf("static ex dy_evalf(const ex &t)\n");
  printf("{\n");
  printf("  return(dy(t));\n");
  printf("}\n");
  printf("\n");
  printf("static ex dy_deriv(const ex &x, unsigned deriv_param)\n");
  printf("{\n");
  printf("  if(deriv_param == 0)\n");
  printf("   return(dy_dx);\n");
  printf("  cerr <<"Illegal deriv_param\n";\n");
  printf("}\n");
  printf("REGISTER_FUNCTION(dy,\n");
  printf("                  eval_func(dy_eval).\n");
  printf("                  evalf_func(dy_evalf).\n");
  printf("                  derivative_func(dy_deriv))\n");
  printf("\n");
  printf("///////////\n");
  printf("// definition of dz\n");
  printf("DECLARE_FUNCTION_1P(dz)\n");
  printf("\n");
  printf("symbol dz_dx("dz_dx");\n");
  printf("\n");
  printf("static ex dz_eval(const ex &t)\n");
  printf("{\n");
  printf("  ex f = t;\n");
  printf("  return( f.diff(z));\n");
  printf("}\n");
  printf("\n");
  printf("static ex dz_evalf(const ex &t)\n");
  printf("{\n");
  printf("  ex f = t;\n");
  printf("  return(f.diff(z));\n");
  printf("}\n");
  printf("\n");
  printf("static ex dz_deriv(const ex &x, unsigned deriv_param)\n");
  printf("{\n");
  printf("  if(deriv_param == 0)\n");
  printf("   return(dz_dx);\n");
  printf("  cerr <<"Illegal deriv_param\n";\n");
  printf("}\n");
  printf("REGISTER_FUNCTION(dz,\n");
  printf("                  eval_func(dz_eval).\n");
  printf("                  evalf_func(dz_evalf).\n");
  printf("                  derivative_func(dz_deriv))\n");
  
  return;
}
  
void make_funcdef( name , ndim)
char *name;
int   ndim;
{
  int i;

  printf("// definition of %s\n",name);
  switch(ndim) {
  case 1:
    printf("DECLARE_FUNCTION_1P(%s)\n",name);
    break;
  case 2:
    printf("DECLARE_FUNCTION_2P(%s)\n",name);
    break;
  case 3:
    printf("DECLARE_FUNCTION_3P(%s)\n",name);
    break;
  default:
    fprintf(stderr,"ndim=%d (error in make_funcdef)\n",ndim);
    exit(1);
  }
  printf("\n");
  
  for(i=0;i<ndim;i++) {
    printf("symbol %s%s(\"%s%s\");\n",name,diffsymbol[i],name,diffsymbol[i]);
  }
  printf("\n");

  printf("static ex %s_eval",name);
  strarg_ginac_dim_const( ndim );   /* ( const ex &x,.... ) */
  printf("\n");

  printf("{\n");
  printf("  return( %s",name);
  strarg_ginac_dim_normal( ndim );   /* ( const ex &x,.... ) */
  printf(".hold() );\n");

  printf("}\n");
  printf("\n");

  printf("static ex %s_evalf",name);
  strarg_ginac_dim_const(ndim);
  printf("\n");
  printf("{\n");
  printf("  return(%s",name);
  strarg_ginac_dim_normal(ndim);
  printf(");\n");
  printf("}\n");
  printf("\n");   

  printf("static ex %s_deriv",name);
  strarg_ginac_dim_const_deriv(ndim);
  printf("\n");
  
  printf("{\n");
  for(i=0;i<ndim;i++) {
    printf("  if(deriv_param == %d)\n",i);
    printf("   return(%s%s);\n",name,diffsymbol[i]);
  }
  printf("  cerr <<\"Illegal deriv_param\\n\";\n");
  printf("}\n");

  printf("REGISTER_FUNCTION(%s,\n",name);
  printf("                  eval_func(%s_eval).\n",name);
  printf("                  evalf_func(%s_evalf).\n",name);
  printf("                  derivative_func(%s_deriv))\n",name);
  printf("\n");
  printf("///////////\n");

  return;
}


#define DIM  3
#define MAX  100

int main()
{
  char buf[20];
  int i;

  make_derivopdef();

  for(i=1;i<=100;i++) {
    sprintf(buf,"_n%d%c",i,'\0');
    make_funcdef(buf,DIM);
  }

}
