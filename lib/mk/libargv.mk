vpath % $(call select_from_repositories,src/lib/libargv)

SRC_CC += libargv.cc
LIBS += base libc
SHARED_LIB = yes
