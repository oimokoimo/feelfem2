C********************************************************************
C
C     SUBDIVIDE GIVEN DOMAIN BY NEW DATA POINT       remesh.f
C
C********************************************************************
      SUBROUTINE REMESH( IELM,IED,JELM,JED,NODE,PX,PY,JNB,NEI,NELM,
     *     MTJ,JAC,IDM,ISTACK,KTE,KTJ,KCM )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PX( KTJ + 3 ),PY( KTJ + 3 ),JNB( KTJ ),NEI( KTJ,KCM )
      DIMENSION JAC( KTE,3 ),IDM( KTE ),ISTACK( KTJ ),MTJ( KTE,3 )
C
      ITOP = 0
      MAXSTK = NODE
      IP = NODE
      XP = PX( IP )
      YP = PY( IP )
C
      IBJ = MOD( IED,3 ) + 1
      JBJ = MOD( JED,3 ) + 1
      IA = JAC( IELM,IBJ )
      IB = JAC( IELM,MOD( IBJ,3 ) + 1 )
      IC = JAC( JELM,JBJ )
      ID = JAC( JELM,MOD( JBJ,3 ) + 1 )
C
      IV1 = MTJ( IELM,IBJ )
      IV2 = MTJ( IELM,MOD( IBJ,3 ) + 1 )
      IV3 = MTJ( JELM,JBJ )
      IV4 = MTJ( JELM,MOD( JBJ,3 ) + 1 )
C
      MTJ( IELM,1 ) = IP
      MTJ( IELM,2 ) = IV1
      MTJ( IELM,3 ) = IV2
C
      JAC( IELM,1 ) = NELM + 2
      JAC( IELM,2 ) = IA
      JAC( IELM,3 ) = NELM + 1
C
      NELM = NELM + 1
      IDM( NELM ) = IDM( IELM )
C
      MTJ( NELM,1 ) = IP
      MTJ( NELM,2 ) = IV2
      MTJ( NELM,3 ) = IV3
C
      JAC( NELM,1 ) = IELM 
      JAC( NELM,2 ) = IB
      JAC( NELM,3 ) = JELM 
C
      MTJ( JELM,1 ) = IP
      MTJ( JELM,2 ) = IV3
      MTJ( JELM,3 ) = IV4
C
      JAC( JELM,1 ) = NELM 
      JAC( JELM,2 ) = IC
      JAC( JELM,3 ) = NELM + 1
C
      NELM = NELM + 1
      IDM( NELM ) = IDM ( JELM )
C
      MTJ( NELM,1 ) = IP
      MTJ( NELM,2 ) = IV4
      MTJ( NELM,3 ) = IV1
C
      JAC( NELM,1 ) = JELM 
      JAC( NELM,2 ) = ID
      JAC( NELM,3 ) = IELM 
C
      IF( IV1.LE.KTJ ) THEN
         NEI( IV1,NEIBOR( IV1,JELM,JNB,NEI,KTJ,KCM ) ) = NELM
      ENDIF
C
      CALL INCR( IV2,NELM-1,JNB,NEI,KTJ,KCM )
C
      IF( IV3.LE.KTJ ) THEN
         NEI( IV3,NEIBOR( IV3,IELM,JNB,NEI,KTJ,KCM ) ) = NELM - 1
      ENDIF
C
      CALL INCR( IV4,NELM,JNB,NEI,KTJ,KCM )
C
      JNB( IP ) = 4
      NEI( IP,1 ) = IELM
      NEI( IP,2 ) = NELM - 1
      NEI( IP,3 ) = JELM
      NEI( IP,4 ) = NELM
C
      IF( IA.NE.0 ) THEN
         IF( IDM( IA ).EQ.IDM( IELM ) ) THEN
            ITOP = ITOP + 1
            ISTACK( ITOP ) = IPUSH( IELM,MAXSTK,ITOP,ISTACK,KTJ )
         ENDIF
      ENDIF
