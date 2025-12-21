#include <stdio.h>

void lisplib_replace_test_func( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun replace-test-func ( lst )\n");
  LISP_SEND(fp,"  (do* ((rst   lst          (cdr rst))  ;\n");
  LISP_SEND(fp,"	(dlst  (car rst)    (car rst))  ; dlst は連立する各行\n");
  LISP_SEND(fp,"	(tst   *test-funcs* (cdr tst))  ; tst  は試験関数のリストのリスト\n");
  LISP_SEND(fp,"	(func  (car tst)    (car tst))  ; func は各方程式に対する試験関数リスト\n");
  LISP_SEND(fp,"	(result   nil                )  ; result は結果を入れる\n");
  LISP_SEND(fp,"	)\n");
  LISP_SEND(fp,"       ((null rst) result)\n");
  LISP_SEND(fp,"       (do* ((lfunc func (cdr lfunc))   ; local-func ループの基本となる\n");
  LISP_SEND(fp,"	                                ; eqの各行に対する試験関数リスト\n");
  LISP_SEND(fp,"	     (testf (car lfunc) (car lfunc)) ; 今回用いる試験関数シンボル\n");
  LISP_SEND(fp,"	     (res   nil             ))  ; resには結果を入れる\n");
  LISP_SEND(fp,"	    ((null lfunc) (setq result (append result res)))\n");
  LISP_SEND(fp,"	    (setq res (append res \n");
  LISP_SEND(fp,"			      (list (replace-string dlst '$ (car lfunc))))))))\n");
  LISP_SEND(fp,"\n");
}
