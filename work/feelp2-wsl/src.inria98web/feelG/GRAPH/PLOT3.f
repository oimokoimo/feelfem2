      SUBROUTINE INITP3 (X0, Y0, Z0, XN, YN, ZN,
     $                   XW, YW, ZW,
     $                   SIGMA, TAU, EH, ALPHA, EL,
     $                   NP, XA, YA, NT, KNC)
*****************************************************
*          initialize parameters for PLOT3          *
*             over triangular network               *
*                    1990.5.4.                      *
*             copyright : Masatake Mori             *
*   ---- input parameters ----                      *
*     (X0,Y0,Z0) ... lower bound of the right       *
*                   angled parallelepiped domain    *
*                   in user coordinates             *
*     (XN,YN,ZN) ... upper bound of the right       *
*                   angled parallelepiped domain    *
*                   in user coordinates             *
*     (XW,YW,ZW) ... size of the right angled       *
*                   parallelepiped domain           *
*                   in 3D world coordinates         *
*     (X0,XN) in user coordinates corresponds to    *
*               (0,XW) in 3D world coodinates,      *
*               and so on                           *
*    -- parameters for perspective projection --    *
*     SIGMA ... distance between the origin and the *
*               plane perpendicular both to the     *
*               view plane and the ground plane     *
*               on which the center of projection   *
*               is located                          *
*     TAU ... distance between the origin and the   *
*             ground plane                          *
*     EH ... the distance between the center of     *
*            projection and the ground plane        *
*     ALPHA ... rotation angle of the right angled  *
*               parallelepiped domain about the     *
*               Z-axis of the world coordinates     *
*     EL ... distance between the center of         *
*            projection and the view plane          *
*     See comments in PLOT3 for other arguments     *
*   ---- common parameters in COMZCL----            *
*     The followings must be given before this      *
*         subroutine is called                      *
*     LZCLP ... 0 or 1                              *
*               if 0 then with clipping for Z       *
*                    at (0 .LE. Z .LE. ZW)          *
*               if 1 then with clipping for Z       *
*                    at (ZMN .LE. Z .LE. ZMX)       *
*        When LZCLP=1 the followings must be given  *
*     ZMN ... minimum value of Z for clipping       *
*             in 3D world coordinate                *
*     ZMX ... maximum value of Z for clipping       *
*             in 3D world coordinate                *
*****************************************************
      COMMON / COMZCL / LZCLP,ZMN,ZMX
*
      DIMENSION XA(NP),YA(NP)
      DIMENSION KNC(3,NT)
*
c      PARAMETER (MTH = 128, NTH = 32)
      PARAMETER (MTH = 512, NTH = 128)
      COMMON / COMDVD / TP0,TPN,RTH,
     $                  NGR(NTH),KGR(MTH,NTH)
      DIMENSION KV(MTH),IREC(MTH),ABX(MTH)
      DIMENSION ISTL(MTH),ISTR(MTH)
*
      COMMON / COMHL1 / CA,SA,ET,ELC,XWC,XWS,YWC,YWS,
     $                  SIGM,XSF,ZSF,XE,YE,ZE
      COMMON / COMHL4 / PX,PZ,PX1,PZ1
*
      COMMON / COMGFX / X0A,XWA,XFCTR,RXFCT,HXFC,RHX
      COMMON / COMGFY / Y0A,YWA,YFCTR,RYFCT,HYFC,RHY
      COMMON / COMGFZ / Z0A,ZWA,ZFCTR
*
      DIMENSION NTW(3)
*
      PARAMETER (RAD = 3.141593 / 180.0)
*
      X0A = X0
      Y0A = Y0
      Z0A = Z0
*
      XFCTR = XW / (XN - X0)
      YFCTR = YW / (YN - Y0)
      ZFCTR = ZW / (ZN - Z0)
*
      PX = 0.002 * XW
      PZ = 0.002 * YW
      PX1 = 1.1 * PX
      PZ1 = 1.1 * PZ
*
      RXFCT = 1 / XFCTR
      RYFCT = 1 / YFCTR
*
      CA = COS(RAD * ALPHA)
      SA = SIN(RAD * ALPHA)
*
      XWC = XW * CA
      XWS = XW * SA
      YWC = YW * CA
      YWS = YW * SA
