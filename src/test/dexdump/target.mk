TARGET = test-dexdump

ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES = dexdump runtime
ANDROID_BUILDFILES = Android.bp test/Android.bp build/Android.bp dexdump/Android.bp
ANDROID_SECTIONS = /art_cc_test[@name=art_dexdump_tests]

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

# Common runtim test class from runtime/
SRC_CC += common_runtime_test.cc

#
# FIXME: SUPPRESS WARNINGS! DEVELOPMENT ONLY - REMOVE FOR PRODUCTION!
$(warning SUPPRESSING WARNINGS - REMOVE FOR PRODUCTION!)
CC_OPT += -w

LIBS := $(filter-out  libart-gtest libartd libartd-disassembler libartd-compiler libgtest libicui18n libicuuc libvixld-arm libvixld-arm64,$(LIBS))
LIBS += stdcxx gtest libart

CC_CXX_WARN_STRICT =
