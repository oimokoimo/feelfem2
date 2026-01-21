C********************************************************
C
C     MAKE BOUNDARY NODE DATA       bndnod.f
C
C********************************************************
      SUBROUTINE BNDNOD( NEX,NIN,NODE,NELM,MTJ,JAC,IDM,
     &     JNT,IBEX,IBIN,IBNN,IBNO,KBD,KTJ )
C
      IMPLICIT REAL*8(A-H,O-Z)
C
c      PARAMETER ( MAXWRK = 4000 )
      PARAMETER ( MAXWRK = 20000 )
C
      DIMENSION MTJ( 2*KTJ + 1,3 ),JAC( 2*KTJ + 1,3 ),IDM( 2*KTJ + 1 )
      DIMENSION JNT( KTJ ),IBEX( KBD ),IBIN( KBD )
      DIMENSION IBNN( KBD,2,KTJ/100 ),IBNO( KBD,KTJ ),IWORK( MAXWRK )
C
      DO 10 I=1,MAXWRK
         IWORK(I) = 0
 10   CONTINUE
C
      NMAX = 0
      DO 100 I=1,NEX
         DO 110 J=1,IBEX(I)
            IBNN(I,1,J) = IBNO(I,J)
            NMAX = MAX(NMAX,IBNO(I,J))
 110     CONTINUE
         IBNN(I,1,IBEX(I)+1) = IBNO(I,1)
 100  CONTINUE
C
      DO 120 I=1,NIN
         DO 130 J=1,IBIN(I)
            IBNN(I,2,J) = NMAX + J
 130     CONTINUE
         IBNN(I,2,IBIN(I)+1) = NMAX + 1
         NMAX = NMAX + IBIN(I)
 120  CONTINUE
C
      JPNT = 1
      DO 140 I=1,NEX
         DO 150 J=JPNT,NELM
            IF ( IDM(J).NE.I ) THEN
               JPNT = J
               GOTO 1000
            ENDIF
C
            DO 160 K=1,3
               IF ( JAC(J,K).EQ.0 .OR. IDM(JAC(J,K)).NE.I ) THEN
                  KGL = MTJ(J,K)
                  IF ( K.EQ.3 ) THEN
                     KST = MTJ(J,1)
                  ELSE
                     KST = MTJ(J,K+1)
                  ENDIF
                  IWORK(KST) = KGL
               ENDIF
 160        CONTINUE
 150     CONTINUE
C
 1000    CONTINUE
C
         IBNODE = JNT(IBNN(I,1,1))
         DO 170 J=1,KTJ/2-1
            IBNO(I,J) = IBNODE
            NXTNOD = IWORK(IBNODE)
            IWORK(IBNODE) = 0
            IF ( NXTNOD.EQ.JNT(IBNN(I,1,1)) ) THEN
               IBNO(I,J+1) = NXTNOD
               GOTO 1010
            ELSE
               IBNODE = NXTNOD
            ENDIF
 170     CONTINUE
         WRITE(*,*) 'ERROR DETECTED IN SUBROUTINE BNDNOD!'
         STOP
C
 1010    CONTINUE
C
         DO 180 J=1,NIN
            IBNODE = JNT(IBNN(J,2,1))
            IF ( IWORK(IBNODE).EQ.0 ) GOTO 180
C
            DO 190 K=KTJ/2+1,KTJ-1
               IBNO(J,K) = IBNODE
               NXTNOD = IWORK(IBNODE)
               IWORK(IBNODE) = 0
               IF ( NXTNOD.EQ.JNT(IBNN(J,2,1)) ) THEN
                  IBNO(J,K+1) = NXTNOD
                  GOTO 180
               ELSE
                  IBNODE = NXTNOD
               ENDIF
 190        CONTINUE
            WRITE(*,*) 'ERROR DETECTED IN SUBROUTINE BNDNOD!'
            STOP
 180     CONTINUE
 140  CONTINUE
C
      DO 200 I=1,MAXWRK
         IF ( IWORK(I).NE.0 ) THEN
            WRITE(*,*) 'ERROR DETECTED IN DO 200 OF SUB BNDNOD !'
            STOP
         ENDIF
 200  CONTINUE
C
      RETURN
C
      E N D