*
      SIGM = SIGMA
      ZE = EH
      ELC = EL
*
      IF (ALPHA .LT. -90.0) THEN
        VV = -(XWS + YWC)
      ELSE IF (ALPHA .LT. 0.0) THEN
        VV = -XWS
      ELSE IF (ALPHA .LT. 90.0) THEN
        VV = 0.0
      ELSE
        VV = -YWC
      END IF
*
      ELD = TAU - VV
*
      EMIN = EL + ELD
      IF (ZE .GT. 0.0) THEN
        ZSF = -EL * ZE / EMIN
      ELSE
        ZSF = -EL * ZE / (EMIN + ABS(XWS) + ABS(YWC))
      END IF
*
      ET = EL + TAU
*
      XE = - ET * SA - SIGMA * CA
      YE = - ET * CA + SIGMA * SA
*
      V0 = SIGMA / ET
      V1 = (SIGMA + XWC) / (ET + XWS)
      V2 = (SIGMA + XWC - YWS) / (ET + XWS + YWC)
      V3 = (SIGMA - YWS) / (ET + YWC)
*
      XSF = MIN(V0, V1, V2, V3) * EL
*
*     --- divide and sort the domain ---
*             for quick search
*
      TP0 =  1.0E32
      TPN = -1.0E32
*
      DO 60 LV = 1, NT
        DO 70 KP = 1, 3
          XV = XFCTR * (XA(KNC(KP,LV)) - X0)
          YV = YFCTR * (YA(KNC(KP,LV)) - Y0)
          THV = (XV * CA - YV * SA + SIGMA) /
     $          (XV * SA + YV * CA + ET)
          IF (THV .LT. TP0) TP0 = THV
          IF (THV .GT. TPN) TPN = THV
   70   CONTINUE
   60 CONTINUE
*
      RTH = NTH / (TPN - TP0)
*
      DO 20 KGV = 1, NTH
        NGR(KGV) = 0
   20 CONTINUE
*
*     --- The tangent between TP0 and TPN is ---
*         divided into NTH sub-tangents.
*         The KP-th nodal point of the LV-th
*         triangle is in the NTW(KP)-th group.
*         The NGR(KGV)-th triangle in the
*         KGV-th group is the LV-th triangle.
*
      DO 30 LV = 1, NT
        DO 40 KP = 1, 3
          XV = XFCTR * (XA(KNC(KP,LV)) - X0)
          YV = YFCTR * (YA(KNC(KP,LV)) - Y0)
          THV = (XV * CA - YV * SA + SIGMA) /
     $          (XV * SA + YV * CA + ET)
          NTW(KP) = (THV - TP0) * RTH + 1
          IF (NTW(KP) .GE. NTH + 1) THEN
            NTW(KP) = NTH
          ELSE IF (NTW(KP) .LE. 0) THEN
            NTW(KP) = 1
          END IF
   40   CONTINUE
        KGMAX = MAX(NTW(1),NTW(2),NTW(3))
        KGMIN = MIN(NTW(1),NTW(2),NTW(3))
        DO 50 KGV = KGMIN, KGMAX
          NGR(KGV) = NGR(KGV) + 1
          KGR(NGR(KGV),KGV) = LV
   50   CONTINUE
   30 CONTINUE
*
      XI = XE / XFCTR + X0
      YI = YE / YFCTR + Y0
*
      DO 110 NV = 1, NTH
*
        NGP = NGR(NV)
*
        DO 120 NGV = 1, NGP
          IREC(NGV) = NGV
          ABX(NGV) = 1.0E35
          XM = 0
          YM = 0
          DO 130 KP = 1, 3
            XM = XM + XA(KNC(KP,KGR(NGV,NV)))
            YM = YM + YA(KNC(KP,KGR(NGV,NV)))
  130     CONTINUE
          XM = XM / 3
          YM = YM / 3
          XD2 = (XM - XI)**2 + (YM - YI)**2
          IF (XD2 .LT. ABX(NGV)) THEN
            ABX(NGV) = XD2
          END IF
  120   CONTINUE
*
        CALL QSORTPLT (NGP, IREC, ABX, ISTL, ISTR)
