TARGET = dex2oat

ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES = dex2oat
ANDROID_BUILDFILES = Android.bp test/Android.bp build/Android.bp dex2oat/Android.bp
ANDROID_SECTIONS = /art_cc_binary[@name=dex2oat]
ANDROID_EXCLUDE_LIBS = valgrind

INC_DIR += $(call select_from_ports,libart)/art/dex2oat/include

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

LIBS += libnativehelper libargv

# FIXME: SUPPRESS WARNINGS! DEVELOPMENT ONLY - REMOVE FOR PRODUCTION!
$(warning SUPPRESSING WARNINGS - REMOVE FOR PRODUCTION!)
CC_OPT += -w
