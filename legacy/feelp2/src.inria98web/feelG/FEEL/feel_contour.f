      SUBROUTINE FEEL_CONTOUR(NN,MM,PX,PY,U,KNC,NP,IWX,IWY,IWW,IWH,IWD,
     &     IFLG,XMIN,XMAX,YMIN,YMAX,UMIN,UMAX,
     &     ID,ITYP,IOUT,IMSH,IDIV,ISCL)
C
      IMPLICIT REAL*8 (A-H,O-Z)
C
      DIMENSION PX(NN),PY(NN),U(NN),KNC(NP,MM)
C-----------------------------------------------------------------------
C     このルーチンはFEELのコンタ図作成を行うルーチンです。
C
C     各引き数の意味(全て入力引き数である)
C
C     NN   : 節点数
C     MM   : 要素数
C     PX   : 節点のX座標値
C     PY   : 節点のY座標値
C     U    : 節点上の物理値
C     KNC  : 要素-節点番号が格納されている配列
C     NP   : KNCの1次元目の長さ
C     IWX  : ディスプレイにおけるウィンドウ左上の点のXの値(既定値0)
C     IWY  : ディスプレイにおけるウィンドウ左上の点のYの値(既定値0)
C     IWW  : ディスプレイにおけるウィンドウの幅の値(既定値700)
C     IWH  : ディスプレイにおけるウィンドウの高さの値(既定値700)
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
C
C     ID   : 要素形状(３角形 = 3  ４角形 = 4)
C     ITYP : コンタタイプ(通常 = 0 対数表示 = 1) ....とりあえず0のみ
C     IOUT : 出力タイプ(塗り潰し=0 カラー線=1 白線=2)
C     IMSH : メッシュフラグ(メッシュを書かない=0  書く=1)
C     IDIV : 値域を何等分するか。言い換えれば何色で塗り分けるか。
C     ISCL : スケールフラグ(スケールを入れない=0  入れる=1以上の値)
C
C     その他主な変数
C
C     MC     : 使用する色番号の対応表
C     V      : しきい値
C     X      : 要素節点のX座標値
C     Y      : 要素節点のY座標値
C     Z      : 要素節点のZ座標値(この場合は全て0)
C     S      : 要素節点の物理値
C     X1,X2  : 4角形要素を2つの3角形に分割する時にX座標を格納する
C     Y1,Y2  : 4角形要素を2つの3角形に分割する時にY座標を格納する
C     S1,S2  : 4角形要素を2つの3角形に分割する時に物理値を格納する
C     XX,YY  : 4角形要素のメッシュを描画する時の配列
C                                                   nsis 渡部弘
C-----------------------------------------------------------------------
      DIMENSION MC(102),V(101),X(4),Y(4),Z(4),S(4)
      DIMENSION X1(3),Y1(3),S1(3),X2(3),Y2(3),S2(3),XX(4),YY(4)
C
C                                  白線ならウィンドウのクリア
      IF ( IOUT.EQ.2 ) THEN
         CALL VCLW(IWD)
      ENDIF
C                                  必要なら既定値にする
      IF ( IWX.LE.0 ) IWX = 0
      IF ( IWY.LE.0 ) IWY = 0
      IF ( IWW.LE.0 ) IWW = 700
      IF ( IWH.LE.0 ) IWH = 700
      IF ( IWD.LT.0 .OR. IWD.GT.9 ) IWD = 0
C
      IF ( ITYP.NE.0 ) THEN
         WRITE(*,*) 'ITYP MUST BE 0 NOW.'
         STOP
      ENDIF
C
      IF ( IOUT.LT.0 .OR. IOUT.GT.2 ) THEN
         WRITE(*,*) 'IOUTは0,1,2のどれかでなければなりません.'
         STOP
      ENDIF
C                                  IFLGの値により表示範囲を設定
      IF ( IFLG.EQ.0 ) THEN
         XMIN =  1.D+72
         XMAX = -1.D+72
         YMIN =  1.D+72
         YMAX = -1.D+72 
         UMIN =  1.D+72
         UMAX = -1.D+72
         DO 100 I=1,MM
            DO 110 J=1,ID
               IN = KNC(J,I)
               XMIN = MIN(XMIN,PX(IN))
               XMAX = MAX(XMAX,PX(IN))
               YMIN = MIN(YMIN,PY(IN))
               YMAX = MAX(YMAX,PY(IN))
               UMIN = MIN(UMIN,U(IN))
               UMAX = MAX(UMAX,U(IN))
 110        CONTINUE
 100     CONTINUE
      ELSEIF ( IFLG.EQ.1 ) THEN
         XMIN =  1.D+72
         XMAX = -1.D+72
         YMIN =  1.D+72
         YMAX = -1.D+72 
         DO 120 I=1,MM
            DO 130 J=1,ID
               IN = KNC(J,I)
               XMIN = MIN(XMIN,PX(IN))
               XMAX = MAX(XMAX,PX(IN))
               YMIN = MIN(YMIN,PY(IN))
               YMAX = MAX(YMAX,PY(IN))
 130        CONTINUE
 120     CONTINUE
      ELSEIF ( IFLG.EQ.2 ) THEN
         UMIN =  1.D+72
         UMAX = -1.D+72
         DO 140 I=1,MM
            DO 150 J=1,ID
               IN = KNC(J,I)
               UMIN = MIN(UMIN,U(IN))
               UMAX = MAX(UMAX,U(IN))
 150        CONTINUE
 140     CONTINUE
      ELSEIF ( IFLG.EQ.3 ) THEN
         CONTINUE
      ELSE
         WRITE(*,*) 'IFLGの値は正しくありません'
         STOP
      ENDIF
