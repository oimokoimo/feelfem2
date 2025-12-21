C*********************************************************************
C
C     CHECK IF POINT LIES INSIDE THE CIRCUMCIRCLE      swap.f
C
C*********************************************************************
      SUBROUTINE SWAP( X1,Y1,X2,Y2,X3,Y3,XP,YP,ISWAP )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      X13 = X1 - X3
      Y13 = Y1 - Y3
      X23 = X2 - X3
      Y23 = Y2 - Y3
      X1P = X1 - XP
      Y1P = Y1 - YP
      X2P = X2 - XP
      Y2P = Y2 - YP
C
      COSA = X13 * X23 + Y13 * Y23
      COSB = X2P * X1P + Y1P * Y2P
C
      IF( ( COSA.GE.0.D0 ).AND.( COSB.GE.0.D0 ) ) THEN
         ISWAP = 0
      ELSE IF( ( COSA.LT.0.D0 ).AND.( COSB.LT.0.D0 ) ) THEN
         ISWAP = 1
      ELSE
         SINA = X13 * Y23 - X23 * Y13
         SINB = X2P * Y1P - X1P * Y2P
C
         IF( ( SINA * COSB + SINB * COSA ).LT.0.D0 ) THEN
            ISWAP = 1
         ELSE
            ISWAP = 0
         ENDIF
      ENDIF
C
      RETURN
      END
