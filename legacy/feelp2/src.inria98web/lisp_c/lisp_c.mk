lisp_c.lib :: lisp_exp_print.c
	cl /c lisp_exp_print.c
	lib /OUT:lisp_c.lib lisp_exp_print.obj
