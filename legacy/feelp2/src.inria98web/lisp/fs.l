;----------------------------------------------------------------------
;    数式簡素化主関数
;
;    Lang/src/LISP VERSION
;----------------------------------------------------------------------
;(load "/usr/feel/feel_p2/src/lisp/fs-dep.l")
;(load "/usr/feel/feel_p2/src/lisp/fs-term-bind.l")
;(load "/usr/feel/feel_p2/src/lisp/fs-sort.l")
;(load "/usr/feel/feel_p2/src/lisp/expand.l")
(defun fs (lst)
  (fs-sort (fs-term-bind (fs-dep (fs-dep-t lst)))))
