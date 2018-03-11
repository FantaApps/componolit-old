TARGET = test-genode_exec

SRC_CC = main.cc exec_genode.cc
LIBS += base stdcxx libc

vpath %.cc $(call select_from_repositories,src/lib/libart)
INC_DIR += $(call select_from_ports,libart)/art/runtime

CC_CXX_WARN_STRICT =
