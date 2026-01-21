ls -l *.f | awk '{printf("make_cfile %s <%s\n",$8,$8)}'
