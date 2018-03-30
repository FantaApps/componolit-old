TARGET = dex2oat

ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES = dex2oat
ANDROID_BUILDFILES = Android.bp test/Android.bp build/Android.bp dex2oat/Android.bp
ANDROID_SECTIONS = /art_cc_binary[@name=dex2oat]

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

LIBS += libnativehelper libargv
