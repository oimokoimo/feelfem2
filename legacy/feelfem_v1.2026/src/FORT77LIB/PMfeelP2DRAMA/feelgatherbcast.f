      subroutine feelgathervbcast(myrank,nprocs,feel,
     $                            mycount,mybuf ,
     $                            np_ibuf,np_counts,np_displs )
*-------------------------------------------------------------------
* 2000/05/30 (feelfem_stokes version)
*
* Gatherv and Bcast  (For INTEGER*4 and REAL*4 only)
* NOTICE :Allocate np_ibuf,np_counts,np_displs HERE
* 
* PURPOSE: Gather data from each processor to PE0, and then, 
*          put them to all processors again
*
* INPUT  : myrank     My PE number
*          nprocs     Total number of processors
*          feel       work array
*          mycount    number of words in my PE region / 0 is possible
*          mybuf(*)   data buffer
*
* OUTPUT : np_ibuf    Buffer:Total data buffer
*          np_counts  Buffer:Number of elements for each PE data
*          np_displs  Buffer:Number of displacement for each PE data
*-------------------------------------------------------------------
      include 'mpif.h'
*
      real*4    feel(*)
      integer*4 mybuf(*)
*-------------------------------------------------------------------
      if(myrank.eq.0) call preportsilent
*---
      if(mycount .lt. 0) call abortexit(myrank,'mycount<0 in fgvb')
*---
      call f_alloc(np_counts,'counts in feelgathervbcast',nprocs,0,0)
      call f_alloc(np_displs,'counts in feelgathervbcast',nprocs,0,0)
*
      call mpi_gather(mycount,         1, MPI_INTEGER,
     $                feel(np_counts), 1, MPI_INTEGER, 0, 
     $                                    mpi_comm_world,ierr)
*-------^
* In this point, only PE0 has appropriate values in feel(np_count)
*-------
      if(myrank .eq. 0) call preportsilent
*-------------------------------------------------------------------
      if(myrank.eq.0) then
         idisp = 0
         do 100 i=1,nprocs
            call feelset_npi(feel,np_displs,i,idisp)
            idisp = idisp + inp_feelget(feel,np_counts,i)
 100     continue
*
         nwords = idisp
      endif

* In this point, only PE0 has appropriate values in feel(np_displs)
*-------------------------------------------------------------------
* Scatter Buffersize
*-------------------
      call mpi_bcast(nwords,1,MPI_INTEGER,0,mpi_comm_world,ierr)
*-------------------------------------------------------------------
* Allocate Buffer in each PE
*-------------------
      call f_alloc(np_ibuf,'np_ibuf/feelgatherbcast',nwords,0,0)

*-------------------------------------------------------------------
* Scatter np_counts,np_displs array
*-------------------------------------------------------------------
      call mpi_bcast(feel(np_counts),nprocs,MPI_INTEGER,
     $               0,mpi_comm_world,ierr)
      call mpi_bcast(feel(np_displs),nprocs,MPI_INTEGER,
     $               0,mpi_comm_world,ierr)
*-------------------------------------------------------------------
* Gather and Scatter the data
*----------------------------
      call mpi_gatherv(mybuf,mycount, MPI_INTEGER,
     $   feel(np_ibuf),feel(np_counts),feel(np_displs),MPI_INTEGER,
     $                 0, mpi_comm_world,ierr)
*
      call mpi_bcast(feel(np_ibuf),nwords,MPI_INTEGER,
     $                 0, mpi_comm_world,ierr)
*-------------------------------------------------------------------
      if(myrank.eq.0)call preportfgatherbcast(nprocs,nwords) 
*
      return
      end
      subroutine feelgathervbcastdbl(myrank,nprocs,feel,
     $                               mycount,mydbuf ,
     $                               np_ibuf,np_counts,np_displs )
*-------------------------------------------------------------------
* Gatherv and Bcast  (For INTEGER*4 and REAL*4 only)
* NOTICE :Allocate np_ibuf,np_counts,np_displs HERE
* 
* PURPOSE: Gather data from each processor to PE0, and then, 
*          put them to all processors again
*
* INPUT  : myrank     My PE number
*          nprocs     Total number of processors
*          feel       work array
*          mycount    number of words in my PE region / 0 is possible
*          mydbuf(*)  REAL*8 data buffer
*
* OUTPUT : np_ibuf    Buffer:Total data buffer
*          np_counts  Buffer:Number of elements for each PE data
*          np_displs  Buffer:Number of displacement for each PE data
*-------------------------------------------------------------------
      include 'mpif.h'
*
      real*4 feel(*)
      real*8 mydbuf(*)
*-------------------------------------------------------------------
      if(myrank.eq.0) call preportsilent
*---
      if(mycount .lt. 0) call abortexit(myrank,'mycount<0 in fgvb')
*---
      call f_alloc(np_counts,'counts in feelgathervbcast',nprocs,0,0)
      call f_alloc(np_displs,'counts in feelgathervbcast',nprocs,0,0)
*
      call mpi_gather(mycount,         1, MPI_INTEGER,
     $                feel(np_counts), 1, MPI_INTEGER, 0, 
     $                                    mpi_comm_world,ierr)
*-------^
* In this point, only PE0 has appropriate values in feel(np_count)
*-------
      if(myrank .eq. 0) call preportsilent
*-------------------------------------------------------------------
      if(myrank.eq.0) then
         idisp = 0
         do 100 i=1,nprocs
            call feelset_npi(feel,np_displs,i,idisp)
            idisp = idisp + inp_feelget(feel,np_counts,i)
 100     continue
*
         nwords = idisp
      endif

* In this point, only PE0 has appropriate values in feel(np_displs)
*-------------------------------------------------------------------
* Scatter Buffersize
*-------------------
      call mpi_bcast(nwords,1,MPI_INTEGER,0,mpi_comm_world,ierr)
*-------------------------------------------------------------------
* Allocate Buffer in each PE
*-------------------
      call f_alloc(np_ibuf,'np_ibuf/feelgatherbcast',nwords,1,0)

*-------------------------------------------------------------------
* Scatter np_counts,np_displs array
*-------------------------------------------------------------------
      call mpi_bcast(feel(np_counts),nprocs,MPI_INTEGER,
     $               0,mpi_comm_world,ierr)
      call mpi_bcast(feel(np_displs),nprocs,MPI_INTEGER,
     $               0,mpi_comm_world,ierr)
*-------------------------------------------------------------------
* Gather and Scatter the data
*----------------------------
      call mpi_gatherv(mydbuf,mycount, MPI_DOUBLE_PRECISION,
     $   feel(np_ibuf),feel(np_counts),feel(np_displs),
     $                                 MPI_DOUBLE_PRECISION,
     $                 0, mpi_comm_world,ierr)
*
      call mpi_bcast(feel(np_ibuf),nwords,MPI_DOUBLE_PRECISION,
     $                 0, mpi_comm_world,ierr)
*-------------------------------------------------------------------
      if(myrank.eq.0)call preportfgatherbcast(nprocs,nwords) 
*
      return
      end

      







