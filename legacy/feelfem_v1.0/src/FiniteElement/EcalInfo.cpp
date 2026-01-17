/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EcalInfo.cpp
 *  Date     : 2002/02/22
 *  Modified : 
 *  
 *  Purpose  : These are called from DiscretizedComponent_Ecalinfo.cpp
 *  
 */

#include "EcalInfo.hpp"

EcalInfo::EcalInfo()
{
  solveNo = 0;
  solveElementNo = 0;
  quadNo  = 0;

  diffOrder = 0;
  //  diffOrder = 1;       // currently second order only.....
  
  commonTerms = 0;
  integrandTerms = 0;

  // use series
  useX  = 0; useY  = 0; useZ  = 0;
  useNX = 0; useNY = 0; useNZ = 0;
  
  return;
}

EcalInfo::~EcalInfo()
{
  commonTermLst.~orderedList();
  integrandTermLst.~orderedList();

  return;
}

void EcalInfo::SetUseXYZ(int x,int y,int z)
{
  useX = x;
  useY = y;
  useZ = z;
  return;
}

void EcalInfo::SetUseNXNYNZ(int nx,int ny,int nz)
{
  useNX = nx;
  useNY = ny;
  useNZ = nz;
  return;
}

int EcalInfo::IsUseX(void)
{
  return useX;
}

int EcalInfo::IsUseY(void)
{
  return useY;
}

int EcalInfo::IsUseZ(void)
{
  return useZ;
}

int EcalInfo::IsUseNX(void)
{
  return useNX;
}

int EcalInfo::IsUseNY(void)
{
  return useNY;
}

int EcalInfo::IsUseNZ(void)
{
  return useNZ;
}


void EcalInfo::SetNumbers(int sNo, int seNo, int qNo)
{
  solveNo = sNo;
  solveElementNo = seNo;
  quadNo = qNo;

  return;
}

void EcalInfo::SetNumbers(int sNo, int nNo)  // boundary has two int
{
  solveNo = sNo;
  ncondNo = nNo;

  return;
}

void EcalInfo::AddUniqTermCommon( char *termName)
{
  string name = termName;

  if(commonTermLst.includes(name) ) {
    return;
  }

  commonTermLst.add(name);
  commonTerms++;
  return;
}

void EcalInfo::AddUniqTermIntegrand( char *termName)
{
  string name = termName;

  if(integrandTermLst.includes(name) ) {
    return;
  }

  integrandTermLst.add(name);
  integrandTerms++;
  return;
}

void EcalInfo::SumUpIntegrandTerm(orderedList <string>&termLst)
{
  listIterator <string> itr(integrandTermLst);
  
  for(itr.init(); !itr ; ++itr ) {
    
    if(termLst.includes(itr())) continue;
    termLst.add(itr());
    
  }
  return;
}

void EcalInfo::AddUniqEcalEvalPair( Element *ePtr, int type)
{
  EcalEvalPair *eepPtr = new EcalEvalPair(ePtr,type);
  
  if(ecalEvalPairPtrLst.includes(eepPtr)) {
    delete eepPtr;
    return;
  }

  ecalEvalPairPtrLst.addlast(eepPtr);
  
  if(! usedElementPtrLst.includes(ePtr) ) {
    usedElementPtrLst.addlast(ePtr);
  }

  return;
}

// currently, no difference from regional one
void EcalInfo::AddUniqEcalEvalPair_boundary( Element *ePtr, int type)
{
  EcalEvalPair *eepPtr = new EcalEvalPair(ePtr,type);
  
  if(ecalEvalPairPtrLst.includes(eepPtr)) {
    delete eepPtr;
    return;
  }

  ecalEvalPairPtrLst.addlast(eepPtr);
  
  if(! usedElementPtrLst.includes(ePtr) ) {
    usedElementPtrLst.addlast(ePtr);
  }

  return;
}
