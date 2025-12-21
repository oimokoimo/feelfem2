      SUBROUTINE AXINX (X0, XN, XW, MX, HGT, IFMTX)
*****************************************************
*        plot numbers for X variable in grid        *
*             plotted by AXISX or GRIDX             *
*                    1989.11.28.                    *
*             copyright : Masatake Mori             *
*   ---- input parameters ----                      *
*    X0,XN,XW,MX,HGT,IFMTX                          *
*    See comments in AXINCX                         *
*****************************************************
      PARAMETER (NUA = 500)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      CHARACTER*(*) IFMTX
*
      IAX1 = 0
      IAX2 = 0
      IAX3 = 0
*
      NU = 0
      CALL AXINCX (X0, XN, XW, MX, HGT, IFMTX,
     $             IAX1, IAX2, IAX3,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE AXINY (Y0, YN, YW, MY, HGT, IFMTY)
*****************************************************
*        plot numbers for Y variable in grid        *
*             plotted by AXISY or GRIDY             *
*   ---- input parameters ----                      *
*    Y0,YN,YW,MY,HGT,IFMTY                          *
*    See comments in AXINCY                         *
*****************************************************
      PARAMETER (NUA = 500)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      CHARACTER*(*) IFMTY
*
      IAX1 = 0
      IAX2 = 0
      IAX3 = 0
*
      NU = 0
      CALL AXINCY (Y0, YN, YW, MY, HGT, IFMTY,
     $             IAX1, IAX2, IAX3,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE AXINCX (X0, XN, XW, MX, HGT, IFMTX,
     $                   IAX1, IAX2, IAX3,
     $                   NU, XU, YU, IPU)
*****************************************************
*            compute stroke pattern of              *
*             numbers for X variable                *
*   ---- input parameters ----                      *
*    (X0,XN) ... bound of X variable for rectangu-  *
*               lar domain in user coordinate       *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*     MX ... (0,XW) is divided into MX equal strip  *
*           subdomains and value of X corresponding *
*           to each of MX+1 grid lines parallel to  *
*           Y-axis is plotted                       *
*     HGT ... height of number in world coordinate  *
*     IFMTX ... format of number to plot            *
*               example '(F4.1)'                    *
*     IAX1 ... 0 or 1                               *
*              if 0 then plot number to negative Y  *
*              if 1 then plot number to positive Y  *
*     IAX2 ... 0 or 1                               *
*              if 0 then plot number in ascending   *
*                   order                           *
*              if 1 then plot number in descending  *
*                   order                           *
*     IAX3 ... 0 or 1                               *
*              if 0 then plot number at X = X0      *
*              if 1 then not plot number at X = X0  *
*****************************************************
      DOUBLE PRECISION DC
      INTEGER IC
*
      CHARACTER*(*) IFMTX
*
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      TH = 0.0
*
      INUMB = 1
      LXYZ = 1
*
      HDX = XW / MX
      HCX = (XN - X0) / MX
*
      CALL NDC (IFMTX, ND)
      CALL NCC (IFMTX, NC)
*
      IF (IAX1 .EQ. 0) THEN
        DX = -HGT * 0.3 - HGT * (NC - ND - 1)
        DY = -HGT * 2.0
      ELSE
        DX = -HGT * 0.3 - HGT * (NC - ND - 1)
        DY =  HGT
      END IF
*
      IF (IAX2 .EQ. 0) THEN
        CX = X0
      ELSE
        CX = XN
        HCX = -HCX
      END IF
*
      IF (IAX3 .EQ. 1) THEN
        IF (IAX2 .EQ. 0) THEN
          DX = DX + HDX
          CX = CX + HCX
          IS = 1
          IL = MX
        ELSE
          IS = 0
          IL = MX - 1
        END IF
      ELSE
        IS = 0
        IL = MX
      END IF
*
      DO 30 I = IS, IL
        CALL NUMBSC (DX, DY, HGT, TH, IFMTX, LXYZ,
     $              INUMB, CX, DC, IC,
     $              NU, XU, YU, IPU)
        DX = DX + HDX
        CX = CX + HCX
   30 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE AXINCY (Y0, YN, YW, MY, HGT, IFMTY,
     $                   IAX1, IAX2, IAX3,
     $                   NU, XU, YU, IPU)
*****************************************************
*            compute stroke pattern of              *
*             numbers for Y variable                *
*   ---- input parameters ----                      *
*    (Y0,YN) ... bound of Y variable for rectangu-  *
*               lar domain in user coordinate       *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*     MY ... (0,YW) is divided into MY equal strip  *
*           subdomains and value of Y corresponding *
*           to each of MY+1 grid lines parallel to  *
*           X-axis is plotted                       *
*     HGT ... height of number in world coordinate  *
*     IFMTY ... format of number to plot            *
*               example '(F4.1)'                    *
*     IAX1 ... 0 or 1                               *
*              if 0 then plot number to negative X  *
*              if 1 then plot number to positive X  *
*     IAX2 ... 0 or 1                               *
*              if 0 then plot number in ascending   *
*                   order                           *
*              if 1 then plot number in descending  *
*                   order                           *
*     IAX3 ... 0 or 1                               *
*              if 0 then plot number at Y = Y0      *
*              if 1 then not plot number at Y = Y0  *
*****************************************************
      DOUBLE PRECISION DC
      INTEGER IC
*
      CHARACTER*(*) IFMTY
*
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      TH = 0.0
*
      INUMB = 1
      LXYZ = 1
*
      HDY = YW / MY
      HCY = (YN - Y0) / MY
*
      CALL NCC (IFMTY, NC)
*
      IF (IAX1 .EQ. 0) THEN
        DX = - HGT * 0.5 - HGT * NC
        DY = -0.5 * HGT
      ELSE
        DX = HGT * 0.75
        DY = -0.5 * HGT
      END IF
*
      IF (IAX2 .EQ. 0) THEN
        CY = Y0
      ELSE
        CY = YN
        HCY = -HCY
      END IF
*
      IF (IAX3 .EQ. 1) THEN
        IF (IAX2 .EQ. 0) THEN
          DY = DY + HDY
          CY = CY + HCY
          IS = 1
          IL = MY
        ELSE
          IS = 0
          IL = MY - 1
        END IF
      ELSE
        IS = 0
        IL = MY
      END IF
*
      DO 60 I = IS, IL
        CALL NUMBSC (DX, DY, HGT, TH, IFMTY, LXYZ,
     $               INUMB, CY, DC, IC,
     $               NU, XU, YU, IPU)
        DY = DY + HDY
        CY = CY + HCY
   60 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE LAXNX (XW, NXMIN, NXMAX, NPX, HGT)
*****************************************************
*    plot numbers for X variable in power-of-10     *
*    format like 5*10**-3 in logarithmic scale      *
*   ---- input parameters ----                      *
*    XW,NXMIN,NXMAX,NPX,HGT                         *
*      See comments in LAXNCX                       *
*****************************************************
      PARAMETER (NUA = 500)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL LAXNCX (XW, NXMIN, NXMAX, NPX, HGT,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE LAXNY (YW, NYMIN, NYMAX, NPY, HGT)
*****************************************************
*    plot numbers for Y variable in power-of-10     *
*    format like 5*10**-3 in logarithmic scale grid *
*   ---- input parameters ----                      *
*    YW,NYMIN,NYMAX,NPY,HGT                         *
*      See comments in LAXNCY                       *
*****************************************************
      PARAMETER (NUA = 500)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL LAXNCY (YW, NYMIN, NYMAX, NPY, HGT,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE LAXNCX (XW, NXMIN, NXMAX, NPX, HGT,
     $                   NU, XU, YU, IPU)
*****************************************************
*            compute stroke pattern of              *
*    numbers for X variable in power-of-10  format  *
*    like 5*10**-3 in logarithmic scale             *
*   ---- input parameters ----                      *
*    XW,NXMIN,NXMAX,NPX,NHX                         *
*      See comments in LAXICX                       *
*    HGT...height of number 10                      *
*    The numers                                     *
*        10**M, M=NXMIN,NXMAX (if NPX is positive)  *
*    or                                             *
*        10**M, M=NXMIN,NXMAX,ABS(NPX)              *
*                             (if NPX is negative)  *
*    will be plotted                                *
*    These values will be stored in                 *
*         (XP(I),I=1,NXMAX-NXMIN+1)                 *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      CHARACTER*16 IFMTX
*
      DIMENSION XP(101),XL(101)
*
      MX = NXMAX - NXMIN
      FCX = XW / MX
*
      IF (NPX .GT. 0) THEN
        NPXABS = 1
      ELSE
        NPXABS = ABS(NPX)
      END IF
*
      IX = 0
      DO 30 I = NXMIN, NXMAX, NPXABS
        IX = IX + 1
        XL(IX) = (I - NXMIN) * FCX
        XP(IX) = EXP(2.302585 * I)
   30 CONTINUE
      IXL = IX
*
      N0 = 0
      DY = -2.0 * HGT
      DO 40 IX = 1, IXL
        DX = XL(IX) - 2.0 * HGT
        CALL NUMBPC (DX, DY, HGT, XP(IX), TH, N0,
     $               NU, XU, YU, IPU)
   40 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE LAXNCY (YW, NYMIN, NYMAX, NPY, HGT,
     $                   NU, XU, YU, IPU)
*****************************************************
*            compute stroke pattern of              *
*    numbers for Y variable in power-of-10  format  *
*    like 5*10**-3 in logarithmic scale             *
*   ---- input parameters ----                      *
*    YW,NYMIN,NYMAX,NPY,NHY                         *
*      See comments in LAXICY                       *
*    HGT...height of number 10                      *
*    The numers                                     *
*        10**M, M=NYIN,NYMAX (if NPY is positive)  *
*    or                                             *
*        10**M, M=NYMIN,NYMAX,ABS(NPY)              *
*                             (if NPY is negative)  *
*    will be plotted                                *
*    These values will be stored                    *
*         (YP(I),I=1,NYMAX-NYMIN+1)                 *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      CHARACTER*16 IFMTY
*
      DIMENSION YP(101),YL(101)
*
      MY = NYMAX - NYMIN
      FCY = YW / MY
*
      IF (NPY .GT. 0) THEN
        NPYABS = 1
      ELSE
        NPYABS = ABS(NPY)
      END IF
*
      IY = 0
      DO 70 I = NYMIN, NYMAX, NPYABS
        IY = IY + 1
        YL(IY) = (I - NYMIN) * FCY
        YP(IY) = EXP(2.302585 * I)
   70 CONTINUE
      IYL = IY
*
      N0 = 0
      DX = -5.5 * HGT
      DO 80 IY= 1, IYL
        DY = YL(IY) - 0.5 * HGT
        CALL NUMBPC (DX, DY, HGT, YP(IY), TH, N0,
     $               NU, XU, YU, IPU)
   80 CONTINUE
*
      RETURN
      END
