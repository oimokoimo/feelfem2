      SUBROUTINE FEEL_XYGRAPH(NLINE,NODES,PX,PY,SX,SY,PPX,PPY,
     $PXMIN,PXMAX,PYMIN,PYMAX,NXDIV,NYDIV,NAXIS,NYAS,NSTEP,IRGF,IWD)
C
      IMPLICIT REAL*8 (A-H,O-Z)
C
      DIMENSION PX(NODES,NLINE)
      DIMENSION PY(NODES,NLINE)
      DIMENSION SX(NODES,NLINE)
      DIMENSION SY(NODES,NLINE)
C
      DIMENSION PPX(NODES),PPY(NODES)
      DIMENSION PXMIN(NLINE),PXMAX(NLINE)
      DIMENSION PYMIN(NLINE),PYMAX(NLINE)
      DIMENSION NXDIV(NLINE),NYDIV(NLINE)
      DIMENSION NAXIS(NLINE)
C
C-----------------------------------------------------------------------
C     このルーチンはFEELのＸＹグラフ図作成を行うルーチンです。
C     各引き数の意味
C
C     NLINE   :グラフの本数
C     NODES   :グラフ１本あたりの点の数
C     PX      :各グラフのＸの配列
C     PY      :各グラフのＹの配列
C     SX      :各グラフのＸの作業領域
C     SY      :各グラフのＹの作業領域
C     PPX     :各グラフのＸの作業領域
C     PPY     :各グラフのＹの作業領域
C     PXMIN   :Ｘ軸の最小値の配列(IRGF=1の時のみ参照)
C     PXMAX   :Ｘ軸の最大値の配列(IRGF=1の時のみ参照)
C     PYMIN   :Ｙ軸の最小値の配列(IRGF=1の時のみ参照)
C     PYMAX   :Ｙ軸の最大値の配列(IRGF=1の時のみ参照)
C     NXDIV   :Ｘ軸の分割数の配列(IRGF=1の時のみ参照)
C     NYDIV   :Ｙ軸の分割数の配列(IRGF=1の時のみ参照)
C     NAXIS   :Ｙ軸表示フラグの配列 ０：書かない １：Ｙ１ ２：Ｙ２
C     NYAS    :Ｙ軸レンジ統一フラグ ０：しない   １：する
C     NSTEP   :グラフのステップ数
C     IRGF    :レンジフラグ ０：Auto １：マニュアル
C     IWD     :ウィンドウＩＤ番号
C-----------------------------------------------------------------------
C     注意事項１   :１０ライン以上は表示できません
C-----------------------------------------------------------------------
C
      DIMENSION ISAVE(10)
C
      DIMENSION XMIN(100),XMAX(100),YMIN(100),YMAX(100)
      DIMENSION FXMIN(10),FXMAX(10),FYMIN(10),FYMAX(10)
      DIMENSION NX(2)
      DATA      NX/2*0/
      DATA      ISAVE/10*0/
      SAVE      ISAVE
      SAVE      XMIN,XMAX,YMIN,YMAX,FXMIN,FXMAX,FYMIN,FYMAX
C
      IF (NLINE.GT.10) THEN
        NLINE=10
      ENDIF
C
      ISTEP=0
      IF (ISAVE(IWD+1).EQ.0) THEN
        CALL FEEL_XYCOLOR(IWD)
        IF(NYAS.EQ.1) THEN
          FXMIN(IWD+1)=PX(1,1)
          FXMAX(IWD+1)=PX(1,1)
          FYMIN(IWD+1)=PY(1,1)
          FYMAX(IWD+1)=PY(1,1)
          DO 201 J=1,NLINE
            DO 101 I=1,NODES
              FXMIN(IWD+1)=MIN(FXMIN(IWD+1),PX(I,J))
              FYMIN(IWD+1)=MIN(FYMIN(IWD+1),PY(I,J))
              FXMAX(IWD+1)=MAX(FXMAX(IWD+1),PX(I,J))
              FYMAX(IWD+1)=MAX(FYMAX(IWD+1),PY(I,J))
101         CONTINUE
201       CONTINUE
        ELSE
          DO 200 J=1,NLINE
            IF (IRGF.EQ.0) THEN
              TXMIN=PX(1,J)
              TXMAX=PX(1,J)
              TYMIN=PY(1,J)
              TYMAX=PY(1,J)
              DO 100 i=1,NODES
                TXMIN=MIN(TXMIN,PX(I,J))
                TYMIN=MIN(TYMIN,PY(I,J))
                TXMAX=MAX(TXMAX,PX(I,J))
                TYMAX=MAX(TYMAX,PY(I,J))
