#include <stdio.h>

void lisplib_fs_sort( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun fs-sort (lst)\n");
  LISP_SEND(fp,"  (if (null lst) 0\n");
  LISP_SEND(fp,"    (do ((dlst lst (cdr dlst))\n");
  LISP_SEND(fp,"	 (rlst nil           ))\n");
  LISP_SEND(fp,"	((null dlst) (if (eq 1 (length rlst)) (car rlst)\n");
  LISP_SEND(fp,"			     (cons '+ rlst)))\n");
  LISP_SEND(fp,"	(let (( item (caar dlst) )\n");
  LISP_SEND(fp,"	      ( cof  (cdar dlst) ) )\n");
  LISP_SEND(fp,"	  (cond ((numberp item) (setq rlst (cons cof rlst)))\n");
  LISP_SEND(fp,"		((eq 1 cof    ) (setq rlst (cons item rlst)))\n");
  LISP_SEND(fp,"		((atom item   ) (setq rlst (cons (cons '* (list cof item)) rlst)))\n");
  LISP_SEND(fp,"		((eq '* (car item)) \n");
  LISP_SEND(fp,"		 (setq rlst (cons (cons '* (cons cof (cdr item))) rlst)))\n");
  LISP_SEND(fp,"		(t (setq rlst (cons (cons '* (list cof item)) rlst))))))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"	 \n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
}
