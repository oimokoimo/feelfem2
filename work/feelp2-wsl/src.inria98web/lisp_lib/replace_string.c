#include <stdio.h>

void lisplib_replace_string( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun replace-string (lst from to)\n");
  LISP_SEND(fp,"  (cond ((atom lst) (if (equal lst from) to  lst))\n");
  LISP_SEND(fp,"	(t (cons (replace-string (car lst) from to)\n");
  LISP_SEND(fp,"		 (replace-string (cdr lst) from to)))))\n");
}
