#
#       Makefile        "@(#)%M% %I% %E% %U%"
#
#	div4	 Makefile
#
#
SHELL=/bin/sh
CFLAGS=-O
FFLAGS=  $(ADDITONALFFLAGS)
.SUFFIXES:
.SUFFIXES:.out .o .c .fs .e .r .f .y .l .s .p
SRCS=bndnod.f input.f main.f output.f renum4.f rmkjac.f
OBJS=div4.rev.o bndnod.o input.o main.o output.o renum4.o rmkjac.o
HDRS=
SCCS=sccs
DESTDIR=
LIBES=
LDFLAGS=

feel.Div.exe:  ${OBJS}
	${FC} ${FFLAGS} ${LDFLAGS} -o feel.Div.exe ${OBJS} ${LIBES}

setrev:
	(echo '/DO NOT DELETE/+1,$$d';echo 'w') | ed - div4.rev.c
	echo '/*' >> div4.rev.c
	what ${HDRS} ${SRCS} >> div4.rev.c
	echo '*/' >> div4.rev.c

makerev:
	echo '/*' > div4.rev.c
	echo ' *      program revision control module' >> div4.rev.c
	echo ' *      name:   div4' >> div4.rev.c
	echo ' */' >> div4.rev.c
	echo 'static char sccsid[] = "@(#)div4 :I: :E:";  /* sccs ident */' | tr ':' '%' >> div4.rev.c
	echo >> div4.rev.c
	echo '/* DO NOT DELETE THIS LINE */' >> div4.rev.c
	echo '/*' >> div4.rev.c
	echo '*/' >> div4.rev.c

update:
	get -e ${SCCS}/s.div4.rev.c
	make setrev
	delta ${SCCS}/s.div4.rev.c
	get ${SCCS}/s.div4.rev.c

lint:
	lint ${SRCS} 2>&1 >error.LINT

install:
	cp div4 div4.temp
	strip div4
	cp div4 ${DESTDIR}/
	mv div4.temp div4

clean:
	rm -f div4 *.o

#clobber: clean
#	rm -f div4.rev.c ${HDRS} ${SRCS}

print:  Print_Time
Print_Time:     Makefile div4.rev.c ${HDRS} ${SRCS}
	@spr $? | lpr
	@touch Print_Time

wc:
	@cstep div4.rev.c ${HDRS} ${SRCS}

size:
	size div4

sources: div4.rev.c ${HDRS} ${SRCS}
${HDRS} ${SRCS}:
	get -t ${SCCS}/s.$@

div4.rev.c:
	-if [ -f ${SCCS}/s.$@ ] ; then get ${SCCS}/s.$@ ; \
	else make -i -f Makefile makerev ; fi

depend:
	makemake -f Makefile  ${HDRS} ${SRCS}

.fs.o:;fs -c ${FFLAGS} $*.fs

# DO NOT DELETE THIS LINE -- makemake depend uses it

