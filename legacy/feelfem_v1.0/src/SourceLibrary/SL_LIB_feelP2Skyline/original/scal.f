C*************************************************************
C
C     FUNCTION SCAL(X,Y,N)             scal.f
C
C**************************************************************
      REAL * 8 FUNCTION SCAL(X,Y,N)
C
      IMPLICIT REAL*8(A-H,O-Z)
C
      DIMENSION X(1),Y(1)
C
      DATA ZERO/0.0D0/
C
      SCAL = ZERO
      DO 10 I = 1,N
         SCAL = SCAL + X( I ) * Y( I )
 10   CONTINUE
C
      RETURN
      END
