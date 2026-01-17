      SUBROUTINE FEEL_LINE(P0,P1,IWD)
C
      IMPLICIT REAL*8 (A-H,O-Z)
C
      DIMENSION P0(2),P1(2)
C-----------------------------------------------------------------------
C     このルーチンはFEELのライン作成を行うルーチンです。
C     このルーチンはperspectのみ有効です。(*1)
C
C     各引き数の意味(全て入力引き数である)
C
C     P0   : 描画するラインの一方の端点の座標値
C     P1   : 描画するラインのもう一方の端点の座標値
C     IWD  : ウィンドウid番号(0〜9)
C     色番号は 43 をつかいます。(*1)
C                                                         nsis 渡部弘
C                                                   (*1)  nsis 岡本
C-----------------------------------------------------------------------
      DIMENSION XX(2),YY(2),ZZ(3)
C                                     端点のX,Y,Z座標値を作成
      XX(1) = P0(1)
      XX(2) = P1(1)
C
      YY(1) = P0(2)
      YY(2) = P1(2)
C
      ZZ(1) = 0.D0
      ZZ(2) = 0.D0
C                                     ラインの描画
      CALL VSLN(XX,YY,ZZ,2,0,43,IWD)
C                                     フラッシュ
      CALL VUPD(IWD)
C
      RETURN
C
      E N D
