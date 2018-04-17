ANDROID_PORT	 = libart
ANDROID_DIR		 = art
ANDROID_SOURCES  = runtime/openjdkjvm
ANDROID_BUILDFILES = build/Android.bp runtime/openjdkjvm/Android.bp
ANDROID_SECTIONS = /art_cc_library[@name=libopenjdkjvm]

# jvm.h is included as follows:
# "../../libcore/ojluni/src/main/native/jvm.h"
INC_DIR += $(call select_from_ports,libcore)/libcore/ojluni

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-lib.inc)

#
# FIXME: SUPPRESS WARNINGS! DEVELOPMENT ONLY - REMOVE FOR PRODUCTION!
$(warning SUPPRESSING WARNINGS - REMOVE FOR PRODUCTION!)
CC_OPT += -w

LIBS   += gtest
