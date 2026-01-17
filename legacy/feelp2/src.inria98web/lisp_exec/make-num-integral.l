;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   make-num-integral.l
;      Date:   1993/10/19
;   
;   Purpose:   要素被積分行列から数値積分処理ルーチンを作成
;
; functions:   make-num-integral
;              make-num-integral-nonlinear   *fem-weak-eq*もリスト対象
;                                            とする 
;              
; Variables:   *fem-integrand*     (入) 要素被積分行列
;              *load-integrand*    (入) 被積分荷重ベクトル
;              *fem-funcs*         (入) 有限要素法の基底関数のシンボルリスト
;
;              *fem-weak-eq*       (入) 非線形問題でのF(u)に相当
;              
;              *num-integral-term* (出) 数値積分処理項リスト、まず初期化する
;              
;   Symbols:          
;--------------------------------------------------------------------------
; 以下、メインProgram make-num-integral から prognで処理が呼び出される
;==========================================================================
(defun make-num-integral ()
  (progn
;--------------------------------------------------------------------------
; 変数 *num-integral-term* の初期化
;--------------------------------------------------------------------------
    (setq *num-integral-term* nil)

;==========================================================================

;--------------------------------------------------------------------------
; 数値積分処理項の抜きだし   *num-integral-term* に登録
;
; *dimension*       には、空間次元    
; *fem-integrand*   には、要素被積分行列
; *load-integrand*  には、荷重被積分ベクトル
; *shape-funcs*     には、形状変換関数のリスト
; *fem-funcs*       には、基底関数リスト
;
; 形状関数に関しては、空間次元*dimension* によって
; (dx XXX) (dy XXX) ... を作成し、登録
;--------------------------------------------------------------------------
    (make-fem-term-list *fem-integrand*  )  ; 要素行列項
    (make-fem-term-list *load-integrand* )  ; 荷重項

;   ヤコビアンの為に、形状変換関数の微分(各次元分だけ)を登録する
    (do* ((dim    *dimension* (- dim 1))
	  (ptr    '(dx dy dz)  (cdr ptr))
	  )
	 ((eq 0 dim ) t)
	 (do ((dlst *shape-funcs* (cdr dlst))
	      (diff (car ptr)               ))
	     ((null dlst) t)
	     (make-fem-term-list (cons diff (list (car dlst))))))
	     
;   空間変数が指定されている場合は、形状変換関数も登録する
    (if(or (member 'x *num-integral-term*)
	   (member 'y *num-integral-term*)
	   (member 'z *num-integral-term*))
	(do (( dlst *shape-funcs* (cdr dlst)) )
	    ((null dlst) t)
	    (make-fem-term-list (car dlst))))
;==========================================================================
;--------------------------------------------------------------------------
; 数値積分評価項のfortranソースコード生成
;
;
; 処理の概要
;
; P1_3       →  qP1_3(itp)  なるCOMMON領域の作成
; (DX P1_3)  →  qP1_3x(itp) なるCOMMON領域の作成
;                dxがあればdy(dz ３次元)も作成の必要
;
; r,sを変数とする評価式を作成
;
;
; 数値積分項数
; 名前  微分値    評価式(r, sを変数とする)
;
; 使用LISP関数  make-num-integral-term.l(make-num-integral-term)
; 
;    ファイル est[solve文番号]_[element番号]_[積分法番号]
;     Files:  estXX-YY-ZZ.dat     est関数用のデータ出力ファイル
;              評価式ファイルフォーマット
;              第１行     :項数   
;              第２行〜   :変数名、評価フラグ、      評価式
;                                   0 = normal
;                                   1 = x微分
;                                  10 = y微分
;                                 100 = z微分
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
;--------------------------------------------------------------------------
    (make-num-integral-term-main)

    )  ;progn の終わり
  )    ;defun の終わり

;==========================================================================

(defun make-num-integral-nonlinear ()
  (progn
;--------------------------------------------------------------------------
; 変数 *num-integral-term* の初期化
;--------------------------------------------------------------------------
    (setq *num-integral-term* nil)

;==========================================================================

;--------------------------------------------------------------------------
; 数値積分処理項の抜きだし   *num-integral-term* に登録
;
; *dimension*       には、空間次元    
; *fem-integrand*   には、要素被積分行列
; *load-integrand*  には、荷重被積分ベクトル
; *shape-funcs*     には、形状変換関数のリスト
; *fem-funcs*       には、基底関数リスト
;
; 形状関数に関しては、空間次元*dimension* によって
; (dx XXX) (dy XXX) ... を作成し、登録
;--------------------------------------------------------------------------
    (make-fem-term-list *fem-integrand*  )  ; 要素行列項
    (make-fem-term-list *fem-weak-eq* )     ; 非線形問題の残差荷重

;   ヤコビアンの為に、形状変換関数の微分(各次元分だけ)を登録する
    (do* ((dim    *dimension* (- dim 1))
	  (ptr    '(dx dy dz)  (cdr ptr))
	  )
	 ((eq 0 dim ) t)
	 (do ((dlst *shape-funcs* (cdr dlst))
	      (diff (car ptr)               ))
	     ((null dlst) t)
	     (make-fem-term-list (cons diff (list (car dlst))))))
	     
;   空間変数が指定されている場合は、形状変換関数も登録する
    (if(or (member 'x *num-integral-term*)
	   (member 'y *num-integral-term*)
	   (member 'z *num-integral-term*))
	(do (( dlst *shape-funcs* (cdr dlst)) )
	    ((null dlst) t)
	    (make-fem-term-list (car dlst))))
;==========================================================================
;--------------------------------------------------------------------------
; 数値積分評価項のfortranソースコード生成
;
;
; 処理の概要
;
; P1_3       →  qP1_3(itp)  なるCOMMON領域の作成
; (DX P1_3)  →  qP1_3x(itp) なるCOMMON領域の作成
;                dxがあればdy(dz ３次元)も作成の必要
;
; r,sを変数とする評価式を作成
;
;
; 数値積分項数
; 名前  微分値    評価式(r, sを変数とする)
;
; 使用LISP関数  make-num-integral-term.l(make-num-integral-term)
; 
;    ファイル est[solve文番号]_[element番号]_[積分法番号]
;     Files:  estXX-YY-ZZ.dat     est関数用のデータ出力ファイル
;              評価式ファイルフォーマット
;              第１行     :項数   
;              第２行〜   :変数名、評価フラグ、      評価式
;                                   0 = normal
;                                   1 = x微分
;                                  10 = y微分
;                                 100 = z微分
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
;--------------------------------------------------------------------------
    (make-num-integral-term-main)

    )  ;progn の終わり
  )    ;defun の終わり

;==========================================================================
