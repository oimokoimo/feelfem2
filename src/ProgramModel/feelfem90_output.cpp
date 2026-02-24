/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90_output.cpp
 *  Date     : 2002/07/17
 *  Modified : 
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

#include <cassert>

#include "PM_feelfem90.hpp"

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "GeometryObject.hpp"

#include "Variable.hpp"
#include "Output.hpp"
#include "Quadrature.hpp"

#include "../check/check_funcs.hpp"


const char *PM_feelfem90::GetOutputRoutineName(int n)
{
  assert(n>0);
  int len = stringLength("output");
  if(n < 10) {
    len++;
  }
  else if(n < 100) {
    len+= 2;
  }
  else if(n < 1000) {
    len+= 3;
  }
  else {
	  std::cerr << "too many assigns\n";
    assert(1==0);
  }
  
  len++;   // for '\0'

  char *ret = new char[len];
  sprintf(ret,"output%d%c",n,'\0');

  return(ret);
}

void PM_feelfem90::pushOutputRoutineName(Output *outputPtr)
{
  pushSource("output");
  pushSourceInt(outputPtr->GetOutputNo());
  return;
}

void PM_feelfem90::DoMainScheme_output(Main *mainPtr,Output *outputPtr)
{
  pushSource("call ");
  pushOutputRoutineName(outputPtr);
  pushSource("(meshDat,firstEdatPtr,");

  pushCoordinateSource();
  pushSource(",npmax");

  // geometry information
  pushVariableListInMain(outputPtr->GetVarPtrList());
  pushSource(")");
  flushSource();
  com();

  return;
}

/////////////////////////////////////////////////////////////////

void PM_feelfem90::DoOutputRoutineHeader (Output *outputPtr)
{
  // module sentence
  pushSource("module mod_");
  pushOutputRoutineName(outputPtr);
  flushSource();

  // contains
  writeSource("contains");
  
  // subroutine sentence
  pushSource("subroutine ");
  pushOutputRoutineName(outputPtr);
  pushSource("(meshDat,firstEdatPtr,");

  // coordinates are always sent.
  pushCoordinateSource();
  pushSource(",npmax");

  // variables
  pushVariableListInCalled(outputPtr->GetVarPtrList());
  pushSource(")");
  flushSource();
 
  //use
  SourceStarters();
  com();

  F90useAlways();
  
  // fem data type
  F90useFEMDataType();
  com();

  // implicit none
  com();
  fortImplicit();

  return;
}

void PM_feelfem90::DoOutputParameters( Output *outputPtr)
{

  writeInteger4pm("iunit = 15     ! for flavia.mesh");  
  writeLogical("isopened");
  writeSource("character(len=50 )             :: fmt");
  com();

  return;
}

void PM_feelfem90::DoOutputVariableDefinitions(Output *outputPtr)
{
  // argument definition of coordinates, and npmax

  comment();

  writeSource("type(meshInformation)          :: meshDat");
  writeSource("type(edatList),pointer         :: firstEdatPtr");
  com();

  CoordinateVariableDeclaration();
  writeInteger4sc("npmax");
  com();

  // arguments
  ArgumentVariableDeclarationLst( outputPtr->GetVarPtrList() );
  com();

  // auto variables for loop counter
  writeInteger4sc("i,j");
  com();

  // edatno,nelem,np
  writeInteger4sc("edatno");
  writeInteger4sc("nelem,np,netype");
  com();

  writeInteger4Ptr2("ielem");
  writeInteger4Ptr1("matno");
  com();

  writeInteger4sc("itime   ! for counter");
  com();

  writeSource("data itime/0/");
  writeSource("save itime");


  comment();
  com();

  return;
}

