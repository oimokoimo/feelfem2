
// 1 parametres

DECLARE_FUNCTION_1P(_fn11)

symbol _fn11_dx("_fn11_dx");
symbol _fn11_dy("_fn11_dy");
symbol _fn11_dz("_fn11_dz");

static ex _fn11_eval(const ex &x)
{
  return( _fn11(x).hold() );
}

static ex _fn11_evalf(const ex &x)
{
  return(_fn11(x));
}
static ex _fn11_deriv(const ex &x, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn11_dx);
  if(deriv_param == 1)
   return(_fn11_dy);
  if(deriv_param == 2)
   return(_fn11_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn11,
                  eval_func(_fn11_eval).
                  evalf_func(_fn11_evalf).
                  derivative_func(_fn11_deriv))
DECLARE_FUNCTION_1P(_fn12)

symbol _fn12_dx("_fn12_dx");
symbol _fn12_dy("_fn12_dy");
symbol _fn12_dz("_fn12_dz");

static ex _fn12_eval(const ex &x)
{
  return( _fn12(x).hold() );
}

static ex _fn12_evalf(const ex &x)
{
  return(_fn12(x));
}
static ex _fn12_deriv(const ex &x, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn12_dx);
  if(deriv_param == 1)
   return(_fn12_dy);
  if(deriv_param == 2)
   return(_fn12_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn12,
                  eval_func(_fn12_eval).
                  evalf_func(_fn12_evalf).
                  derivative_func(_fn12_deriv))
DECLARE_FUNCTION_1P(_fn13)

symbol _fn13_dx("_fn13_dx");
symbol _fn13_dy("_fn13_dy");
symbol _fn13_dz("_fn13_dz");

static ex _fn13_eval(const ex &x)
{
  return( _fn13(x).hold() );
}

static ex _fn13_evalf(const ex &x)
{
  return(_fn13(x));
}
static ex _fn13_deriv(const ex &x, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn13_dx);
  if(deriv_param == 1)
   return(_fn13_dy);
  if(deriv_param == 2)
   return(_fn13_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn13,
                  eval_func(_fn13_eval).
                  evalf_func(_fn13_evalf).
                  derivative_func(_fn13_deriv))
DECLARE_FUNCTION_1P(_fn14)

symbol _fn14_dx("_fn14_dx");
symbol _fn14_dy("_fn14_dy");
symbol _fn14_dz("_fn14_dz");

static ex _fn14_eval(const ex &x)
{
  return( _fn14(x).hold() );
}

static ex _fn14_evalf(const ex &x)
{
  return(_fn14(x));
}
static ex _fn14_deriv(const ex &x, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn14_dx);
  if(deriv_param == 1)
   return(_fn14_dy);
  if(deriv_param == 2)
   return(_fn14_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn14,
                  eval_func(_fn14_eval).
                  evalf_func(_fn14_evalf).
                  derivative_func(_fn14_deriv))
DECLARE_FUNCTION_1P(_fn15)

symbol _fn15_dx("_fn15_dx");
symbol _fn15_dy("_fn15_dy");
symbol _fn15_dz("_fn15_dz");

static ex _fn15_eval(const ex &x)
{
  return( _fn15(x).hold() );
}

static ex _fn15_evalf(const ex &x)
{
  return(_fn15(x));
}
static ex _fn15_deriv(const ex &x, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn15_dx);
  if(deriv_param == 1)
   return(_fn15_dy);
  if(deriv_param == 2)
   return(_fn15_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn15,
                  eval_func(_fn15_eval).
                  evalf_func(_fn15_evalf).
                  derivative_func(_fn15_deriv))

// 2 parametres

DECLARE_FUNCTION_2P(_fn21)

symbol _fn21_dx("_fn21_dx");
symbol _fn21_dy("_fn21_dy");
symbol _fn21_dz("_fn21_dz");

static ex _fn21_eval(const ex &x,const ex &y)
{
  return( _fn21(x,y).hold() );
}

static ex _fn21_evalf(const ex &x,const ex &y)
{
  return(_fn21(x,y));
}
static ex _fn21_deriv(const ex &x,const ex &y, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn21_dx);
  if(deriv_param == 1)
   return(_fn21_dy);
  if(deriv_param == 2)
   return(_fn21_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn21,
                  eval_func(_fn21_eval).
                  evalf_func(_fn21_evalf).
                  derivative_func(_fn21_deriv))
DECLARE_FUNCTION_2P(_fn22)

symbol _fn22_dx("_fn22_dx");
symbol _fn22_dy("_fn22_dy");
symbol _fn22_dz("_fn22_dz");

static ex _fn22_eval(const ex &x,const ex &y)
{
  return( _fn22(x,y).hold() );
}

static ex _fn22_evalf(const ex &x,const ex &y)
{
  return(_fn22(x,y));
}
static ex _fn22_deriv(const ex &x,const ex &y, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn22_dx);
  if(deriv_param == 1)
   return(_fn22_dy);
  if(deriv_param == 2)
   return(_fn22_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn22,
                  eval_func(_fn22_eval).
                  evalf_func(_fn22_evalf).
                  derivative_func(_fn22_deriv))
DECLARE_FUNCTION_2P(_fn23)

symbol _fn23_dx("_fn23_dx");
symbol _fn23_dy("_fn23_dy");
symbol _fn23_dz("_fn23_dz");

static ex _fn23_eval(const ex &x,const ex &y)
{
  return( _fn23(x,y).hold() );
}

