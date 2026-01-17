C*********************************************************************
C
C     GENERATION OF MID POINT IN ELEMENT   newpnt.f
C
C*********************************************************************
      SUBROUTINE NEWPNT( NODE,NELM,MTJ,JAC,PXY,KTJ,KTE,
     &     NMP1,VMP1,NMP2,VMP2,MTJ1,MTJ2,NNOD )
C
      IMPLICIT REAL*8( A-H,O-Z )
      PARAMETER ( NOMAX = 20000 )
C
      DIMENSION MTJ( KTE,4 ),JAC( KTE,4 ),PXY( KTJ*10,2 )
      DIMENSION VMP1( 10 ),VMP2( 16,2 ),MTJ1( KTE,4,10 ),MTJ2( KTE,16 )
C
      NNOD = NODE
      DO 110 I=1,NELM
         DO 120 J=1,4
            JIJ = JAC(I,J)
            IF ( JIJ.LT.0 ) GOTO 120
C
            IF ( JIJ.EQ.0 .OR. JIJ.GT.I ) THEN
               X0 = PXY(MTJ(I,J),1)
               Y0 = PXY(MTJ(I,J),2)
               IF ( J.EQ.4 ) THEN
                  VX = PXY(MTJ(I,1),1) - X0
                  VY = PXY(MTJ(I,1),2) - Y0
               ELSE
                  VX = PXY(MTJ(I,J+1),1) - X0
                  VY = PXY(MTJ(I,J+1),2) - Y0
               ENDIF
C
               DO 130 K=1,NMP1
                  NNOD = NNOD + 1
                  PXY(NNOD,1) = VX*VMP1(K) + X0
                  PXY(NNOD,2) = VY*VMP1(K) + Y0
                  MTJ1(I,J,K) = NNOD
 130           CONTINUE
            ELSE
               IF ( JAC(JIJ,1).EQ.I ) THEN
                  IENO = 1
               ELSEIF ( JAC(JIJ,2).EQ.I ) THEN
                  IENO = 2
               ELSEIF ( JAC(JIJ,3).EQ.I ) THEN
                  IENO = 3
               ELSEIF ( JAC(JIJ,4).EQ.I ) THEN
                  IENO = 4
               ELSE
                  WRITE(*,*) 'ERROR DETECTED IN NEWPNT'
                  STOP
               ENDIF
C
               DO 140 K=1,NMP1
                  MTJ1(I,J,K) = MTJ1(JIJ,IENO,NMP1-K+1)
 140           CONTINUE
            ENDIF
 120     CONTINUE
C
         IF ( JAC(I,4).LT.0 ) THEN
            X1 = PXY(MTJ(I,1),1)
            Y1 = PXY(MTJ(I,1),2)
            X21 = PXY(MTJ(I,2),1) - X1
            Y21 = PXY(MTJ(I,2),2) - Y1
            X31 = PXY(MTJ(I,3),1) - X1
            Y31 = PXY(MTJ(I,3),2) - Y1
C
            DO 150 J=1,NMP2
               NNOD = NNOD + 1
               S = VMP2(J,1)
               T = VMP2(J,2)
               PXY(NNOD,1) = X21*S + X31*T + X1
               PXY(NNOD,2) = Y21*S + Y31*T + Y1
               MTJ2(I,J) = NNOD
 150        CONTINUE
         ELSE
            X1 = PXY(MTJ(I,1),1)
            Y1 = PXY(MTJ(I,1),2)
            X2 = PXY(MTJ(I,2),1)
            Y2 = PXY(MTJ(I,2),2)
            X3 = PXY(MTJ(I,3),1)
            Y3 = PXY(MTJ(I,3),2)
            X4 = PXY(MTJ(I,4),1)
            Y4 = PXY(MTJ(I,4),2)
C
            DO 160 J=1,NMP2
               NNOD = NNOD + 1
               S = VMP2(J,1)
               T = VMP2(J,2)
               PXY(NNOD,1) = ((1 - S)*(1 - T)*X1 + (1 + S)*(1 - T)*X2
     &              + (1 + S)*(1 + T)*X3 + (1 - S)*(1 + T)*X4)/4
               PXY(NNOD,2) = ((1 - S)*(1 - T)*Y1 + (1 + S)*(1 - T)*Y2
     &              + (1 + S)*(1 + T)*Y3 + (1 - S)*(1 + T)*Y4)/4
               MTJ2(I,J) = NNOD
 160        CONTINUE
         ENDIF
 110  CONTINUE
C
      RETURN
C
      E N D