*
        DO 140 NGV = 1, NGP
          KV(NGV) = KGR(NGV,NV)
  140   CONTINUE
        DO 150 NGV = 1, NGP
          KGR(NGV,NV) = KV(IREC(NGV))
  150   CONTINUE
*
  110 CONTINUE
*
*      WRITE (*,2001) SIGMA,TAU,ALPHA,ELD,ZSF,XSF,
*     $               XE,YE,ZE
 2001 FORMAT (' (INITP3) SIGMA=',1PE8.1,' TAU=',E8.1,
     $ ' ALPHA=',E8.1,' ELD=',E8.1/
     $   7X,' XSF=',E8.1,' ZSF=',E8.1,
     $ ' XE=',E8.1,' YE=',E8.1,' ZE=',E8.1)
*
      RETURN
      END
*
      SUBROUTINE QSORTPLT (NREC, IREC, REC, ISTL, ISTR)
*****************************************************
*     sort real data REC(I),I=1,NREC in ascending   *
*     order by quick sort + minimum selection sort  *
*  ---- input parameters ----                       *
*     NREC...total number of data                   *
*     IREC(I),I=1,NREC...index list of data         *
*                        Initially it must be       *
*                         IREC(I)=I,I=1,NREC        *
*     REC(I),I=1,NREC...data to be sorted           *
*  ---- output parameters ----                      *
*     IREC(I),I=1,NREC...The I-th data after sort   *
*             was the IREC(I)-th data before sort   *
*     REC(I),I=1,NREC...the data after sort         *
*  ---- work arrays and parameters ----             *
*     ISTL...stack for the left mark                *
*     ISTR...stack for the right mark               *
*     ISP...stack pointer                           *
*     IL...left mark                                *
*     IR...right mark                               *
*     JL...temporary left mark                      *
*     JR...temporary right mark                     *
*                                                   *
*     In order to sort in descending order replace  *
*      IF (REC(JR) .GE. RL) by IF (REC(JR) .LE. RL) *
*      IF (REC(JL) .LE. RL) by IF (REC(JL) .GE. RL) *
*     and also change MSSORT                        *
*****************************************************
      DIMENSION IREC(NREC),ISTL(NREC),ISTR(NREC)
      DIMENSION REC(NREC)
*
      ISP = 0
      IL = 1
      IR = NREC
*
    1 CONTINUE
*
      IF (IR - IL .LT. 10) THEN
*
*       ---- minimum selection sort ----
*
        CALL MSSORT (NREC, IREC, REC, IL, IR)
*
        GO TO 6
      END IF
*
*     ---- quick sort ----
*
      RL = REC(IL)
      IRL = IREC(IL)
      JL = IL
      JR = IR
*
    2 CONTINUE
*
    3 CONTINUE
      IF (JR .EQ. JL) GO TO 5
      IF (REC(JR) .GE. RL) THEN
        JR = JR - 1
        GO TO 3
      END IF
      REC(JL) = REC(JR)
      IREC(JL) = IREC(JR)
*
    4 CONTINUE
      IF (JL .EQ. JR) GO TO 5
      IF (REC(JL) .LE. RL) THEN
        JL = JL + 1
        GO TO 4
      END IF
      REC(JR) = REC(JL)
      IREC(JR) = IREC(JL)
*
      GO TO 2
*
    5 CONTINUE
      REC(JL) = RL
      IREC(JL) = IRL
*
      IF (IR .GT. JR) THEN
*
*       ---- push down right subinterval to stack ----
*
        ISP = ISP + 1
        ISTL(ISP) = JR + 1
        ISTR(ISP) = IR
      END IF
*
      IR = JL - 1
*
      IF (IL .LT. IR) GO TO 1
*
    6 CONTINUE
      IF (ISP .GT. 0) THEN
*
*       ---- pop up right subinterval from stack ----
*
        IL = ISTL(ISP)
        IR = ISTR(ISP)
        ISP = ISP - 1
        GO TO 1
      ELSE
*
*       -- stack is empty ----
*
        RETURN
      END IF
*
      END
*
      SUBROUTINE MSSORT (NREC, IREC, REC, IL, IR)
