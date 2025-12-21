#include <stdio.h>

void lisplib_fs( fp )
     FILE *fp;
{
  LISP_SEND(fp,"(defun fs (lst)\n");
  LISP_SEND(fp,"  (fs-sort (fs-term-bind (fs-dep (fs-dep-t lst)))))\n");
}
