C*******************************************************************
C
C     COMPUTATION OF ANGLE           theta.f
C
C******************************************************************
      FUNCTION THETA( X0,Y0,X1,Y1,X2,Y2 )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      PI = 3.1415926535893D0
      ERROR = 1.0D-15
      XA = X1 - X0
      YA = Y1 - Y0
      XB = X2 - X0
      YB = Y2 - Y0
      PRDIN = XA * XB + YA * YB
      PRDEX = XA * YB - XB * YA
      IF( DABS( PRDIN ).LT.ERROR ) THEN
         THETA = PI / 2.D0
      ELSE
         THETA = DATAN( PRDEX / PRDIN )
         IF( THETA.LT.0 ) THEN
            THETA = THETA + PI
         ENDIF
         IF( THETA.GT.PI ) THEN
            THETA = THETA - PI
         ENDIF
      ENDIF
C
      RETURN
      END


