      SUBROUTINE PERPL3 (X0, Y0, Z0, XN, YN, ZN,
     $                   XW, YW, ZW,
     $                   SIGMA, TAU, EH, ALPHA, EL,
     $                   NP, XA, YA, ZA, NT, KNC)
*****************************************************
*              perspective projection               *
*             with hidden line masking              *
*             over triangular network               *
*                    1990.6.9.                      *
*             copyright : Masatake Mori             *
*   ---- input parameters ----                      *
*     X0, Y0, Z0, XN, YN, ZN, XW, YW, ZW            *
*     SIGMA,TAU,EH,ALPHA,EL                         *
*     NP, XA, YA, ZA, NT, KNC                       *
*     See comments in INITP3 and PLOT3              *
*   ---- common parameters ----                     *
*     LHL ... 0 or 1                                *
*        if 0 then plot without hidden line masking *
*        if 1 then plot with hidden line masking    *
*     LZC ... 0 or 1                                *
*        if 0 then skip plotting for Z beyond       *
*             ZMN and ZMX                           *
*        if 1 then plot all triangular element      *
*     LAX ... 0 or 1 or 2                           *
*        if 0 then plot without axes                *
*        if 1 then plot frame on the bottom plane   *
*        if 2 then plot frame on the bottom plane   *
*             and four line segments parallel to    *
*             the Z-axis                            *
*        if 3 then plot frame on the bottom plane   *
*             and plot frame on the top plane       *
*             and four line segments parallel to    *
*             the  Z-axis whose heights are ZMX     *
*****************************************************
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
*
      DIMENSION HEIT(2),KHFND(2)
*
      COMMON / COMZCL / LZCLP,ZMN,ZMX
      COMMON / COMHLN / LHL
      COMMON / COMFRM / LZC,LAX
*
c      PARAMETER (NLC = 1000)
      PARAMETER (NLC = 20000)
      DIMENSION IBGN(NLC),IEND(NLC),
     $          IRGT(NLC),ILFT(NLC)
      DIMENSION LHEIT(NLC),LSRC(NLC)
*
      CALL TRTOLS (NT, KNC,
     $             NL, IBGN, IEND, IRGT, ILFT)
*
      CALL INITP3 (X0, Y0, Z0, XN, YN, ZN,
     $             XW, YW, ZW,
     $             SIGMA, TAU, EH, ALPHA, EL,
     $             NP, XA, YA, NT, KNC)
*
      IF (LZCLP .EQ. 0) THEN
        LZCLPC = LZCLP
        ZMNC = ZMN
        ZMXC = ZMX
        LZCLP = 1
        ZMN = 0
        ZMX = ZW
      ELSE
        LZCLPC = 1
      END IF
*
      IF (LZC .EQ. 1) THEN
        IPU = 2
      ELSE
        IPU = 3
      END IF
*
      CALL PLOT ( 0.0, 0.0, 3)
      CALL PLOT ( 0.0, 0.0, 2)
      CALL PLOT ( 0.0, 0.0, 3)
*
*     ---- plot X,Y,Z axis ----
*
      CALL PLTAX3 (X0, Y0, Z0, XN, YN, ZN,
     $             XW, YW, ZW,
     $             NP, XA, YA, ZA, NT, KNC)
*
*     ---- plot triangular elements ----
*
      CALL TRPLT (IPU, X0, Y0, Z0, XN, YN, ZN,
     $            XW, YW, ZW,
     $            NL, IBGN, IEND,
     $            NP, XA, YA, ZA, NT, KNC)
*
*     ---- plot contour curves ----
*
      ZFCTR = ZW / (ZN - Z0)
      KH = 2
      HEIT(1) = ZMN / ZFCTR + Z0
      HEIT(2) = ZMX / ZFCTR + Z0
*
c      CALL CNTPE3 (X0, Y0, Z0, XN, YN, ZN,
c     $     XW, YW, ZW,
c     $     KH, HEIT, KHFND,
c     $     NL, IBGN, IEND, IRGT, ILFT, LHEIT, LSRC,
c     $     NP, XA, YA, ZA, NT, KNC)
*
      IF (LZCLPC .EQ. 0) THEN
        LZCLP = 0
        ZMN = ZMNC
        ZMX = ZMXC
      END IF
