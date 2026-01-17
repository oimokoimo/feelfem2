/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EwiseQuadEcalInfo.hpp
 *  Date     : 2002/07/29
 *  Modified : 
 *  
 *  Purpose  : Ecal information for EwiseQuad assignment
 *  
 */

#ifndef FEM_CLASS_EWISEQUADECALINFO
#define FEM_CLASS_EWISEQUADECALINFO

#include "orderedList.hpp"
#include "orderedPtrList.hpp"
#include "string.hpp"

#include "VariableEvalPair.hpp"

class Element;
class Variable;
class EwiseQuadTC;
class Quadrature;

class EwiseQuadEcalInfo {
  
public:
  EwiseQuadEcalInfo();
  ~EwiseQuadEcalInfo();

  void SetLetNo(int);

  void SetQuadraturePtr(Quadrature *ptr) {
    quadraturePtr = ptr;
    return;
  }
  void SetParametricElementPtr(Element *);
  Element *GetParametricElementPtr(void) {
    return parametricElemPtr;
  }

  void AddUniqElementPtr(Element *);     // element is used.
  void AddUniqD1ElementPtr(Element *);   // 1st derivative is used

  list <Element *> &GetUsedElementPtrList(void) {
    return usedElementPtrLst;
  }
  list <Element *> &GetUsedD1ElementPtrList(void) {
    return usedD1ElementPtrLst;
  }
  int  IsUseElementDerivative(void);

  void SetUseXYZ(int,int,int);

  //  int IsUseX(void);
  //  int IsUseY(void);
  //  int IsUseZ(void);

  int IsUseXVal(void) { return useXval; }
  int IsUseYVal(void) { return useYval; }
  int IsUseZVal(void) { return useZval; }

  void SetConvertedIdentifierList( EwiseQuadTC &);
  void SetConvertedUserFuncStrList( EwiseQuadTC &);
  void AddVariablePtr(Variable *);
  void InfoGenerate(void);
  list <string> &GetUsedUserFuncStrList(void) {
    return usedUserFuncStrLst;
  }

  list <VariableEvalPair *>& GetVariableEvalPairPtrList(void) {
    return vPairLst;    // VariableEvalPair pointer list  , for assign_ewquad
  }

  // move to public (2002/11/19, for integral (call from Assign_EwiseQuad.cpp))
  void AddUniqElementPtrList(Element *);
  void AddUniqD1ElementPtrList(Element *);


private:


  int letNo;

  Quadrature *quadraturePtr;
  Element    *parametricElemPtr;

  int useX,useY,useZ;
  int useXval,useYval,useZval;           // used for qx

  list <Element *>usedElementPtrLst;     // element is used
  list <Element *>usedD1ElementPtrLst;   // 1st derivative is used

  orderedPtrList <Variable *>varPtrLst;

  orderedPtrList <Variable *>dxVarLst;
  orderedPtrList <Variable *>dyVarLst;
  orderedPtrList <Variable *>dzVarLst;

  list <string>identifierLst;           // converted identifier list

  list <VariableEvalPair *>vPairLst;    // VariableEvalPair pointer list
  list <string>usedUserFuncStrLst;

};
#endif
