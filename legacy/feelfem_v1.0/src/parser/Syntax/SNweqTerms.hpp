/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerms.hpp
 *  Date     : 2001/07/16
 *  Modified : 
 *  
 *  Purpose  : Weak integrand terms 
 *  
 */

#ifndef FEM_SYNTAX_WEQTERMS
#define FEM_SYNTAX_WEQTERMS

#include "SNunit.hpp"
#include "SNweqTerm.hpp"

#include "list.hpp"
#include "string.hpp"

class SNsolveNeumann;
class Neumann;
class IntegrandSet;
class Quadrature;

class SNweqTerms : public SNunit {
public:

  ~SNweqTerms() {}

  SNweqTerms(int flag,SNweqTerm *ptr) 
    : SNunit("weqTerms",SN_WEQTERMS) {

    weqTermFlagLst.addlast(flag);
    weqTermPtrLst.addlast(ptr);
  }

  void addWeqTerm(int flag,SNweqTerm *ptr)
  {
    weqTermFlagLst.addlast(flag);
    weqTermPtrLst.addlast(ptr);
  }

  void print(ostream &ost);

  //CHECK functions
  int HasBoundaryTerm(void);  // if boundary temrs exist, return YES

  int VariableDefinedCheck_Regional(list <string> &);
  int VariableDefinedCheck_Boundary(list <string> &,SNsolveNeumann *,
				    list <string> &);

  int EtypeConsistencyCheck(int refEtype,list <string> &,list<string>&);
  int QuadratureConsistencyCheck(int refEtype,list <string>&,Quadrature *);

  //Weakform (regional)
  void WriteRegionWeakEqStrByQuad(int flag, string &, char *,int &,int);
  void MakeRegionIntegrandSetInfoByQuad(string &,IntegrandSet *,list<string>&);

  //Weakform (boundary)
  void WriteBoundaryWeakEqStr(int flag, char *,int &,int);
  void MakeBoundaryIntegrandSetInfo(BoundaryIntegrandSet *,list<string>&);

  //SolveElement
  void AddVariablePtr_Regional( SolveElement *,list <string> &);
  void ListUpQuadrature_Regional( list <string> &);
  
  //Neumann
  void AddVariablePtr_Boundary( Neumann *,list <string> &,list <string>&);

private:

  list <SNweqTerm *>weqTermPtrLst;
  list <int>        weqTermFlagLst; //    (-1 or 1)  Sigma (flag[i]*term[i])

};

#endif
