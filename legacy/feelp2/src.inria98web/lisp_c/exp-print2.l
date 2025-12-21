;----------------------------------------------------------------------------
;  FEEL Finite Element Equation Language FORTRAN77 Code Generator
;
;  Sub-program
;
;  Made      1992/02/24
;----------------------------------------------------------------------------
;----------------------------------------------------------------------------
;  補助関数  リスプ形式の接頭記法から挿入記法への変換
;         培風館 『LISP』より引用
;----------------------------------------------------------------------------
(defun exp-print-fp (lst fp)
  (list-print-x (pre-to-inf lst) fp))

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
;--------------------------------------------------------------------------
(defun list-print-x (lst FP)
  (PROGN  (list-print lst FP)(format FP "~%")))
(defun list-print (lst FP)
  (cond ((atom lst) (FORMAT FP "~S" lst))
	((is-function-exp lst) 
	 (do ((dlst (cdr lst)                    (cdr dlst))
	      (num       0                       (+ 1 num) )
	      (func (format fp "~S(" (car lst))            ))
	     ((null dlst) (format fp ")"))
	     (progn (cond 
		     ((floatp  (car dlst)) (FORMAT FP "~A" (car dlst)))
		     ((numberp (car dlst)) (FORMAT FP "~A.0" (car dlst)))
		     ((atom    (car dlst)) (FORMAT FP "~A"   (car dlst)))
		     (t 
		      (progn (format fp "(")
			     (list-print (car dlst) FP)
			     (FORMAT FP ")"))))
		    (if(eq nil (cdr dlst)) t
		      (format fp ",")))))
	(t
	 (do ((dlst (FORT77-CONVERT lst) (cdr dlst)))
	     ((null dlst) t )
	     (cond 
		   ((floatp  (car dlst)) (FORMAT FP "~A" (car dlst)))
		   ((numberp (car dlst)) (FORMAT FP "~A.0" (car dlst)))
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
