TARGET = dump

vpath % $(call select_from_repositories,src/test/dump)

SRC_C += dump.c
LIBS += libc libargv
OPT_CC += -Wall -Wextra -Werror
