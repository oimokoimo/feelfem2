/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNpedge.cpp
 *  Date     : 2001/04/09
 *  Modified : 
 *  
 *  Purpose  : Make Edge object from Parametric edge
 *  
 */

#include <cmath>             // for sqrt
			     //
using std::sqrt;
#include "../../class/feelfuncs.hpp"
#include "../../class/feeldef.hpp"

#include "SNunit.hpp"
#include "SNpedge.hpp"
#include "SNidentifierlist.hpp"
#include "SNname.hpp"

#include "../../class/Expression.hpp"

#include "../../class/meshEvalGinac.hpp"

#include "../../class/Point.hpp"
#include "../../class/Edge.hpp"
#include "../../class/Geometry.hpp"

Edge *SNpedge::MakeEdgeObj(meshEvalGinac &evaluator)
{
  Edge *egPtr = new Edge(name,TYPE_EDGE_PARAMETRIC);

  list <string> strLst;
  Point *startPointPtr,*endPointPtr;

  if(identifierLst != 0) {
    ((SNidentifierlist *)identifierLst)->StoreContentsInStringLst( strLst );

    // Start point is omitted.
    if(startOmitFlag != 0) {
      startPointPtr = 0;
      endPointPtr   = feelfemgeom.GetPointPtrByName( strLst.lastElement());
    }
    else {
      startPointPtr = feelfemgeom.GetPointPtrByName( strLst.firstElement());

      if(strLst.getNumberOfElements() == 1) {
	endPointPtr = 0;
      }
      else {
	endPointPtr   = feelfemgeom.GetPointPtrByName( strLst.lastElement());
      }
    }
  }
  else {
    startPointPtr = 0;
    endPointPtr   = 0;
  }
  //  Only one side point specification case is under construction

  //  double sx = startPointPtr->getX();
  //  double sy = startPointPtr->getY();
  //  double ex = endPointPtr->getX();
  //  double ey = endPointPtr->getY();
  //  cerr << "PEDGE (" << sx << "," << sy ;
  //  cerr <<     ")-(" << ex << "," << ey << ")" << endl;


  Expression *exprPtr;
  //  ptrList <evalPair *> evalPairPtrLst;


  char   buf[MAX_EXPRPRINT_BUF];
  int errFlag;

  // calculate parameter at start
  exprPtr = (Expression *)rangeFrom;
  buf[0] = '\0';
  exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		     (void *)(&(evaluator.evalList)),(void *)0);
  double st = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);

  // calculate parameter at end
  exprPtr = (Expression *)rangeTo;
  buf[0] = '\0';
  exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		     (void *)&(evaluator.evalList),(void *)0);
  double et = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);


  // First Point
  if(startPointPtr != 0) {
    egPtr->AddPointPtr(startPointPtr);
  }

  evalPair *epairPtr = new evalPair( parameterVar );

  if(nIntervals > 0) {     // nInterval is explicitly specified by user

    // Parametric Point
    double t,dt;

    int npts         = nIntervals-1;
    int start_step;

    dt = (et-st)/nIntervals;

    if(startPointPtr == 0) {
      npts       = npts + 1;
      start_step = 0;
    }
    else {
      start_step = 1;
    }

    if(endPointPtr == 0) {
      npts       = npts + 1;
    }


    // Caution::THIS IS DELETED IN THE END OF THIS ROUTINE
    (evaluator.evalList).addlast( epairPtr );

    for(int i=0;i<npts; i++) {
      t = st + dt*(i+start_step);
      epairPtr->setValue( t );

      exprPtr = (Expression *)xExpr;
      buf[0] = '\0';
      exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
			 (void *)&(evaluator.evalList),(void *)0);
      double px = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);

      exprPtr = (Expression *)yExpr;
      buf[0] = '\0';
      exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
			 (void *)&(evaluator.evalList),(void *)0);
      double py = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);
    
      //    cerr << "(" << px << "," << py << ")";

      Point *paramPointPtr = new Point(px,py);
      paramPointPtr->SetType(TYPE_POINT_PARAMETRICEDGE);
      egPtr->AddPointPtr(paramPointPtr);
      feelfemgeom.AddPointPtr(paramPointPtr);
    }

  }   // end of specified case of nInterval

  else {  // nInterval is not specified

    assert(nIntervals == 0);
    // Parametric Point
    double ds;
    
    ds = feelfemgeom.getApproximateH2D();

    // Caution::THIS IS DELETED IN THE END OF THIS ROUTINE
    (evaluator.evalList).addlast( epairPtr );

    double t,tt;   //  st <= t <= et
    double dt,dtMin,dtMax;
    double px,py,pxg,pyg;

    dtMin = 0.0;
    dtMax = 0.0;
    t = st;

    // starts (x(st),y(st)) must be added
    if(startPointPtr == 0) {   // (x(st),y(st)) must be added
      epairPtr->setValue( t );
      exprPtr = (Expression *)xExpr;
      buf[0] = '\0';
      exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
			 (void *)&(evaluator.evalList),(void *)0);
      px = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);

      exprPtr = (Expression *)yExpr;
      buf[0] = '\0';
      exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
			 (void *)&(evaluator.evalList),(void *)0);
      py = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);
    
      Point *paramPointPtr = new Point(px,py);
      paramPointPtr->SetType(TYPE_POINT_PARAMETRICEDGE);
      egPtr->AddPointPtr(paramPointPtr);
      feelfemgeom.AddPointPtr(paramPointPtr);
    }
    else {
      px = startPointPtr->getX();
      py = startPointPtr->getY();
    }

    // now dt is set initial guess of dt
    dt = (et-st)/DEFAULT_NINTERVALS_FOR_PEDGE;  // guess


    int fail;

    fail = 0;
    // (px,py) is current generated point
    while(t + dt  < et) {
      tt = t + dt;
      epairPtr->setValue( tt );

      exprPtr = (Expression *)xExpr;
      buf[0] = '\0';
      exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
			 (void *)&(evaluator.evalList),(void *)0);
      pxg = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);

      exprPtr = (Expression *)yExpr;
      buf[0] = '\0';
      exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
			 (void *)&(evaluator.evalList),(void *)0);
      pyg = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);
    

      double len = sqrt((px-pxg)*(px-pxg)+(py-pyg)*(py-pyg));

      if(len/ds > PEDGE_GENERATE_MINRATE &&
	 len/ds < PEDGE_GENERATE_MAXRATE    ) {   // tolerance

	//	cerr << "Fail="<<fail << endl;

	Point *paramPointPtr = new Point(pxg,pyg);   // be careful pxG,pyG
	paramPointPtr->SetType(TYPE_POINT_PARAMETRICEDGE);
	egPtr->AddPointPtr(paramPointPtr);
	feelfemgeom.AddPointPtr(paramPointPtr);
	
	t  = tt;
	px = pxg;
	py = pyg;

	fail  = 0;
	dtMax = 0.0;
	dtMin = 0.0;

	continue;
      }

      fail++;

      //      cerr << "Fail No. "<<fail << "  len/ds=" << len/ds << 
      //	" dt="<<dt<< "  dtMin="<<dtMin<<" dtMax="<<dtMax <<endl;
      

      if(fail >PEDGE_GENERATE_MAX_FAIL) {
	      std::cerr << "Too many failure....\n";
	assert(1==0);
      }

      // not torelable
      if(len/ds < PEDGE_GENERATE_MINRATE) {
	// Initial guess is too small
	dtMin = dt;

	if(fail >3 ) {

	  if(dtMax == 0.0) {
	    dt = dt * 1.5;
	    continue;
	  }

	  dt = (dtMax+dtMin) / 2.0;
	  continue;
	}
	dt = dt / (len/ds) * (1.0-(1.0-PEDGE_GENERATE_MINRATE)/2.0);  // linear outer interpolation

	//	dt = dt * 2.0;
	continue;
      }
      else {
	dtMax = dt;

	if(fail >3 ) {
	  if(dtMin == 0.0) {
	    dt = dt *0.75;
	    continue;
	  }
	  
	  dt = (dtMax+dtMin) /2.0;
	  continue;
	}

	dt = dt / (len/ds) * (1.0+(PEDGE_GENERATE_MAXRATE-1.0)/2.0);
	//	dt = dt / 2.0;


	continue;
      }

      assert(1==0);
      //Point *paramPointPtr = new Point(px,py);
      //      paramPointPtr->SetType(TYPE_POINT_PARAMETRICEDGE);
      //      egPtr->AddPointPtr(paramPointPtr);
      //      feelfemgeom.AddPointPtr(paramPointPtr);
    }
  }  // end of if (nIntervals > 0)

  if(endPointPtr != 0) {
    egPtr->AddPointPtr(endPointPtr);
  }

  (evaluator.evalList).deletelastlink();
  delete epairPtr;                           // may cause segmentation fault...

  return(egPtr);
}

