      SUBROUTINE MKNTW (NP, NB, XA, YA,
     $           NLM, NL, IBGN, IEND, IRGT, ILFT)
*****************************************************
*      make triangular network for contour map      *
*                    1990.5.8.                      *
*            copyright : Masatake Mori              *
*   --- input parameters ----                       *
*     NP ... total number of nodal points           *
*     NB ... number of boundary points              *
*     XA(I) ... X coordinate of I-th nodal point    *
*               in user coordinates                 *
*     YA(I) ... Y coordinate of I-th nodal point    *
*               in user coordinates                 *
*     NLM ... estimated total number of sides of    *
*             triangular network and this should    *
*             be given larger than expected NL,     *
*             say, 5*NP                             *
*     IBGN(L) ... point number of start point of    *
*                 the L-th side                     *
*     IEND(L) ... point number of end point of      *
*                 the L-th side                     *
*     IRGT(L) ... point number of right point of    *
*                 the L-th side                     *
*     ILFT(L) ... point number of left point of     *
*                 the L-th side                     *
*     The first NB points (XA(I),YA(I),I=1,NB) are  *
*     boundary points and they must be ordered      *
*     consecutively counterclockwise                *
*     Therefore the first NB boundary sides must be *
*     given as follows:                             *
*     Supose that the NB points (IBGB(L),L=1,NB)    *
*     are the given boundary points. Then           *
*                                                   *
*         DO 210 L = 1, NB - 1                      *
*           IBGN(L) = IBGB(L)                       *
*           IEND(L) = IBGB(L+1)                     *
*           IRGT(L) = -1                            *
*           ILFT(L) = 0                             *
*     210 CONTINUE                                  *
*           IBGN(NB) = IBGB(L)                      *
*           IEND(NB) = IBGB(1)                      *
*           IRGT(NB) = -1                           *
*           ILFT(NB) = 0                            *
*    Closed boundaries may exist inside the domain  *
*                                                   *
*     And other IRGT and ILFT must be defined as    *
*                                                   *
*      DO 220 L = NB + 1, NLM                       *
*        IRGT(L) = 0                                *
*        ILFT(L) = 0                                *
*  220 CONTINUE                                     *
*                                                   *
*  --- output parameters ---                        *
*     NL ... total number of sides of triangular    *
*            network                                *
*     (IBGN(L),L=NB+1,NL)                           *
*     (IEND(L),L=NB+1,NL)                           *
*     (IRGT(L),L=NB+1,NL)                           *
*     (ILFT(L),L=NB+1,NL) ... see comment above     *
*****************************************************
      DIMENSION XA(NP),YA(NP)
      DIMENSION IBGN(NLM),IEND(NLM)
      DIMENSION IRGT(NLM),ILFT(NLM)
*
      M = NB
      DO 10 L = 1, NLM
*
        IF (L .EQ. M) THEN
          NL = M
          RETURN
        END IF
*
        IF (ILFT(L) .NE. 0) GO TO 10
*
*       find nodal point nearest to the line segment
*
        X1 = XA(IBGN(L))
        Y1 = YA(IBGN(L))
        X2 = XA(IEND(L))
        Y2 = YA(IEND(L))
        C = X1 - X2
        S = Y1 - Y2
        XM = 0.5 * (X1 + X2)
        YM = 0.5 * (Y1 + Y2)
        RR = 0.25 * (C**2 + S**2)
        HM = 1.0E+32
        JM = 1
*
        DO 20 J = 1, NP
*
          IF (J .NE. IBGN(L) .AND. J .NE. IEND(L)) THEN
            XV = XA(J) - XM
            YV = YA(J) - YM
            YVV = S * XV - C * YV
            IF (YVV .GT. 0.0) THEN
              H = (XV**2 + YV**2 - RR) / YVV
              IF (H .LT. HM) THEN
                HM = H
                JM = J
              END IF
            END IF
          END IF
*
   20   CONTINUE
*
        ILFT(L) = JM
*
*       check whether the line segment found is
*              already registered or not
*
        L1 = 0
        DO 30 LV = 1, M
          IF (IBGN(LV) .EQ. JM .AND.
     $        IEND(LV) .EQ. IBGN(L)) THEN
            L1 = LV
            GO TO 31
          END IF
   30   CONTINUE
   31   CONTINUE
*
        IF (L1 .EQ. 0) THEN
          M = M + 1
          IBGN(M) = IBGN(L)
          IEND(M) = JM
          IRGT(M) = IEND(L)
          ILFT(M) = 0
        ELSE
          ILFT(L1) = IEND(L)
        END IF
*
        L2 = 0
        DO 40 LV = 1, M
          IF (IBGN(LV) .EQ. IEND(L) .AND.
     $        IEND(LV) .EQ. JM) THEN
            L2 = LV
            GO TO 41
          END IF
   40   CONTINUE
   41   CONTINUE
*
        IF (L2 .EQ. 0) THEN
          M = M + 1
          IBGN(M) = JM
          IEND(M) = IEND(L)
          IRGT(M) = IBGN(L)
          ILFT(M) = 0
        ELSE
          ILFT(L2) = IBGN(L)
        END IF
*
   10 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE PLTNTW (X0, Y0, XN, YN, XW, YW,
     $                   NP, XA, YA, NL, IBGN, IEND)
