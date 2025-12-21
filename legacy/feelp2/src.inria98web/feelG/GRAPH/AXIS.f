      SUBROUTINE AXISX (XW, YW, MX, IAX1, IAX4)
*****************************************************
*              plot of X axis line                  *
*                    1990.1.29.                     *
*            copyright : Masatake Mori              *
*   ---- input parameters ----                      *
*     XW,YW,MX                                      *
*     See comments in AXISCX                        *
*****************************************************
      PARAMETER (NUA = 100)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL AXISCX (XW, YW, MX, IAX1, IAX4,
     $             NU, XU, YU, IPU)
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE AXISY (YW, XW, MY, IAX1, IAX4)
*****************************************************
*              plot of Y axis line                  *
*   ---- input parameters ----                      *
*     XW,YW,MY                                      *
*     See comments in AXISCY                        *
*****************************************************
      PARAMETER (NUA = 100)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL AXISCY (YW, XW, MY, IAX1, IAX4,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE AXISCX (XW, YW, MX, IAX1, IAX4,
     $                   NU, XU, YU, IPU)
*****************************************************
*       compute stroke pattern of X axis line       *
*   ---- input parameters ----                      *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*     MX ... (0,XW) is divided into MX equal sub-   *
*              intervals and MX+1 short dashes      *
*              parallel to Y-axis are plotted       *
*     IAX1 ... 0 or 1                               *
*              if 0 then plot dash to negative Y    *
*              if 1 then plot dash to positive Y    *
*     IAX4 ... 0 or 1                               *
*              if 0 then plot X axis and dashes     *
*              if 1 then plot only dashes           *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      IF (IAX4 .EQ. 0) THEN
        CALL PUSTOR (0.0, 0.0, 3, NU, XU, YU, IPU)
        CALL PUSTOR ( XW, 0.0, 2, NU, XU, YU, IPU)
      END IF
*
      HDX = XW / MX
      IF (IAX1 .EQ. 0) THEN
        DY = -YW / 100
      ELSE
        DY =  YW / 100
      END IF
*
      DO 110 J = 0, MX
        DX = HDX * J
        CALL PUSTOR (DX, 0.0, 3, NU, XU, YU, IPU)
        CALL PUSTOR (DX,  DY, 2, NU, XU, YU, IPU)
  110 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE AXISCY (YW, XW, MY, IAX1, IAX4,
     $                   NU, XU, YU, IPU)
*****************************************************
*       compute stroke pattern of Y axis line       *
*   ---- input parameters ----                      *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*     MY ... (0,YW) is divided into MY equal sub-   *
*              intervals and MY+1 short dashes      *
*              parallel to X-axis are plotted       *
*     IAX1 ... 0 or 1                               *
*              if 0 then plot dash to negative X    *
*              if 1 then plot dash to positive X    *
*     IAX4 ... 0 or 1                               *
*              if 0 then plot Y axis and dashes     *
*              if 1 then plot only dashes           *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      IF (IAX4 .EQ. 0) THEN
        CALL PUSTOR (0.0, 0.0, 3, NU, XU, YU, IPU)
        CALL PUSTOR (0.0,  YW, 2, NU, XU, YU, IPU)
      END IF
*
      HDY = YW / MY
      IF (IAX1 .EQ. 0) THEN
        DX = -XW / 100
      ELSE
        DX =  XW / 100
      END IF
*
      DO 120 J = 0, MY
        DY = HDY * J
        CALL PUSTOR (0.0, DY, 3, NU, XU, YU, IPU)
        CALL PUSTOR ( DX, DY, 2, NU, XU, YU, IPU)
  120 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE GRIDX (XW, YW, MX)
*****************************************************
*       plot of grid lines parallel to Y-axis       *
*   ---- input parameters ----                      *
*     XW,YW,MX                                      *
*     See comments in GRIDCX                        *
*****************************************************
      PARAMETER (NUA = 100)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL GRIDCX (XW, YW, MX,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE GRIDY (YW, XW, MY)
*****************************************************
*       plot of grid lines parallel to Y-axis       *
*   ---- input parameters ----                      *
*     YW,XW MY                                      *
*     See comments in GRIDCY                        *
*****************************************************
      PARAMETER (NUA = 100)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL GRIDCY (YW, XW, MY,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE GRIDCX (XW, YW, MX,
     $                   NU, XU, YU, IPU)
*****************************************************
*       compute stroke pattern of grid lines        *
*                parallel to Y-axis                 *
*   ---- input parameters ----                      *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*     MX ... (0,XW) is divided into MX equal strip  *
*              subdomains and MX+1 grid lines       *
*              parallel to Y-axis are plotted       *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      HDX = XW / MX
*
      DO 110 J = 0, MX
        DX = HDX * J
        IF (MOD(J,2) .EQ. 0) THEN
          CALL PUSTOR (DX, 0.0, 3, NU, XU, YU, IPU)
          CALL PUSTOR (DX,  YW, 2, NU, XU, YU, IPU)
        ELSE
          CALL PUSTOR (DX,  YW, 3, NU, XU, YU, IPU)
          CALL PUSTOR (DX, 0.0, 2, NU, XU, YU, IPU)
        END IF
  110 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE GRIDCY (YW, XW, MY,
     $                   NU, XU, YU, IPU)
*****************************************************
*       compute stroke pattern of grid lines        *
*                parallel to X-axis                 *
*   ---- input parameters ----                      *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*     MY ... (0,YW) is divided into MY equal strip  *
*              subdomains and MY+1 grid lines       *
*              parallel to X-axis are plotted       *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      HDY = YW / MY
*
      DO 120 J = 0, MY
        DY = HDY * J
        IF (MOD(J,2) .EQ. 0) THEN
          CALL PUSTOR (0.0, DY, 3, NU, XU, YU, IPU)
          CALL PUSTOR ( XW, DY, 2, NU, XU, YU, IPU)
        ELSE
          CALL PUSTOR ( XW, DY, 3, NU, XU, YU, IPU)
          CALL PUSTOR (0.0, DY, 2, NU, XU, YU, IPU)
        END IF
  120 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE LAXIX (XW, YW, NXMIN, NXMAX,
     $                  NPX, NHX)
*****************************************************
*         logarithmic plot of X-axis line           *
*   ---- input parameters ----                      *
*     XW,YW,NXMIN,NXMAX,NPX,NHX                     *
*       See comments in LAXICX                      *
*****************************************************
      DIMENSION NHX(9)
*
      PARAMETER (NUA = 100)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL LAXICX (XW, YW, NXMIN, NXMAX, NPX, NHX,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE LAXIY (YW, XW, NYMIN, NYMAX,
     $                  NPY, NHY)
*****************************************************
*         logarithmic plot of Y-axis line           *
*   ---- input parameters ----                      *
*     YW,XW,NYMIN,NYMAX,NPY,NHY                     *
*       See comments in LAXICY                      *
*****************************************************
      DIMENSION NHY(9)
*
      PARAMETER (NUA = 100)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL LAXICY (YW, XW, NYMIN, NYMAX, NPY, NHY,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE LAXICX (XW, YW, NXMIN, NXMAX,
     $                   NPX, NHX,
     $                   NU, XU, YU, IPU)
*****************************************************
*            compute stroke pattern of              *
*         logarithmic scale X-axis line             *
*   ---- input parameters ----                      *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*     NXMIN,NXMAX...                                *
*       It is assumed that range of x variable in   *
*       user coordinate is (10**NXMIN, 10**NXMAX)   *
*       in logarithmic scale which corresponds to   *
*       (0,XW) in world coordinate                  *
*     NPX,NHX...                                    *
*       If NPX is positive then                     *
*       in each interval between 10**I and          *
*       10**(I+1) short dashes are plotted at       *
*       (NHX(J)*10**I,J=1,NPX) (in user coordinate) *
*       If NPX is negative then                     *
*       short dashes corresponding to               *
*           (10**I,I=NXMIN,NXMAX,ABS(NPX))          *
*       are plotted                                 *
*       Position of the IX-th shot dash in world    *
*       coordinate is computed and stored in XL(IX) *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      DIMENSION NHX(9),XL(101)
*
      MX = NXMAX - NXMIN
      FCX = XW / MX
*
      IF (NPX .GT. 0) THEN
*
        IF (MX*NPX+1 .GT. 101) THEN
          WRITE (*,2901)
 2901     FORMAT(' (LAXICX) parameter error for NPX')
          RETURN
        END IF
        IX = 0
        DO 10 I = 0, MX - 1
          IX = IX + 1
          XL(IX) = I * FCX
          DO 20 J = 1, NPX
            IX = IX + 1
            XL(IX) = (I + ALOG10(REAL(NHX(J)))) * FCX
   20     CONTINUE
   10   CONTINUE
        IXL = IX + 1
        XL(IXL) = MX * FCX
*
      ELSE IF (NPX .LT. 0) THEN
*
        NPXABS = ABS(NPX)
        IX = 0
        DO 30 I = NXMIN, NXMAX, NPXABS
          IX = IX + 1
          XL(IX) = (I - NXMIN) * FCX
   30   CONTINUE
        IXL = IX
*
      ELSE
*
        WRITE (*,2901)
        RETURN
*
      END IF
*
      CALL PUSTOR (0.0, 0.0, 3, NU, XU, YU, IPU)
      CALL PUSTOR ( XW, 0.0, 2, NU, XU, YU, IPU)
*
      DY = -YW / 100
*
      DO 40 IX = 1, IXL
        CALL PUSTOR (XL(IX), 0.0, 3, NU, XU, YU, IPU)
        CALL PUSTOR (XL(IX),  DY, 2, NU, XU, YU, IPU)
   40 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE LAXICY (YW, XW, NYMIN, NYMAX,
     $                   NPY, NHY,
     $                   NU, XU, YU, IPU)
*****************************************************
*            compute stroke pattern of              *
*         logarithmic scale Y-axis line             *
*   ---- input parameters ----                      *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*     NYMIN,NYMAX...                                *
*       It is assumed that range of y variable in   *
*       user coordinate is (10**NXMIN, 10**NXMAX)   *
*       in logarithmic scale which corresponds to   *
*       (0,YW) in world coordinate                  *
*     NPY,NHY...                                    *
*       If NPY is positive then                     *
*       in each interval between 10**I and          *
*       10**(I+1) short dashes are plotted at       *
*       (NHY(J)*10**I,J=1,NPY) (in user coordinate) *
*       If NPY is negative then                     *
*       short dashes corresponding to               *
*           (10**I,I=NYMIN,NYMAX,ABS(NPY))          *
*       are plotted                                 *
*       Position of the IY-th shot dash in world    *
*       coordinate is computed and stored in YL(IY) *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      DIMENSION NHY(9),YL(101)
*
      MY = NYMAX - NYMIN
      FCY = YW / MY
*
      IF (NPY .GT. 0) THEN
*
        IF (MY*NPY+1 .GT. 101) THEN
          WRITE (*,2902)
 2902     FORMAT(' (LAXICY) parameter error for NPY')
          RETURN
        END IF
        IY = 0
        DO 50 I = 0, MY - 1
          IY = IY + 1
          YL(IY) = I * FCY
          DO 60 J = 1, NPY
            IY = IY + 1
            YL(IY) = (I + ALOG10(REAL(NHY(J)))) * FCY
   60     CONTINUE
   50   CONTINUE
        IYL = IY + 1
        YL(IYL) = MY * FCY
*
      ELSE IF (NPY .LT. 0) THEN
*
        NPYABS = ABS(NPY)
        IY = 0
        DO 30 I = NYMIN, NYMAX, NPYABS
          IY = IY + 1
          YL(IY) = (I - NYMIN) * FCY
   30   CONTINUE
        IYL = IY
*
      ELSE
*
        WRITE (*,2902)
        RETURN
*
      END IF
*
      CALL PUSTOR (0.0, 0.0, 3, NU, XU, YU, IPU)
      CALL PUSTOR (0.0,  YW, 2, NU, XU, YU, IPU)
*
      DX = -XW / 100
*
      DO 70 IY = 1, IYL
        CALL PUSTOR (0.0, YL(IY), 3, NU, XU, YU, IPU)
        CALL PUSTOR ( DX, YL(IY), 2, NU, XU, YU, IPU)
   70 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE LGRIX (XW, YW, NXMIN, NXMAX,
     $                  NPX, NHX)
*****************************************************
*            compute stroke pattern of              *
*           logarithmic scale grid lines            *
*               parallel to Y-axis                  *
*   ---- input parameters ----                      *
*     XW,YW,NXMIN,MXMZX,NPX,NHX                     *
*     See comments in LGRICX                        *
*****************************************************
      DIMENSION NHX(9)
*
      PARAMETER (NUA = 100)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL LGRICX (XW, YW, NXMIN, NXMAX, NPX, NHX,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE LGRIY (YW, XW, NYMIN, NYMAX,
     $                  NPY, NHY)
*****************************************************
*            compute stroke pattern of              *
*           logarithmic scale grid lines            *
*               parallel to X-axis                  *
*   ---- input parameters ----                      *
*     YW,XW,NYMIN,MYMZX,NPY,NHY                     *
*     See comments in LGRICY                        *
*****************************************************
      DIMENSION NHY(9)
*
      PARAMETER (NUA = 100)
      DIMENSION XU(NUA),YU(NUA),IPU(NUA)
*
      NU = 0
      CALL LGRICY (YW, XW, NYMIN, NYMAX, NPY, NHY,
     $             NU, XU, YU, IPU)
*
      CALL PUPLOT (NU, XU, YU, IPU)
*
      RETURN
      END
*
      SUBROUTINE LGRICX (XW, YW, NXMIN, NXMAX,
     $                   NPX, NHX,
     $                   NU, XU, YU, IPU)
*****************************************************
*            compute stroke pattern of              *
*          logarithmic scale grid lines             *
*               parallel to Y-axis                  *
*   ---- input parameters ----                      *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*     NXMIN,NXMAX...                                *
*       It is assumed that range of x variable in   *
*       user coordinate is (10**NXMIN, 10**NXMAX)   *
*       in logarithmic scale which corresponds to   *
*       (0,XW) in world coordinate                  *
*     NPX,NHX...                                    *
*       If NPX is positive then                     *
*       in each interval between 10**I and          *
*       10**(I+1) grid lines are plotted at         *
*       (NHX(J)*10**I,J=1,NPX) (in user coordinate) *
*       If NPX is negative then                     *
*       glid lines corresponding to                 *
*           (10**I,I=NXMIN,NXMAX,ABS(NPX))          *
*       are plotted                                 *
*       Position of the IX-th grid line in world    *
*       coordinate is computed and stored in XL(IX) *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      DIMENSION NHX(9),XL(101)
*
      MX = NXMAX - NXMIN
      FCX = XW / MX
*
      IF (NPX .GT. 0) THEN
*
        IF (MX*NPX+1 .GT. 101) THEN
          WRITE (*,2901)
 2901     FORMAT(' (LGRICX) parameter error for NPX')
          RETURN
        END IF
        IX = 0
        DO 10 I = 0, MX - 1
          IX = IX + 1
          XL(IX) = I * FCX
          DO 20 J = 1, NPX
            IX = IX + 1
            XL(IX) = (I + ALOG10(REAL(NHX(J)))) * FCX
   20     CONTINUE
   10   CONTINUE
        IXL = IX + 1
        XL(IXL) = MX * FCX
*
      ELSE IF (NPX .LT. 0) THEN
*
        NPXABS = ABS(NPX)
        IX = 0
        DO 30 I = NXMIN, NXMAX, NPXABS
          IX = IX + 1
          XL(IX) = (I - NXMIN) * FCX
   30   CONTINUE
        IXL = IX
*
      ELSE
*
        WRITE (*,2901)
        RETURN
*
      END IF
*
      DO 40 IX = 1, IXL
        IF (MOD(I,2) .EQ. 0) THEN
          CALL PUSTOR (XL(IX), 0.0, 3, NU, XU, YU, IPU)
          CALL PUSTOR (XL(IX),  YW, 2, NU, XU, YU, IPU)
        ELSE
          CALL PUSTOR (XL(IX),  YW, 3, NU, XU, YU, IPU)
          CALL PUSTOR (XL(IX), 0.0, 2, NU, XU, YU, IPU)
        END IF
   40 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE LGRICY (YW, XW, NYMIN, NYMAX,
     $                   NPY, NHY,
     $                   NU, XU, YU, IPU)
*****************************************************
*            compute stroke pattern of              *
*          logarithmic scale grid lines             *
*               parallel to X-axis                  *
*   ---- input parameters ----                      *
*    (0,YW) ... bound of Y variable for rectangular *
*               domain in world coordinate          *
*    (0,XW) ... bound of X variable for rectangular *
*               domain in world coordinate          *
*     NYMIN,NYMAX...                                *
*       It is assumed that range of y variable in   *
*       user coordinate is (10**NXMIN, 10**NXMAX)   *
*       in logarithmic scale which corresponds to   *
*       (0,YW) in world coordinate                  *
*     NPY,NHY...                                    *
*       If NPY is positive then                     *
*       in each interval between 10**I and          *
*       10**(I+1) grid lines are plotted at         *
*       (NHY(J)*10**I,J=1,NPY) (in user coordinate) *
*       If NPY is negative then                     *
*       glid lines corresponding to                 *
*           (10**I,I=NYMIN,NYMAX,ABS(NPY))          *
*       are plotted                                 *
*       Position of the IY-th grid line in world    *
*       coordinate is computed and stored in YL(IY) *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      DIMENSION NHY(9),YL(101)
*
      MY = NYMAX - NYMIN
      FCY = YW / MY
*
      IF (NPY .GT. 0) THEN
*
        IF (MY*NPY+1 .GT. 101) THEN
          WRITE (*,2902)
 2902     FORMAT(' (LGRICY) parameter error for NPY')
          RETURN
        END IF
        IY = 0
        DO 50 I = 0, MY - 1
          IY = IY + 1
          YL(IY) = I * FCY
          DO 60 J = 1, NPY
            IY = IY + 1
            YL(IY) = (I + ALOG10(REAL(NHY(J)))) * FCY
   60     CONTINUE
   50   CONTINUE
        IYL = IY + 1
        YL(IYL) = MY * FCY
*
      ELSE IF (NPY .LT. 0) THEN
*
        NPYABS = ABS(NPY)
        IY = 0
        DO 70 I = NYMIN, NYMAX, NPYABS
          IY = IY + 1
          YL(IY) = (I - NYMIN) * FCY
   70   CONTINUE
        IYL = IY
*
      ELSE
*
        WRITE (*,2902)
        RETURN
*
      END IF
*
      DO 80 IY = 1, IYL
        IF (MOD(I,2) .EQ. 0) THEN
          CALL PUSTOR (0.0, YL(IY), 3, NU, XU, YU, IPU)
          CALL PUSTOR ( XW, YL(IY), 2, NU, XU, YU, IPU)
        ELSE
          CALL PUSTOR ( XW, YL(IY), 3, NU, XU, YU, IPU)
          CALL PUSTOR (0.0, YL(IY), 2, NU, XU, YU, IPU)
        END IF
   80 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE PUSTOR (X, Y, IP, JU, XU, YU, IPU)
*****************************************************
*          store plot data X, Y, IP into            *
*               XU(JU),YU(JU),IPU(JU)               *
*        used in AXIS and AXISNM routines           *
*****************************************************
C      DIMENSION XU(JU),YU(JU),IPU(JU)
      DIMENSION XU(*),YU(*),IPU(*)
*
      JU = JU + 1
      XU(JU) = X
      YU(JU) = Y
      IPU(JU) = IP
*
      RETURN
      END
*
      SUBROUTINE PUPLOT (NU, XU, YU, IPU)
*****************************************************
*                plot data stored in                *
*           (XU(I),YU(I),IPU(I),I=1,NU)             *
*          used in AXIS and AXISNM routines         *
*****************************************************
      DIMENSION XU(NU),YU(NU),IPU(NU)
*
      DO 10 I = 1, NU
        CALL PLOT (XU(I), YU(I), IPU(I))
   10 CONTINUE
*
      RETURN
      END
