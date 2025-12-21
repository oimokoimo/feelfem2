#include <stdio.h>

void lisplib_trans_num_int_integrand( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun trans-num-int-integrand ( lst )\n");
  LISP_SEND(fp,"  (cond ((atom lst) lst)\n");
  LISP_SEND(fp,"	((equal 'dx  (car lst)) (make-num-quad-diff-term (cadr lst) 'x))\n");
  LISP_SEND(fp,"	((equal 'dy  (car lst)) (make-num-quad-diff-term (cadr lst) 'y))\n");
  LISP_SEND(fp,"	((equal 'dz  (car lst)) (make-num-quad-diff-term (cadr lst) 'z))\n");
  LISP_SEND(fp,"	((equal 'dxx (car lst)) (make-num-quad-diff-term (cadr lst) 'xx))\n");
  LISP_SEND(fp,"	((equal 'dxy (car lst)) (make-num-quad-diff-term (cadr lst) 'xy))\n");
  LISP_SEND(fp,"	((equal 'dxz (car lst)) (make-num-quad-diff-term (cadr lst) 'xz))\n");
  LISP_SEND(fp,"	((equal 'dyy (car lst)) (make-num-quad-diff-term (cadr lst) 'yy))\n");
  LISP_SEND(fp,"	((equal 'dyz (car lst)) (make-num-quad-diff-term (cadr lst) 'yz))\n");
  LISP_SEND(fp,"	((equal 'dzz (car lst)) (make-num-quad-diff-term (cadr lst) 'zz))\n");
  LISP_SEND(fp,"	(t (cons (car lst)\n");
  LISP_SEND(fp,"		 (mapcar #'trans-num-int-integrand (cdr lst))))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun make-num-quad-diff-term (term lst)\n");
  LISP_SEND(fp,"  (let (( str   (format  nil \"q~S_~S_~Dp\" term lst *integral-no*)) )\n");
  LISP_SEND(fp,"    (read-from-string str)))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
}
