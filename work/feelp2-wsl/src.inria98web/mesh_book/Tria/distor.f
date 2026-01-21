C*****************************************************************
C
C     COMPUTATION OF DISTORTION RATE          distor.f
C
C*****************************************************************
      SUBROUTINE DISTOR( N,MTJ,PX,PY,DRATE,JEDG,KTE,KTJ )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( KTE,3 ),PX( KTJ ),PY( KTJ ),DST( 3 )
C
      PI = 3.1415926535
      XA = PX( MTJ( N,1 ) )
      YA = PY( MTJ( N,1 ) )
      XB = PX( MTJ( N,2 ) )
      YB = PY( MTJ( N,2 ) )
      XC = PX( MTJ( N,3 ) )
      YC = PY( MTJ( N,3 ) )
C
      ANG1 = THETA( XC,YC,XA,YA,XB,YB )
      ANG2 = THETA( XA,YA,XB,YB,XC,YC )
      ANG3 = PI - ANG1 - ANG2
C
      DST( 1 ) = ANG1 - PI / 3.D0
      DST( 2 ) = ANG2 - PI / 3.D0
      DST( 3 ) = ANG3 - PI / 3.D0
C
      DRATE = DABS( DST( 1 ) ) + DABS( DST( 2 ) ) + DABS( DST( 3 ) )
      JEDG = 1
      IF( DST( 2 ).GT.DST( JEDG ) ) JEDG = 2
      IF( DST( 3 ).GT.DST( JEDG ) ) JEDG = 3
C
      RETURN
      END




