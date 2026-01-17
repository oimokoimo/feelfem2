      SUBROUTINE FEEL_VECTOR(VX,VY,NN,MM,PX,PY,KNC,NP,ID,ITYPE,
     &     IWX,IWY,IWW,IWH,IWD,IFLG,XMIN,XMAX,YMIN,YMAX,VMAX,
     &     VM,IOUT,IMSH,WK,IWK)
C
      IMPLICIT REAL*8 (A-H,O-Z)
C
      DIMENSION VX(*),VY(*),PX(NN),PY(NN),KNC(NP,*),WK(*),IWK(NN)
C-----------------------------------------------------------------------
C  このルーチンはFEELのベクトル図作成を行うルーチンです。
C
C     各引き数の意味(全て入力引き数である)
C
C     VX   : ベクトルのX成分
C     VY   : ベクトルのY成分
C     NN   : 節点数
C     MM   : 要素数
C     PX   : 節点のX座標値
C     PY   : 節点のY座標値
C     KNC  : 要素-節点番号が格納されている配列
C     NP   : KNCの1次元目の長さ
C     ID   : 要素形状(3角形 = 3  4角形 = 4)
C     ITYPE: 表示するベクトルのタイプ
C            (要素内のベクトル = 0  節点上のベクトル = 1)
C
C     IWX  : ディスプレイにおけるウィンドウ左上の点のXの値(既定値0)
C     IWY  : ディスプレイにおけるウィンドウ左上の点のYの値(既定値0)
C     IWW  : ディスプレイにおけるウィンドウの幅の値(既定値700)
C     IWH  : ディスプレイにおけるウィンドウの高さの値(既定値700)
C     IWD  : ウィンドウid番号(0〜9)
C
C     IFLG : XMIN〜YMAX,VMAXの値を自動設定するかどうかを示すフラグ
C            (全て自動設定 = 0       XMIN,XMAX,YMIN,YMAXを自動設定 = 1
C             VMAXを自動設定 = 2     全てをユーザが入力 = 3)
C     XMIN : 表示するX座標の最小値
C     XMAX : 表示するX座標の最大値
C     YMIN : 表示するY座標の最小値
C     YMAX : 表示するY座標の最大値
C     VMAX : 予想されるベクトルの最大長さ
C
C     VM   : ベクトルの拡大率
C     IOUT : 出力タイプ(塗り潰し=0 線=1 白で塗り潰し=2)
C     IMSH : メッシュフラグ(メッシュを書かない = 0  書く = 1)
C     WK   : 実数型ワーク領域
C                   1〜1.5*MM ->ベクトルのX成分
C            1.5*MM+1〜3.0*MM ->ベクトルのY成分
C            3.0*MM+1〜4.5*MM ->ベクトルのZ成分(全て0)
C            4.5*MM+1〜6.0*MM ->ベクトル基点Y成分
C            6.0*MM+1〜7.5*MM ->ベクトル基点のY成分
C            7.5*MM+1〜9.0*MM ->ベクトル基点のZ成分(全て0)
C     IWK  : 整数型ワーク領域(NN)
C
C     その他主な変数
C     MC     : 使用する色番号の対応表
C     CV     : しきい値
C                                                   nsis 渡部弘
C-----------------------------------------------------------------------
      DIMENSION MC(22),CV(21),XT(4),YT(4),ZT(4)
C
C                                  ウィンドウのクリア
      CALL VCLW(IWD)
C                                  必要なら既定値にする
      IF ( IWX.LE.0 ) IWX = 0
      IF ( IWY.LE.0 ) IWY = 0
      IF ( IWW.LE.0 ) IWW = 700
      IF ( IWH.LE.0 ) IWH = 700
      IF ( IWD.LT.0 .OR. IWD.GT.9 ) IWD = 0
C
      IF ( IFLG.LT.0 .OR. IFLG.GT.3 ) IFLG = 0
C
      IF ( IOUT.LT.0 .OR. IOUT.GT.2 ) THEN
         WRITE(*,*) 'IOUTは0,1,2でなければなりません.'
         STOP
      ENDIF
C                                  IOUTを0,1にしIONEWに格納
      IF ( IOUT.NE.2 ) THEN
         IONEW = IOUT
      ELSE
         IONEW = 0
      ENDIF
C                                  IFLGの値により表示範囲を設定
C
      IF ( IFLG.EQ.0 .OR. IFLG.EQ.1 ) THEN
         XMIN =  1.D+72
         XMAX = -1.D+72
         YMIN =  1.D+72
         YMAX = -1.D+72 
         DO 100 I=1,MM
            DO 110 J=1,ID
               IN = KNC(J,I)
               XMIN = MIN(XMIN,PX(IN))
               XMAX = MAX(XMAX,PX(IN))
               YMIN = MIN(YMIN,PY(IN))
               YMAX = MAX(YMAX,PY(IN))
 110        CONTINUE
 100     CONTINUE
      ENDIF
C                                     Xlibに関する初期設定
C
C      CALL FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX)
C
C                                     メッシュの表示
      IF ( IMSH.EQ.1 ) THEN
         DO 120 I=1,MM
C                                     3角形メッシュをセット
            IF ( ID.EQ.3 ) THEN
               IN1 = KNC(1,I)
               IN2 = KNC(2,I)
               IN3 = KNC(3,I)
C
               XT(1) = PX(IN1)
               YT(1) = PY(IN1)
               ZT(1) = 0.D0
C
               XT(2) = PX(IN2)
               YT(2) = PY(IN2)
               ZT(2) = 0.D0
