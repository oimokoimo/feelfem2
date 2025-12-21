C******************************************************************
C
C     LAPLACIAN METHOD              laplas.f
C
C******************************************************************
      SUBROUTINE LAPLAS( NODE,NELM,IFIX,MTJ,PX,PY,JNB,NEI,KTE,KTJ,KCM )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION IFIX( KTJ ),MTJ( KTE,3 ),PX( KTJ + 3 ),PY( KTJ + 3 )
      DIMENSION NEI( KTJ,KCM ),JNB( KTJ )
C
C     ITERA :ITERATION TIMES
C
      ITERA = 10
      DO 10 IT = 1, ITERA
         DO 20 I = 1, NODE
            IF( IFIX( I ).EQ.0 ) THEN
               GX = 0.D0
               GY = 0.D0
               AR = 0.D0
               DO 30 J = 1,JNB( I )
                  IELM = NEI( I,J )
                  J1 = MTJ( IELM,1 )
                  J2 = MTJ( IELM,2 )
                  J3 = MTJ( IELM,3 )
C
                  S = AREA( IELM,MTJ,PX,PY,KTJ,KTE )
C
                  XC = ( PX( J1 ) + PX( J2 ) + PX( J3 ) ) / 3.D0
                  YC = ( PY( J1 ) + PY( J2 ) + PY( J3 ) ) / 3.D0
C
                  AR = AR + S
                  GX = GX + S * XC
                  GY = GY + S * YC
 30            CONTINUE
C
               CGRAX = GX / AR
               CGRAY = GY / AR
               PX( I ) = CGRAX
               PY( I ) = CGRAY
            ENDIF
 20      CONTINUE
 10   CONTINUE
C
      RETURN
      END
