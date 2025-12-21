C*********************************************************************
C
C     FIND VERTEX IN TRIANGLE L WHICH INCLUDES POINT K   ivent.f
C
C*********************************************************************
      FUNCTION IVERT( L,K,MTJ,MMM )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( MMM,3 )
C
      DO 10 I = 1,3
         IF( MTJ( L,I ).EQ.K ) THEN
            IVERT = I
            RETURN
         ENDIF
 10   CONTINUE
C
      WRITE( *,* )' *** ERROR IN FUNCTION IVERT *** '
      WRITE( *,* )' **** VERTICES NOT INCLUDES **** '
      STOP
C
      RETURN
      END
