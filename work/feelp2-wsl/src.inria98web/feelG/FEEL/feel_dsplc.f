      SUBROUTINE FEEL_DSPLC(NP,NE,NN,NEN,PX,PY,QX,QY,U,V,FT,SC,
     $IC,ISL,ICT,IDV,ICS,ITP,ICM,SMIN,SMAX,ICB,NCBX,NCBY,ID,IWD)
C
      IMPLICIT REAL*8 (A-H,O-Z)
C
      DIMENSION PX(*),PY(*),NEN(NN,NE)
      DIMENSION QX(*),QY(*)
      DIMENSION U(*),V(*)
      DIMENSION SC(*)
      DIMENSION IC(*)
C-----------------------------------------------------------------------
C     このルーチンはFEELの変位図作成を行うルーチンです。
C     各引き数の意味
C
C     NP      :節点数
C     NE      :要素数
C     NN      :各要素の節点数
C     NEN     :要素、節点番号が格納されている配列
C     PX      :節点のＸ座標値
C     PY      :節点のＹ座標値
C     QX      :作業領域(変位後のＸ座標値)
C     QY      :作業領域(変位後のＹ座標値)
C     U       :Ｘ座標値の変位量
C     V       :Ｙ座標値の変位量
C     SC      :各座標点のスカラ値
C     FT      :倍率
C     IC(1)   :元の図のカラーＩＤ番号
C     IC(2)   :変位後の図のカラーＩＤ番号
C     ISL     :０→塗りつぶす、１→塗りつぶさない
C     ICT     :０→コンタを書かない、１→コンタを書く
C     IDV     :コンタのしきい値数
C     ICS     :コンタのしきい値フラグ ０：Auto １：マニュアル ２：Full Auto
C     ITP     :コンタの表示タイプ ０：線画 １；塗りつぶし
C     ICM     :変位後のメッシュ ０：書かない１：書く
C     SMIN    :コンタのしきい値の最小値
C     SMAX    :コンタのしきい値の最大値
C     ICB     :カラーバーの有無 ０：なし １：あり
C     NCBX    :カラーバーの位置Ｘ
C     NCBY    :カラーバーの位置Ｙ
C     ID      :要素形状(３角形 = 3  ４角形 = 4)
C     IWD     :ウィンドウＩＤ番号
C-----------------------------------------------------------------------
C     注意事項１   :各要素の節点数の最大は１００とします。
C     注意事項２   :ICS について
C                   (0)IDV を定義しなければなりません
C                   (1)IDV,SMIN,SMAX を定義しなければなりません
C                   (2)IDV,SMIN,SMAX いずれも定義する必要はありません
C-----------------------------------------------------------------------
      DIMENSION  X(100), Y(100), Z(100), S(100)
      DIMENSION XX(100),YY(100),ZZ(100),SS(100)
      DIMENSION MC(100)
      DIMENSION VC(100)
C-----------------------------------------------------------------------
C     NN が１００より大きい場合は表示しません    
C-----------------------------------------------------------------------
      IF ( NN.GT.100 ) THEN
        WRITE(*,*) '変位図を表示できません'
        STOP
      ENDIF
C-----------------------------------------------------------------------
C     画面をクリアします
C-----------------------------------------------------------------------
      CALL VCLW(IWD)
C-----------------------------------------------------------------------
C     元のメッシュ図を表示します
C-----------------------------------------------------------------------
      DO 100 I=1,NE
        DO 200 J=1,NN
          X(J)=PX(NEN(J,I))
          Y(J)=PY(NEN(J,I))
          Z(J)=0.0
 200    CONTINUE
        IT=1
        ICC=IC(1)
        CALL VSPG(X,Y,Z,NN,IT,ICC,IWD)
 100  CONTINUE
C-----------------------------------------------------------------------
C     変化後の座標値を作成します
C-----------------------------------------------------------------------
      DO 300 i = 1,NP
        QX(i) = PX(i) + (U(i) * FT)
        QY(i) = PY(i) + (V(i) * FT)
 300  CONTINUE
C-----------------------------------------------------------------------
C     変化後の図を塗りつぶします
C-----------------------------------------------------------------------
      IF ((ICT.EQ.1.OR.ICM.EQ.1).AND.ISL.EQ.0) THEN
        DO 150 I=1,NE
          DO 250 J=1,NN
            X(J)=QX(NEN(J,I))
            Y(J)=QY(NEN(J,I))
            Z(J)=0.0
 250      CONTINUE
          IT=0
          ICC=0
          CALL VSPG(X,Y,Z,NN,IT,ICC,IWD)
 150    CONTINUE
      ENDIF
C-----------------------------------------------------------------------
C     変化後のメッシュを表示します(ITP=0)
C-----------------------------------------------------------------------
      IF (ICM.EQ.1.AND.ITP.EQ.0) THEN
        write(*,*) 'draw mesh 1'
        IT=1
        ICC=IC(1)
