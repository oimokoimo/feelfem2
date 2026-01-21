      SUBROUTINE CONTL3 (X0, Y0, XN, YN, XW, YW,
     $                   KH, HEIT, KHFND,
     $                   NL, IBGN, IEND, IRGT, ILFT,
     $                   LHEIT, LSRC,
     $                   NP, XA, YA, ZA)
*****************************************************
*         plot contour curves of a surface          *
*             over a triangular network             *
*                    1990.5.8.                      *
*             copyright : Masatake Mori             *
*   --- input parameters ----                       *
*     (X0,Y0) ... left-bottom corner of rectangular *
*                 domain in the user coordinates    *
*     (XN,YN) ... right-top corner of rectangular   *
*                 domain in the user coordinates    *
*     (0,0) ..... left-bottom corner of rectangular *
*                 domain in the world coordinates   *
*     (XW,YW) ... right-top corner of rectangular   *
*                 domain in the world coordinates   *
*     KH ... total number of heights to plot        *
*     HEIT(IH) ... height of the IH-th contour line *
*                  in the user coordinates          *
*     NL ... total number of sides of the           *
*                  triangular network               *
*     IBGN(L) ... point number of the start point   *
*                 of the L-th side                  *
*     IEND(L) ... point number of the end point of  *
*                 the L-th side                     *
*     IRGT(L) ... point number of the right point   *
*                 of the L-th side                  *
*             If the L-th side is a boundary side   *
*             then set IRGT(L)=-1   This means that *
*             the interior of the domain is on the  *
*             left hand side of the bondary.        *
*     ILFT(L) ... point number of the left point of *
*                 the L-th side                     *
*     NP ... total number of nodal points           *
*     XA(I) ... X coordinate of I-th nodal point    *
*               in user coordinates                 *
*     YA(I) ... Y coordinate of I-th nodal point    *
*               in user coordinates                 *
*     ZA(I) ... data atI-th nodal point             *
*               in user coordinates                 *
*   ---- work parameters ----                       *
*     NH ... total number of points to plot         *
*     XH(IH) ... X coordinate of IH-th point to     *
*                plot in world coordinates          *
*     YH(IH) ... Y coordinate of IH-th point to     *
*                plot in world coordinates          *
*     IPH(IH) ... 2 or 3 as pen indicator of PLOT   *
*                 if 2 then plot with pen down      *
*                 if 3 then plot with pen up        *
*     LHEIT,LSRC ... see comments in CONTC3         *
*****************************************************
      DIMENSION HEIT(KH),KHFND(KH)
*
      DIMENSION IBGN(NL),IEND(NL),IRGT(NL),ILFT(NL)
      DIMENSION LHEIT(NL),LSRC(NL)
      DIMENSION XA(NP),YA(NP),ZA(NP)
*
      PARAMETER (NHA = 2000)
      DIMENSION XH(NHA),YH(NHA),IPH(NHA)
*
      XFCTR = XW / (XN - X0)
      YFCTR = YW / (YN - Y0)
*
      DO 50 IH = 1, KH
*
        HTZ = HEIT(IH)
*
        CALL CONTC3 (HTZ, NH, XH, YH, IPH,
     $               NL, IBGN, IEND, IRGT, ILFT,
     $               LHEIT, LSRC,
     $               NP, XA, YA, ZA)
*
        DO 60 JH = 1, NH
          X = XFCTR * (XH(JH) - X0)
          Y = YFCTR * (YH(JH) - Y0)
          CALL PLOT (X, Y, IPH(JH))
   60   CONTINUE
*
        IF (NH .GT. 0) THEN
          KHFND(IH) = 1
        ELSE
          KHFND(IH) = 0
          WRITE (*,2003) HTZ
 2003     FORMAT (' (CONTL3) HEIT(=',1PE9.2,')',
     $            ' is not found')
        END IF
