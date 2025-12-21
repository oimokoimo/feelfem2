;--------------------------------------------------------------------
;  関数 fs-term-bind
;    各単項式を整理する。この関数はfs-depより出力された単項式の同次項を
;    まとめる。
; 
;  全体の処理の流れ
;    fs-dep   -> fs-term-bind -> fs-sort -> 完成
;                ^^^^^^^^^^^
;
;    入力   単項式を仮定   (+ 2 3 (* 2 d e) (* 3 (^ x 3))) など、
;           リストの先頭が＋になっていること。（それ以外の場合は
;           なにもしない。
;       
;    出力   連想リストを出力する（fs-sort入力用）
;
;    補助関数群
;    fs-term-bind-single  単項に対してドットペアを作成する。
;                         ０となるときはnilを出力する。
;--------------------------------------------------------------------
(defun fs-term-bind (lst)
  (cond 
   ((atom lst) (list (fs-term-bind-single lst)))
   ((not (eq '+ (car lst))) (list (fs-term-bind-single lst)))
					;うえの二つは連想リストを返す
   (t
    (do ((dlst (cdr lst) (cdr dlst))
	 (result  nil              ) )      ; result は連想リスト
	((null dlst) result)
	(let* ( (item (fs-term-bind-single (car dlst))) 
					;itemは記録すべきドット対
		(obj  (assoc (car item) result :test (function equal))     ) )
					;obj は該当項のドット対


	  (if (not (null item))         ;itemが０でない時だけ処理する！！！
	      (if (null obj)                    
					;nullのとき、itemは新顔ということ
		  (setq result (cons item result))
		(let ((num (+ (cdr item) (cdr obj))))
					;係数を計算して
					;０の場合を除外する。
		  (if (eq num 0)
		      (setq result (remove obj result))
					;たした結果（num）を代入する
		    (setf (cdr (assoc (car item) result :test (function equal))) num))))))))))

;--------------------------------------------------------------------
;  関数 fs-term-bind-single
;
;     単項に対してドットペアを作成する。
;     
;     注意  ０となるときはnilを出力する。
;--------------------------------------------------------------------
(defun fs-term-bind-single (lst)
  (cond ((numberp lst) (cons 1 lst))    ; 数値の場合
	((atom    lst) (cons lst 1))    ; シンボルの場合
	((not (eq '* (car lst)))        ; かけ算以外の場合、将来複雑な関数
					; を扱う場合ここも表現に一意性が保
					; たれるようにしなければいけない
	                                ; 現状では、単に単項にしているだけ
	 (cons lst 1))
	((member 0 lst) '(1 . 0))            ; かけると０になる
	(t
	 (do*(( num     1       )       ;係数
	      ( sbl   nil       )       ;単項
	      ( fnc   nil       )       ;関数
              ( alst  nil       )       ;連想リスト
              ( dlst (cdr lst) (cdr dlst))   ;do 制御リスト
	      ( item (car dlst) (car dlst))) ;do 制御のかー
	     ((null dlst) (cons (mk-tb-sngl-car alst sbl fnc) num))
	     (cond ((numberp item) (setq num (* num item)))  ; 数値係数項
		   ((atom    item) 
		    (if (member item sbl)      ;既に該当項がある場合
			(let ((cof (cdr (assoc item alst :test (function equal)))))
			  (setf (cdr (assoc item alst :test (function equal))) (+ cof 1)))
					       ;該当項がない場合
		      (setq  sbl  (cons item sbl)
			     alst (cons (cons item 1) alst))))
					;冪乗項の場合
		   ((eq '^ (car item))
		    (let ( (cof2 (caddr item))      ; 指数
			   (sbl2 (cadr  item)) )    ; 底
		      (cond ((atom sbl2)            ; 底がシンボルの場合
			     (if (member sbl2 sbl)
				 (let ((cof3
					(cdr (assoc sbl2 alst :test (function equal)))))
				   (setf (cdr (assoc sbl2 alst :test (function equal))) (+ cof3 cof2)))
			       (setq sbl (cons sbl2 sbl)
				     alst (cons (cons sbl2 cof2) alst))))
					;底がリストの場合
			    (t (if (member sbl2 fnc) ; 注意！！fncはそーちんぐ
                                                     ; していない（拡張予定）
				   (let ((cof3
					  (assoc sbl2 alst :test (function equal))))
				     (setf (cdr (assoc sbl2 alst :test (function equal))) (+ cof2 cof3)))
				 (setq fnc (cons sbl2 fnc)
				       alst (cons (cons sbl2 cof2) alst)))))))
					; リストの場合、表現の一意性に注意！！
		   (t (if (member item fnc )
			  (let ((cof3 (assoc item alst :test (function equal))))
			    (setf (cdr assoc item alst :test (function equal))
				  (+ cof3 1)))
			(setq fnc (cons item fnc)
			      alst (cons (cons item 1) alst)))))))))
;--------------------------------------------------------------------
;  関数 mk-tb-sngl-car
;    与えられたドット対より、単項ドット対のかーの部分を作成する。
;      ( (x . 3) (oimo . 2) (y . 1)) -> (* y (^ x 3) (^ oimo 2))
;    １次の単項の場合、
;      (  (x . 2) )                  -> (^ x 2)
;--------------------------------------------------------------------
(defun mk-tb-sngl-car (alst sbl fnc)
  (cond ((eq 1 (length alst)) (if (eq 1 (cdar alst)) (caar alst)
				(cons '^ (list (caar alst) (cdar alst)))))
	(t
	 (do ((dlst (append (sbl-sort sbl) (lst-sort fnc)) (cdr dlst))
	      (rst  nil            ))
                                       ; dlstの順番に並び替える
;
;              下の(null rst)判定は、(* 20 30) の時の為に
;                                     1992/02/05に修正しました。
;
	     ((null dlst) (if (null rst) 1 (cons '* rst)))
	     (let ((item (assoc (car dlst) alst :test (function equal))))
	       (if (eq 1 (cdr item))
		   (setq rst (cons (car item) rst))
;
;   下のイフ文の最初の条件は拡張しました。(1992/02/04) ちょっと不安です。
;
;   目的は(^ a 0) なるときに１にする為だと思う。(1992/02/05)昨日のことなので
;                                                           よく覚えてない？
;
		 (if(eq 0 (cdr item)) nil
		   (setq rst (append rst 
				     (list (cons '^ 
						 (list (car item) (cdr item)))))))))))))

      

		      





















