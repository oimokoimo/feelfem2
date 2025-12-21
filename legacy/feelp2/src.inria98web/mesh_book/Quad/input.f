C******************************************************************
C
C     INPUT OF DATA ( QUAD )          input.f 
C
C******************************************************************
      SUBROUTINE INPUT( NODE,NELM,MTJ,JAC,IDM,IFIX,PX,PY,KTJ,KTE,
     &     NEDG,IEDG,KTB )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PX( KTJ ),PY( KTJ ),MTJ( KTE,9 ),JAC( KTE,4 )
      DIMENSION IDM( KTE ),IFIX( KTJ ),IEDG( KTB,6 ),IWORK( 10 )
C
c      CHARACTER FNAME*12
C
c      WRITE( *,600 )
c 600  FORMAT( ' INPUT FILE NAME = ? ' )
c      READ( *,500 ) FNAME
c 500  FORMAT( A12 )
C
C      OPEN( 8,FILE = FNAME )
      OPEN( 8,FILE = 'MESH.PLN' )
      READ( 8,* ) NODE
      READ( 8,* )( PX( I ),PY( I ),IFIX( I ),IDMY,I = 1,NODE )
C
      NELM = 0
      READ( 8,* ) ISBD
      DO 100 II=1,ISBD
         READ( 8,* ) ITMP
         READ( 8,* ) IDMY
         MELM = NELM
         NELM = NELM + ITMP
         READ( 8,* )( ( MTJ( I,J ),J = 1,3 ),( JAC( I,J ),J = 1,3 ),
     *        IDM( I ),IDMY,I = MELM+1,NELM )
 100  CONTINUE
C
      READ ( 8,* ) NEDG
      DO 110 I=1,NEDG
         READ ( 8,* ) IEDG( I,1 ),IEDG( I,2 ),ITMP,IEDG( I,6 )
         ICNT = 0
         DO 120 J=1,(ITMP-1)/10+1
            READ ( 8,* ) (IWORK(K),K=1,MIN(10,ITMP-ICNT))
            IF ( J.EQ.1 ) IEDG( I,3 ) = IWORK(1)
            IF ( J.EQ.(ITMP-1)/10+1 ) IEDG ( I,4 ) = IWORK(ITMP-ICNT)
            ICNT = ICNT + 10
 120     CONTINUE
 110  CONTINUE
C
      CLOSE( 8 )
C
      RETURN
      E N D
