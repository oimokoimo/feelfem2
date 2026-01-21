C*****************************************************************
C
C     SUBDIVIDE GIVEN POLYGON USING BY THE MODIFIED-DELAUNAY
C
C                                               sundiv.f
C
C****************************************************************
      SUBROUTINE SUBDIV( NPL,NSR,PX,PY,NTE,IEN,JEE,IHEN,JHEN,IAD,
     *     JSTACK,KTJ,LTE,LTJ,LHN )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION NSR( LTJ ),PX( KTJ + 3 ),PY( KTJ + 3 ),IEN( LTE,3 )
      DIMENSION IHEN( LHN,2 ),JHEN( LHN ),IAD( LHN ),JSTACK( LTJ )
      DIMENSION JEE( LTE,3 )
C
C******* INITIALIZATION
C
      NTE = 0
      NNPL = NPL
      DO 10 I =1,LTE
         DO 10 J = 1,3
            IEN( I,J ) = 0
            JEE( I,J ) = 0
 10   CONTINUE
C
C******* COMPUTATION OF IEN
C
 20   IF( NNPL.GE.3 ) THEN
         NBS = 1
 30      IF( NBS.LE.NNPL-1 ) THEN
            IA = NSR( NBS )
            IB = NSR( NBS + 1 )
            IC = NSR( MOD( NBS + 1, NNPL ) + 1 )
C
            XA = PX( IB ) - PX( IA )
            YA = PY( IB ) - PY( IA )
C
            XB = PX( IC ) - PX( IA )
            YB = PY( IC ) - PY( IA )
C
            SEE = XA * YB - XB * YA
            IF( SEE.GT.1.0D-15 ) THEN
               NTE = NTE + 1
               IEN( NTE,1 ) = IA
               IEN( NTE,2 ) = IB
               IEN( NTE,3 ) = IC
C
               NNPL = NNPL - 1
               DO 40 I = NBS + 1 , NNPL
                  NSR( I ) = NSR( I + 1 )
 40            CONTINUE
            ENDIF
C
            NBS = NBS + 1
            GOTO 30
         ENDIF
         GOTO 20
      ENDIF
C
C******* COMPUTATION JEE
C
      IX = 0
      DO 50 I = 1,LHN
         IHEN( I,1 ) = 0
         IHEN( I,2 ) = 0
         JHEN( I ) = 0
         IAD( I ) = 0
 50   CONTINUE
C
      DO 60 I = 1,NTE
         DO 70 J = 1,3 
            IA = IEN( I,J )
            IB = IEN( I,MOD( J,3 ) + 1 )
            DO 80 K = 1,IX
               IF( ( IHEN( K,1 ).EQ.IB ).AND.( IHEN( K,2 ).EQ.IA ) )THEN
                  JEE( I,J ) = JHEN( K )
                  JEE( JHEN( K ),IAD( K ) ) = I
                  GOTO 70
               ENDIF
 80         CONTINUE
C
            IX = IX + 1
            JHEN( IX ) = I
            IAD( IX ) = J
            IHEN( IX,1 ) = IA
            IHEN( IX,2 ) = IB
 70      CONTINUE
 60   CONTINUE
C
C******* APPLY THE MODIFIED-DELAUNAY TO NEW ELEMENTS
C
      CALL LAWSON( NTE,IEN,JEE,NPL,PX,PY,JSTACK,KTJ,LTE,LTJ )
C
      RETURN
      END


















