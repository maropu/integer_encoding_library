CC		= g++
CCVERSION	:= $(strip $(shell $(CC) --version))
CFLAGS		= -DDEBUG -O2 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
CFLAGS		+= $(if $(filter 4.4.% 4.5.% 4.6.% 4.7.%,$(CCVERSION)), -std=gnu++0x,)
WFLAGS		= -Wall -Wno-unused-function
WFLAGS		+= $(if $(filter 4.6.% 4.7.%,$(CCVERSION)), -Wno-unused-but-set-variable,)
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
		cp $(SCRIPT) ..

.cpp.o:
		$(CC) $(CFLAGS) $(WFLAGS) $(INCLUDE) $(LDFLAGS) $(LIBS) -c $< -o $@

clean:
		rm -f *.log ../*.output ../$(SCRIPT) $(OBJS) $(OBJS_BENCH) $(DECBENCH)

