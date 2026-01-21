C******************************************************************
C
C     FIND EDGE IN TRIANGLE L WHICH IS ADJACENT TO TRIANGLE K   edge.f
C
C******************************************************************
      SUBROUTINE EDGE( L,K,JAC,MMM,IEDGE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION JAC( MMM,3 )
C
      DO 10 I = 1,3
         IF( JAC( L,I ).EQ.K ) THEN
            IEDGE = I
            RETURN
         ENDIF
 10   CONTINUE
C
      WRITE( *,* )' *** ERROR IN SUBROUTINE EDGE *** '
      WRITE( *,* )' **** ELEMENTS NOT ADJACENT **** '
      STOP
C
      RETURN
      END
