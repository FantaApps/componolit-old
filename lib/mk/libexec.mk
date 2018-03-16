LIBEXEC_DIR = $(call select_from_repositories,src/lib/libexec)
vpath %.cc $(LIBEXEC_DIR)

INC_DIR += $(LIBEXEC_DIR)
SRC_CC += libexec.cc
LIBS += base
SHARED_LIB = yes
