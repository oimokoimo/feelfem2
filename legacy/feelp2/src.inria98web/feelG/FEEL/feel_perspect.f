      SUBROUTINE FEEL_PERSPECT(NN,MM,PX,PY,U,KNC,NP,IWD,
     &     IFLG,XMIN,XMAX,YMIN,YMAX,UMIN,UMAX,ID,XA,YA,ZA,KNCNEW)
C
C     SUBROUTINE FEEL_PERSPECT(NN,MM,PX,PY,U,KNC,NP,IWD,
C    &     IFLG,XMIN,XMAX,YMIN,YMAX,UMIN,UMAX,ID,XA,YA,ZA,KNCNEW,
C    &     CAXIS,CPERS)
C     DIMENSION CAXIS(*),CPERS(*)
C
      IMPLICIT REAL*8(A-H,O-Z)
C
      DIMENSION PX(NN),PY(NN),U(NN),KNC(NP,MM),KNCNEW(3,MM*2)
      REAL*4    XA(NN),YA(NN),ZA(NN)
C-----------------------------------------------------------------------
C     このルーチンはFEELのパースペクティブ図作成を行うルーチンです。
C
C     各引き数の意味(NN〜IDは入力引き数、XA以下はワーク領域)
C
C     NN   : 節点数
C     MM   : 要素数
C     PX   : 節点のX座標値
C     PY   : 節点のY座標値
C     U    : 節点上の物理値
C     KNC  : 要素-節点番号が格納されている配列
C     NP   : KNCの1次元目の長さ
C     IWD  : ウィンドウid番号(0〜9)
C
C     IFLG : XMIN〜UMAXの値を自動設定するかどうかを示すフラグ
C            (全て自動設定 = 0   XMIN,XMAX,YMIN,YMAXを自動設定 = 1
C             UMIN,UMAXを自動設定 = 2     全てをユーザが入力 = 3)
C     XMIN : 表示するX座標の最小値
C     XMAX : 表示するX座標の最大値
C     YMIN : 表示するY座標の最小値
C     YMAX : 表示するY座標の最大値
C     UMIN : 表示する物理値の下限
C     UMAX : 表示する物理値の上限
C     ID   : 要素形状(３角形 = 3  ４角形 = 4)
C
C     XA     : 節点の単精度X座標値(ワーク領域)
C     YA     : 節点の単精度Y座標値(ワーク領域)
C     ZA     : 節点上単精度物理値(ワーク領域)
C     KNCNEW : 分割された一次3角形要素の節点番号(ワーク領域)
C
C                                                   nsis 渡部弘
C-----------------------------------------------------------------------
      REAL*4 X0,Y0,Z0,XN,YN,ZN,XW,YW,ZW,SIGMA,TAU,EH,ALPHA,EL,HGT
      CHARACTER*20 IFMTX,IFMTY,IFMTZ
C
      DIMENSION CAXIS(3),CPERS(3)
      COMMON /CMNIWD/IWDNEW
      DATA      CAXIS/1.0,1.0,0.0/
      DATA      CPERS/0.8,0.8,0.8/
*
C                                        ウィンドウのクリア
      CALL VCLW(IWD)
C                                        変数と配列のコピー
      IWDNEW = IWD
      NPNT = NN
C                                        XXXX
      NCID = 43
C
      DO 100 I=1,NN
         XA(I) = PX(I)
         YA(I) = PY(I)
         ZA(I) = U(I)
 100  CONTINUE
C                                        一次3角形要素配列の生成
      IF ( ID.EQ.3 ) THEN
         NT = MM
         DO 110 I=1,MM
            KNCNEW(1,I) = KNC(1,I)
            KNCNEW(2,I) = KNC(2,I)
            KNCNEW(3,I) = KNC(3,I)
 110     CONTINUE
      ELSE
         NT = MM*2
         DO 120 I=1,MM
            KNCNEW(1,2*I-1) = KNC(1,I)
            KNCNEW(2,2*I-1) = KNC(2,I)
            KNCNEW(3,2*I-1) = KNC(3,I)
            KNCNEW(1,2*I) = KNC(1,I)
            KNCNEW(2,2*I) = KNC(3,I)
            KNCNEW(3,2*I) = KNC(4,I)
 120     CONTINUE
      ENDIF