****************************************************
*    sort real data REC(I),I=IL,IR in ascending    *
*    order by minimum selection method             *
*  ---- input parameters ----                      *
*     NREC...total number of data given in REC     *
*     IREC(I),I=1,NREC...index list of data        *
*                 The I-th data was initially the  *
*                 the IREC(I)-th data              *
*      (If this routine is used independently set  *
*             IL=1,IR=NREC, IREC(I)=I,I=1,NREC)    *
*     REC(I),I=IL,IR...data to be sorted           *
*     IL...starting position in REC to be sorted   *
*     IR...end position in REC to be sorted        *
*  ---- output parameters ----                     *
*     IREC(I),I=1,NREC...The I-th data after sort  *
*             was the IREC(I)-th data before sort  *
*     REC(I),I=1,NREC...the I-th data after sort   *
*         Note that only REC(I),I=IL,IR will be    *
*         sorted                                   *
*                                                  *
*     In order to sort in descending order replace *
*         IF (REC(K) .GT. REC(J))                  *
*                   by  IF (REC(K) .LT. REC(J))    *
****************************************************
      DIMENSION IREC(NREC)
      DIMENSION REC(NREC)
*
      DO 110 I = IL+1, IR
        K = I - 1
        DO 120 J = I, IR
          IF (REC(J) .LT. REC(K)) K = J
  120   CONTINUE
        IF (K .NE. I-1) THEN
          RV = REC(K)
          REC(K) = REC(I-1)
          REC(I-1) = RV
          IV = IREC(K)
          IREC(K) = IREC(I-1)
          IREC(I-1) = IV
        END IF
  110 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE PLOT3 (X, Y, Z, IP,
     $                  NP, XA, YA, ZA, NT, KNC)
*****************************************************
*               3-dimensional plot                  *
*            with hidden line masking               *
*            over triangular network                *
*                                                   *
*     plot line segment from the present position   *
*     to the point (X,Y,Z) in 3D world coordinates  *
*     with hidden line masking where ALT plays the  *
*     role of obstacle                              *
*   ---- input parameters ----                      *
*     X,Y,Z, ... coordinates of the end point of    *
*                line segment to plot in 3D world   *
*                coordinates                        *
*     IP ... 2 or 3                                 *
*          if IP = 2  then give 3-dimensional plot  *
*             with hidden line masking              *
*          if IP = 3  then move point to (X,Y,Z)    *
*             without drawing                       *
*     NP ... total number of nodal points in the    *
*            triangular network                     *
*     (XA(I),YA(I)) ... coordinates of the I-th     *
*            nodal point of the triangular network  *
*            in user coordinates                    *
*     ZA(I) ... data of obstacle at the I-th nodal  *
*           point (XA(I),YA(I)) in user coordinates *
*     NT ... total number of triangular elements    *
*            in the network                         *
*     KNC ... connection matrix for the triangular  *
*             network                               *
*             The three nodal points of the L-th    *
*             triangular element are                *
*                  KNC(J,L),J=1,2,3                 *
*****************************************************
      COMMON / COMHLN / LHL
      COMMON / COMFRM / LZC,LAX
      COMMON / COMHL1 / CA,SA,ET,ELC,XWC,XWS,YWC,YWS,
     $                  SIGM,XSF,ZSF,XE,YE,ZE
*
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
*
      SAVE X4,Y4,Z4,XP,ZP,KVS
*
      XPS = XP
      ZPS = ZP
      KVSS = KVS
*
      V = ELC / (X * SA + Y * CA + ET)
      XP = (X * CA - Y * SA + SIGM) * V
      ZP = (Z - ZE) * V
*
      IF (LHL .EQ. 0) THEN
*
*       ---- plot without hidden line masking ----
*
        CALL PLOT (XP - XSF, ZP - ZSF, IP)
        RETURN
      END IF
*
*     ---- plot with hidden line masking ----
*
      XQ = X
      YQ = Y
      ZQ = Z
*
      CALL HLN3 (XQ, YQ, ZQ, KVS, XP, ZP,
     $           NP, XA, YA, ZA, NT, KNC)
*
      IF (IP .EQ. 3) THEN
*
*       ---- move point to (X,Y,Z)
*            without drawing ----
*
        CALL PLOT (XP - XSF, ZP - ZSF, 3)
        X4 = X
        Y4 = Y
        Z4 = Z
        RETURN
      END IF
