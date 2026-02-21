/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SystemError.cpp
 *  Date     : 2001/03/12
 *  Modified : 2001/12/19  add warning message
 *  
 *  Purpose  :
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include <iostream>

#include "feelfem.hpp"                       // for feelfem_web parameter
#include "../parser/Syntax/SNunit.hpp"
#include "string.hpp"

static int checkErrors = 0;
static int checkWarnings = 0;

#define  WEBOUT      std::cout

void SystemError_A(const char *mesg)
{
  checkErrors ++;

  if(feelfem_web) {
    WEBOUT << "feelfem Error : ";
    WEBOUT << mesg << std::endl;
  }
  else {
	  std::cerr << "feelfem Error : ";
	  std::cerr << mesg << std::endl;
  }

  return;
}


void SystemErrorA(SNunit *snunitPtr, const char *mesg)
{
  checkErrors ++;

  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << mesg << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    std::cerr << mesg << std::endl;
  }

  return;
}

void SystemErrorAA(SNunit *snunitPtr, const char *mesg1,const char *mesg2)
{
  checkErrors ++;
  
  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << mesg1 << mesg2  << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    std::cerr << mesg1 << mesg2  << std::endl;
  }

  return;
}

void SystemErrorAAA(SNunit *snunitPtr,
		    const char *m1,const char *m2,const char *m3)
{
  checkErrors ++;

  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << m1 << m2 << m3 << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    std::cerr << m1 << m2 << m3 << std::endl;
  }

  return;
}

void SystemErrorNameA(SNunit *snunitPtr, char *mesg)
{
  checkErrors ++;

  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    snunitPtr->errWrtName(WEBOUT);
    WEBOUT << mesg << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    snunitPtr->errWrtName(std::cerr);
    std::cerr << mesg << std::endl;
  }
  return;
}


void SystemErrorStrA(SNunit *snunitPtr, string &str, char *mesg)
{
  checkErrors ++;
  
  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << str;
    WEBOUT << mesg << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    std::cerr << str;
    std::cerr << mesg << std::endl;
  }
  return;
}

void SystemErrorAStrA(SNunit *snunitPtr, char *m1,string &str, char *m2)
{
  checkErrors ++;
  
  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << m1;
    WEBOUT << str;
    WEBOUT << m2 << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    std::cerr << m1;
    std::cerr << str;
    std::cerr << m2 << std::endl;
  }

  return;
}

void SystemErrorAStr(SNunit *snunitPtr, char *m,string &str)
{
  checkErrors ++;

  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << m;
    WEBOUT << str;
    WEBOUT << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    std::cerr << m;
    std::cerr << str;
    std::cerr << std::endl;
  }

  return;
}

// This is with NameNO specification.
void SystemErrorNameNOA(SNunit *snunitPtr, int nameNo1,char *mesg)
{
  checkErrors ++;
  
  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    snunitPtr->errWrtNameNO(WEBOUT,nameNo1);
    WEBOUT << mesg << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    snunitPtr->errWrtNameNO(std::cerr,nameNo1);
    std::cerr << mesg << std::endl;
  }

  return;
}

void SystemErrorANameA(SNunit *snunitPtr, char *mesg1,char*mesg2)
{
  checkErrors ++;

  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << mesg1;
    snunitPtr->errWrtName(WEBOUT);
    WEBOUT << mesg2 << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    std::cerr << mesg1;
    snunitPtr->errWrtName(std::cerr);
    std::cerr << mesg2 << std::endl;
  }

  return;
}


void SystemErrorAIA(SNunit *snunitPtr, char *mesg1,int n,char*mesg2)
{
  checkErrors ++;

  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
  
    WEBOUT << mesg1;                          // A
    WEBOUT <<     n;                          // I
    WEBOUT << mesg2 << std::endl;                  // A
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
  
    std::cerr << mesg1;                          // A
    std::cerr <<     n;                          // I
    std::cerr << mesg2 << std::endl;                  // A
  }

  return;
}


void SystemErrorANameStrA(SNunit *snunitPtr, string &st,char *mesg1,char*mesg2)
{
  checkErrors ++;

  if(feelfem_web) {

    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
  
    WEBOUT << mesg1;
    snunitPtr->errWrtName(WEBOUT);
    WEBOUT << " " << st;
    WEBOUT << mesg2 << std::endl;

  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
  
    std::cerr << mesg1;
    snunitPtr->errWrtName(std::cerr);
    std::cerr << " " << st;
    std::cerr << mesg2 << std::endl;
  }

  return;
}

void SystemErrorANameAStr(SNunit *snunitPtr, string &st,char *mesg1,char*mesg2)
{
  checkErrors ++;

  if(feelfem_web) {

    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
  
    WEBOUT << mesg1;
    snunitPtr->errWrtName(WEBOUT);
    WEBOUT << mesg2;
    WEBOUT << " " << st  << std::endl;

  }
  else {

    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
  
    std::cerr << mesg1;
    snunitPtr->errWrtName(std::cerr);
    std::cerr << mesg2;
    std::cerr << " " << st  << std::endl;
  }

  return;
}


void SystemErrorANameADataA(SNunit *snunitPtr,
			    char *mesg1,char*mesg2,char *mesg3)
{
  checkErrors ++;

  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
  
    WEBOUT << mesg1;
    snunitPtr->errWrtName(WEBOUT);
    WEBOUT << mesg2;
    snunitPtr->errWrtData(WEBOUT);
    WEBOUT << mesg3 << std::endl;
  }
  else {
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
  
    std::cerr << mesg1;
    snunitPtr->errWrtName(std::cerr);
    std::cerr << mesg2;
    snunitPtr->errWrtData(std::cerr);
    std::cerr << mesg3 << std::endl;
  }

  return;
}

// Warnings
void SystemWarningA(SNunit *snunitPtr, char *mesg)
{
  checkWarnings ++;

  if(feelfem_web) {
    WEBOUT << "Warning  ";
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << mesg << std::endl;
  }
  else {
    std::cerr << "Warning  ";
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
    std::cerr << mesg << std::endl;
  }

  return;
}

void SystemWarningANameA(SNunit *snunitPtr, char *mesg1,char*mesg2)
{
  checkWarnings ++;

  if(feelfem_web) {
    WEBOUT << "Warning  ";
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
  
    WEBOUT << mesg1;
    snunitPtr->errWrtName(WEBOUT);
    WEBOUT << mesg2 << std::endl;
  }
  else {
    std::cerr << "Warning  ";
    snunitPtr->wrtSourceFilename(std::cerr);
    std::cerr << " (";
    snunitPtr->wrtLineNumber(std::cerr);
    std::cerr << "): ";
  
    std::cerr << mesg1;
    snunitPtr->errWrtName(std::cerr);
    std::cerr << mesg2 << std::endl;
  }

  return;
}