void PM_feelfem90::DoOutputMeshData(Output *outputPtr)
{
  writeSource("edatno = meshDat%medtNo     ! Main EDAT No."); //main edat no
  writeSource("call setP2edat(edatno,firstEdatPtr,nelem,np,netype,ielem,matno)");
  com();
  writeSource("inquire(unit=iunit,opened=isopened)");
  writeSource("if( .NOT. isopened ) then");
  com();
  writeSource("! if iunit is not opened yet, it means this is first time.");
  writeSource("! as PROBLEMNAME.flavia.res  is not closed and uses same ");
  writeSource("! Unit no.");
  com();



  // Open statement
  pushSource("  open(unit=iunit,file='");
  pushSource(feelfemgeomobj.GetProblemName());
  pushSource(".flavia.msh')");
  flushSource();
  com();
  
  writeSource("  select case (netype)");
  com();


  // triangle  
  pushSource("  case ("); 
  pushSourceInt(ELEMENT_TYPE_TRI);
  pushSource(")"); 
  flushSource();
  writeSource("    write(iunit,101) 2,'Triangle   ',np");
  com();

  // rectangle
  pushSource("  case ("); 
  pushSourceInt(ELEMENT_TYPE_RECT);
  pushSource(")"); 
  flushSource();
  writeSource("    write(iunit,101) 2,'Rectangle  ',np");
  com();

  // tetrahedra
  pushSource("  case ("); 
  pushSourceInt(ELEMENT_TYPE_TETRA);
  pushSource(")"); 
  flushSource();
  writeSource("    write(iunit,101) 3,'Tetrahedra ',np");
  com();

  // hexagon
  pushSource("  case ("); 
  pushSourceInt(ELEMENT_TYPE_CUBE);
  pushSource(")"); 
  flushSource();
  writeSource("    write(iunit,101) 3,'Hexahedra  ',np");
  com();  

  writeSource("  end select");
  com();

  pushSource("101 format('MESH \"");
  pushSource(feelfemgeomobj.GetProblemName());
  pushSource("\" dimension ',i1,' ElemType ',a11,' Nnode ',i3)");
  flushSource();
  com();

  writeSource("  write(iunit,*) 'coordinates'");
  
  writeSource("  if( netype == 3 .OR. netype == 4) then");
  com();
  writeSource("  do i=1,npmax");
  writeSource("    write(iunit,102) i,x(i),y(i)");
  writeSource("102 format(i8,1x,e15.6,1x,e15.6)");
  writeSource("  end do");
  com();

  writeSource("  else");
  com();

  writeSource("  do i=1,npmax");

  switch(getSpaceDimension()){
  case 1:
    writeSource("    write(iunit,103) i,x(i)");
    writeSource("103 format(i8,1x,e15.6)");
    writeSource("  end do");
    break;

  case 2:
    writeSource("    write(iunit,103) i,x(i),y(i)");
    writeSource("103 format(i8,1x,e15.6,1x,e15.6)");
    writeSource("  end do");
    break;

  case 3:
    writeSource("    write(iunit,103) i,x(i),y(i),z(i)");
    writeSource("103 format(i8,1x,e15.6,1x,e15.6,1x,e15.6)");
    writeSource("  end do");
    break;
  }
  com();

  writeSource("  endif");
  com();

  writeSource("  write(iunit,*)'end coordinates'");
  com();

  // Make element format sentence
  writeSource("! make format");
  writeSource("  if(np < 10) then");
  writeSource("    write(fmt,801) np");
  writeSource("801 format('(i8,',i1,'i8,i8)')");
  writeSource("  else if( np < 100) then");
  writeSource("    write(fmt,802) np");
  writeSource("802 format('(i8,',i2,'i8,i8)')");
  writeSource("  else");
  writeSource("    stop 'too many nodes in one element'");
  writeSource("  end if");
  com();

  writeSource("  write(iunit,*)'elements'");
  writeSource("  do i=1,nelem");
  writeSource("    write(iunit,fmt) i,(ielem(j,i),j=1,np),matno(i)");
  writeSource("  end do");
  writeSource("  write(iunit,*)'end elements'");
  com();

  writeSource("  close(unit=iunit)");
  com();

  writeSource("end if");
  com();
  com();

  return;
}