C
               XT(3) = PX(IN3)
               YT(3) = PY(IN3)
               ZT(3) = 0.D0
C
               CALL VETS(XT,YT,ZT,3,1,32,IWD)
C
C                                     4角形メッシュをセット
            ELSEIF ( ID.EQ.4 ) THEN
               IN1 = KNC(1,I)
               IN2 = KNC(2,I)
               IN3 = KNC(3,I)
               IN4 = KNC(4,I)
C
               XT(1) = PX(IN4)
               YT(1) = PY(IN4)
               ZT(1) = 0.D0
C
               XT(2) = PX(IN3)
               YT(2) = PY(IN3)
               ZT(2) = 0.D0
C
               XT(3) = PX(IN1)
               YT(3) = PY(IN1)
               ZT(3) = 0.D0
C
               XT(4) = PX(IN2)
               YT(4) = PY(IN2)
               ZT(4) = 0.D0
C
               CALL VEQS(XT,YT,ZT,2,2,1,32,IWD)
            ELSE
               WRITE(*,*) 'IDは3,4でなければなりません'
               STOP
            ENDIF
 120     CONTINUE
      ENDIF
C                                     ベクトルのコピーと基点の設定
      IF ( ITYPE.EQ.0 ) THEN
         KK = MM*3/2
         DO 200 I=1,MM
            WK(0*KK + I) = VX(I)
            WK(1*KK + I) = VY(I)
            WK(2*KK + I) = 0.D0
C
            XG = 0.D0
            YG = 0.D0
            DO 210 J=1,ID
               IN = KNC(J,I)
               XG = XG + PX(IN)
               YG = YG + PY(IN)
 210        CONTINUE
            WK(3*KK + I) = XG/ID
            WK(4*KK + I) = YG/ID
            WK(5*KK + I) = 0.D0
 200     CONTINUE
         LL = MM
C
      ELSEIF ( ITYPE.EQ.1 ) THEN
         DO 220 I=1,NN
            IWK(I) = 0
 220     CONTINUE
C
         KK = MM*3/2
         ICNT = 0
         DO 230 I=1,MM
            DO 240 J=1,ID
               NODENO = KNC(J,I)
               IF ( IWK(NODENO).EQ.0 ) THEN
                  IWK(NODENO) = 1
                  ICNT = ICNT + 1
C
                  WK(0*KK + ICNT) = VX(NODENO)
                  WK(1*KK + ICNT) = VY(NODENO)
                  WK(2*KK + ICNT) = 0.D0
                  WK(3*KK + ICNT) = PX(NODENO)
                  WK(4*KK + ICNT) = PY(NODENO)
                  WK(5*KK + ICNT) = 0.D0
               ENDIF
 240        CONTINUE
 230     CONTINUE
         LL = ICNT
      ELSE
         WRITE(*,*) 'ITYPEは0.1でなければなりません'
         STOP
      ENDIF
C                                     ベクトルの最大長さの計算
C
      IF ( IFLG.EQ.0 .OR. IFLG.EQ.2 ) THEN
         VMAX = 0.D0
         DO 130 I=1,LL
            VTMP = WK(0*KK + I)**2 + WK(1*KK + I)**2
            VMAX = MAX(VMAX,VTMP)
 130     CONTINUE
         VMAX = SQRT(VMAX)
      ENDIF
C                                     ベクトル表示のための長さの変換
      DO 140 I=1,LL
C                                     本来の長さを計算
C
         VL = WK(0*KK + I)**2 + WK(1*KK + I)**2
         IF ( VL.LT.1.D-40 ) THEN
            WK(0*KK + I) = 0.D0
            WK(1*KK + I) = 0.D0
            GOTO 140
         ENDIF
         VL = SQRT(VL)
C                                     ベクトルを単位長さに変換
C
         WK(0*KK + I) = WK(0*KK + I)/VL
         WK(1*KK + I) = WK(1*KK + I)/VL
C
C                                     変換後の長さ(0.0〜0.99)を計算
         VTMP = VL/VMAX*10
         VTMP = 1.D0 - 1.D0/(1.D0 + VTMP)**2
C
         WK(0*KK + I) = WK(0*KK + I)*VTMP
         WK(1*KK + I) = WK(1*KK + I)*VTMP
 140  CONTINUE
C                                     表示ベクトルの最大長さ
C
      TMP = (XMAX - XMIN)*(YMAX - YMIN)/MM
      SZ = SQRT(TMP)/4
C                                     しきい値と配色の決定
      IDIV = 21
      DO 150 I=1,IDIV
c         cv(i) = 0.99d0/idiv*i
         CV(I) = 1.D0/IDIV*I
C                                     カラーテーブル
         IF ( IOUT.NE.2 ) THEN
            MC(I) = I + 1
C                                     全て白色
         ELSE
            MC(I) = 1
         ENDIF
 150  CONTINUE
C
      IF ( IOUT.NE.2 ) THEN
         MC(IDIV + 1) = IDIV + 2
      ELSE
         MC(IDIV + 1) = 1
      ENDIF
C                                     VEVTにおける拡大率
      ZOOM = 1.D0/VM
C                                     ベクトル図の表示
C
      CALL VEVT(WK(3*KK+1),WK(4*KK+1),WK(5*KK+1),
     &     WK(0*KK+1),WK(1*KK+1),WK(2*KK+1),LL,
     &     SZ,ZOOM,IONEW,IDIV,CV,MC,IWD)
C
C                                     フラッシュ
      CALL VUPD(IWD)
C                                     マウスクリックされるのを待つ
C      CALL VEWT(IWD)
C
      RETURN
C
      E N D
