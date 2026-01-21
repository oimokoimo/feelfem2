      SUBROUTINE NUMBS (X, Y, H, C, TH, IFMT)
*****************************************************
*           plot number C or DC or IC               *
*       according to the format given in IFMT       *
*                    1989.8.10.                     *
*            copyright : Masatake Mori              *
*     entry for real number...............NUMBS     *
*     entry for double precision number...NUMBD     *
*     entry for integer number............NUMBI     *
*  ---- input parameters ----                       *
*     (X,Y)...XY-coordinate of the lower-left       *
*             corner of the first character of      *
*             the number to be plotted              *
*     H...height of characters                      *
*     C...real number to be plotted                 *
*     DC...double precision number to be plotted    *
*     IC...integer number to be plotted             *
*     TH...angle (in degree) of character           *
*          sequence to be plotted                   *
*     IFMT ... format for the number to plot        *
*              Format must be given in IFMT         *
*              parenthesized like                   *
*              '(F13.6)' or '(1PD8.1)' or '(I5)'    *
*****************************************************
      REAL C
      DOUBLE PRECISION DC
      INTEGER IC
*
      CHARACTER*(*) IFMT
*
      PARAMETER (NA = 500)
      DIMENSION XU(NA),YU(NA),IPU(NA)
*
*     ---- real number ----
*
      INUMB = 1
      GO TO 1
*
*     ---- double precision number ----
*
      ENTRY NUMBD (X, Y, H, DC, TH, IFMT)
*
      INUMB = 2
      GO TO 1
*
*     ---- integer number ----
*
      ENTRY NUMBI (X, Y, H, IC, TH, IFMT)
*
      INUMB = 3
      GO TO 1
*
*     ---- transformation into stroke vector ----
*
    1 CONTINUE
*
      LXYZ = 1
      NU = 0
      CALL NUMBSC (X, Y, H, TH, IFMT, LXYZ,
     $             INUMB, C, DC, IC,
     $             NU, XU, YU, IPU)
*
      DO 10 I = 1, NU
        CALL PLOT (XU(I), YU(I), IPU(I))
   10 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE NUMBSC (X, Y, H, TH, IFMT, LXYZ,
     $                   INUMB, C, DC, IC,
     $                   NU, XU, YU, IPU)
******************************************************
*           compute stroke vector for NUMBS          *
*   ---- input parameters ----                       *
*     LXYZ ... 1 or -1                               *
*               if  1 then normal plot               *
*               if -1 then reverse plot              *
*     INUMB ... if 1 then transfer REAL C            *
*               if 2 then transfer                   *
*                    DOUBLE PRECISION DC             *
*               if 3 then transfer INTEGER IC        *
*     See comments in NUMBS for other parameters     *
******************************************************
      REAL C
      DOUBLE PRECISION DC
      INTEGER IC
*
      CHARACTER*(*) IFMT
      CHARACTER*16 JFMT
      CHARACTER*80 STR
      CHARACTER*1  BL
*
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      DATA BL /' '/
*
      STR = BL
*
      NV = 16
      CALL PAD (IFMT, JFMT, NV)
      IF (NV .NE. 16) RETURN
*
      IF (INUMB .EQ. 1) THEN
        WRITE (STR,JFMT) C
        CALL FZERO (IFMT, STR)
      ELSE IF (INUMB .EQ. 2) THEN
        WRITE (STR,JFMT) DC
        CALL FZERO (IFMT, STR)
      ELSE
        WRITE (STR,JFMT) IC
      END IF
*
      CALL NNUM (STR, N)
      IF (N .EQ. 0) RETURN
*
      NC = N
      CALL SYMBOC (X, Y, H, STR, TH, N,
     $                   NC, IASC, LXYZ,
     $                   NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE PAD (IFMT, JFMT, N)
*****************************************************
*     change characters following after ) in IFMT   *
*     into blanks and stores the result into JFMT   *
*        (If IFMT in calling program consists of    *
*         less than 16 characters, IFMT may have    *
*         extranuous characters after ')')          *
*  ---- input parameters ----                       *
*     IFMT...character sequence including '(...)...'*
*     N...number of characters in IFMT              *
*  ---- output parameters ----                      *
*     JFMT...character sequence IFMT filled with    *
*            blanks after ')'                       *
*         example : if IFMT = '(F5.1)ABC' then      *
*                      JFMT = '(F5.1)   '           *
*     N...number of characters in JFMT              *
*****************************************************
      CHARACTER*(*) IFMT,JFMT
      CHARACTER*1 MJ,SP,RP
