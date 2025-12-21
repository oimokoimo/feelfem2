C********************************************************************
C
C     PLACE ITEM ON LIFO STACK AND INCREMENT STACK SIZE     ipush.f
C
C********************************************************************
      FUNCTION IPUSH( ITEM,MAXSTK,ITOP,ISTACK,NNN )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION ISTACK( NNN )
C
      IF( ITOP.GT.MAXSTK ) THEN
         WRITE( *,* )' *** ERROR IN SUBROUTINE IPUSH *** '
         WRITE( *,* )' ******** STACK OVERFLOW ******** '
         STOP
      ENDIF
C
      IPUSH = ITEM
C
      RETURN
      END