*
   50 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE CONTC3 (HTZ, NH, XH, YH, IPH,
     $                   NL, IBGN, IEND, IRGT, ILFT,
     $                   LHEIT, LSRC,
     $                   NP, XA, YA, ZA)
*****************************************************
*         compute contour of height HTZ             *
*   ---- input parameters ----                      *
*     HTZ ... height in user coordinates            *
*   ---- work arrays ----                           *
*     LHEIR(LC) ... line segment number of the      *
*                   LC-th registered line segment   *
*     LSRC(LC) ...initially set 1 if the contour    *
*                 pass inside the line segment or   *
*                 initially set 2 if the contour    *
*                 pass either of the end points of  *
*                 line segment                      *
*                 if contour search end then set    *
*                 -1 or -2                          *
*     See comments in CONTL3 for other parameters   *
*****************************************************
c      DIMENSION XH(NH),YH(NH),IPH(NH)
      DIMENSION XH(*),YH(*),IPH(*)
*
      DIMENSION IBGN(NL),IEND(NL),IRGT(NL),ILFT(NL)
      DIMENSION LHEIT(NL),LSRC(NL)
      DIMENSION XA(NP),YA(NP),ZA(NP)
*
      DATA EPS / 1.0E-5 /
*
*     ---- find line segment
*          crossing the contour of height HTZ ----
*
      LC = 0
      DO 110 LV = 1, NL
        IF ((ZA(IBGN(LV)) - HTZ)
     $    * (ZA(IEND(LV)) - HTZ) .LT. 0.0) THEN
          LC = LC + 1
          LSRC(LC) = 1
          LHEIT(LC) = LV
        ELSE IF ((ZA(IBGN(LV)) .EQ. HTZ) .OR.
     $           (ZA(IEND(LV)) .EQ. HTZ)) THEN
          LC = LC + 1
          LSRC(LC) = 2
          LHEIT(LC) = LV
        END IF
  110 CONTINUE
*
      NLH = LC
*
*     ---- search contour successively ----
*
      JH = 0
*
      LRCHNG = 0
*
      DO 10 LC = 1, NLH
*
        IF (LSRC(LC) .GT. 0) THEN
*
          LU = LHEIT(LC)
          IB = IBGN(LU)
          IE = IEND(LU)
          INEXT = ILFT(LU)
*
          IB0 = IE
          IE0 = IB
          INEXT0 = IRGT(LU)
*
          LSRC(LC) = -LSRC(LC)
          LSRCS = LSRC(LC)
*
  101     CONTINUE
*
          ZDIF = ZA(IB) - ZA(IE)
          IF (ABS(ZDIF) .GE. EPS) THEN
            RT = (HTZ - ZA(IE)) / ZDIF
          ELSE
            RT = 1.0
          END IF
*
          JH = JH + 1
          JH0 = JH
          XH(JH) = XA(IE) + (XA(IB) - XA(IE)) * RT
          YH(JH) = YA(IE) + (YA(IB) - YA(IE)) * RT
          IPH(JH) = 3
*
          LFIRST = 1
*
  200     CONTINUE
*
          LREP = 0
*
          DO 20 LD = LC+1, NLH
*
            IF (LSRC(LD) .GT. 0) THEN
*
              IF (LSRC(LD) .EQ. 2) THEN
                IBS = IB
                IES = IE
                INEXTS = INEXT
              END IF
*
              LV = LHEIT(LD)
              JB = IBGN(LV)
              JE = IEND(LV)
*
              IF (LFIRST .EQ. 1) THEN
                JB0 = JB
                JE0 = JE
                LFIRST = 0
              END IF