C
        DO 500 I=1,NE
          DO 400 J=1,NN
            X(J)=QX(NEN(J,I))
            Y(J)=QY(NEN(J,I))
            Z(J)=0.0
 400      CONTINUE
          IF (ICM.EQ.1) THEN
            CALL VSPG(X,Y,Z,NN,IT,ICC,IWD)
          ENDIF
 500    CONTINUE
      ENDIF
C-----------------------------------------------------------------------
C     変化後のコンタ図を表示します
C-----------------------------------------------------------------------
      IF (ICT.EQ.1) THEN
        IF (ICS.EQ.0.OR.ICS.EQ.2) THEN
          SMIN =  1.D+72
          SMAX = -1.D+72
          DO 700 I=1,NE
            DO 600 J=1,NN
              SMIN = MIN(SMIN,SC(NEN(J,I)))
              SMAX = MAX(SMAX,SC(NEN(J,I)))
 600        CONTINUE
 700      CONTINUE
        ENDIF
        IF (ICS.EQ.2) THEN
          CALL VEPX2(SMIN,SMAX,IDV,-1)
        ENDIF
C
        IF (IDV.GT.99) THEN 
          IDV = 20
        ENDIF
C
        IF (ITP.EQ.1) THEN
          MC(1) = 0
          DV = 20.8D0/IDV
          DO 800 I=1,IDV
            MC(I+1) = DV*(I-1)+2.D0+0.5D0 
 800      CONTINUE
          MC(IDV+2)=0
        ELSE
          MC(1) = 1
          DV = 20.8D0/IDV
          DO 850 I=1,IDV+1
            MC(I) = DV*(I-1)+2.D0+0.5D0 
 850      CONTINUE
          MC(I) = 1
        ENDIF
C
        DO 900 I=1,IDV
          VC(I) = (SMAX - SMIN) / IDV  * (I - 1 ) + SMIN
 900    CONTINUE
        VC(IDV+1)=SMAX
C
        DO 1100 I=1,NE
          DO 1000 J=1,NN
            X(J)=QX(NEN(J,I))
            Y(J)=QY(NEN(J,I))
            Z(J)=0.0
            S(J)=SC(NEN(J,I))
 1000     CONTINUE
C
          ILIN=1
          IF ( ID.EQ.3 ) THEN
            CALL VETC(X,Y,Z,S,ID,ITP,MC,VC,IDV+1,IWD)
          ENDIF
          IF ( ID.EQ.4 ) THEN
            XX(1)=X(1)
            YY(1)=Y(1)
            ZZ(1)=Z(1)
            SS(1)=S(1)
            XX(2)=X(2)
            YY(2)=Y(2)
            ZZ(2)=Z(2)
            SS(2)=S(2)
            XX(3)=X(3)
            YY(3)=Y(3)
            ZZ(3)=Z(3)
            SS(3)=S(3)
            CALL VETC(XX,YY,ZZ,SS,ID-1,ITP,MC,VC,IDV+1,IWD)
c           CALL VETC(XX,YY,ZZ,SS,ID,ITP,MC,VC,IDV+1,IWD)
C
            XX(1)=X(1)
            YY(1)=Y(1)
            ZZ(1)=Z(1)
            SS(1)=S(1)
            XX(2)=X(3)
            YY(2)=Y(3)
            ZZ(2)=Z(3)
            SS(2)=S(3)
            XX(3)=X(4)
            YY(3)=Y(4)
            ZZ(3)=Z(4)
            SS(3)=S(4)
            CALL VETC(XX,YY,ZZ,SS,ID-1,ITP,MC,VC,IDV+1,IWD)
c           CALL VETC(XX,YY,ZZ,SS,ID,ITP,MC,VC,IDV+1,IWD)
          ENDIF
 1100   CONTINUE
      ENDIF
C-----------------------------------------------------------------------
C     変化後のメッシュ図を表示します(ITP=1)
C-----------------------------------------------------------------------
      IF (ICM.EQ.1.AND.ITP.EQ.1) THEN
        write(*,*) 'draw mesh 2'
        IT=1
        ICC=IC(1)
C
        DO 4500 I=1,NE
          DO 4400 J=1,NN
            X(J)=QX(NEN(J,I))
            Y(J)=QY(NEN(J,I))
            Z(J)=0.0
 4400      CONTINUE
          IF (ICM.EQ.1) THEN
            CALL VSPG(X,Y,Z,NN,IT,ICC,IWD)
          ENDIF
 4500    CONTINUE
       ENDIF
C-----------------------------------------------------------------------
C     カラーバーを表示します
C-----------------------------------------------------------------------
      IF (ICT.EQ.1.AND.ICB.EQ.1) THEN
        IF (ITP.EQ.1) THEN
          IDIV = IDV + 2
        ELSE
          IDIV = IDV
        ENDIF
        CALL VECB2(NCBX,NCBY,IDIV,VC,ITP,1,MC,IWD)
      ENDIF
C-----------------------------------------------------------------------
C     フラッシュ
C-----------------------------------------------------------------------
      CALL VUPD(IWD)
C
      RETURN
      END

