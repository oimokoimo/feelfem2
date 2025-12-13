#include <ginac/ginac.h>
using namespace GiNaC;


// definition of dx
DECLARE_FUNCTION_1P(dx)

symbol dx_dx("dx_dx");

static ex dx_eval(const ex &t)
{
  ex f = t;
  return( f.diff(x) );
}

static ex dx_evalf(const ex &t)
{
  return(dx(t));
}

static ex dx_deriv(const ex &x, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(dx_dx);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(dx,
                  eval_func(dx_eval).
                  evalf_func(dx_evalf).
                  derivative_func(dx_deriv))

///////////
// definition of dy
DECLARE_FUNCTION_1P(dy)

symbol dy_dx("dy_dx");

static ex dy_eval(const ex &t)
{
  ex f = t;
  return( f.diff(y) );
}

static ex dy_evalf(const ex &t)
{
  return(dy(t));
}

static ex dy_deriv(const ex &x, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(dy_dx);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(dy,
                  eval_func(dy_eval).
                  evalf_func(dy_evalf).
                  derivative_func(dy_deriv))

///////////
// definition of dz
DECLARE_FUNCTION_1P(dz)

symbol dz_dx("dz_dx");

static ex dz_eval(const ex &t)
{
  ex f = t;
  return( f.diff(z));
}

static ex dz_evalf(const ex &t)
{
  ex f = t;
  return(f.diff(z));
}

static ex dz_deriv(const ex &x, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(dz_dx);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(dz,
                  eval_func(dz_eval).
                  evalf_func(dz_evalf).
                  derivative_func(dz_deriv))

///////////
// definition of _n1
DECLARE_FUNCTION_3P(_n1)

symbol _n1_dx("_n1_dx");
symbol _n1_dy("_n1_dy");
symbol _n1_dz("_n1_dz");

static ex _n1_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n1(x,y,z).hold() );
}

static ex _n1_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n1(x,y,z));
}

static ex _n1_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n1_dx);
  if(deriv_param == 1)
   return(_n1_dy);
  if(deriv_param == 2)
   return(_n1_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n1,
                  eval_func(_n1_eval).
                  evalf_func(_n1_evalf).
                  derivative_func(_n1_deriv))

///////////
// definition of _n2
DECLARE_FUNCTION_3P(_n2)

symbol _n2_dx("_n2_dx");
symbol _n2_dy("_n2_dy");
symbol _n2_dz("_n2_dz");

static ex _n2_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n2(x,y,z).hold() );
}

static ex _n2_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n2(x,y,z));
}

static ex _n2_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n2_dx);
  if(deriv_param == 1)
   return(_n2_dy);
  if(deriv_param == 2)
   return(_n2_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n2,
                  eval_func(_n2_eval).
                  evalf_func(_n2_evalf).
                  derivative_func(_n2_deriv))

///////////
// definition of _n3
DECLARE_FUNCTION_3P(_n3)

symbol _n3_dx("_n3_dx");
symbol _n3_dy("_n3_dy");
symbol _n3_dz("_n3_dz");

static ex _n3_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n3(x,y,z).hold() );
}

static ex _n3_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n3(x,y,z));
}

static ex _n3_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n3_dx);
  if(deriv_param == 1)
   return(_n3_dy);
  if(deriv_param == 2)
   return(_n3_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n3,
                  eval_func(_n3_eval).
                  evalf_func(_n3_evalf).
                  derivative_func(_n3_deriv))

///////////
// definition of _n4
DECLARE_FUNCTION_3P(_n4)

symbol _n4_dx("_n4_dx");
symbol _n4_dy("_n4_dy");
symbol _n4_dz("_n4_dz");

static ex _n4_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n4(x,y,z).hold() );
}

static ex _n4_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n4(x,y,z));
}

static ex _n4_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n4_dx);
  if(deriv_param == 1)
   return(_n4_dy);
  if(deriv_param == 2)
   return(_n4_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n4,
                  eval_func(_n4_eval).
                  evalf_func(_n4_evalf).
                  derivative_func(_n4_deriv))

///////////
// definition of _n5
DECLARE_FUNCTION_3P(_n5)

symbol _n5_dx("_n5_dx");
symbol _n5_dy("_n5_dy");
symbol _n5_dz("_n5_dz");

static ex _n5_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n5(x,y,z).hold() );
}

static ex _n5_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n5(x,y,z));
}

static ex _n5_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n5_dx);
  if(deriv_param == 1)
   return(_n5_dy);
  if(deriv_param == 2)
   return(_n5_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n5,
                  eval_func(_n5_eval).
                  evalf_func(_n5_evalf).
                  derivative_func(_n5_deriv))

///////////
// definition of _n6
DECLARE_FUNCTION_3P(_n6)

symbol _n6_dx("_n6_dx");
symbol _n6_dy("_n6_dy");
symbol _n6_dz("_n6_dz");

static ex _n6_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n6(x,y,z).hold() );
}

static ex _n6_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n6(x,y,z));
}

static ex _n6_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n6_dx);
  if(deriv_param == 1)
   return(_n6_dy);
  if(deriv_param == 2)
   return(_n6_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n6,
                  eval_func(_n6_eval).
                  evalf_func(_n6_evalf).
                  derivative_func(_n6_deriv))

///////////
// definition of _n7
DECLARE_FUNCTION_3P(_n7)

symbol _n7_dx("_n7_dx");
symbol _n7_dy("_n7_dy");
symbol _n7_dz("_n7_dz");

static ex _n7_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n7(x,y,z).hold() );
}

static ex _n7_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n7(x,y,z));
}

static ex _n7_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n7_dx);
  if(deriv_param == 1)
   return(_n7_dy);
  if(deriv_param == 2)
   return(_n7_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n7,
                  eval_func(_n7_eval).
                  evalf_func(_n7_evalf).
                  derivative_func(_n7_deriv))

///////////
// definition of _n8
DECLARE_FUNCTION_3P(_n8)

symbol _n8_dx("_n8_dx");
symbol _n8_dy("_n8_dy");
symbol _n8_dz("_n8_dz");

static ex _n8_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n8(x,y,z).hold() );
}

static ex _n8_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n8(x,y,z));
}

static ex _n8_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n8_dx);
  if(deriv_param == 1)
   return(_n8_dy);
  if(deriv_param == 2)
   return(_n8_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n8,
                  eval_func(_n8_eval).
                  evalf_func(_n8_evalf).
                  derivative_func(_n8_deriv))

///////////
// definition of _n9
DECLARE_FUNCTION_3P(_n9)

symbol _n9_dx("_n9_dx");
symbol _n9_dy("_n9_dy");
symbol _n9_dz("_n9_dz");

static ex _n9_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n9(x,y,z).hold() );
}

static ex _n9_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n9(x,y,z));
}

static ex _n9_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n9_dx);
  if(deriv_param == 1)
   return(_n9_dy);
  if(deriv_param == 2)
   return(_n9_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n9,
                  eval_func(_n9_eval).
                  evalf_func(_n9_evalf).
                  derivative_func(_n9_deriv))

///////////
// definition of _n10
DECLARE_FUNCTION_3P(_n10)

symbol _n10_dx("_n10_dx");
symbol _n10_dy("_n10_dy");
symbol _n10_dz("_n10_dz");

static ex _n10_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n10(x,y,z).hold() );
}

static ex _n10_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n10(x,y,z));
}

static ex _n10_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n10_dx);
  if(deriv_param == 1)
   return(_n10_dy);
  if(deriv_param == 2)
   return(_n10_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n10,
                  eval_func(_n10_eval).
                  evalf_func(_n10_evalf).
                  derivative_func(_n10_deriv))

///////////
// definition of _n11
DECLARE_FUNCTION_3P(_n11)

symbol _n11_dx("_n11_dx");
symbol _n11_dy("_n11_dy");
symbol _n11_dz("_n11_dz");