static ex _fn23_evalf(const ex &x,const ex &y)
{
  return(_fn23(x,y));
}
static ex _fn23_deriv(const ex &x,const ex &y, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn23_dx);
  if(deriv_param == 1)
   return(_fn23_dy);
  if(deriv_param == 2)
   return(_fn23_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn23,
                  eval_func(_fn23_eval).
                  evalf_func(_fn23_evalf).
                  derivative_func(_fn23_deriv))
DECLARE_FUNCTION_2P(_fn24)

symbol _fn24_dx("_fn24_dx");
symbol _fn24_dy("_fn24_dy");
symbol _fn24_dz("_fn24_dz");

static ex _fn24_eval(const ex &x,const ex &y)
{
  return( _fn24(x,y).hold() );
}

static ex _fn24_evalf(const ex &x,const ex &y)
{
  return(_fn24(x,y));
}
static ex _fn24_deriv(const ex &x,const ex &y, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn24_dx);
  if(deriv_param == 1)
   return(_fn24_dy);
  if(deriv_param == 2)
   return(_fn24_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn24,
                  eval_func(_fn24_eval).
                  evalf_func(_fn24_evalf).
                  derivative_func(_fn24_deriv))
DECLARE_FUNCTION_2P(_fn25)

symbol _fn25_dx("_fn25_dx");
symbol _fn25_dy("_fn25_dy");
symbol _fn25_dz("_fn25_dz");

static ex _fn25_eval(const ex &x,const ex &y)
{
  return( _fn25(x,y).hold() );
}

static ex _fn25_evalf(const ex &x,const ex &y)
{
  return(_fn25(x,y));
}
static ex _fn25_deriv(const ex &x,const ex &y, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn25_dx);
  if(deriv_param == 1)
   return(_fn25_dy);
  if(deriv_param == 2)
   return(_fn25_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn25,
                  eval_func(_fn25_eval).
                  evalf_func(_fn25_evalf).
                  derivative_func(_fn25_deriv))

// 3 parametres

DECLARE_FUNCTION_3P(_fn31)

symbol _fn31_dx("_fn31_dx");
symbol _fn31_dy("_fn31_dy");
symbol _fn31_dz("_fn31_dz");

static ex _fn31_eval(const ex &x,const ex &y,const ex &z)
{
  return( _fn31(x,y,z).hold() );
}

static ex _fn31_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_fn31(x,y,z));
}
static ex _fn31_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn31_dx);
  if(deriv_param == 1)
   return(_fn31_dy);
  if(deriv_param == 2)
   return(_fn31_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn31,
                  eval_func(_fn31_eval).
                  evalf_func(_fn31_evalf).
                  derivative_func(_fn31_deriv))
DECLARE_FUNCTION_3P(_fn32)

symbol _fn32_dx("_fn32_dx");
symbol _fn32_dy("_fn32_dy");
symbol _fn32_dz("_fn32_dz");

static ex _fn32_eval(const ex &x,const ex &y,const ex &z)
{
  return( _fn32(x,y,z).hold() );
}

static ex _fn32_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_fn32(x,y,z));
}
static ex _fn32_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn32_dx);
  if(deriv_param == 1)
   return(_fn32_dy);
  if(deriv_param == 2)
   return(_fn32_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn32,
                  eval_func(_fn32_eval).
                  evalf_func(_fn32_evalf).
                  derivative_func(_fn32_deriv))
DECLARE_FUNCTION_3P(_fn33)

symbol _fn33_dx("_fn33_dx");
symbol _fn33_dy("_fn33_dy");
symbol _fn33_dz("_fn33_dz");

static ex _fn33_eval(const ex &x,const ex &y,const ex &z)
{
  return( _fn33(x,y,z).hold() );
}

static ex _fn33_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_fn33(x,y,z));
}
static ex _fn33_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn33_dx);
  if(deriv_param == 1)
   return(_fn33_dy);
  if(deriv_param == 2)
   return(_fn33_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn33,
                  eval_func(_fn33_eval).
                  evalf_func(_fn33_evalf).
                  derivative_func(_fn33_deriv))
DECLARE_FUNCTION_3P(_fn34)

symbol _fn34_dx("_fn34_dx");
symbol _fn34_dy("_fn34_dy");
symbol _fn34_dz("_fn34_dz");

static ex _fn34_eval(const ex &x,const ex &y,const ex &z)
{
  return( _fn34(x,y,z).hold() );
}

static ex _fn34_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_fn34(x,y,z));
}
static ex _fn34_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn34_dx);
  if(deriv_param == 1)
   return(_fn34_dy);
  if(deriv_param == 2)
   return(_fn34_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn34,
                  eval_func(_fn34_eval).
                  evalf_func(_fn34_evalf).
                  derivative_func(_fn34_deriv))
DECLARE_FUNCTION_3P(_fn35)

symbol _fn35_dx("_fn35_dx");
symbol _fn35_dy("_fn35_dy");
symbol _fn35_dz("_fn35_dz");

static ex _fn35_eval(const ex &x,const ex &y,const ex &z)
{
  return( _fn35(x,y,z).hold() );
}

static ex _fn35_evalf(const ex &x,const ex &y,const ex &z)
{
  return(_fn35(x,y,z));
}
static ex _fn35_deriv(const ex &x,const ex &y,const ex &z, unsigned deriv_param)
{
if(deriv_param == 0)
  return(_fn35_dx);
  if(deriv_param == 1)
   return(_fn35_dy);
  if(deriv_param == 2)
   return(_fn35_dz);
  cerr <<"Illegal deriv_param";
}
REGISTER_FUNCTION(_fn35,
                  eval_func(_fn35_eval).
                  evalf_func(_fn35_evalf).
                  derivative_func(_fn35_deriv))
