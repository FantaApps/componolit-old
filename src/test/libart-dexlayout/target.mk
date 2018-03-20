TARGET = libart-dexlayout_test

ANDROID_PORT	   = libart
ANDROID_DIR		   = art
ANDROID_SOURCES    = dexlayout runtime
ANDROID_BUILDFILES = build/Android.bp test/Android.bp dexlayout/Android.bp
ANDROID_SECTIONS   = /art_cc_test[@name=art_dexlayout_tests]

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

LIBS := $(filter-out  libart-gtest libartd libartd-disassembler libartd-compiler libgtest libicui18n libicuuc libvixld-arm libvixld-arm64,$(LIBS))

CC_OPT += -Wno-error=unused-parameter

# Common runtim test class from runtime/
SRC_CC += common_runtime_test.cc

#
# FIXME: SUPPRESS WARNINGS! DEVELOPMENT ONLY - REMOVE FOR PRODUCTION!
$(warning SUPPRESSING WARNINGS - REMOVE FOR PRODUCTION!)
CC_OPT += -w

LIBS   += gtest libart unwind libargv

# Silence excessive getpid() and getrlimit() warnings
LIBS += libsilence