void PM_feelfem90::DoOutputStatement(Output *outputPtr)
{
  COMMENTlong("Data write");
  com();

  writeSource("inquire(unit=iunit,opened=isopened)");
  writeSource("if( .NOT. isopened ) then");


  com();
  pushSource("  open(unit=iunit,file='");
  pushSource(feelfemgeomobj.GetProblemName());
  pushSource(".flavia.res')");
  flushSource();
  com();

  // Header
  writeSource("  write(iunit,'(a25)') 'GiD Post Results File 1.0'");
  writeSource("  write(iunit,*)");
  writeSource("  write(iunit,*)");
  
  writeSource("end if");
  com();
  com();

  writeSource("itime = itime + 1");
  com();
  
  listIterator <string>itr(outputPtr->GetOutputIdentifierList());

  // If quadrature,,,,
  if(outputPtr->GetQuadraturePtr() != 0) {
    Quadrature *quadPtr = outputPtr->GetQuadraturePtr();
 
    writeSource("if(itime == 1) then");
    com();
   
    COMMENTlong("GaussPoint information");

    // Line 1
    pushSource(" write(iunit,*) 'GaussPoints \"");
    pushSource(quadPtr->GetName());
    pushSource("\" ElemType ");
    
    switch(quadPtr->GetEtype()) {
    case ELEMENT_TYPE_TRI:
      pushSource("Triangle");
      break;
      
    case ELEMENT_TYPE_RECT:
      pushSource("Quadrilateral");
      break;

    case ELEMENT_TYPE_TETRA:
      pushSource("Tetrahedra");
      break;
      
    case ELEMENT_TYPE_CUBE:
      pushSource("Hexahedra");
      break;
      
    default:
      assert(1==0);
    }
    
    pushSource(" \"");
    pushSource(feelfemgeomobj.GetProblemName());
    pushSource("\"'");
    flushSource();
    
    // Line 2 (Number of Gauss Points: 
    pushSource(" write(iunit,*) 'Number of Gauss Points: ");
    pushSourceInt(quadPtr->GetQuadraturePoints());
    pushSource("'");
    flushSource();

    // Line 3
    //    writeSource(" write(iunit,*) 'Nodes not included'");
    

    // Line 4
    writeSource(" write(iunit,*) 'Natural Coordinates: Given'");


    for(int i=0;i<quadPtr->GetQuadraturePoints();i++) {
      
      if(quadPtr->GetDimension() == 2) {

	pushSource(" write(iunit,'(2f15.8)') ");
	pushSourceDbl( quadPtr->GetIthXi(i) );
	pushSource(",");
	pushSourceDbl( quadPtr->GetIthEta(i) );
	flushSource();

      }
      else {

	pushSource(" write(iunit,'(3f15.8)') ");
	pushSourceDbl( quadPtr->GetIthXi(i) );
	pushSource(",");
	pushSourceDbl( quadPtr->GetIthEta(i) );
	pushSource(",");
	pushSourceDbl( quadPtr->GetIthZeta(i) );
	flushSource();
      }
    }
    writeSource(" write(iunit,*) 'End GaussPoints'");
    writeSource(" write(iunit,*)");
    com();
    writeSource("end if");
    com();



    // Result Header for EWISE-QUAD
    if(outputPtr->HowManyComponents() > 1) {
      writeSource("write(iunit,201) itime,'Vector'");
    }
    else {
      writeSource("write(iunit,201) itime,'Scalar'");
    }


    pushSource("201 format('Result \"");

    // option  label
    if(outputPtr->HasOption("label")) {
      string val;
      outputPtr->GetOption("label",val);
      pushSource(val);
    }
    else {
      pushSource("output");
      pushSourceInt(outputPtr->GetOutputNo());
    }


    pushSource("\" \"");
    pushSource(feelfemgeomobj.GetProblemName());
    pushSource("\"',i5,1x,a6,' OnGaussPoints \"");
    pushSource(quadPtr->GetName());
    pushSource("\"')");
    flushSource();
    com();

    writeSource("write(iunit,*) 'Values'");
    com();
    
    writeSource("do i=1,nelem");
    com();

    // 1st line with node number
    pushSource("write(iunit,301) i");
    
    // scalar or ewise variable
    for(itr.init(); !itr ; ++itr) {
      string name = itr();
      if(isDefinedScalarVariable( name ) ) {
	pushSource(",sc_");
	pushSource(itr());
      }
      else {
	pushSource(",ew_");
	pushSource(name);
	pushSource("(");
	pushSource("1,i)");
      }
    }
    flushSource();   // end of 1st line
    
    for(int i=1;i<quadPtr->GetQuadraturePoints(); i++) {
      pushSource("write(iunit,302)  ");
    
      // scalar or ewise variable
      for(itr.init(); !itr ; ++itr) {
	string name = itr();
	if(isDefinedScalarVariable( name ) ) {
	  pushSource(" sc_");
	  pushSource(name);
	}
	else {
	  pushSource(" ew_");
	  pushSource(name);
	  pushSource("(");
	  pushSourceInt(i+1);     // i+1
	  pushSource(",i)");
	}
      }
      flushSource();
    }

    pushSource("301 format(i8,");
    pushSourceInt(outputPtr->HowManyComponents());
    pushSource("e15.7)");
    flushSource();

    pushSource("302 format(8x,");
    pushSourceInt(outputPtr->HowManyComponents());
    pushSource("e15.7)");
    flushSource();
    com();

    writeSource("end do");
    com();

    writeSource("write(iunit,*) 'End Values'");
    com();
    com();

  }  // end of quadrature case


  else {  // FEM variable

    // Result Header for EWISE-QUAD
    if(outputPtr->HowManyComponents() > 1) {
      writeSource("write(iunit,401) itime,'Vector'");
    }
    else {
      writeSource("write(iunit,401) itime,'Scalar'");
    }


    pushSource("401 format('Result \"");

    // option  label
    if(outputPtr->HasOption("label")) {
      string val;
      outputPtr->GetOption("label",val);
      pushSource(val);
    }
    else {
      pushSource("output");
      pushSourceInt(outputPtr->GetOutputNo());
    }

    pushSource("\" \"");
    pushSource(feelfemgeomobj.GetProblemName());
    pushSource("\"',i5,1x,a6,' OnNodes')");
    flushSource();
    com();

    writeSource("write(iunit,*) 'Values'");    
    com();


    writeSource("do i=1,npmax");
    com();

    // 1st line with node number
    pushSource("write(iunit,501) i");
    
    // scalar or ewise variable
    for(itr.init(); !itr ; ++itr) {
      string name = itr();
      if(isDefinedScalarVariable( name ) ) {
	pushSource(",sc_");
	pushSource(itr());
      }
      else {
	if(isCoordinate(name)) {
	  pushSource(",");
	  pushSource(name);
	  pushSource("(i)");
	}
	else {
	  pushSource(",fem_");
	  pushSource(name);
	  pushSource("(i)");
	}
      }
    }
    flushSource();   // end of 1st line
    

    pushSource("501 format(i8,");
    pushSourceInt(outputPtr->HowManyComponents());
    pushSource("e15.7)");
    flushSource();
    com();

    writeSource("end do");
    com();

    writeSource("write(iunit,*) 'End Values'");
    com();
    com();

  }  // end of scalar


  return;
}

