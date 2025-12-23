module mod_eset1_1_1
contains

subroutine eset1_1_1

!------------------------------------------------------
! general modules
use report90
use numeric
use abortmodule

implicit none


!------------------------------------------------------
integer,parameter                       :: NPG1 =  4  ! No.1 [tet2]


!------------------------------------------------------
! auto variables
!------------------------------------------------------
integer                                 :: itp


!------------------------------------------------------
! common variables
!------------------------------------------------------
real(kind=REAL8)                        :: gx_1,gy_1,gz_1,w_1

real(kind=REAL8)                        :: rT1_1_1
real(kind=REAL8)                        :: rT1_1_x_1
real(kind=REAL8)                        :: rT1_1_y_1
real(kind=REAL8)                        :: rT1_1_z_1
real(kind=REAL8)                        :: rT1_2_1
real(kind=REAL8)                        :: rT1_2_x_1
real(kind=REAL8)                        :: rT1_2_y_1
real(kind=REAL8)                        :: rT1_2_z_1
real(kind=REAL8)                        :: rT1_3_1
real(kind=REAL8)                        :: rT1_3_x_1
real(kind=REAL8)                        :: rT1_3_y_1
real(kind=REAL8)                        :: rT1_3_z_1
real(kind=REAL8)                        :: rT1_4_1
real(kind=REAL8)                        :: rT1_4_x_1
real(kind=REAL8)                        :: rT1_4_y_1
real(kind=REAL8)                        :: rT1_4_z_1
real(kind=REAL8)                        :: rT2_10_1
real(kind=REAL8)                        :: rT2_10_x_1
real(kind=REAL8)                        :: rT2_10_y_1
real(kind=REAL8)                        :: rT2_10_z_1
real(kind=REAL8)                        :: rT2_1_1
real(kind=REAL8)                        :: rT2_1_x_1
real(kind=REAL8)                        :: rT2_1_y_1
real(kind=REAL8)                        :: rT2_1_z_1
real(kind=REAL8)                        :: rT2_2_1
real(kind=REAL8)                        :: rT2_2_x_1
real(kind=REAL8)                        :: rT2_2_y_1
real(kind=REAL8)                        :: rT2_2_z_1
real(kind=REAL8)                        :: rT2_3_1
real(kind=REAL8)                        :: rT2_3_x_1
real(kind=REAL8)                        :: rT2_3_y_1
real(kind=REAL8)                        :: rT2_3_z_1
real(kind=REAL8)                        :: rT2_4_1
real(kind=REAL8)                        :: rT2_4_x_1
real(kind=REAL8)                        :: rT2_4_y_1
real(kind=REAL8)                        :: rT2_4_z_1
real(kind=REAL8)                        :: rT2_5_1
real(kind=REAL8)                        :: rT2_5_x_1
real(kind=REAL8)                        :: rT2_5_y_1
real(kind=REAL8)                        :: rT2_5_z_1
real(kind=REAL8)                        :: rT2_6_1
real(kind=REAL8)                        :: rT2_6_x_1
real(kind=REAL8)                        :: rT2_6_y_1
real(kind=REAL8)                        :: rT2_6_z_1
real(kind=REAL8)                        :: rT2_7_1
real(kind=REAL8)                        :: rT2_7_x_1
real(kind=REAL8)                        :: rT2_7_y_1
real(kind=REAL8)                        :: rT2_7_z_1
real(kind=REAL8)                        :: rT2_8_1
real(kind=REAL8)                        :: rT2_8_x_1
real(kind=REAL8)                        :: rT2_8_y_1
real(kind=REAL8)                        :: rT2_8_z_1
real(kind=REAL8)                        :: rT2_9_1
real(kind=REAL8)                        :: rT2_9_x_1
real(kind=REAL8)                        :: rT2_9_y_1
real(kind=REAL8)                        :: rT2_9_z_1
real(kind=REAL8)                        :: rTEST1_1_1
real(kind=REAL8)                        :: rTEST1_1_x_1
real(kind=REAL8)                        :: rTEST1_1_y_1
real(kind=REAL8)                        :: rTEST1_1_z_1
real(kind=REAL8)                        :: rTEST1_2_1
real(kind=REAL8)                        :: rTEST1_2_x_1
real(kind=REAL8)                        :: rTEST1_2_y_1
real(kind=REAL8)                        :: rTEST1_2_z_1
real(kind=REAL8)                        :: rTEST1_3_1
real(kind=REAL8)                        :: rTEST1_3_x_1
real(kind=REAL8)                        :: rTEST1_3_y_1
real(kind=REAL8)                        :: rTEST1_3_z_1
real(kind=REAL8)                        :: rTEST1_4_1
real(kind=REAL8)                        :: rTEST1_4_x_1
real(kind=REAL8)                        :: rTEST1_4_y_1
real(kind=REAL8)                        :: rTEST1_4_z_1
!------------------------------------------------------
common /em1_1_1/gx_1(NPG1),gy_1(NPG1),gz_1(NPG1),w_1(NPG1) &
,rT1_1_1(NPG1),rT1_1_x_1(NPG1),rT1_1_y_1(NPG1),rT1_1_z_1(NPG1) &
,rT1_2_1(NPG1),rT1_2_x_1(NPG1),rT1_2_y_1(NPG1),rT1_2_z_1(NPG1) &
,rT1_3_1(NPG1),rT1_3_x_1(NPG1),rT1_3_y_1(NPG1),rT1_3_z_1(NPG1) &
,rT1_4_1(NPG1),rT1_4_x_1(NPG1),rT1_4_y_1(NPG1),rT1_4_z_1(NPG1) &
,rT2_10_1(NPG1),rT2_10_x_1(NPG1),rT2_10_y_1(NPG1),rT2_10_z_1 &
(NPG1),rT2_1_1(NPG1),rT2_1_x_1(NPG1),rT2_1_y_1(NPG1),rT2_1_z_1 &
(NPG1),rT2_2_1(NPG1),rT2_2_x_1(NPG1),rT2_2_y_1(NPG1),rT2_2_z_1 &
(NPG1),rT2_3_1(NPG1),rT2_3_x_1(NPG1),rT2_3_y_1(NPG1),rT2_3_z_1 &
(NPG1),rT2_4_1(NPG1),rT2_4_x_1(NPG1),rT2_4_y_1(NPG1),rT2_4_z_1 &
(NPG1),rT2_5_1(NPG1),rT2_5_x_1(NPG1),rT2_5_y_1(NPG1),rT2_5_z_1 &
(NPG1),rT2_6_1(NPG1),rT2_6_x_1(NPG1),rT2_6_y_1(NPG1),rT2_6_z_1 &
(NPG1),rT2_7_1(NPG1),rT2_7_x_1(NPG1),rT2_7_y_1(NPG1),rT2_7_z_1 &
(NPG1),rT2_8_1(NPG1),rT2_8_x_1(NPG1),rT2_8_y_1(NPG1),rT2_8_z_1 &
(NPG1),rT2_9_1(NPG1),rT2_9_x_1(NPG1),rT2_9_y_1(NPG1),rT2_9_z_1 &
(NPG1),rTEST1_1_1(NPG1),rTEST1_1_x_1(NPG1),rTEST1_1_y_1(NPG1) &
,rTEST1_1_z_1(NPG1),rTEST1_2_1(NPG1),rTEST1_2_x_1(NPG1),rTEST1_2_y_1 &
(NPG1),rTEST1_2_z_1(NPG1),rTEST1_3_1(NPG1),rTEST1_3_x_1(NPG1) &
,rTEST1_3_y_1(NPG1),rTEST1_3_z_1(NPG1),rTEST1_4_1(NPG1),rTEST1_4_x_1 &
(NPG1),rTEST1_4_y_1(NPG1),rTEST1_4_z_1(NPG1)
!------------------------------------------------------
gx_1(1) =1.38196601125d-01
gy_1(1) =1.38196601125d-01
gz_1(1) =1.38196601125d-01
 w_1(1) =4.16666666667d-02