static ex _n11_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n11(x,y,z).hold() );
}

static ex _n11_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n11(x,y,z));
}

static ex _n11_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n11_dx);
  if(deriv_param == 1)
   return(_n11_dy);
  if(deriv_param == 2)
   return(_n11_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n11,
                  eval_func(_n11_eval).
                  evalf_func(_n11_evalf).
                  derivative_func(_n11_deriv))

///////////
// definition of _n12
DECLARE_FUNCTION_3P(_n12)

symbol _n12_dx("_n12_dx");
symbol _n12_dy("_n12_dy");
symbol _n12_dz("_n12_dz");

static ex _n12_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n12(x,y,z).hold() );
}

static ex _n12_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n12(x,y,z));
}

static ex _n12_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n12_dx);
  if(deriv_param == 1)
   return(_n12_dy);
  if(deriv_param == 2)
   return(_n12_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n12,
                  eval_func(_n12_eval).
                  evalf_func(_n12_evalf).
                  derivative_func(_n12_deriv))

///////////
// definition of _n13
DECLARE_FUNCTION_3P(_n13)

symbol _n13_dx("_n13_dx");
symbol _n13_dy("_n13_dy");
symbol _n13_dz("_n13_dz");

static ex _n13_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n13(x,y,z).hold() );
}

static ex _n13_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n13(x,y,z));
}

static ex _n13_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n13_dx);
  if(deriv_param == 1)
   return(_n13_dy);
  if(deriv_param == 2)
   return(_n13_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n13,
                  eval_func(_n13_eval).
                  evalf_func(_n13_evalf).
                  derivative_func(_n13_deriv))

///////////
// definition of _n14
DECLARE_FUNCTION_3P(_n14)

symbol _n14_dx("_n14_dx");
symbol _n14_dy("_n14_dy");
symbol _n14_dz("_n14_dz");

static ex _n14_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n14(x,y,z).hold() );
}

static ex _n14_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n14(x,y,z));
}

static ex _n14_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n14_dx);
  if(deriv_param == 1)
   return(_n14_dy);
  if(deriv_param == 2)
   return(_n14_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n14,
                  eval_func(_n14_eval).
                  evalf_func(_n14_evalf).
                  derivative_func(_n14_deriv))

///////////
// definition of _n15
DECLARE_FUNCTION_3P(_n15)

symbol _n15_dx("_n15_dx");
symbol _n15_dy("_n15_dy");
symbol _n15_dz("_n15_dz");

static ex _n15_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n15(x,y,z).hold() );
}

static ex _n15_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n15(x,y,z));
}

static ex _n15_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n15_dx);
  if(deriv_param == 1)
   return(_n15_dy);
  if(deriv_param == 2)
   return(_n15_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n15,
                  eval_func(_n15_eval).
                  evalf_func(_n15_evalf).
                  derivative_func(_n15_deriv))

///////////
// definition of _n16
DECLARE_FUNCTION_3P(_n16)

symbol _n16_dx("_n16_dx");
symbol _n16_dy("_n16_dy");
symbol _n16_dz("_n16_dz");

static ex _n16_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n16(x,y,z).hold() );
}

static ex _n16_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n16(x,y,z));
}

static ex _n16_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n16_dx);
  if(deriv_param == 1)
   return(_n16_dy);
  if(deriv_param == 2)
   return(_n16_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n16,
                  eval_func(_n16_eval).
                  evalf_func(_n16_evalf).
                  derivative_func(_n16_deriv))

///////////
// definition of _n17
DECLARE_FUNCTION_3P(_n17)

symbol _n17_dx("_n17_dx");
symbol _n17_dy("_n17_dy");
symbol _n17_dz("_n17_dz");

static ex _n17_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n17(x,y,z).hold() );
}

static ex _n17_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n17(x,y,z));
}

static ex _n17_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n17_dx);
  if(deriv_param == 1)
   return(_n17_dy);
  if(deriv_param == 2)
   return(_n17_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n17,
                  eval_func(_n17_eval).
                  evalf_func(_n17_evalf).
                  derivative_func(_n17_deriv))

///////////
// definition of _n18
DECLARE_FUNCTION_3P(_n18)

symbol _n18_dx("_n18_dx");
symbol _n18_dy("_n18_dy");
symbol _n18_dz("_n18_dz");

static ex _n18_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n18(x,y,z).hold() );
}

static ex _n18_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n18(x,y,z));
}

static ex _n18_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n18_dx);
  if(deriv_param == 1)
   return(_n18_dy);
  if(deriv_param == 2)
   return(_n18_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n18,
                  eval_func(_n18_eval).
                  evalf_func(_n18_evalf).
                  derivative_func(_n18_deriv))

///////////
// definition of _n19
DECLARE_FUNCTION_3P(_n19)

symbol _n19_dx("_n19_dx");
symbol _n19_dy("_n19_dy");
symbol _n19_dz("_n19_dz");

static ex _n19_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n19(x,y,z).hold() );
}

static ex _n19_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n19(x,y,z));
}

static ex _n19_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n19_dx);
  if(deriv_param == 1)
   return(_n19_dy);
  if(deriv_param == 2)
   return(_n19_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n19,
                  eval_func(_n19_eval).
                  evalf_func(_n19_evalf).
                  derivative_func(_n19_deriv))

///////////
// definition of _n20
DECLARE_FUNCTION_3P(_n20)

symbol _n20_dx("_n20_dx");
symbol _n20_dy("_n20_dy");
symbol _n20_dz("_n20_dz");

static ex _n20_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n20(x,y,z).hold() );
}

static ex _n20_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n20(x,y,z));
}

static ex _n20_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n20_dx);
  if(deriv_param == 1)
   return(_n20_dy);
  if(deriv_param == 2)
   return(_n20_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n20,
                  eval_func(_n20_eval).
                  evalf_func(_n20_evalf).
                  derivative_func(_n20_deriv))

///////////
// definition of _n21
DECLARE_FUNCTION_3P(_n21)

symbol _n21_dx("_n21_dx");
symbol _n21_dy("_n21_dy");
symbol _n21_dz("_n21_dz");

static ex _n21_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n21(x,y,z).hold() );
}

static ex _n21_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n21(x,y,z));
}

static ex _n21_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n21_dx);
  if(deriv_param == 1)
   return(_n21_dy);
  if(deriv_param == 2)
   return(_n21_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n21,
                  eval_func(_n21_eval).
                  evalf_func(_n21_evalf).
                  derivative_func(_n21_deriv))

///////////
// definition of _n22
DECLARE_FUNCTION_3P(_n22)

symbol _n22_dx("_n22_dx");
symbol _n22_dy("_n22_dy");
symbol _n22_dz("_n22_dz");

static ex _n22_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n22(x,y,z).hold() );
}

static ex _n22_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n22(x,y,z));
}

static ex _n22_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n22_dx);
  if(deriv_param == 1)
   return(_n22_dy);
  if(deriv_param == 2)
   return(_n22_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n22,
                  eval_func(_n22_eval).
                  evalf_func(_n22_evalf).
                  derivative_func(_n22_deriv))

///////////
// definition of _n23
DECLARE_FUNCTION_3P(_n23)

symbol _n23_dx("_n23_dx");
symbol _n23_dy("_n23_dy");
symbol _n23_dz("_n23_dz");

static ex _n23_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n23(x,y,z).hold() );
}

static ex _n23_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n23(x,y,z));
}

static ex _n23_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n23_dx);
  if(deriv_param == 1)
   return(_n23_dy);
  if(deriv_param == 2)
   return(_n23_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n23,
                  eval_func(_n23_eval).
                  evalf_func(_n23_evalf).
                  derivative_func(_n23_deriv))

///////////
// definition of _n24
DECLARE_FUNCTION_3P(_n24)

