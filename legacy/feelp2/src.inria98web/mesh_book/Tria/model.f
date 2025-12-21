C****************************************************************
C
C     AUTOMATIC MESH GENERATION FOR 2-D NON-CONVEX DOMAIN   model.f
C
C****************************************************************
      SUBROUTINE MODEL( NEX,NIN,IBEX,IBIN,IBNO,NOB,NIB,INDEX,NODE,
     *     PX,PY,NELM,MTJ,JAC,IDM,IFORM,NTOTAL )
C
      IMPLICIT REAL*8(A-H,O-Z)
C
      PARAMETER (KBD=10)
c      PARAMETER (KTJ=4000)
      PARAMETER (KTJ=20000)
      PARAMETER (KCM=70)
C
      DIMENSION IBEX( KBD ),IBIN( KBD ),IBNO( KBD,KTJ )
      DIMENSION INDEX( KBD + 1 ),PX( KTJ + 3 ),PY( KTJ + 3 )
      DIMENSION JNB( KTJ ),NEI( KTJ,KCM ),IFIX( KTJ ),LIST( KTJ )
      DIMENSION ISTACK( KTJ ),KV( 2 * KTJ + 1 ),IBR( 2 * KTJ + 1 )
      DIMENSION ANGL( 2*KTJ + 1 ),NEDG( 2*KTJ + 1 ),KSTACK( 2*KTJ + 1 )
      DIMENSION JAC( 2*KTJ + 1, 3 ),IDM( 2*KTJ + 1 ),IADRES( KTJ + 3 )
      DIMENSION MTJ( 2 * KTJ + 1, 3 ),MAP( 2 * KTJ + 1 )
C
C********* INITIALIZATION
C
      IF ( IFORM.EQ.4 ) NTOTAL = NTOTAL/5
C
      DO 10 I = 1, KBD + 1
         INDEX( I ) = 0
 10   CONTINUE
C
      KTE = 2 * KTJ + 1
      NODE = 0
      NELM = 0
C
      DO 20 I = 1, KTE
         IDM( I ) = 0
         DO 20 J = 1, 3
            MTJ( I,J ) = 0
            JAC( I,J ) = 0
 20   CONTINUE
C
      DO 30 I = 1, KTJ 
         JNB( I ) = 0
         DO 30 J = 1, KCM
            NEI( I,J ) = 0
 30   CONTINUE
C
      DO 40 I = 1, KTJ
         IFIX( I ) = 0
 40   CONTINUE
C
C******** COMPUTATION OF MAX & MIN COORDS FOR X,Y
C         NORMALIZATION OF X,Y-COORDS OF POINTS
C     
      NTP = NOB + NIB
C
      XMIN = PX( 1 )
      XMAX = XMIN
C
      YMIN = PY( 1 )
      YMAX = YMIN
C
      DO 50 I = 2, NTP
         XMIN = DMIN1( XMIN,PX( I ) )
         XMAX = DMAX1( XMAX,PX( I ) )
C
         YMIN = DMIN1( YMIN,PY( I ) )
         YMAX = DMAX1( YMAX,PY( I ) )
 50   CONTINUE
C
      RAX = XMAX - XMIN
      RAY = YMAX - YMIN
      DMAX = DMAX1( RAX,RAY )
C
      DO 60 I = 1,NTP
         PX( I ) = ( PX( I ) - XMIN ) / DMAX
         PY( I ) = ( PY( I ) - YMIN ) / DMAX
 60   CONTINUE
C
C******** DEFINE VERTEX AND ADJACENCY LISTS FOR SUPERTRIANGLE
C
      NELM = 1
      IA = KTJ + 1
      IB = KTJ + 2
      IC = KTJ + 3
C
      MTJ( 1,1 ) = IA
      MTJ( 1,2 ) = IB
      MTJ( 1,3 ) = IC
C
      JAC( 1,1 ) = 0
      JAC( 1,2 ) = 0
      JAC( 1,3 ) = 0
C
C******** SET COORDS OF SUPERTRIANGLE
C
      PX( IA ) = - 1.23D0
      PY( IA ) = - 0.50D0
      PX( IB ) =   2.23D0
      PY( IB ) = - 0.50D0
      PX( IC ) =   0.50D0
      PY( IC ) =   2.50D0
C
C******** ROUGH MESHES
C
      CALL ROUGH( NEX,NIN,IBEX,IBIN,IBNO,NTP,NIB,NODE,PX,PY,
     *     JNB,NEI,NELM,MTJ,JAC,IDM,LIST,IADRES,ISTACK,KV,IBR,
     *     MAP,KBD,KTE,KTJ,KCM )
C
      DO 70 I = 1, NODE
         IFIX( I ) = 1
 70   CONTINUE
C
C********* FINE MESHES
C
      CALL FINE( NODE,PX,PY,JNB,NEI,IFIX,NELM,MTJ,JAC,IDM,ISTACK,
     *     ANGL,NEDG,KSTACK,MAP,KTE,KTJ,KCM,NTOTAL )
C
C******** CHECK OF ELEMENTS FORMED
C
      IF( NELM.NE.2 * NODE + 1 ) THEN
         WRITE( *,* )' *** ERROR IN SUBROUTINE MODEL *** '
         WRITE( *,* )' *** INCORRECT NUMBER OF ELEMENTS *** '
         STOP
      END IF
C
C******** RELOCATE NODES USING BY THE GRID SMOOTHING METHOD
C
      CALL LAPLAS( NODE,NELM,IFIX,MTJ,PX,PY,JNB,NEI,KTE,KTJ,KCM )
C
C******** REMOVE ALL TRIANGLES OUTSIDE OF BOUNDARY
C
      CALL REMOVE( NEX,INDEX,NELM,MTJ,JAC,IDM,KBD,KTE )
C
C******** CHECK OF RESULTS
C
      CALL CHECK( NELM,MTJ,JAC,KTE )
C
C******** RESET X,Y-COORDS TO ORIGINAL VALUES
C
      DO 80 I = 1, NODE
         PX( I ) = PX( I ) * DMAX + XMIN
         PY( I ) = PY( I ) * DMAX + YMIN
 80   CONTINUE
C
      RETURN
      END

      
