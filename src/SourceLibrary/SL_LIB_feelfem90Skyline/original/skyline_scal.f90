  double precision FUNCTION SCAL(X,Y,N)

    implicit none
!    double precision,dimension(*)         :: x,y
    double precision x(*),y(*)
    integer                               :: n

    integer                               :: i
    double precision                      :: zero

    DATA ZERO/0.0D0/
    !
    SCAL = ZERO
    DO I = 1,N
       SCAL = SCAL + X( I ) * Y( I )
    end do
    !
    RETURN

  end function scal

