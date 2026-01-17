;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   do-d-formula.l
;      Date:   1993/08/17
;   
;   Purpose:   ( (lst1) (lst2) (lst3) )の構造を持つデータに対して
;              各リストに含まれている微分記号の処理を行う
; Arguments:   ( (lst1) (lst2) (lst3) )
; Variables:   *fem-funcs* (diff.lにて使用)
;--------------------------------------------------------------------------

(defun do-d-formula ( lst )
  (do* ((rst   lst       (cdr rst))   ; 式の残り
	(expr  (car rst) (car rst))   ; 各式
	(result  nil              ))  ; 結果
       ((null rst) result)
       (setq  result 
	      (append result (list (fs (d-formula expr)))))))