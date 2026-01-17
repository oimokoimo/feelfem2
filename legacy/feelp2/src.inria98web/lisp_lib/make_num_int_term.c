#include <stdio.h>

void lisplib_make_num_integral_term( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun make-num-integral-term-main ()\n");
  LISP_SEND(fp,"   (progn (setq *fname*  (format nil \"est~D-~D-~D.dat\" \n");
  LISP_SEND(fp,"				 *solve-no* *elem-no* *integral-no* ))\n");
  LISP_SEND(fp,"	  (setq *fp*     (open *fname* :direction :output) )\n");
  LISP_SEND(fp,"	  (format *fp* \"~D~%%\" (length *num-integral-term*))\n");
  LISP_SEND(fp,"	  (make-num-integral-term) \n");
  LISP_SEND(fp,"	  (close *fp*)\n");
  LISP_SEND(fp,"	  )\n");
  LISP_SEND(fp,"   )\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun make-num-integral-term ()\n");
  LISP_SEND(fp,"  (do* ((dlst *num-integral-term* (cdr dlst))\n");
  LISP_SEND(fp,"	(rst  (car dlst)          (car dlst)))\n");
  LISP_SEND(fp,"       ((null dlst) t)\n");
  LISP_SEND(fp,"       (make-num-int-term rst)))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun make-num-int-term ( lst )\n");
  LISP_SEND(fp,"  (cond  ((equal lst 'x) (format *fp* \"qx  0   qx ~%%\"))\n");
  LISP_SEND(fp,"	 ((equal lst 'y) (format *fp* \"qy  0   qy ~%%\"))\n");
  LISP_SEND(fp,"	 ((equal lst 'z) (format *fp* \"qz  0   qz ~%%\"))\n");
  LISP_SEND(fp,"	 ((atom lst) \n");
  LISP_SEND(fp,"	  (progn (format *fp* \"q~S 0 \"  lst)\n");
  LISP_SEND(fp,"		 (exp-print-fp (eval lst) *fp*)\n");
  LISP_SEND(fp,"		 )\n");
  LISP_SEND(fp,"	  )\n");
  LISP_SEND(fp,"	 (t (make-num-int-term-diffs lst))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun make-num-int-term-diffs ( lst )\n");
  LISP_SEND(fp,"  (let ((sbl  (car  lst))\n");
  LISP_SEND(fp,"	(term (cadr lst)))\n");
  LISP_SEND(fp,"    (cond ((equal 'dx sbl) (do-num-int-term-diffs term '(r)   'x     1 ))\n");
  LISP_SEND(fp,"	  ((equal 'dy sbl) (do-num-int-term-diffs term '(s)   'y    10 ))\n");
  LISP_SEND(fp,"	  ((equal 'dz sbl) (do-num-int-term-diffs term '(t)   'z   100 ))\n");
  LISP_SEND(fp,"	  ((equal 'dxx sbl) (do-num-int-term-diffs term '(r r) 'xx   2 ))\n");
  LISP_SEND(fp,"	  ((equal 'dxy sbl) (do-num-int-term-diffs term '(r s) 'xy  11 ))\n");
  LISP_SEND(fp,"	  ((equal 'dxz sbl) (do-num-int-term-diffs term '(r t) 'xz 101 ))\n");
  LISP_SEND(fp,"	  ((equal 'dyy sbl) (do-num-int-term-diffs term '(s s) 'yy  20 ))\n");
  LISP_SEND(fp,"	  ((equal 'dyz sbl) (do-num-int-term-diffs term '(s t) 'yz 110 ))\n");
  LISP_SEND(fp,"	  ((equal 'dzz sbl) (do-num-int-term-diffs term '(t t) 'zz 200 ))\n");
  LISP_SEND(fp,"	  (t (format t \"微分 ~S には対応していません(make-num-int-term-diffs)\" sbl)))))\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun do-num-int-term-diffs (lst  diff-lst diff-smbl flag)\n");
  LISP_SEND(fp,"  (progn (format *fp* \"q~S_~S   ~S \" lst diff-smbl flag)\n");
  LISP_SEND(fp,"	 (do* ((dlst diff-lst         (cdr dlst))\n");
  LISP_SEND(fp,"	       (dif  (car dlst)       (car dlst))\n");
  LISP_SEND(fp,"	       (rst  (eval lst)                 ))\n");
  LISP_SEND(fp,"	      ((null dlst) \n");
  LISP_SEND(fp,"	       (exp-print-fp (fs rst) *fp*))\n");
  LISP_SEND(fp,"	      (setq rst (fs (diff-fmla-m rst dif)))\n");
  LISP_SEND(fp,"		     )))\n");
}
