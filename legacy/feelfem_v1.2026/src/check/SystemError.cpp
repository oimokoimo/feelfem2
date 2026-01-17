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
 */

#include <iostream.h>
#include <stream.h>

#include "feelfem.hpp"                       // for feelfem_web parameter
#include "../parser/Syntax/SNunit.hpp"
#include "string.hpp"

static int checkErrors = 0;
static int checkWarnings = 0;

#define  WEBOUT      cout

void SystemError_A(char *mesg)
{
  checkErrors ++;

  if(feelfem_web) {
    WEBOUT << "feelfem Error : ";
    WEBOUT << mesg << endl;
  }
  else {
    cerr << "feelfem Error : ";
    cerr << mesg << endl;
  }

  return;
}


void SystemErrorA(SNunit *snunitPtr, char *mesg)
{
  checkErrors ++;

  if(feelfem_web) {
    snunitPtr->wrtSourceFilename(WEBOUT);
    WEBOUT << " (";
    snunitPtr->wrtLineNumber(WEBOUT);
    WEBOUT << "): ";
    WEBOUT << mesg << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    cerr << mesg << endl;
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
    WEBOUT << mesg1 << mesg2  << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    cerr << mesg1 << mesg2  << endl;
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
    WEBOUT << m1 << m2 << m3 << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    cerr << m1 << m2 << m3 << endl;
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
    WEBOUT << mesg << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    snunitPtr->errWrtName(cerr);
    cerr << mesg << endl;
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
    WEBOUT << mesg << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    cerr << str;
    cerr << mesg << endl;
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
    WEBOUT << m2 << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    cerr << m1;
    cerr << str;
    cerr << m2 << endl;
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
    WEBOUT << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    cerr << m;
    cerr << str;
    cerr << endl;
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
    WEBOUT << mesg << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    snunitPtr->errWrtNameNO(cerr,nameNo1);
    cerr << mesg << endl;
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
    WEBOUT << mesg2 << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    cerr << mesg1;
    snunitPtr->errWrtName(cerr);
    cerr << mesg2 << endl;
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
    WEBOUT << mesg2 << endl;                  // A
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
  
    cerr << mesg1;                          // A
    cerr <<     n;                          // I
    cerr << mesg2 << endl;                  // A
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
    WEBOUT << mesg2 << endl;

  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
  
    cerr << mesg1;
    snunitPtr->errWrtName(cerr);
    cerr << " " << st;
    cerr << mesg2 << endl;
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
    WEBOUT << " " << st  << endl;

  }
  else {

    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
  
    cerr << mesg1;
    snunitPtr->errWrtName(cerr);
    cerr << mesg2;
    cerr << " " << st  << endl;
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
    WEBOUT << mesg3 << endl;
  }
  else {
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
  
    cerr << mesg1;
    snunitPtr->errWrtName(cerr);
    cerr << mesg2;
    snunitPtr->errWrtData(cerr);
    cerr << mesg3 << endl;
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
    WEBOUT << mesg << endl;
  }
  else {
    cerr << "Warning  ";
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
    cerr << mesg << endl;
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
    WEBOUT << mesg2 << endl;
  }
  else {
    cerr << "Warning  ";
    snunitPtr->wrtSourceFilename(cerr);
    cerr << " (";
    snunitPtr->wrtLineNumber(cerr);
    cerr << "): ";
  
    cerr << mesg1;
    snunitPtr->errWrtName(cerr);
    cerr << mesg2 << endl;
  }

  return;
}

