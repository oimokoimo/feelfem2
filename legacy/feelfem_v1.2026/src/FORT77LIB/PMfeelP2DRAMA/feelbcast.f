      subroutine feelbcast(myrank,nprocs,feel,np_ptr,nwords)
*---------------------
      parameter (MAX_NWORDS = 32000)
      include 'mpif.h'
      real*4 feel(*)
*---------------------
      if(myrank.eq.0) call preportsilent
      if(nwords .LT. 1) then
         call abortexit(myrank,'Illegal nwords in feelbcast')
      endif

*---------------------
* Small transfer
*---------------------
      if(nwords .LE. MAX_NWORDS) then
         call mpi_bcast(feel(np_ptr),nwords,    MPI_REAL4,0,
     $        mpi_comm_world,ierr)
*
         if(myrank .eq. 0) call preportfbcast(nprocs,nwords,1)
*
         return
      endif
*---------------------
      ntimes = nwords / MAX_NWORDS
*
      do 100 i=1,ntimes
         nbase = (i-1)*MAX_NWORDS + np_ptr
         nword = MAX_NWORDS
         call mpi_bcast(feel(nbase),nword ,    MPI_REAL4,0,
     $        mpi_comm_world,ierr)
 100  continue
*
      nrem = nwords - ntimes*MAX_NWORDS
      if(nrem .GT. 0) then
         nbase = ntimes*MAX_NWORDS+np_ptr
         nword = nrem
         call mpi_bcast(feel(nbase),nword ,    MPI_REAL4,0,
     $        mpi_comm_world,ierr)
         ntimes = ntimes+1
      endif
      
      if(myrank .eq.0 ) call preportfbcast(nprocs,nwords,ntimes)

      return
      end
         


         
      
