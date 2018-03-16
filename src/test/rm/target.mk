TARGET = rm
vpath % $(call select_from_repositories,src/test/rm)

SRC_C = rm.c
LIBS += libc libargv
CC_CXX_WARN_STRICT =
