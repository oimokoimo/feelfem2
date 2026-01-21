C*******************************************************************
C
C     LOCATE TRIANGLE WHICH ENCLOSES POINT ( XP,YP )  locate.f
C
C*******************************************************************
      SUBROUTINE LOCATE( XP,YP,PX,PY,MTJ,JAC,NELM,KTE,KTJ,ITRI )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PX( KTJ + 3 ),PY( KTJ + 3 ),MTJ( KTE,3 ),JAC( KTE,3 )
C
      ITRI = NELM
 10   CONTINUE
C
      DO 20 I = 1,3
         IA = MTJ( ITRI,I )
         IB = MTJ( ITRI,MOD( I,3 ) + 1 )
         IF( ( PY( IA ) - YP ) * ( PX( IB ) - XP ).GT.
     *        ( PX( IA ) - XP ) * ( PY( IB ) - YP ) ) THEN
            ITRI = JAC( ITRI,I )
            GOTO 10
         ENDIF
 20   CONTINUE
C
      RETURN
      END
