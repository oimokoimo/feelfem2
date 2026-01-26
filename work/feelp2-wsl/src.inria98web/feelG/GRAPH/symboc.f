      SUBROUTINE SYMBOC (X, Y, H, STR, TH, N,
     $                   NC, IASC, LXYZ,
     $                   NU, XU, YU, IPU)
*****************************************************
*           create plot data for SYMBOL             *
*                   1990.2.10.                      *
*            copyright : Masatake Mori              *
*  --- input parameters ---                         *
*     X,Y,H,STR,TH,N ... same as SYMBOL             *
*     NC...if N is negative then 1                  *
*          if N is positive then N                  *
*     IASC...if N is negative then IASC = ICHR1     *
*            if N is positive then free             *
*     LXYZ...1 or -1                                *
*            if  1 then normal plot                 *
*            if -1 then reverse plot                *
*  --- output parameters ---                        *
*     (XU(IU),YU(IU),IPU(IU),IU=1,NU)...computed    *
*          plot data                                *
*  --- COMMON parameters ---                        *
*     XCONT,YCONT...X and Y coordinates of the      *
*        starting point of the succeeding           *
*        call of SYMBOL                             *
*     ISCR...if ISCR=0 then normal plot             *
*            if ISCR=1 then the character will be   *
*               superscripted if it follows after ^ *
*             and subscripted if it follows after _ *
*            When N = -1 or -2 characters cannot    *
*             be super- or subscripted              *
*     RWIDTH...ratio of width between characters    *
*              to height H                          *
*              normally RWIDTH = 1.0                *
*****************************************************
      CHARACTER*(*) STR
      CHARACTER*1   CASC
*
      PARAMETER (MAXSTR = 17, MESHST = 7)
      DIMENSION IXA(MAXSTR),IYA(MAXSTR),IPA(MAXSTR)
*
C      DIMENSION XU(NU),YU(NU),IPU(NU)
      DIMENSION XU(*),YU(*),IPU(*)
*
      COMMON / COMGXB / XCONT,YCONT,ISCR,RWIDTH
*
      IF (LXYZ .LT. 0) THEN
        SGN = -1.0
      ELSE
        SGN =  1.0
      END IF
*
*    ---- for 7*9 character including spaces ----
*                 2 spaces at the right edge
*                 2 spaces at the bottom
*
      RY = H / MESHST
      RX = RY
      IYSP = 2
      IF ((RWIDTH .EQ. 0.0) .OR.
     $     (ABS(RWIDTH - 1.0) .LT. 0.001)) THEN
        WIDTH = H
      ELSE
        WIDTH = H * RWIDTH
      END IF
      IYUP = 6
      IYDN = 2
*
      IUL = 0
      HFACT = 1.0
*
      JU = NU
*
      IF (ABS(TH) .LT. 1.0E-3) THEN
*
*       ---- TH = 0 ----
*
        IF (X .GE. 998.999) THEN
          XORG = XCONT
          YORG = YCONT
        ELSE
          XORG = X
          YORG = Y
        END IF
*
        DO 10 I = 1, NC
          RXV = HFACT * RX
          RYV = HFACT * RY
          IF (IUL .EQ. 0) THEN
            YSHFT = 0
          ELSE IF (IUL .EQ. 1) THEN
            YSHFT = IYUP * RY
          ELSE IF (IUL .EQ. 2) THEN
            YSHFT = - IYDN * RY
          ELSE
            YSHFT = 0
          END IF
          IF (N .GT. 0) THEN
            CASC = STR(I:I)
            IASC = ICHAR(CASC)
            IF (IASC .LT.   0) IASC = 32
            IF (IASC .GE. 256) IASC = 32
          END IF
*
          IF (ISCR .EQ. 1) THEN
            IF (IASC .EQ. 94) THEN
              HFACT = 0.5
              IUL = 1
              GO TO 10
            ELSE IF (IASC .EQ. 95) THEN
              HFACT = 0.5
              IUL = 2
              GO TO 10 
            END IF
          END IF
*
          IREC = IASC + 1
          IF (IASC .EQ. 32) GO TO 21
          IYD = 0
          CALL ALPSTR (IREC, IXA, IYA, IPA, IEND)
*
          IF (IEND .EQ. 0) GO TO 10
          IF (N .EQ. -2) THEN
            IP = 2
          ELSE
            IP = 3
          END IF
*
          JU = JU + 1
          XU(JU) = SGN * RXV * IXA(1) + XORG
          YU(JU) = RYV * (IYA(1) - IYSP)
     $           + YORG + YSHFT
          IPU(JU) = IP
          DO 20 J = 2, IEND
            JU = JU + 1
            XU(JU) = SGN * RXV * IXA(J) + XORG
            YU(JU) = RYV * (IYA(J) - IYSP)
     $             + YORG + YSHFT
            IPU(JU) = IPA(J)
   20     CONTINUE
*
   21     CONTINUE
*
          IF (IUL .NE. 0) THEN
            IF ((I .NE. NC) .AND.
     $          ((ICHAR(STR(I+1:I+1)) .EQ. 94) .OR.
     $           (ICHAR(STR(I+1:I+1)) .EQ. 95))) THEN
              XORG = XORG + 0.5 * WIDTH * SGN
            ELSE
              XORG = XORG + WIDTH * SGN
            END IF
          ELSE
            XORG = XORG + WIDTH * SGN
          END IF
          IUL = 0
          HFACT = 1.0
*
   10   CONTINUE
*
        XCONT = XORG
        YCONT = YORG