*
              IF ((JB .EQ. IB) .AND.
     $            (JE .EQ. INEXT)) THEN
                IE = JE
                INEXT = ILFT(LV)
              ELSE IF ((JB .EQ. INEXT) .AND.
     $                 (JE .EQ. IE)) THEN
                IB = JB
                INEXT = ILFT(LV)
              ELSE IF ((JB .EQ. INEXT) .AND.
     $                 (JE .EQ. IB)) THEN
                IE = JB
                INEXT = IRGT(LV)
              ELSE IF ((JB .EQ. IE) .AND.
     $                 (JE .EQ. INEXT)) THEN
                IB = JE
                INEXT = IRGT(LV)
              ELSE
                GO TO 20
              END IF
*
              ZDIF = ZA(IB) - ZA(IE)
              IF (ABS(ZDIF) .GE. EPS) THEN
                RT = (HTZ - ZA(IE)) / ZDIF
              ELSE
                RT = 1.0
              END IF
*
*             IF (LREP .EQ. 0) THEN
                JH = JH + 1
*             END IF
              XH(JH) = XA(IE) + (XA(IB) - XA(IE))*RT
              YH(JH) = YA(IE) + (YA(IB) - YA(IE))*RT
              IPH(JH) = 2
*
              LSRC(LD) = -LSRC(LD)
*
              IF (LREP .EQ. 0) THEN
                IF ((LSRCS    .EQ. -2) .AND.
     $              (LSRC(LD) .EQ. -2)) THEN
                  IBV = IB
                  IEV = IE
                  INEXTV = INEXT
                  LSRCSV = LSRCS
                  IB = IBS
                  IE = IES
                  INEXT = INEXTS
                  LREP = LREP + 1
                  GO TO 20
                END IF
              END IF
*
              IF (LREP .EQ. 1) THEN
                IF (INEXT .EQ. -1) THEN
                  IB = IBV
                  IE = IEV
                  INEXT = INEXTV
                  LSRCS = LSRCSV
                  LRCHNG = 0
                  GO TO 200
                END IF
              END IF
*
              LRCHNG = 0
              LSRCS = LSRC(LD)
              GO TO 200
*
            END IF
*
   20     CONTINUE
*
          IF (LREP .EQ. 1) THEN
            IB = IBV
            IE = IEV
            INEXT = INEXTV
            LSRCS = LSRCSV
            LRCHNG = 0
            GO TO 200
          END IF
*
          IF (INEXT .NE. -1) THEN
*
            IF ((((IB0 .EQ. IB)    .AND.
     $            (IE0 .EQ. INEXT))      .OR.
     $           ((IB0 .EQ. INEXT) .AND.
     $            (IE0 .EQ. IE))         .OR.
     $           ((IB0 .EQ. INEXT) .AND.
     $            (IE0 .EQ. IB))         .OR.
     $           ((IB0 .EQ. IE)    .AND.
     $            (IE0 .EQ. INEXT)))          .OR.
     $          (((JB0 .EQ. IB)    .AND.
     $            (JE0 .EQ. INEXT))      .OR.
     $           ((JB0 .EQ. INEXT) .AND.
     $            (JE0 .EQ. IE))         .OR.
     $           ((JB0 .EQ. INEXT) .AND.
     $            (JE0 .EQ. IB))         .OR.
     $           ((JB0 .EQ. IE)    .AND.
     $            (JE0 .EQ. INEXT))))         THEN
*
*           ---- contour become a closed one ----
*
              JH = JH + 1
              XH(JH) = XH(JH0)
              YH(JH) = YH(JH0)
              IPH(JH) = 2
*
            ELSE
*
*             ---- contour lost and try
*                  to escape from deadlock ----
*
               IF (LRCHNG .EQ. 0) THEN
                 LRCHNG = 1
                 IB = IB0
                 IE = IE0
                 INEXT = INEXT0
                 GO TO 101
               ELSE
                 LRCHNG = 0
               END IF
*
            END IF
*
          ELSE
*
*           ---- contour come to the boundary
*                   and go to another contour ----
*
          END IF
*
        END IF
*
   10 CONTINUE
*
      write(*,*) 'jh = ',jh
      NH = JH
*
      RETURN
      END
