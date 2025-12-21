#include <stdio.h>

void lisplib_expand( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun list> (lst1 lst2)\n");
  LISP_SEND(fp,"  (cond ((null lst2) t)\n");
  LISP_SEND(fp,"	((null lst1) nil)\n");
  LISP_SEND(fp,"	((equal (car lst1) (car lst2)) (list> (cdr lst1) (cdr lst2)))\n");
  LISP_SEND(fp,"	((listp (car lst1)) (if (listp (car lst2))\n");
  LISP_SEND(fp,"				(list> (car lst1) (car lst2))\n");
  LISP_SEND(fp,"			      t))\n");
  LISP_SEND(fp,"	((listp (car lst2)) nil)\n");
  LISP_SEND(fp,"	(t   (string-comp> (car lst1)  (car lst2)))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun string-comp> ( a b)\n");
  LISP_SEND(fp,"  (cond ((numberp a) (if (numberp b) (> a b) nil))\n");
  LISP_SEND(fp,"	((numberp b) t)\n");
  LISP_SEND(fp,"	(t (string< (string b) (string a)))))\n");
  LISP_SEND(fp,"(defun list< (lst2 lst1)\n");
  LISP_SEND(fp,"  (cond ((null lst2) t)\n");
  LISP_SEND(fp,"	((null lst1) nil)\n");
  LISP_SEND(fp,"	((equal (car lst1) (car lst2)) (list> (cdr lst1) (cdr lst2)))\n");
  LISP_SEND(fp,"	((listp (car lst1)) (if (listp (car lst2))\n");
  LISP_SEND(fp,"				(list> (car lst1) (car lst2))\n");
  LISP_SEND(fp,"			      t))\n");
  LISP_SEND(fp,"	((listp (car lst2)) nil)\n");
  LISP_SEND(fp,"	(t   (string-comp> (car lst1)  (car lst2)))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun string-comp< ( b a )\n");
  LISP_SEND(fp,"  (cond ((numberp a) (if (numberp b) (> a b) nil))\n");
  LISP_SEND(fp,"	((numberp b) t)\n");
  LISP_SEND(fp,"	(t (string< (string b) (string a)))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun sbl-sort (sbl-lst)\n");
  LISP_SEND(fp,"  (sort sbl-lst #'string-comp>))\n");
  LISP_SEND(fp,"(defun lst-sort (lst-lst)\n");
  LISP_SEND(fp,"  (sort lst-lst #'list>))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun lst-sub (lst sbl)\n");
  LISP_SEND(fp,"  (cond ((atom lst) lst)\n");
  LISP_SEND(fp,"	((equal (car lst) sbl) (cdr lst))\n");
  LISP_SEND(fp,"	(t (cons (car lst) (lst-sub (cdr lst) sbl)))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
}
