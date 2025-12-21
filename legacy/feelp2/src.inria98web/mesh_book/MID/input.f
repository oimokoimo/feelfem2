C******************************************************************
C
C     INPUT OF DATA ( Mid Point )          input.f 
C
C******************************************************************
      SUBROUTINE INPUT( NODE,NELM,MTJ,JAC,IDM,PXY,KTJ,KTE,
     &     NEDG,IEDG,IBND,KTB,KTC,NMP1,VMP1,NMP2,VMP2 )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PXY( KTJ*10,2 ),MTJ( KTE,4 ),JAC( KTE,4 ),IDM( KTE )
      DIMENSION IEDG( KTB,6 ),IBND( KTB,KTC )
      DIMENSION VMP1(10),VMP2(16,2)
C
c      CHARACTER MNAME*12,PNAME*12
C
c      WRITE( *,600 )
c 600  FORMAT( ' INPUT MESH FILE NAME = ? ' )
c      READ( *,500 ) MNAME
c      WRITE( *,610 )
c 610  FORMAT( ' INPUT PARAMETER FILE NAME = ? ' )
c      READ( *,500 ) PNAME
c 500  FORMAT( A12 )
C
c      OPEN( 8,FILE = MNAME )
      OPEN( 8,FILE = 'MESH.PLN' )
      READ( 8,* ) NODE
      DO 10 I=1,NODE
         READ( 8,* ) PXY(I,1),PXY(I,2)
 10   CONTINUE
C
      DO 20 I=1,KTE
         JAC(I,4) = -1
 20   CONTINUE
C
      NELM = 0
      READ( 8,* ) ISBD
      DO 100 II=1,ISBD
         READ( 8,* ) ITMP
         READ( 8,* ) IFRM
         MELM = NELM
         NELM = NELM + ITMP
         READ( 8,* )(( MTJ(I,J),J=1,IFRM),(JAC(I,J),J=1,IFRM),
     *        IDM( I ),IDMY,I = MELM+1,NELM )
         IF ( IFRM.EQ.3 ) THEN
            DO 105 JJ=MELM+1,NELM
               MTJ(JJ,4) = MTJ(JJ,1)
 105        CONTINUE
         ENDIF
 100  CONTINUE
C
      READ ( 8,* ) NEDG
      DO 110 I=1,NEDG
         READ ( 8,* ) IEDG( I,1 ),IEDG( I,2 ),IEDG( I,5 ),IEDG( I,6 )
         II = IEDG(I,5)
         ICNT = 0
         DO 120 J=1,(II-1)/10+1
            READ ( 8,* ) (IBND(I,K),K=ICNT+1,MIN(ICNT+10,II))
            ICNT = ICNT + 10
 120     CONTINUE
 110  CONTINUE
C
      CLOSE( 8 )
C
c      OPEN( 8,FILE = PNAME )
      OPEN( 8,FILE = 'MESH.PRM' )
      READ( 8,* ) NMP1
      IF ( NMP1.NE.0 ) READ( 8,* ) (VMP1(I),I=1,NMP1)
      READ( 8,* ) NMP2
      IF ( NMP2.NE.0 ) THEN
         DO 200 I=1,NMP2
            READ( 8,* ) VMP2(I,1),VMP2(I,2)
 200     CONTINUE
      ENDIF
C
      CLOSE( 8 )
C
      RETURN
      E N D
