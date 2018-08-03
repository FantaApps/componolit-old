TARGET = libcutils_test

ANDROID_PORT	 = core
ANDROID_DIR		 = system/core/libcutils/tests
ANDROID_SECTIONS = /cc_test[@name=libcutils_test] /cc_test[@name=libcutils_test]/target/android
ANDROID_EXCLUDE_CC = PropertiesTest.cpp AshmemTest.cpp sched_policy_test.cpp trace-dev_test.cpp

include $(call select_from_repositories,lib/mk/android-prg.inc)

CC_OPT = -Wall -DINT16_MAX=0xffff -fpermissive
SRC_CC += main.cc
LIBS   += libargv gtest
