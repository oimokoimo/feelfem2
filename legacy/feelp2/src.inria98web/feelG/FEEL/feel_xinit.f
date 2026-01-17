      SUBROUTINE FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,RXMIN,RXMAX,RYMIN,RYMAX,
     &     IGRY)
C
      IMPLICIT REAL*8 (A-H,O-Z)
      PARAMETER (PI=3.1415926536D0)
C-----------------------------------------------------------------------
C     このルーチンはXlibの関数をよぶための初期設定を行います。
C     ここで呼ばれる関数はすべてCで書かれています。
C
C 引き数の意味
C
C     IWX   : ディスプレイにおけるウィンドウ左上の点のXの値(既定値0)
C     IWY   : ディスプレイにおけるウィンドウ左上の点のYの値(既定値0)
C     IWW   : ディスプレイにおけるウィンドウの幅の値(既定値700)
C     IWH   : ディスプレイにおけるウィンドウの高さの値(既定値700)
C     IWD   : ウィンドウid番号(0〜9)
C     RXMIN : 表示範囲のX座標の最小値
C     RXMAX : 表示範囲のX座標の最大値
C     RYMIN : 表示範囲のY座標の最小値
C     RYMAX : 表示範囲のY座標の最大値
C     IGRY  : グレイスケール用フラグ(0->カラー  1->グレイ)
C
C 色を割り当てるのための配列
C
C     CBACK : バックグラウンドの色(1->red 2->green 3->blue)
C             それぞれ 0.0〜1.0 の範囲を値にもつ
C     CMESH : メッシュ線の色
C     CLINE : ラインの色
C   
C                                                  NSIS 渡部弘
C-----------------------------------------------------------------------
      DIMENSION CBACK(3),CMESH(3),CLINE(3)
      DIMENSION ISAVE(10)
      DATA      ISAVE/10*0/
      SAVE      ISAVE
C                                      環境変数のチェック
      CALL CHKDSP(IFLG)
C
      IF ( IFLG.LT.0 ) THEN
         WRITE(*,*) '環境変数 DISPLAY が設定されていません'
         STOP
      ENDIF
C                                      初めてのwindowでなければリターン
      IF ( ISAVE(IWD+1).NE.0 ) THEN
         RETURN
C                                      初めてならwindow id 番号を記憶
      ELSE
         ISAVE(IWD+1) = 1
      ENDIF
C                                      始めてのwindowのオープン
      CALL VOPW(IWX,IWY,IWW,IWH,0,IWD)
C                                      set backingStore 
      CALL VSBS(1,IWD)
C                                      windowがオープンされるまで待つ
      CALL VMPW(IWD)
C                                      色の決定
      CBACK(1) = 0.D0
      CBACK(2) = 0.D0
      CBACK(3) = 0.D0
C
      CMESH(1) = 0.5D0
      CMESH(2) = 0.3D0
      CMESH(3) = 1.0D0
C
      CLINE(1) = 1.D0
      CLINE(2) = 1.D0
      CLINE(3) = 1.D0
C                                      作業領域の確保
C                                         ISIZ = (1要素の色数)*(要素数)
C
c      ISIZ = 5*10000
      ISIZ = -1
      CALL VALW(ISIZ,IWD)
C                                      ビューポートの設定
      XREF = (RXMIN + RXMAX)/2
      YREF = (RYMIN + RYMAX)/2
      ZREF = 0.D0
C
      XMIN = (RXMIN - XREF)*1.2D0 + XREF
      XMAX = (RXMAX - XREF)*1.2D0 + XREF
C
      YMIN = (RYMIN - YREF)*1.2D0 + YREF
      YMAX = (RYMAX - YREF)*1.2D0 + YREF
C
      ZMIN = 0.D0
      ZMAX = 0.D0
C
      CALL VSVW(XMIN,YMIN,ZMIN,XMAX,YMAX,ZMAX,XREF,YREF,ZREF,IWD)
C
C                                      カラーテーブルの作成
      IF ( IGRY.NE.1 ) THEN
         CALL VECT(IWD)
C                                      グレイテーブルの作成
      ELSE
         CALL VECTG(IWD)
      ENDIF
C                                      バックグランドの色を31にセット
C
c     CALL VSCL(CBACK(1),CBACK(2),CBACK(3),31,1,IWD)
C     CALL VSBG(31,0,IWD)
C                                      メッシュの色を32にセット
C
      CALL VSCL(CMESH(1),CMESH(2),CMESH(3),32,1,IWD)
C
C                                      ラインの色を33にセット
C
      CALL VSCL(CLINE(1),CLINE(2),CLINE(3),33,1,IWD)
C
C                                      windowのクリア
      CALL VCLW(IWD)
C
C                                      回転角の設定
c      CALL VSRW(PI/2,0.D0,PI/2,IWD)
      CALL VSRW(0.D0,0.D0,1,IWD)
C
      RETURN
C
      E N D
