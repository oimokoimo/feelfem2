;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   symbol-eval-replace.l
;      Date:   1993/08/10
;  Modified:   1993/11/19
;   
;   Purpose:   値が割り付けられているシンボルに対して、そのシンボルをその
;              値で置換する。(旧fem-var-eval関数)
;   Functions: (symbol-eval-replace lst mem)
;              memに含まれているシンボルがlstにある場合、そのシンボルを
;              evalし、その値で置換する
;
;              (symbol-eval-replace-quad lst mem cancel-mem)
;              数値積分内挿法指定の変数に対して置換を実行を
;              抑制する。これは、memの内、cancel-memに含まれている
;              ものを消して、symbol-eval-replaceを呼ぶ
;--------------------------------------------------------------------------
(defun symbol-eval-replace-quad (lst mem cancel-mem)
  (symbol-eval-replace lst (list-minus mem cancel-mem)))

(defun list-minus  ( a  b )
  (do* (( rst     nil                      )
	( member  a           (cdr member) )
	( mem    (car member) (car member) ))
       ((null member) rst)
       (if(not (member mem  b)) (setq rst ( cons mem rst)))))
	
;
;---
;
(defun symbol-eval-replace (lst mem)
  (cond ((atom lst) (if (member lst mem) (eval lst) lst))

; 展開すべきシンボルがべき乗で現れている場合
; (^ u1 3)  u1 が 展開すべきシンボルの場合
;
;【注意】 たとえば、(^ (+ u1 u3) 3)が一意か？
;
;
	((and (eq 3 (length lst))      
	      (member (cadr lst) mem)
	      (eq '^ (car lst))
	      (numberp (caddr lst)))
	 (do ((rlst  '(*)   )
	      (n    (caddr lst) (- n 1)))
	     ((eq 0 n) rlst)
	     (setq rlst 
		   (append rlst (list (eval (cadr lst)))))))
	(t (cons (symbol-eval-replace (car lst) mem)
		 (symbol-eval-replace (cdr lst) mem)))))






