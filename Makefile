# Many small programs in one project. Two kinds of program:
#
#   A folder that has a main.c, e.g. hello/ or stats/: every .c file in
#   that folder (subfolders too) belongs to the program.
#   Any other .c file with its own main(), e.g. exercises/sum.c: a program
#   on its own. Keep many of them in one folder (exercises/ here).
#   A main.c next to other files with a main() is one of those too:
#   pointers/main.c + pointers/seg_fault.c -> pointers/main, pointers/seg_fault.
#
#   Both also get every .c file under common/, if that folder exists
#   (helpers shared by all programs).
#   Add, rename or delete files and folders freely: nothing to edit here.
#
#   make                          build all programs
#   make PROG=hello               build one   -> build/hello
#   make PROG=exercises/sum       build one   -> build/exercises/sum
#   make run PROG=hello           build it, then run it
#   make list                     list the programs
#   make clean                    delete build/
#
# In Emacs, F5 / Cmd+Shift+B / Ctrl+Option+N fill in PROG from the file
# you are in (see .dir-locals.el).
#
# Rules: no spaces in names; don't put a folder program inside another one.

BUILD  := build
CC     := clang
CFLAGS := -std=c17 -g -O0 -Wall -Wextra -Icommon/include
LDLIBS := -lm

# Every .c file in the project (build/ and .git/ skipped), e.g. hello/greet.c
ALL_SRCS := $(sort $(patsubst ./%,%,$(shell find . -name '*.c' -not -path './$(BUILD)/*' -not -path './.git/*')))
# Every .c file that defines main(), e.g. hello/main.c, exercises/sum.c
MAIN_LINE  := ^[[:space:]]*(int|void)[[:space:]]+main[[:space:]]*\(
MAIN_FILES := $(shell grep -lE '$(MAIN_LINE)' $(ALL_SRCS) /dev/null)
# main.c files with another main() in their folder, e.g. pointers/main.c
SHARED_MAINS := $(foreach m,$(filter %/main.c,$(MAIN_FILES)),\
                  $(if $(filter-out $(m),$(filter $(dir $(m))%,$(MAIN_FILES))),$(m)))
# Every folder with a main.c of its own, e.g. hello
DIR_PROGS := $(sort $(patsubst %/main.c,%,$(filter-out $(SHARED_MAINS),\
               $(filter %/main.c,$(ALL_SRCS)))))
# Every other file with a main(), without .c, e.g. exercises/sum, pointers/main
FILE_PROGS := $(sort $(patsubst %.c,%,$(filter-out $(addsuffix /main.c,$(DIR_PROGS)) main.c,\
                $(MAIN_FILES))))
PROGS := $(DIR_PROGS) $(FILE_PROGS)

# clangd (completion, errors, go-to-definition in Emacs) reads
# compile_commands.json: one entry per .c file, with its compile flags.
# Listing every file lets clangd index the whole project, so Cmd+B jumps
# to a function's code in another .c file, not just to its declaration.
# Rewritten when a .c file is added or deleted, or this Makefile changes.
ALL_LIST := $(BUILD)/all-sources.txt
$(shell mkdir -p $(BUILD); echo '$(ALL_SRCS)' | cmp -s - $(ALL_LIST) || echo '$(ALL_SRCS)' > $(ALL_LIST))

compile_commands.json: Makefile $(ALL_LIST)
	@{ echo '['; sep=' '; for f in $(ALL_SRCS); do \
	     printf '%s{"directory": "%s", "file": "%s", "command": "%s %s -c %s"}\n' \
	       "$$sep" "$(CURDIR)" "$$f" "$(CC)" "$(CFLAGS)" "$$f"; sep=','; \
	   done; echo ']'; } > $@

ifeq ($(PROG),)
# ---- No PROG given: all programs -------------------------------------------

.DEFAULT_GOAL := all

all: compile_commands.json
	@for p in $(PROGS); do $(MAKE) --no-print-directory PROG=$$p || exit 1; done

list:
	@printf '%s\n' $(PROGS)

run:
	@echo 'Which program? make run PROG=<folder>. Programs:'; printf '  %s\n' $(PROGS); exit 1

else
# ---- One program: PROG=hello or PROG=exercises/sum ---------------------------

# (PROG=exercises/sum.c works too.)
override PROG := $(patsubst %.c,%,$(patsubst %/,%,$(PROG)))
APP  := $(BUILD)/$(PROG)
COMMON_SRCS := $(shell find common -name '*.c' 2>/dev/null)

# The program's own files + the shared ones. Sorted so the list is stable.
ifneq ($(filter $(PROG),$(DIR_PROGS)),)
# A folder program: all .c files in the folder.
SRCS := $(sort $(shell find $(PROG) -name '*.c') $(COMMON_SRCS))
else ifneq ($(wildcard $(PROG).c),)
# A one-file program.
SRCS := $(sort $(PROG).c $(COMMON_SRCS))
else
$(error $(PROG) is not a program. Programs: $(PROGS))
endif
# hello/x.c -> build/obj/hello/x.o
OBJS := $(SRCS:%.c=$(BUILD)/obj/%.o)
# Each .o gets a .d file listing the headers it includes, so changing a
# header rebuilds exactly the .c files that use it.
DEPS := $(OBJS:.o=.d)

# Relink when a .c file is added or deleted, not only when one changes:
# build/<name>.sources is rewritten only when the file list changes.
SRC_LIST := $(APP).sources
# Clear build leftovers in the way of this program's paths. Happens after
# a rename, e.g. string_functions/main.c (program build/string_functions,
# a file) -> string_functions/str_functions.c (program
# build/string_functions/str_functions, needs a folder there). Only
# build/ is touched; anything removed is rebuilt when needed.
$(shell p=$(BUILD); for s in $(subst /, ,$(patsubst %/,%,$(dir $(PROG)))); do \
          p=$$p/$$s; if [ -e $$p ] && [ ! -d $$p ]; then rm -f $$p $$p.sources; fi; done; \
        if [ -d $(APP) ]; then rm -rf $(APP); fi)
$(shell mkdir -p $(dir $(APP)); echo '$(SRCS)' | cmp -s - $(SRC_LIST) || echo '$(SRCS)' > $(SRC_LIST))

.DEFAULT_GOAL := $(APP)

$(APP): $(OBJS) $(SRC_LIST) | compile_commands.json
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)

run: $(APP)
	./$(APP)

-include $(DEPS)
endif

# ---- Shared rules ------------------------------------------------------------

$(BUILD)/obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD)

.PHONY: all list run clean
