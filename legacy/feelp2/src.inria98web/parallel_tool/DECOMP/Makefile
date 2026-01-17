#all:	feel.decomp install
all:	
	make feel.decomp

feel.decomp : 	decomp_main.o settei.o hajime.o group.o ncomp.o inter.o number.o seibun.o edgecut.o renke.o syoki.o level.o decomp.o 
	f77 -o feel.decomp decomp_main.o settei.o hajime.o group.o ncomp.o inter.o number.o seibun.o edgecut.o renke.o syoki.o level.o decomp.o 

decomp_main.o : decomp_main.f
	f77 -c -O decomp_main.f

decomp.o : decomp.f
	f77 -c -O decomp.f

renke.o : renke.f
	f77 -c -O renke.f

seibun.o : seibun.f
	f77 -c -O seibun.f	

group.o : group.f
	f77 -c -O  group.f 

ncomp.o : ncomp.f
	f77 -c -O ncomp.f

inter.o : inter.f
	f77 -c -O inter.f

hajime.o : hajime.f
	f77 -c -O hajime.f

number.o : number.f	
	f77 -c -O number.f	

edgecut.o : edgecut.f
	f77 -c -O edgecut.f

settei.o : settei.f
	f77 -c -O settei.f

syoki.o : syoki.f
	f77 -c -O syoki.f

level.o : level.f
	f77 -c -O level.f




