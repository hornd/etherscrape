DEBUG=1
DEBUGFLAG=
CC=gcc
LDFLAGS=-lpcap
CFLAGS=-Wall -pedantic
PROG=etherscrape
SRCDIR=src
OBJDIR=obj
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))

ifeq ($(DEBUG),1)
	CFLAGS+=-g
endif

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJECTS)
#	@echo "Linking $@"
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
#	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(PROG)