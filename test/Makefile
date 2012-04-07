CC		= g++
RM		= rm
CP		= cp
CFLAGS		= -DDEBUG -std=gnu++0x -O2 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
#CFLAGS		= -std=gnu++0x -O2 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
WFLAGS		= -Wall -Winline
LDFLAGS		= -L/usr/local/lib
INCLUDE		= -I../include
LIBS		= 
SUBDIRS		= $(shell find ../src -mindepth 1 -maxdepth 1 -type d)
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