*
      DATA SP /' '/, RP /')'/
*
      DO 10 J = 1, N
        NRP = J + 1
        MJ = IFMT(J:J)
        JFMT(J:J) = MJ
        IF (MJ .EQ. RP) GO TO 1
   10 CONTINUE
*
*      ---- number with zero length ----
*
      N = - N
      RETURN
*
*     ---- number with length NRP - 1 ----
*
    1 CONTINUE
      IF (NRP .GT. N) RETURN
*
      DO 20 J = NRP, N
        JFMT(J:J) = SP
   20 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE NNUM (STR, NC)
*****************************************************
*     count number ( = NC) of characters in STR     *
*****************************************************
      CHARACTER*80 STR
      CHARACTER*1  SP
*
      DATA SP /' '/
*
      NC = 0
      DO 10 J = 80, 1, -1
        IF (STR(J:J) .NE. SP) THEN
          NC = J
          RETURN
        END IF
   10 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE FZERO (IFMT, STR)
*****************************************************
*     insert '0' if '0' does not exist before '.'   *
*     in F- or E- or D- format                      *
*****************************************************
      CHARACTER*16 IFMT
      CHARACTER*80 STR
      CHARACTER*1  DOT,ZERO,BLANK,F,E,D
      CHARACTER*2  MINUS
*
      DATA DOT /'.'/, ZERO /'0'/, BLANK /' '/
      DATA F /'F'/, E /'E'/, D /'D'/
      DATA MINUS /'-.'/
*
      J = 0
      DO 10 I = 1, 16
        IF (     IFMT(I:I) .EQ. F
     $      .OR. IFMT(I:I) .EQ. E
     $      .OR. IFMT(I:I) .EQ. D  ) GO TO 11
   10 CONTINUE
      RETURN
*
   11 CONTINUE
*
      DO 20 I = 1, 80
        J = I
        IF (STR(I:I) .NE. BLANK) GO TO 21
   20 CONTINUE
      RETURN
*
   21 CONTINUE
      IF (J .EQ. 1) RETURN
*
      IF (STR(J:J) .EQ. DOT) THEN
        STR(J-1:J-1) = ZERO
        RETURN
      ELSE IF (STR(J:J+1) .EQ. MINUS) THEN
        STR(J-1:J) = '-0'
        RETURN
      ELSE
        RETURN
      END IF
*
      END
*
      SUBROUTINE NDC (IFMT, MD)
*****************************************************
*    compute the number MD of the digits following  *
*    after the decimal point in IFMT                *
*    example : if IFMT='(F5.2)' then  MD=2          *
*    IFMT should be such that 0 .LE. MD .LE. 9      *
*****************************************************
      CHARACTER*(*) IFMT
      CHARACTER*1 ND,BLK,DOT
*
      ND = ' '
      BLK = ' '
      DOT = '.'
*
      JD = 0
      DO 10 I = 1, 16
        ND = IFMT(I:I)
        IF (ND .EQ. DOT) THEN
          JD=1
        ELSE
          IF ((JD .NE. 0) .AND. (ND .NE. BLK))
     $       GO TO 2
        END IF
   10 CONTINUE
*
    2 CONTINUE
      READ (ND,3001) MD
 3001 FORMAT (I1)
*
      RETURN
      END
*
      SUBROUTINE NCC (IFMT, NC)
*****************************************************
*    compute the total column number NC of digits   *
*    given by IFMT including decimal the point and  *
*    blanks                                         *
*    example : IFMT='(F4.1)'...NC=4                 *
*              IFMT='(I5)'.....NC=5                 *
*    IFMT should be such that 0 .LE. NC .LE. 9      *
*****************************************************
      CHARACTER*(*) IFMT
      CHARACTER*1  MC,BL,KF,KE,KD,KI
*
      MC = ' '
      BL = ' '
      KF = 'F'
      KE = 'E'
      KD = 'D'
      KI = 'I'
*
      JD = 0
      DO 10 I = 1, 16
        MC = IFMT(I:I)
        IF (MC .EQ. KF) GO TO 1
        IF (MC .EQ. KE) GO TO 1
        IF (MC .EQ. KD) GO TO 1
        IF (MC .EQ. KI) GO TO 1
        IF (JD .EQ. 0) GO TO 10
        IF (MC .EQ. BL) GO TO 10
        GO TO 2
*
    1   CONTINUE
        JD=1
*
   10 CONTINUE
*
    2 CONTINUE
      READ (MC, 3001) NC
 3001 FORMAT (I1)
*
      RETURN
      END