*
      ELSE
*
*       ---- TH .NE. 0 ----
*
        CT = COS(TH*0.01745329)
        ST = SIN(TH*0.01745329)
        IF (X .GE. 998.999) THEN
          XORG = XCONT
          YORG = YCONT
        ELSE
          XORG = X
          YORG = Y
        END IF
        RXS = RX * ST
        RYC = RY * CT
*
        DO 110 I = 1, NC
          RXV = HFACT * RX
          RYV = HFACT * RY
          RXCV = RXV * CT
          RXSV = RXV * ST
          RYCV = RYV * CT
          RYSV = RYV * ST
          IF (IUL .EQ. 0) THEN
            YSHFT = 0
          ELSE IF (IUL .EQ. 1) THEN
            YSHFT = IYUP
          ELSE IF (IUL .EQ. 2) THEN
            YSHFT = - IYDN
          ELSE
            YSHFT = 0
          END IF
          IF (N .GE. 0) THEN
            CASC = STR(I:I)
            IASC = ICHAR(CASC)
            IF (IASC .LT.   0) IASC = 32
            IF (IASC .GE. 256) IASC = 32
          END IF
          IF (ISCR .EQ. 1) THEN
            IF (IASC .EQ. 94) THEN
              HFACT = 0.5
              IUL = 1
              GO TO 110
            ELSE IF (IASC .EQ. 95) THEN
              HFACT = 0.5
              IUL = 2
              GO TO 110 
            END IF
          END IF
          IREC = IASC + 1
          IF (IASC .EQ. 32) GO TO 121
          CALL ALPSTR (IREC, IXA, IYA, IPA, IEND)
          IF (IEND .EQ. 0) GO TO 110
          IF (N .EQ. -2) THEN
            IP = 2
          ELSE
            IP = 3
          END IF
*
          JU = JU + 1
          XU(JU) = SGN * RXCV * IXA(1)
     $           - RXSV * (IYA(1) - IYSP)
     $           - RXS * YSHFT + XORG
          YU(JU) = SGN * RYSV * IXA(1)
     $           + RYCV * (IYA(1) - IYSP)
     $           + RYC * YSHFT + YORG
          IPU(JU) = IP
          DO 120 J = 2, IEND
            JU = JU + 1
            XU(JU) = SGN * RXCV * IXA(J)
     $             - RXSV * (IYA(J) - IYSP)
     $             - RXS * YSHFT + XORG
            YU(JU) = SGN * RYSV * IXA(J)
     $             + RYCV * (IYA(J) - IYSP)
     $             + RYC * YSHFT + YORG
            IPU(JU) = IPA(J)
  120     CONTINUE
*
  121     CONTINUE
*
          IF (IUL .NE. 0) THEN
            IF ((I .NE. NC) .AND.
     $          ((ICHAR(STR(I+1:I+1)) .EQ. 94) .OR.
     $           (ICHAR(STR(I+1:I+1)) .EQ. 95))) THEN
              XORG = XORG + 0.5 * WIDTH * CT * SGN
              YORG = YORG + 0.5 * WIDTH * ST * SGN
            ELSE
              XORG = XORG + WIDTH * CT * SGN
              YORG = YORG + WIDTH * ST * SGN
            END IF
          ELSE
            XORG = XORG + WIDTH * CT * SGN
            YORG = YORG + WIDTH * ST * SGN
          END IF
          IUL = 0
          HFACT = 1.0
*
  110   CONTINUE
*
        XCONT = XORG
        YCONT = YORG
*
      END IF
*
      NU = JU
*
      RETURN
      END
*
      SUBROUTINE ALPSTR (IREC, IXA, IYA, IPA, IEND)
*****************************************************
*     This routine gets the plot data of            *
*     the character whose ASCII code is IREC - 1    *
*   ---- input parameters ----                      *
*     IREC ... ASCII code + 1                       *
*     (IXA(J),IYA(J),IPA(J),J=1,IEND)...            *
*          stroke data of the character             *
*          from the file ALPHANUM.STR               *
*        IXA : decimal X coordinates                *
*        IYA : decimal Y coordinates                *
*        IPA : if IPA = 2 then move with pen down   *
*              if IPA = 3 then move with pen up     *
*        IEND : number of strokes                   *
*                                                   *
*     Examples in ALPHANUM.STR :                    *
*          IREC = 33 (= 32+1)...space               *
*          IREC = 50 (= 49+1)...1                   *
*          IREC = 66 (= 65+1)...A                   *
*     Each characte consists of 7x9 mesh including  *
*       2 space meshes on the left side and 2 space *
*       meshes at the bottom                        *
*     Maximum stroke is 17                          *
*     If return code is 1 byte then set RECL = 71   *
*       in the OPEN statement                       *
*****************************************************
      COMMON / COMOPS / IOPSY
*
      DIMENSION IXA(*),IYA(*),IPA(*)
*
      CHARACTER*72 IA
*
      IOPSY = 1
      OPEN (IOPSY, FILE='/usr/local/lib/alpnum.str',
     $         ACCESS='DIRECT', RECL=72,
     $         FORM='UNFORMATTED', ERR=99)

*
      IORD = IREC - 32
      READ (IOPSY,REC=IORD) IA
*
      READ (IA,3001) IEND,
     $              (IXA(I),IYA(I),IPA(I),I=1,17)
 3001 FORMAT (I2,17(I1,I2,I1))
*
   99 CONTINUE
*
      CLOSE (IOPSY)
*
      RETURN
      END
