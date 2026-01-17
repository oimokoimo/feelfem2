C*****************************************************************
C
C     OUTPUT OF DATA ( RELOCATE )               output.f
C
C*****************************************************************
      SUBROUTINE OUTPUT( NODE,NELM,MMTJ,JAC,IDMM,PX,PY,IFIX,
     &     IEDG,IBND,KTJ,KTE,KTB,KTC,NEDG)
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MMTJ( KTE,4 ),JAC( KTE,4 ),IDMM( KTE )
      DIMENSION PX( KTJ ),PY( KTJ ),IFIX( KTJ )
      DIMENSION IEDG( KTB,6 ),IBND( KTB,KTC ),IWORK(20)
C
c      CHARACTER FNAME*12
C
c      WRITE( *,600 )
c 600  FORMAT( ' OUTPUT FILE NAME = ? ')
c      READ( *,500 ) FNAME
c 500  FORMAT( A12 )
C
c      OPEN(9,FILE=FNAME)
      OPEN(9,FILE='MESH.PLN')
      WRITE( 9,610 ) NODE
      WRITE( 9,630 )( PX( I ) ,PY( I ), I ,I = 1,NODE )
C
      ISBD = 0
      DO 10 II=1,NELM
         IF ( IDMM(II) .NE. ISBD ) THEN
            ISBD = ISBD + 1
            IF ( IDMM(II) .NE. ISBD ) THEN
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
         WRITE( 9,620 ) IWORK(II+1)-IWORK(II)
         WRITE( 9,620 ) 4
         WRITE( 9,620 )( ( MMTJ( I,J ),J = 1,4 ),( JAC( I,J ),J = 1,4 ),
     *        IDMM(I),I,I = IWORK(II),IWORK(II+1)-1 )
 20   CONTINUE
C
      WRITE( 9,610 ) NEDG
      DO 100 I=1,NEDG
         WRITE( 9,720 ) IEDG(I,1),IEDG(I,2),IEDG(I,5),IEDG(I,6)
         II = IEDG(I,5)
         ICNT = 0
         DO 110 J=1,(II-1)/10+1
            WRITE( 9,730 ) (IBND(I,K),K=ICNT+1,MIN(ICNT+10,II))
            ICNT = ICNT + 10
 110     CONTINUE
 100  CONTINUE
C
 610  FORMAT( 2I6 )
 620  FORMAT( 4I6 ,I8,I6,I6,I6,I6,I7)
 630  FORMAT( 2E15.7 , I7 )
 720  FORMAT( 9I6 )
 730  FORMAT( 10I7 )
      CLOSE( 9 )
C
      RETURN
      E N D

