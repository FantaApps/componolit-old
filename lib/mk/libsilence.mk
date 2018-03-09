vpath % $(call select_from_repositories,src/lib/libsilence)

SRC_C += silence.c
LIBS += libc
SHARED_LIB = yes
CC_CXX_WARN_STRICT =