C                                     Xlibに関する初期設定
C
c      CALL FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX)
C
C                                     使用する色番号の対応表を作成
C
      IF ( IDIV.LE.0 .OR. IDIV.GT.100 ) IDIV = 21
C
      IF ( IOUT.EQ.0 ) THEN
         ILIN = 1
         MC(1) = 0
         TMP = 20.D0/(IDIV - 1)
         DO 160 I=1,IDIV
            MC(I + 1) = TMP*(I - 1) + 2.D0 + 0.5D0
 160     CONTINUE
         MC(IDIV + 2) = 0
      ELSE
         ILIN = 0
         TMP = 20.8D0/IDIV
         DO 170 I=1,IDIV+1
C                                     線へ配色する
            IF ( IOUT.EQ.1) THEN
               MC(I) = TMP*(I - 1) + 2.D0 + 0.1D0
            ELSE
               MC(I) = 1
            ENDIF
 170     CONTINUE
      ENDIF
C                                     しきい値の作成
      TMP = (UMAX - UMIN)/IDIV
      DO 180 I=1,IDIV
         V(I) = TMP*(I - 1) + UMIN
 180  CONTINUE
      V(IDIV + 1) = UMAX
C
c      DO 190 I=1,IDIV+1
c         WRITE(*,'(I4,F20.10)') I,V(I)
c 190  CONTINUE
C                                     VETCのバグへのアドホックな対処
      V(1)        = UMIN + TMP/1000
      V(IDIV + 1) = UMAX - TMP/1000
C                                     Zに0を代入
      Z(1) = 0.D0
      Z(2) = 0.D0
      Z(3) = 0.D0
      Z(4) = 0.D0
C                                     全要素に対して反復
      DO 200 I=1,MM
C                                     要素内のX,Y,Sを作成
         DO 210 J=1,ID
            NODE = KNC(J,I)
            X(J) = PX(NODE)
            Y(J) = PY(NODE)
            S(J) = U(NODE)
 210     CONTINUE
C                                     3角形メッシュの場合
         IF ( ID.EQ.3 ) THEN
C                                     要素内のコンタ図を生成
C
            CALL VETC(X,Y,Z,S,ID,ILIN,MC,V,IDIV+1,IWD)
C
C                                     3角形メッシュをセット
C
            IF ( IMSH.EQ.1 ) CALL VETS(X,Y,Z,ID,1,32,IWD)
C
C                                     4角形メッシュの場合
         ELSEIF ( ID.EQ.4 ) THEN
C                                     対角線の長さ
C
            TMP13 = (X(3) - X(1))**2 + (Y(3) - Y(1))**2
            TMP24 = (X(4) - X(2))**2 + (Y(4) - Y(2))**2
C
C                                     4角形を2つの3角形に分割
            IF ( TMP13.GE.TMP24 ) THEN
               X1(1) = X(1)
               Y1(1) = Y(1)
               S1(1) = S(1)
               X1(2) = X(2)
               Y1(2) = Y(2)
               S1(2) = S(2)
               X1(3) = X(4)
               Y1(3) = Y(4)
               S1(3) = S(4)
C
               X2(1) = X(2)
               Y2(1) = Y(2)
               S2(1) = S(2)
               X2(2) = X(3)
               Y2(2) = Y(3)
               S2(2) = S(3)
               X2(3) = X(4)
               Y2(3) = Y(4)
               S2(3) = S(4)
            ELSE
               X1(1) = X(1)
               Y1(1) = Y(1)
               S1(1) = S(1)
               X1(2) = X(2)
               Y1(2) = Y(2)
               S1(2) = S(2)
               X1(3) = X(3)
               Y1(3) = Y(3)
               S1(3) = S(3)
C
               X2(1) = X(1)
               Y2(1) = Y(1)
               S2(1) = S(1)
               X2(2) = X(3)
               Y2(2) = Y(3)
               S2(2) = S(3)
               X2(3) = X(4)
               Y2(3) = Y(4)
               S2(3) = S(4)
            ENDIF
C                                     要素内のコンタ図を生成
C
            CALL VETC(X1,Y1,Z,S1,3,ILIN,MC,V,IDIV+1,IWD)
            CALL VETC(X2,Y2,Z,S2,3,ILIN,MC,V,IDIV+1,IWD)
C
C                                     4角形メッシュをセット
            XX(1) = X(4)
            YY(1) = Y(4)
            XX(2) = X(3)
            YY(2) = Y(3)
            XX(3) = X(1)
            YY(3) = Y(1)
            XX(4) = X(2)
            YY(4) = Y(2)
            IF ( IMSH.EQ.1 ) CALL VEQS(XX,YY,Z,2,2,1,32,IWD)
         ELSE
            WRITE(*,*) 'IDは3,4でなければなりません'
            STOP
         ENDIF
 200  CONTINUE
C                                     フラッシュ
      CALL VUPD(IWD)
C                                     カラーバーを表示
C
      IF ( ISCL.NE.0 ) CALL VECB(IDIV,V,0,1,MC,IWD)
C
C                                     マウスクリックされるのを待つ
C      CALL VEWT(IWD)
C
      RETURN
C
      E N D
