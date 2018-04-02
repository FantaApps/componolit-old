TARGET = libart-compiler_test

ANDROID_PORT	   = libart
ANDROID_DIR		   = art
ANDROID_SOURCES    = compiler
ANDROID_BUILDFILES = build/Android.bp test/Android.bp compiler/Android.bp
ANDROID_SECTIONS   = /art_cc_test[@name=art_compiler_tests]

ANDROID_EXCLUDE_CC = \
	jni/jni_compiler_test.cc \
	utils/intrusive_forward_list_test.cc \

# Common tests from runtime/ and compiler/
SRC_CC += common_compiler_test.cc
SRC_CC += common_runtime_test.cc

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

LIBS := $(filter-out  libart-gtest libartd libartd-disassembler libartd-compiler libgtest libicui18n libicuuc libvixld-arm libvixld-arm64,$(LIBS))
LIBS   += gtest libart unwind libargv libart-compiler vixl

CC_OPT += -Wno-error=unused-parameter

# FIXME: SUPPRESS WARNINGS! DEVELOPMENT ONLY - REMOVE FOR PRODUCTION!
$(warning SUPPRESSING WARNINGS - REMOVE FOR PRODUCTION!)
CC_OPT += -w

# Silence excessive getpid() and getrlimit() warnings
LIBS += libsilence
