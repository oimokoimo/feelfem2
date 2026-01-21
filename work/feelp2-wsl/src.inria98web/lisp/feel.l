(setq *fem-weak-form* '( (+ (* (dx u)(dx $)) (* (dy u)(dy $)))
		     )
      )
		    
(setq u '(+ (* M1 P1_1) (* M2 P1_2) (* M3 P1_3)))


(setq *test-funcs* '((P1_1 P1_2 P1_3)))   ; 試験関数リスト

(setq *eval-vars*  '( u ) )               ; symbol-eval-replaceで変換する変数
                                          ; fem,ewise,scalar変数
; 【diff.l】の為の変数設定
(setq *fem-funcs* '(P1_1 P1_2 P1_3))      ; 全ての基底関数(diff.l用)
(setq *eval-smbl* nil)                    ; eval用

(setq *coff-vect* '(m1 m2 m3))

(load "replace-string.l")
(load "replace-test-func.l")
(load "symbol-eval-replace.l")

(load "diff.l")                           ; 微分処理関数

(load "fs.l")
(load "diff-fmla-m.l")

;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   test.l
;      Date:   1993/08/16
;   
;   Purpose:   デバッグ用
;
;--------------------------------------------------------------------------
(setq now1 (replace-test-func *fem-weak-form*))
(setq now2 (symbol-eval-replace now1 *eval-vars*))
(setq now2a (car now2))
(setq now3 (d-formula now2a))
(setq now4 (fs now3))
(setq now5 (diff-fmla-m now4 'm1))
(setq now6 (fs now5))