void SNpedge::EvaluateXYMinMax(meshEvalGinac &evaluator)
{

  Expression *exprPtr;
  char   buf[MAX_EXPRPRINT_BUF];
  int errFlag;

  // calculate parameter at start
  exprPtr = (Expression *)rangeFrom;
  buf[0] = '\0';
  exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		     (void *)(&(evaluator.evalList)),(void *)0);
  double st = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);

  // calculate parameter at end
  exprPtr = (Expression *)rangeTo;
  buf[0] = '\0';
  exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		     (void *)&(evaluator.evalList),(void *)0);
  double et = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);

  // Parametric Point
  double t,dt;

  //  int npts = PEDGE_DEFAULT_INNERPOINTS;
  int npts;
  if(nIntervals > 0) {
    npts = nIntervals-1;
  }
  else {
    npts = DEFAULT_NINTERVALS_FOR_PEDGE-1;    // 100
  }

  int start_step;

  dt = (et-st)/(npts + 1);

  start_step = 0;
  evalPair *epairPtr = new evalPair( parameterVar );

  // Caution::THIS IS DELETED IN THE END OF THIS ROUTINE
  (evaluator.evalList).addlast( epairPtr );

  for(int i=0;i<npts; i++) {
    t = st + dt*(i+start_step);
    epairPtr->setValue( t );

    exprPtr = (Expression *)xExpr;
    buf[0] = '\0';
    exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		       (void *)&(evaluator.evalList),(void *)0);
    double px = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);

    exprPtr = (Expression *)yExpr;
    buf[0] = '\0';
    exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		       (void *)&(evaluator.evalList),(void *)0);
    double py = evaluateBufGinac(buf,&(evaluator.evalList),errFlag);
    
    feelfemgeom.candidateXMin( px );
    feelfemgeom.candidateXMax( px );
    feelfemgeom.candidateYMin( py );
    feelfemgeom.candidateYMax( py );

  }

  (evaluator.evalList).deletelastlink();
  delete epairPtr;                           // may cause segmentation fault...

  //  cerr << "getApproximateH2d = " << feelfemgeom.getApproximateH2D()<< endl;

  return;
}

void SNpedge::print(std::ostream &ost)
{
  ost << "pedge ";


  ost <<  name;

  if(identifierLst) identifierLst->print(ost);

  ost << "[(";
  xExpr -> print(ost);
  ost << ",";
  yExpr -> print(ost);
  ost << ")," << parameterVar << "=";

  rangeFrom->print(ost);
  ost << ",";
  rangeTo->print(ost);
  ost << "]";

  return;
}
