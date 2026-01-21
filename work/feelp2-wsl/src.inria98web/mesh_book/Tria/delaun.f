C*****************************************************************
C
C     DELAUNAY TRIANGULATION          delaun.f
C
C****************************************************************
      SUBROUTINE DELAUN( IZ,IS,IG,NTP,PX,PY,JNB,NEI,NELM,MTJ,
     *     JAC,IDM,IADRES,ISTACK,KTE,KTJ,KCM )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PX( KTJ + 3 ),PY( KTJ + 3 ),JNB( KTJ ),NEI( KTJ,KCM )
      DIMENSION JAC( KTE,3 ),IDM( KTE ),IADRES( KTJ + 3 )
      DIMENSION MTJ( KTE,3 ),ISTACK( KTJ )
C
      ITOP = 0
      MAXSTK = NTP
      DO 100 I = IS, IG
         IP = I 
         XP = PX( IP )
         YP = PY( IP )
C
         CALL LOCATE( XP,YP,PX,PY,MTJ,JAC,NELM,KTE,KTJ,IT )
C
         IF( IDM( IT ).NE.IZ ) THEN
            WRITE( *,* )' *** ERROR IN SUBROUTINE DELAUN *** '
            WRITE( *,* )' *** NEW POINT EXISTS OUTSIDE   *** '
            STOP
         ENDIF
C
         IA = JAC( IT,1 )
         IB = JAC( IT,2 )
         IC = JAC( IT,3 )
C
         IV1 = MTJ( IT,1 )
         IV2 = MTJ( IT,2 )
         IV3 = MTJ( IT,3 )
C
         MTJ( IT,1 ) = IP
         MTJ( IT,2 ) = IV1
         MTJ( IT,3 ) = IV2
C
         JAC( IT,1 ) = NELM + 2
         JAC( IT,2 ) = IA
         JAC( IT,3 ) = NELM + 1
C
         NELM = NELM + 1
C
         IDM( NELM ) = IZ
C
         MTJ( NELM,1 ) = IP
         MTJ( NELM,2 ) = IV2
         MTJ( NELM,3 ) = IV3
C
         JAC( NELM,1 ) = IT
         JAC( NELM,2 ) = IB
         JAC( NELM,3 ) = NELM + 1
C
         NELM = NELM + 1
C
         IDM( NELM ) = IZ
C
         MTJ( NELM,1 ) = IP
         MTJ( NELM,2 ) = IV3
         MTJ( NELM,3 ) = IV1
C
         JAC( NELM,1 ) = NELM - 1
         JAC( NELM,2 ) = IC 
         JAC( NELM,3 ) = IT
C
         CALL INCR( IV1,NELM,JNB,NEI,KTJ,KCM )
         CALL INCR( IV2,NELM - 1,JNB,NEI,KTJ,KCM )
C
         IF( IV3.LE.KTJ ) THEN
            NEI( IV3,NEIBOR( IV3,IT,JNB,NEI,KTJ,KCM ) ) = NELM - 1
         ENDIF
C
         CALL INCR( IV3,NELM,JNB,NEI,KTJ,KCM )
C
         JNB( IP ) = 3
C
         NEI( IP,1 ) = IT
         NEI( IP,2 ) = NELM - 1
         NEI( IP,3 ) = NELM
C
         IF( IA.NE.0 ) THEN
            MS = IADRES( IV1 ) * IADRES( IV2 )
            IDF = IABS( IADRES( IV1 ) - IADRES( IV2 ) )
            IF( ( IDM( IA ).EQ.IZ ).AND.
     *           ( ( MS.EQ.0 ).OR.( IDF.NE.1 ) ) ) THEN
               ITOP = ITOP + 1
               ISTACK( ITOP ) = IPUSH( IT,MAXSTK,ITOP,ISTACK,KTJ )
            ENDIF
C
         ENDIF
C
         IF( IB.NE.0 ) THEN
            CALL EDGE( IB,IT,JAC,KTE,IEDGE )
            JAC( IB,IEDGE ) = NELM - 1
            MS = IADRES( IV2 ) * IADRES( IV3 )
            IDF = IABS( IADRES( IV2 ) - IADRES( IV3 ) )
            IF( ( IDM( IB ).EQ.IZ ).AND.( ( MS.EQ.0 )
     *           .OR.( IDF.NE.1 ) ) ) THEN
               ITOP = ITOP + 1
               ISTACK(ITOP) = IPUSH( NELM-1,MAXSTK,ITOP,ISTACK,KTJ )
            ENDIF
         ENDIF
C

         IF( IC.NE.0 ) THEN
            CALL EDGE( IC,IT,JAC,KTE,IEDGE )
            JAC( IC,IEDGE ) = NELM
            MS = IADRES( IV3 ) * IADRES( IV1 )
            IDF = IABS( IADRES( IV3 ) - IADRES( IV1 ) )
            IF( ( IDM( IC ).EQ.IZ ).AND.
     *           ( ( MS.EQ.0 ).OR.( IDF.NE.1 ) ) ) THEN
               ITOP = ITOP + 1
               ISTACK( ITOP ) = IPUSH( NELM,MAXSTK,ITOP,ISTACK,KTJ )
            ENDIF
         ENDIF
C
 50      IF( ITOP.GT.0 ) THEN
            IL = ISTACK( ITOP )
            ITOP = ITOP - 1
            IR = JAC( IL,2 )
C
            CALL EDGE( IR,IL,JAC,KTE,IERL )
            IERA = MOD( IERL,3 ) + 1
            IERB = MOD( IERA,3 ) + 1
c
            IV1 = MTJ( IR,IERL )
            IV2 = MTJ( IR,IERA )
            IV3 = MTJ( IR,IERB )
C
            CALL SWAP( PX( IV1 ),PY( IV1 ),PX( IV2 ),PY( IV2 ),
     *           PX( IV3 ),PY( IV3 ),XP,YP,ISWAP )
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
                  MS = IADRES( IV2 ) * IADRES( IV3 )
                  IDF = IABS( IADRES( IV2 ) - IADRES( IV3 ) )
                  IF( ( IDM( IA ).EQ.IZ ).AND.
     *                 ( ( MS.EQ.0 ).OR.( IDF.NE.1 ) ) ) THEN
                     ITOP = ITOP + 1
                     ISTACK(ITOP) = IPUSH( IL,MAXSTK,ITOP,ISTACK,KTJ )
                  ENDIF
C
               ENDIF
C
               IF( IB.NE.0 ) THEN
                  MS = IADRES( IV3 ) * IADRES( IV1 )
                  IDF = IABS( IADRES( IV3 ) - IADRES( IV1 ) )
                  IF( ( IDM( IB ).EQ.IZ ).AND.
     *                 ( ( MS.EQ.0 ).OR.( IDF.NE.1 ) ) ) THEN
                     ITOP = ITOP + 1
                     ISTACK(ITOP) = IPUSH( IR,MAXSTK,ITOP,ISTACK,KTJ )
                  ENDIF
C
               ENDIF
C
               IF( IC.NE.0 ) THEN
                  CALL EDGE( IC,IL,JAC,KTE,IEDGE )
                  JAC( IC,IEDGE ) = IR
               ENDIF
C
            ENDIF
C
            GOTO 50
         ENDIF
C
 100  CONTINUE
C
      RETURN
      END

               
               
