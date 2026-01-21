C*******************************************************************
C
C     REMOVE TRIANGLE L FROM ADJACENT LIST OF POINT N     decr.f
C
C*******************************************************************
      SUBROUTINE DECR( N,L,JNB,NEI,KTJ,KCM )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION JNB( KTJ ),NEI( KTJ,KCM )
C
      IF( N.LE.KTJ ) THEN
         INB = NEIBOR( N,L,JNB,NEI,KTJ,KCM )
         DO 10 I = INB,JNB( N ) - 1 
            NEI( N,I ) = NEI( N,I + 1 )
 10      CONTINUE
C
         NEI( N,JNB( N ) ) = 0
         JNB( N ) = JNB( N ) - 1
         IF( JNB( N ).EQ.0 ) THEN
            WRITE( *,* )' *** ERROR IN SUBROUTINE DECR *** '
            WRITE( *,* )' **** NEIGHBOR LIST UNDEFLOW **** '
            STOP
         ENDIF
      ENDIF
C
      RETURN
      END
