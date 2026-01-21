C**********************************************************************
C
C     SQUARE           square.f
C
C**********************************************************************
      SUBROUTINE SQUARE( NODE,NELM,MTJ,PX,PY,ID,MMTJ,IDM,IDMM,KTJ,KTE )
C
      DIMENSION MTJ( KTE,9 ),PX( KTJ ),PY( KTJ ),ID( KTE )
      DIMENSION MMTJ( KTE,4 )
      DIMENSION IDM( KTE ),IDMM( KTE )
C
      NELM1 = 0
      DO 10 I = 1,NELM
         IF( MTJ( I,9 ).EQ.0 ) THEN
            DO 20 J = 1,ID( I )
               NELM1 = NELM1 + 1
               MMTJ( NELM1,1 ) = MTJ( I,MOD( 2 * J + 3,6 ) + 1 )
               MMTJ( NELM1,2 ) = MTJ( I,2 * J - 1 )
               MMTJ( NELM1,3 ) = MTJ( I,2 * J )
               MMTJ( NELM1,4 ) = MTJ( I,7 )
               IDMM( NELM1 ) = IDM( I )
 20         CONTINUE
C
         ELSE
            DO 30 J = 1,ID( I )
               NELM1 =NELM1 + 1
               MMTJ( NELM1,1 ) = MTJ( I,MOD( 2 * J + 5,8 ) + 1 )
               MMTJ( NELM1,2 ) = MTJ( I,2 * J - 1 )
               MMTJ( NELM1,3 ) = MTJ( I,2 * J )
               MMTJ( NELM1,4 ) = MTJ( I,9 )
               IDMM( NELM1 ) = IDM( I )
 30         CONTINUE
         ENDIF
C
 10   CONTINUE
C
      NELM = NELM1
C
      RETURN
      END
