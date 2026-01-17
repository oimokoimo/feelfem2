/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Quadrature_dbgXDisplay.cpp
 *  Date     : 2001/12/17
 *  Modified : 
 *  
 *  Purpose  : Debug for quadrature information
 *  
 */

#include <stdio.h>       // for BUFSIZ
#include <strstream.h>
#include <iostream.h>
#include <stdlib.h>      // for exit()
#include <assert.h>

#include "dbgFunctions.hpp"
#include "xplotfuncs.hpp"

#include "feeldef.hpp"

#include "Quadrature.hpp"

void Quadrature::dbgXDisplay(void)
{
  char buf[BUFSIZ];
  ostrstream outputStream(buf,BUFSIZ);

  double x1,y1;

  switch(elementEtype) {
    
  case ELEMENT_TYPE_TRI:
    dbgOpenpl();
    fspace(-0.1,-0.1,1.1,1.1);

    x1 = 0.0;    y1 = 1.0;
    outputStream << name << " [triangle]" << '\0';

    fmove(0.0,0.0);
    fcont(1.0,0.0);
    fcont(0.0,1.0);
    fcont(0.0,0.0);

    break;

  case ELEMENT_TYPE_RECT:
    dbgOpenpl();
    fspace(-1.2,-1.2,1.2,1.2);

    x1 = -1.0;    y1 = 1.0;
    outputStream << name << " [rectangle]" << '\0';

    fmove(-1.0,-1.0);
    fcont( 1.0,-1.0);
    fcont( 1.0, 1.0);
    fcont(-1.0, 1.0);
    fcont(-1.0,-1.0);

    break;

  case ELEMENT_TYPE_TETRA:
    dbgOpenpl();
    fspace(-0.1,-0.1,1.1,1.1);

    x1 = 0.0;    y1 = 1.0;
    outputStream << name << " [tetrahedra]" << '\0';

    break;


  case ELEMENT_TYPE_CUBE:
    dbgOpenpl();
    fspace(-0.1,-0.1,1.1,1.1);

    x1 = 0.0;    y1 = 1.0;
    outputStream << name << " [hexahedra]" << '\0';


    break;

  default:
    cerr << "Quadrature::Quadrature_dbgXDisplay.cpp (not support etype for disp) "
	 << elementEtype << endl;
    return;
  }

  // title
  fsymbol(x1,y1,buf);

  //  cerr << name << " pts=" << GetQuadraturePoints() << endl;
  for(int i=0;i<GetQuadraturePoints();i++) {
    double xi,eta,zeta;
    double w;

    w    = GetIthWeight(i);

    switch(dimension){
    case 1:
      xi   = GetIthXi(i);
      fpeke(xi,0.0);
      
      break;

    case 2:
      xi   = GetIthXi(i);
      eta  = GetIthEta(i);
      fpeke(xi,eta);

      {
	char text[80];
	sprintf(text,"%15.11f%c", w ,'\0');
	fsymbol(xi+0.05,eta,text);
      }
      
      // cerr << "No."<<i+1 << " (" << xi << ","<<eta <<") : " << w << endl;

      break;

    case 3:
      xi   = GetIthXi(i);
      eta  = GetIthEta(i);

      cerr << "3d fpeke is not existing now." << endl;
      break;

    default:
      assert(1==0);
      break;
    }
  }  // iteration for GaussPoints

  

  xwait();
  closepl();

  return;
}
