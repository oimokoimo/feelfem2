subroutine zeroi(dat,n)
implicit none
integer               :: n
integer,dimension(n)  :: dat

!auto
integer               :: i

do i=1,n
 dat(i)=0
end do
end subroutine zeroi
subroutine zerod(dat,n)
use numeric
implicit none
integer                        :: n
real(kind=REAL8),dimension(n)  :: dat

!auto
integer                        :: i

do i=1,n
 dat(i)=0.0
end do
end subroutine zerod