*
*     ---- draw line from present position
*          to (X,Y,Z) with hidden line masking ----
*
      IF (KVS .NE. KVSS) THEN
        X3 = X4
        X4 = X
        Y3 = Y4
        Y4 = Y
        Z3 = Z4
        Z4 = Z
*
*       ---- find disappearing point (XB,ZB) ----
*
        CALL BISEC3 (X3, Y3, Z3, X4, Y4, Z4, 
     $               XPS, ZPS, XP, ZP, XB, ZB, KVS,
     $               NP, XA, YA, ZA, NT, KNC)
*
        IF (KVSS .EQ. 1) THEN
          IPW = 2
          IPV = 3
        ELSE
          IPW = 3
          IPV = 2
        END IF
*
*       ---- draw line from present position
*            to disappearing point ----
*
        CALL PLOT (XB - XSF, ZB - ZSF, IPW)
*
*       ---- draw line from disappearing point
*            to (X,Y,Z) ----
*
        CALL PLOT (XP - XSF, ZP - ZSF, IPV)
*
      ELSE
*
*       ---- no disappearing point exists between
*            present position and (X,Y,Z) ----
*
        IF (KVS .EQ. 1) THEN
          IPV = 2
        ELSE
          IPV = 3
        END IF
        CALL PLOT (XP - XSF, ZP - ZSF, IPV)
      END IF
*
      X4 = X
      Y4 = Y
      Z4 = Z
*
      RETURN
      END
*
      SUBROUTINE BISEC3 (X3, Y3, Z3, X4, Y4, Z4,
     $           XPS, ZPS, XP, ZP, XB, ZB, KVS,
     $           NP, XA, YA, ZA, NT, KNC)
*****************************************************
*          find disappearing point (XB,ZB)          *
*               by bisection method                 *
*   ---- input parameters ----                      *
*     X3, Y3, Z3, X4, Y4, Z4, XPS, ZPS, XP, ZP ...  *
*        search between (X3,Y3,Z3) and (X4,Y4,Z4)   *
*         in 3D world coordinates or equivalently   *
*        search between (XPS,ZPS) and (XP,ZP) in    *
*         2D world coordinates on the view plane    *
*       (XPS,ZPS) is the projection of (X3,Y3,Z3)   *
*         in 2D world coordinates on the view plane *
*       (XP,ZP) is the projection of (X4,Y4,Z4)     *
*         in 2D world coordinates on the view plane *
*     KVS ... if (XBS,ZBS) was visible then set -1  *
*             else set 1                            *
*     See comments in PLOT3 for other parameters    *
*   ---- output parameters ----                     *
*     (XB,ZB) ... disappearing point in 2D world    *
*                 coordinates on the view plane     *
*     KVS ... if (XB,ZB) is visible then return -1  *
*                                   else return 1   *
*****************************************************
      COMMON / COMHL1 / CA,SA,ET,ELC,XWC,XWS,YWC,YWS,
     $                  SIGM,XSF,ZSF,XE,YE,ZE
      COMMON / COMHL4 / PX,PZ,PX1,PZ1
*
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
*
*     ---- search disappearing point
*             by bisection method ----
*
      XB = XP
      ZB = ZP
*
      XQ = X4
      YQ = Y4
      ZQ = Z4
*
      DX = -0.5 * (X4 - X3)
      DY = -0.5 * (Y4 - Y3)
      DZ = -0.5 * (Z4 - Z3)
*
      DMX = MAX (ABS(DX),ABS(DY),ABS(DZ))
      IF (DMX .LE. 0.5) THEN
        LEND = 4
      ELSE IF (DMX .LE. 2.0) THEN
        LEND = 6
      ELSE
        LEND = 8
      END IF
*
      DO 130 L = 1, LEND
*
        XQ = XQ + DX
        YQ = YQ + DY
        ZQ = ZQ + DZ
        XBS = XB
        ZBS = ZB
        V = ELC / (XQ * SA + YQ * CA + ET)
        XB = (XQ * CA - YQ * SA + SIGM) * V
        ZB = (ZQ - ZE) * V
        KVSS = KVS
*
        IF (L .EQ. LEND) GO TO 132
*
        CALL HLN3 (XQ, YQ, ZQ, KVS, XB, ZB,
     $             NP, XA, YA, ZA, NT, KNC)
*
        IF ((ABS(XB - XBS) .LE. PX) .AND.
     $      (ABS(ZB - ZBS) .LE. PZ)) GO TO 132
