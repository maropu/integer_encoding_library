#-----------------------------------------------------------------------------
#  Makefile - This generates two executable files: Encoders & Decodes
#
#  Authors:
#      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
#      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
#      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
#-----------------------------------------------------------------------------

CC		= g++
RM		= rm
CFLAGS		= -O3 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
WFLAGS		= -Wall -Winline
LDFLAGS		= -L/usr/local/lib
INCLUDE		= -I./include
LIBS		= 
SUBDIRS		= $(shell find ./src -mindepth 1 -maxdepth 1 -type d)
SRCS		= $(shell find $(SUBDIRS) -type f -name '*.cpp')
OBJS		= $(subst .cpp,.o,$(SRCS))
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
SRCS_UTEST	+= $(SRCS)
OBJS_UTEST	= $(subst .cpp,.o,$(SRCS_UTEST))
CODERS_UTEST	= codersUTest

.PHONY:all
all:		$(ENCODERS) $(DECODERS)

$(ENCODERS):	$(OBJS) $(OBJS_ENC)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(OBJS_ENC) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@

$(DECODERS):	$(OBJS) $(OBJS_DEC)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(OBJS_DEC) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $(WFLAGS) $(INCLUDE) $(CPPFLAGS) $(LDFLAGS) $(LIBS) -c $< -o $@

.PHONY:test
test:
		$(MAKE) -C test test

.PHONY:utest
utest:		$(OBJS_UTEST) gtest_main.a
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -lpthread $^ -o $(CODERS_UTEST)

gtest-all.o:	$(GTEST_SRCS)	
		$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o:	$(GTEST_SRCS)
		$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a:	gtest-all.o
		$(AR) $(ARFLAGS) $@ $^

gtest_main.a:	gtest-all.o gtest_main.o
		$(AR) $(ARFLAGS) $@ $^
		
.PHONY:clean
clean:
		$(RM) -f *.log *.o *.a $(OBJS) $(OBJS_ENC) $(OBJS_DEC) $(OBJS_UTEST) \
			$(ENCODERS) $(DECODERS) $(CODERS_UTEST)
		$(MAKE) -C test clean

