C********************************************************************
C
C     APPLY LAWSON'S SWAPPING ALGORITHM TO NEW ELEMENTS    lawson.f
C
C********************************************************************
      SUBROUTINE LAWSON( NTE,IEN,JEE,NPL,PX,PY,JSTACK,KTJ,LTE,LTJ )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION IEN( LTE,3 ),JEE( LTE,3 ),PX( KTJ + 3 ),PY( KTJ + 3 )
      DIMENSION JSTACK( LTJ )
C
      ITOP = 0
      MAXSTK = NPL
      NCOUNT = 0
      DO 10 I = 1, NTE 
         IELM = I
         ITOP = ITOP + 1
         JSTACK( ITOP ) = IPUSH( IELM,MAXSTK,ITOP,JSTACK,LTJ )
 10   CONTINUE
C
 20   IF( ITOP.GT.0 ) THEN
         NCOUNT = NCOUNT + 1
         IF( NCOUNT.GT.LTE ) THEN
            WRITE( *,* )' *** ERROR IN SUBROUTINE LAWSON *** '
            WRITE( *,* )' ******** NON-CONVERGENCE *********'
            STOP
         ENDIF
C
         IL = JSTACK( ITOP )
         ITOP = ITOP - 1
         DO 30 J = 1,3
            JL1 = J
            JL2 = MOD( JL1,3 ) + 1
            JL3 = MOD( JL2,3 ) + 1
C
            IR = JEE( IL,JL1 )
            IF( IR.EQ.0 ) GOTO 30
C
            IV1 = IEN( IL,JL1 )
            IV2 = IEN( IL,JL2 )
            IV3 = IEN( IL,JL3 )
C
            XX = PX( IEN( IL,JL3 ) )
            YY = PY( IEN( IL,JL3 ) )
C
            CALL EDGE( IR,IL,JEE,LTE,JR1 )
C
            JR2 = MOD( JR1,3 ) + 1
            JR3 = MOD( JR2,3 ) + 1
            IV4 = IEN( IR,JR3 )
C
            CALL SWAP( PX( IV2 ),PY( IV2 ),PX( IV1 ),PY( IV1 ),
     *           PX( IV4 ),PY( IV4 ),XX,YY,ISWAP )
C
            IF( ISWAP.EQ.1 ) THEN
               IA = JEE( IL,JL2 )
               IB = JEE( IR,JR2 )
C
               IEN( IL,JL2 ) = IV4
               JEE( IL,JL1 ) = IB
               JEE( IL,JL2 ) = IR
C
               IEN( IR,JR2 ) = IV3
               JEE( IR,JR1 ) = IA
               JEE( IR,JR2 ) = IL
C
               IF( IA.NE.0 ) THEN
                  CALL EDGE( IA,IL,JEE,LTE,IEDGE )
                  JEE( IA,IEDGE ) = IR
               ENDIF
C
               IF( IB.NE.0 ) THEN
                  CALL EDGE( IB,IR,JEE,LTE,IEDGE )
                  JEE( IB,IEDGE ) = IL
               ENDIF
C
               ITOP = ITOP + 1
               JSTACK( ITOP ) = IPUSH( IL,MAXSTK,ITOP,JSTACK,LTJ )
               GOTO 20
            ENDIF
 30      CONTINUE
         GOTO 20
      ENDIF
C
      RETURN
      END