symbol _n24_dx("_n24_dx");
symbol _n24_dy("_n24_dy");
symbol _n24_dz("_n24_dz");

static ex _n24_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n24(x,y,z).hold() );
}

static ex _n24_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n24(x,y,z));
}

static ex _n24_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n24_dx);
  if(deriv_param == 1)
   return(_n24_dy);
  if(deriv_param == 2)
   return(_n24_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n24,
                  eval_func(_n24_eval).
                  evalf_func(_n24_evalf).
                  derivative_func(_n24_deriv))

///////////
// definition of _n25
DECLARE_FUNCTION_3P(_n25)

symbol _n25_dx("_n25_dx");
symbol _n25_dy("_n25_dy");
symbol _n25_dz("_n25_dz");

static ex _n25_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n25(x,y,z).hold() );
}

static ex _n25_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n25(x,y,z));
}

static ex _n25_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n25_dx);
  if(deriv_param == 1)
   return(_n25_dy);
  if(deriv_param == 2)
   return(_n25_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n25,
                  eval_func(_n25_eval).
                  evalf_func(_n25_evalf).
                  derivative_func(_n25_deriv))

///////////
// definition of _n26
DECLARE_FUNCTION_3P(_n26)

symbol _n26_dx("_n26_dx");
symbol _n26_dy("_n26_dy");
symbol _n26_dz("_n26_dz");

static ex _n26_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n26(x,y,z).hold() );
}

static ex _n26_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n26(x,y,z));
}

static ex _n26_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n26_dx);
  if(deriv_param == 1)
   return(_n26_dy);
  if(deriv_param == 2)
   return(_n26_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n26,
                  eval_func(_n26_eval).
                  evalf_func(_n26_evalf).
                  derivative_func(_n26_deriv))

///////////
// definition of _n27
DECLARE_FUNCTION_3P(_n27)

symbol _n27_dx("_n27_dx");
symbol _n27_dy("_n27_dy");
symbol _n27_dz("_n27_dz");

static ex _n27_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n27(x,y,z).hold() );
}

static ex _n27_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n27(x,y,z));
}

static ex _n27_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n27_dx);
  if(deriv_param == 1)
   return(_n27_dy);
  if(deriv_param == 2)
   return(_n27_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n27,
                  eval_func(_n27_eval).
                  evalf_func(_n27_evalf).
                  derivative_func(_n27_deriv))

///////////
// definition of _n28
DECLARE_FUNCTION_3P(_n28)

symbol _n28_dx("_n28_dx");
symbol _n28_dy("_n28_dy");
symbol _n28_dz("_n28_dz");

static ex _n28_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n28(x,y,z).hold() );
}

static ex _n28_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n28(x,y,z));
}

static ex _n28_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n28_dx);
  if(deriv_param == 1)
   return(_n28_dy);
  if(deriv_param == 2)
   return(_n28_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n28,
                  eval_func(_n28_eval).
                  evalf_func(_n28_evalf).
                  derivative_func(_n28_deriv))

///////////
// definition of _n29
DECLARE_FUNCTION_3P(_n29)

symbol _n29_dx("_n29_dx");
symbol _n29_dy("_n29_dy");
symbol _n29_dz("_n29_dz");

static ex _n29_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n29(x,y,z).hold() );
}

static ex _n29_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n29(x,y,z));
}

static ex _n29_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n29_dx);
  if(deriv_param == 1)
   return(_n29_dy);
  if(deriv_param == 2)
   return(_n29_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n29,
                  eval_func(_n29_eval).
                  evalf_func(_n29_evalf).
                  derivative_func(_n29_deriv))

///////////
// definition of _n30
DECLARE_FUNCTION_3P(_n30)

symbol _n30_dx("_n30_dx");
symbol _n30_dy("_n30_dy");
symbol _n30_dz("_n30_dz");

static ex _n30_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n30(x,y,z).hold() );
}

static ex _n30_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n30(x,y,z));
}

static ex _n30_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n30_dx);
  if(deriv_param == 1)
   return(_n30_dy);
  if(deriv_param == 2)
   return(_n30_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n30,
                  eval_func(_n30_eval).
                  evalf_func(_n30_evalf).
                  derivative_func(_n30_deriv))

///////////
// definition of _n31
DECLARE_FUNCTION_3P(_n31)

symbol _n31_dx("_n31_dx");
symbol _n31_dy("_n31_dy");
symbol _n31_dz("_n31_dz");

static ex _n31_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n31(x,y,z).hold() );
}

static ex _n31_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n31(x,y,z));
}

static ex _n31_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n31_dx);
  if(deriv_param == 1)
   return(_n31_dy);
  if(deriv_param == 2)
   return(_n31_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n31,
                  eval_func(_n31_eval).
                  evalf_func(_n31_evalf).
                  derivative_func(_n31_deriv))

///////////
// definition of _n32
DECLARE_FUNCTION_3P(_n32)

symbol _n32_dx("_n32_dx");
symbol _n32_dy("_n32_dy");
symbol _n32_dz("_n32_dz");

static ex _n32_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n32(x,y,z).hold() );
}

static ex _n32_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n32(x,y,z));
}

static ex _n32_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n32_dx);
  if(deriv_param == 1)
   return(_n32_dy);
  if(deriv_param == 2)
   return(_n32_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n32,
                  eval_func(_n32_eval).
                  evalf_func(_n32_evalf).
                  derivative_func(_n32_deriv))

///////////
// definition of _n33
DECLARE_FUNCTION_3P(_n33)

symbol _n33_dx("_n33_dx");
symbol _n33_dy("_n33_dy");
symbol _n33_dz("_n33_dz");

static ex _n33_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n33(x,y,z).hold() );
}

static ex _n33_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n33(x,y,z));
}

static ex _n33_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n33_dx);
  if(deriv_param == 1)
   return(_n33_dy);
  if(deriv_param == 2)
   return(_n33_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n33,
                  eval_func(_n33_eval).
                  evalf_func(_n33_evalf).
                  derivative_func(_n33_deriv))

///////////
// definition of _n34
DECLARE_FUNCTION_3P(_n34)

symbol _n34_dx("_n34_dx");
symbol _n34_dy("_n34_dy");
symbol _n34_dz("_n34_dz");

static ex _n34_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n34(x,y,z).hold() );
}

static ex _n34_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n34(x,y,z));
}

static ex _n34_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n34_dx);
  if(deriv_param == 1)
   return(_n34_dy);
  if(deriv_param == 2)
   return(_n34_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n34,
                  eval_func(_n34_eval).
                  evalf_func(_n34_evalf).
                  derivative_func(_n34_deriv))

///////////
// definition of _n35
DECLARE_FUNCTION_3P(_n35)

symbol _n35_dx("_n35_dx");
symbol _n35_dy("_n35_dy");
symbol _n35_dz("_n35_dz");

static ex _n35_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n35(x,y,z).hold() );
}

static ex _n35_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n35(x,y,z));
}

static ex _n35_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n35_dx);
  if(deriv_param == 1)
   return(_n35_dy);
  if(deriv_param == 2)
   return(_n35_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n35,
                  eval_func(_n35_eval).
                  evalf_func(_n35_evalf).
                  derivative_func(_n35_deriv))

///////////
// definition of _n36
DECLARE_FUNCTION_3P(_n36)

symbol _n36_dx("_n36_dx");
symbol _n36_dy("_n36_dy");
symbol _n36_dz("_n36_dz");

static ex _n36_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n36(x,y,z).hold() );
}

static ex _n36_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n36(x,y,z));
}

static ex _n36_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n36_dx);
  if(deriv_param == 1)
   return(_n36_dy);
  if(deriv_param == 2)
   return(_n36_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n36,
                  eval_func(_n36_eval).
                  evalf_func(_n36_evalf).
                  derivative_func(_n36_deriv))

