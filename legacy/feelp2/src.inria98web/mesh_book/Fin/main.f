C*********************************************************************
C
C     REFORM DATA         main.f
C
C*********************************************************************
      PROGRAM REFORM
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      PARAMETER( KTJ = 20000 )
      PARAMETER( KTE = 20000 )
      PARAMETER( KTB = 100 )
      PARAMETER( KTC = 500 )
C
      DIMENSION PXY( KTJ*10,2 ),MTJ( KTE,4 ),JAC( KTE,4 ),IDM( KTE )
      DIMENSION IEDG( KTB,6 ),IBND( KTB,KTC )
      DIMENSION VMP1( 10 ),VMP2( 16,2 ),MTJ1( KTE,4,10 ),MTJ2( KTE,16 )
C
      CALL INPUT( NODE,NELM,MTJ,JAC,IDM,PXY,KTJ,KTE,
     &     NEDG,IEDG,IBND,KTB,KTC,NMP1,NMP2,VMP1,VMP2,MTJ1,MTJ2 )
C
      CALL OUTPUT( NODE,NELM,MTJ,JAC,IDM,NMP1,NMP2,MTJ1,MTJ2,
     &     PXY,KTJ,KTE,NEDG,IEDG,IBND,KTB,KTC )
C
      STOP
      E N D
