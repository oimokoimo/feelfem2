;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   test.l
;      Date:   1993/08/16
;   
;   Purpose:   デバッグ用
;
;--------------------------------------------------------------------------
(setq *fem-weak-eq* '( (+ (* (dx u)(dx $)) (* (dy u)(dy $)) (* f $))
		     )
      )
		    
(setq u '(+ (* M1 P1_1) (* M2 P1_2) (* M3 P1_3)))
(setq f '(+ (* f_1 P1_1) (* f_2 P1_2) (* f_3 P1_3)))


(setq *test-funcs* '((P1_1 P1_2 P1_3)))   ; 試験関数リスト
(setq *eval-vars*  '( u f ) )        ; symbol-eval-replaceで変換する変数


;  現在、ni, s , q を定数と置いています
;(setq *eval-vars*  '( u ) )        ; symbol-eval-replaceで変換する変数


                                          ; fem,ewise,scalar変数
; 【diff.l】の為の変数設定
(setq *fem-funcs* '(P1_1 P1_2 P1_3))      ; 全ての基底関数(diff.l用)
(setq *eval-smbl* nil)                    ; eval用

(setq *coff-vect* '(m1 m2 m3))


;---------------
;実行プログラム
;---------------
(load "feel-package.l")
(time (load "make-linear-weak.l"))