*
      CALL PLOT (0.0, 0.0, 3)
*
      RETURN
      END
*
      SUBROUTINE TRPLT (IPU, X0, Y0, Z0, XN, YN, ZN,
     $                  XW, YW, ZW,
     $                  NL, IBGN, IEND,
     $                  NP, XA, YA, ZA, NT, KNC)
*****************************************************
*      3D plot of triangular wireframe network      *
*              given in XA,YA,ZA and KNC            *
*  ---- input parameters ----                       *
*     IPU ... if LZC = 1 then 2 else 3              *
*     NL ... total number of line segments          *
*     IBGN(L) ... point number of the start point   *
*                 of the L-th line segment          *
*     IEND(L) ... point number of the end point     *
*                 of the L-th line segment          *
*     See comments in PLOT3 for other parameters    *
*****************************************************
      COMMON / COMZCL / LZCLP,ZMN,ZMX
*
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
      DIMENSION IBGN(NL),IEND(NL)
*
      DIMENSION XT(5),YT(5),IPT(5)
*
      XFCTR = XW / (XN - X0)
      YFCTR = YW / (YN - Y0)
      ZFCTR = ZW / (ZN - Z0)
*
      DO 10 L = 1, NL
*
        NU = 0
*
        XS = XFCTR * (XA(IBGN(L)) - X0)
        YS = YFCTR * (YA(IBGN(L)) - Y0)
        ZS = ZFCTR * (ZA(IBGN(L)) - Z0)
        X  = XFCTR * (XA(IEND(L)) - X0)
        Y  = YFCTR * (YA(IEND(L)) - Y0)
        Z  = ZFCTR * (ZA(IEND(L)) - Z0)
*
        IF (LZCLP .EQ. 0) THEN
*
          CALL PLOT3 (XS, YS, ZS, 3,
     $                NP, XA, YA, ZA, NT, KNC)
          CALL PLOT3 ( X,  Y,  Z, 2,
     $                NP, XA, YA, ZA, NT, KNC)
*
        ELSE
*
          IF (Z .LT. ZS) THEN
            XVV = X
            YVV = Y
            ZVV = Z
            X = XS
            Y = YS
            Z = ZS
            XS = XVV
            YS = YVV
            ZS = ZVV
          END IF
*
          XD = X - XS
          YD = Y - YS
*
          IF (ZS .GE. ZMN) THEN
            IF (Z .LE. ZMX) THEN
              CALL PLOT3 (XS, YS, ZS,   3,
     $                    NP, XA, YA, ZA, NT, KNC)
              CALL PLOT3 ( X,  Y,  Z,   2,
     $                    NP, XA, YA, ZA, NT, KNC)
            ELSE IF (ZS .GT. ZMX) THEN
              ZU = ZMX
              CALL PLOT3 (XS, YS, ZU,   3,
     $                    NP, XA, YA, ZA, NT, KNC)
              CALL PLOT3 ( X,  Y, ZU, IPU,
     $                    NP, XA, YA, ZA, NT, KNC)
            ELSE IF (Z .GT. ZMX) THEN
              CALL PLOT3 (XS, YS,  ZS,  3,
     $                    NP, XA, YA, ZA, NT, KNC)
              RT = (ZMX - ZS) / (Z - ZS)
              XU = XS + RT * XD
              YU = YS + RT * YD
              ZU = ZMX
              CALL PLOT3 (XU, YU, ZU,   2,
     $                    NP, XA, YA, ZA, NT, KNC)
              CALL PLOT3 ( X,  Y, ZU, IPU,
     $                    NP, XA, YA, ZA, NT, KNC)
            END IF
          ELSE
            IF (Z .LT. ZMN) THEN
              ZU = ZMN
              CALL PLOT3 (XS, YS, ZU,   3,
     $                    NP, XA, YA, ZA, NT, KNC)
              CALL PLOT3 ( X,  Y, ZU, IPU,
     $                    NP, XA, YA, ZA, NT, KNC)
            ELSE IF (Z .LE. ZMX) THEN
              ZU = ZMN
              CALL PLOT3 (XS, YS, ZU,   3,
     $                    NP, XA, YA, ZA, NT, KNC)
              RT = (ZMN - ZS) / (Z - ZS)
              XU = XS + RT * XD
              YU = YS + RT * YD
              CALL PLOT3 (XU, YU, ZU, IPU,
     $                    NP, XA, YA, ZA, NT, KNC)
              CALL PLOT3 ( X,  Y,  Z,   2,
     $                    NP, XA, YA, ZA, NT, KNC)
            ELSE
              ZU = ZMN
              CALL PLOT3 (XS, YS, ZU,   3,
     $                    NP, XA, YA, ZA, NT, KNC)
              RT = (ZMN - ZS) / (Z - ZS)
              XU = XS + RT * XD
              YU = YS + RT * YD
              CALL PLOT3 (XU, YU, ZU, IPU,
     $                    NP, XA, YA, ZA, NT, KNC)
              RT = (ZMX - ZS) / (Z - ZS)
              XU = XS + RT * XD
              YU = YS + RT * YD
              ZU = ZMX
              CALL PLOT3 (XU, YU, ZU,   2,
     $                    NP, XA, YA, ZA, NT, KNC)
              CALL PLOT3 ( X,  Y, ZU, IPU,
     $                    NP, XA, YA, ZA, NT, KNC)
            END IF
          END IF