///////////
// definition of _n37
DECLARE_FUNCTION_3P(_n37)

symbol _n37_dx("_n37_dx");
symbol _n37_dy("_n37_dy");
symbol _n37_dz("_n37_dz");

static ex _n37_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n37(x,y,z).hold() );
}

static ex _n37_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n37(x,y,z));
}

static ex _n37_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n37_dx);
  if(deriv_param == 1)
   return(_n37_dy);
  if(deriv_param == 2)
   return(_n37_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n37,
                  eval_func(_n37_eval).
                  evalf_func(_n37_evalf).
                  derivative_func(_n37_deriv))

///////////
// definition of _n38
DECLARE_FUNCTION_3P(_n38)

symbol _n38_dx("_n38_dx");
symbol _n38_dy("_n38_dy");
symbol _n38_dz("_n38_dz");

static ex _n38_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n38(x,y,z).hold() );
}

static ex _n38_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n38(x,y,z));
}

static ex _n38_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n38_dx);
  if(deriv_param == 1)
   return(_n38_dy);
  if(deriv_param == 2)
   return(_n38_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n38,
                  eval_func(_n38_eval).
                  evalf_func(_n38_evalf).
                  derivative_func(_n38_deriv))

///////////
// definition of _n39
DECLARE_FUNCTION_3P(_n39)

symbol _n39_dx("_n39_dx");
symbol _n39_dy("_n39_dy");
symbol _n39_dz("_n39_dz");

static ex _n39_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n39(x,y,z).hold() );
}

static ex _n39_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n39(x,y,z));
}

static ex _n39_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n39_dx);
  if(deriv_param == 1)
   return(_n39_dy);
  if(deriv_param == 2)
   return(_n39_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n39,
                  eval_func(_n39_eval).
                  evalf_func(_n39_evalf).
                  derivative_func(_n39_deriv))

///////////
// definition of _n40
DECLARE_FUNCTION_3P(_n40)

symbol _n40_dx("_n40_dx");
symbol _n40_dy("_n40_dy");
symbol _n40_dz("_n40_dz");

static ex _n40_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n40(x,y,z).hold() );
}

static ex _n40_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n40(x,y,z));
}

static ex _n40_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n40_dx);
  if(deriv_param == 1)
   return(_n40_dy);
  if(deriv_param == 2)
   return(_n40_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n40,
                  eval_func(_n40_eval).
                  evalf_func(_n40_evalf).
                  derivative_func(_n40_deriv))

///////////
// definition of _n41
DECLARE_FUNCTION_3P(_n41)

symbol _n41_dx("_n41_dx");
symbol _n41_dy("_n41_dy");
symbol _n41_dz("_n41_dz");

static ex _n41_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n41(x,y,z).hold() );
}

static ex _n41_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n41(x,y,z));
}

static ex _n41_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n41_dx);
  if(deriv_param == 1)
   return(_n41_dy);
  if(deriv_param == 2)
   return(_n41_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n41,
                  eval_func(_n41_eval).
                  evalf_func(_n41_evalf).
                  derivative_func(_n41_deriv))

///////////
// definition of _n42
DECLARE_FUNCTION_3P(_n42)

symbol _n42_dx("_n42_dx");
symbol _n42_dy("_n42_dy");
symbol _n42_dz("_n42_dz");

static ex _n42_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n42(x,y,z).hold() );
}

static ex _n42_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n42(x,y,z));
}

static ex _n42_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n42_dx);
  if(deriv_param == 1)
   return(_n42_dy);
  if(deriv_param == 2)
   return(_n42_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n42,
                  eval_func(_n42_eval).
                  evalf_func(_n42_evalf).
                  derivative_func(_n42_deriv))

///////////
// definition of _n43
DECLARE_FUNCTION_3P(_n43)

symbol _n43_dx("_n43_dx");
symbol _n43_dy("_n43_dy");
symbol _n43_dz("_n43_dz");

static ex _n43_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n43(x,y,z).hold() );
}

static ex _n43_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n43(x,y,z));
}

static ex _n43_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n43_dx);
  if(deriv_param == 1)
   return(_n43_dy);
  if(deriv_param == 2)
   return(_n43_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n43,
                  eval_func(_n43_eval).
                  evalf_func(_n43_evalf).
                  derivative_func(_n43_deriv))

///////////
// definition of _n44
DECLARE_FUNCTION_3P(_n44)

symbol _n44_dx("_n44_dx");
symbol _n44_dy("_n44_dy");
symbol _n44_dz("_n44_dz");

static ex _n44_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n44(x,y,z).hold() );
}

static ex _n44_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n44(x,y,z));
}

static ex _n44_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n44_dx);
  if(deriv_param == 1)
   return(_n44_dy);
  if(deriv_param == 2)
   return(_n44_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n44,
                  eval_func(_n44_eval).
                  evalf_func(_n44_evalf).
                  derivative_func(_n44_deriv))

///////////
// definition of _n45
DECLARE_FUNCTION_3P(_n45)

symbol _n45_dx("_n45_dx");
symbol _n45_dy("_n45_dy");
symbol _n45_dz("_n45_dz");

static ex _n45_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n45(x,y,z).hold() );
}

static ex _n45_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n45(x,y,z));
}

static ex _n45_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n45_dx);
  if(deriv_param == 1)
   return(_n45_dy);
  if(deriv_param == 2)
   return(_n45_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n45,
                  eval_func(_n45_eval).
                  evalf_func(_n45_evalf).
                  derivative_func(_n45_deriv))

///////////
// definition of _n46
DECLARE_FUNCTION_3P(_n46)

symbol _n46_dx("_n46_dx");
symbol _n46_dy("_n46_dy");
symbol _n46_dz("_n46_dz");

static ex _n46_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n46(x,y,z).hold() );
}

static ex _n46_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n46(x,y,z));
}

static ex _n46_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n46_dx);
  if(deriv_param == 1)
   return(_n46_dy);
  if(deriv_param == 2)
   return(_n46_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n46,
                  eval_func(_n46_eval).
                  evalf_func(_n46_evalf).
                  derivative_func(_n46_deriv))

///////////
// definition of _n47
DECLARE_FUNCTION_3P(_n47)

symbol _n47_dx("_n47_dx");
symbol _n47_dy("_n47_dy");
symbol _n47_dz("_n47_dz");

static ex _n47_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n47(x,y,z).hold() );
}

static ex _n47_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n47(x,y,z));
}

static ex _n47_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n47_dx);
  if(deriv_param == 1)
   return(_n47_dy);
  if(deriv_param == 2)
   return(_n47_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n47,
                  eval_func(_n47_eval).
                  evalf_func(_n47_evalf).
                  derivative_func(_n47_deriv))

///////////
// definition of _n48
DECLARE_FUNCTION_3P(_n48)

symbol _n48_dx("_n48_dx");
symbol _n48_dy("_n48_dy");
symbol _n48_dz("_n48_dz");

static ex _n48_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n48(x,y,z).hold() );
}

static ex _n48_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n48(x,y,z));
}

static ex _n48_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n48_dx);
  if(deriv_param == 1)
   return(_n48_dy);
  if(deriv_param == 2)
   return(_n48_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n48,
                  eval_func(_n48_eval).
                  evalf_func(_n48_evalf).
                  derivative_func(_n48_deriv))

///////////
// definition of _n49
DECLARE_FUNCTION_3P(_n49)

symbol _n49_dx("_n49_dx");
symbol _n49_dy("_n49_dy");
symbol _n49_dz("_n49_dz");

static ex _n49_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n49(x,y,z).hold() );
}

static ex _n49_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n49(x,y,z));
}

static ex _n49_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n49_dx);
  if(deriv_param == 1)
   return(_n49_dy);
  if(deriv_param == 2)
   return(_n49_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n49,
                  eval_func(_n49_eval).
                  evalf_func(_n49_evalf).
                  derivative_func(_n49_deriv))

