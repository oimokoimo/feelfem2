(load "make-num-integral-term.l")
(load "../lisp_c/exp-print.l")
(load "../lisp_exec/feel-package.l")

(setq *num-integral-term* '(p1_1 (dx p1_2)))
(setq p1_1 '(* r r ))
(setq p1_2 '(+ (* r r -1) (* r s )))
(setq *solve-no* 2)
(setq *elem-no* 1)
(setq *integral-no* 3)

(defun a ()
  (make-num-integral-term-main))