*
        END IF
*
   10 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE CNTPE3 (X0, Y0, Z0, XN, YN, ZN,
     $     XW, YW, ZW,
     $     KH, HEIT, KHFND,
     $     NL, IBGN, IEND, IRGT, ILFT, LHEIT, LSRC,
     $     NP, XA, YA, ZA, NT, KNC)
*****************************************************
*         perspective plot of contour lines         *
*              over triangular network              *
*              with hidden line masking             *
*   --- input parameters ----                       *
*     (X0,Y0) ... left-bottom corner of rectangular *
*                 domain in user coordinates        *
*     Z0 ........ minimum value of Z in user        *
*                 coordinates                       *
*     (XN,YN) ... right-top corner of rectangular   *
*                 domain in world coordinates       *
*     ZN ........ maximum value of Z in user        *
*                 coordinates                       *
*     (0,0) ..... left-bottom corner of rectangular *
*                 domain in world coordinates       *
*                 minimum value of Z in world       *
*                 coordinates is 0                  *
*     (XW,YW) ... right-top corner of rectangular   *
*                 domain in world coordinates       *
*     ZW ........ maximum value of Z in world       *
*                 coordinates                       *
*     KH ........ total number of heights to plot   *
*     HEIT(IH) ... height of IH-th contour line     *
*                  in user coordinates              *
*     NL ........ total number of sides of          *
*                 traiangular network               *
*     IBGN(I) ... point number of start point of    *
*                 the I-th side                     *
*     IEND(I) ... point number of end point of      *
*                 the I-th side                     *
*     IRGT(I) ... point number of right point of    *
*                 the I-th side                     *
*     ILFT(I) ... point number of left point of     *
*                 the I-th side                     *
*     NP ... total number of nodal points           *
*     XA(I) ... X coordinate of I-th nodal point    *
*               in user coordinates                 *
*     YA(I) ... Y coordinate of I-th nodal point    *
*               in user coordinates                 *
*     ZA(I) ... data atI-th nodal point             *
*               in user coordinates                 *
*****************************************************
c      PARAMETER (NHC = 1000)
      PARAMETER (NHC = 20000)
      DIMENSION XH(NHC),YH(NHC),IPH(NHC)
*
      DIMENSION HEIT(KH),KHFND(KH)
*
      DIMENSION IBGN(NL),IEND(NL),IRGT(NL),ILFT(NL)
      DIMENSION LHEIT(NL),LSRC(NL)
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
*
      XFCTR = XW / (XN - X0)
      YFCTR = YW / (YN - Y0)
      ZFCTR = ZW / (ZN - Z0)
*
      DO 20 IH = 1, KH
*
        HTZ = HEIT(IH)
