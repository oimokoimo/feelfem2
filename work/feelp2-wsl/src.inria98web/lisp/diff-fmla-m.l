;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   diff-fmla-m.l
;      Date:   1993/08/17
;   
;   Purpose:   数式微分を用いて係数を割り出す
;              この関数は、線形、非線形共に用いる
;   Functions: (diff-fmla-m fmla var) 
;                                      fmlaを varで微分する
;
;   fmlaがリストの場合のcase文で、
;     (dx 0)等の記載があるが、これは、微分作用素がそのまま着いている
;     数式は、(dx fem-funcのシンボル)しか生成していないはずであることに
;     よる。
;--------------------------------------------------------------------------

(defun diff-fmla-m (fmla var)
  (cond 
   ((numberp fmla) 0)                        ; 定数？
   ((symbolp fmla)                           ; 変数
    (if (eq fmla var)
	1                                    ; dm?/dm? = 1
	0))                                  ; m?以外は０


   (t (case (car fmla)           ; リストの場合
	    
	    (+ (cons '+          ; 和の微分法
		     (mapcar #'(lambda (f) (diff-fmla-m f var))
			     (cdr fmla))))

            (- (list '-          ; 差の微分法
		     (mapcar #'(lambda (f) (diff-fmla-m f var))
			     (cdr fmla))))

	    (* (cons '+          ; 積の微分法
		     (mapcar #'(lambda (fmlas) (cons '* fmlas))
			     (diff-*-args-m (cdr fmla) var))))
	    
	    (^ (if (numberp (caddr fmla))
		   (list '*          ; 指数の微分法
			 (caddr fmla)
			 (list '^ (cadr fmla) (1- (caddr fmla)))
			 (diff-fmla-m (cadr fmla) var))
	       (format t "階乗の微分で指数が数字ではありません。")))

                                 ; 指数関数
	    (exp (list '*  fmla (diff-fmla-m (cadr fmla) var)))

                                 ; 指数関数
	    (dexp (list '*  fmla (diff-fmla-m (cadr fmla) var)))

                                 ; 三角関数
	    (sin (list '* 
		       (append (list 'cos) (cdr fmla)) 
		       (diff-fmla-m (cadr fmla) var)))

	    (dsin (list '* 
		       (append (list 'dcos) (cdr fmla)) 
		       (diff-fmla-m (cadr fmla) var)))

	    (cos (list '*
		       (list '- (append '(sin) (cdr fmla)))
		       (diff-fmla-m (cadr fmla) var)))

	    (dcos (list '*
		       (list '- (append '(dsin) (cdr fmla)))
		       (diff-fmla-m (cadr fmla) var)))
	    (dx 0)
	    (dy 0)
	    (dz 0)
	    )
      )
   )
)
;--------------------------------------------------------------------------
; 数式微分補助関数（積の微分法）
;--------------------------------------------------------------------------
(defun diff-*-args-m (fmlas var)
  (if (null fmlas)
      nil
    (cons (cons  (diff-fmla-m (car fmlas ) var)
		(cdr fmlas))
	  (mapcar #'(lambda (fs)
		      (cons (car fmlas) fs))
		  (diff-*-args-m (cdr fmlas) var)))))
