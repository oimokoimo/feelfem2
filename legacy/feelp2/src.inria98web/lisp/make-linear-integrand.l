;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   make-linear-integrand.l
;      Date:   1993/08/17
;   
;   Purpose:   線形問題に対して、被積分関数のリストを作成する
;              非線形問題に対しては、M1,M2が残留する。この項に対して、
;              u_1,u_3等を置き換える
;
;              未知fem変数の局所節点記法(u_2など)と、m1,m2,などとの対応
;              表はＣ側で用意する(93/08/17現在、非線形バージョンは考慮せず)
;
; Arguments:   lst ((m1,m2,m3, の各式) ...) 
;              coff-list     未知変数シンボル  ( m1 m2 m3 ...) など
;
;   Outputs:   (( (Ａ  ) (Ａ  )  ) (２行目の被積分関数のリスト) ... )
;                    11     12
;--------------------------------------------------------------------------
(defun make-linear-integrand ( lst coff-list )
  (do* ((rst     lst        (cdr rst))
	(expr   (car rst)   (car rst))
	(result  nil                 ))
       ((null rst) result)
       (do* ((coff  coff-list  (cdr coff))
	     (term (car coff)  (car coff))
	     (sres nil                   ))
	    ((null coff) (setq result (append result (list sres))))
	    (setq sres
		  (append sres
			  (list (fs (diff-fmla-m expr term))))))))