100           CONTINUE
              XMIN(IWD*10+J)=TXMIN-(TXMAX-TXMIN)*0.05
              XMAX(IWD*10+J)=TXMAX+(TXMAX-TXMIN)*0.05
              YMIN(IWD*10+J)=TYMIN-(TYMAX-TYMIN)*0.05
              YMAX(IWD*10+J)=TYMAX+(TYMAX-TYMIN)*0.05
            ELSE
              XMIN(IWD*10+J)=PXMIN(J)
              XMAX(IWD*10+J)=PXMAX(J)
              YMIN(IWD*10+J)=PYMIN(J)
              YMAX(IWD*10+J)=PYMAX(J)
            ENDIF
            CALL VEPX2(XMIN(IWD*10+J),XMAX(IWD*10+J),NXDIV(J),IRGF)
            CALL VEPX2(YMIN(IWD*10+J),YMAX(IWD*10+J),NYDIV(J),IRGF)
200       CONTINUE
        ENDIF
C
        IF(NYAS.EQ.1) THEN
          CALL VEPX2(FXMIN(IWD+1),FXMAX(IWD+1),NXDIV(1),IRGF)
          CALL VEPX2(FYMIN(IWD+1),FYMAX(IWD+1),NYDIV(1),IRGF)
          CALL VEPA(FXMIN(IWD+1),FXMAX(IWD+1),FYMIN(IWD+1),
     $              FYMAX(IWD+1),NXDIV(1),NYDIV(1),1,1,IWD)
        ELSE
          DO 250 J=1,NLINE
            IF (NAXIS(J).EQ.1.AND.NX(1).EQ.0) THEN
              CALL VEPA(XMIN(IWD*10+J),XMAX(IWD*10+J),
     $                  YMIN(IWD*10+J),YMAX(IWD*10+J),
     $                  NXDIV(J),NYDIV(J),1,1,IWD)
              NX(1)=1
            ENDIF
            IF (NAXIS(J).EQ.2.AND.NX(2).EQ.0) THEN
              CALL VEPA(XMIN(IWD*10+J),XMAX(IWD*10+J),
     $                  YMIN(IWD*10+J),YMAX(IWD*10+J),
     $                  NXDIV(J),NYDIV(J),2,1,IWD)
              NX(2)=1
            ENDIF
250       CONTINUE
        ENDIF
      ENDIF
C
      IF(ISTEP.EQ.0.OR.ISTEP.EQ.NSTEP) THEN
        IF(ISAVE(IWD+1).EQ.1) THEN
          IF(NYAS.EQ.1) THEN
            CALL FEEL_XYDRAW2(NLINE,NODES,FXMIN(IWD+1),FXMAX(IWD+1),
     $         FYMIN(IWD+1),FYMAX(IWD+1),SX,SY,PPX,PPY,2,IWD)
          ELSE
            CALL FEEL_XYDRAW(NLINE,NODES,XMIN,XMAX,YMIN,YMAX,
     $                                   SX,SY,PPX,PPY,2,IWD)
          ENDIF
        ENDIF
        IF(NYAS.EQ.1) THEN
          CALL FEEL_XYDRAW2(NLINE,NODES,FXMIN(IWD+1),FXMAX(IWD+1),
     $         FYMIN(IWD+1),FYMAX(IWD+1),PX,PY,PPX,PPY,1,IWD)
        ELSE
          CALL FEEL_XYDRAW(NLINE,NODES,XMIN,XMAX,YMIN,YMAX,
     $                                   PX,PY,PPX,PPY,1,IWD)
        ENDIF
C
        DO 400 j=1,NLINE
          DO 300 i=1,NODES
            SX(i,j)=PX(i,j)
            SY(i,j)=PY(i,j)
300       CONTINUE
400     CONTINUE
C
        ISTEP=0
      ENDIF     
C
      ISAVE(IWD+1)=1
      ISTEP=ISTEP+1
C
      RETURN
      END
C
C
C-----------------------------------------------------------------
C
      SUBROUTINE FEEL_XYCOLOR(IWD)
C
      IMPLICIT REAL*8 (A-H,O-Z)
C
C-----------------------------------------------------------------------
C     このルーチンはFEELのＸＹグラフの色をイニシャライズします
C     各引き数の意味
C
C     IWD     :ウィンドウＩＤ番号
C-----------------------------------------------------------------------
C
      DIMENSION R(3,4)
      DIMENSION G(3,4)
      DIMENSION B(3,4)
C
C     色番号   31  32  33   34  35  36   37  38  39   40  41  42
      DATA  R/1.0,1.0,0.0, 0.5,0.5,0.0, 1.0,0.0,0.0, 0.5,0.0,0.0/
      DATA  G/0.0,1.0,1.0, 0.0,0.5,0.5, 1.0,1.0,0.0, 0.5,0.5,0.0/
      DATA  B/0.0,0.0,1.0, 0.0,0.0,0.5, 0.0,1.0,1.0, 0.0,0.5,0.5/
