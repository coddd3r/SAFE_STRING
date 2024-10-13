#arcfour makefile 

# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables

CC=gcc
INCDIRS=. 

CFLAGS=  -fPIC -Wall -Wextra -g -O2 $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)
LDFLAGS=  -shared -ldl -D_GNU_SOURCE
# LIBFLAGS = 

TARGET_LIB = safestring.so                       # target lib

CODEDIRS=.
#INCDIRS=. #can be list
LIBINCDIR=/usr/include
LIBDIR=/usr/lib/x86_64-linux-gnu
# INCFILES=

ALL_CFILES=$(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
CFILES=$(filter-out $(CODEDIRS)/test.c, $(ALL_CFILES))


DEPDIR = .deps
DEPFILES=$(patsubst %.c, %.d, $(CFILES))
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPFILES)
BINARIES = $(CFILES:.c=)
TARGETS = $(BINARIES) $(TARGET_LIB)

OBJS = $(CFILES:.c=.o)                    # object file

.PHONY: all clean
all: clean $(TARGETS)

$(TARGET_LIB):$(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^       
	

%.o:%.c $(DEPDIR)/%.d | $(DEPDIR)
	$(CC) -c $(CFLAGS) $(DEPFLAGS) -o $@ $<

# example: example.o 
#gcc arcfour.o example.o -o example -Wall -O2

$(BINARIES): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	clear && rm -f $(TARGETS) $(BINARY) $(OBJS) $(DEPFILES) *.out *.o

install:
	scp ${TARGET_LIB} ${LIBDIR}
	scp arcfour.h ${LIBINCDIR}  
	ldconfig

$(DEPDIR):
	@mkdir -p $(DEPDIR)

$(DEPFILES):

include $(wildcard $(DEPFILES))