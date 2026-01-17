;;;==========================================================================
;;;  File          fs-dep.l
;;;  Made          1992/01/29
;;;  LastModified  1992/01/30
;;;  Version       0.1
;;;-----------------------------------------------
;;; Purpose : formula development.
;;;           develop formula into TANKOU SHIKI
;;;-----------------------------------------------
;;; FUNCTIONS
;;;
;;;   fs-dep
;;;   fs-dep+
;;;   fs-dep*(fs-dep-*x,fs-dep*-make-term,fs-dep*-make-aux,fs-dep*-make-aux-2)
;;;          (fs-dep-term+)
;;;   ------
;;;   fs-dep-t(list-sub)
;;;   fs-undep
;;;==========================================================================
(setq *funcs* '(sin cos tan asin acos atan exp log ln lap div rot dx dy
		dsin dcos dtan dexp dlog ))
;;;==========================================================================
;;;==========================================================================
; FS-DEP ;
;
; 【注意】93/08/17に、(^ m 1),(^ m (+ 2 3))等の処理を行う様に改造した(対症療法)
;         fs-dep中の指数が１の時、数式の時の部分がそれ。
;         これは、数式微分で、(diff-fmla-m '(^ m 2) m) などで現れる。
;
;         今、両方とも数字の場合、実際に計算する処理はまだ
;         
;
;;;==========================================================================
(defun fs-dep (lst)
  (cond ((atom lst)                  lst)
	((eq '^  (car lst) )
	 (if(eq 0 (caddr lst)) 1                 ; 指数が0 の時
	   (if(eq 1 (caddr lst))    (cadr lst)   ; 指数が1 の時
	     (if(listp (caddr lst))
		 (list '^ (cadr lst) (fs (caddr lst))) ;指数が数式の時
	       lst))))
	((member (car lst) *funcs*)  lst)

	((eq '+  (car lst) ) (fs-dep+ lst))
	((eq '*  (car lst) ) (fs-dep* lst))
	(t (format t "OH MY GOD IN FS-DEP =>~S~%" lst))))
;;;==========================================================================
;;;==========================================================================
; FS-DEP+ ;
;;;==========================================================================
(defun fs-dep+ (lst)
  (let ((dlst  (mapcar #'fs-dep (cdr lst))))
    (do* ((rlst  '(+)                 )
	  (llst  dlst       (cdr llst))
	  (ptr  (car llst)  (car llst)))
	 ((null llst) rlst)
	 (cond 
	  ((atom ptr)        (setq rlst (append rlst (list ptr))))
	  ((eq '+ (car ptr)) (setq rlst (append rlst
						(cdr ptr))))
	  (t (setq rlst (append rlst (list ptr))))))))


;;;==========================================================================
; FS-DEP* ;
;;;==========================================================================
(defun fs-dep* (lst)
  (let* (( tmp   (fs-dep-*x lst nil nil ) )
	 ( term* (cadr  tmp) )
	 ( term+ (caddr tmp) )                    )
    (cond 
     ((null term+) (cons '* term*))
     ((eq 1 (length term+))
      (fs-dep*-make-term (mapcar #'list (car term+)) term*))
     (t (fs-dep*-make-term 
	 (fs-dep-term+ (cons (mapcar #'list (car term+)) (cdr term+)))
	 term*)))))

;;-----------------
;; fs-dep*-make-term
;;-----------------
(defun fs-dep*-make-term (term+ term*)
  (cons '+
	(mapcar #'(lambda (x) (cons '* (append x term*))) 
		(fs-dep*-make-aux term+))))

(defun fs-dep*-make-aux (lst)
  (cond ((null lst) nil)
	(t
	 (cons (fs-dep*-make-aux-2 (car lst)) 
	       (fs-dep*-make-aux (cdr lst))))))

(defun fs-dep*-make-aux-2 (lst)
  (cond ((atom (car lst)) lst)
	(t 
	 (do* (( dlst lst (cdr dlst))	       
	       ( ptr  (car dlst) (car dlst))
	       ( rlst nil           ))
	      ((null dlst) rlst)
	      (cond ((atom ptr) (setq rlst (append rlst
						    (list ptr))))
		    ((eq '* (car ptr)) ( setq rlst
					      (append rlst (cdr ptr))))
		    (t (setq rlst (append rlst (list ptr)))))))))
;;-----------------	 
;; fs-dep-term+  ; develop term+ [at first, length must not be 1] 
;;   this function returns ( (a b c ) (a b d) (.. ) ) 
;;-----------------
(defun fs-dep-term+ (lst)
  (if(eq 1 (length lst)) (car lst)
    (let ((t1  (car  lst)    )
	  (t2  (cadr lst)    )
	  (remain (cddr lst) ))
      (do* ((dlst t2        (cdr dlst))
	    (ptr (car dlst) (car dlst))
	    (rlst nil                 ))
	   ((null dlst) (fs-dep-term+ (cons rlst remain)))
	   (setq rlst (append rlst
			      (mapcar #'(lambda (x) (cons ptr x)) t1)))))))

;;;==========================================================================
; FS-DEP-*x lst lst* lst+;
;
;  lst   formula to develop
;  lst*  mul 
;  lst+  tashizan
;;;==========================================================================
(defun fs-dep-*x (lst lst* lst+)
  (let (( tmp  nil           ))
    
    (cond 
     ((atom lst) (list  nil (cons lst lst*) lst+))
     ((eq '^ (car lst)) (list  nil (cons lst lst*)  lst+))
     ((member (car lst) *funcs*) (list nil (cons lst lst*) lst+))
     ((eq '+ (car lst)) (list  nil 
			       lst*
			       (cons (cdr (fs-dep lst)) lst+)))

     ((eq '* (car lst))
      (do* (( dlst    (cdr lst)  (cdr dlst))
	    ( rlst     nil                 )
	    ( ptr     (car dlst) (car dlst))
	    ( get     (fs-dep-*x ptr lst* lst+) (fs-dep-*x ptr lst* lst+)))
	   ((null dlst) (list nil lst* lst+))
	   (setq lst* (cadr  get)
		 lst+ (caddr get)))))))

;;;==========================================================================
;;;  FS-DEP-T
;;;  (trivial transformation  (* 0 x) => 0  (+ 0 a) => a (* 1 a) => a
;;;   RECURSIVE VERSION
;;;==========================================================================
(defun fs-dep-t (lst)
  (cond ((atom lst) lst)
	(t
	 (let (( rlst  (mapcar #'fs-dep-t lst) )
;	       ( tlst  (format t "~S~%" (mapcar #'fs-dep-t lst)))
	       )

	   (cond ((atom rlst) rlst)
		 ((and (eq (car rlst) '^)(eq 0 (caddr rlst))) 1)

		 ((eq (car rlst) '*)
		  (if(member 0 rlst) 0
		    (if(member 1 rlst)
			(if(eq 3 (length rlst))
			    (if(eq 1 (cadr rlst)) (caddr rlst)(cadr rlst))
			  (fs-dep-t (list-sub rlst 1)));;in case more 1s in lst
		      rlst)))

		 ((eq (car rlst) '+)
		  (if(member 0 rlst)
		      (if(eq 3 (length rlst))
			  (if(eq 0 (cadr rlst)) (caddr rlst) (cadr rlst))
			(fs-dep-t (list-sub rlst 0))) ;; in case more 0s in lst
		    rlst))
;
;    REMAIN TASK
;
;   case -,/
;
;   if the list is some function, apply this function to the variables of the
;   function!
;
		 (t rlst))))))
;;;==========================================================================
;;;  LIST-SUB
;;;
;;;==========================================================================

(defun list-sub (lst atm)
  (cond ((equal atm (car lst)) (cdr lst))
	(t (cons (car lst) (list-sub (cdr lst) atm)))))



;;;==========================================================================
;;;  FS-UNDEP
;;;
;;;==========================================================================
(defun fs-undep (lst)
  (cond ((atom lst) lst)
	((eq '^ (car lst)) 
	 (do ((num (caddr lst) (- num 1))
	      (rlst (list '* (cadr lst))) )
	     ((eq num 1) rlst)
	     (setq rlst (append rlst (list (cadr lst))))))
	(t (cons (fs-undep (car lst)) (fs-undep (cdr lst))))))