///////////
// definition of _n50
DECLARE_FUNCTION_3P(_n50)

symbol _n50_dx("_n50_dx");
symbol _n50_dy("_n50_dy");
symbol _n50_dz("_n50_dz");

static ex _n50_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n50(x,y,z).hold() );
}

static ex _n50_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n50(x,y,z));
}

static ex _n50_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n50_dx);
  if(deriv_param == 1)
   return(_n50_dy);
  if(deriv_param == 2)
   return(_n50_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n50,
                  eval_func(_n50_eval).
                  evalf_func(_n50_evalf).
                  derivative_func(_n50_deriv))

///////////
// definition of _n51
DECLARE_FUNCTION_3P(_n51)

symbol _n51_dx("_n51_dx");
symbol _n51_dy("_n51_dy");
symbol _n51_dz("_n51_dz");

static ex _n51_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n51(x,y,z).hold() );
}

static ex _n51_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n51(x,y,z));
}

static ex _n51_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n51_dx);
  if(deriv_param == 1)
   return(_n51_dy);
  if(deriv_param == 2)
   return(_n51_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n51,
                  eval_func(_n51_eval).
                  evalf_func(_n51_evalf).
                  derivative_func(_n51_deriv))

///////////
// definition of _n52
DECLARE_FUNCTION_3P(_n52)

symbol _n52_dx("_n52_dx");
symbol _n52_dy("_n52_dy");
symbol _n52_dz("_n52_dz");

static ex _n52_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n52(x,y,z).hold() );
}

static ex _n52_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n52(x,y,z));
}

static ex _n52_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n52_dx);
  if(deriv_param == 1)
   return(_n52_dy);
  if(deriv_param == 2)
   return(_n52_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n52,
                  eval_func(_n52_eval).
                  evalf_func(_n52_evalf).
                  derivative_func(_n52_deriv))

///////////
// definition of _n53
DECLARE_FUNCTION_3P(_n53)

symbol _n53_dx("_n53_dx");
symbol _n53_dy("_n53_dy");
symbol _n53_dz("_n53_dz");

static ex _n53_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n53(x,y,z).hold() );
}

static ex _n53_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n53(x,y,z));
}

static ex _n53_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n53_dx);
  if(deriv_param == 1)
   return(_n53_dy);
  if(deriv_param == 2)
   return(_n53_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n53,
                  eval_func(_n53_eval).
                  evalf_func(_n53_evalf).
                  derivative_func(_n53_deriv))

///////////
// definition of _n54
DECLARE_FUNCTION_3P(_n54)

symbol _n54_dx("_n54_dx");
symbol _n54_dy("_n54_dy");
symbol _n54_dz("_n54_dz");

static ex _n54_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n54(x,y,z).hold() );
}

static ex _n54_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n54(x,y,z));
}

static ex _n54_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n54_dx);
  if(deriv_param == 1)
   return(_n54_dy);
  if(deriv_param == 2)
   return(_n54_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n54,
                  eval_func(_n54_eval).
                  evalf_func(_n54_evalf).
                  derivative_func(_n54_deriv))

///////////
// definition of _n55
DECLARE_FUNCTION_3P(_n55)

symbol _n55_dx("_n55_dx");
symbol _n55_dy("_n55_dy");
symbol _n55_dz("_n55_dz");

static ex _n55_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n55(x,y,z).hold() );
}

static ex _n55_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n55(x,y,z));
}

static ex _n55_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n55_dx);
  if(deriv_param == 1)
   return(_n55_dy);
  if(deriv_param == 2)
   return(_n55_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n55,
                  eval_func(_n55_eval).
                  evalf_func(_n55_evalf).
                  derivative_func(_n55_deriv))

///////////
// definition of _n56
DECLARE_FUNCTION_3P(_n56)

symbol _n56_dx("_n56_dx");
symbol _n56_dy("_n56_dy");
symbol _n56_dz("_n56_dz");

static ex _n56_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n56(x,y,z).hold() );
}

static ex _n56_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n56(x,y,z));
}

static ex _n56_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n56_dx);
  if(deriv_param == 1)
   return(_n56_dy);
  if(deriv_param == 2)
   return(_n56_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n56,
                  eval_func(_n56_eval).
                  evalf_func(_n56_evalf).
                  derivative_func(_n56_deriv))

///////////
// definition of _n57
DECLARE_FUNCTION_3P(_n57)

symbol _n57_dx("_n57_dx");
symbol _n57_dy("_n57_dy");
symbol _n57_dz("_n57_dz");

static ex _n57_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n57(x,y,z).hold() );
}

static ex _n57_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n57(x,y,z));
}

static ex _n57_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n57_dx);
  if(deriv_param == 1)
   return(_n57_dy);
  if(deriv_param == 2)
   return(_n57_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n57,
                  eval_func(_n57_eval).
                  evalf_func(_n57_evalf).
                  derivative_func(_n57_deriv))

///////////
// definition of _n58
DECLARE_FUNCTION_3P(_n58)

symbol _n58_dx("_n58_dx");
symbol _n58_dy("_n58_dy");
symbol _n58_dz("_n58_dz");

static ex _n58_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n58(x,y,z).hold() );
}

static ex _n58_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n58(x,y,z));
}

static ex _n58_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n58_dx);
  if(deriv_param == 1)
   return(_n58_dy);
  if(deriv_param == 2)
   return(_n58_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n58,
                  eval_func(_n58_eval).
                  evalf_func(_n58_evalf).
                  derivative_func(_n58_deriv))

///////////
// definition of _n59
DECLARE_FUNCTION_3P(_n59)

symbol _n59_dx("_n59_dx");
symbol _n59_dy("_n59_dy");
symbol _n59_dz("_n59_dz");

static ex _n59_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n59(x,y,z).hold() );
}

static ex _n59_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n59(x,y,z));
}

static ex _n59_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n59_dx);
  if(deriv_param == 1)
   return(_n59_dy);
  if(deriv_param == 2)
   return(_n59_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n59,
                  eval_func(_n59_eval).
                  evalf_func(_n59_evalf).
                  derivative_func(_n59_deriv))

///////////
// definition of _n60
DECLARE_FUNCTION_3P(_n60)

symbol _n60_dx("_n60_dx");
symbol _n60_dy("_n60_dy");
symbol _n60_dz("_n60_dz");

static ex _n60_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n60(x,y,z).hold() );
}

static ex _n60_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n60(x,y,z));
}

static ex _n60_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n60_dx);
  if(deriv_param == 1)
   return(_n60_dy);
  if(deriv_param == 2)
   return(_n60_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n60,
                  eval_func(_n60_eval).
                  evalf_func(_n60_evalf).
                  derivative_func(_n60_deriv))

///////////
// definition of _n61
DECLARE_FUNCTION_3P(_n61)

symbol _n61_dx("_n61_dx");
symbol _n61_dy("_n61_dy");
symbol _n61_dz("_n61_dz");

static ex _n61_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n61(x,y,z).hold() );
}

static ex _n61_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n61(x,y,z));
}

static ex _n61_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n61_dx);
  if(deriv_param == 1)
   return(_n61_dy);
  if(deriv_param == 2)
   return(_n61_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n61,
                  eval_func(_n61_eval).
                  evalf_func(_n61_evalf).
                  derivative_func(_n61_deriv))

///////////
// definition of _n62
DECLARE_FUNCTION_3P(_n62)

symbol _n62_dx("_n62_dx");
symbol _n62_dy("_n62_dy");
symbol _n62_dz("_n62_dz");

static ex _n62_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n62(x,y,z).hold() );
}

static ex _n62_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n62(x,y,z));
}