*
        IF (KVS .EQ. KVSS) THEN
          DX =  0.5 * DX
          DY =  0.5 * DY
          DZ =  0.5 * DZ
        ELSE
          DX = -0.5 * DX
          DY = -0.5 * DY
          DZ = -0.5 * DZ
        END IF
*
  130 CONTINUE
*
  132 CONTINUE
*
      IF ((ABS(XB - XP) .LE. PX1) .AND.
     $    (ABS(ZB - ZP) .LE. PZ1)) THEN
        XB = XP
        ZB = ZP
      ELSE IF ((ABS(XB - XPS) .LE. PX1) .AND.
     $         (ABS(ZB - ZPS) .LE. PZ1)) THEN
        XB = XPS
        ZB = ZPS
      END IF
*
      RETURN
      END
*
      SUBROUTINE HLN3 (XQ, YQ, ZQ, KVS, XP, ZP,
     $                 NP, XA, YA, ZA, NT, KNC)
*****************************************************
*       determine whether the objecive point        *
*           (XQ,YQ,ZQ) is visible or not            *
*             over triangular network               *
*                                                   *
*   ---- input parameters ----                      *
*       (XQ,YQ,ZQ) ... the objective point in 3D    *
*                      world coordinates            *
*       (XP,ZP) ... projection of (XQ,YQ,ZQ) on the *
*                view plane in 2D world coordinates *
*        See comments in PLOT3 for other parameters *
*   ---- output parameter ----                      *
*       KVS ... 1 or -1                             *
*          if (XQ,YQ,ZQ) is visible then return 1   *
*                                   else return -1  *
*****************************************************
      COMMON / COMZCL / LZCLP,ZMN,ZMX
*
c      PARAMETER (MTH = 128, NTH = 32)
      PARAMETER (MTH = 512, NTH = 128)
      COMMON / COMDVD / TP0,TPN,RTH,
     $                  NGR(NTH),KGR(MTH,NTH)
*
      COMMON / COMHL1 / CA,SA,ET,ELC,XWC,XWS,YWC,YWS,
     $                  SIGM,XSF,ZSF,XE,YE,ZE
*
      COMMON / COMGFX / X0A,XWA,XFCTR,RXFCT,HXFC,RHX
      COMMON / COMGFY / Y0A,YWA,YFCTR,RYFCT,HYFC,RHY
      COMMON / COMGFZ / Z0A,ZWA,ZFCTR
*
      DIMENSION XA(NP),YA(NP),ZA(NP)
      DIMENSION KNC(3,NT)
*
      DIMENSION XV(4),YV(4),ZV(4)
*
      SAVE K0
*
      DATA EPS / 1.0E-4 /
      DATA K0 / 1 /
*
*     ---- find line segment crossing the line ----
*        connecting the eye and the object point
*
      TQ = (XQ * CA - YQ * SA + SIGM) /
     $     (XQ * SA + YQ * CA + ET)
*
      NTV = (TQ - TP0) * RTH + 1
*
*     --- (XQ,YQ) belongs to the NTV-th group ---
*
      IF (NTV .GE. NTH + 1) THEN
        NTV = NTH
      ELSE IF (NTV .LE. 0) THEN
        NTV = 1
      END IF
*
      XR = XQ / XFCTR + X0A
      YR = YQ / YFCTR + Y0A
*
      U = (CA - XP / ELC * SA) / YFCTR
      V = (XP / ELC * CA + SA) / XFCTR
*
      WR = U * XR - V * YR
*
      KVS = 1
*
      NEND = NGR(NTV)
*
      IF ((K0 .LT. 1) .OR. (K0 .GT. NEND)) THEN
        K0 = 1
      END IF
*
      JC = 0
      JSGN = -1
*
      DO 10 NGV = 1, NEND
*
*       --- check prodeeds as
*           K0, K0+1, K0-1, K0+2, K0-2, ... ---
*
        IF (JC .EQ. 0) THEN
          KGV = K0 + JSGN * (NGV / 2)
          JSGN = -JSGN
          IF (KGV .LT. 1) THEN
            KGV = KGVS + 1
            JC = 1
          ELSE IF (KGV .GT. NEND) THEN
            KGV = KGVS - 1
            JC = -1
          END IF
          KGVS = KGV
        ELSE
          KGV = KGV + JC
        END IF
