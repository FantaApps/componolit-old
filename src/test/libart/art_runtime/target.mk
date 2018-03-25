TARGET = art_runtime_test

ANDROID_PORT	   = libart
ANDROID_DIR		   = art
ANDROID_BUILDFILES = build/Android.bp test/Android.bp runtime/Android.bp
ANDROID_SECTIONS   = /art_cc_test[@name=art_runtime_tests] /art_cc_library[@name=libart-runtime-gtest]

ANDROID_EXCLUDE_CC += gc/space/dlmalloc_space_random_test.cc
ANDROID_EXCLUDE_CC += gc/space/rosalloc_space_random_test.cc

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

LIBS := $(filter-out  libart-gtest libartd libartd-disassembler libartd-compiler libgtest libicui18n libicuuc libvixld-arm libvixld-arm64,$(LIBS))

CC_OPT += -Wno-error=unused-parameter

#
# FIXME: SUPPRESS WARNINGS! DEVELOPMENT ONLY - REMOVE FOR PRODUCTION!
$(warning SUPPRESSING WARNINGS - REMOVE FOR PRODUCTION!)
CC_OPT += -w
LIBS   += gtest posix valgrind dlmalloc libcore_includes libart icu unwind libargv

# Silence excessive getpid() and getrlimit() warnings
LIBS += libsilence