C                                        IFLGの値によりXMIN〜UMAXを設定
      IF ( IFLG.EQ.0 ) THEN
         XMIN =  1.D+72
         XMAX = -1.D+72
         YMIN =  1.D+72
         YMAX = -1.D+72
         UMIN =  1.D+72
         UMAX = -1.D+72
         DO 130 I=1,MM
            DO 140 J=1,ID
               IN = KNC(J,I)
               XMIN = MIN(XMIN,PX(IN))
               XMAX = MAX(XMAX,PX(IN))
               YMIN = MIN(YMIN,PY(IN))
               YMAX = MAX(YMAX,PY(IN))
               UMIN = MIN(UMIN,U(IN))
               UMAX = MAX(UMAX,U(IN))
 140        CONTINUE
 130     CONTINUE
      ELSEIF ( IFLG.EQ.1 ) THEN
         XMIN =  1.D+72
         XMAX = -1.D+72
         YMIN =  1.D+72
         YMAX = -1.D+72
         DO 150 I=1,MM
            DO 160 J=1,ID
               IN = KNC(J,I)
               XMIN = MIN(XMIN,PX(IN))
               XMAX = MAX(XMAX,PX(IN))
               YMIN = MIN(YMIN,PY(IN))
               YMAX = MAX(YMAX,PY(IN))
 160        CONTINUE
 150     CONTINUE
      ELSEIF ( IFLG.EQ.2 ) THEN
         UMIN =  1.D+72
         UMAX = -1.D+72
         DO 170 I=1,MM
            DO 180 J=1,ID
               IN = KNC(J,I)
               UMIN = MIN(UMIN,U(IN))
               UMAX = MAX(UMAX,U(IN))
 180        CONTINUE
 170     CONTINUE
      ELSEIF ( IFLG.EQ.3 ) THEN
         CONTINUE
      ENDIF
C                                          パースペクティブ用変数初期化
      X0 = XMIN
      XN = XMAX
      Y0 = YMIN
      YN = YMAX
      Z0 = UMIN
      ZN = UMAX
*
      CALL INITS (XW, YW, ZW, SIGMA, TAU, EH, ALPHA, EL)
C
*
C      CALL PLOT (5.0, 2.0, -3)
      CALL PLOT (0.0, 0.0, -3)
*
      CALL VSCL(CPERS(1),CPERS(2),CPERS(3),NCID,1,IWD)
C
      CALL PERPL3 (X0, Y0, Z0, XN, YN, ZN,
     $             XW, YW, ZW,
     $             SIGMA, TAU, EH, ALPHA, EL,
     $             NPNT, XA, YA, ZA, NT, KNCNEW)
C                                     フラッシュ
      CALL VUPD(IWD)
*
      MX = 5
      MY = 5
      MZ = 5
      HGT = 0.3
*
      IFMTX = '(F6.1)'
      IFMTY = '(F6.1)'
      IFMTZ = '(F6.1)'
*
      CALL VSCL(CAXIS(1),CAXIS(2),CAXIS(3),NCID,1,IWD)
C
      CALL AXIS3 (XW, YW, ZW, MX, MY, MZ,
     $            X0, Y0, Z0, XN, YN, ZN,
     $            HGT, IFMTX, IFMTY, IFMTZ,
     $            NPNT, XA, YA, NT, KNCNEW)
*
C                                     フラッシュ
      CALL VUPD(IWD)
C
      RETURN
C
      E N D
*
      SUBROUTINE INITS (XW, YW, ZW, SIGMA, TAU, EH, ALPHA, EL)
*****************************************************
*             sample data for PERPLT                *
*****************************************************
      COMMON / COMHLN / LHL
      COMMON / COMFRM / LZC,LAX
      COMMON / COMZCL / LZCLP,ZMN,ZMX
*
c                        LHL=0 -> 陰線処理を行わない
c                        LHL=1 -> 陰線処理を行う
      LHL = 0
      LZC = 1
      LAX = 3
*
      XW = 10.0
      YW = 10.0
      ZW =  6.25
*
      SIGMA = 2.0
      TAU = 5.0
      EH = 25.0
      ALPHA = 15.0
      EL = 25.0
*
      LZCLP = 0
*
      RETURN
      END
*
