#include <stdio.h>

void lisplib_make_linear_integrand( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun make-linear-integrand ( lst coff-list )\n");
  LISP_SEND(fp,"  (do* ((rst     lst        (cdr rst))\n");
  LISP_SEND(fp,"	(expr   (car rst)   (car rst))\n");
  LISP_SEND(fp,"	(result  nil                 ))\n");
  LISP_SEND(fp,"       ((null rst) result)\n");
  LISP_SEND(fp,"       (do* ((coff  coff-list  (cdr coff))\n");
  LISP_SEND(fp,"	     (term (car coff)  (car coff))\n");
  LISP_SEND(fp,"	     (sres nil                   ))\n");
  LISP_SEND(fp,"	    ((null coff) (setq result (append result (list sres))))\n");
  LISP_SEND(fp,"	    (setq sres\n");
  LISP_SEND(fp,"		  (append sres\n");
  LISP_SEND(fp,"			  (list (fs (diff-fmla-m expr term))))))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
}
