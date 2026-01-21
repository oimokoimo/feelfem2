;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   replace-string.l
;      Date:   1993/08/16
;   
;   Purpose:   シンボルの置き換え
;   
; Arguments:   lst   置き換えるlist
;              from  置き換えるシンボル(元)
;              to    置き換えるシンボル(新)
;          
;--------------------------------------------------------------------------
(defun replace-string (lst from to)
  (cond ((atom lst) (if (equal lst from) to  lst))
	(t (cons (replace-string (car lst) from to)
		 (replace-string (cdr lst) from to)))))
