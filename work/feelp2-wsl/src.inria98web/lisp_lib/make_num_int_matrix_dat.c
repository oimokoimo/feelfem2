#include <stdio.h>

void lisplib_make_num_int_matrix_dat( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun make-num-int-matrix-dat ()\n");
  LISP_SEND(fp,"   (progn (setq *fname*  (format nil \"ecal~D-~D-~D.dat\" \n");
  LISP_SEND(fp,"				 *solve-no* *elem-no* *integral-no* ))\n");
  LISP_SEND(fp,"	  (setq *fp*     (open *fname* :direction :output) )\n");
  LISP_SEND(fp,"	  (make-num-int-matrix-mat)    ; 要素小行列部分\n");
  LISP_SEND(fp,"	  (make-num-int-matrix-load)   ; ロードベクトル\n");
  LISP_SEND(fp,"	  (close *fp*)\n");
  LISP_SEND(fp,"	  )\n");
  LISP_SEND(fp,"   )\n");
  LISP_SEND(fp,"(defun make-num-int-matrix-dat-nonlinear ()\n");
  LISP_SEND(fp,"   (progn (setq *fname*  (format nil \"ecal~D-~D-~D.dat\" \n");
  LISP_SEND(fp,"				 *solve-no* *elem-no* *integral-no* ))\n");
  LISP_SEND(fp,"	  (setq *fp*     (open *fname* :direction :output) )\n");
  LISP_SEND(fp,"	  (make-num-int-matrix-mat)              ; 要素小行列部分(ヤコビアン)\n");
  LISP_SEND(fp,"	  (make-num-int-matrix-nonlinear-load)   ; 残差ベクトル\n");
  LISP_SEND(fp,"	  (close *fp*)\n");
  LISP_SEND(fp,"	  )\n");
  LISP_SEND(fp,"   )\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"(defun make-num-int-matrix-mat  ()\n");
  LISP_SEND(fp,"  (do* (( dlst *fem-integrand* (cdr dlst) )\n");
  LISP_SEND(fp,"	( rlst (car dlst)      (car dlst) ))\n");
  LISP_SEND(fp,"       ((null dlst) t)\n");
  LISP_SEND(fp,"       (do* ( ( dlst2  rlst       (cdr dlst2) )\n");
  LISP_SEND(fp,"	      ( rlst2 (car dlst2) (car dlst2) ) )\n");
  LISP_SEND(fp,"	    ((null dlst2) t)\n");
  LISP_SEND(fp,"	    (exp-print-fp ( trans-num-int-integrand  rlst2 ) *fp* ))))\n");
  LISP_SEND(fp,"	\n");
  LISP_SEND(fp,"(defun make-num-int-matrix-load ()\n");
  LISP_SEND(fp,"  (do* (( dlst *load-integrand* (cdr dlst) )\n");
  LISP_SEND(fp,"	( rlst (car dlst)      (car dlst) ))\n");
  LISP_SEND(fp,"       ((null dlst) t)\n");
  LISP_SEND(fp,"       (exp-print-fp ( trans-num-int-integrand  rlst ) *fp* )))\n");
  LISP_SEND(fp,"	\n");
  LISP_SEND(fp,"(defun make-num-int-matrix-nonlinear-load ()\n");
  LISP_SEND(fp,"  (do* (( dlst *fem-weak-eq* (cdr dlst) )\n");
  LISP_SEND(fp,"	( rlst (car dlst)      (car dlst) ))\n");
  LISP_SEND(fp,"       ((null dlst) t)\n");
  LISP_SEND(fp,"       (exp-print-fp ( trans-num-int-integrand  rlst ) *fp* )))\n");
  LISP_SEND(fp,"	\n");
  LISP_SEND(fp,"\n");
  LISP_SEND(fp,"	\n");
}
