C****************************************************************
C
C     COMPUTATION OF AREA               area.f
C
C****************************************************************
      FUNCTION AREA( IELM,MTJ,PX,PY,KTJ,KTE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( KTE,3 ),PX( KTJ + 3 ),PY( KTJ + 3 )
C
      J1 = MTJ( IELM,1 )
      J2 = MTJ( IELM,2 )
      J3 = MTJ( IELM,3 )
C
      AREA = 0.5D0 * ( PX( J1 ) * PY( J2 ) + PX( J2 ) * PY( J3 )
     *               + PX( J3 ) * PY( J1 ) - PX( J1 ) * PY( J3 )
     *               - PX( J2 ) * PY( J1 ) - PX( J3 ) * PY( J2 ) )
C
      RETURN
      END
