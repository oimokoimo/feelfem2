      subroutine abortexit(myrank,mesg)
      include 'mpif.h'
      character mesg*(*)
      

      write(*,*) 'MY RANK     : ',myrank
      write(*,*) 'ABORT MODULE: ',mesg

      if(myrank.eq.0) call doclosefil

      call mpi_abort(mpi_comm_world,-1,ierr)

      stop
      end