*
        LV = KGR(KGV,NTV)
*
        LC = 0
        KPU = 0
        KPV = 0
*
        DO 20 KP = 1, 3
*
          K1 = KNC(KP,LV)
          IF (KP .EQ. 1) THEN
            K2 = KNC(2,LV)
          ELSE IF (KP .EQ. 2) THEN
            K2 = KNC(3,LV)
          ELSE
            K2 = KNC(1,LV)
          END IF
*
          UV1 = U * XA(K1) - V * YA(K1)
          UV2 = U * XA(K2) - V * YA(K2)
*
          IF ((WR - UV1) * (WR - UV2) .LT. 0) THEN
            XD = XA(K2) - XA(K1)
            YD = YA(K2) - YA(K1)
            WA = XA(K1) * YA(K2) - XA(K2) * YA(K1)
            RD = 1 / (U * XD - V * YD)
            XUA = (XD * WR - V * WA) * RD
            XUF = (XUA - X0A) * XFCTR
            YUA = (YD * WR - U * WA) * RD
            IF (ABS(XUF - XE) .LT. ABS(XQ - XE)) THEN
              LC = LC + 1
              XV(LC) = XUF
              YV(LC) = (YUA - Y0A) * YFCTR
              IF (ABS(XD) .GT. EPS) THEN
                ZV(LC) = (ZA(K1) + (XUA - XA(K1))
     $                 / XD * (ZA(K2) - ZA(K1))
     $                 - Z0A) * ZFCTR
              ELSE
                ZV(LC) = (ZA(K1) + (YUA - YA(K1))
     $                 / YD * (ZA(K2) - ZA(K1))
     $                 - Z0A) * ZFCTR
              END IF
            ELSE
              KPU = KP
            END IF
*
          ELSE IF ((WR - UV1) * (WR - UV2) .GT. 0)
     $      THEN
            GO TO 20
*
          ELSE IF ((WR - UV1) .EQ. 0) THEN
            XAF = (XA(K1) - X0A) * XFCTR
            ZAF = (ZA(K1) - Z0A) * ZFCTR
            IF (ABS(XAF - XE) .LT. ABS(XQ - XE))
     $          THEN
              IF ((XAF .NE. XQ) .OR.
     $            (ZAF .NE. ZQ)) THEN
                LC = LC + 1
                XV(LC) = XAF
                YV(LC) = (YA(K1) - Y0A) * YFCTR
                ZV(LC) = ZAF
              END IF
            ELSE
              KPV = KP
            END IF
*
          END IF
*
   20   CONTINUE
*
        IF ((LC .EQ. 1) .AND. (KPU .GT. 0)) THEN
*
*         ---- (XQ,YQ) is in the triangle ----
*
          K1 = KNC(KPU,LV)
          IF (KPU .EQ. 1) THEN
            K2 = KNC(2,LV)
          ELSE IF (KPU .EQ. 2) THEN
            K2 = KNC(3,LV)
          ELSE
            K2 = KNC(1,LV)
          END IF
*
          XD = XA(K2) - XA(K1)
          YD = YA(K2) - YA(K1)
          WA = XA(K1) * YA(K2) - XA(K2) * YA(K1)
          RD = 1 / (U * XD - V * YD)
          XUA = (XD * WR - V * WA) * RD
          YUA = (YD * WR - U * WA) * RD
          IF (ABS(XD) .GT. EPS) THEN
            ZUF = (ZA(K1) + (XUA - XA(K1)) / XD
     $          * (ZA(K2) - ZA(K1))
     $          - Z0A) * ZFCTR
          ELSE
            ZUF = (ZA(K1) + (YUA - YA(K1)) / YD
     $          * (ZA(K2) - ZA(K1))
     $          - Z0A) * ZFCTR
          END IF
          LC = LC + 1
          XV(LC) = XQ
          YV(LC) = YQ
          ZV(LC) = ZV(LC-1) + (XQ - XV(LC-1))
     $           / ((XUA - X0A) * XFCTR - XV(LC-1))
     $           * (ZUF - ZV(LC-1))
        ELSE IF ((LC .EQ. 1) .AND. (KPV .GT. 0)) THEN
