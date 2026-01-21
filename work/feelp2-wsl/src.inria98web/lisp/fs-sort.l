;--------------------------------------------------------------------
;  関数 fs-sort
;    fs-term-bindより出力された連想リストから、ソートされた数式データ
;    を作る
; 
;  全体の処理の流れ
;    fs-dep   -> fs-term-bind -> fs-sort -> 完成
;                                ^^^^^^^
;
;    入力   連想リスト  例えば、( ( x . 1) ( (* c d) . 10) ( (^ x 3) . 3))
;       
;           特別な場合  (nil)  -> 0 とする
;
;    出力   最終的な出力
;
;    補助関数群
;
;--------------------------------------------------------------------
(defun fs-sort (lst)
  (if (null lst) 0
    (do ((dlst lst (cdr dlst))
	 (rlst nil           ))
	((null dlst) (if (eq 1 (length rlst)) (car rlst)
			     (cons '+ rlst)))
	(let (( item (caar dlst) )
	      ( cof  (cdar dlst) ) )
	  (cond ((numberp item) (setq rlst (cons cof rlst)))
		((eq 1 cof    ) (setq rlst (cons item rlst)))
		((atom item   ) (setq rlst (cons (cons '* (list cof item)) rlst)))
		((eq '* (car item)) 
		 (setq rlst (cons (cons '* (cons cof (cdr item))) rlst)))
		(t (setq rlst (cons (cons '* (list cof item)) rlst))))))))

	 



