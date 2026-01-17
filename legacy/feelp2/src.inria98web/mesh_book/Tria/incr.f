C******************************************************************
C
C PLACE TRIANGLE L ON ADJACENT LIST OF POINT N AND INCREMENT LIST SIZE
C
C                                                incr.f
C
C******************************************************************
      SUBROUTINE INCR( N,L,JNB,NEI,KTJ,KCM )
C
      IMPLICIT REAL*8 ( A-H,O-Z )
C
      DIMENSION JNB( KTJ ),NEI( KTJ,KCM )
C
      IF( N.LE.KTJ ) THEN
         JNB( N ) = JNB( N ) + 1
         IF( JNB( N ).GT.KCM ) THEN
            WRITE( *,* )' *** ERROR IN SUBROUTINE INCR *** '
            WRITE( *,* )' **** NEIGHBOR LIST OVERFLOW **** ',n,jnb(n)
            STOP
         ENDIF
C
         NEI( N,JNB( N ) ) = L
      ENDIF
C
      RETURN
      END
