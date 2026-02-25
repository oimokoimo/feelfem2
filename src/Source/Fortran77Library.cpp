/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Fortran77Library.cpp
 *  Date     : 2000/04/06
 *  Modified : 2000/04/06
 *  
 *  Purpose  : Frequently used source code for Fortran77
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

#include <cstdio>
#include "Fortran77Generator.hpp"

void Fortran77Generator::F77_MPI_Initialize(void)
{
  // used variable name    ierr,nprocs,myrank
  
  writeSource("      call mpi_init(ierr)");
  writeSource("      call mpi_comm_size(mpi_comm_world,nprocs,ierr)");
  writeSource("      call mpi_comm_rank(mpi_comm_world,myrank,ierr)");

  return;
}

void Fortran77Generator::F77_MPI_Finalize(void)
{
  writeSource("      call mpi_finalize(ierr)");
  return;
}

void Fortran77Generator::F77_MPI_Abort(void)
{
  writeSource("      call mpi_abort(mpi_comm_world,-1,ierr)");
  return;
}

