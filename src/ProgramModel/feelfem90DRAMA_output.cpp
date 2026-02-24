/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90DRAMA_output.cpp
 *  Date     : 2003/02/19 (copied from feelfem90_output.cpp)
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

#include "PM_feelfem90DRAMA.hpp"

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "GeometryObject.hpp"

#include "Variable.hpp"
#include "Output.hpp"
#include "Quadrature.hpp"

#include "../check/check_funcs.hpp"


const char *PM_feelfem90DRAMA::GetOutputRoutineName(int n)
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

void PM_feelfem90DRAMA::pushOutputRoutineName(Output *outputPtr)
{
  pushSource("output");
  pushSourceInt(outputPtr->GetOutputNo());
  return;
}

void PM_feelfem90DRAMA::DoMainScheme_output(Main *mainPtr,Output *outputPtr)
{
  pushSource("call ");
  pushOutputRoutineName(outputPtr);
  pushSource("(myrank,nprocs,meshDat,firstDramaEdatPtr,");

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

void PM_feelfem90DRAMA::DoOutputRoutineHeader (Output *outputPtr)
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
  pushSource("(myrank,nprocs,meshDat,firstDramaEdatPtr,");

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
  fortImplicit();
  com();

  writeSource("include 'mpif.h'");
  com();

  return;
}

void PM_feelfem90DRAMA::DoOutputParameters( Output *outputPtr)
{

  writeInteger4pm("iunit = 15     ! for flavia.mesh");  
  writeLogical("isopened");
  writeSource("character(len=50 )             :: fmt");
  com();

  return;
}

void PM_feelfem90DRAMA::DoOutputVariableDefinitions(Output *outputPtr)
{
  // argument definition of coordinates, and npmax

  comment();

  writeInteger4sc("myrank,nprocs");

  writeSource("type(meshInformation)          :: meshDat");
  writeSource("type (dramaEdatList),pointer   :: firstDramaEdatPtr");
  com();

  CoordinateVariableDeclaration();
  writeInteger4sc("npmax");
  com();

  // arguments
  ArgumentVariableDeclarationLst( outputPtr->GetVarPtrList() );
  com();

  // auto variables for loop counter
  writeInteger4sc("i,j,k,l");
  writeInteger4sc("nelem_c,matno_c");
  writeInteger4sc("ipt,ip_from,ip_to");
  com();

  // edatno,nelem,np
  writeInteger4sc("edatno");
  writeInteger4sc("nelem");
  writeInteger4sc("netype");
  com();

  writeInteger4Ptr2("enptr,con");
  writeInteger4Ptr1("matno");
  com();

  COMMENTlong("MPI processing");
  writeInteger4sc("np      ! P2 limit, 1 elem type only");
  writeInteger4sc("npmax_g,nelem_g");
  writeInteger4sc("ierr");
  com();

  writeInteger4Ptr1("counts,displs");
  writeInteger4Ptr1("cnt_enptr,dsp_enptr");
  writeInteger4Ptr1("cnt_con,dsp_con");
  com();

  writeReal8Ptr1("x_g,y_g,z_g");
  writeInteger4Ptr2("enptr_g");
  writeInteger4Ptr2("con_g");
  writeInteger4Ptr1("matno_g");
  com();
  writeInteger4Ptr1("ielemp     ! ielem pointer");
  writeInteger4sc  ("peno");

  com();

  pushReal8Ptr1();
  for(int i=0;i<outputPtr->HowManyComponents();i++) {
    if(i > 0) pushSource(",");
    pushSource("dat");
    pushSourceInt(i+1);
    pushSource("_g");
  }
  flushSource();
  com();

  writeInteger4sc("itime   ! for counter");
  com();

  writeSource("data itime/0/");
  writeSource("save itime");


  comment();
  com();

  return;
}

