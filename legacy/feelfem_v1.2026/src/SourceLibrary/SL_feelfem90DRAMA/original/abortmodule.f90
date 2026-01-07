module abortmodule

contains

subroutine abortexit(mypeid)
implicit none
include 'mpif.h'

integer, intent(in) :: mypeid
integer             :: ierror

write(*,*) 'Error occured in PE id.',mypeid

call MPI_ABORT(MPI_COMM_WORLD,-1,ierror)

end subroutine abortexit

!--------------------
end module abortmodule
