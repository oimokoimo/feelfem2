C*****************************************************************
C
C     OUTPUT OF DATA ( MID POINT )               output.f
C
C*****************************************************************
      SUBROUTINE OUTPUT( NNOD,NELM,MTJ,JAC,IDM,NMP1,NMP2,MTJ1,MTJ2,
     &     PXY,INE,JNE,JNT,INV,KTJ,KTE,NEDG,IEDG,IBND,KTB,KTC )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( KTE,4 ),JAC( KTE,4 ),IDM( KTE )
      DIMENSION MTJ1( KTE,4,10 ),MTJ2( KTE,16 )
      DIMENSION PXY( KTJ*10,2 ),INE( KTJ*10,40 ),JNE( KTJ*10 )
      DIMENSION JNT( KTJ*10 ),INV( KTJ*10 )
      DIMENSION IEDG( KTB,6 ),IBND( KTB,KTC ),IWORK( 1000 )
C
c      CHARACTER FNAME*12
C
c      WRITE( *,600 )
c 600  FORMAT( ' OUTPUT FILE NAME = ? ')
c      READ( *,500 ) FNAME
c 500  FORMAT( A12 )
C
c      OPEN(9,FILE=FNAME)
      OPEN(9,FILE='MESH.MID')
      WRITE( 9,610 ) NNOD
      WRITE( 9,630 )( PXY(INV(I),1) ,PXY(INV(I),2), I ,I = 1,NNOD )
C
      ISBD = 0
      DO 10 II=1,NELM
         IF ( IDM(II) .NE. ISBD ) THEN
            ISBD = ISBD + 1
            IF ( IDM(II) .NE. ISBD ) THEN
               WRITE(*,*) 'ERROR DETECTED IN OUTPUT.F'
               STOP
            ENDIF
            IWORK(ISBD) = II
         ENDIF
 10   CONTINUE
      IWORK(ISBD+1) = NELM + 1
C
      WRITE( 9,620 ) ISBD
      DO 20 II=1,ISBD
         IF ( JAC(IWORK(II),4).LT.0 ) THEN
            IFRM = 3
         ELSE
            IFRM = 4
         ENDIF
C
         WRITE( 9,620 ) IWORK(II+1)-IWORK(II)
         WRITE( 9,620 ) IFRM
         DO 30 I=IWORK(II),IWORK(II+1)-1
            WRITE( 9,620 ) (MTJ(I,J),J=1,IFRM),(JAC(I,J),J=1,IFRM),
     *           IDM(I),I
            IF ( NMP1.NE.0 ) THEN
               DO 40 J=1,IFRM
                  WRITE( 9,620 ) ( MTJ1(I,J,K),K=1,NMP1 )
 40            CONTINUE
            ENDIF
            IF ( NMP2.NE.0 ) WRITE( 9,620 ) ( MTJ2(I,J),J=1,NMP2 )
 30      CONTINUE
 20   CONTINUE
C
      DO 50 I=1,NEDG
         DO 60 J=1,IEDG(I,5)
            IBND(I,J) = JNT(IBND(I,J))
 60      CONTINUE
 50   CONTINUE
C
      WRITE( 9,610 ) NEDG
      DO 100 I=1,NEDG
         II = 0
         DO 110 J=1,IEDG(I,5)-1
            IST = IBND(I,J)
            IGL = IBND(I,J+1)
            DO 120 K=1,JNE(IST)
               IELM = INE(IST,K)
               DO 130 L=1,4
                  IF ( JAC(IELM,L).LT.0 ) GOTO 130
C
                  LST = MTJ(IELM,L)
                  IF ( L.EQ.4 ) THEN
                     LGL = MTJ(IELM,1)
                  ELSE
                     LGL = MTJ(IELM,L+1)
                  ENDIF
                  IF ( LST.EQ.IGL .AND. LGL.EQ.IST ) GOTO 1000
 130           CONTINUE
 120        CONTINUE
            WRITE(*,*) 'ERROR DETECTED AFTER DO 130 IN OUTPUT'
            STOP
C
 1000       CONTINUE
C
            II = II + 1
            IWORK(II) = IST
            DO 140 K=1,NMP1
               II = II + 1
               IWORK(II) = MTJ1(IELM,L,NMP1-K+1)
 140        CONTINUE
 110     CONTINUE
C
         II = II + 1
         IWORK(II) = IBND(I,IEDG(I,5))
C
         WRITE( 9,720 ) IEDG(I,1),IEDG(I,2),II,IEDG(I,6)
         ICNT = 0
         DO 150 J=1,(II-1)/10+1
            WRITE( 9,620 ) (IWORK(K),K=ICNT+1,MIN(ICNT+10,II))
            ICNT = ICNT + 10
 150     CONTINUE
 100  CONTINUE
C
 610  FORMAT( 2I7 )
 620  FORMAT( 16I7 )
 630  FORMAT( 2E15.7 , I7 )
 720  FORMAT( 9I7 )
C
      CLOSE( 9 )
C
      RETURN
      E N D
