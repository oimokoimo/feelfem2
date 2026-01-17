C********************************************************
C
C     INPUT DATA       input.f
C
C********************************************************
      SUBROUTINE INPUT( NEX,NIN,IBEX,IBIN,IBNO,NOB,NIB,PX,PY,KBD,KTJ,
     &     IFORM,NTOTAL)
C
      IMPLICIT REAL*8(A-H,O-Z)
C
      DIMENSION IBEX( KBD ),IBIN( KBD ),IBNO( KBD,KTJ ),PX( KTJ + 3 )
      DIMENSION PY( KTJ + 3 )
C
      OPEN( 8,FILE = 'MESH.GEO' )
      READ( 8,* ) NEX,NIN
      IF( NEX.NE.0 ) THEN
         READ( 8,* )( IBEX( I ), I = 1,NEX )
      END IF
C
      IF( NIN.NE.0 ) THEN
         READ( 8,* )( IBIN( I ), I = 1,NIN )
c      ELSE
c         READ( 8,* ) IBIN( 1 )
      ENDIF
C
      DO 10 I = 1, NEX
         READ( 8,* )( IBNO( I,J ) , J = 1, IBEX( I ) )
 10   CONTINUE
C
      READ( 8,* ) NOB,NIB
C
      READ( 8,* )( PX( I ),PY( I ),I = 1, NOB+NIB )
C
      READ( 8,* ) IFORM
C
      READ( 8,* ) NTOTAL
C
      CLOSE( 8 )
C
      RETURN
      END
