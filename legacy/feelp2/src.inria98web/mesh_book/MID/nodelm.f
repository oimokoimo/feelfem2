C******************************************************************
C
C     SEARCH FOR ELEMENTS AROUND A POINT ( Mid Point )   nodelm.f
C
C******************************************************************
      SUBROUTINE NODELM( NELM,NODE,MTJ,JAC,INE,JNE,KTJ,KTE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( KTE,4 ),JAC( KTE,4 ),INE( KTJ*10,40),JNE( KTJ*10)
C
      DO 100 I=1,NODE
         JNE(I) = 0
 100  CONTINUE
C
      DO 110 I=1,NELM
         DO 120 J=1,4
            IF ( JAC(I,J).LT.0 ) GOTO 120
            MIJ = MTJ(I,J)
            JNE(MIJ) = JNE(MIJ) + 1
            IF ( JNE(MIJ).GT.40 ) THEN
               WRITE(*,*) 'ERROR!! JNE COLUMN IS TOO SMALL.'
               STOP
            ENDIF
            INE(MIJ,JNE(MIJ)) = I
 120     CONTINUE
 110  CONTINUE
C
      RETURN
      E N D
