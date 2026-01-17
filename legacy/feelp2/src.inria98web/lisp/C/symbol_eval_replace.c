#include <stdio.h>

void lisplib_symbol_eval_replace( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun symbol-eval-replace-quad (lst mem cancel-mem)\n");
  LISP_SEND(fp,"  (symbol-eval-replace lst (list-minus mem cancel-mem)))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun list-minus  ( a  b )\n");
  LISP_SEND(fp,"  (do* (( rst     nil                      )\n");
  LISP_SEND(fp,"	( member  a           (cdr member) )\n");
  LISP_SEND(fp,"	( mem    (car member) (car member) ))\n");
  LISP_SEND(fp,"       ((null member) rst)\n");
  LISP_SEND(fp,"       (if(not (member mem  b)) (setq rst ( cons mem rst)))))\n");
  LISP_SEND(fp,"	\n");
  LISP_SEND(fp,"(defun symbol-eval-replace (lst mem)\n");
  LISP_SEND(fp,"  (cond ((atom lst) (if (member lst mem) (eval lst) lst))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"	((and (eq 3 (length lst))      \n");
  LISP_SEND(fp,"	      (member (cadr lst) mem)\n");
  LISP_SEND(fp,"	      (eq '^ (car lst))\n");
  LISP_SEND(fp,"	      (numberp (caddr lst)))\n");
  LISP_SEND(fp,"	 (do ((rlst  '(*)   )\n");
  LISP_SEND(fp,"	      (n    (caddr lst) (- n 1)))\n");
  LISP_SEND(fp,"	     ((eq 0 n) rlst)\n");
  LISP_SEND(fp,"	     (setq rlst \n");
  LISP_SEND(fp,"		   (append rlst (list (eval (cadr lst)))))))\n");
  LISP_SEND(fp,"	(t (cons (symbol-eval-replace (car lst) mem)\n");
  LISP_SEND(fp,"		 (symbol-eval-replace (cdr lst) mem)))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
}
