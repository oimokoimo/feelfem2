;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   make-fem-term-list.l
;      Date:   1993/10/19
;   Bug-fix:   1993/11/11   member の LIST対応
;   
;   Purpose:   数値積分時に評価が必要な項の抜きだし
;              微分としては (dx なにがし)
;              座標として   x,y,z
;          
;          
; Arguments: 
; Variables:   *num-integral-term*  数値積分時に特別扱が必要な項
;                                   これは、最初 NILにしておくこと
;                                   このシンボルにどんどん足して行く
;         
;              *fem-funcs*          基底関数の集合
;        
;             
;   CAUTION:   微分作用素の場合は(作用素 シンボル) という形で入ってくること
;              たとえば、(* 3 (DX P1_1)) など。(DX (* 3 P1_1)) は不可。
;             
;              ヤコビアン計算のため、DX DY DZ についても作成
;             
;             
;--------------------------------------------------------------------------
(defun make-fem-term-list ( lst )
  (cond 
   ( (atom lst) 
     (cond 
      ((equal 'x lst) (add-make-fem-term-list 'x))
      ((equal 'y lst) (add-make-fem-term-list 'y))
      ((equal 'z lst) (add-make-fem-term-list 'z))

      ((member lst *fem-funcs*) (add-make-fem-term-list lst))
      (t nil)))
;
; 数値積分計算時は、(dx PH_1)が必要な時は(dy PH_1)等も必要になる
;
   ( (eq (car lst) 'dx) 
     (progn (add-make-fem-term-list lst)
;２次元
	   (if (not (equal *dimension* 1))
	       (add-make-fem-term-list (cons 'dy (list (cadr lst)))))

;3次元
	   (if (equal *dimension* 3)
	       (add-make-fem-term-list (cons 'dz (list (cadr lst)))))
	   ))
   ( (eq (car lst) 'dy) (add-make-fem-term-list lst)
	   (add-make-fem-term-list (cons 'dx (list (cadr lst))))
	   (if (equal *dimension* 3)
	       (add-make-fem-term-list (cons 'dz (list (cadr lst))))
	     ))
   ( (eq (car lst) 'dz) (progn (add-make-fem-term-list lst)
			       (add-make-fem-term-list (cons 'dx (list (cadr lst))))
			       (add-make-fem-term-list (cons 'dy (list (cadr lst))))))
;
;   ２階以上の微分は保留
;
   ( (eq (car lst) 'dxx) (add-make-fem-term-list lst))
   ( (eq (car lst) 'dxy) (add-make-fem-term-list lst))
   ( (eq (car lst) 'dxz) (add-make-fem-term-list lst))
   ( (eq (car lst) 'dyy) (add-make-fem-term-list lst))
   ( (eq (car lst) 'dyz) (add-make-fem-term-list lst))
   ( (eq (car lst) 'dzz) (add-make-fem-term-list lst))
;
;  cons,cdrで全てのLIST要素について検査
;
   (t (progn (make-fem-term-list (car lst))
	     (make-fem-term-list (cdr lst))))))

;;;;;
;--------------------------------------------------------------------------
; 関数 add-make-fem-term-list  実際に *num-integral-term* に代入
;--------------------------------------------------------------------------
(defun add-make-fem-term-list ( lst )
  (if(list-member lst *num-integral-term*) nil
    (setq *num-integral-term* (cons lst *num-integral-term*))))



(defun list-member (mem  lst)
  (do ((dlst lst (cdr dlst))
       (flag nil           ))
      ((null dlst) flag)
      (if(equal mem (car dlst))
	  (setq flag t))))