void PM_feelfem90DRAMA::DoOutputMeshData(Output *outputPtr)
{
  writeSource("edatno = meshDat%medtNo     ! Main EDAT No."); //main edat no
  writeSource("call setdramaedat(edatno,firstDramaEdatPtr,           &");
  writeSource("                         nelem,enptr,con,matno,netype  )");

  COMMENTlong("Gather data");
  com();
  writeSource("! for nodes");
  com();
  writeSource("if(myrank .eq. 0) then");
  writeSource("  allocate(displs(nprocs),counts(nprocs))");
  writeSource("end if");
  com();

  writeSource("call MPI_GATHER(npmax, 1,MPI_INTEGER,                     &");
  writeSource("                counts,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)");
  com();

  writeSource("if(myrank .eq. 0) then");
  com();

  writeSource("  displs(1) = 0");
  writeSource("  npmax_g   = counts(1)");
  writeSource("  do i=2,nprocs");
  writeSource("   displs(i)=displs(i-1)+counts(i-1)");
  writeSource("   npmax_g  =counts(i)");
  writeSource("  end do");
  com();

  switch(getSpaceDimension()){
  case 1:
    writeSource("  allocate(x_g(npmax_g))");
    break;

  case 2:
    writeSource("  allocate(x_g(npmax_g))");
    writeSource("  allocate(y_g(npmax_g))");
    break;

  case 3:
    writeSource("  allocate(x_g(npmax_g))");
    writeSource("  allocate(y_g(npmax_g))");
    writeSource("  allocate(z_g(npmax_g))");
    break;

  default:
    assert(1==0);
  }
  com();

  writeSource("end if   !PE(0)");
  com();

  switch(getSpaceDimension()){
  case 1:
    writeSource("call MPI_GATHERV(x  ,npmax,        MPI_DOUBLE_PRECISION, &");
    writeSource("                 x_g,counts,displs,MPI_DOUBLE_PRECISION, &");
    writeSource("                 0,MPI_COMM_WORLD,ierr)");
    break;

  case 2:
    writeSource("call MPI_GATHERV(x  ,npmax,        MPI_DOUBLE_PRECISION, &");
    writeSource("                 x_g,counts,displs,MPI_DOUBLE_PRECISION, &");
    writeSource("                 0,MPI_COMM_WORLD,ierr)");
    com();

    writeSource("call MPI_GATHERV(y  ,npmax,        MPI_DOUBLE_PRECISION, &");
    writeSource("                 y_g,counts,displs,MPI_DOUBLE_PRECISION, &");
    writeSource("                 0,MPI_COMM_WORLD,ierr)");

    break;

  case 3:
    writeSource("call MPI_GATHERV(x  ,npmax,        MPI_DOUBLE_PRECISION, &");
    writeSource("                 x_g,counts,displs,MPI_DOUBLE_PRECISION, &");
    writeSource("                 MPI_COMM_WORLD,ierr)");
    com();

    writeSource("call MPI_GATHERV(y  ,npmax,        MPI_DOUBLE_PRECISION, &");
    writeSource("                 y_g,counts,displs,MPI_DOUBLE_PRECISION, &");
    writeSource("                 MPI_COMM_WORLD,ierr)");
    com();

    writeSource("call MPI_GATHERV(z  ,npmax,        MPI_DOUBLE_PRECISION, &");
    writeSource("                 z_g,counts,displs,MPI_DOUBLE_PRECISION, &");
    writeSource("                 MPI_COMM_WORLD,ierr)");

    break;

  default:
    assert(1==0);
  }
  com();


  writeSource("!-------------");
  writeSource("! for elements");
  writeSource("!-------------");
  com();

  writeSource("if(myrank .eq. 0) then ");
  writeSource("  allocate(cnt_enptr(nprocs),dsp_enptr(nprocs))");
  writeSource("  allocate(cnt_con(nprocs)  ,dsp_con(nprocs))");
  writeSource("end if");
  com();

  writeSource("call MPI_GATHER(nelem  ,1,MPI_INTEGER,                     &");
  writeSource("                cnt_con,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)");
  com();

  writeSource("if(myrank .eq. 0) then ");


  writeSource("  dsp_con(1) = 0");
  writeSource("  nelem_g      = cnt_con(1)");
  writeSource("  do i=2,nprocs");
  writeSource("    dsp_con(i)=dsp_con(i-1)+cnt_con(i-1)");
  writeSource("    nelem_g  =nelem_g + cnt_con(i)");
  writeSource("  end do");
  com();
  
  writeSource("  allocate(matno_g(nelem_g))");
  com();
  writeSource("end if");

  com();
  writeSource("call MPI_GATHERV(matno,nelem,MPI_INTEGER,                 &");
  writeSource("                 matno_g,cnt_con,dsp_con,MPI_INTEGER,     &");
  writeSource("                 0,MPI_COMM_WORLD,ierr                     )");
  com();


  writeSource("if(myrank.eq.0) then");
  com();
  writeSource("  do i=1,nprocs");
  writeSource("    cnt_enptr(i)=cnt_con(i)+1    ! enptr(nelem+1,2)");
  writeSource("  end do");


  com();
  writeSource("  dsp_enptr(1) = 0");
  writeSource("  do i=2,nprocs");
  writeSource("    dsp_enptr(i)=dsp_enptr(i-1)+cnt_enptr(i-1)");
  writeSource("  end do");
  com();


  writeSource("! P2 limit, only one type of element");
  writeSource("  np = enptr(2,1)-enptr(1,1) + 1");
  writeSource("  allocate(ielemp(np))");
  com();

  writeSource("! as enptr(:,2),con(:,2)");
  writeSource("  do i=1,nprocs");
  com();
  writeSource("    cnt_con(i)=cnt_con(i)*2*np");
  writeSource("    dsp_con(i)=dsp_con(i)*2*np");
  com();
  writeSource("    cnt_enptr(i)=cnt_enptr(i)*2");
  writeSource("    dsp_enptr(i)=dsp_enptr(i)*2");
  com();
  writeSource("  end do");
  com();

  //allocate enptr new
  writeSource("  allocate(enptr_g(nelem_g+nprocs ,2))");
  writeSource("  allocate(con_g  (np * nelem_g   ,2))");
  com();

  writeSource("end if  ! if(PE0)");
  com();
  
  writeSource("call MPI_GATHERV(enptr  ,(nelem+1)*2        ,MPI_INTEGER,  &");
  writeSource("                 enptr_g,cnt_enptr,dsp_enptr,MPI_INTEGER,  &");
  writeSource("                 0,MPI_COMM_WORLD,ierr                      )");
  com();

  writeSource("call MPI_GATHERV(con  ,nelem*2*np       ,MPI_INTEGER,  &");
  writeSource("                 con_g,cnt_con,dsp_con  ,MPI_INTEGER,  &");
  writeSource("                 0,MPI_COMM_WORLD,ierr                      )");
  com();


  writeSource("if(myrank .eq. 0) then ");
  writeSource(" inquire(unit=iunit,opened=isopened)");
  writeSource(" if( .NOT. isopened ) then");
  com();
  writeSource("!   if iunit is not opened yet, it means this is first time.");
  writeSource("!   as PROBLEMNAME.flavia.res  is not closed and uses same ");
  writeSource("!   Unit no.");
  com();



  // Open statement
  pushSource("    open(unit=iunit,file='");
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
  writeSource("   do i=1,npmax_g");
  writeSource("     write(iunit,102) i,x_g(i),y_g(i)");
  writeSource("102  format(i8,1x,e15.6,1x,e15.6)");
  writeSource("   end do");
  com();

  writeSource("  else");
  com();

  writeSource("   do i=1,npmax_g");

  switch(getSpaceDimension()){
  case 1:
    writeSource("     write(iunit,103) i,x_g(i)");
    writeSource("103  format(i8,1x,e15.6)");
    writeSource("   end do");
    break;

  case 2:
    writeSource("     write(iunit,103) i,x_g(i),y_g(i)");
    writeSource("103  format(i8,1x,e15.6,1x,e15.6)");
    writeSource("   end do");
    break;

  case 3:
    writeSource("     write(iunit,103) i,x_g(i),y_g(i),z_g(i)");
    writeSource("103  format(i8,1x,e15.6,1x,e15.6,1x,e15.6)");
    writeSource("   end do");
    break;
  }
  com();

  writeSource("  endif");
  com();

  writeSource("  write(iunit,*)'end coordinates'");
  com();

  // end of writing coordinates

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
  writeSource("  do i=1,nprocs");

  com();

  writeSource("   nelem_c = cnt_con(i)/2/np  ! ith PE's elements");
  writeSource("   do j=1,nelem_c");
  com();

  writeSource("    ip_from=enptr_g(dsp_enptr(i)+j  ,1)");
  writeSource("    ip_to  =enptr_g(dsp_enptr(i)+j+1,1)-1");
  com();

  writeSource("    ip_from=ip_from+dsp_con(i)/2");
  writeSource("    ip_to  =ip_to  +dsp_con(i)/2");
  com();

  writeSource("    ipt = 1");
  writeSource("    do k=ip_from,ip_to");
  writeSource("      ielemp(ipt) = con_g(k,1)+displs(con_g(k,2)+1)");
  writeSource("      ipt= ipt + 1");
  writeSource("    end do");
  com();
  
  writeSource("    matno_c = matno_g(dsp_con(i)/2+j)");


  writeSource("    write(iunit,fmt) i,(ielemp(l),l=1,np),matno_c");
  com();
  writeSource("   end do ! nelem_c");
  com();
  writeSource("  end do ! end nprocs");
  com();
  writeSource("  write(iunit,*)'end elements'");
  com();

  writeSource("  close(unit=iunit)");
  com();

  writeSource(" end if  ! if already opened and coordinate was written.");
  com();

  writeSource("end if  !PE 0");
  com();

  com();
  com();

  return;
}

void PM_feelfem90DRAMA::DoOutputStatement(Output *outputPtr)
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

void PM_feelfem90DRAMA::DoOutputReturnSequence(Output *outputPtr)
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
//void PM_feelfem90DRAMA::doOutputScalar(Output *outputPtr)
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
//void PM_feelfem90DRAMA::doOutputFEMnode(Output *outputPtr)
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
//void PM_feelfem90DRAMA::doOutputEWISEmaterial(Output *outputPtr)
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
