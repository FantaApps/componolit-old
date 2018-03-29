TARGET = dex2oat_test

ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES += dex2oat
ANDROID_BUILDFILES += Android.bp test/Android.bp build/Android.bp dex2oat/Android.bp
ANDROID_SECTIONS += /art_cc_test[@name=art_dex2oat_tests] /cc_library_headers[@name=dex2oat_headers]

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

# FIXME: This should be pulled in by /cc_library_headers[@name=dex2oat_headers] but isn't for some reason
INC_DIR += $(call select_from_ports,libart)/art/dex2oat/include

# Common runtim test class from runtime/
SRC_CC += common_runtime_test.cc

#
# FIXME: SUPPRESS WARNINGS! DEVELOPMENT ONLY - REMOVE FOR PRODUCTION!
$(warning SUPPRESSING WARNINGS - REMOVE FOR PRODUCTION!)
CC_OPT += -w

LIBS := $(filter-out  libart-gtest libartd libartd-disassembler libartd-compiler libgtest libicui18n libicuuc libvixld-arm libvixld-arm64,$(LIBS))
LIBS += stdcxx gtest libart

CC_CXX_WARN_STRICT =
