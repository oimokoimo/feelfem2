C*********************************************************************
C
C     GENERATION OF QUAD FROM TWO TRIANGLES      exelm.c
C
C*********************************************************************
      SUBROUTINE EXELM( NODE,NELM,MTJ,JAC,KV,IDM,MAP,PX,PY,KTJ,KTE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PX( KTJ ),PY( KTJ ),MTJ( KTE,9 ),JAC( KTE,4 ),PL( 3 )
      DIMENSION IDM( KTE ),MAP( KTE ),KV( KTE )
C
      IV = 0
      DO 10 I = 1,NELM
         IF( MTJ( I,1 ).EQ.0 ) GOTO 10
         IF( MTJ( I,4 ).NE.0 ) GOTO 10
C
         PXA = PX( MTJ( I,1 ) ) - PX( MTJ( I,2 ) )
         PYA = PY( MTJ( I,1 ) ) - PY( MTJ( I,2 ) )
         PXB = PX( MTJ( I,2 ) ) - PX( MTJ( I,3 ) )
         PYB = PY( MTJ( I,2 ) ) - PY( MTJ( I,3 ) )
         PXC = PX( MTJ( I,3 ) ) - PX( MTJ( I,1 ) )
         PYC = PY( MTJ( I,3 ) ) - PY( MTJ( I,1 ) )
C
         PL( 1 ) = PXA * PXA + PYA * PYA
         PL( 2 ) = PXB * PXB + PYB * PYB
         PL( 3 ) = PXC * PXC + PYC * PYC
C
         DO 20 J = 1,3 
            IF( ( PL( J ).GT.PL( MOD( J,3 ) + 1 ) ).AND.
     *           ( PL( J ).GT.PL( MOD( J + 1 , 3 ) + 1 ) ) ) THEN
               IP = J
               GOTO 30
            ENDIF
 20      CONTINUE
C
 30      IN = JAC( I,IP )
C
         IF( IN.LE.0 ) GOTO 10
         IF( IDM( I ).NE.IDM( IN ) ) GOTO 10
         IF( MTJ( IN,4 ).NE.0 ) GOTO 10
         IF( IN.EQ.0 ) GOTO 10
C
         CALL EDGE( IN,I,JAC,KTE,IE1 )
C
         IE2 = MOD( IE1,3 ) + 1
         IE3 = MOD( IE2,3 ) + 1
C
         PX12 = PX( MTJ( IN,IE2 ) ) - PX( MTJ( IN,IE3 ) )
         PY12 = PY( MTJ( IN,IE2 ) ) - PY( MTJ( IN,IE3 ) )
         PX23 = PX( MTJ( IN,IE3 ) ) - PX( MTJ( IN,IE1 ) )
         PY23 = PY( MTJ( IN,IE3 ) ) - PY( MTJ( IN,IE1 ) )
C
         PL12 = PX12 * PX12 + PY12 * PY12
         PL23 = PX23 * PX23 + PY23 * PY23
C
         IF( ( PL12.GT.PL( IP ) ).OR.(PL23.GT.PL( IP ) ) ) GOTO 10
C
         IA = MTJ( I,MOD(IP,3 ) + 1 )
         IB = MTJ( I,MOD( IP + 1 ,3 ) + 1 )
         IC = MTJ( I,IP )
C
         JACIA = JAC( I,MOD( IP,3 ) + 1 )
         JACIB = JAC( I,MOD( IP + 1 , 3 ) + 1 )
C
         MTJ( I,1 ) = IA
         MTJ( I,2 ) = IB
         MTJ( I,3 ) = IC
         MTJ( I,4 ) = MTJ( IN,IE3 )
C
         JAC( I,1 ) = JACIA
         JAC( I,2 ) = JACIB
C
         INN1 = JAC( IN,IE2 )
         INN2 = JAC( IN,IE3 )
C
         IF( INN1.NE.0 ) THEN
            CALL EDGE( INN1,IN,JAC,KTE,IEN1 )
            JAC( INN1,IEN1 ) = I
         ENDIF
C
         IF( INN2.NE.0 ) THEN
            CALL EDGE( INN2,IN,JAC,KTE,IEN2 )
            JAC( INN2,IEN2 ) = I
         ENDIF
         JAC( I,3 ) = INN1
         JAC( I,4 ) = INN2
C
         DO 40 K = 1,3 
            MTJ( IN,K ) = 0
            JAC( IN,K ) = 0
            IDM( IN ) = 0
 40      CONTINUE
C
         IV = IV + 1
         KV( IV ) = IN
 10   CONTINUE
C
      CALL DELETE( NELM,MTJ,JAC,IDM,KTE,IV,KV,MAP )
C
      RETURN
      END

         

