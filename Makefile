CC       = gcc
APP      = etherscrape
SRCDIR   = src
OBJDIR   = obj
INCLUDES = -I./inc
CFLAGS   = -Wall -pedantic -c $(INCLUDES)
LDFLAGS  = -lpcap
SRCS    := $(shell find $(SRCDIR) -name '*.c')
SRCDIRS := $(shell find . -name '*.c' -exec dirname {} \; | uniq) #Gets all directories with .c files
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(APP)

debug: CFLAGS += -DDEBUG_MODE -g
debug: all

$(APP): buildrepo $(OBJS)
	@mkdir -p `dirname $@`
	@echo "Linking $@..."
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c
	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(APP)

buildrepo:
	@$(call make-repo)

define make-repo
   for dir in $(SRCDIRS); \
   do \
	mkdir -p $(OBJDIR)/$$dir; \
   done
endef


define make-depend
  $(CC) -MM       \
        -MF $3    \
        -MP       \
        -MT $2    \
        $(CFLAGS) \
        $1
endef
