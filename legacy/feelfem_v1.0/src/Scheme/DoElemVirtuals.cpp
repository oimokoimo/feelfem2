/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DoElemVirtuals.cpp
 *  Date     : 2001/11/29
 *  Modified : 
 *  
 *  Purpose  : DoElem family virtual functions
 *  
 */

#include <iostream.h>
#include "ElemGeneratorVirtuals.hpp"


//void ElemGeneratorVirtuals::DoElemStarters() { 
//  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemStarters)\n"; }

//void ElemGeneratorVirtuals::DoElemDeclareArgumentVariablesPM(SolveElement *sePtr) { cerr << "THIS IS ELEMGENERATORVIRTUALS\n"; } 

void ElemGeneratorVirtuals::DoElemParameters(SolveElement *sePtr) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemParameters)\n"; }

void ElemGeneratorVirtuals::DoElemVariableDefinitionsPM(SolveElement *sePtr) {
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemVariableDefinitionsPM)\n"; }

void ElemGeneratorVirtuals::DoElemInitializer(SolveElement *sePtr) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemInitializer)\n"; }

void ElemGeneratorVirtuals::DoElemElementLoopStart(int n) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemElementLoopStart)\n"; }

void ElemGeneratorVirtuals::DoElemCallEcalRoutine(SolveElement *sePtr,int n) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemCallEcalRoutine)\n"; }

void ElemGeneratorVirtuals::DoElemElementLoopEnd(int n) {
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemElementLoopEnd)\n"; }

void ElemGeneratorVirtuals::DoElemReturnSequence(SolveElement *sePtr) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemReturnSequence)\n"; }

  // for vector processing  ElemNormalVectorAssembly() etc.
void ElemGeneratorVirtuals::DoElemQuadratureLoopStart
(SolveElement *sePtr, int n) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemQuadratureLoopStart)\n"; }

void ElemGeneratorVirtuals::DoElemQuadratureLoopEnd
(SolveElement *sePtr, int n) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemQuadratureLoopEnd)\n"; } 

void ElemGeneratorVirtuals::DoElemQuadLoopPreparation
(SolveElement *sePtr, int n) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemQuadLoopPreparation)\n"; } 

void ElemGeneratorVirtuals::DoElemQuadLoopMakeAllElement
(SolveElement *sePtr, int n) { 
  cerr << "THIS IS ELEMGENERATORVIRTUALS(DoElemQuadLoopMakeAllElement)\n"; } 