static ex _n62_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n62_dx);
  if(deriv_param == 1)
   return(_n62_dy);
  if(deriv_param == 2)
   return(_n62_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n62,
                  eval_func(_n62_eval).
                  evalf_func(_n62_evalf).
                  derivative_func(_n62_deriv))

///////////
// definition of _n63
DECLARE_FUNCTION_3P(_n63)

symbol _n63_dx("_n63_dx");
symbol _n63_dy("_n63_dy");
symbol _n63_dz("_n63_dz");

static ex _n63_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n63(x,y,z).hold() );
}

static ex _n63_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n63(x,y,z));
}

static ex _n63_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n63_dx);
  if(deriv_param == 1)
   return(_n63_dy);
  if(deriv_param == 2)
   return(_n63_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n63,
                  eval_func(_n63_eval).
                  evalf_func(_n63_evalf).
                  derivative_func(_n63_deriv))

///////////
// definition of _n64
DECLARE_FUNCTION_3P(_n64)

symbol _n64_dx("_n64_dx");
symbol _n64_dy("_n64_dy");
symbol _n64_dz("_n64_dz");

static ex _n64_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n64(x,y,z).hold() );
}

static ex _n64_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n64(x,y,z));
}

static ex _n64_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n64_dx);
  if(deriv_param == 1)
   return(_n64_dy);
  if(deriv_param == 2)
   return(_n64_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n64,
                  eval_func(_n64_eval).
                  evalf_func(_n64_evalf).
                  derivative_func(_n64_deriv))

///////////
// definition of _n65
DECLARE_FUNCTION_3P(_n65)

symbol _n65_dx("_n65_dx");
symbol _n65_dy("_n65_dy");
symbol _n65_dz("_n65_dz");

static ex _n65_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n65(x,y,z).hold() );
}

static ex _n65_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n65(x,y,z));
}

static ex _n65_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n65_dx);
  if(deriv_param == 1)
   return(_n65_dy);
  if(deriv_param == 2)
   return(_n65_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n65,
                  eval_func(_n65_eval).
                  evalf_func(_n65_evalf).
                  derivative_func(_n65_deriv))

///////////
// definition of _n66
DECLARE_FUNCTION_3P(_n66)

symbol _n66_dx("_n66_dx");
symbol _n66_dy("_n66_dy");
symbol _n66_dz("_n66_dz");

static ex _n66_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n66(x,y,z).hold() );
}

static ex _n66_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n66(x,y,z));
}

static ex _n66_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n66_dx);
  if(deriv_param == 1)
   return(_n66_dy);
  if(deriv_param == 2)
   return(_n66_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n66,
                  eval_func(_n66_eval).
                  evalf_func(_n66_evalf).
                  derivative_func(_n66_deriv))

///////////
// definition of _n67
DECLARE_FUNCTION_3P(_n67)

symbol _n67_dx("_n67_dx");
symbol _n67_dy("_n67_dy");
symbol _n67_dz("_n67_dz");

static ex _n67_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n67(x,y,z).hold() );
}

static ex _n67_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n67(x,y,z));
}

static ex _n67_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n67_dx);
  if(deriv_param == 1)
   return(_n67_dy);
  if(deriv_param == 2)
   return(_n67_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n67,
                  eval_func(_n67_eval).
                  evalf_func(_n67_evalf).
                  derivative_func(_n67_deriv))

///////////
// definition of _n68
DECLARE_FUNCTION_3P(_n68)

symbol _n68_dx("_n68_dx");
symbol _n68_dy("_n68_dy");
symbol _n68_dz("_n68_dz");

static ex _n68_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n68(x,y,z).hold() );
}

static ex _n68_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n68(x,y,z));
}

static ex _n68_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n68_dx);
  if(deriv_param == 1)
   return(_n68_dy);
  if(deriv_param == 2)
   return(_n68_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n68,
                  eval_func(_n68_eval).
                  evalf_func(_n68_evalf).
                  derivative_func(_n68_deriv))

///////////
// definition of _n69
DECLARE_FUNCTION_3P(_n69)

symbol _n69_dx("_n69_dx");
symbol _n69_dy("_n69_dy");
symbol _n69_dz("_n69_dz");

static ex _n69_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n69(x,y,z).hold() );
}

static ex _n69_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n69(x,y,z));
}

static ex _n69_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n69_dx);
  if(deriv_param == 1)
   return(_n69_dy);
  if(deriv_param == 2)
   return(_n69_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n69,
                  eval_func(_n69_eval).
                  evalf_func(_n69_evalf).
                  derivative_func(_n69_deriv))

///////////
// definition of _n70
DECLARE_FUNCTION_3P(_n70)

symbol _n70_dx("_n70_dx");
symbol _n70_dy("_n70_dy");
symbol _n70_dz("_n70_dz");

static ex _n70_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n70(x,y,z).hold() );
}

static ex _n70_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n70(x,y,z));
}

static ex _n70_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n70_dx);
  if(deriv_param == 1)
   return(_n70_dy);
  if(deriv_param == 2)
   return(_n70_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n70,
                  eval_func(_n70_eval).
                  evalf_func(_n70_evalf).
                  derivative_func(_n70_deriv))

///////////
// definition of _n71
DECLARE_FUNCTION_3P(_n71)

symbol _n71_dx("_n71_dx");
symbol _n71_dy("_n71_dy");
symbol _n71_dz("_n71_dz");

static ex _n71_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n71(x,y,z).hold() );
}

static ex _n71_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n71(x,y,z));
}

static ex _n71_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n71_dx);
  if(deriv_param == 1)
   return(_n71_dy);
  if(deriv_param == 2)
   return(_n71_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n71,
                  eval_func(_n71_eval).
                  evalf_func(_n71_evalf).
                  derivative_func(_n71_deriv))

///////////
// definition of _n72
DECLARE_FUNCTION_3P(_n72)

symbol _n72_dx("_n72_dx");
symbol _n72_dy("_n72_dy");
symbol _n72_dz("_n72_dz");

static ex _n72_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n72(x,y,z).hold() );
}

static ex _n72_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n72(x,y,z));
}

static ex _n72_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n72_dx);
  if(deriv_param == 1)
   return(_n72_dy);
  if(deriv_param == 2)
   return(_n72_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n72,
                  eval_func(_n72_eval).
                  evalf_func(_n72_evalf).
                  derivative_func(_n72_deriv))

///////////
// definition of _n73
DECLARE_FUNCTION_3P(_n73)

symbol _n73_dx("_n73_dx");
symbol _n73_dy("_n73_dy");
symbol _n73_dz("_n73_dz");

static ex _n73_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n73(x,y,z).hold() );
}

static ex _n73_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n73(x,y,z));
}

static ex _n73_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n73_dx);
  if(deriv_param == 1)
   return(_n73_dy);
  if(deriv_param == 2)
   return(_n73_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n73,
                  eval_func(_n73_eval).
                  evalf_func(_n73_evalf).
                  derivative_func(_n73_deriv))

///////////
// definition of _n74
DECLARE_FUNCTION_3P(_n74)

symbol _n74_dx("_n74_dx");
symbol _n74_dy("_n74_dy");
symbol _n74_dz("_n74_dz");

static ex _n74_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n74(x,y,z).hold() );
}

static ex _n74_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n74(x,y,z));
}

static ex _n74_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n74_dx);
  if(deriv_param == 1)
   return(_n74_dy);
  if(deriv_param == 2)
   return(_n74_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n74,
                  eval_func(_n74_eval).
                  evalf_func(_n74_evalf).
                  derivative_func(_n74_deriv))

///////////
// definition of _n75
DECLARE_FUNCTION_3P(_n75)

symbol _n75_dx("_n75_dx");
symbol _n75_dy("_n75_dy");
symbol _n75_dz("_n75_dz");

static ex _n75_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n75(x,y,z).hold() );
}

static ex _n75_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n75(x,y,z));
}

