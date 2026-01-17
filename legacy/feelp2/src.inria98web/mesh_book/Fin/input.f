C******************************************************************
C
C     INPUT OF DATA ( Mid Point )          input.f 
C
C******************************************************************
      SUBROUTINE INPUT( NODE,NELM,MTJ,JAC,IDM,PXY,KTJ,KTE,
     &     NEDG,IEDG,IBND,KTB,KTC,NMP1,NMP2,VMP1,VMP2,MTJ1,MTJ2 )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PXY( KTJ*10,2 ),MTJ( KTE,4 ),JAC( KTE,4 ),IDM( KTE )
      DIMENSION IEDG( KTB,6 ),IBND( KTB,KTC )
      DIMENSION VMP1(10),VMP2(16,2),MTJ1( KTE,4,10 ),MTJ2( KTE,16 )
C
      OPEN( 8,FILE = 'MESH.PRM' )
C
      READ( 8,* ) NMP1
      IF ( NMP1.NE.0 ) READ( 8,* ) (VMP1(I),I=1,NMP1)
      READ( 8,* ) NMP2
      IF ( NMP2.NE.0 ) THEN
         DO 10 I=1,NMP2
            READ( 8,* ) VMP2(I,1),VMP2(I,2)
 10      CONTINUE
      ENDIF
C
      CLOSE( 8 )
C
      OPEN( 8,FILE = 'MESH.MID' )
C
      READ( 8,* ) NODE
      DO 20 I=1,NODE
         READ( 8,* ) PXY(I,1),PXY(I,2),IDMY
 20   CONTINUE
C
      DO 30 I=1,KTE
         JAC(I,4) = -1
 30   CONTINUE
C
      NELM = 0
      READ( 8,* ) ISBD
      DO 100 II=1,ISBD
         READ( 8,* ) ITMP
         READ( 8,* ) IFRM
         MELM = NELM
         NELM = NELM + ITMP
         DO 110 I=MELM+1,NELM 
            READ( 8,* ) (MTJ(I,J),J=1,IFRM),(JAC(I,J),J=1,IFRM),
     *           IDM( I ),IDMY
            IF ( NMP1.NE.0 ) THEN
               DO 120 K=1,IFRM
                  READ( 8,* ) ( MTJ1(I,K,KK),KK=1,NMP1 )
 120           CONTINUE
            ENDIF
            IF ( NMP2.NE.0 ) READ( 8,* ) ( MTJ2(I,KK),KK=1,NMP2 )
 110     CONTINUE
 100  CONTINUE
C
      READ ( 8,* ) NEDG
      DO 130 I=1,NEDG
         READ ( 8,* ) IEDG( I,1 ),IEDG( I,2 ),IEDG( I,5 ),IEDG( I,6 )
         II = IEDG(I,5)
         ICNT = 0
         DO 140 J=1,(II-1)/10+1
            READ ( 8,* ) (IBND(I,K),K=ICNT+1,MIN(ICNT+10,II))
            ICNT = ICNT + 10
 140     CONTINUE
 130  CONTINUE
C
      CLOSE( 8 )
C      
      RETURN
      E N D