*****************************************************
*             plot triangular network               *
*****************************************************
      DIMENSION XA(NP),YA(NP)
      DIMENSION IBGN(NL),IEND(NL)
*
      XFCTR = XW / (XN - X0)
      YFCTR = YW / (YN - Y0)
*
      DO 30 L = 1, NL
        X = XFCTR * (XA(IBGN(L)) - X0)
        Y = YFCTR * (YA(IBGN(L)) - Y0)
        CALL PLOT (X, Y, 3)
        X = XFCTR * (XA(IEND(L)) - X0)
        Y = YFCTR * (YA(IEND(L)) - Y0)
        CALL PLOT (X, Y, 2)
   30 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE PLTBND (X0, Y0, XN, YN, XW, YW,
     $                   NP, XA, YA,
     $                   NL, IBGN, IEND, IRGT)
*****************************************************
*        plot boundary of triangular network        *
*****************************************************
      DIMENSION XA(NP),YA(NP)
      DIMENSION IBGN(NL),IEND(NL),IRGT(NL)
*
      XFCTR = XW / (XN - X0)
      YFCTR = YW / (YN - Y0)
*
      DO 30 L = 1, NL
        IF (IRGT(L) .EQ. -1) THEN
          X = XFCTR * (XA(IBGN(L)) - X0)
          Y = YFCTR * (YA(IBGN(L)) - Y0)
          CALL PLOT (X, Y, 3)
          X = XFCTR * (XA(IEND(L)) - X0)
          Y = YFCTR * (YA(IEND(L)) - Y0)
          CALL PLOT (X, Y, 2)
        END IF
   30 CONTINUE
*
      RETURN
      END
*
      SUBROUTINE TRTOLS (NT, KNC,
     $                   NL, IBGN, IEND, IRGT, ILFT)
*****************************************************
*              define line segment data             *
*      (IBGN(L),IEND(L),IRGT(L),ILFT(L),L=1,NL)     *
*            from triangular element data           *
*             ((KNC(J,M),J=1,3),M=1,NT)             *
*****************************************************
      DIMENSION KNC(3,NT)
c      DIMENSION IBGN(NL),IEND(NL),IRGT(NL),ILFT(NL)
      DIMENSION IBGN(*),IEND(*),IRGT(*),ILFT(*)
*
*      WRITE (*,2001)
* 2001 FORMAT (' start TRTOLS ')
*
      NL = 0
*
      DO 10 M = 1, NT
*
        DO 20 J = 1, 3
*
          K1 = KNC(J,M)
          IF (J .EQ. 1) THEN
            K2 = KNC(2,M)
            K3 = KNC(3,M)
          ELSE IF (J .EQ. 2) THEN
            K2 = KNC(3,M)
            K3 = KNC(1,M)
          ELSE
            K2 = KNC(1,M)
            K3 = KNC(2,M)
          END IF
*
          DO 30 L = 1, NL
            IF ((IBGN(L) .NE. K2) .OR.
     $          (IEND(L) .NE. K1)) THEN
              GO TO 30
            ELSE
              IRGT(L) = K3
              GO TO 20
            END IF
   30     CONTINUE
*
          NL = NL + 1
          IBGN(NL) = K1
          IEND(NL) = K2
          ILFT(NL) = K3
          IRGT(NL) = -1
*
   20   CONTINUE
*
   10 CONTINUE
*
*      WRITE (*,2002) NL
* 2002 FORMAT (' end   TRTOLS : NL=',I4)
*
      RETURN
      END
*
      SUBROUTINE LSTOTR (NL, IBGN, IEND, IRGT, ILFT,
     $                   NT, KNC)
*****************************************************
*          define triangular element data           *
*              ((KNC(J,M),J=1,3),M=1,NT)            *
*               from line segment data              *
*      (IBGN(L),IEND(L),IRGT(L),IRGT(L),L=1,NL)     *
*****************************************************
      DIMENSION IBGN(*),IEND(*),IRGT(*),ILFT(*)
      DIMENSION KNC(3,*)
*
*      WRITE (*,2011)
* 2011 FORMAT (' start LSTOTR ')
*
      NT = 0
*
      DO 10 L = 1, NL
*
        DO 20 M = 1, NT
*
          DO 30 J = 1, 3
*
            K1 = KNC(J,M)
            IF (J .EQ. 1) THEN
              K2 = KNC(2,M)
              K3 = KNC(3,M)
            ELSE IF (J .EQ. 2) THEN
              K2 = KNC(3,M)
              K3 = KNC(1,M)
            ELSE
              K2 = KNC(1,M)
              K3 = KNC(2,M)
            END IF
*
            IF ((K1. EQ. IBGN(L)) .AND.
     $          (K2 .EQ. IEND(L)) .AND.
     $          (K3 .EQ. ILFT(L))) THEN
              GO TO 10
            END IF
*
   30     CONTINUE
*
   20   CONTINUE
*
        NT = NT + 1
        KNC(1,NT) = IBGN(L)
        KNC(2,NT) = IEND(L)
        KNC(3,NT) = ILFT(L)
*
   10 CONTINUE
*
*      WRITE (*,2012) NT
* 2012 FORMAT (' end   LSTOTR : NT=',I4)
*
      RETURN
      END
