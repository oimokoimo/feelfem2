C*****************************************************************
C
C     OUTPUT OF DATA ( MID POINT )               output.f
C
C*****************************************************************
      SUBROUTINE OUTPUT( NODE,NELM,MTJ,JAC,IDM,NMP1,NMP2,MTJ1,MTJ2,
     &     PXY,KTJ,KTE,NEDG,IEDG,IBND,KTB,KTC )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PXY( KTJ*10,2 ),MTJ( KTE,4 ),JAC( KTE,4 ),IDM(KTE)
      DIMENSION MTJ1( KTE,4,10 ),MTJ2( KTE,16 )
      DIMENSION IEDG( KTB,6 ),IBND( KTB,KTC )
      DIMENSION IHEN( 10 ),INAK( 16 ),IWORK( 1000 )
C
      IFRM = 4
      IF ( JAC(1,4).LT.0 ) IFRM = 3
C
      OPEN(8,FILE='MESH.REF')
      OPEN(9,FILE='MESH.FIN')
C
      READ( 8,* ) IMESH
      DO 100 I=1,IMESH
         READ( 8,* ) NHEN
         IF ( NHEN.NE.0 ) READ( 8,* ) ( IHEN(II),II=1,NHEN )
         READ( 8,* ) NAKA
         IF ( NAKA.NE.0 ) READ( 8,* ) ( INAK(II),II=1,NAKA )
C
         NWORK = IFRM + NHEN*IFRM + NAKA
         WRITE( 9,* ) ' '
         WRITE( 9,* ) 'MESH'
         WRITE( 9,720 ) I,NELM,NWORK
         DO 110 J=1,NELM
            ICNT = 0
            DO 120 K=1,IFRM
               ICNT = ICNT + 1
               IWORK(ICNT) = MTJ(J,K)
 120        CONTINUE
            DO 130 K=1,IFRM
               DO 140 L=1,NHEN
                  ICNT = ICNT + 1
                  IWORK(ICNT) = MTJ1(J,K,IHEN(L))
 140           CONTINUE
 130        CONTINUE
            DO 150 K=1,NAKA
               ICNT = ICNT + 1
               IWORK(ICNT) = MTJ2(J,INAK(K))
 150        CONTINUE
C
            WRITE( 9,640 ) (IWORK(JJ),JJ=1,NWORK),IDM(J),J
 110     CONTINUE
 100  CONTINUE
C
      WRITE( 9,* ) ' '
      WRITE( 9,* ) 'BOUNDARY'
      WRITE( 9,610 ) NEDG
      DO 200 I=1,NEDG
         WRITE( 9,720 ) IEDG(I,1),IEDG(I,2),IEDG(I,5),IEDG(I,6)
         II = IEDG(I,5)
         ICNT = 0
         DO 210 J=1,(II-1)/10+1
            WRITE( 9,620 ) (IBND(I,K),K=ICNT+1,MIN(ICNT+10,II))
            ICNT = ICNT + 10
 210     CONTINUE
 200  CONTINUE
C
      WRITE( 9,* ) ' '
      WRITE( 9,* ) 'POINT'
      WRITE( 9,610 ) NODE
      WRITE( 9,630 )( PXY(I,1),PXY(I,2), I ,I = 1,NODE )
C
      CLOSE( 8 )
      CLOSE( 9 )
C
 610  FORMAT( 2I6 )
 620  FORMAT( 10I7 )
 630  FORMAT( 2E15.7 , I7 )
 640  FORMAT( 70I6 )
 720  FORMAT( 9I6 )
C
      RETURN
      E N D
