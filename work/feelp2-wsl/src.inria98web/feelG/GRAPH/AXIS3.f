      SUBROUTINE AXIS3 (XW, YW, ZW, MX, MY, MZ,
     $                  X0, Y0, Z0, XN, YN, ZN,
     $                  HGT, IFMTX, IFMTY, IFMTZ,
     $                  NP, XA, YA, NT, KNC)
*****************************************************
*      3-dimensional plot of axis and number        *
*             over triangular network               *
*                   1989.9.12.                      *
*             copyright : Masatake Mori             *
*     (XW,YW,ZW) ... size of the right angled       *
*                   parallelepiped domain           *
*                   in 3D world coordinates         *
*     MX ... (0,XW) is divided into MX equal sub-   *
*              intervals and MX+1 short dashes      *
*              parallel to Y-axis are plotted       *
*     MY ... (0,YW) is divided into MY equal sub-   *
*              intervals and MY+1 short dashes      *
*              parallel to X-axis are plotted       *
*     MZ ... (0,ZW) is divided into MZ equal sub-   *
*              intervals and MZ+1 short dashes      *
*              parallel to X-axis are plotted       *
*     (X0,Y0,Z0) ... lower bound of the right       *
*                   angled parallelepiped domain    *
*                   in user coordinates             *
*     (XN,YN,ZN) ... upper bound of the right       *
*                   angled parallelepiped domain    *
*                   in user coordinates             *
*     HGT ... height of number in world coordinate  *
*     IFMTX ... format of the number to plot        *
*               along X axis : example '(F4.1)'     *
*     IFMTY ... format of the number to plot        *
*               along Y axis : example '(F4.1)'     *
*     IFMTZ ... format of the number to plot        *
*               along Z axis : example '(F4.1)'     *
*     IFMTY ... format of number to plot            *
*               example '(F4.1)'                    *
*     NP ... total number of nodal points in the    *
*            triangular network                     *
*     (XA(I),YA(I)) ... coordinates of the I-th     *
*            nodal point of the triangular network  *
*            in user coordinates                    *
*     NT ... total number of triangular elements    *
*            in the network                         *
*     KNC ... connection matrix for the triangular  *
*             network                               *
*             The three nodal points of the L-th    *
*             triangular element are                *
*                  KNC(J,L),J=1,2,3                 *
*****************************************************
      PARAMETER (NUA = 1000)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      DIMENSION XA(NP),YA(NP)
      DIMENSION KNC(3,NT)
*
      CHARACTER*(*) IFMTX,IFMTY,IFMTZ
*
      IAX1 = 0
      IAX4 = 0
*
      Z = 0.0
*
      NU = 0
      CALL AXISCX (XW, YW, MX, IAX1, IAX4,
     $             NU, XU, YU, IPU)
      DO 10 JU = 1, NU
        CALL PLOT3 (XU(JU), YU(JU), Z, IPU(JU),
     $              NP, XA, YA, ZA, NT, KNC)
   10 CONTINUE
*
      NU = 0
      CALL AXISCY (YW, XW, MY, IAX1, IAX4,
     $             NU, XU, YU, IPU)
      DO 20 JU = 1, NU
        CALL PLOT3 (XU(JU), YU(JU), Z, IPU(JU),
     $              NP, XA, YA, ZA, NT, KNC)
   20 CONTINUE
*
      Y = 0.0
*
      NU = 0
      CALL AXISCY (ZW, XW, MZ, IAX1, IAX4,
     $             NU, XU, YU, IPU)
      DO 30 JU = 1, NU
        CALL PLOT3 (XU(JU), Y, YU(JU), IPU(JU),
     $              NP, XA, YA, ZA, NT, KNC)
   30 CONTINUE
*
      Z = 0.0
      IAX2 = 0
      IAX3 = 0
*
      NU = 0
      CALL AXINCX (X0, XN, XW, MX, HGT, IFMTX,
     $             IAX1, IAX2, IAX3,
     $             NU, XU, YU, IPU)
      DO 40 JU = 1, NU
        CALL PLOT3 (XU(JU), YU(JU), Z, IPU(JU),
     $              NP, XA, YA, ZA, NT, KNC)
   40 CONTINUE
*
      IAX3 = 1
*
      NU = 0
      CALL AXINCY (Y0, YN, YW, MY, HGT, IFMTY,
     $             IAX1, IAX2, IAX3,
     $             NU, XU, YU, IPU)
      DO 50 JU = 1, NU
        CALL PLOT3 (XU(JU), YU(JU), Z, IPU(JU),
     $              NP, XA, YA, ZA, NT, KNC)
   50 CONTINUE
*
      Y = 0.0
      IAX3 = 0
*
      NU = 0
      CALL AXINCY (Z0, ZN, ZW, MZ, HGT, IFMTZ,
     $             IAX1, IAX2, IAX3,
     $             NU, XU, YU, IPU)
      DO 60 JU = 1, NU
        CALL PLOT3 (XU(JU), Y, YU(JU), IPU(JU),
     $              NP, XA, YA, ZA, NT, KNC)
   60 CONTINUE
*
      RETURN
      END
