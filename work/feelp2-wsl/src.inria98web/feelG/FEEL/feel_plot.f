      SUBROUTINE PLOT(X, Y, IP)
C
      REAL*4 X,Y
C
      COMMON /CMNIWD/IWD
C
      REAL*8 P1(2),OP1(2),OP2(2),OP(2)
      DATA   OP /0.D0 , 0.D0/
      SAVE   P1,OP
C
      IF ( ABS(IP).EQ.2 ) THEN
         OP1(1) = OP(1) + P1(1)
         OP1(2) = OP(1) + P1(2)
         OP2(1) = OP(1) + X
         OP2(2) = OP(1) + Y
         CALL FEEL_LINE(OP1,OP2,IWD)
      ENDIF
C
      P1(1) = X
      P1(2) = Y
C
      IF ( IP.LT.0 ) THEN
         OP(1) = OP(1) + X
         OP(2) = OP(2) + Y
      ENDIF
C
      RETURN
C
      E N D


