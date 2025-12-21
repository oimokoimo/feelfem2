;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   minus-convert.l
;      Date:   1993/11/16
;   
;   Purpose:   数式に含まれる - 演算子を ＋ 置き換える
;              
; Arguments: 
; Variables: 
;   Symbols:          
; functions: 
;--------------------------------------------------------------------------
(defun minus-convert ( lst )
  (cond  ((atom lst) lst)
	 ((equal '- (car lst))
	  (if (eq (length lst) 2)
	      (list '* '-1 (minus-convert (cadr lst)))
	    (append (list '+ (minus-convert (cadr lst)))
		    (mapcar #'minus-ichi (cddr lst)))))
	 (t (cons (car lst)
		  (mapcar #'minus-convert (cdr lst))))))


(defun minus-ichi ( lst )
  (list '* -1 (minus-convert lst)))

	
	 