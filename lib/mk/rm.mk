vpath % $(call select_from_repositories,src/lib/test/rm)

SRC_C = rm.c
LIBS += libc
SHARED_LIB = yes
CC_CXX_WARN_STRICT =
