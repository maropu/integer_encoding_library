CC		= g++
RM		= rm
#CFLAGS		+= -DNDEBUG -O3 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
CFLAGS		+= -O3 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
#WFLAGS		= -Wall -Winline
WFLAGS		= -Wall
LDFLAGS		= -L/usr/local/lib
INCLUDE		= -I./include
LIBS		= 
SUBDIRS		= $(shell find ./src -mindepth 1 -maxdepth 1 -type d)
SRCS		= $(shell find $(SUBDIRS) -type f -name '*.cpp')
OBJS		= $(subst .cpp,.o,$(SRCS))
SHARED		= libcode.so

# For bench
OBJS_ENC	= src/encoders.o
OBJS_DEC	= src/decoders.o
ENCODERS	= encoders
DECODERS	= decoders

# For gtest
GTEST_DIR	= .utest/gtest-1.6.0
CPPFLAGS	+= -I$(GTEST_DIR)/include -I$(GTEST_DIR)
GTEST_HEADERS	= $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS	= $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
SRCS_UTEST	= $(shell find ./test/utest -type f -name '*.cpp')
OBJS_UTEST	= $(subst .cpp,.o,$(SRCS_UTEST))
CODERS_UTEST	= codersUTest

.PHONY:all
all:		$(SHARED)

$(SHARED):	$(OBJS)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(INCLUDE) $(LDFLAGS) $(LIBS) -shared -o $@

.cpp.o:
		$(CC) $(CFLAGS) $(WFLAGS) $(INCLUDE) $(LDFLAGS) $(LIBS) -c $< -o $@

.PHONY:bench
bench:		$(ENCODERS) $(DECODERS)

$(ENCODERS):	$(OBJS) $(OBJS_ENC)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(OBJS_ENC) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@

$(DECODERS):	$(OBJS) $(OBJS_DEC)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(OBJS_DEC) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@

.PHONY:test
test:
		$(MAKE) -C test test

.PHONY:utest
utest:		$(OBJS_UTEST) $(OBJS) gtest_main.a
		$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -lpthread $^ -o $(CODERS_UTEST)

gtest-all.o:	$(GTEST_SRCS)	
		$(CC) $(CPPFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o:	$(GTEST_SRCS)
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a:	gtest-all.o
		$(AR) $(ARFLAGS) $@ $^

gtest_main.a:	gtest-all.o gtest_main.o
		$(AR) $(ARFLAGS) $@ $^

$(OBJS_UTEST):	$(SRCS_UTEST)	
		$(CC) $(CPPFLAGS) $(CFLAGS) $(WFLAGS) $(INCLUDE) $(LDFLAGS) $(LIBS) -c $< -o $@

.PHONY:clean
clean:
		$(RM) -f *.log *.o *.a $(OBJS) $(OBJS_ENC) $(OBJS_DEC) $(OBJS_UTEST) \
			$(ENCODERS) $(DECODERS) $(SHARED) $(CODERS_UTEST)
		$(MAKE) -C test clean

