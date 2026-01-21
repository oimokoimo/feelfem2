#include <stdio.h>

void lisplib_do_d_formula( fp )
     FILE *fp;
{
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun do-d-formula ( lst )\n");
  LISP_SEND(fp,"  (do* ((rst   lst       (cdr rst))   ; 式の残り\n");
  LISP_SEND(fp,"	(expr  (car rst) (car rst))   ; 各式\n");
  LISP_SEND(fp,"	(result  nil              ))  ; 結果\n");
  LISP_SEND(fp,"       ((null rst) result)\n");
  LISP_SEND(fp,"       (setq  result \n");
  LISP_SEND(fp,"	      (append result (list (fs (d-formula expr)))))))\n");
}
