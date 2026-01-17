# Makefile: a makefile
# Location: $(TOP)/feelfem/src/. 
# Executed-By: $(TOP)/feelfem/src
#

YACC     = yacc
LEX      = lex
PLUSPLUS = g++ 
OPTION   =
TOP      = 
INCLUDE  = -I../class

X11LIB   = ../Xplot++/Xplot++.a -L/usr/X11R6/lib -lX11

.SUFFIXES:    .lex

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

CC                      = $(PLUSPLUS)


SUBDIRS =   SL_feelfem90       \
	    SL_aistpcp90       \
            SL_feelfem90DRAMA  \
            SL_feelP2          \
            SL_MT_P2CRS        \
            SL_MT_ff90PAMGCRS  \
            SL_MT_ff90AMGCRS   \
            SL_MT_ff90smpiMUMPSCA  \
            SL_LIB_feelP2Achim \
            SL_MT_P2Skyline    \
            SL_LIB_feelP2Skyline \
            SL_LIB_feelfem90Skyline \
            SL_MT_ff90SKYLINE

all : src_libs
	ar rv SourceLibrary.a */*.o
	ranlib SourceLibrary.a 


src_libs :
	@for i in $(SUBDIRS); \
		do (cd $$i ; make) ; \
	done


clean :
	@for i in $(SUBDIRS); \
 		do (cd $$i ; make clean) ; \
	done
	rm SourceLibrary.a
	
