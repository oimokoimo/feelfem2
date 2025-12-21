;----------------------------------------------------------------------------
;  FESL Finite Element Simulation Language FORTRAN77 Code Generator
;
;  Sub-program
;
;  Made      1992/02/24
;----------------------------------------------------------------------------
;----------------------------------------------------------------------------
;  補助関数  リスプ形式の接頭記法から挿入記法への変換
;         培風館 『LISP』より引用
;----------------------------------------------------------------------------
(defun exp-print (lst)
  (list-print-x (pre-to-inf (beki-fix lst)) t))

(defun exp-print-fp (lst fp)
  (list-print-x (pre-to-inf (beki-fix lst)) fp))

(defun pre-to-inf (l)
  (cond ((null l) nil)
	((atom l)  l )
	((null (member (car l) '( + - * / ^))) 
	 (cons (car l) (mapcar #'pre-to-inf (cdr l))))
	(t (pre-to-inf-aux  (mapcar #'pre-to-inf (cdr l)) (car l)))))

(defun pre-to-inf-aux  (lst smbl)
  (cdr (pre-to-inf-aux2 lst smbl)))
		 
(defun pre-to-inf-aux2 ( lst  smbl)
  (cond ((null lst) nil)
	(t (append (list smbl (car lst)) (pre-to-inf-aux2 (cdr lst) smbl)))))
;--------------------------------------------------------------------------
; LIST-PRINT
; Made      1992/01/30
; Modified  1992/02/18
; Modified  1993/11/18
;--------------------------------------------------------------------------
(defun list-print-x (lst FP)
  (PROGN  (list-print lst FP)(format FP "~%")))
(defun list-print (lst FP)
  (cond ((floatp  lst) (FORMAT FP "~Ad0"   lst ))
	((numberp lst) (FORMAT FP "~A.0d0" lst ))
	((atom lst)    (FORMAT FP "~S"     lst ))
	((is-function-exp lst) 
	 (do ((dlst (cdr lst)                    (cdr dlst))
	      (num       0                       (+ 1 num) )
	      (func (format fp "~S(" (car lst))            ))
	     ((null dlst) (format fp ")"))
	     (progn (cond 
		     ((floatp  (car dlst)) (FORMAT FP "~Ad0" (car dlst)))
		     ((numberp (car dlst)) (FORMAT FP "~A.0d0" (car dlst)))
		     ((atom    (car dlst)) (FORMAT FP "~A"   (car dlst)))
		     (t 
		      (progn (format fp "(")
			     (list-print (car dlst) FP)
			     (FORMAT FP ")"))))
		    (if(eq 0 num) t
		      (format fp ",")))))
	(t
	 (do ((dlst (FORT77-CONVERT lst) (cdr dlst)))
	     ((null dlst) t )
	     (cond 
		   ((floatp  (car dlst)) (FORMAT FP "~Ad0" (car dlst)))
		   ((numberp (car dlst)) (FORMAT FP "~A.0d0" (car dlst)))
		   ((atom    (car dlst)) (FORMAT FP "~A" (car dlst)))
		   (t (progn(FORMAT FP "(")
			    (list-print (car dlst) FP)
			    (FORMAT FP ")"))))))))

;--------------------------------------------------------------------------
; FORT77-CONVERT
;
;--------------------------------------------------------------------------
(defun FORT77-CONVERT (LST)
  (COND ((EQ LST '^) '**)
	((ATOM LST ) LST)
	(T (CONS (FORT77-CONVERT (CAR LST))
		 (FORT77-CONVERT (CDR LST))))))
;--------------------------------------------------------------------------
; funtion test
;--------------------------------------------------------------------------
(defun is-function-exp ( lst )
  (cond ((member '+ lst) nil)
	((member '- lst) nil)
	((member '* lst) nil)
	((member '/ lst) nil)
	((member '^ lst) nil)
	((member '** lst) nil)
	(t t)))

;-----------------------------------------------------------------
; 関数 beki-fix
;   (^ XXXX  数字) の場合、 掛け算に変更する
;
;-----------------------------------------------------------------
(defun beki-fix ( lst )
  (cond ((atom lst) lst)
	((and (eq '^ (car lst)) (integerp (caddr lst)))
	 (cond ((= 0 (caddr lst))   1)
	       ((> 0 (caddr lst)) lst)
	       (t
		(do* ((expr (list (cadr  lst))          )
		      (num  (caddr lst)        (- num 1))
		      (dlst '(* )                       ))
		     ((= 0 num) dlst )
		     (setq dlst  (append dlst expr))))))
	(t (cons (car lst)
		 (mapcar #'beki-fix (cdr lst))))))

	       

