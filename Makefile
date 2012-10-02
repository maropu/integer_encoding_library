CC		= g++
CCVERSION	:= $(strip $(shell $(CC) --version))
#CFLAGS		+= -O2 -msse2
CFLAGS		+= -DNDEBUG -O9 -msse2 -fomit-frame-pointer --param max-inline-insns-single=1000 \
			--param inline-unit-growth=1000 --param max-completely-peel-times=100 -march=nocona
CFLAGS		+= $(if $(filter 4.4.% 4.5.% 4.6.%,$(CCVERSION)), -std=gnu++0x,)
CFLAGS		+= $(if $(filter 4.7.%,$(CCVERSION)), -std=gnu++11,)
WFLAGS		= -Wall -Wextra -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wfloat-equal \
			-Wno-strict-aliasing -Wpointer-arith -Wswitch-enum -Woverloaded-virtual -Weffc++  -Wno-unused
# WFLAGS		+= -Wconversion
WFLAGS		+= $(if $(filter 4.6.% 4.7.%,$(CCVERSION)), -Wno-unused-but-set-variable,)
LDFLAGS		= -L/usr/local/lib
INCLUDE		= -I./include
LIBS		= -lpthread
SRCS		= $(shell find ./src ! -regex ".*test.*" -name '*.cpp' -type f)
OBJS		= $(subst .cpp,.o,$(SRCS))

# vcompress
VSRCS		= $(shell find ./tool -name '*.cpp' -type f)
VOBJS		= $(subst .cpp,.o,$(VSRCS))
VCOMPRESS	= vcompress
VSCRIPT		= run-perfs.sh

# For general tests
TSRCS		= $(shell find ./src -name '*_unitest.cpp' -type f)
TOBJS		= $(subst .cpp,.o,$(TSRCS))
TEST		= encoding_utest
INSPECT		= .inspection.sh

# For google tests
GDIR		= .utest/gtest-1.6.0
GINCLUDE	= -I$(GDIR)/include -I$(GDIR)
GHEADERS	= $(GDIR)/include/gtest/*.h $(GDIR)/include/gtest/internal/*.h
GSRCS		= $(GDIR)/src/*.cc $(GDIR)/src/*.h $(GTEST_HEADERS)

.PHONY:all
all:		$(VCOMPRESS)

$(VCOMPRESS):	$(OBJS) $(VOBJS)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(VOBJS) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@
		cp tool/$(VSCRIPT) .

.cpp.o:
		$(CC) $(CXXFLAGS) $(CFLAGS) $(WFLAGS) $(INCLUDE) $(LDFLAGS) $(LIBS) -c $< -o $@

.PHONY:check
check:
		./$(INSPECT)

.PHONY:test
test:		$(TEST)

$(TEST):	gtest-all.o $(TOBJS) $(OBJS)
		$(CC) $(CXXFLAGS) $(CFLAGS) $(TOBJS) $(OBJS) $(LIBS) gtest-all.o -o $@

gtest-all.o:	$(GSRCS)
		$(CC) $(GINCLUDE) -c $(GDIR)/src/gtest-all.cc

$(TOBJS):
		$(CC) $(CXXFLAGS) $(CPPFLAGS) $(CFLAGS) $(INCLUDE) $(GINCLUDE) \
		$(LDFLAGS) -c $(addsuffix .cpp, $(basename $@)) -o $@

.PHONY:clean
clean:
		rm -f *.dat *.output *.log *.gcda *.gcno *.info *.o *.a \
			$(VCOMPRESS) $(VSCRIPT) $(TEST)
		$(MAKE) -C src clean
		$(MAKE) -C tool clean

