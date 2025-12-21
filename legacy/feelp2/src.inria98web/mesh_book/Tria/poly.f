C***************************************************************
C
C     SUBDIVIDE GIVEN POLYGON INTO FINE ELEMENT     poly.f
C
C***************************************************************
      SUBROUTINE POLY( IQ,IP,IV,KV,PX,PY,NELM,MTJ,JAC,JNB,NEI,
     *     MAP,KTE,KTJ,KCM )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      PARAMETER ( LTE = 100 )
C
      DIMENSION KV( KTE ),PX( KTJ + 3 ),PY( KTJ + 3 ),MTJ( KTE,3 )
      DIMENSION JNB( KTJ ),NEI( KTJ,KCM ),MAP( KTE ),NSRA( LTE + 2 )
      DIMENSION IENA( LTE,3 ),IENB( LTE,3 ),JEEA( LTE,3 )
      DIMENSION IHEN( 2*LTE + 1 ),JHEN( 2*LTE + 1 ),IAD( 2*LTE + 1)
      DIMENSION JAC( KTE,3 ),NSRB( LTE + 2 ),JEEB( LTE,3 )
      DIMENSION JSTACK( LTE + 2 )
C
      IF( IV.EQ.2 ) THEN
         CALL EDGE( KV( 1 ),KV( 2 ),JAC,KTE,IA )
         CALL EDGE( KV( 2 ),KV( 1 ),JAC,KTE,JA )
C
         IR = JAC( KV( 1 ),MOD( IA,3 ) + 1 )
         JR = JAC( KV( 2 ),MOD( JA,3 ) + 1 )
C
         MTJ( KV( 1 ),MOD( IA,3 ) + 1 ) = IQ
         JAC( KV( 1 ),IA ) = JR
         JAC( KV( 1 ),MOD( IA,3 ) + 1 ) = KV( 2 )
C
         MTJ( KV( 2 ),MOD( JA,3 ) + 1 ) = IP
         JAC( KV( 2 ),IA ) = IR
         JAC( KV( 2 ),MOD( JA,3 ) + 1 ) = KV( 1 )
C
         IF( IR.NE.0 ) THEN
            CALL EDGE( IR,KV( 1 ),JAC,KTE,IEDGE )
            JAC( IR,IEDGE ) = KV( 2 )
         ENDIF
C
         IF( JR.NE.0 ) THEN
            CALL EDGE( JR,KV( 2 ),JAC,KTE,IEDGE )
            JAC( JR,IEDGE ) = KV( 1 )
         ENDIF
C
         IV1 = MTJ( KV( 1 ),IA )
         IV2 = MTJ( KV( 2 ),JA )
C
         CALL DECR( IV1,KV( 2 ),JNB,NEI,KTJ,KCM )
         CALL DECR( IV2,KV( 1 ),JNB,NEI,KTJ,KCM )
         CALL INCR( IQ,KV( 1 ),JNB,NEI,KTJ,KCM )
         CALL INCR( IP,KV( 2 ),JNB,NEI,KTJ,KCM )
C
         ELSE
            LTJ = LTE + 2
            LHN = 2 * LTE + 1
            NPA = 0
            NPB = 0
            DO 10 I = 1,LTJ
               NSRA( I ) = 0
               NSRB( I ) = 0
 10         CONTINUE
C
            DO 20 I = 1,NELM
               MAP( I ) = 0
 20         CONTINUE
C
            DO 30 I = 1,IV
               MAP( KV( I ) ) = 1
 30         CONTINUE
C
            DO 40 I = 1,IV
               IELM = KV( I )
               DO 40 J = 1,3
                  IVX = MTJ( IELM,J )
                  CALL DECR( IVX,IELM,JNB,NEI,KTJ,KCM )
 40         CONTINUE
C
C******* PICK UP NODES WHICH SURROUND GIVEN POLYGON
C
            CALL PICK( IQ,IP,IV,KV,MTJ,JAC,MAP,NPA,NPB,NSRA,NSRB,
     *           KTE,KTJ,LTJ )
C
C******* DIVIDE GIVEN POLYGON INTO TWO DOMAINS
C        AND APPLY THE MODIFIED-DELAUNAY TO EACH DOMAIN
C
            CALL SUBDIV( NPA,NSRA,PX,PY,NTA,IENA,JEEA,IHEN,JHEN,
     *           IAD,JSTACK,KTJ,LTE,LTJ,LHN )
C
            CALL SUBDIV( NPB,NSRB,PX,PY,NTB,IENB,JEEB,IHEN,JHEN,
     *           IAD,JSTACK,KTJ,LTE,LTJ,LHN )
C
C******* CHECK OF ELEMENTS SUBDIVIDES
C
            IF( IV.NE.NTA + NTB ) THEN
               WRITE( *,* )' *** ERROR IN SUBROUTINE POLY *** '
               WRITE( *,* )' ** INCORRECT NUMBER OF ELEMENTS FORMED **'
               STOP
            ENDIF
C
C******* MODIFICATION OF MTJ,JAC,JNB,NEI
C
            DO 50 I = 1, IV
               DO 50 J = 1,3 
                  JAC( KV( I ),J ) = 0
 50         CONTINUE
C
            DO 60 I = 1, NTA
               IELM = KV( I )
               DO 70 J = 1,3
                  MTJ( IELM,J ) = IENA( I,J )
                  IF( JEEA( I,J ).NE.0 ) THEN
                     JAC( IELM,J ) = KV( JEEA( I,J ) )
                  ENDIF
 70            CONTINUE
 60         CONTINUE
C
            DO 80 I = 1,NTB
               IELM = KV( NTA + I )
               DO 90 J = 1,3
                  MTJ( IELM,J ) = IENB( I,J )
                  IF( JEEB( I,J ).NE.0 ) THEN
                     JAC( IELM,J ) = KV( NTA + JEEB( I,J ) )
                  ENDIF
 90         CONTINUE
 80      CONTINUE
C
         DO 100 I = 1, IV
            IELM = KV( I )
            DO 110 J = 1,3 
               IVX = MTJ( IELM,J )
               CALL INCR( IVX,IELM,JNB,NEI,KTJ,KCM )
 110        CONTINUE
 100     CONTINUE
C
         DO 120 I =1,IV
            IELM = KV( I )
            DO 130 J = 1,3 
               JELM = JAC( IELM,J )
               IF( JELM.NE.0 ) GOTO 130
               IPS = MTJ( IELM,J )
               IPG = MTJ( IELM,MOD( J,3 ) + 1 )
               DO 140 K = 1,JNB( IPG )
                  KELM = NEI( IPG,K )
                  DO 150 L = 1,3
                     IVA = MTJ( KELM,L )
                     IVB = MTJ( KELM,MOD( L,3 ) + 1 )
                     IF( ( IVA.EQ.IPG ).AND.( IVB.EQ.IPS ) ) THEN
                        JAC( IELM,J ) = KELM
                        JAC( KELM,L ) = IELM
                        GOTO 130
                     ENDIF
 150              CONTINUE
 140           CONTINUE
 130        CONTINUE
 120     CONTINUE 
C
      ENDIF
C
      RETURN
      END




               
       