C
      IF( IB.NE.0 ) THEN
         CALL EDGE( IB,IELM,JAC,KTE,IEDGE )
         JAC( IB,IEDGE ) = NELM - 1
         IF( IDM( IB ).EQ.IDM( NELM-1 ) ) THEN
            ITOP = ITOP + 1
            ISTACK( ITOP ) = IPUSH( NELM-1, MAXSTK,ITOP,ISTACK,KTJ )
         ENDIF
      ENDIF
C
      IF( IC.NE.0 ) THEN
         IF( IDM( IC ).EQ.IDM( JELM ) ) THEN
            ITOP = ITOP + 1
            ISTACK( ITOP ) = IPUSH( JELM,MAXSTK,ITOP,ISTACK,KTJ )
         ENDIF
      ENDIF
C
      IF( ID.NE.0 ) THEN
         CALL EDGE( ID,JELM,JAC,KTE,IEDGE )
         JAC( ID,IEDGE ) = NELM
         IF( IDM( ID ).EQ.IDM( NELM ) ) THEN
            ITOP = ITOP + 1
            ISTACK( ITOP ) = IPUSH( NELM,MAXSTK,ITOP,ISTACK,KTJ )
         ENDIF
      ENDIF
C
 10   IF( ITOP.GT.0 ) THEN
         IL = ISTACK( ITOP )
         ITOP = ITOP - 1
         IR = JAC( IL,2 )
C
         CALL EDGE( IR,IL,JAC,KTE,IERL )
         IERA = MOD( IERL,3 ) + 1
         IERB = MOD( IERA,3 ) + 1
C
         IV1 = MTJ( IR,IERL )
         IV2 = MTJ( IR,IERA )
         IV3 = MTJ( IR,IERB )
C
         CALL SWAP( PX( IV1 ),PY( IV1 ),PX( IV2 ),PY( IV2 ),
     *        PX( IV3 ),PY( IV3 ),XP,YP,ISWAP )
C
         IF( ISWAP.EQ.1 ) THEN
            IA = JAC( IR,IERA )
            IB = JAC( IR,IERB )
            IC = JAC( IL,3 )
C
            MTJ( IL,3 ) = IV3
            JAC( IL,2 ) = IA
            JAC( IL,3 ) = IR
C
            MTJ( IR,1 ) = IP
            MTJ( IR,2 ) = IV3
            MTJ( IR,3 ) = IV1
C
            JAC( IR,1 ) = IL
            JAC( IR,2 ) = IB
            JAC( IR,3 ) = IC
C
            CALL DECR( IV1,IL,JNB,NEI,KTJ,KCM )
            CALL DECR( IV2,IR,JNB,NEI,KTJ,KCM )
            CALL INCR( IP,IR,JNB,NEI,KTJ,KCM )
            CALL INCR( IV3,IL,JNB,NEI,KTJ,KCM )
C
            IF( IA.NE.0 ) THEN
               CALL EDGE( IA,IR,JAC,KTE,IEDGE )
               JAC( IA,IEDGE ) = IL
               IF( IDM( IA ).EQ.IDM( IL ) ) THEN
                  ITOP = ITOP + 1
                  ISTACK( ITOP ) = IPUSH( IL,MAXSTK,ITOP,ISTACK,KTJ )
               ENDIF
            ENDIF
C
            IF( IB.NE.0 ) THEN
               IF( IDM( IB ).EQ.IDM( IR ) ) THEN
                  ITOP = ITOP + 1
                  ISTACK( ITOP ) = IPUSH( IR,MAXSTK,ITOP,ISTACK,KTJ )
               ENDIF
            ENDIF
C
            IF( IC.NE.0 ) THEN
c               write(*,*) 'in remesh.f before edge11'
               CALL EDGE( IC,IL,JAC,KTE,IEDGE )
               JAC( IC,IEDGE ) = IR
            ENDIF
         ENDIF
c         write(*,*) 'in remesh.f after if iswap eq 1'
         GOTO 10
      ENDIF
C
      RETURN
      END



