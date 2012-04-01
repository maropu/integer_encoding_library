CC		= g++
RM		= rm
#CFLAGS		+= -DNDEBUG -O2 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
CFLAGS		+= -O2 -msse2 -fomit-frame-pointer -fstrict-aliasing -march=nocona
WFLAGS		= -Wall -Winline
LDFLAGS		= -L/usr/local/lib
INCLUDE		= -I./include
LIBS		= 
SUBDIRS		= $(shell find ./src -mindepth 1 -maxdepth 1 -type d)
SRCS		= $(shell find $(SUBDIRS) -type f -name '*.cpp')
OBJS		= $(subst .cpp,.o,$(SRCS))

# For shared lib
SNAME		= libcode
SLINK		= $(SNAME).so
MAJOR		= 0
MINOR		= 1
MICRO		= 0
SHAREDLIB	= $(SLINK).$(MAJOR).$(MINOR).$(MICRO)

# For bench
OBJS_ENC	= src/encoders.o
OBJS_DEC	= src/decoders.o
ENCODERS	= encoders
DECODERS	= decoders

.PHONY:all
all:		$(SLINK)

$(SLINK):	$(SHAREDLIB)
		ln -sf $< $@

$(SHAREDLIB):	$(OBJS)
		$(CC) $(CFLAGS) $(WFLAGS) $(OBJS) $(INCLUDE) $(LDFLAGS) $(LIBS) -fPIC -shared -o $@

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

.PHONY:clean
clean:
		$(RM) -f *.log *.o *.a $(OBJS) $(OBJS_ENC) $(OBJS_DEC) \
			$(ENCODERS) $(DECODERS) $(SLINK) $(SHAREDLIB)
		$(MAKE) -C test clean

