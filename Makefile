CC        = gcc
APP       = etherscrape
SRCDIR    = src
OBJDIR    = obj
INCLUDES  = -I./inc
CFLAGS    = -Wall -pedantic -c $(INCLUDES)
LDFLAGS   = -lpcap
DEBUG_LVL = 3
SRCS    := $(shell find $(SRCDIR) -name '*.c')
SRCDIRS := $(shell find . -name '*.c' -exec dirname {} \; | uniq) #Gets all directories with .c files
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean

# TODO: Revisit the gcc flags in make-depend and figure out why changes
#       in header files aren't causing all to recompile. In the meantime
#       do a full recompile (for now it's relatively fast)
all:	clean $(APP)

debug:	CFLAGS += -DDEBUG_MODE -DDEBUG_LEVEL=$(DEBUG_LVL) -g
debug:  all

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
