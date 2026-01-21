C********************************************************************
C
C     GENERATINO OF NODES        isogen.f
C
C********************************************************************
      SUBROUTINE ISOGEN( NODE,NELM,MTJ,JAC,PX,PY,ID,MMTJ,IFIX,
     *     IDM,IDMM,KTJ,KTE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( KTE,9 ),PX( KTJ ),PY( KTJ ),ID( KTE ),IFIX( KTJ )
      DIMENSION MMTJ( KTE,4 ),JAC( KTE,4 ),IDM( KTE )
      DIMENSION IDMM( KTE )
C
      DO 10 I = 1,NELM
         IF( MTJ( I,4 ).EQ.0 ) THEN
            ID( I ) = 3
            MTJ( I,5 ) = MTJ( I,3 )
            MTJ( I,3 ) = MTJ( I,2 )
            MTJ( I,2 ) = 0
         ELSE
            ID( I ) = 4
            MTJ( I,7 ) = MTJ( I,4 )
            MTJ( I,5 ) = MTJ( I,3 )
            MTJ( I,4 ) = 0
            MTJ( I,3 ) = MTJ( I,2 )
            MTJ( I,2 ) = 0
         ENDIF
 10   CONTINUE
C
      DO 20 I = 1,NELM
         DO 30 J = 1,ID( I ) 
            IF( MTJ( I, 2 * J ).NE.0 ) GOTO 30
            NODE = NODE + 1
            MTJ( I,2 * J ) = NODE
            PX( NODE ) = ( PX(MTJ( I,2 * J - 1 ) ) +
     *           PX( MTJ( I,MOD( 2 * J ,2 * ID( I ) ) + 1 ) ) ) / 2.D0
            PY( NODE ) = ( PY(MTJ( I,2 * J - 1 ) ) +
     *           PY( MTJ( I,MOD( 2 * J ,2 * ID( I ) ) + 1 ) ) ) / 2.D0
C
            IF( JAC( I,J ).EQ.0 ) THEN
               IFIX( NODE ) = 1
               GOTO 30
            ENDIF
C
            IN = JAC( I,J )
            CALL EDGE( IN,I,JAC,KTE,IEN )
            IF( MTJ( IN,2 * IEN ).NE.0 ) GOTO 30
            MTJ( IN,2 * IEN ) = NODE
            IF( IDM( I ).NE.IDM( IN ) )  IFIX( NODE ) = 1
 30      CONTINUE
C
         NODE = NODE + 1
         MTJ( I,2 * ID( I ) + 1 ) = NODE
         PXX = 0
         PYY = 0
         DO 40 K = 1,ID( I )
            PXX = PXX + PX( MTJ( I,2 * K ) )
            PYY = PYY + PY( MTJ( I,2 * K ) )
 40      CONTINUE
C
         PX( NODE ) = PXX / ID( I )
         PY( NODE ) = PYY / ID( I )
 20   CONTINUE
C
      CALL SQUARE( NODE,NELM,MTJ,PX,PY,ID,MMTJ,IDM,IDMM,KTJ,KTE )
C
      RETURN
      END