C
      k=31
      DO 200 j=1,4
        DO 100 i=1,3
          CALL VSCL(R(i,j),G(i,j),B(i,j),k,1,IWD)
          k=k+1
100     CONTINUE
200   CONTINUE
C
      RETURN
      END
C
C-----------------------------------------------------------------
C
      SUBROUTINE FEEL_XYDRAW(NLINE,NODES,XMIN,XMAX,YMIN,YMAX,
     &                                PX,PY,PPX,PPY,NFG,IWD)
C
      IMPLICIT REAL*8 (A-H,O-Z)
C-----------------------------------------------------------------------
C     このルーチンはFEELのＸＹグラフの描画ルーチンです
C     各引き数の意味
C
C     NLINE   :グラフの本数
C     NODES   :グラフ１本あたりの点の数
C     PX      :各グラフのＸの配列
C     PY      :各グラフのＹの配列
C     PPX     :各グラフのＸの作業領域
C     PPY     :各グラフのＹの作業領域
C     XMIN   :Ｘ軸の最小値の配列
C     XMAX   :Ｘ軸の最大値の配列
C     YMIN   :Ｙ軸の最小値の配列
C     YMAX   :Ｙ軸の最大値の配列
C     NFG     :グラフの色のフラグ １：普通の色 ２：薄い色
C     IWD     :ウィンドウＩＤ番号
C-----------------------------------------------------------------------
C
      DIMENSION PX(NODES,NLINE)
      DIMENSION PY(NODES,NLINE)
      DIMENSION PPX(*)
      DIMENSION PPY(*)
      DIMENSION XMIN(*),XMAX(*),YMIN(*),YMAX(*)
C
      DIMENSION NM(10)
      DATA      NM/1,2,3,7*1/
C
      DO 200 j=1,NLINE
        DO 300 i=1,NODES
          PPX(i)=PX(i,j)
          PPY(i)=PY(i,j)
          ILID=j+30
          IMID=j+30+6
300     CONTINUE
C
        IF (NFG.EQ.2) THEN
          ILID=ILID+3
          IMID=IMID+3
        ENDIF
C
        CALL VEPL(PPX,PPY,NODES,XMIN(IWD*10+j),XMAX(IWD*10+j),
     $            YMIN(IWD*10+j),YMAX(IWD*10+j),ILID,IWD)
        CALL VEPM(PPX,PPY,NODES,XMIN(IWD*10+j),XMAX(IWD*10+j),
     $            YMIN(IWD*10+j),YMAX(IWD*10+j),NM(j),IMID,IWD)
C
200   CONTINUE
C
      CALL VUPD(IWD)
C
      RETURN
      END
C
C-----------------------------------------------------------------
C
      SUBROUTINE FEEL_XYDRAW2(NLINE,NODES,XMIN,XMAX,YMIN,YMAX,
     &                                PX,PY,PPX,PPY,NFG,IWD)
C
      IMPLICIT REAL*8 (A-H,O-Z)
C-----------------------------------------------------------------------
C     このルーチンはFEELの統一Ｙ軸用ＸＹグラフの描画ルーチンです
C     各引き数の意味
C
C     NLINE   :グラフの本数
C     NODES   :グラフ１本あたりの点の数
C     PX      :各グラフのＸの配列
C     PY      :各グラフのＹの配列
C     PPX     :各グラフのＸの作業領域
C     PPY     :各グラフのＹの作業領域
C     XMIN   :Ｘ軸の最小値
C     XMAX   :Ｘ軸の最大値
C     YMIN   :Ｙ軸の最小値
C     YMAX   :Ｙ軸の最大値
C     NFG     :グラフの色のフラグ １：普通の色 ２：薄い色
C     IWD     :ウィンドウＩＤ番号
C-----------------------------------------------------------------------
C
      DIMENSION PX(NODES,NLINE)
      DIMENSION PY(NODES,NLINE)
      DIMENSION PPX(*)
      DIMENSION PPY(*)
C
      DIMENSION NM(10)
      DATA      NM/1,2,3,7*1/
C
      DO 200 j=1,NLINE
        DO 300 i=1,NODES
          PPX(i)=PX(i,j)
          PPY(i)=PY(i,j)
          ILID=j+30
          IMID=j+30+6
300     CONTINUE
C
        IF (NFG.EQ.2) THEN
          ILID=ILID+3
          IMID=IMID+3
        ENDIF
C
        CALL VEPL(PPX,PPY,NODES,XMIN,XMAX,YMIN,YMAX,ILID,IWD)
        CALL VEPM(PPX,PPY,NODES,XMIN,XMAX,YMIN,YMAX,NM(j),IMID,IWD)
C
200   CONTINUE
C
      CALL VUPD(IWD)
C
      RETURN
      END
C

