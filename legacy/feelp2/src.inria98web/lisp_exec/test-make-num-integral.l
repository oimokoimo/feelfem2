(setq *dimension* 3)
(setq *fem-integrand* '( (dx u)))
(setq *load-integrand* '( u))
(setq *shape-function* '( a b))
(setq *fem-funcs* '(a b u))


(load "make-num-integral.l")
(load "../lisp/make-fem-term-list.l")