void PM_feelfem90::DoOutputReturnSequence(Output *outputPtr)
{
  writeSource("return");
  com();
  
  pushSource("end subroutine ");
  pushOutputRoutineName(outputPtr);
  flushSource();

  pushSource("end module mod_");
  pushOutputRoutineName(outputPtr);
  flushSource();

  return;
}


// GiD
//void PM_feelfem90::doOutputScalar(Output *outputPtr)
//{
//  pushSource("  ");
//  pushVariableInCalled(outputPtr->GetLeftVarPtr());
//  pushSource("=");
//
//  TermConvert tc;
//
//  // x     ->  x(nd)  , etc
//  // fem_u ->  fem_u(nd)
//  // no ewise variable allowed here
//
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "x", "x(nd)");
//  }
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "y", "y(nd)");
//  }
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "z", "z(nd)");
//  }
//
//
//  listIterator <Variable *>itrV(outputPtr->GetVarPtrList());
//  for(itrV.init(); !itrV ; ++itrV) {
//
//    char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
//    char bto  [VARIABLE_TERMCONVERT_BUFSIZ];
//
//    switch(itrV()->GetType()) {
//    case VAR_INT:
//    case VAR_DOUBLE:
//    case VAR_CONST:
//      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
//      sprintf(bto  ,"sc_%s%c",itrV()->GetName(),'\0');      
//      tc.storeConvertPair( bfrom, bto );
//      break;
//
//    case VAR_EWISE:
//    case VAR_EWISE_A:
//      cerr << "ewise variable must not be appeared here.\n";
//      assert(1==0);  
//
//    case VAR_FEM:
//      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
//      sprintf(bto  ,"fem_%s(nd)%c",itrV()->GetName(),'\0');      
//      tc.storeConvertPair( bfrom, bto );
//      break;
//
//    case VAR_VFEM:
//      cerr << "Not implemented...???\n";
//      assert(1==0);
//    }
//  }
//  
//  string exprF90Str = tc.convertExpressionString(outputPtr->GetExprString());
//  
//  pushSource( exprF90Str );
//  
//  flushSource();
//  com();
//
//  return;
//}
//
//void PM_feelfem90::doOutputFEMnode(Output *outputPtr)
//{
//  // do loop
//  writeSource("do i=1,npmax");
//  com();
//
//  pushSource("  ");
//  pushVariableInCalled(outputPtr->GetLeftVarPtr());
//  pushSource("(i)=");
//
//  TermConvert tc;
//
//  // x     ->  x(nd)  , etc
//  // fem_u ->  fem_u(nd)
//  // no ewise variable allowed here
//
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "x", "x(i)");
//  }
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "y", "y(i)");
//  }
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "z", "z(i)");
//  }
//
//
//  listIterator <Variable *>itrV(outputPtr->GetVarPtrList());
//  for(itrV.init(); !itrV ; ++itrV) {
//
//    char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
//    char bto  [VARIABLE_TERMCONVERT_BUFSIZ];
//
//    switch(itrV()->GetType()) {
//    case VAR_INT:
//    case VAR_DOUBLE:
//    case VAR_CONST:
//      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
//      sprintf(bto  ,"sc_%s%c",itrV()->GetName(),'\0');      
//      tc.storeConvertPair( bfrom, bto );
//      break;
//
//    case VAR_EWISE:
//    case VAR_EWISE_A:
//      cerr << "ewise variable must not be appeared here.\n";
//      assert(1==0);  
//
//    case VAR_FEM:
//      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
//      sprintf(bto  ,"fem_%s(i)%c",itrV()->GetName(),'\0');      
//      tc.storeConvertPair( bfrom, bto );
//      break;
//
//    case VAR_VFEM:
//      cerr << "Not implemented...???\n";
//      assert(1==0);
//    }
//  }
//  
//  string exprF90Str = tc.convertExpressionString(outputPtr->GetExprString());
//  
//  pushSource( exprF90Str );
//  flushSource();
//  com();
//
//  writeSource("end do");
//
//  return;
//}
//
//void PM_feelfem90::doOutputEWISEmaterial(Output *outputPtr)
//{
//  // do loop
//
//  //EDAT1
//  writeSource("call setP2edat(1,firstEdatPtr,nelem,np,netype,ielem,matno)");
//  com();
//
//
//  TermConvert tc;
//
//  // x     ->  ex
//  // fem_u ->  fe m_u(nd)
//  // only material ewise allowed.
//
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "x", "ex");
//  }
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "y", "ey");
//  }
//  if(outputPtr->IsUseX()) {
//    tc.storeConvertPair( "z", "ez");
//  }
//
//  listIterator <Variable *>itrV(outputPtr->GetVarPtrList());
//  for(itrV.init(); !itrV ; ++itrV) {
//
//    char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
//    char bto  [VARIABLE_TERMCONVERT_BUFSIZ];
//
//    switch(itrV()->GetType()) {
//    case VAR_INT:
//    case VAR_DOUBLE:
//    case VAR_CONST:
//      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
//      sprintf(bto  ,"sc_%s%c",itrV()->GetName(),'\0');      
//      tc.storeConvertPair( bfrom, bto );
//      break;
//
//    case VAR_EWISE:
//      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
//      sprintf(bto  ,"ew_%s(i)%c",itrV()->GetName(),'\0');      
//      tc.storeConvertPair( bfrom, bto );      
//      break;
//
//    case VAR_EWISE_A:
//      cerr << "ewise variable must not be appeared here.\n";
//      assert(1==0);  
//
//    case VAR_FEM:
//      cerr << "fem var in ewise-material is UC.\n";
//      assert(1==0);
//
//      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
//      sprintf(bto  ,"fem_%s(i)%c",itrV()->GetName(),'\0');      
//      tc.storeConvertPair( bfrom, bto );
//      break;
//
//    case VAR_VFEM:
//      cerr << "Not implemented...???\n";
//      assert(1==0);
//    }
//  }
//  // Right hand side formula
//  string exprF90Str = tc.convertExpressionString(outputPtr->GetExprString());
//
//  // Geometry is specified,
//  int matGeoms = outputPtr->GetNumberOfPlaces();
//
//  // check program for materials are assigned are not.
//  if(matGeoms > 0) {
//
//    listIterator <GeomObj *> itrRGeom(outputPtr->GetGeomObjPtrList());
//    for(itrRGeom.init();!itrRGeom;++itrRGeom) {
//
//      RegionObject *robjPtr = (RegionObject *)itrRGeom();
//
//      // if corresponding no is -1
//      pushSource("if(matData%regmat(");
//      pushSourceInt(robjPtr->GetPropertyNo());
//      pushSource(") == -1) then");
//      flushSource();
//
//      // write warting
//      pushSource("  write(*,*) 'Warning: Material [");
//      pushSource(robjPtr->GetName());
//      pushSource("] is not assigned.'");
//      flushSource();
//
//      // endif
//      writeSource("end if");
//      com();
//      com();
//    }
//  }
//
//  // Element loop starts here
//  writeSource("do i=1,nelem");
//  com();
//
//  if(matGeoms > 0) {
//    
//    listIterator <GeomObj *> itrRGeom(outputPtr->GetGeomObjPtrList());
//    for(itrRGeom.init();!itrRGeom;++itrRGeom) {
//      RegionObject *robjPtr = (RegionObject *)itrRGeom();
//      pushSource("  if(matno(i) == ");
//
//      pushSource("matData%regmat(");
//      pushSourceInt(robjPtr->GetPropertyNo());    // matData%regmat(*) is crsp
//      pushSource(")");
//
//      pushSource(" ) then          ! Region ");
//      pushSource(robjPtr->GetName());
//      flushSource();
//
//      // assignment
//      pushSource("   ");
//      pushVariableInCalled(outputPtr->GetLeftVarPtr());
//      pushSource("(i)=");
//      pushSource( exprF90Str );
//      flushSource();
//      
//      // endif
//      writeSource("  endif");
//      com();
//    }
//  }
//  else {
//
//    pushSource("  ");
//    pushVariableInCalled(outputPtr->GetLeftVarPtr());
//    pushSource("(i)=");
//  
//    pushSource( exprF90Str );
//    flushSource();
//    com();
//  }
//
//  writeSource("end do");
//  com();
//
//  return;
//}
//                      
