cat | awk '{printf("%s(){printf(\"%s\\n\");}\n",$1,$1);}' >oimo

