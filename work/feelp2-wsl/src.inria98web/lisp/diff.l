;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   diff.l
;      Date:   1993/06/08 (Modified)
;   
;   Purpose:   数式微分関数
;   Functions: (diff-fmla fmla var) 
;                                      fmlaを varで微分する
;                                      *fem-funcs* で指定されるシンボルに
;                                      対しては、微分演算子を付加したまま
;                                      処理する。
;
;
;              (d-formula1 fmla)       微分演算子を含む数式を処理する
;              
;              
;   外部変数   *fem-funcs*   関数として扱うシンボルのリスト
;                            このリストのmemberに対しては
;                            (dx fmla1) の形で生成
;              
;              *eval-smbl*   evalして微分処理を行うシンボルのリスト
;                            このリストに対しては、
;                            (diff-fmla  (eval fmla) var) を実行
;                   【注意】 *eval-smbl* のメンバーは、*fem-funcs*にも
;                            含まれていなければいけない。
;--------------------------------------------------------------------------

(defun diff-fmla (fmla var)
  (cond 
   ((numberp fmla) 0)                        ; 定数？
   ((symbolp fmla)                           ; 変数
    (if (eq fmla var)
	1                                    ; dx/dx = 1
      (if(member fmla *fem-funcs*)           ; xの関数の場合

	  (if(member fmla *eval-smbl*)       ; シンボルを評価した後微分処理
	      (diff-fmla (eval fmla) var)
	    
	    (case  var                       ; (dx なにがし)の形で出力
		   (x (list 'dx fmla))
		   (y (list 'dy fmla))
		   (z (list 'dz fmla))
		   (t (format t "Inner error in fmla"))))
	0)))


   (t (case (car fmla)           ; リストの場合
	    
	    (+ (cons '+          ; 和の微分法
		     (mapcar #'(lambda (f) (diff-fmla f var))
			     (cdr fmla))))

            (- (list '-          ; 差の微分法
		     (mapcar #'(lambda (f) (diff-fmla f var))
			     (cdr fmla))))

	    (* (cons '+          ; 積の微分法
		     (mapcar #'(lambda (fmlas) (cons '* fmlas))
			     (diff-*-args (cdr fmla) var))))
	    
	    (^ (if (numberp (caddr fmla))
		   (list '*          ; 指数の微分法
			 (caddr fmla)
			 (list '^ (cadr fmla) (1- (caddr fmla)))
			 (diff-fmla (cadr fmla) var)))
	       (format t "階乗の微分で指数が数字ではありません。"))

                                 ; 指数関数
	    (exp (list '*  fmla (diff-fmla (cadr fmla) var)))

                                 ; 三角関数
	    (sin (list '* 
		       (append (list 'cos) (cdr fmla)) 
		       (diff-fmla (cadr fmla) var)))

	    (cos (list '*
		       (list '- (append '(sin) (cdr fmla)))
		       (diff-fmla (cadr fmla) var)))
	    )
      )
   )
)
;--------------------------------------------------------------------------
; 数式微分補助関数（積の微分法）
;--------------------------------------------------------------------------
(defun diff-*-args (fmlas var)
  (if (null fmlas)
      nil
    (cons (cons  (diff-fmla (car fmlas ) var)
		(cdr fmlas))
	  (mapcar #'(lambda (fs)
		      (cons (car fmlas) fs))
		  (diff-*-args (cdr fmlas) var)))))
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;
; 数式微分 補助関数
;
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;--------------------------------------------------------------------------
; シンボルxで微分する
;--------------------------------------------------------------------------
(defun dx (lst)
  (diff-fmla lst 'x))
;--------------------------------------------------------------------------
; シンボルyで微分する
;--------------------------------------------------------------------------
(defun dy (lst)
  (diff-fmla lst 'y))
;--------------------------------------------------------------------------
; シンボルzで微分する
;--------------------------------------------------------------------------
(defun dz (lst)
  (diff-fmla lst 'z))
;--------------------------------------------------------------------------
; 数式内に微分演算子の記述を許す 演算子は（dx,dy,dz）  
;--------------------------------------------------------------------------
(defun d-formula (lst)
  (cond ((null lst) nil)
	((atom lst) lst)
	((atom (car lst)) (cond 
			   ((eq (car lst) 'dx) (dx (cadr lst)))
			   ((eq (car lst) 'dy) (dy (cadr lst)))
			   ((eq (car lst) 'dz) (dz (cadr lst)))
			   (t (cons(car lst) (mapcar #'d-formula(cdr lst))))))
	(t (cond ((eq (caar lst) 'dx)
		  (append (dx (cdar lst))(mapcar #'d-formula (cdr lst))))
		 ((eq (caar lst) 'dy)
		  (append (dy (cdar lst))(mapcar #'d-formula (cdr lst))))
		 ((eq (caar lst) 'dz)
		  (append (dz (cdar lst))(mapcar #'d-formula (cdr lst))))
		 (t (cons (car lst) (mapcar #'d-formula (cdr lst))))))))
