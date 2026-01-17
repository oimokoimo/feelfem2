/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNpedge.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : pedge class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_PEDGE
#define FEM_SYNTAX_PEDGE

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "SNexprlist.hpp"
#include "../../class/string.hpp"
#include "../../class/Expression.hpp"
#include "../../class/meshEvalGinac.hpp"

class Edge;


class SNpedge : public SNunit {
public:
  SNpedge( char *nm, SNunit *ptr, Expression *xp,Expression *yp, 
	   char *pvar, Expression *from,Expression *to,int n) 
    : name(nm),SNunit("pedge",SN_PEDGE) {
    identifierLst = (SNidentifierlist *)ptr;
    xExpr         = xp ;
    yExpr         = yp ;
    parameterVar  = pvar;
    rangeFrom     = from;
    rangeTo       = to;
    nIntervals    = n;
    startOmitFlag = 0;
    return;
  }
  // with start omit
  SNpedge( int omit,char *nm, SNunit *ptr, Expression *xp,Expression *yp, 
	   char *pvar, Expression *from,Expression *to,int n) 
    : name(nm),SNunit("pedge",SN_PEDGE) {
    identifierLst = (SNidentifierlist *)ptr;
    xExpr         = xp ;
    yExpr         = yp ;
    parameterVar  = pvar;
    rangeFrom     = from;
    rangeTo       = to;
    nIntervals    = n;
    startOmitFlag = omit;
    return;
  }

  // Without two points
  SNpedge( char *nm,   Expression *xp,Expression *yp, 
	   char *pvar, Expression *from,Expression *to,int n) 
    : name(nm),SNunit("pedge",SN_PEDGE) {
    identifierLst = 0;
    xExpr         = xp ;
    yExpr         = yp ;
    parameterVar  = pvar;
    rangeFrom     = from;
    rangeTo       = to;
    nIntervals    = n;
    startOmitFlag = 0;
    return;
  }

  // With both two ends, and without segment specification
  SNpedge( char *nm, SNunit *ptr, Expression *xp,Expression *yp, 
	   char *pvar, Expression *from,Expression *to) 
    : name(nm),SNunit("pedge",SN_PEDGE) {
    identifierLst = (SNidentifierlist *)ptr;
    xExpr         = xp ;
    yExpr         = yp ;
    parameterVar  = pvar;
    rangeFrom     = from;
    rangeTo       = to;
    nIntervals    = 0;             // no specification
    startOmitFlag = 0;
    return;
  }

  // with start omit and without segment specification
  SNpedge( int omit,char *nm, SNunit *ptr, Expression *xp,Expression *yp, 
	   char *pvar, Expression *from,Expression *to) 
    : name(nm),SNunit("pedge",SN_PEDGE) {
    identifierLst = (SNidentifierlist *)ptr;
    xExpr         = xp ;
    yExpr         = yp ;
    parameterVar  = pvar;
    rangeFrom     = from;
    rangeTo       = to;
    nIntervals    = 0;             // no specification
    startOmitFlag = omit;
    return;
  }

  // Without two points and without segment specification
  SNpedge( char *nm,   Expression *xp,Expression *yp, 
	   char *pvar, Expression *from,Expression *to) 
    : name(nm),SNunit("pedge",SN_PEDGE) {
    identifierLst = 0;
    xExpr         = xp ;
    yExpr         = yp ;
    parameterVar  = pvar;
    rangeFrom     = from;
    rangeTo       = to;
    nIntervals    = 0;             // no specification
    startOmitFlag = 0;
    return;
  }

  //  SNpedge( char *nm, SNunit *ptr, SNunit *xp,SNunit *yp, 
  //	   char *pvar, SNunit *from,SNunit *to, int np) 
  //    : name(nm),SNunit("pedge",SN_PEDGE) {
  //    identifierLst = ptr;
  //    xExpr         = xp ;
  //    yExpr         = yp ;
  //    parameterVar  = pvar;
  //    rangeFrom     = from;
  //    rangeTo       = to;
  //    nPts          = np;
  //    
  //    return;
  //  }

  void print(ostream &);

  void errWrtName(ostream &ost ) {
    ost << name;
    return;
  }

  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  Edge *MakeEdgeObj(meshEvalGinac &);
  void EvaluateXYMinMax(meshEvalGinac &); // feelfemgeom.xmin,xmax,ymin,ymax
  

private:
  string  name;                  // parametric edge name
  SNidentifierlist *identifierLst;  // the first and the last point
  string  parameterVar;          // parameter 
  int     nIntervals;            // how many initial nodes on parametric edge
  Expression *xExpr;                 // expression (Expression *asExpression)
  Expression *yExpr;                 // expression (Expression *asExpression)
  Expression *rangeFrom;             // expression (Expression *asExpression)
  Expression *rangeTo;               // expression (Expression *asExpression)

  int startOmitFlag;

};

#endif
