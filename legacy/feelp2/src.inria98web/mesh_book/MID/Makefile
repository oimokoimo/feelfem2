#
#       Makefile        "@(#)%M% %I% %E% %U%"
#
#	mid	 Makefile
#
#
SHELL=/bin/sh
CFLAGS=-O
.SUFFIXES:
.SUFFIXES:.out .o .c .fs .e .r .f .y .l .s .p
SRCS=input.f main.f newpnt.f nodelm.f output.f reelm.f renode.f
OBJS=mid.rev.o input.o main.o newpnt.o nodelm.o output.o reelm.o renode.o
HDRS=
SCCS=sccs
DESTDIR=
LIBES=
LDFLAGS= 
FFLAGS= $(ADDITONALFFLAGS)

feel.Mid.exe:  ${OBJS}
	f77 ${FFLAGS} ${LDFLAGS} -o feel.Mid.exe ${OBJS} ${LIBES}

setrev:
	(echo '/DO NOT DELETE/+1,$$d';echo 'w') | ed - mid.rev.c
	echo '/*' >> mid.rev.c
	what ${HDRS} ${SRCS} >> mid.rev.c
	echo '*/' >> mid.rev.c

makerev:
	echo '/*' > mid.rev.c
	echo ' *      program revision control module' >> mid.rev.c
	echo ' *      name:   mid' >> mid.rev.c
	echo ' */' >> mid.rev.c
	echo 'static char sccsid[] = "@(#)mid :I: :E:";  /* sccs ident */' | tr ':' '%' >> mid.rev.c
	echo >> mid.rev.c
	echo '/* DO NOT DELETE THIS LINE */' >> mid.rev.c
	echo '/*' >> mid.rev.c
	echo '*/' >> mid.rev.c

update:
	get -e ${SCCS}/s.mid.rev.c
	make setrev
	delta ${SCCS}/s.mid.rev.c
	get ${SCCS}/s.mid.rev.c

lint:
	lint ${SRCS} 2>&1 >error.LINT

install:
	cp mid mid.temp
	strip mid
	cp mid ${DESTDIR}/
	mv mid.temp mid

clean:
	rm -f mid *.o

#clobber: clean
#	rm -f mid.rev.c ${HDRS} ${SRCS}

print:  Print_Time
Print_Time:     Makefile mid.rev.c ${HDRS} ${SRCS}
	@spr $? | lpr
	@touch Print_Time

wc:
	@cstep mid.rev.c ${HDRS} ${SRCS}

size:
	size mid

sources: mid.rev.c ${HDRS} ${SRCS}
${HDRS} ${SRCS}:
	get -t ${SCCS}/s.$@

mid.rev.c:
	-if [ -f ${SCCS}/s.$@ ] ; then get ${SCCS}/s.$@ ; \
	else make -i -f Makefile makerev ; fi

depend:
	makemake -f Makefile  ${HDRS} ${SRCS}

.fs.o:;fs -c ${FFLAGS} $*.fs

# DO NOT DELETE THIS LINE -- makemake depend uses it

