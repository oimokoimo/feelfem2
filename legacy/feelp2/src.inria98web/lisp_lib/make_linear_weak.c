#include <stdio.h>

void lisplib_make_linear_weak( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun make-linear-weak  ( )\n");
  LISP_SEND(fp,"  (progn \n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"    (setq *fem-weak-eq* (symbol-eval-replace-quad  *fem-weak-eq* \n");
  LISP_SEND(fp,"						   *eval-vars* \n");
  LISP_SEND(fp,"						   *quad-vars*    ) )\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"    (setq *fem-weak-eq* (replace-test-func *fem-weak-eq*))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"    (setq *fem-weak-eq* (mapcar #'minus-convert *fem-weak-eq*))\n");
  LISP_SEND(fp,"    (setq *fem-weak-eq* (do-d-formula  *fem-weak-eq*) )\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"    (setq *fem-integrand* (make-linear-integrand *fem-weak-eq* *coff-vect*))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"    (setq *load-integrand* (make-load-integrand *fem-weak-eq* *coff-vect*))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"    ) ; progn の終わリ\n");
  LISP_SEND(fp,"  )   ; defun の終わり\n");
  LISP_SEND(fp,"\n");
}