static ex _n75_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n75_dx);
  if(deriv_param == 1)
   return(_n75_dy);
  if(deriv_param == 2)
   return(_n75_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n75,
                  eval_func(_n75_eval).
                  evalf_func(_n75_evalf).
                  derivative_func(_n75_deriv))

///////////
// definition of _n76
DECLARE_FUNCTION_3P(_n76)

symbol _n76_dx("_n76_dx");
symbol _n76_dy("_n76_dy");
symbol _n76_dz("_n76_dz");

static ex _n76_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n76(x,y,z).hold() );
}

static ex _n76_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n76(x,y,z));
}

static ex _n76_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n76_dx);
  if(deriv_param == 1)
   return(_n76_dy);
  if(deriv_param == 2)
   return(_n76_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n76,
                  eval_func(_n76_eval).
                  evalf_func(_n76_evalf).
                  derivative_func(_n76_deriv))

///////////
// definition of _n77
DECLARE_FUNCTION_3P(_n77)

symbol _n77_dx("_n77_dx");
symbol _n77_dy("_n77_dy");
symbol _n77_dz("_n77_dz");

static ex _n77_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n77(x,y,z).hold() );
}

static ex _n77_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n77(x,y,z));
}

static ex _n77_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n77_dx);
  if(deriv_param == 1)
   return(_n77_dy);
  if(deriv_param == 2)
   return(_n77_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n77,
                  eval_func(_n77_eval).
                  evalf_func(_n77_evalf).
                  derivative_func(_n77_deriv))

///////////
// definition of _n78
DECLARE_FUNCTION_3P(_n78)

symbol _n78_dx("_n78_dx");
symbol _n78_dy("_n78_dy");
symbol _n78_dz("_n78_dz");

static ex _n78_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n78(x,y,z).hold() );
}

static ex _n78_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n78(x,y,z));
}

static ex _n78_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n78_dx);
  if(deriv_param == 1)
   return(_n78_dy);
  if(deriv_param == 2)
   return(_n78_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n78,
                  eval_func(_n78_eval).
                  evalf_func(_n78_evalf).
                  derivative_func(_n78_deriv))

///////////
// definition of _n79
DECLARE_FUNCTION_3P(_n79)

symbol _n79_dx("_n79_dx");
symbol _n79_dy("_n79_dy");
symbol _n79_dz("_n79_dz");

static ex _n79_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n79(x,y,z).hold() );
}

static ex _n79_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n79(x,y,z));
}

static ex _n79_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n79_dx);
  if(deriv_param == 1)
   return(_n79_dy);
  if(deriv_param == 2)
   return(_n79_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n79,
                  eval_func(_n79_eval).
                  evalf_func(_n79_evalf).
                  derivative_func(_n79_deriv))

///////////
// definition of _n80
DECLARE_FUNCTION_3P(_n80)

symbol _n80_dx("_n80_dx");
symbol _n80_dy("_n80_dy");
symbol _n80_dz("_n80_dz");

static ex _n80_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n80(x,y,z).hold() );
}

static ex _n80_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n80(x,y,z));
}

static ex _n80_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n80_dx);
  if(deriv_param == 1)
   return(_n80_dy);
  if(deriv_param == 2)
   return(_n80_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n80,
                  eval_func(_n80_eval).
                  evalf_func(_n80_evalf).
                  derivative_func(_n80_deriv))

///////////
// definition of _n81
DECLARE_FUNCTION_3P(_n81)

symbol _n81_dx("_n81_dx");
symbol _n81_dy("_n81_dy");
symbol _n81_dz("_n81_dz");

static ex _n81_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n81(x,y,z).hold() );
}

static ex _n81_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n81(x,y,z));
}

static ex _n81_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n81_dx);
  if(deriv_param == 1)
   return(_n81_dy);
  if(deriv_param == 2)
   return(_n81_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n81,
                  eval_func(_n81_eval).
                  evalf_func(_n81_evalf).
                  derivative_func(_n81_deriv))

///////////
// definition of _n82
DECLARE_FUNCTION_3P(_n82)

symbol _n82_dx("_n82_dx");
symbol _n82_dy("_n82_dy");
symbol _n82_dz("_n82_dz");

static ex _n82_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n82(x,y,z).hold() );
}

static ex _n82_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n82(x,y,z));
}

static ex _n82_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n82_dx);
  if(deriv_param == 1)
   return(_n82_dy);
  if(deriv_param == 2)
   return(_n82_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n82,
                  eval_func(_n82_eval).
                  evalf_func(_n82_evalf).
                  derivative_func(_n82_deriv))

///////////
// definition of _n83
DECLARE_FUNCTION_3P(_n83)

symbol _n83_dx("_n83_dx");
symbol _n83_dy("_n83_dy");
symbol _n83_dz("_n83_dz");

static ex _n83_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n83(x,y,z).hold() );
}

static ex _n83_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n83(x,y,z));
}

static ex _n83_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n83_dx);
  if(deriv_param == 1)
   return(_n83_dy);
  if(deriv_param == 2)
   return(_n83_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n83,
                  eval_func(_n83_eval).
                  evalf_func(_n83_evalf).
                  derivative_func(_n83_deriv))

///////////
// definition of _n84
DECLARE_FUNCTION_3P(_n84)

symbol _n84_dx("_n84_dx");
symbol _n84_dy("_n84_dy");
symbol _n84_dz("_n84_dz");

static ex _n84_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n84(x,y,z).hold() );
}

static ex _n84_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n84(x,y,z));
}

static ex _n84_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n84_dx);
  if(deriv_param == 1)
   return(_n84_dy);
  if(deriv_param == 2)
   return(_n84_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n84,
                  eval_func(_n84_eval).
                  evalf_func(_n84_evalf).
                  derivative_func(_n84_deriv))

///////////
// definition of _n85
DECLARE_FUNCTION_3P(_n85)

symbol _n85_dx("_n85_dx");
symbol _n85_dy("_n85_dy");
symbol _n85_dz("_n85_dz");

static ex _n85_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n85(x,y,z).hold() );
}

static ex _n85_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n85(x,y,z));
}

static ex _n85_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n85_dx);
  if(deriv_param == 1)
   return(_n85_dy);
  if(deriv_param == 2)
   return(_n85_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n85,
                  eval_func(_n85_eval).
                  evalf_func(_n85_evalf).
                  derivative_func(_n85_deriv))

///////////
// definition of _n86
DECLARE_FUNCTION_3P(_n86)

symbol _n86_dx("_n86_dx");
symbol _n86_dy("_n86_dy");
symbol _n86_dz("_n86_dz");

static ex _n86_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n86(x,y,z).hold() );
}

static ex _n86_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n86(x,y,z));
}

static ex _n86_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n86_dx);
  if(deriv_param == 1)
   return(_n86_dy);
  if(deriv_param == 2)
   return(_n86_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n86,
                  eval_func(_n86_eval).
                  evalf_func(_n86_evalf).
                  derivative_func(_n86_deriv))

///////////
// definition of _n87
DECLARE_FUNCTION_3P(_n87)

symbol _n87_dx("_n87_dx");
symbol _n87_dy("_n87_dy");
symbol _n87_dz("_n87_dz");

static ex _n87_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n87(x,y,z).hold() );
}

static ex _n87_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n87(x,y,z));
}

static ex _n87_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n87_dx);
  if(deriv_param == 1)
   return(_n87_dy);
  if(deriv_param == 2)
   return(_n87_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n87,
                  eval_func(_n87_eval).
                  evalf_func(_n87_evalf).
                  derivative_func(_n87_deriv))

///////////
// definition of _n88
DECLARE_FUNCTION_3P(_n88)

symbol _n88_dx("_n88_dx");
symbol _n88_dy("_n88_dy");
symbol _n88_dz("_n88_dz");

static ex _n88_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n88(x,y,z).hold() );
}

