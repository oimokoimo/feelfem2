element.lib :: cordinate_check.c element_order.c element_parse.c get_etype_no.c get_freedom_by_element_name.c
	cl /c cordinate_check.c element_order.c element_parse.c get_etype_no.c get_freedom_by_element_name.c
	lib /OUT:element.lib cordinate_check.obj element_order.obj element_parse.obj get_etype_no.obj get_freedom_by_element_name.obj
