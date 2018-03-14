TARGET = write

vpath % $(call select_from_repositories,src/test/write)

SRC_C += write.c
LIBS += libc libargv
SHARED_LIB = yes
