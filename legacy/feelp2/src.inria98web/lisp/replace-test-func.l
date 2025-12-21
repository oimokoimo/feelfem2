;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   replace-test-func.l
;      Date:   1993/08/16
;   
;   Purpose:   弱形式に含まれている試験関数シンボルを、実際の
;              試験関数で置換する
;              
; Arguments:   lst          ((eq1) (eq2) ...) eq1,eq2
;
;              
; Variables:   *test-funcs*  試験関数の列 ((eq1の試験関数リスト)
;                                          (eq2の試験関数リスト) (...) ... )
;
;   Symbols:   $             試験関数を表すシンボル
;              
;--------------------------------------------------------------------------
(defun replace-test-func ( lst )
  (do* ((rst   lst          (cdr rst))  ;
	(dlst  (car rst)    (car rst))  ; dlst は連立する各行
	(tst   *test-funcs* (cdr tst))  ; tst  は試験関数のリストのリスト
	(func  (car tst)    (car tst))  ; func は各方程式に対する試験関数リスト
	(result   nil                )  ; result は結果を入れる
	)
       ((null rst) result)
       (do* ((lfunc func (cdr lfunc))   ; local-func ループの基本となる
	                                ; eqの各行に対する試験関数リスト
	     (testf (car lfunc) (car lfunc)) ; 今回用いる試験関数シンボル
	     (res   nil             ))  ; resには結果を入れる
	    ((null lfunc) (setq result (append result res)))
	    (setq res (append res 
			      (list (replace-string dlst '$ (car lfunc))))))))

