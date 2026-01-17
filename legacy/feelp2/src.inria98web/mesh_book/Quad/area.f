C*****************************************************************
C
C     COMPUTATION OF AREA                     area.f
C
C*****************************************************************
      FUNCTION AREA( KTE,KTJ,IELM,MTJ,PX,PY )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( KTE,4 ),PX( KTJ ),PY ( KTJ )
C
      J1 = MTJ( IELM,1 )
      J2 = MTJ( IELM,2 )
      J3 = MTJ( IELM,3 )
      J4 = MTJ( IELM,4 )
C
      AREA1 = 0.5D0 * ( PX( J1 ) * PY( J2 ) + PX( J2 ) * PY( J3 )
     *                 +PX( J3 ) * PY( J1 ) - PX( J1 ) * PY( J3 )
     *                 -PX( J2 ) * PY( J1 ) - PX( J3 ) * PY( J2 ) )
      AREA2 = 0.5D0 * ( PX( J1 ) * PY( J3 ) + PX( J3 ) * PY( J4 )
     *                 +PX( J4 ) * PY( J1 ) - PX( J1 ) * PY( J4 )
     *                 -PX( J3 ) * PY( J1 ) - PX( J4 ) * PY( J3 ) )
C
      AREA = AREA1 + AREA2
C
      RETURN
      END