*
        CALL CONTC3 (HTZ, NH, XH, YH, IPH,
     $               NL, IBGN, IEND, IRGT, ILFT,
     $               LHEIT, LSRC,
     $               NP, XA, YA, ZA)
*
        HGHT = ZFCTR * (HTZ - Z0)
*
        DO 30 JH = 1, NH
          X = XFCTR * (XH(JH) - X0)
          Y = YFCTR * (YH(JH) - Y0)
          CALL PLOT3 (X, Y, HGHT, IPH(JH),
     $                NP, XA, YA, ZA, NT, KNC)
   30   CONTINUE
*
        IF (NH .GT. 0) THEN
          KHFND(IH) = 1
        ELSE
          KHFND(IH) = 0
          WRITE (*,2003) HTZ
 2003     FORMAT (' (CNTPE3) HEIT(=',1PE9.2,')',
     $            ' is not found')
        END IF
*
   20 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE PLTAX3 (X0, Y0, Z0, XN, YN, ZN,
     $                   XW, YW, ZW,
     $                   NP, XA, YA, ZA, NT, KNC)
*****************************************************
*         plot horizontal and vertical axes         *
*   ---- input parameters ----                      *
*     All the arguments are for input               *
*     See comments in PLOT3 and PERPL3              *
*****************************************************
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
*
      COMMON / COMZCL / LZCLP,ZMN,ZMX
*
      COMMON / COMHLN / LHL
      COMMON / COMFRM / LZC,LAX
*
      DIMENSION ZH(4)
*
      DATA EPS / 1.0E-5 /
*
      IF (LAX .EQ. 0) RETURN
*
      CALL PLXYZ3 (0.0, 0.0, ZMN, 1, XW,
     $             NP, XA, YA, ZA, NT, KNC)
      CALL PLXYZ3 (XW, 0.0, ZMN, 2, YW,
     $             NP, XA, YA, ZA, NT, KNC)
      CALL PLXYZ3 (0.0, YW, ZMN, 1, XW,
     $             NP, XA, YA, ZA, NT, KNC)
      CALL PLXYZ3 (0.0, 0.0, ZMN, 2, YW,
     $             NP, XA, YA, ZA, NT, KNC)
*
      IF (LAX .EQ. 2) THEN
*
        ZFCTR = ZW / (ZN - Z0)
*
        DO 10 IT = 1, NT
*
          DO 20 KP = 1, 3
            IV = KNC(KP,IT)
            IF ((ABS(XA(IV)-X0) .LE. EPS) .AND.
     $          (ABS(YA(IV)-Y0) .LE. EPS)) THEN
              ZH(1) = MAX(ZMN,
     $                MIN(ZMX,(ZA(IV)-Z0)*ZFCTR))
            ELSE IF ((ABS(XA(IV)-XN) .LE. EPS) .AND.
     $               (ABS(YA(IV)-Y0) .LE. EPS)) THEN
              ZH(2) = MAX(ZMN,
     $                MIN(ZMX,(ZA(IV)-Z0)*ZFCTR))
            ELSE IF ((ABS(XA(IV)-XN) .LE. EPS) .AND.
     $               (ABS(YA(IV)-YN) .LE. EPS)) THEN
              ZH(3) = MAX(ZMN,
     $                MIN(ZMX,(ZA(IV)-Z0)*ZFCTR))
            ELSE IF ((ABS(XA(IV)-X0) .LE. EPS) .AND.
     $               (ABS(YA(IV)-YN) .LE. EPS)) THEN
              ZH(4) = MAX(ZMN,
     $                MIN(ZMX,(ZA(IV)-Z0)*ZFCTR))
            END IF
   20     CONTINUE
*
   10   CONTINUE
