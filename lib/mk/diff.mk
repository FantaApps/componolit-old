DIFFUTILS_DIR = $(call select_from_ports,diff)/diff
DIFF_DIR = $(call select_from_repositories,/src/lib/test/diff)

vpath % $(DIFFUTILS_DIR)/src
vpath % $(DIFFUTILS_DIR)/lib
INC_DIR += $(DIFFUTILS_DIR)/src $(DIFFUTILS_DIR)/lib $(DIFF_DIR)

SRC_C = \
	analyze.c \
	c-stack.c \
	cmpbuf.c \
	diff.c \
	error.c \
	exclude.c \
	exitfail.c \
	filenamecat.c \
	io.c \
	normal.c \
	mbchar.c \
	progname.c \
	regex.c \
	util.c \
	xasprintf.c \
	xvasprintf.c \
	xmalloc.c \

CC_OPT = -DO_BINARY=0 -DGNULIB_FILENAMECAT -D_GNU_SOURCE -w
LIBS += libc
SHARED_LIB = yes

CC_CXX_WARN_STRICT =