*
      SUBROUTINE NUMBPW (X, Y, H, C, TH, N)
*****************************************************
*     plot real number C in power of 10 format      *
*                   1.2*10**3                       *
*   ---- input parameters ----                      *
*     (X,Y)...XY-coordinate of the lower-left       *
*         corner of the first character of the      *
*         number to be plotted                      *
*         If C is positive or zero then a blank     *
*         is inserted as the first character        *
*     H...height of characters (mantissa part)      *
*     C...value of the number to be plotted         *
*     TH...angle (in degree) of character sequence  *
*          to be plotted                            *
*     N...number of digits of mantissa              *
*         N must not be less than 0 and not         *
*         larger than 5                             *
*                                                   *
*     example of N : C = 1.234E-2                   *
*       N = 0 : 10**(-2)                            *
*       N = 1 : 1*10**(-2)                          *
*       N = 2 : 1.2*10*(-2)                         *
*       N = 3 : 1.23*10**(-2)                       *
*****************************************************
      PARAMETER (NUA = 500)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL NUMBPC (X, Y, H, C, TH, N,
     $             NU, XU, YU, IPU)
*
      DO 10 I = 1, NU
        CALL PLOT (XU(I), YU(I), IPU(I))
   10 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE NUMBPC (X, Y, H, C, TH, N,
     $                   NU, XU, YU, IPU)
*****************************************************
*         compute string vector for NUMBPW          *
*  ---- internal parameters ----                    *
*     RATIO...W/H where W and H are the width and   *
*             the height of characters              *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      CHARACTER*13 IA
      CHARACTER*12 IB
      CHARACTER*3  IC
      CHARACTER*1  MINUS,ZERO,BLANK
*
      PARAMETER (RATIO = 7.0 / 7.0)
*
      DATA MINUS /'-'/, ZERO /'0'/, BLANK /' '/
*
      IF (N .LT. 0) RETURN
      IF (N .GT. 5) RETURN
*
*     ---- replace 9.99E-4 by 1.00E-3 ----
*
      CV = ABS(C) * 1.000005
      IF (C .LT. 0.0) CV = - CV
*
      IA = '             '
*
      WRITE (IA,'(1PE13.6)') CV
*
*     ---- arrange mantissa ----
*
      IB = '            '
*
      IF (N .EQ. 0) THEN
        IF (C .LT. 0.0) THEN
          IB(1:3) = '-10'
        ELSE
          IB(1:3) = ' 10'
        END IF
        NP = 3
*
      ELSE IF (N. EQ. 1) THEN
        IB(1:5) = IA(1:2) // 'X10'
        NP = 5
*
      ELSE
        IB(1:N+5) = IA(1:N+2) // 'X10'
        NP = N + 5
      END IF
*
*     ---- arrange exponent ----
*
      IC = '   '
*
      IF (IA(11:11) .EQ. MINUS) THEN
        IF (   IA(12:12) .EQ. ZERO
     $    .OR. IA(12:12) .EQ. BLANK ) THEN
          IC(1:2) = '-' // IA(13:13)
          NP1 = 3
        ELSE
          IC(1:3) = '-' // IA(12:13)
          NP1 = 3
        END IF
      ELSE
        IF (   IA(12:12) .EQ. ZERO
     $    .OR. IA(12:12) .EQ. BLANK ) THEN
          IC(1:1) = IA(13:13)
          NP1 = 1
        ELSE
          IC(1:2) = IA(12:13)
          NP1 = 2
        END IF
      END IF
*
*     ---- plot mantissa ----
*
      NC = NP
      LXYZ = 1
*
      CALL SYMBOC (X, Y, H, IB, TH, NP,
     $             NC, IASC, LXYZ,
     $             NU, XU, YU, IPU)
*
*     ---- plot exponent ----
*
      H2 = H * 5.0 / 7.0
      X1 = NP * H * RATIO
      Y1 = H * 4.0 / 7.0
*
      IF (ABS(TH) .LT. 1.0E-4) THEN
        X1 = X + X1
        Y1 = Y + Y1
      ELSE
        CT = COS(TH * 0.01745329)
        ST = SIN(TH * 0.01745329)
        X2 = X1 * CT - Y1 * ST
        Y1 = Y + X1 * ST + Y1 * CT
        X1 = X + X2
      END IF
*
      NC = NP1
*
      CALL SYMBOC (X1, Y1, H2, IC, TH, NP1,
     $             NC, IASC, LXYZ,
     $             NU, XU, YU, IPU)
*
      RETURN
      END
