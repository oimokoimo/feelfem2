C****************************************************************
C
C     FINE TRIANGULATION BY INSERTING NRE POINT       fine.f
C
C****************************************************************
      SUBROUTINE FINE( NODE,PX,PY,JNB,NEI,IFIX,NELM,MTJ,JAC,IDM,
     *     ISTACK,ANGL,NEDG,KSTACK,MAP,KTE,KTJ,KCM,NTOTAL )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PX( KTJ + 3 ),PY( KTJ + 3 ),JNB( KTJ ),NEI( KTJ,KCM )
      DIMENSION JAC( KTE,3 ),IDM( KTE ),ANGL( KTE ),NEDG( KTE )
      DIMENSION IFIX( KTJ ),ISTACK( KTJ ),MAP( KTE ),MTJ( KTE,3 )
      DIMENSION KSTACK( KTE )
C
C******* IMPUT DATA
C
      IF( NODE.GE.NTOTAL ) GOTO 180
C
C******* INITIALIZATION
C
      ALMT = 1.D0 / REAL( NTOTAL )
 20   ALMT = 0.5D0 * ALMT
      NEIB = 0
      DO 30 I = 1,KTE
         ANGL( I ) = 0.D0
         NEDG( I ) = 0
         KSTACK( I ) = 0
 30   CONTINUE
C
C******* COMPUTE DISTORSION RATE FOR EACH ELEMENT
C
      DO 40 I = 1,NELM
c         write(*,*) 'idm ',i,idm(i)
         IF( IDM( I ).NE.0 ) THEN
            IELM = I
            NEIB = NEIB + 1
            KSTACK( NEIB ) = IELM
            CALL DISTOR( IELM,MTJ,PX,PY,DRATE,JEDG,KTE,KTJ )
            S = AREA( IELM,MTJ,PX,PY,KTJ,KTE )
            ANGL( IELM ) = DRATE
            NEDG( IELM ) = JEDG
         ENDIF
 40   CONTINUE
C
C******* ARRANGE TO DESCENDING ORDER
C 
      DO 50 I = 1, NEIB - 1
         K = KSTACK( I )
         XX = ANGL( K ) 
         II = I + 1
         L = I
         DO 60 J = II , NEIB
            KK = KSTACK( J )
            IF( ANGL( KK ).LE.XX ) GOTO 60
            XX = ANGL( KK )
            L = J
 60      CONTINUE
C
         MM = KSTACK( I )
         KSTACK( I ) = KSTACK( L )
         KSTACK( L ) = MM
 50   CONTINUE
c
c      write(*,*) 'neib = ',neib
c      do 111 ijkl=1,neib
c         write(*,*) 'kstack  angl',kstack(ijkl),angl(kstack(ijkl))
c 111  continue
C
C******* SUBDIVISION START
C
 70   IF( NEIB.EQ.0 ) GOTO 20
c      IF( ANGL( KSTACK( 1 ) ).LT.1.D0 ) GOTO 20
      IF( NODE.LT.NTOTAL ) THEN
         IELM = KSTACK( 1 )
         IED = NEDG( IELM )
         JELM = JAC( IELM,IED )
         CALL EDGE( JELM,IELM,JAC,KTE,JED )
C
         IV1 = MTJ( IELM,IED )
         IV2 = MTJ( IELM,MOD( IED,3 ) + 1 )
         NODE = NODE + 1
C
         PX( NODE ) = ( PX( IV1 ) + PX( IV2 ) ) / 2.D0
         PY( NODE ) = ( PY( IV1 ) + PY( IV2 ) ) / 2.D0
C
C******* REMESH BY INSERTION OF POINT
C
         CALL REMESH( IELM,IED,JELM,JED,NODE,PX,PY,JNB,NEI,NELM,MTJ,
     *        JAC,IDM,ISTACK,KTE,KTJ,KCM )
