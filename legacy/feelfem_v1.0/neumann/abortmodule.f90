module abortmodule

contains

subroutine abortexit(cha)
implicit none

character(len=*)   :: cha

write(*,*) cha

stop

end subroutine abortexit

!--------------------
end module abortmodule
