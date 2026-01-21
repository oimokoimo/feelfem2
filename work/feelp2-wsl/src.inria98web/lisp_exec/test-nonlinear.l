;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   test.l
;      Date:   1993/08/16
;   
;   Purpose:   デバッグ用
;
;--------------------------------------------------------------------------
(setq *fem-weak-eq* '( (+ (* (dx u)(dx $)) (* (dy u)(dy $))
			    (* $ C1 ni (exp (* -1 S u)))
			    (* -1 $ C1 ni (exp (*  S u)))
			    (* $ C1 Q))

		     )
      )
		    
(setq u '(+ (* M1 P1_1) (* M2 P1_2) (* M3 P1_3)))
(setq ni '(+ (* ni_1 P1_1) (* ni_2 P1_2) (* ni_3 P1_3)))
(setq S  '(+ (* s_1 P1_1) (* s_2 P1_2) (* s_3 P1_3)))
(setq Q  '(+ (* q_1 P1_1) (* q_2 P1_2) (* q_3 P1_3)))


(setq *test-funcs* '((P1_1 P1_2 P1_3)))   ; 試験関数リスト
(setq *eval-vars*  '( u ni s q ) )        ; symbol-eval-replaceで変換する変数


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
