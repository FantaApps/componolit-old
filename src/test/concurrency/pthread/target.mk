TARGET = test-pthread-rwlock
SRC_CC = main.cc \
    src/tst-rwlock1.c \
    src/tst-rwlock5.c \
    src/tst-rwlock13.c \

LIBS = libc pthread

# To include missing <error.h> used in multiple tests
CC_OPT += -I$(REP_DIR)/src/test/concurrency/pthread/src
#CC_OPT += -Isrc

CC_OPT += -DPTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER_NP=PTHREAD_RWLOCK_INITIALIZER
