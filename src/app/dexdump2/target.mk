TARGET = dexdump2

ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES = dexdump
ANDROID_BUILDFILES = Android.bp test/Android.bp build/Android.bp dexdump/Android.bp
ANDROID_SECTIONS = /art_cc_binary[@name=dexdump2]

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

LIBS += libnativehelper

CC_OPT += -Wno-error=maybe-uninitialized
