SRC_CC += main.cc
CC_OPT += -g -Wall -Werror -fno-builtin
CC_CXX_WARN_STRICT =

LIBNATIVEBRIDGE_TESTS_DIR := $(call select_from_ports,core)/system/core/libnativebridge/tests
vpath %.cpp $(LIBNATIVEBRIDGE_TESTS_DIR)
vpath %.cc $(REP_DIR)/src/test/libnativebridge

INC_DIR += $(LIBNATIVEBRIDGE_TESTS_DIR)

LIBS += libc stdcxx liblog gtest libnativehelper libnativebridge libcore_includes libargv
