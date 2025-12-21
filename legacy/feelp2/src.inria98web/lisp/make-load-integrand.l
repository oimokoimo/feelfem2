;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   make-load-integrand.l
;      Date:   1993/10/20
;   
;   Purpose:   荷重被積分ベクトルを計算する
;              
; Arguments: weak-form   弱形式(M1,M2等が含まれる)
;            coff-lst    M1 M2 などのシンボル
;            
;            処理は、coff-smblに含まれる項を、zero-replace関数で0に置き換え
;            数式簡単化関数fsにより右辺項を得ている
; Variables: 
;   Symbols:          
; functions: 
;--------------------------------------------------------------------------

(defun make-load-integrand (weak-form coff-lst)
  (do* (( rst   nil                  )
	( dlst  weak-form  (cdr dlst))
	( lst   (car dlst) (car dlst)))
       ((null dlst)  rst )
       (setq rst (append rst 
			  (list (fs (list '* '-1 (zero-replace lst coff-lst))))))))

;--------------------------------------------------------------------------
; 補助関数  (zero-replace lst coff-lst) 
;     機能  lst のうち、coff-lstに含まれるものを 0 で置換
;--------------------------------------------------------------------------
(defun zero-replace (lst coff-lst)
  (if (atom lst)
      (if (member lst coff-lst) 0  lst)  ; coff-lstにあれば０なければそのまま
    (cons (zero-replace (car lst) coff-lst)
	  (zero-replace (cdr lst) coff-lst))))