C
C******* NODE RELOCATION BY THE LAPLACIAN METHOD
C
         IF( IDM( IELM ).NE.IDM( JELM ) ) THEN
            IFIX( NODE ) = 1
         ELSE
            GX = 0.D0
            GY = 0.D0
            AR = 0.D0
            DO 80 J = 1,JNB( NODE )
               KELM = NEI( NODE,J )
               S = AREA( KELM,MTJ,PX,PY,KTJ,KTE )
               J1 = MTJ(KELM,1)
               J2 = MTJ(KELM,2)
               J3 = MTJ(KELM,3)
               XC = ( PX( J1 ) + PX( J2 ) + PX( J3 ) ) / 3.D0
               YC = ( PY( J1 ) + PY( J2 ) + PY( J3 ) ) / 3.D0
C
               AR = AR + S
               GX = GX + S * XC
               GY = GY + S * YC
 80         CONTINUE
C
            CGRAX = GX / AR
            CGRAY = GY / AR
C
            XKP = PX( NODE )
            YKP = PY( NODE )
            PX( NODE ) = CGRAX
            PY( NODE ) = CGRAY
C
            DO 90 J = 1,JNB( NODE )
               KELM = NEI( NODE,J )
               S = AREA( KELM,MTJ,PX,PY,KTJ,KTE )
               IF( S.LE.( 0.1 * ALMT ) ) THEN
                  PX( NODE ) = XKP
                  PY( NODE ) = YKP
                  GOTO 100
               ENDIF
 90         CONTINUE
 100        CONTINUE
         ENDIF
C
         DO 110 I = 1,NELM
            MAP( I ) = 1
 110     CONTINUE
C
         DO 120 I = 1,JNB( NODE )
            LELM = NEI( NODE , I )
            MAP( LELM ) = 0
            ANGL( LELM ) = 0
            NEDG( LELM ) = 0
 120     CONTINUE
C
         NN = 0
         DO 130 I = 1,NEIB
            IF( MAP( KSTACK( I ) ).EQ.1 ) THEN
               NN = NN + 1
               KSTACK( NN ) = KSTACK( I )
            ENDIF
 130     CONTINUE
C
         NEIB = NN
C
         DO 140 I = 1,JNB( NODE )
            MELM = NEI( NODE,I )
            S = AREA( MELM,MTJ,PX,PY,KTJ,KTE )
            IF( ( S.GT.ALMT ).AND.(IDM( MELM ).NE.0 ) ) THEN
               CALL DISTOR( MELM,MTJ,PX,PY,DRATE,JEDG,KTE,KTJ )
               ANGL( MELM ) = DRATE
               NEDG( MELM ) = JEDG
C
               IF ( NEIB.LE.0 ) THEN
                  NEIB = 1
                  KSTACK( NEIB ) = MELM
               ELSE IF( DRATE.GT.ANGL( KSTACK( 1 ) ) ) THEN
                  DO 150 J = 1,NEIB
                     KSTACK( NEIB - J + 2 ) = KSTACK( NEIB - J + 1 )
 150              CONTINUE
                  NEIB = NEIB + 1
                  KSTACK( 1 ) = MELM
               ELSE IF( DRATE.LE.ANGL( KSTACK( NEIB ) ) ) THEN
                  NEIB = NEIB + 1
                  KSTACK( NEIB ) = MELM
               ELSE
                  LS = 1
                  LE = NEIB
 160              IF( ( LE - LS ).NE.1 ) THEN
                     LM = ( LS + LE ) / 2
                     IF( DRATE.GT.ANGL( KSTACK( LM ) ) ) THEN
                        LE = LM
                     ELSE
                        LS = LM
                     ENDIF
                     GOTO 160
                  ENDIF
C
                  DO 170 K = NEIB,LE,-1
                     KSTACK( K + 1 ) = KSTACK( K )
 170              CONTINUE
C
                  NEIB = NEIB + 1
                  KSTACK( LE ) = MELM
               ENDIF
            ENDIF
 140     CONTINUE
         GOTO 70
      ENDIF
C
 180  RETURN
      END

