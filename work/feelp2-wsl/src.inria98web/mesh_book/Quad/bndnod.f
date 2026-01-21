      SUBROUTINE BNDNOD( NODE,NELM,MMTJ,JAC,IDMM,JNT,
     &     IEDG,IBND,KTJ,KTE,KTB,KTC,NEDG,IWORK )
C
      DIMENSION MMTJ( KTE,4 ),JAC( KTE,4 ),IDMM( KTE ), JNT( KTJ )
      DIMENSION IEDG( KTB,6 ),IBND( KTB,KTC ),IWORK( KTJ )
C
      DO 100 I=1,KTJ
         IWORK(I) = 0
 100  CONTINUE
      DO 105 I=1,NEDG
         IBND(I,1) = 0
 105  CONTINUE
C
      IDMNO = 1
      DO 110 I=1,NELM
         DO 120 J=1,4
            IF ( JAC(I,J).EQ.0 .OR. IDMM(JAC(I,J)).NE.IDMNO ) THEN
               JGL = MMTJ(I,J)
               IF ( J.EQ.4 ) THEN
                  JST = MMTJ(I,1)
               ELSE
                  JST = MMTJ(I,J+1)
               ENDIF
               IWORK(JST) = JGL
            ENDIF
 120     CONTINUE
C
         IF ( I.EQ.NELM .OR. IDMM(I+1).NE.IDMNO ) THEN
            DO 130 J=1,NEDG
               IF ( IEDG(J,6).NE.IDMNO .AND. IEDG(J,6).NE.0 ) GOTO 130
C
               IEST = JNT(IEDG(J,3))
               IEGL = JNT(IEDG(J,4))
C
               NXTNOD = IWORK(IEST)
               IF ( NXTNOD.EQ.0 ) GOTO 130
C
               IBND(J,1) = IEST
               IWORK(IBND(J,1)) = 0
C
               DO 140 K=2,KTC
                  IBND(J,K) = NXTNOD
                  IF ( IBND(J,K).EQ.IEGL ) THEN
                     IEDG(J,5) = K
                     GOTO 130
                  ENDIF
                  NXTNOD = IWORK(IBND(J,K))
                  IWORK(IBND(J,K)) = 0
 140           CONTINUE
               WRITE(*,*) 'ERROR DETECTED AFTER DO 140 IN BNDNOD'
               STOP
 130        CONTINUE
            IF ( I.NE.NELM ) IDMNO = IDMM(I+1)
         ENDIF
 110  CONTINUE
C
      DO 200 I=1,KTJ
         IF ( IWORK(I).NE.0 ) THEN
            WRITE(*,*) 'ERROR DETECTED IN DO 200 IN BNDNOD '
            STOP
         ENDIF
 200  CONTINUE
C
      DO 210 I=1,NEDG
         IF ( IBND(I,1).EQ.0 ) THEN
            WRITE(*,*) 'ERROR DETECTED IN DO 210 IN BNDNOD '
            STOP
         ENDIF
 210  CONTINUE
C
      RETURN
C
      E  N  D

