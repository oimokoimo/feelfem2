/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Fortran90Library.cpp
 *  Date     : 2000/10/26
 *  Modified : 2000/10/26
 *  
 *  Purpose  : Frequently used source code for Fortran90
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

#include "Fortran90Generator.hpp"

void Fortran90Generator::F90_MPI_Initialize(void)
{
  // used variable name    ierr,nprocs,myrank
  
  writeSource("call MPI_INIT(ierror)");
  writeSource("call MPI_COMM_SIZE(MPI_COMM_WORLD,nprocs,ierror)");
  writeSource("call MPI_COMM_RANK(MPI_COMM_WORLD,myrank,ierror)");
  com();

  return;
}

void Fortran90Generator::F90_MPI_Finalize(void)
{
  writeSource("call MPI_FINALIZE(ierror)");
  return;
}

void Fortran90Generator::F90_MPI_Abort(void)
{
  writeSource("call mpi_abort(mpi_comm_world,-1,ierror)");
  return;
}