*
*         ---- (XQ,YQ) is on the edge ----
*                 of the triangle
*
          LC = LC + 1
          XV(LC) = XQ
          YV(LC) = YQ
          XAF = (XA(KNC(KPV,LV)) - X0A) * XFCTR
          ZAF = (ZA(KNC(KPV,LV)) - Z0A) * ZFCTR
          ZV(LC) = ZV(LC-1) + (XQ - XV(LC-1))
     $           / (XAF - XV(LC-1))
     $           * (ZAF - ZV(LC-1))
*
        END IF
*
        LCT = LC
*
*       ---- clip at upper and lower bounds of z ----
*
        IF (LZCLP .EQ. 1) THEN
*
          IF (LCT .EQ. 2) THEN
*
            IF (ZV(2) .LT. ZV(1)) THEN
              XVV = XV(1)
              YVV = YV(1)
              ZVV = ZV(1)
              XV(1) = XV(2)
              YV(1) = YV(2)
              ZV(1) = ZV(2)
              XV(2) = XVV
              YV(2) = YVV
              ZV(2) = ZVV
            END IF
*
            IF (ZV(1) .GE. ZMN) THEN
              IF (ZV(2) .LE. ZMX) THEN
                CONTINUE
              ELSE IF (ZV(1) .GT. ZMX) THEN
                ZV(1) = ZMX
                ZV(2) = ZMX
              ELSE
                LCT = 3
                XV(3) = XV(2)
                YV(3) = YV(2)
                ZV(3) = ZMX
                RT2 = (ZMX - ZV(1)) / (ZV(2) - ZV(1))
                XV(2) = XV(1) + RT2 * (XV(2) - XV(1))
                YV(2) = YV(1) + RT2 * (YV(2) - YV(1))
                ZV(2) = ZMX
              END IF
            ELSE
              IF (ZV(2) .LT. ZMN) THEN
                ZV(1) = ZMN
                ZV(2) = ZMN
              ELSE IF (ZV(2) .LE. ZMX) THEN
                LCT = 3
                XV(3) = XV(2)
                YV(3) = YV(2)
                ZV(3) = ZV(2)
                RT1 = (ZMN - ZV(1)) / (ZV(2) - ZV(1))
                XV(2) = XV(1) + RT1 * (XV(2) - XV(1))
                YV(2) = YV(1) + RT1 * (YV(2) - YV(1))
                ZV(2) = ZMN
                ZV(1) = ZMN
              ELSE
                LCT = 4
                XV(4) = XV(2)
                YV(4) = YV(2)
                ZV(4) = ZMX
                RT1 = (ZMN - ZV(1)) / (ZV(2) - ZV(1))
                XV(2) = XV(1) + RT1 * (XV(2) - XV(1))
                YV(2) = YV(1) + RT1 * (YV(2) - YV(1))
                RT2 = (ZMX - ZV(1)) / (ZV(2) - ZV(1))
                XV(3) = XV(1) + RT2 * (XV(2) - XV(1))
                YV(3) = YV(1) + RT2 * (YV(2) - YV(1))
                ZV(1) = ZMN
                ZV(2) = ZMN
                ZV(3) = ZMX
              END IF
            END IF
*
          END IF
*
        END IF
*
*       ---- check whether (XQ,YQ,ZQ) is ----
*                  visible or not
*
        KHL = 0
*
        DO 30 LC = 1, LCT
*
          ZPV = (ZV(LC) - ZE)
     $        / (XV(LC) * SA + YV(LC) * CA + ET)
     $        * ELC
*
          IF (KHL .EQ. 0) THEN
            IF (ZPV .GT. ZP + EPS) THEN
              KHL = 1
            ELSE IF (ZPV .LT. ZP - EPS) THEN
              KHL = -1
            END IF
*
          ELSE IF (KHL .EQ. 1) THEN
            IF (ZPV .LE. ZP - EPS) THEN
              KVS = -1
              K0 = KGV
              RETURN
            END IF
*
          ELSE IF (KHL .EQ. -1) THEN
            IF (ZPV .GE. ZP + EPS) THEN
              KVS = -1
              K0 = KGV
              RETURN
            END IF
          END IF
* 
   30   CONTINUE
*
   10 CONTINUE
*
      RETURN
      END
