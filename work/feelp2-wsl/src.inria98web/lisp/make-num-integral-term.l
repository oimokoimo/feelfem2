;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   make-num-integral-term.l
;      Date:   1993/11/02
;   
;   Purpose:   数値積分用評価項リスト *num-integral-term*から評価式ファイル
;              を作成
;              
;              評価式ファイルフォーマット
;              第１行     :項数   
;              第２行〜   :変数名、評価フラグ、      評価式
;                                   0 = normal
;                                   1 = x微分
;                                  10 = y微分
;                                 100 = z微分
;                                  -1 = 空間変数
;                                    
;              
; Arguments: 
; Variables:  *solve-no*                 solve文番号
;             *elem-no*                  elem文番号
;             *integral-no*              elem文内の積分法番号
;             *num-integral-term*        数値積分対象リスト
;              
;   Symbols:          
; functions: 
;     Files:  estXX-YY.dat     est関数用のデータ出力ファイル
;
; 変更  1993/12/14
;       (list-print (pre-to-inf lst) fp)   ===>   (exp-print lst fp)
;
;--------------------------------------------------------------------------
;--------------------------------------------------------------------------
;  制御用プログラム
;--------------------------------------------------------------------------
(defun make-num-integral-term-main ()
   (progn (setq *fname*  (format nil "est~D-~D-~D.dat" 
				 *solve-no* *elem-no* *integral-no* ))
	  (setq *fp*     (open *fname* :direction :output) )
	  (format *fp* "~D~%" (length *num-integral-term*))
	  (make-num-integral-term) 
	  (close *fp*)
	  )
   )

;--------------------------------------------------------------------------
; 
;--------------------------------------------------------------------------
(defun make-num-integral-term ()
  (do* ((dlst *num-integral-term* (cdr dlst))
	(rst  (car dlst)          (car dlst)))
       ((null dlst) t)
       (make-num-int-term rst)))


(defun make-num-int-term ( lst )
  (cond  ((equal lst 'x) (format *fp* "qx  0   qx ~%"))
	 ((equal lst 'y) (format *fp* "qy  0   qy ~%"))
	 ((equal lst 'z) (format *fp* "qz  0   qz ~%"))
	 ((atom lst) 
	  (progn (format *fp* "q~S 0 "  lst)
		 (exp-print-fp (eval lst) *fp*)
		 )
	  )
	 (t (make-num-int-term-diffs lst))))

(defun make-num-int-term-diffs ( lst )
  (let ((sbl  (car  lst))
	(term (cadr lst)))
    (cond ((equal 'dx sbl) (do-num-int-term-diffs term '(r)   'x     1 ))
	  ((equal 'dy sbl) (do-num-int-term-diffs term '(s)   'y    10 ))
	  ((equal 'dz sbl) (do-num-int-term-diffs term '(t)   'z   100 ))
	  ((equal 'dxx sbl) (do-num-int-term-diffs term '(r r) 'xx   2 ))
	  ((equal 'dxy sbl) (do-num-int-term-diffs term '(r s) 'xy  11 ))
	  ((equal 'dxz sbl) (do-num-int-term-diffs term '(r t) 'xz 101 ))
	  ((equal 'dyy sbl) (do-num-int-term-diffs term '(s s) 'yy  20 ))
	  ((equal 'dyz sbl) (do-num-int-term-diffs term '(s t) 'yz 110 ))
	  ((equal 'dzz sbl) (do-num-int-term-diffs term '(t t) 'zz 200 ))
	  (t (format t "微分 ~S には対応していません(make-num-int-term-diffs)" sbl)))))

;----------------------------------------------------------------------
(defun do-num-int-term-diffs (lst  diff-lst diff-smbl flag)
  (progn (format *fp* "q~S_~S   ~S " lst diff-smbl flag)
	 (do* ((dlst diff-lst         (cdr dlst))
	       (dif  (car dlst)       (car dlst))
	       (rst  (eval lst)                 ))
	      ((null dlst) 
	       (exp-print-fp (fs rst) *fp*))
	      (setq rst (fs (diff-fmla-m rst dif)))
		     )))
