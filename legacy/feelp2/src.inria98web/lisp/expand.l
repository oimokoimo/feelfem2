;-----------------------------------------------------------------------
; リスプのリストの大小関係を定める関数群
;
;
;-----------------------------------------------------------------------
(defun list> (lst1 lst2)
  (cond ((null lst2) t)
	((null lst1) nil)
	((equal (car lst1) (car lst2)) (list> (cdr lst1) (cdr lst2)))
	((listp (car lst1)) (if (listp (car lst2))
				(list> (car lst1) (car lst2))
			      t))
	((listp (car lst2)) nil)
	(t   (string-comp> (car lst1)  (car lst2)))))

(defun string-comp> ( a b)
  (cond ((numberp a) (if (numberp b) (> a b) nil))
	((numberp b) t)
	(t (string< (string b) (string a)))))
;
(defun list< (lst2 lst1)
  (cond ((null lst2) t)
	((null lst1) nil)
	((equal (car lst1) (car lst2)) (list> (cdr lst1) (cdr lst2)))
	((listp (car lst1)) (if (listp (car lst2))
				(list> (car lst1) (car lst2))
			      t))
	((listp (car lst2)) nil)
	(t   (string-comp> (car lst1)  (car lst2)))))

(defun string-comp< ( b a )
  (cond ((numberp a) (if (numberp b) (> a b) nil))
	((numberp b) t)
	(t (string< (string b) (string a)))))

;-----------------------------------------------------------------------
;  補助ソート関数
;
;-----------------------------------------------------------------------
(defun sbl-sort (sbl-lst)
  (sort sbl-lst #'string-comp>))
(defun lst-sort (lst-lst)
  (sort lst-lst #'list>))

;-----------------------------------------------------------------------
;  補助関数  リストの引き算
;-----------------------------------------------------------------------
(defun lst-sub (lst sbl)
  (cond ((atom lst) lst)
	((equal (car lst) sbl) (cdr lst))
	(t (cons (car lst) (lst-sub (cdr lst) sbl)))))







