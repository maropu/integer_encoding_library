#-----------------------------------------------------------------------------
#  Makefile - This generates a executable file for test & benchmarks
#
#  Authors:
#      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
#      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
#      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
#-----------------------------------------------------------------------------

CC		= g++
RM		= rm
CP		= cp
CFLAGS		= -O3 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
WFLAGS		= -Wall -Winline
LDFLAGS		= -L/usr/local/lib
INCLUDE		= -I../include
LIBS		= 
SUBDIRS		= ../src/compress ../src/io ../src/utils
SRCS		= $(shell find $(SUBDIRS) -type f -name '*.cpp')
OBJS		= $(subst .cpp,.o,$(SRCS))
OBJS_BENCH	= decbench.o
DECBENCH	= decbench
SCRIPT		= run_decbench.sh

test:		$(DECBENCH)

$(DECBENCH):	$(OBJS) $(OBJS_BENCH)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(OBJS_BENCH) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@
		$(CP) $(SCRIPT) ..

.cpp.o:
		$(CC) $(CFLAGS) $(WFLAGS) $(INCLUDE) $(LDFLAGS) $(LIBS) -c $< -o $@

clean:
		$(RM) -f *.log ../*.output ../$(SCRIPT) $(OBJS) $(OBJS_BENCH) $(DECBENCH)