gx_1(2) =1.38196601125d-01
gy_1(2) =1.38196601125d-01
gz_1(2) =5.85410196625d-01
 w_1(2) =4.16666666667d-02

gx_1(3) =1.38196601125d-01
gy_1(3) =5.85410196625d-01
gz_1(3) =1.38196601125d-01
 w_1(3) =4.16666666667d-02

gx_1(4) =5.85410196625d-01
gy_1(4) =1.38196601125d-01
gz_1(4) =1.38196601125d-01
 w_1(4) =4.16666666667d-02

!------------------------------------------------------
do itp=1,NPG1

  rT2_1_1(itp)=( 1.000000000000000-gx_1(itp)-gz_1(itp)-gy_1(itp)) &
*( 2.000000000000000*( 1.000000000000000-gx_1(itp)-gz_1(itp) &
-gy_1(itp))- 1.000000000000000)
  rT2_2_1(itp)=gx_1(itp)*( 2.000000000000000*gx_1(itp)- 1.000000000000000)
  rT2_3_1(itp)=gy_1(itp)*( 2.000000000000000*gy_1(itp)- 1.000000000000000)
  rT2_4_1(itp)=gz_1(itp)*( 2.000000000000000*gz_1(itp)- 1.000000000000000)
  rT2_5_1(itp)= 4.000000000000000*gx_1(itp)*( 1.000000000000000 &
-gx_1(itp)-gz_1(itp)-gy_1(itp))
  rT2_6_1(itp)= 4.000000000000000*gx_1(itp)*gy_1(itp)
  rT2_7_1(itp)= 4.000000000000000*gy_1(itp)*( 1.000000000000000 &
-gx_1(itp)-gz_1(itp)-gy_1(itp))
  rT2_8_1(itp)= 4.000000000000000*gz_1(itp)*( 1.000000000000000 &
-gx_1(itp)-gz_1(itp)-gy_1(itp))
  rT2_9_1(itp)= 4.000000000000000*gx_1(itp)*gz_1(itp)
  rT2_10_1(itp)= 4.000000000000000*gy_1(itp)*gz_1(itp)
  rT2_1_x_1(itp)=-3.0+(4.0)*gy_1(itp)+(4.0)*gx_1(itp)+(4.0)*gz_1(itp)
  rT2_2_x_1(itp)=-1.0+(4.0)*gx_1(itp)
  rT2_3_x_1(itp)=0
  rT2_4_x_1(itp)=0
  rT2_5_x_1(itp)=4.0-(4.0)*gy_1(itp)-(8.0)*gx_1(itp)-(4.0)*gz_1(itp)
  rT2_6_x_1(itp)=(4.0)*gy_1(itp)
  rT2_7_x_1(itp)=-(4.0)*gy_1(itp)
  rT2_8_x_1(itp)=-(4.0)*gz_1(itp)
  rT2_9_x_1(itp)=(4.0)*gz_1(itp)
  rT2_10_x_1(itp)=0
  rT2_1_y_1(itp)=-3.0+(4.0)*gy_1(itp)+(4.0)*gx_1(itp)+(4.0)*gz_1(itp)
  rT2_2_y_1(itp)=0
  rT2_3_y_1(itp)=-1.0+(4.0)*gy_1(itp)
  rT2_4_y_1(itp)=0
  rT2_5_y_1(itp)=-(4.0)*gx_1(itp)
  rT2_6_y_1(itp)=(4.0)*gx_1(itp)
  rT2_7_y_1(itp)=4.0-(8.0)*gy_1(itp)-(4.0)*gx_1(itp)-(4.0)*gz_1(itp)
  rT2_8_y_1(itp)=-(4.0)*gz_1(itp)
  rT2_9_y_1(itp)=0
  rT2_10_y_1(itp)=(4.0)*gz_1(itp)
  rT2_1_z_1(itp)=-3.0+(4.0)*gy_1(itp)+(4.0)*gx_1(itp)+(4.0)*gz_1(itp)
  rT2_2_z_1(itp)=0
  rT2_3_z_1(itp)=0
  rT2_4_z_1(itp)=-1.0+(4.0)*gz_1(itp)
  rT2_5_z_1(itp)=-(4.0)*gx_1(itp)
  rT2_6_z_1(itp)=0
  rT2_7_z_1(itp)=-(4.0)*gy_1(itp)
  rT2_8_z_1(itp)=4.0-(4.0)*gy_1(itp)-(4.0)*gx_1(itp)-(8.0)*gz_1(itp)
  rT2_9_z_1(itp)=(4.0)*gx_1(itp)
  rT2_10_z_1(itp)=(4.0)*gy_1(itp)
  rT1_1_1(itp)= 1.000000000000000-gx_1(itp)-gy_1(itp)-gz_1(itp)
  rT1_2_1(itp)=gx_1(itp)
  rT1_3_1(itp)=gy_1(itp)
  rT1_4_1(itp)=gz_1(itp)
  rT1_1_x_1(itp)=-1
  rT1_2_x_1(itp)=1
  rT1_3_x_1(itp)=0
  rT1_4_x_1(itp)=0
  rT1_1_y_1(itp)=-1
  rT1_2_y_1(itp)=0
  rT1_3_y_1(itp)=1
  rT1_4_y_1(itp)=0
  rT1_1_z_1(itp)=-1
  rT1_2_z_1(itp)=0
  rT1_3_z_1(itp)=0
  rT1_4_z_1(itp)=1
  rTEST1_1_1(itp)=1-gx_1(itp)-gy_1(itp)-gz_1(itp)
  rTEST1_2_1(itp)=gx_1(itp)
  rTEST1_3_1(itp)=gy_1(itp)
  rTEST1_4_1(itp)=gz_1(itp)
  rTEST1_1_x_1(itp)=-1
  rTEST1_2_x_1(itp)=1
  rTEST1_3_x_1(itp)=0
  rTEST1_4_x_1(itp)=0
  rTEST1_1_y_1(itp)=-1
  rTEST1_2_y_1(itp)=0
  rTEST1_3_y_1(itp)=1
  rTEST1_4_y_1(itp)=0
  rTEST1_1_z_1(itp)=-1
  rTEST1_2_z_1(itp)=0
  rTEST1_3_z_1(itp)=0
  rTEST1_4_z_1(itp)=1


end do
!------------------------------------------------------

return

end subroutine eset1_1_1
end module mod_eset1_1_1
