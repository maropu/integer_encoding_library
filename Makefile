CC		= g++
#CC		= ccache g++
CCVERSION	:= $(strip $(shell $(CC) --version))
CFLAGS		+= -DNDEBUG -O2 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
CFLAGS		+= $(if $(filter 4.4.% 4.5.% 4.6.%,$(CCVERSION)), -std=gnu++0x,)
CFLAGS		+= $(if $(filter 4.7.%,$(CCVERSION)), -std=gnu++11,)
WFLAGS		= -Wall
WFLAGS		+= $(if $(filter 4.6.% 4.7.%,$(CCVERSION)), -Wno-unused-but-set-variable,)
LDFLAGS		= -L/usr/local/lib
INCLUDE		= -I./include
LIBS		= 
SUBDIRS		= $(shell find ./src -mindepth 1 -maxdepth 1 -type d)
SRCS		= $(shell find $(SUBDIRS) -type f -name '*.cpp')
OBJS		= $(subst .cpp,.o,$(SRCS))

# For shared lib
NAME		= libcode
SNAME		= $(NAME).so
MAJOR		= 0
MINOR		= 2
RELEASE		= 0
SHAREDLIB	= $(SNAME).$(MAJOR).$(MINOR).$(RELEASE)
SLINK1		= $(SNAME).$(MAJOR).$(MINOR)
SLINK2		= $(SNAME).$(MAJOR)
SLINK3		= $(SNAME)
SFLAGS		= -fPIC -shared
#SFLAGS		= -Wl, -soname=$(SLINK).$(MAJOR) -fPIC -shared

# For bench
OBJS_ENC	= src/encoders.o
OBJS_DEC	= src/decoders.o
ENCODERS	= encoders
DECODERS	= decoders

# For check
SCRIPT_COV	= .check-coverage.sh
SCRIPT_CHK	= test/test_run.sh
OBJS_CHK	= test/decbench.o
CHECKERS	= decbench

.PHONY:all
all:		$(SNAME)

$(SNAME):	$(SHAREDLIB)
		ln -sf $(SHAREDLIB) $(SLINK1)
		ln -sf $(SLINK1) $(SLINK2)
		ln -sf $(SLINK2) $(SLINK3)

$(SHAREDLIB):	$(OBJS)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(INCLUDE) $(LDFLAGS) $(LIBS) $(SFLAGS) -o $@

.PHONY:bench
bench:		$(ENCODERS) $(DECODERS)

$(ENCODERS):	$(OBJS) $(OBJS_ENC)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(OBJS_ENC) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@

$(DECODERS):	$(OBJS) $(OBJS_DEC)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(OBJS_DEC) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@

.cpp.o:
		$(CC) $(CXXFLAGS) $(CFLAGS) $(WFLAGS) $(INCLUDE) $(LDFLAGS) $(LIBS) -fPIC -c $< -o $@

.PHONY:check
check:		$(CHECKERS)
		cp $(SCRIPT_CHK) .

$(CHECKERS):	$(OBJS) $(OBJS_CHK)
		$(CC) $(CXXFLAGS) $(CFLAGS) $(WFLAGS) $(OBJS) $(OBJS_CHK) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@

.PHONY:clean
clean:
		rm -f *.dat *.log *.gcda *.gcno *.info *.o *.a \
			$(notdir $(SCRIPT_CHK)) $(OBJS) $(OBJS_ENC) $(OBJS_DEC) \
			$(ENCODERS) $(DECODERS) $(CHECKERS) $(SHAREDLIB) $(SLINK1) $(SLINK2) $(SLINK3)
		$(MAKE) -C test clean
		$(MAKE) -C src clean