static ex _n88_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n88(x,y,z));
}

static ex _n88_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n88_dx);
  if(deriv_param == 1)
   return(_n88_dy);
  if(deriv_param == 2)
   return(_n88_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n88,
                  eval_func(_n88_eval).
                  evalf_func(_n88_evalf).
                  derivative_func(_n88_deriv))

///////////
// definition of _n89
DECLARE_FUNCTION_3P(_n89)

symbol _n89_dx("_n89_dx");
symbol _n89_dy("_n89_dy");
symbol _n89_dz("_n89_dz");

static ex _n89_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n89(x,y,z).hold() );
}

static ex _n89_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n89(x,y,z));
}

static ex _n89_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n89_dx);
  if(deriv_param == 1)
   return(_n89_dy);
  if(deriv_param == 2)
   return(_n89_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n89,
                  eval_func(_n89_eval).
                  evalf_func(_n89_evalf).
                  derivative_func(_n89_deriv))

///////////
// definition of _n90
DECLARE_FUNCTION_3P(_n90)

symbol _n90_dx("_n90_dx");
symbol _n90_dy("_n90_dy");
symbol _n90_dz("_n90_dz");

static ex _n90_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n90(x,y,z).hold() );
}

static ex _n90_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n90(x,y,z));
}

static ex _n90_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n90_dx);
  if(deriv_param == 1)
   return(_n90_dy);
  if(deriv_param == 2)
   return(_n90_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n90,
                  eval_func(_n90_eval).
                  evalf_func(_n90_evalf).
                  derivative_func(_n90_deriv))

///////////
// definition of _n91
DECLARE_FUNCTION_3P(_n91)

symbol _n91_dx("_n91_dx");
symbol _n91_dy("_n91_dy");
symbol _n91_dz("_n91_dz");

static ex _n91_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n91(x,y,z).hold() );
}

static ex _n91_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n91(x,y,z));
}

static ex _n91_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n91_dx);
  if(deriv_param == 1)
   return(_n91_dy);
  if(deriv_param == 2)
   return(_n91_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n91,
                  eval_func(_n91_eval).
                  evalf_func(_n91_evalf).
                  derivative_func(_n91_deriv))

///////////
// definition of _n92
DECLARE_FUNCTION_3P(_n92)

symbol _n92_dx("_n92_dx");
symbol _n92_dy("_n92_dy");
symbol _n92_dz("_n92_dz");

static ex _n92_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n92(x,y,z).hold() );
}

static ex _n92_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n92(x,y,z));
}

static ex _n92_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n92_dx);
  if(deriv_param == 1)
   return(_n92_dy);
  if(deriv_param == 2)
   return(_n92_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n92,
                  eval_func(_n92_eval).
                  evalf_func(_n92_evalf).
                  derivative_func(_n92_deriv))

///////////
// definition of _n93
DECLARE_FUNCTION_3P(_n93)

symbol _n93_dx("_n93_dx");
symbol _n93_dy("_n93_dy");
symbol _n93_dz("_n93_dz");

static ex _n93_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n93(x,y,z).hold() );
}

static ex _n93_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n93(x,y,z));
}

static ex _n93_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n93_dx);
  if(deriv_param == 1)
   return(_n93_dy);
  if(deriv_param == 2)
   return(_n93_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n93,
                  eval_func(_n93_eval).
                  evalf_func(_n93_evalf).
                  derivative_func(_n93_deriv))

///////////
// definition of _n94
DECLARE_FUNCTION_3P(_n94)

symbol _n94_dx("_n94_dx");
symbol _n94_dy("_n94_dy");
symbol _n94_dz("_n94_dz");

static ex _n94_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n94(x,y,z).hold() );
}

static ex _n94_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n94(x,y,z));
}

static ex _n94_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n94_dx);
  if(deriv_param == 1)
   return(_n94_dy);
  if(deriv_param == 2)
   return(_n94_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n94,
                  eval_func(_n94_eval).
                  evalf_func(_n94_evalf).
                  derivative_func(_n94_deriv))

///////////
// definition of _n95
DECLARE_FUNCTION_3P(_n95)

symbol _n95_dx("_n95_dx");
symbol _n95_dy("_n95_dy");
symbol _n95_dz("_n95_dz");

static ex _n95_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n95(x,y,z).hold() );
}

static ex _n95_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n95(x,y,z));
}

static ex _n95_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n95_dx);
  if(deriv_param == 1)
   return(_n95_dy);
  if(deriv_param == 2)
   return(_n95_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n95,
                  eval_func(_n95_eval).
                  evalf_func(_n95_evalf).
                  derivative_func(_n95_deriv))

///////////
// definition of _n96
DECLARE_FUNCTION_3P(_n96)

symbol _n96_dx("_n96_dx");
symbol _n96_dy("_n96_dy");
symbol _n96_dz("_n96_dz");

static ex _n96_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n96(x,y,z).hold() );
}

static ex _n96_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n96(x,y,z));
}

static ex _n96_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n96_dx);
  if(deriv_param == 1)
   return(_n96_dy);
  if(deriv_param == 2)
   return(_n96_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n96,
                  eval_func(_n96_eval).
                  evalf_func(_n96_evalf).
                  derivative_func(_n96_deriv))

///////////
// definition of _n97
DECLARE_FUNCTION_3P(_n97)

symbol _n97_dx("_n97_dx");
symbol _n97_dy("_n97_dy");
symbol _n97_dz("_n97_dz");

static ex _n97_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n97(x,y,z).hold() );
}

static ex _n97_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n97(x,y,z));
}

static ex _n97_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n97_dx);
  if(deriv_param == 1)
   return(_n97_dy);
  if(deriv_param == 2)
   return(_n97_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n97,
                  eval_func(_n97_eval).
                  evalf_func(_n97_evalf).
                  derivative_func(_n97_deriv))

///////////
// definition of _n98
DECLARE_FUNCTION_3P(_n98)

symbol _n98_dx("_n98_dx");
symbol _n98_dy("_n98_dy");
symbol _n98_dz("_n98_dz");

static ex _n98_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n98(x,y,z).hold() );
}

static ex _n98_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n98(x,y,z));
}

static ex _n98_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n98_dx);
  if(deriv_param == 1)
   return(_n98_dy);
  if(deriv_param == 2)
   return(_n98_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n98,
                  eval_func(_n98_eval).
                  evalf_func(_n98_evalf).
                  derivative_func(_n98_deriv))

///////////
// definition of _n99
DECLARE_FUNCTION_3P(_n99)

symbol _n99_dx("_n99_dx");
symbol _n99_dy("_n99_dy");
symbol _n99_dz("_n99_dz");

static ex _n99_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n99(x,y,z).hold() );
}

static ex _n99_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n99(x,y,z));
}

static ex _n99_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n99_dx);
  if(deriv_param == 1)
   return(_n99_dy);
  if(deriv_param == 2)
   return(_n99_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n99,
                  eval_func(_n99_eval).
                  evalf_func(_n99_evalf).
                  derivative_func(_n99_deriv))

///////////
// definition of _n100
DECLARE_FUNCTION_3P(_n100)

symbol _n100_dx("_n100_dx");
symbol _n100_dy("_n100_dy");
symbol _n100_dz("_n100_dz");

static ex _n100_eval(const ex &x,const ex &y,const ex &z)
{
  return( _n100(x,y,z).hold() );
}

static ex _n100_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_n100(x,y,z));
}

static ex _n100_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
  if(deriv_param == 0)
   return(_n100_dx);
  if(deriv_param == 1)
   return(_n100_dy);
  if(deriv_param == 2)
   return(_n100_dz);
  cerr <<"Illegal deriv_param\n";
}
REGISTER_FUNCTION(_n100,
                  eval_func(_n100_eval).
                  evalf_func(_n100_evalf).
                  derivative_func(_n100_deriv))

///////////
