C******************************************************************
C
C     RENUMBERING NODE NUMBER       renode.f
C
C******************************************************************
      SUBROUTINE RENODE( NNOD,NELM,MTJ,JAC,NMP1,NMP2,MTJ1,MTJ2,IORD
     &     ,JNT,INV,KTJ,KTE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ(KTE,4),JAC(KTE,4),MTJ1(KTE,4,10),MTJ2(KTE,16)
      DIMENSION IORD( KTE ),JNT( KTJ*10 ),INV( KTJ*10 )
C
      DO 10 I=1,NNOD
         JNT(I) = 0
         INV(I) = 0
 10   CONTINUE
C
      ICNT = 0
      DO 100 I=1,NELM
         II = IORD(I)
         DO 110 J=1,4
            IF ( JNT(MTJ(II,J)).NE.0 ) GOTO 110
            ICNT = ICNT + 1
            JNT(MTJ(II,J)) = ICNT
 110     CONTINUE
C
         DO 120 J=1,4
            IF ( JAC(II,J).LT.0 ) GOTO 120
            DO 130 K=1,NMP1
               IF ( JNT(MTJ1(II,J,K)).NE.0 ) GOTO 130
               ICNT = ICNT + 1
               JNT(MTJ1(II,J,K)) = ICNT
 130        CONTINUE
 120     CONTINUE
C
         DO 140 J=1,NMP2
            ICNT = ICNT + 1
            JNT(MTJ2(II,J)) = ICNT
 140     CONTINUE
 100  CONTINUE
C
      IF ( ICNT.NE.NNOD ) THEN
         WRITE(*,*) 'ERROR DETECTED AFTER DO 100 OF RENODE'
         STOP
      ENDIF
C
      DO 150 I=1,NNOD
         IF ( JNT(I).EQ.0 ) THEN
            WRITE(*,*) 'ERROR DETECTED IN DO 150 OF RENODE.'
            STOP
         ENDIF
         INV(JNT(I)) = I
 150  CONTINUE
C
      IBWD = 0
      DO 200 I=1,NELM
         IMIN = NNOD + 1
         IMAX = 0
         DO 210 J=1,4
            MTJ(I,J) = JNT(MTJ(I,J))
            IMIN = MIN(IMIN,MTJ(I,J))
            IMAX = MAX(IMAX,MTJ(I,J))
 210     CONTINUE
C
         DO 220 J=1,4
            IF ( JAC(I,J).LT.0 ) GOTO 220
            DO 230 K=1,NMP1
               MTJ1(I,J,K) = JNT(MTJ1(I,J,K))
               IMIN = MIN(IMIN,MTJ1(I,J,K))
               IMAX = MAX(IMAX,MTJ1(I,J,K))
 230        CONTINUE
 220     CONTINUE
C
         DO 240 J=1,NMP2
            MTJ2(I,J) = JNT(MTJ2(I,J))
            IMIN = MIN(IMIN,MTJ2(I,J))
            IMAX = MAX(IMAX,MTJ2(I,J))
 240     CONTINUE
         IBWD = MAX(IBWD,IMAX-IMIN+1)
 200  CONTINUE
C
c      WRITE(*,*) ' '
c      WRITE(*,*) 'NEW BAND WIDTH = ',IBWD
c      WRITE(*,*) ' '
C
      RETURN
      E N D
