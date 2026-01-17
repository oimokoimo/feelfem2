      subroutine feelallocbcast(feel,myrank,nprocs,nwords,np_ptr)
*---------------------
      parameter (MAX_NWORDS = 32000)
*
      include 'mpif.h'
      real   *4 feel(*)
      integer*4 myrank,nprocs
*---------------------
      if(myrank.eq.0) call preportsilent
      call mpi_bcast(nwords,1,MPI_INTEGER,0,mpi_comm_world,ierr)
*
      if(myrank.ne.0) then
         call f_alloc(np_ptr,'(feelallocbcast)',nwords,0,0)
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
*      
      if(myrank .eq.0 ) call preportfbcast(nprocs,nwords,ntimes)
*
      return
      end
