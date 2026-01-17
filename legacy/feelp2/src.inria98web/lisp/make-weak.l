;------------------------------------------------------------------
;  feel p2 弱形式化プログラム
;
;  入力          *fem-pde-eq* 
;  フォーマット  (  ( 偏微分方程式その１)
;                   ( 偏微分方程式その２) .... )
;  偏微分方程式のフォーマット
;                ( 右辺  左辺 )
;
;  出力  弱形式  領域積分項  *fem-weak-eq*
;        弱形式  境界積分項  *fem-edge-eq*
;
;  許されるOperator
;   LAP      ラプラシアン
;   (lap u)   ->  (* -1 (+ (* (dx u)(dx $)) (* (dy u)(dy $))))  領域積分項
;             ->  (* (dn u) $)                                  境界積分項
;
;   DIV_GRAD 一般化ラプラシアン
;   (div_grad (a)  u)
;             ->  (* -1 (+ (*  (a) (dx u)(dx $)) (* (a) (dx
;
;   注意  fem変数は関数、ewise変数は定数として扱われる
;
;------------------------------------------------------------------
(defun make-weak-proc ()
  (progn
    (setq *fem-weak-eq* nil
	  *fem-edge-eq* nil )
    (do (( dlst *fem-pde-eq** (cdr dlst))
	 ( eqno    1          (+1  eqno))
	 ( tmp    nil                   ))
	((null dlst) t)
	
