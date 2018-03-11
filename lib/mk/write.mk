vpath % $(call select_from_repositories,src/lib/test/write)

SRC_C += main.c
LIBS += libc
SHARED_LIB = yes
CC_CXX_WARN_STRICT =
