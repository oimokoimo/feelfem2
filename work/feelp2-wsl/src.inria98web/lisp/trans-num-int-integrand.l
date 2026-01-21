;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   trans-num-int-integrand.l
;      Date:   1993/11/19
;   
;   Purpose:   *fem-integrand*から、数値積分用のプログラム生成補助データ作成
;              
;              
;              *fem-funcs* に関する取り扱い
;              
;              微分演算子付き (dx Q1_4)   → qQ1_4_x_##p   ##は数値積分番号
;                                            数値積分番号を付加する必要は
;                                            ないが、一応付加するか…
;----------------------------------------------------------------------------
;              以下の変更はＣの処理で行う
;       
;              *fem-funcs* に関する取り扱い
;
;              そのまま        Q1_4     → qQ1_4_##(itp)   ##は数値積分番号
;
;              *quad_var* に関する取り扱い
;              
;              A1                       → qA1_##(itp)      ##は数値積分番号
;              
;----------------------------------------------------------------------------
(defun trans-num-int-integrand ( lst )
  (cond ((atom lst) lst)
	((equal 'dx  (car lst)) (make-num-quad-diff-term (cadr lst) 'x))
	((equal 'dy  (car lst)) (make-num-quad-diff-term (cadr lst) 'y))
	((equal 'dz  (car lst)) (make-num-quad-diff-term (cadr lst) 'z))
	((equal 'dxx (car lst)) (make-num-quad-diff-term (cadr lst) 'xx))
	((equal 'dxy (car lst)) (make-num-quad-diff-term (cadr lst) 'xy))
	((equal 'dxz (car lst)) (make-num-quad-diff-term (cadr lst) 'xz))
	((equal 'dyy (car lst)) (make-num-quad-diff-term (cadr lst) 'yy))
	((equal 'dyz (car lst)) (make-num-quad-diff-term (cadr lst) 'yz))
	((equal 'dzz (car lst)) (make-num-quad-diff-term (cadr lst) 'zz))
	(t (cons (car lst)
		 (mapcar #'trans-num-int-integrand (cdr lst))))))

(defun make-num-quad-diff-term (term lst)
  (let (( str   (format  nil "q~S_~S_~Dp" term lst *integral-no*)) )
    (read-from-string str)))





