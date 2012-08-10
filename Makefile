CC		= ccache g++
CCVERSION	:= $(strip $(shell $(CC) --version))
CFLAGS		+= -DNDEBUG -O2 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
CFLAGS		+= $(if $(filter 4.4.% 4.5.% 4.6.%,$(CCVERSION)), -std=gnu++0x,)
CFLAGS		+= $(if $(filter 4.7.%,$(CCVERSION)), -std=gnu++11,)
#WFLAGS		= -Wall -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wfloat-equal \
			-Wpointer-arith -Wswitch-enum -Woverloaded-virtual -Weffc++
#WFLAGS		+= -Wextra -Wconversion -Wstrict-aliasing=2
WFLAGS		+= $(if $(filter 4.6.% 4.7.%,$(CCVERSION)), -Wno-unused-but-set-variable,)
LDFLAGS		= -L/usr/local/lib
INCLUDE		= -I./include
LIBS		= -lpthread
SRCS		= $(shell find ./src ./tool ! -regex ".*test.*" -name '*.cpp' -type f)
OBJS		= $(subst .cpp,.o,$(SRCS))

# vcompress
VCOMPRESS	= vcompress

# For general test
TEST_SRCS	= $(shell find ./src -name '*.cpp' -type f)
TEST_OBJS	= $(subst .cpp,.o,$(TEST_SRCS))
TEST		= encoding_utest
INSPECT		= .inspection.sh

# For gtest
GDIR		= .utest/gtest-1.6.0
GINCLUDE	= -I$(GDIR)/include -I$(GDIR)
GHEADERS	= $(GDIR)/include/gtest/*.h $(GDIR)/include/gtest/internal/*.h
GSRCS		= $(GDIR)/src/*.cc $(GDIR)/src/*.h $(GTEST_HEADERS)

.PHONY:all
all:		$(VCOMPRESS)

$(VCOMPRESS):	$(OBJS)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@

.cpp.o:
		$(CC) $(CXXFLAGS) $(CFLAGS) $(WFLAGS) $(INCLUDE) $(LDFLAGS) $(LIBS) -fPIC -c $< -o $@

.PHONY:check
check:
		./$(INSPECT)

.PHONY:test
test:		$(TEST)

$(TEST):	gtest-all.o $(TEST_OBJS)
		$(CC) $(CXXFLAGS) $(CFLAGS) $(TEST_OBJS) $(LIBS) gtest-all.o -o $@

gtest-all.o:	$(GSRCS)	
		$(CC) $(GINCLUDE) -c $(GDIR)/src/gtest-all.cc

$(TEST_OBJS):
		$(CC) $(CXXFLAGS) $(CPPFLAGS) $(CFLAGS) $(INCLUDE) $(GINCLUDE) \
		$(LDFLAGS) -c $(addsuffix .cpp, $(basename $@)) -o $@

.PHONY:clean
clean:
		rm -f *.dat *.log *.gcda *.gcno *.info *.o *.a $(VCOMPRESS) $(TEST)
		$(MAKE) -C src clean
		$(MAKE) -C tool clean

