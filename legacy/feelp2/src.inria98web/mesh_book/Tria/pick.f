C*********************************************************************
C
C     PICK UP POINTS ON BOUNDARY OF GIVEN POLYGON      pick.f
C
C*********************************************************************
      SUBROUTINE PICK( IQ,IP,IV,KV,MTJ,JAC,MAP,NPA,NPB,NSRA,
     *     NSRB,KTE,KTJ,LTJ )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION KV( KTE ),MTJ( KTE,3 ),JAC( KTE,3 ),MAP( KTE )
      DIMENSION NSRA( LTJ ),NSRB( LTJ )
C
C******* DOMAIN A
C
      NPA = 1
      NSRA( NPA ) = IP
      IVX = IVERT( KV( 1 ),IP,MTJ,KTE )
      NPA = NPA + 1
      NSRA( NPA ) = MTJ( KV( 1 ),MOD( IVX,3 ) + 1 )
C
      DO 10 I = 2,IV-1
         JVX = IVERT( KV( I ),NSRA( NPA ),MTJ,KTE )
         JELM = JAC( KV( I ),JVX )
         IF( JELM.EQ.0 ) THEN
            NPA = NPA + 1
            NSRA( NPA ) = MTJ( KV( I ),MOD( JVX,3 ) + 1 )
         ELSE IF( MAP( JELM ).EQ.0 ) THEN
            NPA = NPA + 1
            NSRA( NPA ) = MTJ( KV( I ),MOD( JVX,3 ) + 1 )
         ENDIF
 10   CONTINUE
C
      NPA = NPA + 1
      NSRA( NPA ) = IQ
C
C******* DOMAIN B
C
      NPB = 1
      NSRB( NPB ) = IQ
      IVX = IVERT( KV( IV ),IQ,MTJ,KTE )
      NPB = NPB + 1
      NSRB( NPB ) = MTJ( KV( IV ),MOD( IVX,3 ) + 1 )
C
      DO 20 I = IV-1,2,-1
         JVX = IVERT( KV( I ),NSRB( NPB ),MTJ,KTE )
         JELM = JAC( KV( I ),JVX )
         IF( JELM.EQ.0 ) THEN
            NPB = NPB + 1
            NSRB( NPB ) = MTJ( KV( I ),MOD( JVX,3 ) + 1 )
         ELSE IF( MAP( JELM ).EQ.0 ) THEN
            NPB = NPB + 1
            NSRB( NPB ) = MTJ( KV( I ),MOD( JVX,3 ) + 1 )
         ENDIF
 20   CONTINUE
C
      NPB = NPB + 1
      NSRB( NPB ) = IP
C
C******* CHECK OF NODES WHICH IS PICKED UP
C
      IF( IV.NE.NPA + NPB - 4 ) THEN
         WRITE( *,* )' *** ERROR IN SUBROUTINE PICK *** '
         WRITE( *,* )' *** INCORRECT NUMBER OF NODES ** '
         STOP
      ENDIF
C
      RETURN
      END



