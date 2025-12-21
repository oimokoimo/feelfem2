C*******************************************************************
C
C     CHECK FOR ADJUST ELEMENTS        check.f
C
C*******************************************************************
      SUBROUTINE CHECK( NELM,MTJ,JAC,KTE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( KTE,3 ),JAC( KTE,3 )
C
      DO 10 I = 1,NELM
         DO 10 J = 1,3
            IELM = I
            IA = MTJ( I,J )
            IB = MTJ( I,MOD( J,3 ) + 1 )
            JELM = JAC( I,J )
            IF( JELM.EQ.0 ) GOTO 10
C
            DO 20 K = 1,3
               KELM = JAC( JELM,K )
               IF( KELM.EQ.IELM ) THEN
                  JA = MTJ( JELM,K )
                  JB = MTJ( JELM,MOD( K,3 ) + 1 )
                  IF( ( IA.EQ.JB ).AND.( IB.EQ.JA ) ) GOTO 10
                  WRITE( *,* )' *** ERROR IN SUBROUTINE CHECK *** '
                  WRITE( *,* )' ********** JAC IS WRONG **********'
                  STOP
               ENDIF
 20         CONTINUE
C
            WRITE( *,* )' *** ERROR IN SUBROUTINE CHECK *** '
            WRITE( *,* )' *** ADJACENT ELEMENT NOT FOUND ***'
            STOP
 10   CONTINUE
C
      RETURN
      END







