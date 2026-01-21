;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   make-num-int-matrix-dat.l
;      Date:   1993/11/19
;   
;   Purpose:   連立一次方程式
;              
; Arguments: 
; Variables: 
;   Symbols:          
; functions:   make-num-int-matrix-dat            ecalデータを作成
;              make-num-int-matrix-dat-nonlinear  非線形版ecalデータを作成
;--------------------------------------------------------------------------
;==========
; 線形版 
;==========
(defun make-num-int-matrix-dat ()
   (progn (setq *fname*  (format nil "ecal~D-~D-~D.dat" 
				 *solve-no* *elem-no* *integral-no* ))
	  (setq *fp*     (open *fname* :direction :output) )
	  (make-num-int-matrix-mat)    ; 要素小行列部分
	  (make-num-int-matrix-load)   ; ロードベクトル
	  (close *fp*)
	  )
   )
;==========
; 非線形版 
;==========
(defun make-num-int-matrix-dat-nonlinear ()
   (progn (setq *fname*  (format nil "ecal~D-~D-~D.dat" 
				 *solve-no* *elem-no* *integral-no* ))
	  (setq *fp*     (open *fname* :direction :output) )
	  (make-num-int-matrix-mat)              ; 要素小行列部分(ヤコビアン)
	  (make-num-int-matrix-nonlinear-load)   ; 残差ベクトル
	  (close *fp*)
	  )
   )

;--------------------------------------------------------------------------
;  make-num-int-matrix-mat
;--------------------------------------------------------------------------
(defun make-num-int-matrix-mat  ()
  (do* (( dlst *fem-integrand* (cdr dlst) )
	( rlst (car dlst)      (car dlst) ))
       ((null dlst) t)
       (do* ( ( dlst2  rlst       (cdr dlst2) )
	      ( rlst2 (car dlst2) (car dlst2) ) )
	    ((null dlst2) t)
	    (exp-print-fp ( trans-num-int-integrand  rlst2 ) *fp* ))))
	
;--------------------------------------------------------------------------
;  make-num-int-matrix-load
;  make-num-int-matrix-nonlinear-load
;--------------------------------------------------------------------------
(defun make-num-int-matrix-load ()
  (do* (( dlst *load-integrand* (cdr dlst) )
	( rlst (car dlst)      (car dlst) ))
       ((null dlst) t)
       (exp-print-fp ( trans-num-int-integrand  rlst ) *fp* )))
	
(defun make-num-int-matrix-nonlinear-load ()
  (do* (( dlst *fem-weak-eq* (cdr dlst) )
	( rlst (car dlst)      (car dlst) ))
       ((null dlst) t)
       (exp-print-fp ( trans-num-int-integrand  rlst ) *fp* )))
	

	
