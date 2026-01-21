C*****************************************************************
C
C     ROUGH TRIANGLATION BY THE MODIFIED-DELAUNAY METHOD   rough.f
C
C*****************************************************************
      SUBROUTINE ROUGH( NEX,NIN,IBEX,IBIN,IBNO,NTP,NIB,NODE,PX,PY,
     *     JNB,NEI,NELM,MTJ,JAC,IDM,LIST,IADRES,ISTACK,KV,IBR,MAP,KBD,
     *     KTE,KTJ,KCM )
C
      IMPLICIT REAL*8(A-H,O-Z)
C
      DIMENSION IBEX( KBD ),IBIN( KBD ),IBNO( KBD,KTJ ),PX( KTJ + 3 )
      DIMENSION PY( KTJ + 3 ),MTJ( KTE,3 ),JAC( KTE,3 ),IDM( KTE )
      DIMENSION LIST( KTJ ),IADRES( KTJ + 3 ),ISTACK( KTJ ),JNB( KTJ )
      DIMENSION MAP( KTE ),NEI( KTJ,KCM ),IBR( KTE ), KV( KTE )
C
C******** EXTERIOR BOUNDARIES
C
      DO 10 I = 1, NEX
         IZ = 0
         NB = I
         NP = IBEX( NB )
C
         DO 20 J = 1, NP
            LIST( J ) = IBNO( NB,J )
 20      CONTINUE
C
         CALL BOUGEN( IZ,NP,LIST,NTP,PX,PY,JNB,NEI,NELM,MTJ,JAC,IDM,
     *        IADRES,ISTACK,KV,IBR,MAP,NODE,KTE,KTJ,KCM )
C
         DO 30 K = 1, NELM
            IF( IDM( K ).EQ.IZ ) THEN
               MA = IADRES( MTJ( K,1 ) )
               MB = IADRES( MTJ( K,2 ) )
               MC = IADRES( MTJ( K,3 ) )
C
               MS = MA * MB * MC
               MP = ( MB - MA ) * ( MC - MB ) * ( MA - MC )
               IF( ( MS.NE.0 ).AND.( MP.GT.0 ) ) THEN
                  IDM( K ) = NB 
               ENDIF
            ENDIF
 30      CONTINUE
 10   CONTINUE
C
C********** INTERIOR BOUNDARIES
C
      DO 50 I = 1, NIN
         NB = I
         NP = IBIN( NB )
         DO 60 J = 1, NP
            LIST( J ) = NODE + J
 60      CONTINUE
C
         IS = LIST( 1 )
         XS = PX( IS )
         YS = PY( IS )
C
         CALL LOCATE( XS,YS,PX,PY,MTJ,JAC,NELM,KTE,KTJ,LOC )
C
         IZ = IDM( LOC )
C
         CALL BOUGEN( IZ,NP,LIST,NTP,PX,PY,JNB,NEI,NELM,MTJ,JAC,IDM,
     *        IADRES,ISTACK,KV,IBR,MAP,NODE,KTE,KTJ,KCM )
C
         DO 70 K = 1,NELM
            IF( IDM( K ).EQ.IZ ) THEN
               MA = IADRES( MTJ( K,1 ) )
               MB = IADRES( MTJ( K,2 ) )
               MC = IADRES( MTJ( K,3 ) )
C
               MS = MA * MB * MC
               MP = ( MB - MA ) * ( MC - MB ) * ( MA - MC )
               IF( ( MS.NE.0 ).AND.( MP.LT.0 ) ) THEN
                  IDM( K ) = 0
               ENDIF
            ENDIF
 70      CONTINUE
 50   CONTINUE
C
C******** REMESH BY POINTS IN BOUNDARY BY THE DELAUNAY TRIANGULATION
C
      DO 100 I = 1, KTJ + 3
         IADRES( I ) = 0
 100  CONTINUE
C
      DO 110 I = 1,NIB
         NODE = NODE + 1
         XA = PX( NODE )
         YA = PY( NODE )
         WRITE( *,620 ) NODE
 620     FORMAT( ' INNER POINT NUMBER = ',I5 )
C
         CALL LOCATE( XA,YA,PX,PY,MTJ,JAC,NELM,KTE,KTJ,IT )
C
         IZ = IDM( IT )
C     

         CALL DELAUN( IZ,NODE,NODE,NTP,PX,PY,JNB,NEI,NELM,MTJ,
     *        JAC,IDM,IADRES,ISTACK,KTE,KTJ,KCM )
 110  CONTINUE
C
C******** CHECK OF NODES GENERATED
C
      IF( NODE.NE.NTP ) THEN
         WRITE( *,* )' *** ERROR IN SUBROUTINE ROUGH *** ' 
         WRITE( *,* )' *** INCORRECT NUMBER OF NODES *** '
         STOP
      ENDIF
C
      RETURN
      END

         
         



