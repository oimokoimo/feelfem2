C*******************************************************************
C
C     FIND TRIANGLE L IN ADJACENT LIST OF POINT N      neibor.f
C
C*******************************************************************
      FUNCTION NEIBOR( N,L,JNB,NEI,KTJ,KCM )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION JNB( KTJ ),NEI( KTJ,KCM )
C
      DO 10 I = 1,JNB( N )
         IF( NEI( N,I ).EQ.L ) THEN
            NEIBOR = I
            RETURN
         ENDIF
 10   CONTINUE
C
      WRITE( *,* )' *** ERROR IN FUNCTION NEIBOR *** '
      WRITE( *,* )' ***** ELEMENTS NOT ADJCENT ***** '
      STOP
C
      RETURN
      END
