#include <stdio.h>

void lisplib_make_fem_term_list( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun make-fem-term-list ( lst )\n");
  LISP_SEND(fp,"  (cond \n");
  LISP_SEND(fp,"   ( (atom lst) \n");
  LISP_SEND(fp,"     (cond \n");
  LISP_SEND(fp,"      ((equal 'x lst) (add-make-fem-term-list 'x))\n");
  LISP_SEND(fp,"      ((equal 'y lst) (add-make-fem-term-list 'y))\n");
  LISP_SEND(fp,"      ((equal 'z lst) (add-make-fem-term-list 'z))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"      ((member lst *fem-funcs*) (add-make-fem-term-list lst))\n");
  LISP_SEND(fp,"      (t nil)))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dx) \n");
  LISP_SEND(fp,"     (progn (add-make-fem-term-list lst)\n");
  LISP_SEND(fp,"	   (if (not (equal *dimension* 1))\n");
  LISP_SEND(fp,"	       (add-make-fem-term-list (cons 'dy (list (cadr lst)))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"	   (if (equal *dimension* 3)\n");
  LISP_SEND(fp,"	       (add-make-fem-term-list (cons 'dz (list (cadr lst)))))\n");
  LISP_SEND(fp,"	   ))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dy) (add-make-fem-term-list lst)\n");
  LISP_SEND(fp,"	   (add-make-fem-term-list (cons 'dx (list (cadr lst))))\n");
  LISP_SEND(fp,"	   (if (equal *dimension* 3)\n");
  LISP_SEND(fp,"	       (add-make-fem-term-list (cons 'dz (list (cadr lst))))\n");
  LISP_SEND(fp,"	     ))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dz) (progn (add-make-fem-term-list lst)\n");
  LISP_SEND(fp,"			       (add-make-fem-term-list (cons 'dx (list (cadr lst))))\n");
  LISP_SEND(fp,"			       (add-make-fem-term-list (cons 'dy (list (cadr lst))))))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dxx) (add-make-fem-term-list lst))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dxy) (add-make-fem-term-list lst))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dxz) (add-make-fem-term-list lst))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dyy) (add-make-fem-term-list lst))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dyz) (add-make-fem-term-list lst))\n");
  LISP_SEND(fp,"   ( (eq (car lst) 'dzz) (add-make-fem-term-list lst))\n");
  LISP_SEND(fp,"   (t (progn (make-fem-term-list (car lst))\n");
  LISP_SEND(fp,"	     (make-fem-term-list (cdr lst))))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun add-make-fem-term-list ( lst )\n");
  LISP_SEND(fp,"  (if(list-member lst *num-integral-term*) nil\n");
  LISP_SEND(fp,"    (setq *num-integral-term* (cons lst *num-integral-term*))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun list-member (mem  lst)\n");
  LISP_SEND(fp,"  (do ((dlst lst (cdr dlst))\n");
  LISP_SEND(fp,"       (flag nil           ))\n");
  LISP_SEND(fp,"      ((null dlst) flag)\n");
  LISP_SEND(fp,"      (if(equal mem (car dlst))\n");
  LISP_SEND(fp,"	  (setq flag t))))\n");
}
