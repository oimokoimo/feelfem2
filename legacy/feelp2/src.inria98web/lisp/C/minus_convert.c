#include <stdio.h>

void lisplib_minus_convert( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun minus-convert ( lst )\n");
  LISP_SEND(fp,"  (cond  ((atom lst) lst)\n");
  LISP_SEND(fp,"	 ((equal '- (car lst))\n");
  LISP_SEND(fp,"	  (if (eq (length lst) 2)\n");
  LISP_SEND(fp,"	      (list '* '-1 (minus-convert (cadr lst)))\n");
  LISP_SEND(fp,"	    (append (list '+ (minus-convert (cadr lst)))\n");
  LISP_SEND(fp,"		    (mapcar #'minus-ichi (cddr lst)))))\n");
  LISP_SEND(fp,"	 (t (cons (car lst)\n");
  LISP_SEND(fp,"		  (mapcar #'minus-convert (cdr lst))))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun minus-ichi ( lst )\n");
  LISP_SEND(fp,"  (list '* -1 (minus-convert lst)))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"	\n");
  LISP_SEND(fp,"	 \n");
}
