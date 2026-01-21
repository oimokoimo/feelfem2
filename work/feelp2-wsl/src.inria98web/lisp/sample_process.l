(setq *eq* '(+ (* (dx u)(dx $)) (* (dy u)(dy $))
	       (* v (exp (* q u)) $)))

; 方程式の一つ


; リプレース関数
(defun replace (lst old new)
  (cond ((eq lst old) new)
        ((atom lst )  lst)
        (t (cons (replace (car lst) old new) (replace (cdr lst) old new)))))


(setq *eq-2* (replace *eq* 'u '(+ (* m1 q1) (* m2 q2)(* m3 q3)(* m4 q4))))
(setq *eq-3* (replace *eq-2* '$ 'q1))

(setq *fem-funcs* '(q1 q2 q3 q4)')