*
        CALL PLXYZ3 (0.0, 0.0, ZMN, 3, ZH(1),
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (XW, 0.0, ZMN, 3, ZH(2),
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (XW, YW, ZMN, 3, ZH(3),
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (0.0, YW, ZMN, 3, ZH(4),
     $               NP, XA, YA, ZA, NT, KNC)
*
        RETURN
      END IF
*
      IF (LAX .EQ. 3) THEN
*
        CALL PLXYZ3 (0.0, 0.0, ZMN, 3, ZMX-ZMN,
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (XW, 0.0, ZMN, 3, ZMX-ZMN,
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (XW, YW, ZMN, 3, ZMX-ZMN,
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (0.0, YW, ZMN, 3, ZMX-ZMN,
     $               NP, XA, YA, ZA, NT, KNC)
*
        CALL PLXYZ3 (0.0, 0.0, ZMX, 1, XW,
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (XW, 0.0, ZMX, 2, YW,
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (0.0, YW, ZMX, 1, XW,
     $               NP, XA, YA, ZA, NT, KNC)
        CALL PLXYZ3 (0.0, 0.0, ZMX, 2, YW,
     $               NP, XA, YA, ZA, NT, KNC)
        RETURN
      END IF
*
      RETURN
      END
*
      SUBROUTINE PLXYZ3 (X, Y, Z, M, D,
     $                   NP, XA, YA, ZA, NT, KNC)
*****************************************************
*            plot axis line by sub-division         *
*****************************************************
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
*
      PARAMETER (ND = 10)
      PARAMETER (NUA = 2 * ND + 1)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      H = D / ND
*
      NU = 0
*
      CALL PLOT3 (X, Y, Z, 3,
     $            NP, XA, YA, ZA, NT, KNC)
      IF (M .EQ. 1) THEN
        DO 10 I = 1, ND
          XD = H * I
          CALL PLOT3 (X + XD, Y, Z, 2,
     $                NP, XA, YA, ZA, NT, KNC)
   10   CONTINUE
      ELSE IF (M .EQ. 2) THEN
        DO 20 I = 1, ND
          YD = H * I
          CALL PLOT3 (X, Y + YD, Z, 2,
     $                NP, XA, YA, ZA, NT, KNC)
   20   CONTINUE
      ELSE IF (M .EQ. 3) THEN
        DO 30 I = 1, ND
          ZD = H * I
          CALL PLOT3 (X, Y, Z + ZD, 2,
     $                NP, XA, YA, ZA, NT, KNC)
   30   CONTINUE
      END IF
*
      RETURN
      END
*
      SUBROUTINE STERE3 (X0, Y0, Z0, XN, YN, ZN,
     $                   XW, YW, ZW,
     $                   SIGMA, TAU, EH, ALPHA, EL,
     $                   NP, XA, YA, ZA, NT, KNC)
*****************************************************
*                 stereo projection                 *
*   ---- input parameters ----                      *
*     See comments in PLOT3                         *
*****************************************************
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
*
      CALL PLOT (0.05, 0.00, 3)
      CALL PLOT (0.00, 0.00, 2)
      CALL PLOT (0.00, 0.05, 2)
      CALL PLOT (0.00, 0.00, 3)
*
      SIGMA = SIGMA + 0.05 * (EL + TAU)
      CALL PERPL3 (X0, Y0, Z0, XN, YN, ZN,
     $             XW, YW, ZW,
     $             SIGMA, TAU, EH, ALPHA, EL,
     $             NP, XA, YA, ZA, NT, KNC)
*
      CALL PLOT (4.85, 0.00, 3)
      CALL PLOT (4.90, 0.00, 2)
      CALL PLOT (4.90, 0.05, 2)
*
      CALL PLOT (5.0,0.0,-3)
*
      CALL PLOT (0.05, 0.00, 3)
      CALL PLOT (0.00, 0.00, 2)
      CALL PLOT (0.00, 0.05, 2)
      CALL PLOT (0.00, 0.00, 3)
*
      SIGMA = SIGMA - 0.1 * (EL + TAU)
      CALL PERPL3 (X0, Y0, Z0, XN, YN, ZN,
     $             XW, YW, ZW,
     $             SIGMA, TAU, EH, ALPHA, EL,
     $             NP, XA, YA, ZA, NT, KNC)
*
      CALL PLOT (4.85, 0.00, 3)
      CALL PLOT (4.90, 0.00, 2)
      CALL PLOT (4.90, 0.05, 2)
*
      CALL PLOT (-5.0,0.0,-3)
*
      SIGMA = SIGMA + 0.05 * (EL + TAU)
*
      RETURN
      END
