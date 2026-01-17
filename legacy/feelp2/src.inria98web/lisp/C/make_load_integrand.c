#include <stdio.h>

void lisplib_make_load_integrand( fp )
     FILE *fp;
{
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun make-load-integrand (weak-form coff-lst)\n");
  LISP_SEND(fp,"  (do* (( rst   nil                  )\n");
  LISP_SEND(fp,"	( dlst  weak-form  (cdr dlst))\n");
  LISP_SEND(fp,"	( lst   (car dlst) (car dlst)))\n");
  LISP_SEND(fp,"       ((null dlst)  rst )\n");
  LISP_SEND(fp,"       (setq rst (append rst \n");
  LISP_SEND(fp,"			  (list (fs (list '* '-1 (zero-replace lst coff-lst))))))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun zero-replace (lst coff-lst)\n");
  LISP_SEND(fp,"  (if (atom lst)\n");
  LISP_SEND(fp,"      (if (member lst coff-lst) 0  lst)  ; coff-lstにあれば０なければそのまま\n");
  LISP_SEND(fp,"    (cons (zero-replace (car lst) coff-lst)\n");
  LISP_SEND(fp,"	  (zero-replace (cdr lst) coff-lst))))\n");
}
